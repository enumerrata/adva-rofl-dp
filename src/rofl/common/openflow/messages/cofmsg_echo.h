/*
 * cofmsg_echo.h
 *
 *  Created on: 18.03.2013
 *      Author: andi
 */

#ifndef COFMSG_ECHO_H_
#define COFMSG_ECHO_H_ 1

#include "cofmsg.h"

namespace rofl
{

/**
 *
 */
class cofmsg_echo_request :
	public cofmsg
{
private:

	cmemory			body;

public:


	/** constructor
	 *
	 */
	cofmsg_echo_request(
			uint8_t of_version = 0,
			uint32_t xid = 0,
			uint8_t* data = 0,
			size_t datalen = 0);


	/**
	 *
	 */
	cofmsg_echo_request(
			cofmsg_echo_request const& echo);


	/**
	 *
	 */
	cofmsg_echo_request&
	operator= (
			cofmsg_echo_request const& echo);


	/** destructor
	 *
	 */
	virtual
	~cofmsg_echo_request();


	/**
	 *
	 */
	cofmsg_echo_request(cmemory *memarea);


	/** reset packet content
	 *
	 */
	virtual void
	reset();


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
	cmemory&
	get_body();
};



/**
 *
 */
class cofmsg_echo_reply :
	public cofmsg
{
private:

	cmemory			body;

public:


	/** constructor
	 *
	 */
	cofmsg_echo_reply(
			uint8_t of_version = 0,
			uint32_t xid = 0,
			uint8_t* data = 0,
			size_t datalen = 0);


	/**
	 *
	 */
	cofmsg_echo_reply(
			cofmsg_echo_reply const& echo);


	/**
	 *
	 */
	cofmsg_echo_reply&
	operator= (
			cofmsg_echo_reply const& echo);


	/** destructor
	 *
	 */
	virtual
	~cofmsg_echo_reply();


	/**
	 *
	 */
	cofmsg_echo_reply(cmemory *memarea);


	/** reset packet content
	 *
	 */
	virtual void
	reset();


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
	cmemory&
	get_body();
};



} // end of namespace rofl

#endif /* COFMSG_ECHO_H_ */
