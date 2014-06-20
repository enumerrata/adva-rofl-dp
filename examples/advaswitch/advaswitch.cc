#include "advaswitch.h"
#include "rofl/common/openflow/cofport_ocs.h"

#include <string.h>
#include <inttypes.h>
#include <threads.h>

// for debugging only
#define DBG(a, b...) fprintf(stderr, "ROFL [%s]:"a"\n", __func__, ##b);

using namespace advaswitch;

advaroadm::advaroadm(X_CorePtr _core_ptr):core_ptr(_core_ptr)
{

}

advaroadm::~advaroadm()
{
	// ...
}

void
advaroadm::handle_ctrl_open(rofl::cofctl *ctl)
{
//	DBG("checkpoint");
}

void
advaroadm::handle_dpath_open(rofl::cofdpt *dpt) {
//	DBG("checkpoint");
}

void
advaroadm::handle_features_request(cofctl *ctl,
		cofmsg_features_request *msg) {
//	DBG("FEATURES_REQUEST received from the controller.");

	// Constructing FEATURES_REPLY message
	uint32_t num_of_buffers = 0;
	uint32_t num_of_tables = 0;
	uint32_t capabilities = 0;
	uint32_t actions = 0;

	//physical circuit ports
	std::list<ofp_phy_cport> l_cport = std::list<ofp_phy_cport>();
	int i=0;
	X_ListNodePtr pNode;
	struct ofp_phy_cport *opcp;

	/* lock before accessing core_ptr pointer */
	pthread_mutex_lock(&core_mutex_init);
	X_List_ForEach(core_ptr->Ports, pNode) {
		opcp = static_cast<ofp_phy_cport*>(pNode->Data);
		opcp->num_bandwidth = 1;

		l_cport.push_back(*opcp);
		++i;
	}
	pthread_mutex_unlock(&core_mutex_init);
	// OCS for debugging
//	std::list<ofp_phy_cport>::const_iterator it;
//	for (it=l_cport.begin(); it != l_cport.end(); it++) {
//		std::cout << it->name << "::" << ntohs(it->port_no) << std::endl;
//	}
//	DBG("Number of ports read from pCore: %d", l_cport.size());

	crofbase::send_features_reply_ocs(
			ctl, msg->get_xid(), core_ptr->SysIP,
			num_of_buffers, num_of_tables,
			X_List_Size(core_ptr->Ports),
			capabilities, actions,l_cport);

	delete msg;
}

// OCS TODO
void
advaroadm::handle_cflow_mod(cofctl *ctl, cofmsg_cflow_mod *msg)
{

	uint16_t err_type=0, err_code=0;
	size_t err_datalen = 0;
	uint8_t *err_data = (uint8_t*) malloc(err_datalen);
	err_data = (uint8_t*) memset(err_data, 0, err_datalen);

	if (msg == NULL)
	{
		DBG("Message received is empty");
		free(err_data);
		delete msg;
		return;
	}

	uint16_t supp_wildcards = 0x0f;		// lamda cross-connect (wports)
	struct ofp_cflow_mod *cflow_mod =
			(struct ofp_cflow_mod*) msg->soframe();
	struct ofp_wave_port in, out, *pwave;

//	DBG("supported wildcards: %d, provided wildcards: %d", supp_wildcards, cflow_mod->connect.wildcards);

	// check for errors with the request. send
	if(cflow_mod->command == supp_wildcards)
	{
		//form data and send an error message here!!
		DBG("ERROR cross-connection requested is not supported.");
		err_type = 4; err_code = 2;
		crofbase::send_error_message(
				ctl, msg->get_xid(), err_type, err_code, err_data, err_datalen);
		free(err_data);
		delete msg;
		return;
	}
	ofp_wave_port wport = cflow_mod->connect.in_wport[0];
//	DBG("In wave port: port_no:%d, lamda:%016llX", wport.wport, wport.wavelength);
	wport = cflow_mod->connect.out_wport[0];
//	DBG("Out wave port: port_no:%d, lamda:%016llX", wport.wport, wport.wavelength);

	pwave = (struct ofp_wave_port *) &cflow_mod->connect.in_wport[0];
	memcpy(&in, pwave, sizeof(in));
//	pwave++;
	pwave = (struct ofp_wave_port *) &cflow_mod->connect.out_wport[0];
	memcpy(&out, pwave, sizeof(out));

//	DBG("CFLOW_MOD in_port: %d@%016llX, out_port: %d@%016llX",
//			in.wport, in.wavelength, out.wport, out.wavelength);

	/*************************************************************
	 * LOCK MUTEX AT THIS POINT
	 *
	 * ***********************************************************/
//	DBG("Will attempt to cross-connect. Locking core_mutex_init");

	X_ListNodePtr pNode;
	struct ofp_phy_cport *port_in = NULL, *port_out = NULL, *ofport;
	pthread_mutex_lock(&core_mutex_init);

	// looking for in/out ports using X_Core in the device
	X_List_ForEach(core_ptr->Ports, pNode)
	{
		ofport = (struct ofp_phy_cport*)(pNode->Data);
//		DBG("core_ptr ports iteration: %d", ofport->port_no);
		if (ofport->port_no == in.wport)
			port_in = ofport;
		if (ofport->port_no == out.wport)
			port_out = ofport;
		if (port_in && port_out)
			break;
	}
//	DBG("Port_in no: %d, name: %s", ntohs(port_in->port_no), port_in->name);
//	DBG("Port_out no: %d, name: %s", ntohs(port_out->port_no), port_out->name);

	/* at least one of the ports was not found on the device */
	if ((port_in == NULL) || (port_out == NULL))
	{
		DBG("Port(s) not found!");
		err_type = 4; err_code = 2; // OCS TODO
		crofbase::send_error_message(
				ctl, msg->get_xid(), err_type, err_code, err_data, err_datalen);
		pthread_mutex_unlock(&core_mutex_init);
		free(err_data);
		delete msg;
		return;
	}


	size_t freq = ntohl(in.wavelength);	// HACK!
//	size_t freq = be64toh(in.wavelength);
//	DBG("freq=%d, wavelength(HEX)=%016X", freq, in.wavelength);

	freq = 193900;
	X_Addr inaddr, outaddr;

	X_Addr_Parse(&inaddr, (char*) port_in->name);
	X_Addr_Parse(&outaddr, (char*) port_out->name);

	X_ModulePtr pMod_in = X_Resource_FindModule(core_ptr->Resources, &inaddr);
	X_ModulePtr pMod_out = X_Resource_FindModule(core_ptr->Resources, &outaddr);

	if (pMod_in == NULL || pMod_out == NULL)
	{
		DBG("No module found for one or both of the ports!");
		err_type = 4; err_code = 2; // OCS TODO
		crofbase::send_error_message(
				ctl, msg->get_xid(), err_type, err_code, err_data, err_datalen);
		pthread_mutex_unlock(&core_mutex_init);
		free(err_data);
		delete msg;
		return;
	}

	X_ListPtr pList = X_List_New((X_ListMemFree_t) X_PathData_Free);

	X_Resource_Find_Path(core_ptr->Resources, X_RES_DIR_IN, freq, pMod_in, pMod_out, pList);

	// CFlowMod ADD cross-connection command
	if (cflow_mod->command == OFP10FC_ADD) {

		X_Allocate_Resource(core_ptr->Resources, pList, freq);

	}
	// CFlowMod TEAR-DOWN cross connection command
	if (cflow_mod->command == OFP10FC_DELETE) {

		X_Allocate_Resource(core_ptr->Resources, pList, freq);

	}
	X_List_Clear(pList);

	X_Resource_Find_Path(core_ptr->Resources, X_RES_DIR_OUT, freq, pMod_in, pMod_out, pList);

	if (cflow_mod->command == OFP10FC_ADD) {

		X_Allocate_Resource(core_ptr->Resources, pList, freq);

	}
	if (cflow_mod->command == OFP10FC_DELETE) {

		X_Allocate_Resource(core_ptr->Resources, pList, freq);

	}
	X_List_Clear(pList);
	X_List_Free(pList);

	DBG("Cross-connection successful. Now we need to equalize.");

	pthread_mutex_unlock(&core_mutex_init);
	free(err_data);
	delete msg;
}

void
advaroadm::handle_experimenter_message(cofctl *ctl, cofmsg_experimenter *msg)
{

	uint8_t* ptr = msg->sobody();
	uint32_t vendor = 0, type = 0;
	memcpy(&vendor, ptr, sizeof(uint32_t));	// vendor id - SHOULD be ADVA
	ptr += 4;
	memcpy(&type, ptr, sizeof(uint32_t));	// ADVA vendor message type
	DBG("Vendor id:%d, exp type:%d [ADVA vendor id is: %d]", ntohl(vendor), ntohl(type), ADVA_ROADM_FS);

	/** ADVA vendor messages */
	switch(ntohl(type)) {
		case OOE_SWITCH_CONSTRAINTS_REQUEST:
		{
			/* Not supported yet */
			DBG("OOE_SWITCH_CONSTRAINTS_REQUEST message detected.");
			handle_switching_constrains_req(ctl, msg);
			break;
		}
		case OOE_POWER_EQ_REQUEST:
		{
			DBG("OOE_POWER_EQ_REQUEST message detected");
			handle_power_equalization_req(ctl, msg);
			break;
		}
		default:
		{
			DBG("NOT_VALID experimenter message", ntohl(type));
			send_error_message(ctl, msg->get_xid(), OFPET_BAD_REQUEST, OFPBRC_BAD_EXPERIMENTER,
										(unsigned char*)msg->soframe(), 96);
			break;
		}
	} //:end of switch

}


// OCS TODO
void
advaroadm::handle_switching_constrains_req(cofctl *ctl, cofmsg_experimenter *msg)
{
	/* Not supported - sending error message */
	send_error_message(ctl, msg->get_xid(), OFPET_BAD_REQUEST, OFPBRC_BAD_EXPERIMENTER,
								(unsigned char*)msg->soframe(), 96);
}


// OCS TODO
void
advaroadm::handle_power_equalization_req (cofctl *ctl, cofmsg_experimenter *msg)
{

	uint8_t* ptr = msg->sobody();
	uint32_t vendor=0, type=0, freq=0;
	uint16_t in_port=0, out_port=0;
	uint8_t result=0;

	memcpy(&vendor, ptr, sizeof(uint32_t));
	ptr += 4;
	memcpy(&type, ptr, sizeof(uint32_t));
	ptr += 4;
	memcpy(&in_port, ptr, sizeof(uint16_t));
	in_port = ntohs(in_port);
	ptr += 2;
	memcpy(&out_port, ptr, sizeof(uint16_t));
	out_port = ntohs(out_port);
	ptr += 2;
	memcpy(&freq, ptr, sizeof(uint32_t));
	freq = ntohl(freq);
	ptr += 4;
	memcpy(&result, ptr, sizeof(uint8_t));
//	DBG("Parse EQ_REQUEST_MSG: in:%d->out:%d @ freq:%d, result:%d",
//			in_port, out_port, freq, result);

	struct ofp_phy_cport *in_cport = NULL, *out_cport = NULL, *cport;
	X_ListNodePtr pNode;


	pthread_mutex_lock(&core_mutex_init);
	X_List_ForEach(core_ptr->Ports, pNode)
	{
		cport = (struct ofp_phy_cport*) (pNode->Data);
//		DBG("read ports numbers core_ptr: %d", cport->port_no);
		if (in_port == cport->port_no)
			in_cport = cport;
		if (out_port == cport->port_no)
			out_cport = cport;
		if ((in_cport != NULL) && (out_cport != NULL))
			break;
	}
	if ((in_cport == NULL) || (out_cport == NULL))
	{
		DBG("Port numbers to equalize not valid.");
		pthread_mutex_unlock(&core_mutex_init);
		send_error_message(ctl, msg->get_xid(), OFPET_BAD_REQUEST,
				OFPBRC_BAD_EXPERIMENTER, (unsigned char*)msg->soframe(), 96);
		return;
	}
	X_Addr in_addr, out_addr;
	X_ModulePtr pSrcMod, pDstMod;
    X_ListPtr pList;
    unsigned int eqlzid = 0;

    X_Addr_Parse(&in_addr, (char *)in_cport->name);
    X_Addr_Parse(&out_addr, (char *) out_cport->name);

    pSrcMod = X_Resource_FindModule(core_ptr->Resources, &in_addr);
    pDstMod = X_Resource_FindModule(core_ptr->Resources, &out_addr);

    if ((pSrcMod == NULL) || (pDstMod == NULL))
    {
    	DBG("Module NOT found!");
    	send_error_message(ctl, msg->get_xid(), OFPET_BAD_REQUEST,
    			OFPBRC_BAD_EXPERIMENTER, (unsigned char*)msg->soframe(), 96);
    	pthread_mutex_unlock(&core_mutex_init);
    	return;
    }

    pList = X_List_New((X_ListMemFree_t)X_PathData_Free);
    X_Resource_Find_Path(
    		core_ptr->Resources, X_RES_DIR_OUT, freq, pSrcMod, pDstMod, pList);
    if (pList->Size > 0)
    {
    	X_Update_Resources(core_ptr->Resources, pList, freq, 1, &eqlzid);
    }
    else
    {
    	send_error_message(ctl, msg->get_xid(), OFPET_BAD_REQUEST,
    	    	OFPBRC_BAD_EXPERIMENTER, (unsigned char*)msg->soframe(), 96);
    	pthread_mutex_unlock(&core_mutex_init);
    	return;
    }
    if (eqlzid > 0)
    {
    	DBG("equalization is in progress (id=%d)", eqlzid);
    	EqlzReqPtr pEqlz = EqlzReq_New();

    	pEqlz->id = eqlzid;
    	pEqlz->in_port = in_port;
    	pEqlz->out_port = out_port;
    	pEqlz->freq = freq;

    	X_List_Append(core_ptr->Eqlz, pEqlz);
    }
    else
    {
    	DBG("Nothing to equalize!");
    	// OCS TODO
    	send_error_message(ctl, msg->get_xid(), OFPET_BAD_REQUEST,
    	    	 OFPBRC_BAD_EXPERIMENTER, (unsigned char*)msg->soframe(), 96);
    }
	pthread_mutex_unlock(&core_mutex_init);
	return;
}


void
advaroadm::handle_ctrl_close(rofl::cofctl *ctl)
{
	DBG("Closing connection to the controller.")
}

char*
advaroadm::get_controller_ip()
{
	char* tmp_str;
	tmp_str = strdup(core_ptr->OpenFlowAddr);
	char* delimiter = ":";
	char *tcp, *ip;

	tcp = strtok(tmp_str, delimiter);
	ip = strtok(NULL, delimiter);

	return ip;
}

