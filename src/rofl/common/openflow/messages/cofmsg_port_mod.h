/*
 * cofmsg_port_mod.h
 *
 *  Created on: 18.03.2013
 *      Author: andi
 */

#ifndef COFMSG_PORT_MOD_H_
#define COFMSG_PORT_MOD_H_ 1

#include "cofmsg.h"

namespace rofl
{

/**
 *
 */
class cofmsg_port_mod :
	public cofmsg
{
private:

	union {
		uint8_t*					ofhu_port_mod;
		struct ofp10_port_mod*		ofhu10_port_mod;
		struct ofp12_port_mod*		ofhu12_port_mod;
		struct ofp13_port_mod*		ofhu13_port_mod;
	} ofhu;

#define ofh_port_mod   ofhu.ofhu_port_mod
#define ofh10_port_mod ofhu.ofhu10_port_mod
#define ofh12_port_mod ofhu.ofhu12_port_mod
#define ofh13_port_mod ofhu.ofhu13_port_mod

public:


	/** constructor
	 *
	 */
	cofmsg_port_mod(
			uint8_t of_version = 0,
			uint32_t xid = 0,
			uint32_t port_no = 0,
			cmacaddr const& hwaddr = cmacaddr("00:00:00:00:00:00"),
			uint32_t config = 0,
			uint32_t mask = 0,
			uint32_t advertise = 0);


	/**
	 *
	 */
	cofmsg_port_mod(
			cofmsg_port_mod const& port_mod);


	/**
	 *
	 */
	cofmsg_port_mod&
	operator= (
			cofmsg_port_mod const& port_mod);


	/** destructor
	 *
	 */
	virtual
	~cofmsg_port_mod();


	/**
	 *
	 */
	cofmsg_port_mod(cmemory *memarea);


	/** reset packet content
	 *
	 */
	virtual void
	reset();


	/**
	 *
	 */
	virtual void
	resize(size_t len);


	/** returns length of packet in packed state
	 *
	 */
	virtual size_t
	length() const;


	/**
	 *
	 */
	virtual void
	pack(uint8_t *buf = (uint8_t*)0, size_t buflen = 0);


	/**
	 *
	 */
	virtual void
	unpack(uint8_t *buf, size_t buflen);


	/** parse packet and validate it
	 */
	virtual void
	validate();


public:


	/**
	 *
	 */
	uint32_t
	get_port_no() const;

	/**
	 *
	 */
	void
	set_port_no(uint32_t port_no);

	/**
	 *
	 */
	cmacaddr
	get_hwaddr() const;

	/**
	 *
	 */
	void
	set_hwaddr(cmacaddr const& hwaddr);

	/**
	 *
	 */
	uint32_t
	get_config() const;

	/**
	 *
	 */
	void
	set_config(uint32_t config);

	/**
	 *
	 */
	uint32_t
	get_mask() const;

	/**
	 *
	 */
	void
	set_mask(uint32_t mask);

	/**
	 *
	 */
	uint32_t
	get_advertise() const;

	/**
	 *
	 */
	void
	set_advertise(uint32_t advertise);
};

} // end of namespace rofl

#endif /* COFMSG_PORT_MOD_H_ */
