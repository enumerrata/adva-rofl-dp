#ifndef ADVASWITCH_H
#define ADVASWITCH_H 1
#endif

#include <map>
#include "rofl/common/cmacaddr.h"
#include "rofl/common/caddress.h"
#include "rofl/common/crofbase.h"
#include "rofl/common/openflow/cofdpt.h"
#include <rofl/common/utils/c_logger.h>
#include <fstream>
extern "C"{
	#include "../../adva-agent-rofl/Agent/Agent.h"
	#include "../../adva-agent-rofl/SnmpAccess/List.h"
}

#include <cfib.h>

using namespace rofl;

namespace advaswitch
{

class advaroadm :
		public crofbase
{
private:

	X_CorePtr core_ptr;

public:

	advaroadm(X_CorePtr _core_ptr);

	virtual
	~advaroadm();

	virtual void
	handle_ctrl_open(rofl::cofctl *ctl);

	virtual void
	handle_dpath_open(rofl::cofdpt *dpt);

	void
	handle_features_request (cofctl *ctl, cofmsg_features_request *msg);

	void
	handle_cflow_mod(cofctl *ctl, cofmsg_cflow_mod *msg); // { delete msg; };

	void
	handle_experimenter_message(cofctl *ctl, cofmsg_experimenter *msg);

	void
	handle_switching_constrains_req(cofctl *ctl, cofmsg_experimenter *msg);

//	void
//	handle_mgmt_info_request(cofctl *ctl, cofmsg_experimenter *msg);

	void
	handle_power_equalization_req (cofctl *ctl, cofmsg_experimenter *msg);

	virtual void
	handle_ctrl_close(rofl::cofctl *ctl);

public:

	char*
	get_controller_ip();


private:

	void
	request_flow_stats();
	
};

}; // end of namespace

