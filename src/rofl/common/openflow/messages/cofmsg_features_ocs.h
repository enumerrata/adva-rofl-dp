/*
 * cofmsg_features_ocs.h
 *
 *  Created on: 31.01.2014
 *      Author: Fred (UNIVBRIS)
 */

#ifndef COFMSG_FEATURES_OCS_H_
#define COFMSG_FEATURES_OCS_H_ 1

#include "cofmsg.h"
#include "rofl/common/openflow/cofportlist.h"
#include "rofl/common/openflow/openflow10_opt_ext.h"

namespace rofl
{


/**
 *
 */
class cofmsg_features_reply_ocs :
	public cofmsg
{
private:

	cofportlist			ports;
	static struct ofp_phy_cport _empty_cports;
	struct ofp_phy_cport cports;


	union {
		uint8_t*						ofhu_switch_features;
		struct ofp10_switch_features*	ofhu10_switch_features;
		struct ofp10_switch_features_ocs*	ofhu10_switch_features_ocs;
		struct ofp12_switch_features*	ofhu12_switch_features;
		struct ofp13_switch_features*	ofhu13_switch_features;
	} ofhu;

#define ofh_switch_features   ofhu.ofhu_switch_features
#define ofh10_switch_features ofhu.ofhu10_switch_features
#define ofh10_switch_features_ocs	ofhu.ofhu10_switch_features_ocs
#define ofh12_switch_features ofhu.ofhu12_switch_features
#define ofh13_switch_features ofhu.ofhu13_switch_features

public:


	/**
	 * constructor
	 */
	cofmsg_features_reply_ocs(
			uint8_t of_version = 0,
			uint32_t xid = 0,
			uint64_t dpid = 0,
			uint32_t n_buffers = 0,
			uint8_t  n_tables = 0,
			uint8_t  n_cports = 0,
			uint32_t capabilities = 0,
			uint32_t of10_actions_bitmap = 0,
			uint8_t  of13_auxiliary_id = 0,
			cofportlist const& ports = cofportlist(),
			struct ofp_phy_cport *cports = &_empty_cports);


	/**
	 * constructor
	 */
	cofmsg_features_reply_ocs(
			cofmsg_features_reply_ocs const& features_reply);

	/**
	 * constructor
	 */
	cofmsg_features_reply_ocs(cmemory *memarea);


	/**
	 * operator override
	 */
	cofmsg_features_reply_ocs&
	operator= (
			cofmsg_features_reply_ocs const& features_reply_ocs);

	/**
	 * destructor
	 */
	virtual
	~cofmsg_features_reply_ocs();

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
	get_dpid() const;

	/**
	 *
	 */
	void
	set_dpid(uint64_t dpid);

	/**
	 *
	 */
	uint32_t
	get_n_buffers() const;

	/**
	 *
	 */
	void
	set_n_buffers(uint32_t n_buffers);

	/**
	 *
	 */
	uint8_t
	get_n_tables() const;

	/**
	 *
	 */
	void
	set_n_tables(uint8_t n_tables);

	uint8_t
	get_n_cports();

	void
	set_n_cports(uint8_t n_cports);

	/** OF1.3
	 *
	 */
	uint8_t
	get_auxiliary_id() const;

	/**
	 *
	 */
	void
	set_auxiliary_id(uint8_t auxiliary_id);

	/**
	 *
	 */
	uint32_t
	get_capabilities() const;

	/**
	 *
	 */
	void
	set_capabilities(uint32_t capabilities);

	/** OF1.0 only
	 *
	 */
	uint32_t
	get_actions_bitmap() const;

	/**
	 *
	 */
	void
	set_actions_bitmap(uint32_t actions_bitmap);

	/**
	 *
	 */
	cofportlist&
	get_ports();
};

} // end of namespace rofl

#endif /* COFMSG_FEATURES_OCS_H_ */
