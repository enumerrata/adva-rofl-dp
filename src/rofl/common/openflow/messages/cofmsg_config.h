/*
 * cofmsg_config.h
 *
 *  Created on: 18.03.2013
 *      Author: andi
 */

#ifndef COFMSG_CONFIG_H_A
#define COFMSG_CONFIG_H_A 1

#include "cofmsg.h"
#include "rofl/common/openflow/cofportlist.h"

namespace rofl
{

/**
 *
 */
class cofmsg_get_config_request :
	public cofmsg
{
public:


	/** constructor
	 *
	 */
	cofmsg_get_config_request(
			uint8_t of_version = 0,
			uint32_t xid = 0);


	/**
	 *
	 */
	cofmsg_get_config_request(
			cofmsg_get_config_request const& get_config_request);


	/**
	 *
	 */
	cofmsg_get_config_request&
	operator= (
			cofmsg_get_config_request const& get_config_request);


	/** destructor
	 *
	 */
	virtual
	~cofmsg_get_config_request();


	/**
	 *
	 */
	cofmsg_get_config_request(cmemory *memarea);


	/** reset packet content
	 *
	 */
	virtual void
	reset();


	/** returns length of packet in packed state
	 *
	 */
	virtual size_t
	length();


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
};


/**
 *
 */
class cofmsg_get_config_reply :
	public cofmsg
{
private:

	union {
		uint8_t*					ofhu_switch_config;
		struct ofp10_switch_config*	ofhu10_switch_config;
		struct ofp12_switch_config*	ofhu12_switch_config;
		struct ofp13_switch_config*	ofhu13_switch_config;
	} ofhu;

#define ofh_switch_config   ofhu.ofhu_switch_config
#define ofh10_switch_config ofhu.ofhu10_switch_config
#define ofh12_switch_config ofhu.ofhu12_switch_config
#define ofh13_switch_config ofhu.ofhu13_switch_config

public:


	/** constructor
	 *
	 */
	cofmsg_get_config_reply(
			uint8_t of_version = 0,
			uint32_t xid = 0,
			uint16_t flags = 0,
			uint16_t miss_send_len = 0);


	/**
	 *
	 */
	cofmsg_get_config_reply(
			cofmsg_get_config_reply const& config);


	/**
	 *
	 */
	cofmsg_get_config_reply&
	operator= (
			cofmsg_get_config_reply const& config);


	/** destructor
	 *
	 */
	virtual
	~cofmsg_get_config_reply();


	/**
	 *
	 */
	cofmsg_get_config_reply(cmemory *memarea);


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
	get_flags() const;

	/**
	 *
	 */
	void
	set_flags(uint16_t flags);

	/**
	 *
	 */
	uint16_t
	get_miss_send_len() const;

	/**
	 *
	 */
	void
	set_miss_send_len(uint16_t miss_send_len);
};



/**
 *
 */
class cofmsg_set_config :
	public cofmsg
{
private:

	union {
		uint8_t*					ofhu_switch_config;
		struct ofp10_switch_config*	ofhu10_switch_config;
		struct ofp12_switch_config*	ofhu12_switch_config;
		struct ofp13_switch_config*	ofhu13_switch_config;
	} ofhu;

#define ofh_switch_config   ofhu.ofhu_switch_config
#define ofh10_switch_config ofhu.ofhu10_switch_config
#define ofh12_switch_config ofhu.ofhu12_switch_config
#define ofh13_switch_config ofhu.ofhu13_switch_config

public:


	/** constructor
	 *
	 */
	cofmsg_set_config(
			uint8_t of_version = 0,
			uint32_t xid = 0,
			uint16_t flags = 0,
			uint16_t miss_send_len = 0);


	/**
	 *
	 */
	cofmsg_set_config(
			cofmsg_set_config const& config);


	/**
	 *
	 */
	cofmsg_set_config&
	operator= (
			cofmsg_set_config const& config);


	/** destructor
	 *
	 */
	virtual
	~cofmsg_set_config();


	/**
	 *
	 */
	cofmsg_set_config(cmemory *memarea);


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
	get_flags() const;

	/**
	 *
	 */
	void
	set_flags(uint16_t flags);

	/**
	 *
	 */
	uint16_t
	get_miss_send_len() const;

	/**
	 *
	 */
	void
	set_miss_send_len(uint16_t miss_send_len);
};




} // end of namespace rofl

#endif /* COFMSG_CONFIG_H_ */
