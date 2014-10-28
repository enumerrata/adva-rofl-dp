#ifndef POLATISSWITCH_H
#define POLATISSWITCH_H 1
#endif

#include <map>
#include "rofl/common/cmacaddr.h"
#include "rofl/common/caddress.h"
#include "rofl/common/crofbase.h"
#include "rofl/common/openflow/cofdpt.h"
#include <rofl/common/utils/c_logger.h>
#include <fstream>
extern "C"{
	#include "../../agent-hsl/Agent/Agent.h"
	#include "../../agent-hsl/Agent/TL1_conn.h"
}

#include <cfib.h>

using namespace rofl;

namespace polatisswitch
{

class polatissw :
		public crofbase
{
private:

	X_CorePtr core_ptr;

	struct crossc_table {
		ofp_phy_cport in_port[0];
		ofp_phy_cport out_port[0];
	};

public:

	polatissw(X_CorePtr _core_ptr);

	virtual
	~polatissw();

	virtual void
	handle_ctrl_open(rofl::cofctl *ctl);

	virtual void
	handle_dpath_open(rofl::cofdpt *dpt);

	void
	handle_features_request (cofctl *ctl, cofmsg_features_request *msg);

	void
	handle_barrier_request(cofctl *ctl, cofmsg_barrier_request *msg);

	void
	handle_cflow_mod(cofctl *ctl, cofmsg_cflow_mod *msg); // { delete msg; };

	void
	handle_experimenter_message(cofctl *ctl, cofmsg_experimenter *msg);

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

