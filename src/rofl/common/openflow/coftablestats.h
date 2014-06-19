/*
 * coftablestats.h
 *
 *  Created on: 14.03.2013
 *      Author: andi
 */

#ifndef COFTABLESTATS_H_
#define COFTABLESTATS_H_ 1

#include "../cmemory.h"
#include "../cvastring.h"
#include "../../platform/unix/csyslog.h"
#include "openflow.h"
#include "openflow_rofl_exceptions.h"

namespace rofl
{

class coftable_stats_reply
{
private: // data structures

	std::string		info;
	uint8_t 		of_version;
	uint8_t			table_id;
	std::string		name;
	uint64_t 		match;
	uint64_t		wildcards;
	uint32_t		write_actions;
	uint32_t 		apply_actions;
	uint64_t		write_setfields;
	uint64_t		apply_setfields;
	uint64_t		metadata_match;
	uint64_t		metadata_write;
	uint32_t		instructions;
	uint32_t		config;
	uint32_t		max_entries;
	uint32_t		active_count;
	uint64_t		lookup_count;
	uint64_t		matched_count;

public: // data structures

	friend std::ostream&
	operator<< (std::ostream& os, coftable_stats_reply const& tsr) {
		os << "tableID=" << (int)(tsr.table_id) << " "
				<< "name=" << tsr.name << " "
				<< "match=" << tsr.match << " "
				<< "wildcards=" << tsr.wildcards << " "
				<< "write-actions=" << tsr.write_actions << " "
				<< "apply-actions=" << tsr.apply_actions << " "
				<< "write-setfields=" << tsr.write_setfields << " "
				<< "apply-setfields=" << tsr.apply_setfields << " "
				<< "metadata-match=" << tsr.metadata_match << " "
				<< "metadata-write=" << tsr.metadata_write << " "
				<< "instructions=" << tsr.instructions << " "
				<< "config=" << tsr.config << " "
				<< "max_entries=" << tsr.max_entries << " "
				<< "active-count=" << tsr.active_count << " "
				<< "lookup-count=" << tsr.lookup_count << " "
				<< "matched-count=" << tsr.matched_count << " ";
		return os;
	};

public:
	/**
	 *
	 */
	coftable_stats_reply(
			uint8_t of_version = 0);

	/** OF1.0
	 *
	 */
	coftable_stats_reply(
			uint8_t of_version,
			uint8_t table_id,
			std::string name,
			uint32_t wildcards,
			uint32_t max_entries,
			uint32_t active_count,
			uint64_t lookup_count,
			uint64_t matched_count);

	/** OF1.2
	 *
	 */
	coftable_stats_reply(
			uint8_t of_version,
			uint8_t table_id,
			std::string name,
			uint64_t match,
			uint64_t wildcards,
			uint32_t write_actions,
			uint32_t apply_actions,
			uint64_t write_setfields,
			uint64_t apply_setfields,
			uint64_t metadata_match,
			uint64_t metadata_write,
			uint32_t instructions,
			uint32_t config,
			uint32_t max_entries,
			uint32_t active_count,
			uint64_t lookup_count,
			uint64_t matched_count);

	/**
	 *
	 */
	virtual
	~coftable_stats_reply();


	/**
	 *
	 */
	coftable_stats_reply(
			coftable_stats_reply const& table_stats);

	/**
	 *
	 */
	coftable_stats_reply&
	operator= (
			coftable_stats_reply const& table_stats);


	/**
	 *
	 */
	const char*
	c_str();


	/**
	 *
	 */
	size_t
	length() const;


	/**
	 *
	 */
	void
	set_version(uint8_t of_version);


	/**
	 *
	 */
	uint8_t
	get_version() const;


	/**
	 *
	 */
	uint8_t
	get_table_id() const;

	/**
	 *
	 */
	void
	set_table_id(uint8_t table_id);

	/**
	 *
	 */
	std::string&
	get_name();

	/**
	 *
	 */
	uint64_t
	get_match() const;

	/**
	 *
	 */
	void
	set_match(uint64_t match);

	/**
	 *
	 */
	uint64_t
	get_wildcards() const;

	/**
	 *
	 */
	void
	set_wildcards(uint64_t wildcards);

	/**
	 *
	 */
	uint32_t
	get_write_actions() const;

	/**
	 *
	 */
	void
	set_write_actions(uint32_t write_actions);

	/**
	 *
	 */
	uint32_t
	get_apply_actions() const;

	/**
	 *
	 */
	void
	set_apply_actions(uint32_t apply_actions);

	/**
	 *
	 */
	uint64_t
	get_write_setfields() const;

	/**
	 *
	 */
	void
	set_write_setfields(uint64_t write_setfields);

	/**
	 *
	 */
	uint64_t
	get_apply_setfields() const;

	/**
	 *
	 */
	void
	set_apply_setfields(uint64_t apply_setfields);

	/**
	 *
	 */
	uint64_t
	get_metadata_match() const;

	/**
	 *
	 */
	void
	set_metadata_match(uint64_t metadata_match);

	/**
	 *
	 */
	uint64_t
	get_metadata_write() const;

	/**
	 *
	 */
	void
	set_metadata_write(uint64_t metadata_write);

	/**
	 *
	 */
	uint32_t
	get_instructions() const;

	/**
	 *
	 */
	void
	set_instructions(uint32_t instructions);

	/**
	 *
	 */
	uint32_t&
	get_config();

	/**
	 *
	 */
	uint32_t
	get_max_entries() const;

	/**
	 *
	 */
	uint32_t
	get_active_count() const;

	/**
	 *
	 */
	uint64_t&
	get_lookup_count();

	/**
	 *
	 */
	uint64_t&
	get_matched_count();

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
};

}

#endif /* COFTABLESTATS_H_ */
