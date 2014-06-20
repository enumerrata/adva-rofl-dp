extern "C"{
	#include "../../adva-agent-rofl/Agent/Agent.h"
}
#include <rofl/platform/unix/cunixenv.h>
#include "advaswitch.h"
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
	printf("\nADVA ROADM OpenFlow agent just started. ");
	printf("(Default OpenFlow port is 6653)\n\n");

	if (argc < 2) {
		std::cout << "Usage is: advaswitch <config_file.xml> [controller port]\n";
		exit(0);
	}

	/* Rofl debugging and logging initialisation*/
	rofl::csyslog::set_debug_level("csocket", "dbg");

	rofl::csyslog::set_debug_level("ciosrv", "warn");
	rofl::csyslog::set_debug_level("cthread", "warn");
	rofl::csyslog::set_debug_level("cofctlImpl", "dbg");
	rofl::csyslog::set_debug_level("cofdtpImpl", "dbg");
//	rofl::csyslog::set_debug_level("crofbase", "dbg");
//	rofl::csyslog::set_debug_level("advaroadm", "dbg");
//	rofl::csyslog::set_all_debug_levels("dbg");

	/** SNMP channel and resource model logging */
//  X_Log_Open(X_LOG_MASK_STDERR /*| X_LOG_MASK_FILE*/);
//  X_Log_SetFile("log.txt");
//  X_Log_SetLevel(0, 3);	// enable logging for channel module
//  X_Log_SetLevel(1, 3);	// enable logging for interface
//  X_Log_SetLevel(2, 3);	// enable logging for resources

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

    advaswitch::advaroadm::init();		// initialise structures

    DBG("Retrieving Openflow attributes from ADVA ROADM...");
    pthread_mutex_lock(&core_mutex_init);
    advaswitch::advaroadm sw(&core);
    pthread_mutex_unlock(&core_mutex_init);

    if ((of_ip = sw.get_controller_ip()) == NULL)
    	of_ip = "localhost";
	sw.rpc_connect_to_ctl(OFP10_VERSION, RECONNECT_CTRL_TIME,
			caddress(AF_INET, of_ip, of_port));
	DBG("Established connection to SDN controller (%s:%d).", of_ip, of_port);

	advaswitch::advaroadm::run();
	
	rofl::csyslog::flushlog();
	rofl::ciosrv::destroy();

	return 0;
}
