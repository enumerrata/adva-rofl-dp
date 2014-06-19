#include "etherswitch.h"
#include <inttypes.h>

#define DBG(a, b...) fprintf(stderr, "ROFL: [%s]\t"a"\n", __func__)

using namespace etherswitch;

ethswitch::ethswitch(X_CorePtr _core_ptr):core_ptr(_core_ptr) {

}

ethswitch::~ethswitch() {
	// ...
}

void ethswitch::handle_ctrl_open(rofl::cofctl *ctl) {
	std::ofstream OUT;
	OUT.open("home/openflow/text.txt", std::ios::out | std::ios::in
			| std::ios::app);
	OUT << "connection was successful" << std::endl;
	std::cout << "ctrl connection was successful" << std::endl;
}

void ethswitch::handle_dpath_open(rofl::cofdpt *dpt) {
	std::ofstream OUT;
	OUT.open("/home/openflow/text.txt");
	OUT << "dpath connection was successful" << std::endl;
	std::cout << "dpath connection was successful" << std::endl;
}

void ethswitch::handle_features_request(cofctl *ctl,
		cofmsg_features_request *msg) {

	DBG("FEATURES_REQ received.\tDPID from core_prt: %lu", core_ptr->SysIP);
	DBG("X_List size: %d", X_List_Size(core_ptr->Ports));

	//logical_switch_port_t* ls_port;
	//switch_port_t* _port;

	uint32_t num_of_tables = 0;
	uint32_t num_of_buffers = 0;
	uint32_t capabilities = 0;

	// array of structures ofp_port
	cofportlist portlist;

	/*
	 num_of_tables 	= of10switch->pipeline->num_of_tables;
	 num_of_buffers 	= of10switch->pipeline->num_of_buffers;
	 capabilities 	= of10switch->pipeline->capabilities;
	 //we check all the positions in case there are empty slots
	 for (unsigned int n = 1; n < of10switch->max_ports; n++){

	 ls_port = &of10switch->logical_ports[n];
	 _port = ls_port->port;

	 if(_port!=NULL && ls_port->attachment_state!=LOGICAL_PORT_STATE_DETACHED){

	 //Mapping of port state
	 assert(n == _port->of_port_num);

	 cofport port(ctl->get_version());

	 port.set_port_no(_port->of_port_num);
	 port.set_hwaddr(cmacaddr(_port->hwaddr, OFP_ETH_ALEN));
	 port.set_name(std::string(_port->name));

	 uint32_t config = 0;
	 if(!_port->up)
	 config |= OFP10PC_PORT_DOWN;
	 if(_port->drop_received)
	 config |= OFP10PC_NO_RECV;
	 if(_port->no_flood)
	 config |= OFP10PC_NO_FLOOD;
	 if(!_port->forward_packets)
	 config |= OFP10PC_NO_FWD;
	 if(!_port->of_generate_packet_in)
	 config |= OFP10PC_NO_PACKET_IN;

	 port.set_config(config);
	 port.set_state(_port->state);
	 port.set_curr(_port->curr);
	 port.set_advertised(_port->advertised);
	 port.set_supported(_port->supported);
	 port.set_peer(_port->peer);

	 portlist.next() = port;
	 }
	 }*/
	struct ofp_phy_cport *cport_ptr = NULL;

	DBG("Sending FEATURES_REPLY message");
	send_features_reply_ocs(ctl, msg->get_xid(),
			0x12345,
			num_of_buffers,
			num_of_tables, 0, capabilities, 0, 0, portlist,	cport_ptr);


	delete msg;
	DBG("Finish handling the OF message");
}

void ethswitch::handle_ctrl_close(rofl::cofctl *ctl) {
	std::ofstream OUT;
	OUT.open("/home/openflow/text.txt");
	OUT << "connection was successful" << std::endl;
//	std::cout << "### connection ctrl close" << std::endl;
	printf("%s: connection to CTRL closed", __func__);
}
