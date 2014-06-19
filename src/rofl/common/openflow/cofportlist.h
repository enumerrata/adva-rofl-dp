/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef COFPORTLIST_H
#define COFPORTLIST_H 1

#include <algorithm>

#include "../cvastring.h"
#include "../cerror.h"
#include "../coflist.h"
#include "openflow.h"

#include "cofport.h"

namespace rofl
{

class ePortListBase : public cerror {}; // base error class cofinlist
class ePortListInval : public ePortListBase {}; // invalid parameter
class ePortListNotFound : public ePortListBase {}; // element not found
class ePortListOutOfRange : public ePortListBase {}; // out of range



class cofportlist :
	public coflist<cofport>
{
public: // static methods

	/**
	 */
	static void test();

public: // methods


	/** constructor
	 */
	cofportlist();


	/** destructor
	 */
	virtual
	~cofportlist();


	/**
	 */
	cofportlist(cofportlist const& portlist)
	{
		*this = portlist;
	};


	/**
	 */
	cofportlist& operator= (cofportlist const& portlist)
	{
		if (this == &portlist)
			return *this;
		coflist<cofport>::operator= (portlist);
		return *this;
	};

#if 0
	/** stores cofinst instances in this->invec from a packed array struct ofp_instruction (e.g. in struct ofp_flow_mod)
	 */
	template<class T>
	std::vector<cofport>&			// returns reference to this->invec
	unpack(
		T *ports, // parses memory area buckets and creates cofinst instance in this->invec
		size_t portlen)					// length of memory area to be parsed
	throw (ePortListInval);
#endif

	/** stores cofinst instances in this->invec from a packed array struct ofp_instruction (e.g. in struct ofp_flow_mod)
	 */
	std::vector<cofport>&			// returns reference to this->invec
	unpack(
		struct ofp10_port *ports, // parses memory area buckets and creates cofinst instance in this->invec
		size_t portlen)					// length of memory area to be parsed
	throw (ePortListInval);


	/** stores cofinst instances in this->invec from a packed array struct ofp_instruction (e.g. in struct ofp_flow_mod)
	 */
	std::vector<cofport>&			// returns reference to this->invec
	unpack(
		struct ofp12_port *ports, // parses memory area buckets and creates cofinst instance in this->invec
		size_t portlen)					// length of memory area to be parsed
	throw (ePortListInval);


#if 0
	/** builds an array of struct ofp_instruction from this->invec
	 */
	template<class T>
	T*			// returns parameter "struct ofp_instruction *instructions"
	pack(
		T *ports, // pointer to memory area for storing this->invec
		size_t portlen) 					// length of memory area
	throw (ePortListInval);
#endif

	/** builds an array of struct ofp_instruction from this->invec
	 */
	struct ofp10_port*			// returns parameter "struct ofp_instruction *instructions"
	pack(
		struct ofp10_port *ports, // pointer to memory area for storing this->invec
		size_t portlen) const					// length of memory area
	throw (ePortListInval);


	/** builds an array of struct ofp_instruction from this->invec
	 */
	struct ofp12_port*			// returns parameter "struct ofp_instruction *instructions"
	pack(
		struct ofp12_port *ports, // pointer to memory area for storing this->invec
		size_t portlen) const					// length of memory area
	throw (ePortListInval);

#if 0
	/** builds an array of struct ofp_instruction from this->invec
	 */
	struct ofp13_port*			// returns parameter "struct ofp_instruction *instructions"
	pack(
		struct ofp13_port *ports, // pointer to memory area for storing this->invec
		size_t portlen) 					// length of memory area
	throw (ePortListInval);
#endif


	/** returns required length for array of struct ofp_instruction
	 * for all instructions defined in this->invec
	 */
	size_t
	length() const;


	/** dump info string
	 */
	const char*
	c_str();


	/** find a specific ofport
	 */
	cofport&
	find_port(
			uint32_t port_no)
	throw (ePortListNotFound);


private:

	std::string info; // info string

};

}; // end of namespace

#endif
