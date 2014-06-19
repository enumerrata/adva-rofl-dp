#include "cofmsg_desc_stats.h"

using namespace rofl;





cofmsg_desc_stats_request::cofmsg_desc_stats_request(
		uint8_t of_version,
		uint32_t xid,
		uint16_t flags) :
	cofmsg_stats(of_version, xid, OFPST_DESC, flags)
{
	switch (of_version) {
	case OFP10_VERSION: {
		set_type(OFPT10_STATS_REQUEST);
		resize(sizeof(struct ofp10_stats_request));
	} break;
	case OFP12_VERSION: {
		set_type(OFPT12_STATS_REQUEST);
		resize(sizeof(struct ofp12_stats_request));
	} break;
	case OFP13_VERSION: {
		// TODO
		throw eNotImplemented();
	} break;
	default:
		throw eBadVersion();
	}
}



cofmsg_desc_stats_request::cofmsg_desc_stats_request(
		cmemory *memarea) :
	cofmsg_stats(memarea)
{

}



cofmsg_desc_stats_request::cofmsg_desc_stats_request(
		cofmsg_desc_stats_request const& stats)
{
	*this = stats;
}



cofmsg_desc_stats_request&
cofmsg_desc_stats_request::operator= (
		cofmsg_desc_stats_request const& stats)
{
	if (this == &stats)
		return *this;

	cofmsg_stats::operator =(stats);

	return *this;
}



cofmsg_desc_stats_request::~cofmsg_desc_stats_request()
{

}



void
cofmsg_desc_stats_request::reset()
{
	cofmsg_stats::reset();
}



void
cofmsg_desc_stats_request::resize(size_t len)
{
	cofmsg::resize(len);
}



size_t
cofmsg_desc_stats_request::length() const
{
	switch (get_version()) {
	case OFP10_VERSION: {
		return (sizeof(struct ofp10_stats_request));
	} break;
	case OFP12_VERSION: {
		return (sizeof(struct ofp12_stats_request));
	} break;
	case OFP13_VERSION: {
		// TODO
		throw eNotImplemented();
	} break;
	default:
		throw eBadVersion();
	}
	return 0;
}



void
cofmsg_desc_stats_request::pack(uint8_t *buf, size_t buflen)
{
	cofmsg_stats::pack(buf, buflen); // copies common statistics header

	if ((0 == buf) || (0 == buflen))
		return;

	if (buflen < length())
		throw eInval();

	switch (get_version()) {
	case OFP10_VERSION: {
		if (buflen < (sizeof(struct ofp10_stats_request)))
			throw eInval();
	} break;
	case OFP12_VERSION: {
		if (buflen < (sizeof(struct ofp12_stats_request)))
			throw eInval();
	} break;
	case OFP13_VERSION: {
		// TODO
		throw eNotImplemented();
	} break;
	default:
		throw eBadVersion();
	}
}



void
cofmsg_desc_stats_request::unpack(uint8_t *buf, size_t buflen)
{
	cofmsg_stats::unpack(buf, buflen);

	validate();
}



void
cofmsg_desc_stats_request::validate()
{
	cofmsg_stats::validate(); // check generic statistics header

	switch (get_version()) {
	case OFP10_VERSION: {
		if (get_length() < (sizeof(struct ofp10_stats_request)))
			throw eBadSyntaxTooShort();
	} break;
	case OFP12_VERSION: {
		if (get_length() < (sizeof(struct ofp12_stats_request)))
			throw eBadSyntaxTooShort();
	} break;
	case OFP13_VERSION: {
		// TODO
		throw eNotImplemented();
	} break;
	default:
		throw eBadRequestBadVersion();
	}
}








cofmsg_desc_stats_reply::cofmsg_desc_stats_reply(
		uint8_t of_version,
		uint32_t xid,
		uint16_t flags,
		cofdesc_stats_reply const& desc_stats) :
	cofmsg_stats(of_version, xid, OFPST_DESC, flags),
	desc_stats(desc_stats)
{
	switch (of_version) {
	case OFP10_VERSION: {
		set_type(OFPT10_STATS_REPLY);
		resize(sizeof(struct ofp10_stats_reply) + sizeof(struct ofp10_desc_stats));
		desc_stats.pack(soframe() + sizeof(struct ofp10_stats_reply), sizeof(struct ofp10_desc_stats));
	} break;
	case OFP12_VERSION: {
		set_type(OFPT12_STATS_REPLY);
		resize(sizeof(struct ofp12_stats_reply) + sizeof(struct ofp12_desc_stats));
		desc_stats.pack(soframe() + sizeof(struct ofp12_stats_reply), sizeof(struct ofp12_desc_stats));
	} break;
	case OFP13_VERSION: {
		// TODO
		throw eNotImplemented();
	} break;
	default:
		throw eBadVersion();
	}
}



cofmsg_desc_stats_reply::cofmsg_desc_stats_reply(
		cmemory *memarea) :
	cofmsg_stats(memarea),
	desc_stats(get_version())
{
	switch (get_version()) {
	case OFP10_VERSION: {
		ofh_desc_stats = soframe() + sizeof(struct ofp10_stats_reply);
	} break;
	case OFP12_VERSION: {
		ofh_desc_stats = soframe() + sizeof(struct ofp12_stats_reply);
	} break;
	case OFP13_VERSION: {
		throw eNotImplemented();
	} break;
	default:
		throw eBadVersion();
	}
}



cofmsg_desc_stats_reply::cofmsg_desc_stats_reply(
		cofmsg_desc_stats_reply const& stats)
{
	*this = stats;
}



cofmsg_desc_stats_reply&
cofmsg_desc_stats_reply::operator= (
		cofmsg_desc_stats_reply const& stats)
{
	if (this == &stats)
		return *this;

	cofmsg_stats::operator =(stats);

	ofh_desc_stats = soframe();

	return *this;
}



cofmsg_desc_stats_reply::~cofmsg_desc_stats_reply()
{

}



void
cofmsg_desc_stats_reply::reset()
{
	cofmsg_stats::reset();
}



void
cofmsg_desc_stats_reply::resize(size_t len)
{
	cofmsg::resize(len);
	switch (get_version()) {
	case OFP10_VERSION: {
		ofh_desc_stats = soframe() + sizeof(struct ofp10_stats_reply);
	} break;
	case OFP12_VERSION: {
		ofh_desc_stats = soframe() + sizeof(struct ofp12_stats_reply);
	} break;
	case OFP13_VERSION: {
		// TODO
		throw eNotImplemented();
	} break;
	default:
		throw eBadVersion();
	}

}



size_t
cofmsg_desc_stats_reply::length() const
{
	switch (get_version()) {
	case OFP10_VERSION: {
		return (sizeof(struct ofp10_stats_reply) + desc_stats.length());
	} break;
	case OFP12_VERSION: {
		return (sizeof(struct ofp12_stats_reply) + desc_stats.length());
	} break;
	case OFP13_VERSION: {
		// TODO
		throw eNotImplemented();
	} break;
	default:
		throw eBadVersion();
	}
	return 0;
}



void
cofmsg_desc_stats_reply::pack(uint8_t *buf, size_t buflen)
{
	cofmsg_stats::pack(buf, buflen); // copies common statistics header

	if ((0 == buf) || (0 == buflen))
		return;

	if (buflen < length())
		throw eInval();

	switch (get_version()) {
	case OFP10_VERSION: {
		if (buflen < (sizeof(struct ofp10_stats_reply) + desc_stats.length()))
			throw eInval();
		desc_stats.pack(buf + sizeof(struct ofp10_stats_reply), desc_stats.length());
	} break;
	case OFP12_VERSION: {
		if (buflen < (sizeof(struct ofp12_stats_reply) + desc_stats.length()))
			throw eInval();
		desc_stats.pack(buf + sizeof(struct ofp12_stats_reply), desc_stats.length());
	} break;
	case OFP13_VERSION: {
		// TODO
		throw eNotImplemented();
	} break;
	default:
		throw eBadVersion();
	}
}



void
cofmsg_desc_stats_reply::unpack(uint8_t *buf, size_t buflen)
{
	cofmsg_stats::unpack(buf, buflen);

	validate();
}



void
cofmsg_desc_stats_reply::validate()
{
	cofmsg_stats::validate(); // check generic statistics header

	ofh_desc_stats = soframe();

	switch (get_version()) {
	case OFP10_VERSION: {
		desc_stats.set_version(OFP10_VERSION);
		if (get_length() < (sizeof(struct ofp10_stats_reply) + sizeof(struct ofp10_desc_stats)))
			throw eBadSyntaxTooShort();
		ofh_desc_stats = soframe() + sizeof(struct ofp10_stats_reply);
		desc_stats.unpack(ofh_desc_stats, sizeof(struct ofp10_desc_stats));
	} break;
	case OFP12_VERSION: {
		desc_stats.set_version(OFP12_VERSION);
		if (get_length() < (sizeof(struct ofp12_stats_request) + sizeof(struct ofp12_desc_stats)))
			throw eBadSyntaxTooShort();
		ofh_desc_stats = soframe() + sizeof(struct ofp12_stats_reply);
		desc_stats.unpack(ofh_desc_stats, sizeof(struct ofp12_desc_stats));
	} break;
	case OFP13_VERSION: {
		// TODO
		throw eNotImplemented();
	} break;
	default:
		throw eBadRequestBadVersion();
	}
}



cofdesc_stats_reply&
cofmsg_desc_stats_reply::get_desc_stats()
{
	return desc_stats;
}


