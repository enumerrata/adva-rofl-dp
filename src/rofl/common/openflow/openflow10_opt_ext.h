/*
 * openflow10_opt_ext.h
 *
 *  Created on: 31.01.2014
 *      Author: UNIVBRIS
 *
 *  contains structures as defined in the optical switch addendum
 */


#ifndef _OPENFLOW_OPENFLOW10_OPT_EXT_H
#define _OPENFLOW_OPENFLOW10_OPT_EXT_H 1

#include "openflow_common.h"
#include "openflow10.h"

/*
 * Circuit switch physical port description
 * */
struct ofp_phy_cport {
    uint16_t port_no;
    uint8_t hw_addr[OFP_ETH_ALEN];		 /*Ethernet address - 6-byte*/
    uint8_t name[OFP_MAX_PORT_NAME_LEN]; /* Null-terminated - 16 byte*/

    uint32_t config;           /* Bitmap of OFPPC_* flags. */
    uint32_t state;            /* Bitmap of OFPPS_* flags. */

    /* Bitmaps of OFPPF_* that describe features.  All bits zeroed if
     * unsupported or unavailable. */
    uint32_t curr;             /* Current features. */
    uint32_t advertised;       /* Features being advertised by the port. */
    uint32_t supported;        /* Features supported by the port. */
    uint32_t peer;             /* Features advertised by peer. */
    // 48 byte up to this point

    uint32_t supp_sw_tdm_gran; /* TDM switching granularity OFPTSG_* flags */
    uint16_t supp_swtype;      /* Bitmap of switching type OFPST_* flags */
    uint16_t peer_port_no;	   /* Discovered peer's switchport number */
    uint64_t peer_datapath_id; /* Discovered peer's datapath id */
    uint16_t num_bandwidth;	   /* Identifies number of bandwidth array elems */
    uint8_t  pad[6];           /* Align to 64 bits */
    uint64_t bandwidth[1];	   /* Bitmap of OFPCBL_* or OFPCBT_* flags */
};
OFP_ASSERT(sizeof(struct ofp_phy_cport) == 80);

/* Description of a TDM port */
struct ofp_tdm_port {
	uint16_t tport;		/* port numbers in OFPP_* ports */
	uint16_t tstart;	/* starting time slot */
	uint32_t tsignal;	/*one of OFPTSG_* flags */
};
OFP_ASSERT(sizeof(struct ofp_tdm_port) == 8);

/* Description of a lambda channel */
struct ofp_wave_port {
	uint16_t wport;		 /* restricted to real port numbers in OFPP_* ports */
	uint8_t  pad[6];	 /* align to 64 bits */
	uint64_t wavelength; /* use of the OFPCBL_* flags */
};
OFP_ASSERT(sizeof(struct ofp_wave_port) == 16);

/*
 * switch features struct as modified for circuit switch
 *
 *  */
struct ofp10_switch_features_ocs {
    struct ofp_header header;
    uint64_t datapath_id;   /* Datapath unique ID.  The lower 48-bits are for
                               a MAC address, while the upper 16-bits are
                               implementer-defined. */

    uint32_t n_buffers;     /* Max packets buffered at once. */

    uint8_t n_tables;       /* Number of tables supported by datapath. */

    uint8_t n_cports;		/* circuit ports */
    uint8_t pad[2];			/* 64 bit padding */

    /* Features. */
    uint32_t capabilities;  /* Bitmap of support "ofp_capabilities". */
    uint32_t actions;       /* Bitmap of supported "ofp_action_type"s. */

    struct ofp10_port ports[0]; /* packet ports */

    struct ofp_phy_cport cports[0]; /* circuit ports */
};
OFP_ASSERT(sizeof(struct ofp10_switch_features_ocs) == 32);

enum ofp_capabilities_ocs {

	OFPC_OCS_FLOW_STATS		= 1 << 0,	/* Flow statistics */
	OFPC_OCS_TABLE_STATS	= 1 << 1,	/* Table statistics */
	OFPC_OCS_PORT_STATS		= 1 << 2,	/* Port statistics */
	OFPC_OCS_STP			= 1 << 3, 	/* 802.1d spanning tree */
	OFPC_OCS_RESERVED		= 1 << 4, 	/* Reserved, must be zero */
	OFPC_OCS_IP_REASM		= 1 << 5, 	/* Can reassemble IP fragments */
	OFPC_OCS_QUEUE_STATS	= 1 << 6, 	/* Queue statistics */
	OFPC_OCS_ARP_MATCH_IP	= 1 << 7, 	/* Match IP addresses in ARP pkts */

	/* following capabilities are defined for circuit switches */
	OFPC_OCS_CTG_CONCAT		= 1 << 31,	/* Contiguous concat on all TDM ports. */
	OFPC_OCS_VIR_CONCAT		= 1 << 30,	/* Virtual concat on all TDM ports. */
	OFPC_OCS_LCAS			= 1 << 29,	/* Link Capacity Adjustment Scheme */
	OFPC_OCS_POS			= 1 << 28,	/* Packet over Sonet adaptation */
	OFPC_OCS_GFP			= 1 << 27,	/* Generic Framing Procedure */
	OFPC_OCS_10G_WAN		= 1 << 26	/* native transport of 10G_WAN_PHY
										   on OC-192 */
};


/**
 * Port numbering. Physical ports are numbered starting from 1
 * */
enum ofp_port_ocs {
/* Maximum number of physical switch ports. */
/* Switch internal ports - 0xfa00 to 0xfaff */
/* Switch virtual circuit ports - 0xfb00 to 0xfeff */
/* Other virtual ports - 0xff00 to 0xffff */
	OFPP_MAX 		= 0xfa00,		/* Fake output "ports". */
	OFPP_IN_PORT 	= 0xfff8,		/* Send the packet out the input port. This
									   virtual port must be explicitly used
									   in order to send back out of the input
									   port. */
	OFPP_TABLE		= 0xfff9,		/* Perform actions in flow table.
									   NB: This can only be the destination
									   port for packet-out messages. */
	OFPP_NORMAL		= 0xfffa, 		/* Process with normal L2/L3 switching. */
	OFPP_FLOOD		= 0xfffb, 		/* All physical ports except input port and
									   those disabled by STP. */
	OFPP_ALL		= 0xfffc,		/* All physical ports except input port. */
	OFPP_CONTROLLER = 0xfffd, 		/* Send to controller. */
	OFPP_LOCAL		= 0xfffe,		/* Local openflow "port". */
	OFPP_NONE		= 0xffff		/* Not associated with a physical port. */
};

/* Features of physical ports available in a datapath. */
enum ofp_port_features_ocs {
	OFPPF_OCS_10MB_HD		= 1 << 0,	/* 10 Mb half-duplex rate support. */
	OFPPF_OCS_10MB_FD		= 1 << 1,	/* 10 Mb full-duplex rate support. */
	OFPPF_OCS_100MB_HD 		= 1 << 2,	/* 100 Mb half-duplex rate support. */
	OFPPF_OCS_100MB_FD		= 1 << 3,	/* 100 Mb full-duplex rate support. */
	OFPPF_OCS_1GB_HD		= 1 << 4,	/* 1 Gb half-duplex rate support. */
	OFPPF_OCS_1GB_FD		= 1 << 5,	/* 1 Gb full-duplex rate support. */
	OFPPF_OCS_10GB_FD		= 1 << 6,	/* 10 Gb full-duplex rate support. */
	OFPPF_OCS_COPPER		= 1 << 7, 	/* Copper medium */
	OFPPF_OCS_FIBER			= 1 << 8,	/* Fiber medium */
	OFPPF_OCS_AUTONEG		= 1 << 9,	/* Auto-negotiation */
	OFPPF_OCS_PAUSE			= 1 << 10,	/* Pause */
	OFPPF_OCS_PAUSE_ASYM	= 1 << 11,	/* Asymmetric pause */

	/* The following have been added for WAN interfaces */
	OFPPF_OCS_X				= 1 << 20,	/* Dont care applicable to fiber ports */
	OFPPF_OCS_OC1			= 1 << 21,	/* 51.84 Mbps OC-1/STM-0 */
	OFPPF_OCS_OC3			= 1 << 22,	/* 155.52 Mbps OC-3/STM-1 */
	OFPPF_OCS_OC12			= 1 << 23,	/* 622.08 Mbps OC-12/STM-4 */
	OFPPF_OCS_OC48			= 1 << 24,	/* 2.48832 Gbps OC-48/STM-16 */
	OFPPF_OCS_OC192			= 1 << 25,	/* 9.95328 Gbps OC-192/STM-64 */
	OFPPF_OCS_OC768			= 1 << 26,	/* 39.81312 Gbps OC-768/STM-256 */
	OFPPF_OCS_100GB			= 1 << 27,	/* 100 Gbps */
	OFPPF_OCS_10GB_WAN 		= 1 << 28,	/* 10 Gbps Ethernet WAN PHY (9.95328 Gbps) */
	OFPPF_OCS_OTU1 			= 1 << 29,	/* OTN OTU-1 2.666 Gbps */
	OFPPF_OCS_OTU2 			= 1 << 30,	/* OTN OTU-2 10.709 Gbps */
	OFPPF_OCS_OTU3 			= 1 << 31	/* OTN OTU-3 42.836 Gbps */

};

/*
 * Switching type of physical ports available in a datapath.
 * */
enum ofp_port_swtype_ocs {
	OFPST_L4		= 1 << 0, /* can switch packets based on TCP/UDP headers */
	OFPST_IP		= 1 << 1, /* can switch packets based on IP  headers */
	OFPST_MPLS		= 1 << 2, /* can switch packets based on MPLS labels */
	OFPST_VLAN		= 1 << 3, /* can switch packets based on VLAN tags */
	OFPST_ETH		= 1 << 4, /* can switch packets based on ETH headers */

	OFPST_T_SONET 	= 1 << 11,/* can switch circuits based on SONET standard */
	OFPST_T_SDH		= 1 << 12,/* can switch circuits based on SDH standard */
	OFPST_T_OTN		= 1 << 13,/* can switch circuits based on OTN standard */
	OFPST_WAVE		= 1 << 14,/* can switch circuits based on ITU-T lambdas */
	OFPST_FIBER		= 1 << 15 /* can switch circuits based on SM-MM fiber */
};

/* Minimum switching granularity of TDM physical ports available in a datapath. */
enum ofp_tdm_gran_ocs {
	OFPTSG_STS_1,		/* STS-1	/ STM-0		*/
	OFPTSG_STS_3,		/* STS-3	/ STM-1		*/
	OFPTSG_STS_3c,		/* STS-3c	/ STM-1		*/
	OFPTSG_STS_12,		/* STS-12	/ STM-4		*/
	OFPTSG_STS_12c,		/* STS-12c	/ STM-4c	*/
	OFPTSG_STS_48,		/* STS-48	/ STM-16	*/
	OFPTSG_STS_48c,		/* STS-48c	/ STM-16c	*/
	OFPTSG_STS_192,		/* STS-192	/ STM-64	*/
	OFPTSG_STS_192c,	/* STS-192c	/ STM-64c	*/
	OFPTSG_STS_768,		/* STS-768	/ STM-256	*/
	OFPTSG_STS_768c		/* STS-768c	/ STM-256c	*/
};

/* bandwidth field in wave ports - 64 bitmap
 * lower 10 bits reserved flags with special meaning */
enum ofp_port_lam_bw {
	OFPCBL_X		= 1 << 0,/* 1 if fiber switch, 0 if wavelength switch */
	OFPCBL_100_50	= 1 << 1,/* 1 if 100GHz channel spacing, 0 if 50GHz */
	OFPCBL_C_L		= 1 << 2,/* 1 if using C-band frequencies, 0 if L-band */
	OFPCBL_OSC		= 1 << 3,/* 1 if supporting OSC at 1510nm, 0 if not */
	OFPCBL_TLS		= 1 << 4,/* 1 if using a TLS, 0 if not */
	OFPCBL_FLAG		= 1 << 5,/* 1 if reporting wave-support, 0 if reporting used waves */
};

/* Description of a cross-connection */
struct ofp_connect_ocs {
	uint16_t	wildcards;				/* identifies ports to use below */
	uint16_t	num_components;			/* identifies number of cross-connects
										   to be made - num array elements */
	uint8_t		pad[4];					/* Align to 64 bits */

	uint16_t	in_port[0];				/* OFPP_* ports - real or virtual */
	uint16_t	out_port[0];			/* OFPP_* ports - real or virtual */

	struct ofp_tdm_port in_tport[0];	/* Description of a TDM channel */
	struct ofp_tdm_port out_tport[0];

	struct ofp_wave_port in_wport[0];	/* Description of a Lambda channel */
	struct ofp_wave_port out_wport[0];
};
OFP_ASSERT(sizeof(struct ofp_connect_ocs) == 8);

/* Circuit flow wildcards
 * Zeroed bits are used to mark used ports
 * */
enum ofp_connect_wildcards {
	OFPCW_IN_PORT	= 1 << 0,
	OFPCW_OUT_PORT	= 1 << 1,
	OFPCW_IN_TPORT	= 1 << 2,
	OFPCW_OUT_TPORT = 1 << 3,
	OFPCW_IN_WPORT	= 1 << 4,
	OFPCW_OUT_WPORT = 1 << 5
};

/* Openflow message type.
 * Extended for circuit switch elements  */
enum ofp_type_ocs {
    /* Immutable messages. */
    OFPT_HELLO,               /* Symmetric message */
    OFPT_ERROR,               /* Symmetric message */
    OFPT_ECHO_REQUEST,        /* Symmetric message */
    OFPT_ECHO_REPLY,          /* Symmetric message */
    OFPT_EXPERIMENTER,        /* Symmetric message */

    /* Switch configuration messages. */
    OFPT_FEATURES_REQUEST,    /* Controller/switch message */
    OFPT_FEATURES_REPLY,      /* Controller/switch message */
    OFPT_GET_CONFIG_REQUEST,  /* Controller/switch message */
    OFPT_GET_CONFIG_REPLY,    /* Controller/switch message */
    OFPT_SET_CONFIG,          /* Controller/switch message */

    /* Asynchronous messages. */
    OFPT_PACKET_IN,           /* Async message */
    OFPT_FLOW_REMOVED,        /* Async message */
    OFPT_PORT_STATUS,         /* Async message */

    /* Controller command messages. */
    OFPT_PACKET_OUT,          /* Controller/switch message */
    OFPT_FLOW_MOD,            /* Controller/switch message */
    OFPT_GROUP_MOD,           /* Controller/switch message */
    OFPT_PORT_MOD,            /* Controller/switch message */
    OFPT_TABLE_MOD,           /* Controller/switch message */

    /* Statistics messages. */
    OFPT_STATS_REQUEST,       /* Controller/switch message */
    OFPT_STATS_REPLY,         /* Controller/switch message */

    /* Barrier messages. */
    OFPT_BARRIER_REQUEST,     /* Controller/switch message */
    OFPT_BARRIER_REPLY,       /* Controller/switch message */

    /* Queue Configuration messages. */
    OFPT_QUEUE_GET_CONFIG_REQUEST,  /* Controller/switch message */
    OFPT_QUEUE_GET_CONFIG_REPLY,     /* Controller/switch message */

    /* Messages for circuit switched ports. */
    OFPT_CFLOW_MOD_NOX  = 22,		/* Hack for NOX controller  */
    OFPT_CFLOW_MOD		= 0xff,		/* Controller/switch message */
    OFPT_CPORT_STATUS_NOX = 23,		/* Hack for NOX controller  */
    OFPT_CPORT_STATUS	= 0xfe		/* Async message */
};

/* Circuit flow setup, modification and teardown (controller -> datapath) */
struct ofp_cflow_mod {
	struct ofp_header header;		/* Openflow header */
	uint16_t command;				/* one of OFPFC_* commands */
	uint16_t hard_timeout;			/* max time to connection tear down,
									   if 0 then explicit tear-down required */
	uint8_t pad[4];					/* Align to 64 bits */
	struct ofp_connect_ocs connect; /* 8B followed by variable length arrays */
	struct ofp_action_header actions[0]; /* variable number of action */
};
OFP_ASSERT(sizeof(struct ofp_cflow_mod) == 24);

/* CFLOW_MOD message command enumeration */
enum ofp_flow_mod_command_ocs {
	OFPFC_OCS_ADD,				/* New flow */
	OFPFC_OCS_MODIFY,			/* Modify all matching flows */
	OFPFC_OCS_MODIFY_STRICT,	/* Modify entry strictly matching wildcards */
	OFPFC_OCS_DELETE,			/* Delete all matching flows */
	OFPFC_OCS_DELETE_STRICT, 	/* Strictly match wildcards and priority. */
	OFPFC_OCS_DROP = 0xffff		/* Terminate a circuit flow */
};

/* Action types for CFLOW_MOD command */
enum ofp10_action_type_ocs {
    OFPAT_OCS_OUTPUT,           		/* Output to switch port. */
    OFPAT_OCS_SET_VLAN_VID,     		/* Set the 802.1q VLAN id. */
    OFPAT_OCS_SET_VLAN_PCP,     		/* Set the 802.1q priority. */
    OFPAT_OCS_STRIP_VLAN,       		/* Strip the 802.1q header. */
    OFPAT_OCS_SET_DL_SRC,       		/* Ethernet source address. */
    OFPAT_OCS_SET_DL_DST,       		/* Ethernet destination address. */
    OFPAT_OCS_SET_NW_SRC,       		/* IP source address. */
    OFPAT_OCS_SET_NW_DST,       		/* IP destination address. */
    OFPAT_OCS_SET_NW_TOS,       		/* IP ToS (DSCP field, 6 bits). */
    OFPAT_OCS_SET_TP_SRC,       		/* TCP/UDP source port. */
    OFPAT_OCS_SET_TP_DST,       		/* TCP/UDP destination port. */
    OFPAT_OCS_ENQUEUE,          		/* Output to queue.  */
    /* Circuit switch extensions */
    OFPAT_OCS_CKT_OUTPUT = 0xfffd,	/* Output to circuit port */
    OFPAT_OCS_CKT_INPUT = 0xfffe,		/* Input from circuit port */

    OFPAT_OCS_VENDOR = 0xffff
};

/* adaptation type enum */
enum ofpc_adap_type {
	OFPCAT_NONE		= 1 << 0,	/* no adaptation, native transport */
	OFPCAT_POS		= 1 << 1,	/* Packet-over-SONET adaptation */
	OFPCAT_GFP		= 1 << 2,	/* Generic Framing Procedure adaptation */
	OFPCAT_10G_WAN	= 1 << 3	/* 10G Ethernet WAN PHY framing for SONET
								   OC-192 or SDH STM-64 */
};

/* Action structure for OFPAT_OCS_CKT_OUTPUT, which sends packets out of a
 * circuit port */
struct ofp_action_ckt_output {
	uint16_t type;			/* OFPAT_OCS_CKT_OUTPUT */
	uint16_t len;			/* Length is 24 */
	uint16_t adaptation;	/* Adaptation type - one of OFPCAT_* */
	uint16_t cport;			/* Real of virtual OFPP_* ports */

	/*Define the circuit port characteristics if necessary */
	uint64_t wavelength;	/* use of OFPCBL_* flags */
	uint32_t tsignal;		/* one of the OFPTSG_* flags. Not valid if used with
							   ofp_connect for TDM signals */
	uint16_t tstart; 		/* starting time slot. Not valid if used with
							   of_connect for TDM signals */
	uint16_t tlcas_enable;	/* enable/disable LCAS*/
};
OFP_ASSERT(sizeof(struct ofp_action_ckt_output) == 24);

/* Action structure for OFP10AT_OCS_CKT_INPUT, which extracts packet flows
 *  from a circuit port */
struct ofp_action_ckt_input {
	uint16_t type;			/* OFP10AT_OCS_CKT_INPUT */
	uint16_t len;			/* Length is 24 */
	uint16_t adaptation;	/* Adaptation type - one of OFPCAT_* */
	uint16_t cport;			/* Real of virtual OFPP_* ports */

	/*Define the circuit port characteristics if necessary */
	uint64_t wavelength;	/* use of OFPCBL_* flags */
	uint32_t tsignal;		/* one of the OFPTSG_* flags. Not valid if used with
							   ofp_connect for TDM signals */
	uint16_t tstart; 		/* starting time slot. Not valid if used with
							   of_connect for TDM signals */
	uint16_t tlcas_enable;	/* enable/disable LCAS*/
};
OFP_ASSERT(sizeof(struct ofp_action_ckt_input) == 24);

/*Values for 'type' in ofp_error_message. These values */
enum of_errro_type_ocs {
	OFPET_OCS_HELLO_FAILED,				/* Hello protocol failed. */
	OFPET_OCS_BAD_REQUEST,				/* Request was not understood. */
	OFPET_OCS_BAD_ACTION,				/* Error in action description. */
	OFPET_OCS_FLOW_MOD_FAILED,			/* Problem modifying flow entry. */
	OFPET_OCS_PORT_MOD_FAILED,			/* Port mod request failed. */
	OFPET_OCS_QUEUE_OP_FAILED,			/* Queue operation failed. */
	OFPET_OCS_CFLOW_MOD_FAILED = 0xffff /* Problem modifying circuit flow entry */
};

/* ofp_error_msg 'code' values for OFPET_OCS_CFLOW_MOD_FAILED. 'data' contains
 * at least the first 64 bytes of the failed request */
enum ofp_cflow_mod_failed_code {
	OFPCFMFC_VCG_DEF,	/* Creating or modification of VCG failed */
	OFPCFMFC_OVERLAP,	/* Attempted to add overlapping flow with currently
						   used time-slots */
	OFPCFMFC_MISMATCH	/* Mistmatched tsignals in ofp_connect struct */
};

/*Openflow message to report changes in circuit port status */
struct ofp_cport_status {
	struct ofp_header header;
	uint8_t reason;				/* One of OFPPR_* */
	uint8_t pad[7];				/* Align to 64 bits */
	struct ofp_phy_cport desc;	/* Circuit port description */
};
OFP_ASSERT(sizeof(struct ofp_cport_status) == 96);

/* What changed about the physical port */
enum ofp_port_reason_ocs {
	OFPPR_OCS_ADD,				/* The port was added */
	OFPPR_OCS_DELETE, 			/* The port was removed */
	OFPPR_OCS_MODIFY,			/* Some attribute of the port has changed */
	OFPPR_OCS_BW_MODIFY = 255,	/* Bandwidth usage has changed */
	OFPPR_OCS_BW_DOWN	= 254	/* Bandwidth time-slots have become un-usable */
};

/* Current state of the physical port. These are not configurable
 * from the controller */
enum ofp_port_state {
	OFPPS_LINK_DOWN		= 1 << 0, /* No physical link present. */

	/* The OFPPS_STP_* bits have no effect on switch operation. The
	* controller must adjust OFPPC_NO_RECV, OFPPC_NO_FWD, and
	* OFPPC_NO_PACKET_IN appropriately to fully implement an 802.1D spanning
	* tree. */
	OFPPS_STP_LISTEN 	= 0 << 8, /* Not learning or relaying frames. */
	OFPPS_STP_LEARN		= 1 << 8, /* Learning but not relaying frames. */
	OFPPS_STP_FORWARD 	= 2 << 8, /* Learning and relaying frames. */
	OFPPS_STP_BLOCK		= 3 << 8, /* Not part of spanning tree. */
	OFPPS_STP_MASK		= 3 << 8 /* Bit mask for OFPPS_STP_* values. */
};

enum ooe_vendor_id {
	ADVA_ROADM_FS	= 0x41445641	/* id for ADVA specific vendor messages */
};

enum ooe_type {
	OOE_SWITCH_CONSTRAINTS_REQUEST,		/* switching constraints message */
	OOE_SWITCH_CONSTRAINTS_REPLY,		/* switching constraints message */
	OOE_POWER_EQ_REQUEST,			/* power equalization */
	OOE_POWER_EQ_REPLY				/* power equalization */
};

/** Vendor messages structs - ADVA specific */
struct ooe_header {
    /** Usual OpenFlow header **/
    struct ofp_header   header;
    /** OOE_VENDOR_ID **/
    uint32_t            vendor;
    /** one of the 'ooe_type' for different vendor messages **/
    uint32_t            type;
    /** payload **/
    uint8_t             data[0];
};
OFP_ASSERT(sizeof(struct ooe_header) == 16);

/** power equalization request (note it is unidirectional!)**/
struct ooe_power_eq {
    struct ooe_header header;
    /** port number of the starting port **/
    uint16_t    in_port;
    /** port number of the terminating port **/
    uint16_t    out_port;
    /** frequency in GHz **/
    uint32_t    freq;
    /** result of power equalization, only valid for notification **/
    uint8_t     result;
    uint8_t     pad[3];
};
OFP_ASSERT(sizeof(struct ooe_power_eq) == 28);



#endif /* _OPENFLOW_OPENFLOW10_OPT_EXT_H */
