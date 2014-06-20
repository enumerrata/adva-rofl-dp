/*
 * cofmsg_features_ocs.h
 *
 *  Created on: 31.01.2014
 *      Author: UNIVBRIS
 */

#ifndef COFMSG_FEATURES_OCS_H_
#define COFMSG_FEATURES_OCS_H_ 1

#include <list>

#include "cofmsg.h"
#include "rofl/common/openflow/openflow10_opt_ext.h"
#include "rofl/common/openflow/openflow10.h"

namespace rofl
{



/**
 *
 */
class cofmsg_features_reply_ocs :
	public cofmsg
{

public:

	struct ofp10_switch_features_ocs* switch_features_ocs;
	std::list<ofp10_port> port_list;
	std::list<ofp_phy_cport> cport_list;


public:


	/** constructor
	 *
	 */
	cofmsg_features_reply_ocs(
			uint8_t of_version,
			uint32_t xid,
			uint64_t dpid,
			uint32_t n_buffers,
			uint8_t  n_tables,
			uint8_t  n_cports,
			uint32_t capabilities,
			uint32_t of10_actions_bitmap,
			std::list<ofp_phy_cport> cports);


	cofmsg_features_reply_ocs(
			cofmsg_features_reply_ocs const& features_reply);


	cofmsg_features_reply_ocs&
	operator= (
			cofmsg_features_reply_ocs const& features_reply_ocs);


	/** destructor
	 *
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

#if 0
	/** parse packet and validate it
	 */
	virtual void
	validate();
#endif
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
	const struct
	ofp10_switch_features_ocs * get_switch_features_ocs() const;

	/**
	 *
	 */
	void
	set_switch_features_ocs(
			struct ofp10_switch_features_ocs* switchFeaturesOcs);


};

} // end of namespace rofl

#endif /* COFMSG_FEATURES_OCS_H_ */
