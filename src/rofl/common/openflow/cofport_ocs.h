/*
 * cofport_ocs.h
 *
 *  Created on: 20 May 2014
 *      Author: UNIVBRIS
 */

#ifndef COFPORT_OCS_H_
#define COFPORT_OCS_H_

#include "rofl/common/openflow/openflow10_opt_ext.h"

namespace rofl
{
class cofport_ocs :
		public csyslog
{

private:	// data structures

	ofp_phy_cport port;		// circuit port

public:

	//default constructor
	cofport_ocs();

	cofport_ocs(uint16_t _port_no);


	struct ofp_phy_port
	get_port();

	void
	set_port(struct ofp_phy_port _port);

};

}




#endif /* COFPORT_OCS_H_ */
