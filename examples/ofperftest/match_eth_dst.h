#ifndef MATCH_ETH_DST_H
#define MATCH_ETH_DST_H 1

#include <map>
#include "rofl/common/cmacaddr.h"
#include "rofl/common/caddress.h"
#include "rofl/common/crofbase.h"
#include "rofl/common/openflow/cofdpt.h"

#include "ofperftest.h"

using namespace rofl;

class match_eth_dst :
		public ofperftest
{
private:

	struct fibentry_t {
		uint32_t 		port_no;	// port where a certain is attached
		time_t 			timeout;	// timeout event for this FIB entry
	};

	unsigned int 		n_entries;	// number of competing flowmods to be installed
	// a very simple forwarding information base
	std::map<cofdpt*, std::map<uint16_t, std::map<cmacaddr, struct fibentry_t> > > fib;

	unsigned int 		fib_check_timeout; 		// periodic timeout for removing expired FIB entries
	unsigned int		fm_delete_all_timeout;	// periodic purging of all FLOW-MODs

	enum match_eth_dst_timer_t {
		ETHSWITCH_TIMER_BASE = ((0x6271)),
		ETHSWITCH_TIMER_FIB,
		ETHSWITCH_TIMER_FLOW_MOD_DELETE_ALL,
	};

public:

	match_eth_dst(unsigned int n_entries = 0);

	virtual
	~match_eth_dst();

	virtual void
	handle_timeout(int opaque);

	virtual void
	handle_dpath_open(cofdpt *dpt);

	virtual void
	handle_dpath_close(cofdpt *dpt);

	virtual void
	handle_packet_in(cofdpt *dpt, cofmsg_packet_in *msg);

private:

	void
	install_flow_mods(cofdpt *dpt, unsigned int n = 0);

	void
	drop_expired_fib_entries();

	void
	flow_mod_delete_all();
};

#endif
