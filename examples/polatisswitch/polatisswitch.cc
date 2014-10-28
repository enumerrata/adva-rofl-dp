#include "polatisswitch.h"
#include "rofl/common/openflow/cofport_ocs.h"

#include <string.h>
#include <inttypes.h>
#include <threads.h>
#include <list>

// for debugging only
//#define DBG(a, b...) fprintf(stderr, "ROFL [%s]:"a"\n", __func__, ##b);

using namespace polatisswitch;

polatissw::polatissw(X_CorePtr _core_ptr) :
		core_ptr(_core_ptr) {

}

polatissw::~polatissw() {
	// ...
}

void polatissw::handle_ctrl_open(rofl::cofctl *ctl) {
//	DBG("checkpoint");
}

void polatissw::handle_dpath_open(rofl::cofdpt *dpt) {
//	DBG("checkpoint");
}

void polatissw::handle_features_request(cofctl *ctl,
		cofmsg_features_request *msg) {

	DBG("FEATURES_REQUEST received from the controller.");

	// Constructing FEATURES_REPLY message
	uint32_t num_of_buffers = 0;
	uint32_t num_of_tables = 1;
	uint32_t capabilities = 0;
	uint32_t actions = 0;

//	DBG("Device IP: %s:%d", core_ptr->TL1_Listen, atoi(core_ptr->TL1_Port));

	struct listNode * Dict_head = (struct listNode*) malloc(
			sizeof(struct listNode));

	pthread_mutex_lock(&core_mutex_init);
	Dict_head = TL1_Channel_Callback(core_ptr->TL1_Listen, core_ptr->TL1_Port,
			"cmd_maps_TL1.txt");

	char *cmd_output, *pAddr;
	unsigned int tmp_int;
	cmd_output = (char *) fetchCmd(Dict_head, "sr_no");

//	DBG("DPID:%s tmp_id value:%d", cmd_output, tmp_int);

	uint64_t datapath_id = atoi(cmd_output);
	DBG("\n\n # Switch datapath id: %d", datapath_id);

	/*** calculate number of ports of the switch ***/
	memset(cmd_output, '\0', sizeof(cmd_output));
	cmd_output = (char *) fetchCmd(Dict_head, "switch_size");
	DBG("Switch size:%s\n", cmd_output);
	int n_cports = atoi(cmd_output);

	/*** update capabilities value ***/
	capabilities = htonl(OFPC_FLOW_STATS | OFPC_TABLE_STATS | OFPC_PORT_STATS);
	bool power = false, attenuate = false;
	if (parseSingleCmd("attenuate")) {
		attenuate = true;
	}
	if (parseSingleCmd("power")) {
		power = true;
	}
	if (power && attenuate) {
		capabilities = htonl(
				OFPC_FLOW_STATS | OFPC_TABLE_STATS | OFPC_PORT_STATS
						| OFPC_OCS_ATTENUATE | OFPC_OCS_POWER);
	} else if (power) {

		capabilities = htonl(
				OFPC_FLOW_STATS | OFPC_TABLE_STATS | OFPC_PORT_STATS
						| OFPC_OCS_POWER);
	} else {
		capabilities = htonl(
				OFPC_FLOW_STATS | OFPC_TABLE_STATS | OFPC_PORT_STATS);
	}

	DBG("capabilities:%d, n_cports:%d (parsed from device)", capabilities,
			n_cports);

	/*** Parse the ports of the switch ***/
	std::list<ofp_phy_cport> cport_list = std::list<ofp_phy_cport>();
	struct ofp_phy_cport *c_opp;
	c_opp = (struct ofp_phy_cport*) malloc(sizeof(struct ofp_phy_cport));
	uint8_t hw_addr[6] = { 00, 02, 03, 04, 05, 06 };
	char portName[6] = { 'P', 'O', 'L', '1', '-', '\0' };
	int k = 0;

	for (k = 0; k < n_cports; k++) {

		printf(" # %d #", k);

		int portBase = 0;
		int j;
		char *pch;
		char buffTemp[3];

		if (c_opp == NULL)
			continue;

		memset(c_opp, 0, sizeof(struct ofp_phy_cport));
		portBase = portBase + k;
		c_opp->port_no = htons(portBase);
		for (j = 0; j < 6; j++) {
			c_opp->hw_addr[j] = hw_addr[j];
		}
		char * charBase = itoa(portBase, 10);
		c_opp->name[0] = 'P';
		c_opp->name[1] = 'O';
		c_opp->name[2] = 'L';
		c_opp->name[3] = charBase[0];
		c_opp->name[4] = charBase[1];
		c_opp->name[5] = charBase[2];
		c_opp->name[6] = '\0';

		c_opp->config = htonl(111);

		char portStatus[] = "RTRV-PORT-SHUTTER::000&&000:123:;";
		pch = strchr(portStatus, '0');
		j = 0;
		sprintf(buffTemp, "%d", portBase);

		if (pch != NULL) {
			for (j = 0; j < strlen(buffTemp);) {
				if (strlen(buffTemp) == 2) {
					portStatus[(pch - portStatus) + (1 + j)] = buffTemp[j];
					portStatus[(pch - portStatus) + (6 + j)] = buffTemp[j];
				} else if (strlen(buffTemp) == 3) {
					portStatus[(pch - portStatus) + j] = buffTemp[j];
					portStatus[(pch - portStatus) + (5 + j)] = buffTemp[j];
				} else {
					portStatus[(pch - portStatus) + (2 + j)] = buffTemp[j];
					portStatus[(pch - portStatus) + (7 + j)] = buffTemp[j];
				}
				//printf("bufftemp:%s and j:%c and text:%s\t", buffTemp[j], j, portStatus[(pch-portStatus) + (2 - j)]);
				j++;
			}
		}
		memset(buffTemp, '\0', sizeof(buffTemp));

		c_opp->state = htonl(222);

		c_opp->curr = htonl(OFPPF_OCS_X);
		c_opp->advertised = htonl(
				OFPPF_OCS_OC1 | OFPPF_OCS_OTU2 | OFPPF_OCS_OC768);
		c_opp->supported = htonl(
				OFPPF_OCS_OC3 | OFPPF_OCS_100GB | OFPPF_OCS_OTU1);
		c_opp->peer = htonl(OFPPF_OCS_X);

		c_opp->supp_sw_tdm_gran = 0;
		c_opp->supp_swtype = htons(OFPST_FIBER);

		c_opp->peer_port_no = 0;
		c_opp->peer_datapath_id = 0;
		c_opp->num_bandwidth = 1;	// TODO check if order is correct
		c_opp->bandwidth[0] = 1 << 0;

		cport_list.push_back(*c_opp);	// add ports to the list
		printf("[%d]", cport_list.size());
	}

//	printf("\n\n######### k value after loop: %d [list MAX_size:%d] n_cports:[%d] ##########\n\n",
//			k, cport_list.max_size(), n_cports);

	crofbase::send_features_reply_ocs(ctl, msg->get_xid(), datapath_id,
			num_of_buffers, num_of_tables, n_cports,		// number of cports
			htonl(capabilities),	// capabilities
			actions, cport_list);
	DBG("FEATURES_REPLY message send to the controller.");
	delete msg;
//	DBG("FEATURES_REQUEST message deleted.");
}

void polatissw::handle_barrier_request(cofctl *ctl,
		cofmsg_barrier_request *msg) {

	DBG("Handle Barrier request message from polatissw.");
	crofbase::send_barrier_reply(ctl, msg->get_xid());

}

// OCS
void polatissw::handle_cflow_mod(cofctl *ctl, cofmsg_cflow_mod *msg) {

	DBG("Received CFLOW_MOD message with type %d", msg->get_type());
//	DBG("message received: %s", msg->c_str());
	uint16_t err_type = 0, err_code = 0;
	size_t err_datalen = 0;
	uint8_t *err_data = (uint8_t*) malloc(err_datalen);
	err_data = (uint8_t*) memset(err_data, 0, err_datalen);

	if (msg == NULL) {
		DBG("Message received is empty");
		free(err_data);
		delete msg;
		return;
	}

	DBG("length:%d\n\n", msg->framelen());
	uint8_t *ptr = msg->soframe();
	uint16_t in_port, out_port;
	bool tear = false;

	printf("%s", msg->c_str());

	for (int p = 0; p < msg->framelen(); p++) {
//		if (p==0)
//			printf("\n\n");
//		else {
//			if(p%4 == 0)
//				printf("  ");
//		}
//		printf("%02x ", *ptr)
		if (p == 25) {
			printf("[%02x:%d]", *ptr, *ptr);
			in_port = *ptr;
		} else if (p == 27) {
			printf("[%02x:%d]", *ptr, *ptr);
			out_port = *ptr;
		} else if (p == 8) {
			printf("[%02x:%d]", *ptr, *ptr);
			int temp = *ptr;
			if (temp != 0)
				tear = true;
		}
		ptr += 1;
	}

	uint16_t supp_wildcards = 0x0f;		// lamda cross-connect (wports)
	struct ofp_cflow_mod *cflow_mod = (struct ofp_cflow_mod*) msg->soframe();

	DBG("cross-connect: %d<==>%d [%d]", in_port, out_port, tear);

	struct crossFlow *sendCF;
	XCflow xcFlow;
	sendCF = &xcFlow;

	xcFlow.in_port = in_port;
	xcFlow.out_port = out_port;

	if (tear == true) {
		DBG("perform tear-down of lightpath %d%<==>d", in_port, out_port);
		if (parseFlowCmd(&xcFlow, "flowdel")) {
			DBG("success!");
//			del_flows(ntohs(in_port), ntohs(out_port), 0);
		} else {
			DBG("failed!");
		}
	} else {
		DBG("perform cross connection between ports: %d<==>%d", in_port,
				out_port);
		if (parseFlowCmd(&xcFlow, "flowmod")) {
			DBG("success!");
//			add_flows(ntohs(in_port), ntohs(out_port), 0);
//			send CPORT_STATUS message to controller
		} else {
			DBG("failed!");
			// send message failed message
		}
	}



	free(err_data);
	delete msg;
}

void polatissw::handle_experimenter_message(cofctl *ctl,
		cofmsg_experimenter *msg) {

	uint8_t* ptr = msg->sobody();
	uint32_t vendor = 0, type = 0;
	memcpy(&vendor, ptr, sizeof(uint32_t));
	ptr += 4;
	memcpy(&type, ptr, sizeof(uint32_t));

	// no experimenter messages for fibre switches so far
	switch (ntohl(type)) {

	default: {
		DBG("NOT_VALID experimenter message", ntohl(type));
		send_error_message(ctl, msg->get_xid(), OFPET_BAD_REQUEST,
				OFPBRC_BAD_EXPERIMENTER, (unsigned char*) msg->soframe(), 96);
		break;
	}
	} //:end of switch

}

void polatissw::handle_ctrl_close(rofl::cofctl *ctl) {
	DBG("Closing connection to the controller.");
}

char*
polatissw::get_controller_ip() {
	char* tmp_str;
	tmp_str = strdup(core_ptr->OpenFlowAddr);
	char* delimiter = ":";
	char *tcp, *ip;

	tcp = strtok(tmp_str, delimiter);
	ip = strtok(NULL, delimiter);

	return ip;
}

