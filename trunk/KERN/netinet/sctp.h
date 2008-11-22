/*-
 * Copyright (c) 2001-2008, by Cisco Systems, Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 * a) Redistributions of source code must retain the above copyright notice, 
 *   this list of conditions and the following disclaimer.
 *
 * b) Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in 
 *   the documentation and/or other materials provided with the distribution.
 *
 * c) Neither the name of Cisco Systems, Inc. nor the names of its 
 *    contributors may be used to endorse or promote products derived 
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
/* $KAME: sctp.h,v 1.18 2005/03/06 16:04:16 itojun Exp $	 */

#ifdef __FreeBSD__
#include <sys/cdefs.h>
__FBSDID("$FreeBSD: head/sys/netinet/sctp.h 181054 2008-07-31 11:08:30Z rrs $");

#endif
#ifndef _NETINET_SCTP_H_
#define _NETINET_SCTP_H_

#ifdef __APPLE__
#include <stdint.h>
#endif
#include <sys/types.h>

#if defined(__Windows__)
#include <packon.h>
#endif

#define SCTP_PACKED __attribute__((packed))

/*
 * SCTP protocol - RFC2960.
 */
struct sctphdr {
	uint16_t src_port;	/* source port */
	uint16_t dest_port;	/* destination port */
	uint32_t v_tag;		/* verification tag of packet */
	uint32_t checksum;	/* Adler32 C-Sum */
	/* chunks follow... */
} SCTP_PACKED ;

/*
 * SCTP Chunks
 */
struct sctp_chunkhdr {
	uint8_t chunk_type;	/* chunk type */
	uint8_t chunk_flags;	/* chunk flags */
	uint16_t chunk_length;	/* chunk length */
	/* optional params follow */
} SCTP_PACKED;

/*
 * SCTP chunk parameters
 */
struct sctp_paramhdr {
	uint16_t param_type;	/* parameter type */
	uint16_t param_length;	/* parameter length */
} SCTP_PACKED;

/*
 * user socket options: socket API defined
 */
/*
 * read-write options
 */
#define SCTP_RTOINFO			0x00000001
#define SCTP_ASSOCINFO			0x00000002
#define SCTP_INITMSG			0x00000003
#define SCTP_NODELAY			0x00000004
#define SCTP_AUTOCLOSE			0x00000005
#define SCTP_SET_PEER_PRIMARY_ADDR	0x00000006
#define SCTP_PRIMARY_ADDR		0x00000007
#define SCTP_ADAPTATION_LAYER		0x00000008
/* same as above */
#define SCTP_ADAPTION_LAYER		0x00000008
#define SCTP_DISABLE_FRAGMENTS		0x00000009
#define SCTP_PEER_ADDR_PARAMS 		0x0000000a
#define SCTP_DEFAULT_SEND_PARAM		0x0000000b
/* ancillary data/notification interest options */
#define SCTP_EVENTS			0x0000000c
/* Without this applied we will give V4 and V6 addresses on a V6 socket */
#define SCTP_I_WANT_MAPPED_V4_ADDR	0x0000000d
#define SCTP_MAXSEG 			0x0000000e
#define SCTP_DELAYED_SACK               0x0000000f
#define SCTP_FRAGMENT_INTERLEAVE        0x00000010
#define SCTP_PARTIAL_DELIVERY_POINT     0x00000011
/* authentication support */
#define SCTP_AUTH_CHUNK 		0x00000012
#define SCTP_AUTH_KEY 			0x00000013
#define SCTP_HMAC_IDENT 		0x00000014
#define SCTP_AUTH_ACTIVE_KEY 		0x00000015
#define SCTP_AUTH_DELETE_KEY 		0x00000016
#define SCTP_USE_EXT_RCVINFO		0x00000017
#define SCTP_AUTO_ASCONF		0x00000018 /* rw */
#define SCTP_MAXBURST			0x00000019 /* rw */
#define SCTP_MAX_BURST			0x00000019 /* rw */
/* assoc level context */
#define SCTP_CONTEXT                    0x0000001a /* rw */
/* explict EOR signalling */
#define SCTP_EXPLICIT_EOR               0x0000001b
#define SCTP_REUSE_PORT                 0x0000001c /* rw */
#define SCTP_AUTH_DEACTIVATE_KEY	0x0000001d

/*
 * read-only options
 */
#define SCTP_STATUS			0x00000100
#define SCTP_GET_PEER_ADDR_INFO		0x00000101
/* authentication support */
#define SCTP_PEER_AUTH_CHUNKS 		0x00000102
#define SCTP_LOCAL_AUTH_CHUNKS 		0x00000103
#define SCTP_GET_ASSOC_NUMBER           0x00000104 /* ro */
#define SCTP_GET_ASSOC_ID_LIST          0x00000105 /* ro */

/*
 * user socket options: BSD implementation specific
 */
/*
 * Blocking I/O is enabled on any TCP type socket by default. For the UDP
 * model if this is turned on then the socket buffer is shared for send
 * resources amongst all associations.  The default for the UDP model is that
 * is SS_NBIO is set.  Which means all associations have a seperate send
 * limit BUT they will NOT ever BLOCK instead you will get an error back
 * EAGAIN if you try to send to much. If you want the blocking symantics you
 * set this option at the cost of sharing one socket send buffer size amongst
 * all associations. Peeled off sockets turn this option off and block. But
 * since both TCP and peeled off sockets have only one assoc per socket this
 * is fine. It probably does NOT make sense to set this on SS_NBIO on a TCP
 * model OR peeled off UDP model, but we do allow you to do so. You just use
 * the normal syscall to toggle SS_NBIO the way you want.
 *
 * Blocking I/O is controled by the SS_NBIO flag on the socket state so_state
 * field.
 */

/* these should probably go into sockets API */
#define SCTP_RESET_STREAMS		0x00001004 /* wo */


/* here on down are more implementation specific */
#define SCTP_SET_DEBUG_LEVEL		0x00001005
#define SCTP_CLR_STAT_LOG               0x00001007
/* CMT ON/OFF socket option */
#define SCTP_CMT_ON_OFF                 0x00001200
#define SCTP_CMT_USE_DAC                0x00001201
/* EY - NR_SACK on/off socket option */
#define SCTP_NR_SACK_ON_OFF                 0x00001300
/* JRS - Pluggable Congestion Control Socket option */
#define SCTP_PLUGGABLE_CC				0x00001202

/* read only */
#define SCTP_GET_SNDBUF_USE		0x00001101
#define SCTP_GET_STAT_LOG		0x00001103
#define SCTP_PCB_STATUS			0x00001104
#define SCTP_GET_NONCE_VALUES           0x00001105


/* Special hook for dynamically setting primary for all assoc's,
 * this is a write only option that requires root privledge.
 */
#define SCTP_SET_DYNAMIC_PRIMARY        0x00002001

/* VRF (virtual router feature) and multi-VRF support 
 * options. VRF's provide splits within a router
 * that give the views of multiple routers. A
 * standard host, without VRF support, is just
 * a single VRF. If VRF's are supported then 
 * the transport must be VRF aware. This means
 * that every socket call coming in must be directed
 * within the endpoint to one of the VRF's it belongs
 * to. The endpoint, before binding, may select
 * the "default" VRF it is in by using a set socket 
 * option with SCTP_VRF_ID. This will also
 * get propegated to the default VRF. Once the
 * endpoint binds an address then it CANNOT add
 * additional VRF's to become a Multi-VRF endpoint.
 *
 * Before BINDING additional VRF's can be added with
 * the SCTP_ADD_VRF_ID call or deleted with
 * SCTP_DEL_VRF_ID.
 *
 * Associations are ALWAYS contained inside a single
 * VRF. They cannot reside in two (or more) VRF's. Incoming
 * packets, assuming the router is VRF aware, can always
 * tell us what VRF they arrived on. A host not supporting
 * any VRF's will find that the packets always arrived on the
 * single VRF that the host has. 
 *
 */

#define SCTP_VRF_ID			0x00003001
#define SCTP_ADD_VRF_ID			0x00003002
#define SCTP_GET_VRF_IDS		0x00003003
#define SCTP_GET_ASOC_VRF               0x00003004
#define SCTP_DEL_VRF_ID                 0x00003005

/* 
 * If you enable packet logging you can get
 * a poor mans ethereal output in binary
 * form. Note this is a compile option to
 * the kernel,  SCTP_PACKET_LOGGING, and
 * without it in your kernel you
 * will get a EOPNOTSUPP
 */
#define SCTP_GET_PACKET_LOG             0x00004001

/*
 * hidden implementation specific options these are NOT user visible (should
 * move out of sctp.h)
 */
/* sctp_bindx() flags as hidden socket options */
#define SCTP_BINDX_ADD_ADDR		0x00008001
#define SCTP_BINDX_REM_ADDR		0x00008002
/* Hidden socket option that gets the addresses */
#define SCTP_GET_PEER_ADDRESSES		0x00008003
#define SCTP_GET_LOCAL_ADDRESSES	0x00008004
/* return the total count in bytes needed to hold all local addresses bound */
#define SCTP_GET_LOCAL_ADDR_SIZE	0x00008005
/* Return the total count in bytes needed to hold the remote address */
#define SCTP_GET_REMOTE_ADDR_SIZE	0x00008006
/* hidden option for connectx */
#define SCTP_CONNECT_X			0x00008007
/* hidden option for connectx_delayed, part of sendx */
#define SCTP_CONNECT_X_DELAYED		0x00008008
#define SCTP_CONNECT_X_COMPLETE         0x00008009
/* hidden socket option based sctp_peeloff */
#define SCTP_PEELOFF                    0x0000800a
/* the real worker for sctp_getaddrlen() */
#define SCTP_GET_ADDR_LEN               0x0000800b
/* temporary workaround for Apple listen() issue, no args used */
#define SCTP_LISTEN_FIX			0x0000800c
/* Debug things that need to be purged */
#define SCTP_SET_INITIAL_DBG_SEQ	0x00009f00

/* JRS - Supported congestion control modules for pluggable
 * congestion control
 */
/* Standard TCP Congestion Control */
#define SCTP_CC_RFC2581		0x00000000
/* High Speed TCP Congestion Control (Floyd) */
#define SCTP_CC_HSTCP		0x00000001
/* HTCP Congestion Control */
#define SCTP_CC_HTCP		0x00000002


/* fragment interleave constants 
 * setting must be one of these or
 * EINVAL returned.
 */
#define SCTP_FRAG_LEVEL_0    0x00000000
#define SCTP_FRAG_LEVEL_1    0x00000001
#define SCTP_FRAG_LEVEL_2    0x00000002

/*
 * user state values
 */
#define SCTP_CLOSED			0x0000
#define SCTP_BOUND			0x1000
#define SCTP_LISTEN			0x2000
#define SCTP_COOKIE_WAIT		0x0002
#define SCTP_COOKIE_ECHOED		0x0004
#define SCTP_ESTABLISHED		0x0008
#define SCTP_SHUTDOWN_SENT		0x0010
#define SCTP_SHUTDOWN_RECEIVED		0x0020
#define SCTP_SHUTDOWN_ACK_SENT		0x0040
#define SCTP_SHUTDOWN_PENDING		0x0080

/*
 * SCTP operational error codes (user visible)
 */
#define SCTP_CAUSE_NO_ERROR		0x0000
#define SCTP_CAUSE_INVALID_STREAM	0x0001
#define SCTP_CAUSE_MISSING_PARAM	0x0002
#define SCTP_CAUSE_STALE_COOKIE		0x0003
#define SCTP_CAUSE_OUT_OF_RESC		0x0004
#define SCTP_CAUSE_UNRESOLVABLE_ADDR	0x0005
#define SCTP_CAUSE_UNRECOG_CHUNK	0x0006
#define SCTP_CAUSE_INVALID_PARAM	0x0007
#define SCTP_CAUSE_UNRECOG_PARAM	0x0008
#define SCTP_CAUSE_NO_USER_DATA		0x0009
#define SCTP_CAUSE_COOKIE_IN_SHUTDOWN	0x000a
#define SCTP_CAUSE_RESTART_W_NEWADDR	0x000b
#define SCTP_CAUSE_USER_INITIATED_ABT	0x000c
#define SCTP_CAUSE_PROTOCOL_VIOLATION	0x000d

/* Error causes from RFC5061 */
#define SCTP_CAUSE_DELETING_LAST_ADDR	0x00a0
#define SCTP_CAUSE_RESOURCE_SHORTAGE	0x00a1
#define SCTP_CAUSE_DELETING_SRC_ADDR	0x00a2
#define SCTP_CAUSE_ILLEGAL_ASCONF_ACK	0x00a3
#define SCTP_CAUSE_REQUEST_REFUSED	0x00a4

/* Error causes from nat-draft */
#define SCTP_CAUSE_NAT_COLLIDING_STATE  0x00b0
#define SCTP_CAUSE_NAT_MISSING_STATE    0x00b1

/* Error causes from RFC4895 */
#define SCTP_CAUSE_UNSUPPORTED_HMACID	0x0105

/*
 * error cause parameters (user visisble)
 */
struct sctp_error_cause {
	uint16_t code;
	uint16_t length;
	/* optional cause-specific info may follow */
}  SCTP_PACKED;

struct sctp_error_invalid_stream {
	struct sctp_error_cause cause;	/* code=SCTP_ERROR_INVALID_STREAM */
	uint16_t stream_id;	/* stream id of the DATA in error */
	uint16_t reserved;
} SCTP_PACKED;

struct sctp_error_missing_param {
	struct sctp_error_cause cause;	/* code=SCTP_ERROR_MISSING_PARAM */
	uint32_t num_missing_params;	/* number of missing parameters */
	/* uint16_t param_type's follow */
} SCTP_PACKED;

struct sctp_error_stale_cookie {
	struct sctp_error_cause cause;	/* code=SCTP_ERROR_STALE_COOKIE */
	uint32_t stale_time;	/* time in usec of staleness */
} SCTP_PACKED;

struct sctp_error_out_of_resource {
	struct sctp_error_cause cause;	/* code=SCTP_ERROR_OUT_OF_RESOURCES */
} SCTP_PACKED;

struct sctp_error_unresolv_addr {
	struct sctp_error_cause cause;	/* code=SCTP_ERROR_UNRESOLVABLE_ADDR */

} SCTP_PACKED;

struct sctp_error_unrecognized_chunk {
	struct sctp_error_cause cause;	/* code=SCTP_ERROR_UNRECOG_CHUNK */
	struct sctp_chunkhdr ch;/* header from chunk in error */
} SCTP_PACKED;

/*
 * Main SCTP chunk types we place these here so natd and f/w's in user land
 * can find them.
 */
/************0x00 series ***********/
#define SCTP_DATA		0x00
#define SCTP_INITIATION		0x01
#define SCTP_INITIATION_ACK	0x02
#define SCTP_SELECTIVE_ACK	0x03
#define SCTP_HEARTBEAT_REQUEST	0x04
#define SCTP_HEARTBEAT_ACK	0x05
#define SCTP_ABORT_ASSOCIATION	0x06
#define SCTP_SHUTDOWN		0x07
#define SCTP_SHUTDOWN_ACK	0x08
#define SCTP_OPERATION_ERROR	0x09
#define SCTP_COOKIE_ECHO	0x0a
#define SCTP_COOKIE_ACK		0x0b
#define SCTP_ECN_ECHO		0x0c
#define SCTP_ECN_CWR		0x0d
#define SCTP_SHUTDOWN_COMPLETE	0x0e
/* RFC4895 */
#define SCTP_AUTHENTICATION     0x0f
/* EY nr_sack chunk id*/
#define SCTP_NR_SELECTIVE_ACK 0x10
/************0x40 series ***********/
/************0x80 series ***********/
/* RFC5061 */
#define	SCTP_ASCONF_ACK		0x80
/* draft-ietf-stewart-pktdrpsctp */
#define SCTP_PACKET_DROPPED	0x81
/* draft-ietf-stewart-strreset-xxx */
#define SCTP_STREAM_RESET       0x82

/* RFC4820                         */
#define SCTP_PAD_CHUNK          0x84
/************0xc0 series ***********/
/* RFC3758 */
#define SCTP_FORWARD_CUM_TSN	0xc0
/* RFC5061 */
#define SCTP_ASCONF		0xc1


/* ABORT and SHUTDOWN COMPLETE FLAG */
#define SCTP_HAD_NO_TCB		0x01

/* Packet dropped flags */
#define SCTP_FROM_MIDDLE_BOX	SCTP_HAD_NO_TCB
#define SCTP_BADCRC		0x02
#define SCTP_PACKET_TRUNCATED	0x04

#define SCTP_SAT_NETWORK_MIN	400	/* min ms for RTT to set satellite
					 * time */
#define SCTP_SAT_NETWORK_BURST_INCR  2	/* how many times to multiply maxburst
					 * in sat */

/* Data Chuck Specific Flags */
#define SCTP_DATA_FRAG_MASK        0x03
#define SCTP_DATA_MIDDLE_FRAG      0x00
#define SCTP_DATA_LAST_FRAG        0x01
#define SCTP_DATA_FIRST_FRAG       0x02
#define SCTP_DATA_NOT_FRAG         0x03
#define SCTP_DATA_UNORDERED        0x04
#define SCTP_DATA_SACK_IMMEDIATELY 0x08
/* ECN Nonce: SACK Chunk Specific Flags */
#define SCTP_SACK_NONCE_SUM        0x01

/* EY nr_sack all bit - All bit is the 2nd LSB of nr_sack chunk flags*/
/* if All bit is set in an nr-sack chunk, then all nr gap acks gap acks*/
#define SCTP_NR_SACK_ALL_BIT	0x02
/* CMT DAC algorithm SACK flag */
#define SCTP_SACK_CMT_DAC          0x80

/*
 * PCB flags (in sctp_flags bitmask).
 * Note the features and flags are meant
 * for use by netstat.
 */
#define SCTP_PCB_FLAGS_UDPTYPE		0x00000001
#define SCTP_PCB_FLAGS_TCPTYPE		0x00000002
#define SCTP_PCB_FLAGS_BOUNDALL		0x00000004
#define SCTP_PCB_FLAGS_ACCEPTING	0x00000008
#define SCTP_PCB_FLAGS_UNBOUND		0x00000010
#define SCTP_PCB_FLAGS_CLOSE_IP         0x00040000
#define SCTP_PCB_FLAGS_WAS_CONNECTED    0x00080000
#define SCTP_PCB_FLAGS_WAS_ABORTED      0x00100000
/* TCP model support */

#define SCTP_PCB_FLAGS_CONNECTED	0x00200000
#define SCTP_PCB_FLAGS_IN_TCPPOOL	0x00400000
#define SCTP_PCB_FLAGS_DONT_WAKE	0x00800000
#define SCTP_PCB_FLAGS_WAKEOUTPUT	0x01000000
#define SCTP_PCB_FLAGS_WAKEINPUT	0x02000000
#define SCTP_PCB_FLAGS_BOUND_V6		0x04000000
#define SCTP_PCB_FLAGS_BLOCKING_IO	0x08000000
#define SCTP_PCB_FLAGS_SOCKET_GONE	0x10000000
#define SCTP_PCB_FLAGS_SOCKET_ALLGONE	0x20000000
/* flags to copy to new PCB */
#define SCTP_PCB_COPY_FLAGS		(SCTP_PCB_FLAGS_BOUNDALL|\
					 SCTP_PCB_FLAGS_WAKEINPUT|\
					 SCTP_PCB_FLAGS_BOUND_V6)


/*
 * PCB Features (in sctp_features bitmask)
 */
#define SCTP_PCB_FLAGS_EXT_RCVINFO      0x00000002
#define SCTP_PCB_FLAGS_DONOT_HEARTBEAT  0x00000004
#define SCTP_PCB_FLAGS_FRAG_INTERLEAVE  0x00000008
#define SCTP_PCB_FLAGS_INTERLEAVE_STRMS	0x00000010
#define SCTP_PCB_FLAGS_DO_ASCONF	0x00000020
#define SCTP_PCB_FLAGS_AUTO_ASCONF	0x00000040
#define SCTP_PCB_FLAGS_ZERO_COPY_ACTIVE 0x00000080
/* socket options */
#define SCTP_PCB_FLAGS_NODELAY		0x00000100
#define SCTP_PCB_FLAGS_AUTOCLOSE	0x00000200
#define SCTP_PCB_FLAGS_RECVDATAIOEVNT	0x00000400
#define SCTP_PCB_FLAGS_RECVASSOCEVNT	0x00000800
#define SCTP_PCB_FLAGS_RECVPADDREVNT	0x00001000
#define SCTP_PCB_FLAGS_RECVPEERERR	0x00002000
#define SCTP_PCB_FLAGS_RECVSENDFAILEVNT	0x00004000
#define SCTP_PCB_FLAGS_RECVSHUTDOWNEVNT	0x00008000
#define SCTP_PCB_FLAGS_ADAPTATIONEVNT	0x00010000
#define SCTP_PCB_FLAGS_PDAPIEVNT	0x00020000
#define SCTP_PCB_FLAGS_AUTHEVNT		0x00040000
#define SCTP_PCB_FLAGS_STREAM_RESETEVNT 0x00080000
#define SCTP_PCB_FLAGS_NO_FRAGMENT	0x00100000
#define SCTP_PCB_FLAGS_EXPLICIT_EOR     0x00400000
#define SCTP_PCB_FLAGS_NEEDS_MAPPED_V4	0x00800000
#define SCTP_PCB_FLAGS_MULTIPLE_ASCONFS	0x01000000
#define SCTP_PCB_FLAGS_PORTREUSE        0x02000000
#define SCTP_PCB_FLAGS_DRYEVNT          0x04000000
/*-
 * mobility_features parameters (by micchie).Note
 * these features are applied against the
 * sctp_mobility_features flags.. not the sctp_features
 * flags.
 */
#define SCTP_MOBILITY_BASE		0x00000001
#define SCTP_MOBILITY_FASTHANDOFF	0x00000002
#define SCTP_MOBILITY_PRIM_DELETED	0x00000004


#define SCTP_SMALLEST_PMTU 512	 /* smallest pmtu allowed when disabling PMTU discovery */

#include <netinet/sctp_uio.h>

/* This dictates the size of the packet
 * collection buffer. This only applies
 * if SCTP_PACKET_LOGGING is enabled in
 * your config.
 */
#define SCTP_PACKET_LOG_SIZE 65536

/* Maximum delays and such a user can set for options that
 * take ms.
 */
#define SCTP_MAX_SACK_DELAY 500 /* per RFC4960 */
#define SCTP_MAX_HB_INTERVAL 14400000 /* 4 hours in ms */
#define SCTP_MAX_COOKIE_LIFE  3600000 /* 1 hour in ms */


/* Types of logging/KTR tracing  that can be enabled via the 
 * sysctl net.inet.sctp.sctp_logging. You must also enable
 * SUBSYS tracing.
 * Note that you must have the SCTP option in the kernel
 * to enable these as well.
 */
#define SCTP_BLK_LOGGING_ENABLE				0x00000001
#define SCTP_CWND_MONITOR_ENABLE			0x00000002
#define SCTP_CWND_LOGGING_ENABLE			0x00000004
#define SCTP_EARLYFR_LOGGING_ENABLE			0x00000010
#define SCTP_FLIGHT_LOGGING_ENABLE			0x00000020
#define SCTP_FR_LOGGING_ENABLE				0x00000040
#define SCTP_LOCK_LOGGING_ENABLE			0x00000080
#define SCTP_MAP_LOGGING_ENABLE				0x00000100
#define SCTP_MBCNT_LOGGING_ENABLE			0x00000200
#define SCTP_MBUF_LOGGING_ENABLE			0x00000400
#define SCTP_NAGLE_LOGGING_ENABLE			0x00000800
#define SCTP_RECV_RWND_LOGGING_ENABLE		0x00001000
#define SCTP_RTTVAR_LOGGING_ENABLE			0x00002000
#define SCTP_SACK_LOGGING_ENABLE			0x00004000
#define SCTP_SACK_RWND_LOGGING_ENABLE		0x00008000
#define SCTP_SB_LOGGING_ENABLE				0x00010000
#define SCTP_STR_LOGGING_ENABLE				0x00020000
#define SCTP_WAKE_LOGGING_ENABLE			0x00040000
#define SCTP_LOG_MAXBURST_ENABLE			0x00080000
#define SCTP_LOG_RWND_ENABLE    			0x00100000
#define SCTP_LOG_SACK_ARRIVALS_ENABLE       0x00200000
#define SCTP_LTRACE_CHUNK_ENABLE            0x00400000
#define SCTP_LTRACE_ERROR_ENABLE            0x00800000
#define SCTP_LAST_PACKET_TRACING            0x01000000
#define SCTP_THRESHOLD_LOGGING              0x02000000
#define SCTP_LOG_AT_SEND_2_SCTP             0x04000000
#define SCTP_LOG_AT_SEND_2_OUTQ             0x08000000


#if defined(__Windows__)
#include <packoff.h>
#endif

#undef SCTP_PACKED

#endif				/* !_NETINET_SCTP_H_ */
