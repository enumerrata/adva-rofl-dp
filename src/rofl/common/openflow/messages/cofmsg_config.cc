#include "cofmsg_config.h"

using namespace rofl;

cofmsg_get_config_request::cofmsg_get_config_request(
		uint8_t of_version,
		uint32_t xid) :
	cofmsg(sizeof(struct ofp_header))
{
	set_version(of_version);
	set_length(sizeof(struct ofp_header));
	set_xid(xid);

	switch (of_version) {
	case OFP10_VERSION: {
		set_type(OFPT10_GET_CONFIG_REQUEST);
	} break;
	case OFP12_VERSION: {
		set_type(OFPT12_GET_CONFIG_REQUEST);
	} break;
	case OFP13_VERSION: {
		set_type(OFPT13_GET_CONFIG_REQUEST);
	} break;
	default:
		throw eBadVersion();
	}
}



cofmsg_get_config_request::cofmsg_get_config_request(
		cmemory *memarea) :
	cofmsg(memarea)
{

}



cofmsg_get_config_request::cofmsg_get_config_request(
		cofmsg_get_config_request const& get_config_request)
{
	*this = get_config_request;
}



cofmsg_get_config_request&
cofmsg_get_config_request::operator= (
		cofmsg_get_config_request const& get_config_request)
{
	if (this == &get_config_request)
		return *this;

	cofmsg::operator =(get_config_request);

	return *this;
}



cofmsg_get_config_request::~cofmsg_get_config_request()
{

}



void
cofmsg_get_config_request::reset()
{
	cofmsg::reset();
}



size_t
cofmsg_get_config_request::length()
{
	return (sizeof(struct ofp_header));
}



void
cofmsg_get_config_request::pack(uint8_t *buf, size_t buflen)
{
	set_length(length());

	if ((0 == buf) || (buflen == 0))
		return;

	if (buflen < length())
		throw eInval();

	cofmsg::pack(buf, buflen);
}



void
cofmsg_get_config_request::unpack(uint8_t *buf, size_t buflen)
{
	cofmsg::unpack(buf, buflen);

	validate();
}



void
cofmsg_get_config_request::validate()
{
	cofmsg::validate(); // check generic OpenFlow header

	switch (get_version()) {
	case OFP10_VERSION: {

	} break;
	case OFP12_VERSION: {

	} break;
	case OFP13_VERSION: {

	} break;
	default:
		throw eBadRequestBadVersion();
	}
}










cofmsg_get_config_reply::cofmsg_get_config_reply(
		uint8_t of_version,
		uint32_t xid,
		uint16_t flags,
		uint16_t miss_send_len) :
	cofmsg(sizeof(struct ofp_header))
{
	ofh_switch_config = soframe();

	set_version(of_version);
	set_xid(xid);

	switch (get_version()) {
	case OFP10_VERSION: {
		set_type(OFPT10_GET_CONFIG_REPLY);
		resize(sizeof(struct ofp10_switch_config));
		set_length(sizeof(struct ofp10_switch_config));

		ofh10_switch_config->flags 			= htobe16(flags);
		ofh10_switch_config->miss_send_len	= htobe16(miss_send_len);
	} break;
	case OFP12_VERSION: {
		set_type(OFPT12_GET_CONFIG_REPLY);
		resize(sizeof(struct ofp12_switch_config));
		set_length(sizeof(struct ofp12_switch_config));

		ofh12_switch_config->flags 			= htobe16(flags);
		ofh12_switch_config->miss_send_len	= htobe16(miss_send_len);
	} break;
	case OFP13_VERSION: {
		set_type(OFPT13_GET_CONFIG_REPLY);
		resize(sizeof(struct ofp13_switch_config));
		set_length(sizeof(struct ofp13_switch_config));

		ofh13_switch_config->flags 			= htobe16(flags);
		ofh13_switch_config->miss_send_len	= htobe16(miss_send_len);
	} break;
	default:
		throw eBadVersion();
	}
}



cofmsg_get_config_reply::cofmsg_get_config_reply(
		cmemory *memarea) :
	cofmsg(memarea)
{
	ofh_switch_config = soframe();
}



cofmsg_get_config_reply::cofmsg_get_config_reply(
		cofmsg_get_config_reply const& config)
{
	*this = config;
}



cofmsg_get_config_reply&
cofmsg_get_config_reply::operator= (
		cofmsg_get_config_reply const& config)
{
	if (this == &config)
		return *this;

	cofmsg::operator =(config);

	ofh_switch_config = soframe();

	return *this;
}



cofmsg_get_config_reply::~cofmsg_get_config_reply()
{

}



void
cofmsg_get_config_reply::reset()
{
	cofmsg::reset();
}



void
cofmsg_get_config_reply::resize(size_t len)
{
	cofmsg::resize(len);
	ofh_switch_config = soframe();
}



size_t
cofmsg_get_config_reply::length() const
{
	switch (ofh_header->version) {
	case OFP10_VERSION: {
		return (sizeof(struct ofp10_switch_config));
	} break;
	case OFP12_VERSION: {
		return (sizeof(struct ofp12_switch_config));
	} break;
	case OFP13_VERSION: {
		return (sizeof(struct ofp13_switch_config));
	} break;
	default:
		throw eBadVersion();
	}
	return 0;
}



void
cofmsg_get_config_reply::pack(uint8_t *buf, size_t buflen)
{
	set_length(length());

	if ((0 == buf) || (0 == buflen))
		return;

	if (buflen < length())
		throw eInval();

	switch (get_version()) {
	case OFP10_VERSION: {
		memcpy(buf, soframe(), framelen());
	} break;
	case OFP12_VERSION: {
		memcpy(buf, soframe(), framelen());
	} break;
	case OFP13_VERSION: {
		memcpy(buf, soframe(), framelen());
	} break;
	default:
		throw eBadVersion();
	}
}



void
cofmsg_get_config_reply::unpack(uint8_t *buf, size_t buflen)
{
	cofmsg::unpack(buf, buflen);

	validate();
}



void
cofmsg_get_config_reply::validate()
{
	cofmsg::validate(); // check generic OpenFlow header

	ofh_switch_config = soframe();

	switch (get_version()) {
	case OFP10_VERSION: {
		if (get_length() < sizeof(struct ofp10_switch_config))
			throw eBadSyntaxTooShort();
	} break;
	case OFP12_VERSION: {
		if (get_length() < sizeof(struct ofp12_switch_config))
			throw eBadSyntaxTooShort();
	} break;
	case OFP13_VERSION: {
		if (get_length() < sizeof(struct ofp13_switch_config))
			throw eBadSyntaxTooShort();
	} break;
	default:
		throw eBadRequestBadVersion();
	}
}




uint16_t
cofmsg_get_config_reply::get_flags() const
{
	switch (get_version()) {
	case OFP10_VERSION: {
		return be16toh(ofh10_switch_config->flags);
	} break;
	case OFP12_VERSION: {
		return be16toh(ofh12_switch_config->flags);
	} break;
	case OFP13_VERSION: {
		return be16toh(ofh13_switch_config->flags);
	} break;
	default:
		throw eBadVersion();
	}
	return 0;
}



void
cofmsg_get_config_reply::set_flags(uint16_t flags)
{
	switch (get_version()) {
	case OFP10_VERSION: {
		ofh10_switch_config->flags = htobe16(flags);
	} break;
	case OFP12_VERSION: {
		ofh12_switch_config->flags = htobe16(flags);
	} break;
	case OFP13_VERSION: {
		ofh13_switch_config->flags = htobe16(flags);
	} break;
	default:
		throw eBadVersion();
	}
}



uint16_t
cofmsg_get_config_reply::get_miss_send_len() const
{
	switch (get_version()) {
	case OFP10_VERSION: {
		return be16toh(ofh10_switch_config->miss_send_len);
	} break;
	case OFP12_VERSION: {
		return be16toh(ofh12_switch_config->miss_send_len);
	} break;
	case OFP13_VERSION: {
		return be16toh(ofh13_switch_config->miss_send_len);
	} break;
	default:
		throw eBadVersion();
	}
	return 0;
}



void
cofmsg_get_config_reply::set_miss_send_len(uint16_t miss_send_len)
{
	switch (get_version()) {
	case OFP10_VERSION: {
		ofh10_switch_config->miss_send_len = htobe16(miss_send_len);
	} break;
	case OFP12_VERSION: {
		ofh12_switch_config->miss_send_len = htobe16(miss_send_len);
	} break;
	case OFP13_VERSION: {
		ofh13_switch_config->miss_send_len = htobe16(miss_send_len);
	} break;
	default:
		throw eBadVersion();
	}
}










cofmsg_set_config::cofmsg_set_config(
		uint8_t of_version,
		uint32_t xid,
		uint16_t flags,
		uint16_t miss_send_len) :
	cofmsg(sizeof(struct ofp_header))
{
	ofh_switch_config = soframe();

	set_version(of_version);
	set_xid(xid);

	switch (get_version()) {
	case OFP10_VERSION: {
		set_type(OFPT10_SET_CONFIG);
		resize(sizeof(struct ofp10_switch_config));
		set_length(sizeof(struct ofp10_switch_config));

		ofh10_switch_config->flags 			= htobe16(flags);
		ofh10_switch_config->miss_send_len	= htobe16(miss_send_len);
	} break;
	case OFP12_VERSION: {
		set_type(OFPT12_SET_CONFIG);
		resize(sizeof(struct ofp12_switch_config));
		set_length(sizeof(struct ofp12_switch_config));

		ofh12_switch_config->flags 			= htobe16(flags);
		ofh12_switch_config->miss_send_len	= htobe16(miss_send_len);
	} break;
	case OFP13_VERSION: {
		set_type(OFPT13_SET_CONFIG);
		resize(sizeof(struct ofp13_switch_config));
		set_length(sizeof(struct ofp13_switch_config));

		ofh13_switch_config->flags 			= htobe16(flags);
		ofh13_switch_config->miss_send_len	= htobe16(miss_send_len);
	} break;
	default:
		throw eBadVersion();
	}
}



cofmsg_set_config::cofmsg_set_config(
		cmemory *memarea) :
	cofmsg(memarea)
{
	ofh_switch_config = soframe();
}



cofmsg_set_config::cofmsg_set_config(
		cofmsg_set_config const& config)
{
	*this = config;
}



cofmsg_set_config&
cofmsg_set_config::operator= (
		cofmsg_set_config const& config)
{
	if (this == &config)
		return *this;

	cofmsg::operator =(config);

	ofh_switch_config = soframe();

	return *this;
}



cofmsg_set_config::~cofmsg_set_config()
{

}



void
cofmsg_set_config::reset()
{
	cofmsg::reset();
}



void
cofmsg_set_config::resize(size_t len)
{
	cofmsg::resize(len);
	ofh_switch_config = soframe();
}



size_t
cofmsg_set_config::length() const
{
	switch (ofh_header->version) {
	case OFP10_VERSION: {
		return (sizeof(struct ofp10_switch_config));
	} break;
	case OFP12_VERSION: {
		return (sizeof(struct ofp12_switch_config));
	} break;
	case OFP13_VERSION: {
		return (sizeof(struct ofp13_switch_config));
	} break;
	default:
		throw eBadVersion();
	}
	return 0;
}



void
cofmsg_set_config::pack(uint8_t *buf, size_t buflen)
{
	set_length(length());

	if ((0 == buf) || (0 == buflen))
		return;

	if (buflen < length())
		throw eInval();

	switch (get_version()) {
	case OFP10_VERSION: {
		memcpy(buf, soframe(), framelen());
	} break;
	case OFP12_VERSION: {
		memcpy(buf, soframe(), framelen());
	} break;
	case OFP13_VERSION: {
		memcpy(buf, soframe(), framelen());
	} break;
	default:
		throw eBadVersion();
	}
}



void
cofmsg_set_config::unpack(uint8_t *buf, size_t buflen)
{
	cofmsg::unpack(buf, buflen);

	validate();
}



void
cofmsg_set_config::validate()
{
	cofmsg::validate(); // check generic OpenFlow header

	ofh_switch_config = soframe();

	switch (get_version()) {
	case OFP10_VERSION: {
		if (get_length() < sizeof(struct ofp10_switch_config))
			throw eBadSyntaxTooShort();
	} break;
	case OFP12_VERSION: {
		if (get_length() < sizeof(struct ofp12_switch_config))
			throw eBadSyntaxTooShort();
	} break;
	case OFP13_VERSION: {
		if (get_length() < sizeof(struct ofp13_switch_config))
			throw eBadSyntaxTooShort();
	} break;
	default:
		throw eBadRequestBadVersion();
	}
}




uint16_t
cofmsg_set_config::get_flags() const
{
	switch (get_version()) {
	case OFP10_VERSION: {
		return be16toh(ofh10_switch_config->flags);
	} break;
	case OFP12_VERSION: {
		return be16toh(ofh12_switch_config->flags);
	} break;
	case OFP13_VERSION: {
		return be16toh(ofh13_switch_config->flags);
	} break;
	default:
		throw eBadVersion();
	}
	return 0;
}



void
cofmsg_set_config::set_flags(uint16_t flags)
{
	switch (get_version()) {
	case OFP10_VERSION: {
		ofh10_switch_config->flags = htobe16(flags);
	} break;
	case OFP12_VERSION: {
		ofh12_switch_config->flags = htobe16(flags);
	} break;
	case OFP13_VERSION: {
		ofh13_switch_config->flags = htobe16(flags);
	} break;
	default:
		throw eBadVersion();
	}
}



uint16_t
cofmsg_set_config::get_miss_send_len() const
{
	switch (get_version()) {
	case OFP10_VERSION: {
		return be16toh(ofh10_switch_config->miss_send_len);
	} break;
	case OFP12_VERSION: {
		return be16toh(ofh12_switch_config->miss_send_len);
	} break;
	case OFP13_VERSION: {
		return be16toh(ofh13_switch_config->miss_send_len);
	} break;
	default:
		throw eBadVersion();
	}
	return 0;
}



void
cofmsg_set_config::set_miss_send_len(uint16_t miss_send_len)
{
	switch (get_version()) {
	case OFP10_VERSION: {
		ofh10_switch_config->miss_send_len = htobe16(miss_send_len);
	} break;
	case OFP12_VERSION: {
		ofh12_switch_config->miss_send_len = htobe16(miss_send_len);
	} break;
	case OFP13_VERSION: {
		ofh13_switch_config->miss_send_len = htobe16(miss_send_len);
	} break;
	default:
		throw eBadVersion();
	}
}
