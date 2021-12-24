/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "BASE"
 *     found in "BASE.asn"
 *     `asn1c -gen-PER`
 */

#ifndef    _ItsAidSsp_H_
#define    _ItsAidSsp_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ItsAid.h"
#include <OCTET_STRING.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ItsAidSsp */
typedef struct ItsAidSsp {
    ItsAid_t     itsAid;
    OCTET_STRING_t     serviceSpecificPermissions;

    /* Context for parsing across buffer boundaries */
    asn_struct_ctx_t _asn_ctx;
} ItsAidSsp_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ItsAidSsp;
extern asn_SEQUENCE_specifics_t asn_SPC_ItsAidSsp_specs_1;
extern asn_TYPE_member_t asn_MBR_ItsAidSsp_1[2];

#ifdef __cplusplus
}
#endif

#endif    /* _ItsAidSsp_H_ */
#include <asn_internal.h>
