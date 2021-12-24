/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "BASE"
 *     found in "BASE.asn"
 *     `asn1c -gen-PER`
 */

#ifndef    _RectangularRegion_H_
#define    _RectangularRegion_H_


#include <asn_application.h>

/* Including external dependencies */
#include "TwoDLocation.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* RectangularRegion */
typedef struct RectangularRegion {
    TwoDLocation_t     northWest;
    TwoDLocation_t     southEast;

    /* Context for parsing across buffer boundaries */
    asn_struct_ctx_t _asn_ctx;
} RectangularRegion_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RectangularRegion;
extern asn_SEQUENCE_specifics_t asn_SPC_RectangularRegion_specs_1;
extern asn_TYPE_member_t asn_MBR_RectangularRegion_1[2];

#ifdef __cplusplus
}
#endif

#endif    /* _RectangularRegion_H_ */
#include <asn_internal.h>
