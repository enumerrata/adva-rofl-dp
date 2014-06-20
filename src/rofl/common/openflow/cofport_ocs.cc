/*
 * cofport_ocs.cc
 *
 *  Created on: 20 May 2014
 *      Author: UNIVBRIS
 */

#include "cofport_ocs.h"

using namespace rofl;

cofport_ocs::cofport_ocs()
{

}


cofport_ocs::cofport_ocs(uint16_t _port_no)
{
	port.port_no = _port_no;
}


struct ofp_phy_port
cofport_ocs::get_port()
{
	return port;
}

void
cofport_ocs::set_port(struct ofp_phy_port _port)
{
	port = _port;
}


