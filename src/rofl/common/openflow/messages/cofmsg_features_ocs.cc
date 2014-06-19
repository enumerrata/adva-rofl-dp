/*
 * cofmsg_features_ocs.cc
 *
 *  Created on: 31.01.2014
 *      Author: Fred (UNIVBRIS)
 */


#include "cofmsg_features_ocs.h"

using namespace rofl;


cofmsg_features_reply_ocs::cofmsg_features_reply_ocs(
		uint8_t of_version,
		uint32_t xid,
		uint64_t dpid,
		uint32_t n_buffers,
		uint8_t  n_tables,
		uint8_t n_cports,
		uint32_t capabilities,
		uint32_t of10_actions_bitmap,
		uint8_t  of13_auxiliary_id,
		cofportlist const& ports,
		struct ofp_phy_cport *cports) :
	cofmsg(sizeof(struct ofp_header)),
	ports(ports)
{
	ofh_switch_features = soframe();

	set_version(of_version);
	set_xid(xid);

	switch (get_version()) {
	case OFP10_VERSION: {
		set_type(OFPT10_FEATURES_REPLY);
		resize(sizeof(struct ofp10_switch_features_ocs));
		set_length(sizeof(struct ofp10_switch_features_ocs));

		ofh10_switch_features_ocs->datapath_id 		= htobe64(dpid);
		ofh10_switch_features_ocs->n_buffers 		= htobe32(n_buffers);
		ofh10_switch_features_ocs->n_tables 		= n_tables;
		ofh10_switch_features_ocs->n_cports			= n_cports;
		ofh10_switch_features_ocs->capabilities 	= htobe32(capabilities);
		ofh10_switch_features_ocs->actions			= htobe32(of10_actions_bitmap);
	} break;
	default:
		throw eBadVersion();
	}
}



cofmsg_features_reply_ocs::cofmsg_features_reply_ocs(
		cmemory *memarea) :
	cofmsg(memarea)
{
	ofh_switch_features = soframe();
}



cofmsg_features_reply_ocs::cofmsg_features_reply_ocs(
		cofmsg_features_reply_ocs const& features_reply)
{
	*this = features_reply;
}



cofmsg_features_reply_ocs&
cofmsg_features_reply_ocs::operator= (
		cofmsg_features_reply_ocs const& features_reply)
{
	if (this == &features_reply)
		return *this;

	cofmsg::operator =(features_reply);

	ofh_switch_features = soframe();

	ports = features_reply.ports;
	cports = features_reply.cports;

	return *this;
}



cofmsg_features_reply_ocs::~cofmsg_features_reply_ocs()
{

}



void
cofmsg_features_reply_ocs::reset()
{
	cofmsg::reset();
	ports.clear();
}



void
cofmsg_features_reply_ocs::resize(size_t len)
{
	cofmsg::resize(len);
	ofh_switch_features = soframe();
}



size_t
cofmsg_features_reply_ocs::length() const
{
	switch (ofh_header->version) {
	case OFP10_VERSION: {
		return (sizeof(struct ofp10_switch_features_ocs) + ports.length());
	} break;
	default:
		throw eBadVersion();
	}
	return 0;
}



void
cofmsg_features_reply_ocs::pack(uint8_t *buf, size_t buflen)
{
	set_length(length());

	if ((0 == buf) || (0 == buflen))
		return;

	if (buflen < length())
		throw eInval();

	switch (get_version()) {
	case OFP10_VERSION: {
		memcpy(buf, soframe(), framelen());
		ports.pack((struct ofp10_port*)(buf + sizeof(struct ofp10_switch_features)), ports.length());
	} break;
	default:
		throw eBadVersion();
	}
}



void
cofmsg_features_reply_ocs::unpack(uint8_t *buf, size_t buflen)
{
	cofmsg::unpack(buf, buflen);

	validate();
}



void
cofmsg_features_reply_ocs::validate()
{
	cofmsg::validate(); // check generic OpenFlow header

	ofh_switch_features = soframe();

	ports.clear();

	switch (get_version()) {
	case OFP10_VERSION: {
		if (get_length() < sizeof(struct ofp10_switch_features))
			throw eBadSyntaxTooShort();
		if (get_length() > sizeof(struct ofp10_switch_features)) {
			ports.unpack(ofh10_switch_features->ports, get_length() - sizeof(struct ofp10_switch_features));
		}
	} break;
	default:
		throw eBadRequestBadVersion();
	}
}




uint64_t
cofmsg_features_reply_ocs::get_dpid() const
{
	switch (get_version()) {
	case OFP10_VERSION: {
		return be64toh(ofh10_switch_features_ocs->datapath_id);
	} break;
	default:
		throw eBadVersion();
	}
	return 0;
}



void
cofmsg_features_reply_ocs::set_dpid(uint64_t dpid)
{
	switch (get_version()) {
	case OFP10_VERSION: {
		ofh10_switch_features_ocs->datapath_id = htobe64(dpid);
	} break;
	default:
		throw eBadVersion();
	}
}



uint32_t
cofmsg_features_reply_ocs::get_n_buffers() const
{
	switch (get_version()) {
	case OFP10_VERSION: {
		return be32toh(ofh10_switch_features_ocs->n_buffers);
	} break;
	default:
		throw eBadVersion();
	}
	return 0;
}



void
cofmsg_features_reply_ocs::set_n_buffers(uint32_t n_buffers)
{
	switch (get_version()) {
	case OFP10_VERSION: {
		ofh10_switch_features_ocs->n_buffers = htobe32(n_buffers);
	} break;
	default:
		throw eBadVersion();
	}
}



uint8_t
cofmsg_features_reply_ocs::get_n_tables() const
{
	switch (get_version()) {
	case OFP10_VERSION: {
		return (ofh10_switch_features_ocs->n_tables);
	} break;
	default:
		throw eBadVersion();
	}
	return 0;
}



void
cofmsg_features_reply_ocs::set_n_tables(uint8_t n_tables)
{
	switch (get_version()) {
	case OFP10_VERSION: {
		ofh10_switch_features_ocs->n_tables = n_tables;
	} break;
	default:
		throw eBadVersion();
	}
}

uint8_t
cofmsg_features_reply_ocs::get_n_cports()
{
	switch (get_version()) {
		case OFP10_VERSION: {
			return (ofh10_switch_features_ocs->n_cports);
		} break;
		default:
			throw eBadVersion();
	}
		return 0;
}

void
cofmsg_features_reply_ocs::set_n_cports(uint8_t n_cports)
{
	switch (get_version()) {
	case OFP10_VERSION: {
		ofh10_switch_features_ocs->n_cports = n_cports;
	} break;
	default:
		throw eBadVersion();
	}
}



uint32_t
cofmsg_features_reply_ocs::get_capabilities() const
{
	switch (get_version()) {
	case OFP10_VERSION: {
		return be32toh(ofh10_switch_features_ocs->capabilities);
	} break;
	default:
		throw eBadVersion();
	}
	return 0;
}



void
cofmsg_features_reply_ocs::set_capabilities(uint32_t capabilities)
{
	switch (get_version()) {
	case OFP10_VERSION: {
		ofh10_switch_features_ocs->capabilities = htobe32(capabilities);
	} break;
	default:
		throw eBadVersion();
	}
}



uint32_t
cofmsg_features_reply_ocs::get_actions_bitmap() const
{
	switch (get_version()) {
	case OFP10_VERSION: {
		return be32toh(ofh10_switch_features->actions);
	} break;
	default:
		throw eBadVersion();
	}
	return 0;
}



void
cofmsg_features_reply_ocs::set_actions_bitmap(uint32_t actions_bitmap)
{
	switch (get_version()) {
	case OFP10_VERSION: {
		ofh10_switch_features_ocs->actions = htobe32(actions_bitmap);
	} break;
	default:
		throw eBadVersion();
	}
}



cofportlist&
cofmsg_features_reply_ocs::get_ports()
{
	return ports;
}



