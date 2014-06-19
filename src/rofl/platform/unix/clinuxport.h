/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/*
 * clinuxport.h
 *
 * common interfaces and utility methods for all ports on a linux system
 *
 */

#ifndef CLINUXPORT_H_
#define CLINUXPORT_H_

//#include <linux/if.h>
#include <sys/ioctl.h>

#include "rofl/common/cport.h"

namespace rofl
{

class clinuxport :
	public cport
{
public:

		cmacaddr		hwaddr;
		uint32_t		ifindex;
		uint32_t		state;
		uint32_t		curr_speed;
		uint32_t		max_speed;

public:

	/**
	 *
	 */
	clinuxport(
			cport_owner *owner,
			std::string devname,
			std::string devtype);


	/**
	 *
	 */
	virtual uint32_t
	get_curr_speed();


	/** get max speed
	 */
	virtual uint32_t
	get_max_speed();


	/** get hw_addr: stores mac address of port in cmacaddr
	 *
	 * @param ma
	 * @return
	 */
	virtual cmacaddr&
	get_hw_addr() throw (ePortSocketCallFailed, ePortIoctlCallFailed);

	/** set hw_addr
	 */
	virtual void
	set_hw_addr(cmacaddr const& maddr) throw (ePortSocketCallFailed, ePortInval,
			ePortSetHwAddrFailed);

	/** enable interface (set IFF_UP flag)
	 */
	virtual void
	enable_interface() throw (ePortSocketCallFailed, ePortIoctlCallFailed);

	/** disable interface (clear IFF_UP flag)
	 */
	virtual void
	disable_interface() throw (ePortSocketCallFailed, ePortIoctlCallFailed);

	/** get port number: returns uint32_t
	 */
	virtual uint32_t
	get_port_no_from_kernel() throw (ePortSocketCallFailed, ePortIoctlCallFailed);

	/** get state
	 */
	virtual uint32_t
	get_state() throw (ePortSocketCallFailed, ePortIoctlCallFailed);
};

}; // end of namespace

#endif /* CLINUXPORT_H_ */
