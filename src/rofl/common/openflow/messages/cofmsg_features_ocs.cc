/*
 * cofmsg_features_ocs.cc
 *
 *  Created on: 31.01.2014
 *      Author: UNIVBRIS
 */


#include "cofmsg_features_ocs.h"

#define DBG(a, b...) fprintf(stderr, "ROFL [%s]:"a"\n", __func__, ##b);

using namespace rofl;

// constructor
cofmsg_features_reply_ocs::cofmsg_features_reply_ocs(
		uint8_t of_version,
		uint32_t xid,
		uint64_t dpid,
		uint32_t n_buffers,
		uint8_t  n_tables,
		uint8_t n_cports,
		uint32_t capabilities,
		uint32_t of10_actions_bitmap,
		std::list<ofp_phy_cport> cports
		) : cofmsg(sizeof(struct ofp_header))
{
	switch_features_ocs = (ofp10_switch_features_ocs*) soframe();

	// header
	set_version(of_version);
	set_type(OFPT10_FEATURES_REPLY);
	set_xid(xid);	// xid from FEATURES_REQUEST message
	// calculate the length of the packet
	int len = sizeof(struct ofp10_switch_features_ocs)
			+ n_cports*sizeof(ofp_phy_cport);
	resize(len);	// this should also change the size of the memory reserved for this packet
	set_length(len);

	set_dpid(dpid);
	set_n_buffers(n_buffers);
	set_n_tables(n_tables);
	set_n_cports(n_cports);
	set_capabilities(capabilities);
	set_actions_bitmap(of10_actions_bitmap);

	std::list<ofp_phy_cport>::iterator it1 = cports.begin();
	uint8_t* ptr = soframe();
	ptr += sizeof(struct ofp10_switch_features_ocs);
	while (it1 != cports.end()) {
		memcpy(ptr, &(*it1), sizeof(ofp_phy_cport));
		cport_list.push_front(*it1);
		it1++;
		ptr += sizeof(ofp_phy_cport);
	}

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

	//switch_features_ocs = soframe();

//	ports = features_reply.ports;
//	cports = features_reply.cports;

	return *this;
}



cofmsg_features_reply_ocs::~cofmsg_features_reply_ocs()
{
//	delete switch_features_ocs;
}



void
cofmsg_features_reply_ocs::reset()
{
	cofmsg::reset();
}



void
cofmsg_features_reply_ocs::resize(size_t len)
{
	cofmsg::resize(len);
}



size_t
cofmsg_features_reply_ocs::length() const
{
	size_t length = 0;
	length = sizeof(struct ofp10_switch_features_ocs);	//32

	try {
		length += cport_list.size()*(sizeof(ofp_phy_cport));
		return length;
	}
	catch (int e){
		DBG("Got error while trying to get number of circuit ports. Code: %d", e);
		return 0;
	}
	return length;
}

void
cofmsg_features_reply_ocs::pack(uint8_t *buf, size_t buflen)
{
	// check if the computation is correct for the message length
	set_length(length());

//	DBG("[cofmsg_features_reply_ocs] Packet length set in the header: %d, dpid:%u", length(), get_dpid());

	try {
		memcpy(buf, soframe(), framelen());
	}
	catch (int e)
	{
		DBG("[cofmsg_features_reply_ocs] got error code: %d.", e);
	}
}


void
cofmsg_features_reply_ocs::unpack(uint8_t *buf, size_t buflen)
{
	cofmsg::unpack(buf, buflen);

	validate();
}

#if 0
void
cofmsg_features_reply_ocs::validate()
{
	cofmsg::validate(); // check generic OpenFlow header

	ofh_switch_features = soframe();

	cport_list.clear();
	//ports.clear();

	switch (get_version()) {
	case OFP10_VERSION: {
		if (get_length() < sizeof(struct ofp10_switch_features))
			throw eBadSyntaxTooShort();
		if (get_length() > sizeof(struct ofp10_switch_features)) {
			// XXX what does unpack do
			//ports.unpack(ofh10_switch_features->ports, get_length() - sizeof(struct ofp10_switch_features));
		}
	} break;
	default:
		throw eBadRequestBadVersion();
	}
}
#endif

uint64_t
cofmsg_features_reply_ocs::get_dpid() const
{
	switch (get_version()) {
	case OFP10_VERSION: {
		return be64toh(switch_features_ocs->datapath_id);
	} break;
	default:
		throw eBadVersion();
	}
	return 0;
}




void
cofmsg_features_reply_ocs::set_dpid(uint64_t dpid)
{
	switch_features_ocs = (ofp10_switch_features_ocs *)soframe();
//	switch_features_ocs->datapath_id = dpid;
	switch_features_ocs->datapath_id = htobe64(dpid);
//	switch (get_version()) {
//	case OFP10_VERSION: {
//		switch_features_ocs->datapath_id = htobe64(dpid);
//	} break;
//	default:
//		throw eBadVersion();
//	}
}



uint32_t
cofmsg_features_reply_ocs::get_n_buffers() const
{
	switch (get_version()) {
	case OFP10_VERSION: {
		return be32toh(switch_features_ocs->n_buffers);
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
		switch_features_ocs->n_buffers = htobe32(n_buffers);
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
		return (switch_features_ocs->n_tables);
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
		switch_features_ocs->n_tables = n_tables;
	} break;
	default:
		throw eBadVersion();
	}
}

uint8_t
cofmsg_features_reply_ocs::get_n_cports()
{
	return (switch_features_ocs->n_cports);
}

void
cofmsg_features_reply_ocs::set_n_cports(uint8_t n_cports)
{
	switch (get_version()) {
	case OFP10_VERSION: {
		switch_features_ocs->n_cports = n_cports;
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
		return be32toh(switch_features_ocs->capabilities);
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
		switch_features_ocs->capabilities = htobe32(capabilities);
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
		return be32toh(switch_features_ocs->actions);
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
		switch_features_ocs->actions = htobe32(actions_bitmap);
	} break;
	default:
		throw eBadVersion();
	}
}


const struct
ofp10_switch_features_ocs * rofl::cofmsg_features_reply_ocs::get_switch_features_ocs() const {
	return switch_features_ocs;
}


void
rofl::cofmsg_features_reply_ocs::set_switch_features_ocs(
		struct ofp10_switch_features_ocs* switchFeaturesOcs) {
	switch_features_ocs = switchFeaturesOcs;
}
