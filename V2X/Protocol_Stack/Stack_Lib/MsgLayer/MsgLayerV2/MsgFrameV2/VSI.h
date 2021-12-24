/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VPM"
 * 	found in "VPM.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_VSI_H_
#define	_VSI_H_


#include <asn_application.h>

/* Including external dependencies */
#include "DDateTime.h"
#include <OCTET_STRING.h>
#include "RandStr8.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct OBUInfo;
struct VPApplicationList;

/* VSI */
typedef struct VSI {
	DDateTime_t	 time;
	OCTET_STRING_t	 obuId;
	OCTET_STRING_t	*targetId	/* OPTIONAL */;
	struct OBUInfo	*obuInfo	/* OPTIONAL */;
	struct VPApplicationList	*vpapplicationList	/* OPTIONAL */;
	RandStr8_t	*rndOBU	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} VSI_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_VSI;
extern asn_SEQUENCE_specifics_t asn_SPC_VSI_specs_1;
extern asn_TYPE_member_t asn_MBR_VSI_1[6];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "OBUInfo.h"
#include "VPApplicationList.h"

#endif	/* _VSI_H_ */
#include <asn_internal.h>