/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/*
 * cclock.h
 *
 *  Created on: 07.07.2012
 *      Author: andreas
 */
#ifndef CCLOCK_H_
#define CCLOCK_H_ 

#include <string>
#include <errno.h>
#include <string.h>
#include <time.h>

#include "cvastring.h"
#include "rofl/platform/unix/csyslog.h"

namespace rofl
{

class cclock :
	public csyslog
{
private: // data structures

	std::string info;

public: // data structures

	struct timespec ts;

public:

	/**
	 *
	 */
	static cclock
	now();

	/** constructor
	 *
	 */
	cclock(
			time_t delta_sec = 0,
			time_t delta_nsec = 0);

	/** copy constructor
	 *
	 */
	cclock(
			cclock const& cc);

	/** destructor
	 *
	 */
	~cclock();
	/** assignment operator
	 *
	 */
	cclock&
	operator= (cclock const& cc);
	/** operator+
	 *
	 */
	cclock
	operator+ (cclock const& cc);
	/** operator-
	 *
	 */
	cclock
	operator- (cclock const& cc);
	/** operator+=
	 *
	 */
	cclock&
	operator+= (cclock const& cc);
	/** operator-=
	 *
	 */
	cclock&
	operator-= (cclock const& cc);

	/** operator==
	 *
	 */
	bool operator== (cclock const& cc) const;

	/** operator!=
	 *
	 */
	bool operator!= (cclock const& cc) const;

	/** operator<
	 *
	 */
	bool operator< (cclock const& cc) const;

	/** operator<=
	 *
	 */
	bool operator<= (cclock const& cc) const;

	/** operator>
	 *
	 */
	bool operator> (cclock const& cc) const;

	/** operator>=
	 *
	 */
	bool operator>= (cclock const& cc) const;

	/**
	 *
	 */
	void
	current_time();

	/**
	 *
	 */
	const char*
	c_str();
};

}; // end of namespace

#endif /* CCLOCK_H_ */
