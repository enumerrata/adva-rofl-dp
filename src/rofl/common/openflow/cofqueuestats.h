/*
 * cofqueuestats.h
 *
 *  Created on: 14.03.2013
 *      Author: andi
 */

#ifndef COFQUEUESTATS_H_
#define COFQUEUESTATS_H_ 1

#include "../cmemory.h"
#include "../../platform/unix/csyslog.h"
#include "openflow.h"
#include "openflow_rofl_exceptions.h"

namespace rofl
{



class cofqueue_stats_request
{
private: // data structures

	uint8_t 		of_version;
	uint32_t 		port_no;
	uint32_t		queue_id;

public: // data structures


public:
	/**
	 *
	 */
	cofqueue_stats_request(
			uint8_t of_version = 0);

	/**
	 *
	 */
	cofqueue_stats_request(
			uint8_t of_version,
			uint32_t port_no,
			uint32_t queue_id);

	/**
	 *
	 */
	virtual
	~cofqueue_stats_request();


	/**
	 *
	 */
	cofqueue_stats_request(
			cofqueue_stats_request const& stats);

	/**
	 *
	 */
	cofqueue_stats_request&
	operator= (
			cofqueue_stats_request const& stats);


	/**
	 *
	 */
	void
	pack(uint8_t *buf, size_t buflen) const;

	/**
	 *
	 */
	void
	unpack(uint8_t *buf, size_t buflen);


	/**
	 *
	 */
	size_t
	length() const;


public:


	/**
	 *
	 */
	void
	set_version(uint8_t of_version) { this->of_version = of_version; };


	/**
	 *
	 */
	uint8_t
	get_version() const { return of_version; };


	/**
	 *
	 */
	uint32_t
	get_port_no() const { return port_no; };


	/**
	 *
	 */
	uint32_t
	get_queue_id() const { return queue_id; };


	/**
	 *
	 */
	void
	set_port_no(uint32_t port_no) { this->port_no = port_no; };


	/**
	 *
	 */
	void
	set_queue_id(uint32_t queue_id) { this->queue_id = queue_id; };


public:


	/**
	 *
	 */
	friend std::ostream&
	operator<< (std::ostream& os, cofqueue_stats_request const& request)
	{
		os << "cofqueue_stats_request[";
		os << std::hex;
		os << "port-no=" << request.port_no << " ";
		os << "queue-id=" << request.queue_id << " ";
		os << std::dec;
		os << "]";
		return os;
	};
};



class cofqueue_stats_reply
{
private: // data structures

	uint8_t 		of_version;
	uint32_t		port_no;
	uint32_t		queue_id;
	uint64_t		tx_bytes;
	uint64_t		tx_packets;
	uint64_t		tx_errors;

public: // data structures


public:
	/**
	 *
	 */
	cofqueue_stats_reply(
			uint8_t of_version = 0);

	/**
	 *
	 */
	cofqueue_stats_reply(
			uint8_t of_version,
			uint32_t port_no,
			uint32_t queue_id,
			uint64_t tx_bytes,
			uint64_t tx_packets,
			uint64_t tx_errors);

	/**
	 *
	 */
	virtual
	~cofqueue_stats_reply();


	/**
	 *
	 */
	cofqueue_stats_reply(
			cofqueue_stats_reply const& stats);

	/**
	 *
	 */
	cofqueue_stats_reply&
	operator= (
			cofqueue_stats_reply const& stats);


	/**
	 *
	 */
	void
	pack(uint8_t *buf, size_t buflen) const;

	/**
	 *
	 */
	void
	unpack(uint8_t *buf, size_t buflen);


	/**
	 *
	 */
	size_t
	length() const;


public:


	/**
	 *
	 */
	void
	set_version(uint8_t of_version) { this->of_version = of_version; };


	/**
	 *
	 */
	uint8_t
	get_version() const { return of_version; };


	/**
	 *
	 */
	uint32_t
	get_port_no() const { return port_no; };

	/**
	 *
	 */
	uint32_t
	get_queue_id() const { return queue_id; };

	/**
	 *
	 */
	uint64_t
	get_tx_bytes() const { return tx_bytes; };

	/**
	 *
	 */
	uint64_t
	get_tx_packets() const { return tx_packets; };

	/**
	 *
	 */
	uint64_t
	get_tx_errors() const { return tx_errors; };

	/**
	 *
	 */
	void
	set_port_no(uint32_t port_no) { this->port_no = port_no; };

	/**
	 *
	 */
	void
	set_queue_id(uint32_t queue_id) { this->queue_id = queue_id; };

	/**
	 *
	 */
	void
	set_tx_bytes(uint64_t tx_bytes) { this->tx_bytes = tx_bytes; };

	/**
	 *
	 */
	void
	set_tx_packets(uint64_t tx_packets) { this->tx_packets = tx_packets; };

	/**
	 *
	 */
	void
	set_tx_errors(uint64_t tx_errors) { this->tx_errors = tx_errors; };


public:


	/**
	 *
	 */
	friend std::ostream&
	operator<< (std::ostream& os, cofqueue_stats_reply const& reply)
	{
		os << "cofqueue_stats_request[";
		os << std::hex;
		os << "port-no=" << reply.port_no << " ";
		os << "queue-id=" << reply.queue_id << " ";
		os << std::dec;
		os << "tx-bytes=" << reply.tx_bytes << " ";
		os << "tx-packets=" << reply.tx_packets << " ";
		os << "tx-errors=" << reply.tx_errors << " ";
		os << "]";
		return os;
	};
};

}

#endif /* COFQUEUESTATS_H_ */
