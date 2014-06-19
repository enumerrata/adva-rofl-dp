/*
 * cofmsg_group_mod.h
 *
 *  Created on: 18.03.2013
 *      Author: andi
 */

#ifndef COFMSG_GROUP_MOD_H_
#define COFMSG_GROUP_MOD_H_ 1

#include "cofmsg.h"
#include "rofl/common/openflow/cofbclist.h"

namespace rofl
{

/**
 *
 */
class cofmsg_group_mod :
	public cofmsg
{
private:

	cofbclist			buckets;

	union {
		uint8_t*					ofhu_group_mod;
		struct ofp12_group_mod*		ofhu12_group_mod;
		struct ofp13_group_mod*		ofhu13_group_mod;
	} ofhu;

#define ofh_group_mod   ofhu.ofhu_group_mod
#define ofh12_group_mod ofhu.ofhu12_group_mod
#define ofh13_group_mod ofhu.ofhu13_group_mod

public:


	/** constructor
	 *
	 */
	cofmsg_group_mod(
			uint8_t of_version = 0,
			uint32_t xid = 0,
			uint16_t command = 0,
			uint8_t  group_type = 0,
			uint32_t group_id = 0,
			cofbclist const& buckets = cofbclist());


	/**
	 *
	 */
	cofmsg_group_mod(
			cofmsg_group_mod const& group_mod);


	/**
	 *
	 */
	cofmsg_group_mod&
	operator= (
			cofmsg_group_mod const& group_mod);


	/** destructor
	 *
	 */
	virtual
	~cofmsg_group_mod();


	/**
	 *
	 */
	cofmsg_group_mod(cmemory *memarea);


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
	uint16_t
	get_command() const;

	/**
	 *
	 */
	void
	set_command(uint16_t command);

	/**
	 *
	 */
	uint8_t
	get_group_type() const;

	/**
	 *
	 */
	void
	set_group_type(uint8_t group_type);

	/**
	 *
	 */
	uint32_t
	get_group_id() const;

	/**
	 *
	 */
	void
	set_group_id(uint32_t group_id);

	/**
	 *
	 */
	cofbclist&
	get_buckets();
};

} // end of namespace rofl

#endif /* COFMSG_GROUP_MOD_H_ */
