#include <rofl/platform/unix/cunixenv.h>
#include "etherswitch.h"
#include <stdio.h>
#include <thread>
#include <string>
#include <unistd.h>
extern "C"{
	#include "../../adva-agent-rofl/Agent/Agent.h"
}

#define DBG(a, b...) fprintf(stderr, "ROFL:[%s]\t"a"\r\n", __func__, ##b);

std::string of_ctrl_IP="127.0.0.1";	// default IP of openflow controller
int of_ctrl_port=6633;			// default port of openflow controller

//Handler to stop ciosrv
void interrupt_handler(int dummy=0) {
	//Only stop ciosrv
	ciosrv::stop();
}

#if 0
void parse_xml() {
	// TODO
	of_ctrl_IP = "";
	of_ctrl_port = 6633;
}
#endif

int main(int argc, char** argv) {

	if(argc < 2) {
		printf("Usage: %s <config_file.xml>\n", argv[0]);
		return 0;
	}
	/* update defaults */
	rofl::csyslog::initlog(rofl::csyslog::LOGTYPE_FILE, rofl::csyslog::DBG,
			std::string("etherswitch.log"),	"### AGENT: ");
	rofl::csyslog::set_debug_level("csocket", "dbg");
	rofl::csyslog::set_debug_level("ciosrv", "dbg");
	rofl::csyslog::set_debug_level("cthread", "dbg");

	// SNMP part logging
	X_Log_Open(X_LOG_MASK_STDERR | X_LOG_MASK_FILE);
	X_Log_SetFile("log.txt");
	X_Log_SetLevel(0, 3); // enable logging for channel module
//	X_Log_SetLevel(1, 3); // enable logging for interface
//	X_Log_SetLevel(2, 3); // enable logging for resources

	// initialise SNMP library
	SNMP_Lib_Init();

	X_Core Core;
	DBG("Initial Core size is: %d", sizeof(Core));
	DBG("Starting the SNMP thread to initialise resource manager.");
	std::thread snmp_thrd(rofl_X_Core_Create_From_File, argv[1], &Core);

	DBG("Main thread will wait for 3 seconds...");
	sleep(3); 	// sleep for 5 seconds
	DBG("New Core size is: %d", sizeof(Core));
	DBG("sizeof of list_ports: %d\n", sizeof(Core.Ports));

	rofl::ciosrv::init();

	etherswitch::ethswitch sw(&Core);

	sw.rpc_connect_to_ctl(OFP10_VERSION,30,caddress(AF_INET, "127.0.0.1", of_ctrl_port));
	//sw.rpc_close_all();

	//Capture control+C
	signal(SIGINT, interrupt_handler);

	// after that thread enters an infinite loop
	DBG("Starting infinite ciosrv loop.");
	rofl::ciosrv::run();
	
	rofl::csyslog::flushlog();
	rofl::ciosrv::destroy();

	return 0;
}

