#include <rofl/platform/unix/cunixenv.h>
#include "polatisswitch.h"
#include <thread>
#include <threads.h>

#define DBG(a,b...) fprintf(stderr, "ROFL [%s]\t"a"\n", __func__, ##b);
#define RECONNECT_CTRL_TIME		12

pthread_mutex_t core_mutex_init;	/* mutex used to access the resource model
 	 	 	 	 	 	 	 	 	   of the device */

//Handler to stop ciosrv
void interrupt_handler(int dummy=0) {

	rofl::csyslog::flushlog();
	rofl::ciosrv::destroy();

	ciosrv::stop();
}

int
main(int argc, char** argv)
{
	printf("\nPOLATIS Fibre switch OpenFlow agent just started... ");
	printf("(Default OpenFlow port is 6653)\n\n");

	if (argc < 2) {
		std::cout << "Usage is: polatisswitch <config_file.xml> [controller port]\n";
		exit(0);
	}

	/* Rofl debugging and logging initialisation*/
	rofl::csyslog::set_debug_level("csocket", "dbg");

	rofl::csyslog::set_debug_level("ciosrv", "dbg");
	rofl::csyslog::set_debug_level("cthread", "dbg");
	rofl::csyslog::set_debug_level("cofctlImpl", "dbg");
	rofl::csyslog::set_debug_level("cofdtpImpl", "dbg");
	rofl::csyslog::set_debug_level("crofbase", "dbg");
//	rofl::csyslog::set_all_debug_levels("dbg");

	// initializing structures
	uint16_t of_port = 6653;	// default
	char* of_ip = "localhost";	// default
	if (argv[2] != NULL)
	{
		of_port = atoi(argv[2]);
	}
    core_mutex_init = PTHREAD_MUTEX_INITIALIZER;
    X_Core core;	// core structure - contains the resource model of the device
    SNMP_Lib_Init();
    signal(SIGINT, interrupt_handler); 	//Capture control+C

    pthread_mutex_lock(&core_mutex_init);

    rofl_X_Core_Create_From_File(argv[1], &core);	// update core with device info

    // &core_mutex_init should be unlocked somewhere in the agent.c code


    DBG("Retrieving Openflow attributes from ADVA ROADM...");
    polatisswitch::polatissw::init();		// initialise structures

    pthread_mutex_lock(&core_mutex_init);
    printf("Controller ip: %s : %s", core.TL1_Listen, core.TL1_Port);
    polatisswitch::polatissw sw(&core);
    pthread_mutex_unlock(&core_mutex_init);

    if ((of_ip = sw.get_controller_ip()) == NULL)
    	of_ip = "localhost";
    DBG("Trying to connect to controller with IP: %s:%d", of_ip, of_port);
	sw.rpc_connect_to_ctl(OFP10_VERSION, RECONNECT_CTRL_TIME,
			caddress(AF_INET, of_ip, of_port));
	DBG("Established connection to SDN controller (%s:%d).", of_ip, of_port);

	polatisswitch::polatissw::run();
	
	rofl::csyslog::flushlog();
	rofl::ciosrv::destroy();

	return 0;
}
