/*
 * cofmsg_experimenter_stats.h
 *
 *  Created on: 18.03.2013
 *      Author: andi
 */

#ifndef COFMSG_EXPERIMENTER_STATS_H_
#define COFMSG_EXPERIMENTER_STATS_H_ 1

#include "cofmsg_stats.h"
#include "rofl/common/openflow/cofgroupfeaturesstats.h"
#include "rofl/common/cmemory.h"

namespace rofl
{


/**
 *
 */
class cofmsg_experimenter_stats_request :
	public cofmsg_stats
{
private:

	cmemory			body;

	union {
		uint8_t*									ofhu_exp_stats;
		struct ofp10_vendor_stats_header*			ofhu10_exp_stats;
		struct ofp12_experimenter_stats_header*		ofhu12_exp_stats;
		// TODO: OF1.3
	} ofhu;

#define ofh_exp_stats   			ofhu.ofhu_exp_stats
#define ofh10_exp_stats 			ofhu.ofhu10_exp_stats
#define ofh12_exp_stats 			ofhu.ofhu12_exp_stats
// TODO OF1.3

public:


	/** constructor
	 *
	 */
	cofmsg_experimenter_stats_request(
			uint8_t of_version = 0,
			uint32_t xid = 0,
			uint16_t flags = 0,
			uint32_t exp_id = 0,
			uint32_t exp_type = 0,
			cmemory const& body = cmemory(0));


	/**
	 *
	 */
	cofmsg_experimenter_stats_request(
			cofmsg_experimenter_stats_request const& stats);


	/**
	 *
	 */
	cofmsg_experimenter_stats_request&
	operator= (
			cofmsg_experimenter_stats_request const& stats);


	/** destructor
	 *
	 */
	virtual
	~cofmsg_experimenter_stats_request();


	/**
	 *
	 */
	cofmsg_experimenter_stats_request(cmemory *memarea);


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
	void
	set_exp_id(uint32_t exp_id);


	/**
	 *
	 */
	uint32_t
	get_exp_id() const;


	/**
	 *
	 */
	void
	set_exp_type(uint32_t exp_type);


	/**
	 *
	 */
	uint32_t
	get_exp_type() const;


	/**
	 *
	 */
	cmemory&
	get_body();
};



/**
 *
 */

/**
 *
 */
class cofmsg_experimenter_stats_reply :
	public cofmsg_stats
{
private:

	cmemory			body;

	union {
		uint8_t*									ofhu_exp_stats;
		struct ofp10_vendor_stats_header*			ofhu10_exp_stats;
		struct ofp12_experimenter_stats_header*		ofhu12_exp_stats;
		// TODO: OF1.3
	} ofhu;

#define ofh_exp_stats   			ofhu.ofhu_exp_stats
#define ofh10_exp_stats 			ofhu.ofhu10_exp_stats
#define ofh12_exp_stats 			ofhu.ofhu12_exp_stats
// TODO OF1.3

public:


	/** constructor
	 *
	 */
	cofmsg_experimenter_stats_reply(
			uint8_t of_version = 0,
			uint32_t xid = 0,
			uint16_t flags = 0,
			uint32_t exp_id = 0,
			uint32_t exp_type = 0,
			cmemory const& body = cmemory(0));


	/**
	 *
	 */
	cofmsg_experimenter_stats_reply(
			cofmsg_experimenter_stats_reply const& stats);


	/**
	 *
	 */
	cofmsg_experimenter_stats_reply&
	operator= (
			cofmsg_experimenter_stats_reply const& stats);


	/** destructor
	 *
	 */
	virtual
	~cofmsg_experimenter_stats_reply();


	/**
	 *
	 */
	cofmsg_experimenter_stats_reply(cmemory *memarea);


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
	void
	set_exp_id(uint32_t exp_id);


	/**
	 *
	 */
	uint32_t
	get_exp_id() const;


	/**
	 *
	 */
	void
	set_exp_type(uint32_t exp_type);


	/**
	 *
	 */
	uint32_t
	get_exp_type() const;


	/**
	 *
	 */
	cmemory&
	get_body();
};



} // end of namespace rofl

#endif /* COFMSG_GROUP_FEATURES_STATS_H_ */
