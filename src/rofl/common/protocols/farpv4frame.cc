/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "farpv4frame.h"

using namespace rofl;

farpv4frame::farpv4frame(
		uint8_t* data,
		size_t datalen) :
		fframe(data, datalen),
		arp_hdr(0)
{
	initialize();
}



farpv4frame::farpv4frame(
		size_t len) :
		fframe(len),
		arp_hdr(0)
{
	initialize();
}



farpv4frame::~farpv4frame()
{

}



void
farpv4frame::initialize()
{
	arp_hdr = (struct arpv4_hdr_t*)soframe();
}



bool
farpv4frame::complete()
{
	initialize();

	if (framelen() < sizeof(struct arpv4_hdr_t))
		return false;

	return true;
}



size_t
farpv4frame::need_bytes()
{
	if (complete())
		return 0;

	if (framelen() < sizeof(struct arpv4_hdr_t))
		return (sizeof(struct arpv4_hdr_t) - framelen());

	return 0; // just to make gcc happy
}



void
farpv4frame::payload_insert(
		uint8_t *data,
		size_t datalen) throw (eFrameOutOfRange)
{
	return;
}


uint8_t*
farpv4frame::payload() const throw (eFrameNoPayload)
{
	throw eFrameNoPayload();
	return NULL;
}


size_t
farpv4frame::payloadlen() const throw (eFrameNoPayload)
{
	throw eFrameNoPayload();
	return 0;
}


void
farpv4frame::validate(uint16_t total_len) throw (eARPv4FrameTooShort)
{
	initialize();

	if (framelen() < (sizeof(struct arpv4_hdr_t)))
	{
		throw eARPv4FrameTooShort();
	}
}


void
farpv4frame::set_hw_addr_type(
		uint16_t hwaddrtype)
{
	arp_hdr->ar_hrd = htobe16(hwaddrtype);
}


uint16_t
farpv4frame::get_hw_addr_type()
{
	return be16toh(arp_hdr->ar_hrd);
}


void
farpv4frame::set_prot_addr_type(
		uint16_t prothwaddrtype)
{
	arp_hdr->ar_pro = htobe16(prothwaddrtype);
}


uint16_t
farpv4frame::get_prot_addr_type()
{
	return be16toh(arp_hdr->ar_pro);
}


void
farpv4frame::set_hw_addr_size(
		uint8_t size)
{
	arp_hdr->ar_hln = size;
}


uint8_t
farpv4frame::get_hw_addr_size()
{
	return arp_hdr->ar_hln;
}


void
farpv4frame::set_prot_hw_addr_size(
		uint8_t size)
{
	arp_hdr->ar_pln = size;
}


uint8_t
farpv4frame::get_prot_hw_addr_size()
{
	return arp_hdr->ar_pln;
}


void
farpv4frame::set_opcode(
		uint16_t operation)
{
	arp_hdr->ar_op = htobe16(operation);
}


uint16_t
farpv4frame::get_opcode()
{
	return be16toh(arp_hdr->ar_op);
}


void
farpv4frame::set_dl_src(
		cmacaddr const& dl_src)
{
	memcpy(arp_hdr->dl_src, dl_src.somem(), dl_src.memlen());
}


cmacaddr
farpv4frame::get_dl_src()
{
	return cmacaddr(arp_hdr->dl_src, OFP_ETH_ALEN);
}


void
farpv4frame::set_dl_dst(
		cmacaddr const& dl_dst)
{
	memcpy(arp_hdr->dl_dst, dl_dst.somem(), dl_dst.memlen());
}


cmacaddr
farpv4frame::get_dl_dst()
{
	return cmacaddr(arp_hdr->dl_dst, OFP_ETH_ALEN);
}


void
farpv4frame::set_nw_src(
		uint32_t src)
{
	arp_hdr->ip_src = src;
}


void
farpv4frame::set_nw_src(
		caddress const& addr)
{
	if (not addr.is_af_inet())
		return; // TODO: throw ...

	arp_hdr->ip_src = addr.ca_s4addr->sin_addr.s_addr;
}


caddress
farpv4frame::get_nw_src()
{
	caddress addr(AF_INET, "0.0.0.0");
	addr.ca_s4addr->sin_addr.s_addr = arp_hdr->ip_src;
	return addr;
}


void
farpv4frame::set_nw_dst(
		uint32_t dst)
{
	arp_hdr->ip_dst = dst;
}


void
farpv4frame::set_nw_dst(
		caddress const& addr)
{
	if (not addr.is_af_inet())
		return; // TODO: throw ...

	arp_hdr->ip_dst = addr.ca_s4addr->sin_addr.s_addr;
}


caddress
farpv4frame::get_nw_dst()
{
	caddress addr(AF_INET, "0.0.0.0");
	addr.ca_s4addr->sin_addr.s_addr = arp_hdr->ip_dst;
	return addr;
}


const char*
farpv4frame::c_str()
{
	cvastring vas;

	info.assign(vas("[farpv4frame(%p) dl_dst:%s dl_src:%s ip_dst:%s ip_src:%s %s]",
			this,
			get_dl_dst().c_str(),
			get_dl_src().c_str(),
			get_nw_dst().addr_c_str(),
			get_nw_src().addr_c_str(),
			fframe::c_str() ));

	return info.c_str();
}

