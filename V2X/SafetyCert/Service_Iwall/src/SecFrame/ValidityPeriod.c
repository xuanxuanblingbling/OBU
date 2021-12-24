/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "CER"
 *     found in "CER.asn"
 *     `asn1c -gen-PER`
 */

#include "ValidityPeriod.h"

static asn_oer_constraints_t asn_OER_type_ValidityPeriod_constr_1 CC_NOTUSED = {
    { 0, 0 },
    -1};
asn_per_constraints_t asn_PER_type_ValidityPeriod_constr_1 CC_NOTUSED = {
    { APC_CONSTRAINED,     1,  1,  0,  1 }    /* (0..1) */,
    { APC_UNCONSTRAINED,    -1, -1,  0,  0 },
    0, 0    /* No PER value map */
};
asn_TYPE_member_t asn_MBR_ValidityPeriod_1[] = {
    { ATF_NOFLAGS, 0, offsetof(struct ValidityPeriod, choice.timeEnd),
        (ASN_TAG_CLASS_CONTEXT | (0 << 2)),
        -1,    /* IMPLICIT tag at current level */
        &asn_DEF_Time32,
        0,
        { 0, 0, 0 },
        0, 0, /* No default value */
        "timeEnd"
        },
    { ATF_NOFLAGS, 0, offsetof(struct ValidityPeriod, choice.timeStartAndEnd),
        (ASN_TAG_CLASS_CONTEXT | (1 << 2)),
        -1,    /* IMPLICIT tag at current level */
        &asn_DEF_TimeStartAndEnd,
        0,
        { 0, 0, 0 },
        0, 0, /* No default value */
        "timeStartAndEnd"
        },
};
static const asn_TYPE_tag2member_t asn_MAP_ValidityPeriod_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* timeEnd */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* timeStartAndEnd */
};
asn_CHOICE_specifics_t asn_SPC_ValidityPeriod_specs_1 = {
    sizeof(struct ValidityPeriod),
    offsetof(struct ValidityPeriod, _asn_ctx),
    offsetof(struct ValidityPeriod, present),
    sizeof(((struct ValidityPeriod *)0)->present),
    asn_MAP_ValidityPeriod_tag2el_1,
    2,    /* Count of tags in the map */
    0, 0,
    -1    /* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_ValidityPeriod = {
    "ValidityPeriod",
    "ValidityPeriod",
    &asn_OP_CHOICE,
    0,    /* No effective tags (pointer) */
    0,    /* No effective tags (count) */
    0,    /* No tags (pointer) */
    0,    /* No tags (count) */
    { &asn_OER_type_ValidityPeriod_constr_1, &asn_PER_type_ValidityPeriod_constr_1, CHOICE_constraint },
    asn_MBR_ValidityPeriod_1,
    2,    /* Elements count */
    &asn_SPC_ValidityPeriod_specs_1    /* Additional specs */
};

