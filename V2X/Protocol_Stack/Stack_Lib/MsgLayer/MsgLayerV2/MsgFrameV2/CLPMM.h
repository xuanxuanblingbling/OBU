/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Platooning"
 * 	found in "Platooning.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_CLPMM_H_
#define	_CLPMM_H_


#include <asn_application.h>

/* Including external dependencies */
#include "MsgCount.h"
#include <OCTET_STRING.h>
#include "DSecond.h"
#include "RoleInPlatooning.h"
#include "StatusInPlatooning.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct MemberManagement;

/* CLPMM */
typedef struct CLPMM {
	MsgCount_t	 msgCnt;
	OCTET_STRING_t	 id;
	DSecond_t	 secMark;
	OCTET_STRING_t	 pid;
	RoleInPlatooning_t	 role;
	StatusInPlatooning_t	 status;
	struct MemberManagement	*leadingExt	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CLPMM_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CLPMM;
extern asn_SEQUENCE_specifics_t asn_SPC_CLPMM_specs_1;
extern asn_TYPE_member_t asn_MBR_CLPMM_1[7];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "MemberManagement.h"

#endif	/* _CLPMM_H_ */
#include <asn_internal.h>
