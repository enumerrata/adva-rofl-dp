#include "rofl/common/openflow/coxmlist.h"
#include "rofl/common/cmemory.h"
#include "rofl/common/caddress.h"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace rofl;

class coxmlistTest : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE( coxmlistTest );
	CPPUNIT_TEST( testPack );
	CPPUNIT_TEST( testAssignmentOperator );
	CPPUNIT_TEST( testIsPartOf );
	CPPUNIT_TEST( testContains );
	CPPUNIT_TEST_SUITE_END();

private:

	coxmlist*	packet;
	coxmlist*	rule_nonstrict;
	coxmlist*	rule_strict;
	coxmlist*	rule_mismatch;

	uint16_t	exact_hits;
	uint16_t	wildcard_hits;
	uint16_t	missed;

public:
	void setUp();
	void tearDown();

	void testPack();
	void testAssignmentOperator();
	void testIsPartOf();
	void testContains();
};

