/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Map"
 * 	found in "Map.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_ST_Point_H_
#define	_ST_Point_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ST-Point */
typedef struct ST_Point {
	long	 s_axis;
	long	 t_axis;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ST_Point_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ST_Point;
extern asn_SEQUENCE_specifics_t asn_SPC_ST_Point_specs_1;
extern asn_TYPE_member_t asn_MBR_ST_Point_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _ST_Point_H_ */
#include <asn_internal.h>
