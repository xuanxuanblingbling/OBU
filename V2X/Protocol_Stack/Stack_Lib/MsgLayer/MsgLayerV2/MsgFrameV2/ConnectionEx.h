/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Map"
 * 	found in "Map.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_ConnectionEx_H_
#define	_ConnectionEx_H_


#include <asn_application.h>

/* Including external dependencies */
#include "NodeReferenceID.h"
#include "PhaseID.h"
#include "Maneuver.h"
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct SignalWaitingLane;
struct ConnectingLaneEx;

/* ConnectionEx */
typedef struct ConnectionEx {
	NodeReferenceID_t	 remoteIntersection;
	struct SignalWaitingLane	*swl	/* OPTIONAL */;
	struct connectingLane {
		A_SEQUENCE_OF(struct ConnectingLaneEx) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *connectingLane;
	PhaseID_t	*phaseId	/* OPTIONAL */;
	Maneuver_t	*turn_direction	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ConnectionEx_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ConnectionEx;
extern asn_SEQUENCE_specifics_t asn_SPC_ConnectionEx_specs_1;
extern asn_TYPE_member_t asn_MBR_ConnectionEx_1[5];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "SignalWaitingLane.h"
#include "ConnectingLaneEx.h"

#endif	/* _ConnectionEx_H_ */
#include <asn_internal.h>
