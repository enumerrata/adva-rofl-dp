#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include "crofbasetest.h"
#include <stdlib.h>

using namespace rofl;

CPPUNIT_TEST_SUITE_REGISTRATION( crofbaseTest );


void
crofbaseTest::setUp()
{
	ctl = new crofbase();
	dpt = new crofbase();
}



void
crofbaseTest::tearDown()
{
	delete dpt;
	delete ctl;
}



void
crofbaseTest::testConnect()
{
	ctl->rpc_listen_for_dpts(caddress(AF_INET, "0.0.0.0", 6633));
	dpt->rpc_connect_to_ctl(0x3, 2, caddress(AF_INET, "127.0.0.1", 6633));
	
	//ciosrv::run();

	CPPUNIT_ASSERT(0 == 0);
}

