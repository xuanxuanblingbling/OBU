/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SensorSharing"
 * 	found in "SensorSharing.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_ObjectSize_H_
#define	_ObjectSize_H_


#include <asn_application.h>

/* Including external dependencies */
#include "SizeValue.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ObjectSize */
typedef struct ObjectSize {
	SizeValue_t	 width;
	SizeValue_t	 length;
	SizeValue_t	*height	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ObjectSize_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ObjectSize;
extern asn_SEQUENCE_specifics_t asn_SPC_ObjectSize_specs_1;
extern asn_TYPE_member_t asn_MBR_ObjectSize_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _ObjectSize_H_ */
#include <asn_internal.h>
