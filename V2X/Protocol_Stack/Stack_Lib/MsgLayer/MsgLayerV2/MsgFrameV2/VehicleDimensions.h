/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VPM"
 * 	found in "VPM.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_VehicleDimensions_H_
#define	_VehicleDimensions_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* VehicleDimensions */
typedef struct VehicleDimensions {
	long	 vehicleLength;
	long	 vehicleWidth;
	long	 vehicleHeigth;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} VehicleDimensions_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_VehicleDimensions;
extern asn_SEQUENCE_specifics_t asn_SPC_VehicleDimensions_specs_1;
extern asn_TYPE_member_t asn_MBR_VehicleDimensions_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _VehicleDimensions_H_ */
#include <asn_internal.h>
