/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VIR"
 * 	found in "VIR.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_Req_SignalPriority_H_
#define	_Req_SignalPriority_H_


#include <asn_application.h>

/* Including external dependencies */
#include "NodeReferenceID.h"
#include "MovementEx.h"
#include "TimeOffset.h"
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Req-SignalPriority */
typedef struct Req_SignalPriority {
	NodeReferenceID_t	 intersectionId;
	MovementEx_t	 requiredMov;
	TimeOffset_t	*estimatedArrivalTime	/* OPTIONAL */;
	long	*distance2Intersection	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Req_SignalPriority_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Req_SignalPriority;
extern asn_SEQUENCE_specifics_t asn_SPC_Req_SignalPriority_specs_1;
extern asn_TYPE_member_t asn_MBR_Req_SignalPriority_1[4];

#ifdef __cplusplus
}
#endif

#endif	/* _Req_SignalPriority_H_ */
#include <asn_internal.h>