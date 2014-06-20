#include "etherswitch.h"

#include <inttypes.h>

using namespace etherswitch;

ethswitch::ethswitch()
{

}



ethswitch::~ethswitch()
{
	// ...
}



void
ethswitch::handle_timeout(int opaque)
{

}




void
ethswitch::request_flow_stats()
{
#if 0
	std::map<cofdpt*, std::map<uint16_t, std::map<cmacaddr, struct fibentry_t> > >::iterator it;

	for (it = fib.begin(); it != fib.end(); ++it) {
		cofdpt *dpt = it->first;

		cofflow_stats_request req;

		switch (dpt->get_version()) {
		case OFP10_VERSION: {
			req.set_version(dpt->get_version());
			req.set_table_id(OFPTT_ALL);
			req.set_match(cofmatch(OFP10_VERSION));
			req.set_out_port(OFPP_ANY);
		} break;
		case OFP12_VERSION: {
			req.set_version(dpt->get_version());
			req.set_table_id(OFPTT_ALL);
			cofmatch match(OFP12_VERSION);
			//match.set_eth_dst(cmacaddr("01:80:c2:00:00:00"));
			req.set_match(match);
			req.set_out_port(OFPP_ANY);
			req.set_out_group(OFPG_ANY);
			req.set_cookie(0);
			req.set_cookie_mask(0);
		} break;
		default: {
			// do nothing
		} break;
		}

		fprintf(stderr, "etherswitch: calling FLOW-STATS-REQUEST for dpid: 0x%"PRIu64"\n",
				dpt->get_dpid());

		send_flow_stats_request(dpt, /*flags=*/0, req);
	}

	register_timer(ETHSWITCH_TIMER_FLOW_STATS, flow_stats_timeout);
#endif
}



void
ethswitch::handle_flow_stats_reply(cofdpt *dpt, cofmsg_flow_stats_reply *msg)
{
#if 0
	if (fib.find(dpt) == fib.end()) {
		delete msg; return;
	}

	std::vector<cofflow_stats_reply>& replies = msg->get_flow_stats();

	std::vector<cofflow_stats_reply>::iterator it;
	for (it = replies.begin(); it != replies.end(); ++it) {
		switch (it->get_version()) {
		case OFP10_VERSION: {
			fprintf(stderr, "FLOW-STATS-REPLY:\n  match: %s\n  actions: %s\n",
					it->get_match().c_str(), it->get_actions().c_str());
		} break;
		case OFP12_VERSION: {
			fprintf(stderr, "FLOW-STATS-REPLY:\n  match: %s\n  instructions: %s\n",
					it->get_match().c_str(), it->get_instructions().c_str());
		} break;
		default: {
			// do nothing
		} break;
		}
	}
#endif
	delete msg;
}





void
ethswitch::handle_dpath_open(
		cofdpt *dpt)
{
	rofl::cflowentry fe(dpt->get_version());

	fe.set_command(OFPFC_ADD);
	fe.set_table_id(0);

	fe.instructions.next() = cofinst_apply_actions(dpt->get_version());
	fe.instructions.back().actions.next() = cofaction_output(dpt->get_version(), OFPP12_CONTROLLER);

	fe.match.set_eth_type(farpv4frame::ARPV4_ETHER);
	send_flow_mod_message(dpt, fe);

	cfib::get_fib(dpt->get_dpid()).dpt_bind(this, dpt);
}



void
ethswitch::handle_dpath_close(
		cofdpt *dpt)
{
	cfib::get_fib(dpt->get_dpid()).dpt_release(this, dpt);
}



void
ethswitch::handle_packet_in(
		cofdpt *dpt,
		cofmsg_packet_in *msg)
{
	cmacaddr eth_src = msg->get_packet().ether()->get_dl_src();
	cmacaddr eth_dst = msg->get_packet().ether()->get_dl_dst();

	/*
	 * sanity check: if source mac is multicast => invalid frame
	 */
	if (eth_src.is_multicast()) {
		delete msg; return;
	}

	/*
	 * block mac address 01:80:c2:00:00:00
	 */
	if (msg->get_packet().ether()->get_dl_dst() == cmacaddr("01:80:c2:00:00:00") ||
		msg->get_packet().ether()->get_dl_dst() == cmacaddr("01:00:5e:00:00:fb")) {
		cflowentry fe(dpt->get_version());

		fe.set_command(OFPFC_ADD);
		fe.set_buffer_id(msg->get_buffer_id());
		fe.set_idle_timeout(15);
		fe.set_table_id(msg->get_table_id());

		fe.match.set_in_port(msg->get_match().get_in_port());
		fe.match.set_eth_dst(msg->get_packet().ether()->get_dl_dst());
		fe.instructions.next() = cofinst_apply_actions(dpt->get_version());

		fprintf(stderr, "etherswitch: installing FLOW-MOD with entry: %s\n",
				fe.c_str());

		send_flow_mod_message(dpt, fe);

		delete msg; return;
	}

	fprintf(stderr, "etherswitch: PACKET-IN from dpid:0x%"PRIu64" buffer-id:0x%x => from %s to %s type: 0x%x\n",
			dpt->get_dpid(),
			msg->get_buffer_id(),
			msg->get_packet().ether()->get_dl_src().c_str(),
			msg->get_packet().ether()->get_dl_dst().c_str(),
			msg->get_packet().ether()->get_dl_type());


	cofaclist actions;

	cfib::get_fib(dpt->get_dpid()).fib_update(
							this,
							dpt,
							msg->get_packet().ether()->get_dl_src(),
							msg->get_match().get_in_port());

	if (eth_dst.is_multicast()) {

		actions.next() = cofaction_output(dpt->get_version(), OFPP12_FLOOD);

	} else {

		cfibentry& entry = cfib::get_fib(dpt->get_dpid()).fib_lookup(
					this,
					dpt,
					msg->get_packet().ether()->get_dl_dst(),
					msg->get_packet().ether()->get_dl_src(),
					msg->get_match().get_in_port());

		if (msg->get_match().get_in_port() == entry.get_out_port_no()) {
			delete msg; return;
		}

		actions.next() = cofaction_output(dpt->get_version(), entry.get_out_port_no());
	}



	if (OFP_NO_BUFFER != msg->get_buffer_id()) {
		send_packet_out_message(dpt, msg->get_buffer_id(), msg->get_match().get_in_port(), actions);
	} else {
		send_packet_out_message(dpt, msg->get_buffer_id(), msg->get_match().get_in_port(), actions,
				msg->get_packet().soframe(), msg->get_packet().framelen());
	}

	delete msg; return;
}



