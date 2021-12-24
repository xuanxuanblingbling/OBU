/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Platooning"
 * 	found in "Platooning.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_MemberManagement_H_
#define	_MemberManagement_H_


#include <asn_application.h>

/* Including external dependencies */
#include "MemberList.h"
#include <NativeInteger.h>
#include <BOOLEAN.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct MemberList;

/* MemberManagement */
typedef struct MemberManagement {
	MemberList_t	 memberList;
	struct MemberList	*joiningList	/* OPTIONAL */;
	struct MemberList	*leavingList	/* OPTIONAL */;
	long	 capacity;
	BOOLEAN_t	 openToJoin;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MemberManagement_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MemberManagement;
extern asn_SEQUENCE_specifics_t asn_SPC_MemberManagement_specs_1;
extern asn_TYPE_member_t asn_MBR_MemberManagement_1[5];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "MemberList.h"

#endif	/* _MemberManagement_H_ */
#include <asn_internal.h>
