#include "cofmsg_cflow_mod.h"

#define DBG(a, b...) fprintf(stderr, "ROFL [%s]:"a"\n", __func__, ##b);

using namespace rofl;


cofmsg_cflow_mod::cofmsg_cflow_mod(
		uint8_t of_version,
		uint8_t type,
		uint32_t xid,
		uint8_t  command,
		uint16_t hard_timeout/*,
		ofp_connect_ocs connect*/
		):cofmsg(sizeof(struct ofp_header))
{
	cflow_mod = (struct ofp_cflow_mod*) soframe();

	set_version(of_version);
	set_type(type);		// NOX ?
	set_xid(xid);
	set_type(OFPT10_FLOW_MOD);
	cflow_mod->hard_timeout	= htobe16(hard_timeout);

	// OCS
	resize(56);
}

cofmsg_cflow_mod::cofmsg_cflow_mod(cmemory *memarea)
		: cofmsg(memarea)
{
	cflow_mod = (struct ofp_cflow_mod*) soframe();

	uint8_t *ptr = (uint8_t*) cflow_mod;
	uint16_t *num = (uint16_t*) malloc(sizeof(uint16_t));

	ptr += sizeof(struct ofp_header);
	memcpy(num, ptr, sizeof(uint16_t));
//	DBG("command:%d", ntohs(*num));
	set_command(ntohs(*num));

	ptr += sizeof(uint16_t);
	memcpy(num, ptr, sizeof(uint16_t));
//	DBG("hard_timeout:%d", ntohs(*num));
	this->set_hard_timeout(ntohs(*num));

	ptr = ptr + sizeof(uint16_t) + 4;	//pad
	memcpy(num, ptr, sizeof(uint16_t));
//	DBG("wildcards:%d", ntohs(*num));
	this->set_wildcards(ntohs(*num));

	ptr += sizeof(uint16_t);
	memcpy(num, ptr, sizeof(uint16_t));
//	DBG("num_components:%d", ntohs(*num));
	this->set_num_components(ntohs(*num));

	ptr = ptr + sizeof(uint16_t) + 4;	//pad
	memcpy(num, ptr, sizeof(uint16_t));
//	DBG("in wport:%d", ntohs(*num));

	ptr = ptr + sizeof(uint16_t) + 6 + sizeof(uint64_t);
	memcpy(num, ptr, sizeof(uint16_t));
//	DBG("out wport:%d", ntohs(*num));

	free(num);


}

#if 0


cofmsg_cflow_modcs::cofmsg_flow_mod_ocs(
		cofmsg_flow_mod_ocs const& flow_mod)
{
	*this = flow_mod;
}



cofmsg_flow_mod_ocs&
cofmsg_flow_mod_ocs::operator= (
		cofmsg_flow_mod_ocs const& flow_mod)
{
	if (this == &flow_mod)
		return *this;

	cofmsg::operator =(flow_mod);

	ofh_flow_mod = soframe();

	actions			= flow_mod.actions; // OF1.0 only
	instructions 	= flow_mod.instructions;
	match			= flow_mod.match;

	return *this;
}

#endif

cofmsg_cflow_mod::~cofmsg_cflow_mod()
{

}



void
cofmsg_cflow_mod::reset()
{
	cofmsg::reset();
}



void
cofmsg_cflow_mod::resize(size_t len)
{
	cofmsg::resize(len);
	cflow_mod = (struct ofp_cflow_mod*) soframe();
}



size_t
cofmsg_cflow_mod::length() const
{
	// OCS need to fix that - for now only wport cross-connection supported
	return 56;
}



void
cofmsg_cflow_mod::pack(uint8_t *buf, size_t buflen)
{
	set_length(length());

	if ((0 == buf) || (0 == buflen))
		return;

	if (buflen < length())
		throw eInval();

	memcpy(buf, soframe(), buflen);

}



void
cofmsg_cflow_mod::unpack(uint8_t *buf, size_t buflen)
{
	cofmsg::unpack(buf, buflen);

	validate();
}



void
cofmsg_cflow_mod::validate()
{
	cofmsg::validate(); // check generic OpenFlow header

	cflow_mod = (struct ofp_cflow_mod *) soframe();

//	actions.clear();
//	instructions.clear();
//	match.clear();


//	switch (get_version()) {
//	case OFP10_VERSION: {
//		if (get_length() < sizeof(struct ofp10_flow_mod))
//			throw eBadSyntaxTooShort();
//		match.unpack(&(ofh10_flow_mod->match), sizeof(struct ofp10_match));
//		actions.unpack(ofh10_flow_mod->actions, get_length() - sizeof(struct ofp10_flow_mod));
//	} break;

}


#if 0
/** IMPLEMENTATION  FOR CROSS CONNECTED PORTS GETTERS & SETTERS*/
void
set_in_port(std::list<uint16_t> ports) {

}

/**
 * list of in ports
 * */
std::list<uint16_t>
get_in_port() {

}

void
set_out_port(std::list<uint16_t> ports) {

}

/**
 * list of out ports
 * */
std::list<uint16_t>
get_out_port() {
}

void
set_in_tport(std::list<ofp_tdm_port> ports) {

}

std::list<ofp_tdm_port>
get_in_tport() {

}

void
set_out_tport(std::list<ofp_tdm_port> ports) {

}

std::list<ofp_tdm_port>
get_out_tport() {

}

void
set_in_wport(std::list<ofp_wave_port> ports) {

}

std::list<ofp_wave_port>
get_in_wport() {

}

void
set_out_wport(std::list<ofp_wave_port> ports) {

}

std::list<ofp_wave_port>
get_out_wport() {

}
#endif
