/*
 * cofmsg_flow_mod.h
 *
 *  Created on: 18.03.2013
 *      Author: andi
 */

#ifndef COFMSG_FLOW_MOD_H_
#define COFMSG_FLOW_MOD_H_ 1

#include "cofmsg.h"
#include "rofl/common/openflow/cofaclist.h"
#include "rofl/common/openflow/cofinlist.h"
#include "rofl/common/openflow/cofmatch.h"

namespace rofl
{

/**
 *
 */
class cofmsg_flow_mod :
	public cofmsg
{
private:

	cofaclist			actions; 		// for OF1.0
	cofinlist			instructions; 	// since OF1.1
	cofmatch			match;

	union {
		uint8_t*					ofhu_flow_mod;
		struct ofp10_flow_mod*		ofhu10_flow_mod;
		struct ofp12_flow_mod*		ofhu12_flow_mod;
		struct ofp13_flow_mod*		ofhu13_flow_mod;
	} ofhu;

#define ofh_flow_mod   ofhu.ofhu_flow_mod
#define ofh10_flow_mod ofhu.ofhu10_flow_mod
#define ofh12_flow_mod ofhu.ofhu12_flow_mod
#define ofh13_flow_mod ofhu.ofhu13_flow_mod

#define OFP10_FLOW_MOD_STATIC_HDR_LEN				72
#define OFP12_FLOW_MOD_STATIC_HDR_LEN				48
#define OFP13_FLOW_MOD_STATIC_HDR_LEN				48

public:


	/** constructor
	 *
	 */
	cofmsg_flow_mod(
			uint8_t of_version = 0, // must be OFP10_VERSION
			uint32_t xid = 0,
			uint64_t cookie = 0,
			uint8_t  command = 0,
			uint16_t idle_timeout = 0,
			uint16_t hard_timeout = 0,
			uint16_t priority = 0,
			uint32_t buffer_id = 0,
			uint16_t out_port = 0,
			uint16_t flags = 0,
			cofaclist const& actions = cofaclist(),
			cofmatch const& match = cofmatch(OFP10_VERSION));


	/** constructor
	 *
	 */
	cofmsg_flow_mod(
			uint8_t of_version = 0,  // OFP12_VERSION, OFP13_VERSION, and beyond
			uint32_t xid = 0,
			uint64_t cookie = 0,
			uint64_t cookie_mask = 0,
			uint8_t  table_id = 0,
			uint8_t  command = 0,
			uint16_t idle_timeout = 0,
			uint16_t hard_timeout = 0,
			uint16_t priority = 0,
			uint32_t buffer_id = 0,
			uint32_t out_port = 0,
			uint32_t out_group = 0,
			uint16_t flags = 0,
			cofinlist const& instructions = cofinlist(),
			cofmatch const& match = cofmatch(OFP12_VERSION));


	/**
	 *
	 */
	cofmsg_flow_mod(
			cofmsg_flow_mod const& flow_mod);


	/**
	 *
	 */
	cofmsg_flow_mod&
	operator= (
			cofmsg_flow_mod const& flow_mod);


	/** destructor
	 *
	 */
	virtual
	~cofmsg_flow_mod();


	/**
	 *
	 */
	cofmsg_flow_mod(cmemory *memarea);


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
	uint64_t
	get_cookie() const;

	/**
	 *
	 */
	void
	set_cookie(uint64_t cookie);

	/**
	 *
	 */
	uint64_t
	get_cookie_mask() const;

	/**
	 *
	 */
	void
	set_cookie_mask(uint64_t cookie_mask);

	/**
	 *
	 */
	uint8_t
	get_table_id() const;

	/**
	 *
	 */
	void
	set_table_id(uint8_t table_id);

	/**
	 *
	 */
	uint8_t
	get_command() const;

	/**
	 *
	 */
	void
	set_command(uint8_t command);

	/**
	 *
	 */
	uint16_t
	get_idle_timeout() const;

	/**
	 *
	 */
	void
	set_idle_timeout(uint16_t idle_timeout);

	/**
	 *
	 */
	uint16_t
	get_hard_timeout() const;

	/**
	 *
	 */
	void
	set_hard_timeout(uint16_t hard_timeout);

	/**
	 *
	 */
	uint16_t
	get_priority() const;

	/**
	 *
	 */
	void
	set_priority(uint16_t priority);

	/**
	 *
	 */
	uint32_t
	get_buffer_id() const;

	/**
	 *
	 */
	void
	set_buffer_id(uint32_t buffer_id);

	/**
	 *
	 */
	uint32_t
	get_out_port() const;

	/**
	 *
	 */
	void
	set_out_port(uint32_t out_port);

	/**
	 *
	 */
	uint32_t
	get_out_group() const;

	/**
	 *
	 */
	void
	set_out_group(uint32_t out_group);

	/**
	 *
	 */
	uint16_t
	get_flags() const;

	/**
	 *
	 */
	void
	set_flags(uint16_t flags);

	/**
	 *
	 */
	cofaclist&
	get_actions();

	/**
	 *
	 */
	cofinlist&
	get_instructions();

	/**
	 *
	 */
	cofmatch&
	get_match();
};

} // end of namespace rofl

#endif /* COFMSG_FLOW_MOD_H_ */
