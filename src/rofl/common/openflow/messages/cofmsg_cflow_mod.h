/*
 * cofmsg_flow_mod.h
 *
 *  Created on: 18.03.2013
 *      Author: andi
 */

#ifndef COFMSG_FLOW_MOD_OCS_H_
#define COFMSG_FLOW_MOD_OCS_H_ 1

#include <endian.h>

#include "cofmsg.h"
#include "../openflow10_opt_ext.h"

namespace rofl
{

/**
 *
 */
class cofmsg_cflow_mod :
	public cofmsg
{
private:
	struct ofp_cflow_mod 	*cflow_mod;

//	std::list<uint16_t> in_wport;
//	std::list<uint16_t> out_wport;

public:


	/** constructor
	 *
	 */
	cofmsg_cflow_mod(
			uint8_t of_version = OFP10_VERSION,
			uint8_t type = OFPT_CFLOW_MOD,
			uint32_t xid = 0,
			uint8_t  command = 0,
			uint16_t hard_timeout = 0/*,
			ofp_connect_ocs connect = 0*/
			);

//	/**
//	 *
//	 */
//	cofmsg_cflow_mod(
//			cofmsg_cflow_mod const& cflow_mod);
//
//
//	/**
//	 *
//	 */
//	cofmsg_cflow_mod&
//	operator= (
//			cofmsg_cflow_mod const& cflow_mod);
//
//
	/** destructor
	 *
	 */
	virtual
	~cofmsg_cflow_mod();


	/**
	 *
	 */
	cofmsg_cflow_mod(cmemory *memarea);


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
	uint8_t
	get_command() const {return cflow_mod->command;} ;

	/**
	 *
	 */
	void
	set_command(uint8_t command) {cflow_mod->command = command;} ;

	/**
	 *
	 */
	uint16_t
	get_hard_timeout() const {return cflow_mod->hard_timeout;} ;

	/**
	 *
	 */
	void
	set_hard_timeout(uint16_t hard_timeout) {cflow_mod->hard_timeout = hard_timeout;} ;


	void
	set_wildcards(uint16_t wildcards) {cflow_mod->connect.wildcards = wildcards;} ;

	uint16_t
	get_wildcards() const {return cflow_mod->connect.wildcards;} ;

	void
	set_num_components(uint16_t num_components) {cflow_mod->connect.num_components = num_components;} ;

	uint16_t
	get_num_components() const {return cflow_mod->connect.num_components;} ;

#if 0
	void
	set_in_port(std::list<uint16_t> ports);

	/**
	 * list of in ports
	 * */
	std::list<uint16_t>
	get_in_port();

	void
	set_out_port(std::list<uint16_t> ports);

	/**
	 * list of out ports
	 * */
	std::list<uint16_t>
	get_out_port();

	void
	set_in_tport(std::list<ofp_tdm_port> ports);

	std::list<ofp_tdm_port>
	get_in_tport();

	void
	set_out_tport(std::list<ofp_tdm_port> ports);

	std::list<ofp_tdm_port>
	get_out_tport();

	void
	set_in_wport(std::list<ofp_wave_port> ports);

	std::list<ofp_wave_port>
	get_in_wport();

	void
	set_out_wport(std::list<ofp_wave_port> ports);

	std::list<ofp_wave_port>
	get_out_wport();
#endif

};

} // end of namespace rofl

#endif /* COFMSG_FLOW_MOD_OCS_H_ */
