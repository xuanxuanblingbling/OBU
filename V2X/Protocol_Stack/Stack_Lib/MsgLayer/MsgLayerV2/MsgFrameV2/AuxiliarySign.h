/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "RSI"
 * 	found in "RSI.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_AuxiliarySign_H_
#define	_AuxiliarySign_H_


#include <asn_application.h>

/* Including external dependencies */
#include "AuxiliarySignVehicleType.h"
#include "AuxiliarySignDirection.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* AuxiliarySign */
typedef struct AuxiliarySign {
	AuxiliarySignVehicleType_t	*signWithVehicleType	/* OPTIONAL */;
	AuxiliarySignDirection_t	*signDirection	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} AuxiliarySign_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_AuxiliarySign;
extern asn_SEQUENCE_specifics_t asn_SPC_AuxiliarySign_specs_1;
extern asn_TYPE_member_t asn_MBR_AuxiliarySign_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _AuxiliarySign_H_ */
#include <asn_internal.h>
