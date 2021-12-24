/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SecMsg"
 *     found in "SecMsg.asn"
 *     `asn1c -gen-PER`
 */

#include "RecipientInfo.h"

static asn_oer_constraints_t asn_OER_type_RecipientInfo_constr_1 CC_NOTUSED = {
    { 0, 0 },
    -1};
asn_per_constraints_t asn_PER_type_RecipientInfo_constr_1 CC_NOTUSED = {
    { APC_CONSTRAINED,     2,  2,  0,  3 }    /* (0..3) */,
    { APC_UNCONSTRAINED,    -1, -1,  0,  0 },
    0, 0    /* No PER value map */
};
asn_TYPE_member_t asn_MBR_RecipientInfo_1[] = {
    { ATF_NOFLAGS, 0, offsetof(struct RecipientInfo, choice.pskRecipientInfo),
        (ASN_TAG_CLASS_CONTEXT | (0 << 2)),
        -1,    /* IMPLICIT tag at current level */
        &asn_DEF_PreSharedKeyRecipientInfo,
        0,
        { 0, 0, 0 },
        0, 0, /* No default value */
        "pskRecipientInfo"
        },
    { ATF_NOFLAGS, 0, offsetof(struct RecipientInfo, choice.symmRecipInfo),
        (ASN_TAG_CLASS_CONTEXT | (1 << 2)),
        -1,    /* IMPLICIT tag at current level */
        &asn_DEF_SymmRecipInfo,
        0,
        { 0, 0, 0 },
        0, 0, /* No default value */
        "symmRecipInfo"
        },
    { ATF_NOFLAGS, 0, offsetof(struct RecipientInfo, choice.certRecipInfo),
        (ASN_TAG_CLASS_CONTEXT | (2 << 2)),
        -1,    /* IMPLICIT tag at current level */
        &asn_DEF_PKRecipientInfo,
        0,
        { 0, 0, 0 },
        0, 0, /* No default value */
        "certRecipInfo"
        },
    { ATF_NOFLAGS, 0, offsetof(struct RecipientInfo, choice.signedDataRecipInfo),
        (ASN_TAG_CLASS_CONTEXT | (3 << 2)),
        -1,    /* IMPLICIT tag at current level */
        &asn_DEF_PKRecipientInfo,
        0,
        { 0, 0, 0 },
        0, 0, /* No default value */
        "signedDataRecipInfo"
        },
};
static const asn_TYPE_tag2member_t asn_MAP_RecipientInfo_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* pskRecipientInfo */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* symmRecipInfo */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* certRecipInfo */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* signedDataRecipInfo */
};
asn_CHOICE_specifics_t asn_SPC_RecipientInfo_specs_1 = {
    sizeof(struct RecipientInfo),
    offsetof(struct RecipientInfo, _asn_ctx),
    offsetof(struct RecipientInfo, present),
    sizeof(((struct RecipientInfo *)0)->present),
    asn_MAP_RecipientInfo_tag2el_1,
    4,    /* Count of tags in the map */
    0, 0,
    -1    /* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_RecipientInfo = {
    "RecipientInfo",
    "RecipientInfo",
    &asn_OP_CHOICE,
    0,    /* No effective tags (pointer) */
    0,    /* No effective tags (count) */
    0,    /* No tags (pointer) */
    0,    /* No tags (count) */
    { &asn_OER_type_RecipientInfo_constr_1, &asn_PER_type_RecipientInfo_constr_1, CHOICE_constraint },
    asn_MBR_RecipientInfo_1,
    4,    /* Elements count */
    &asn_SPC_RecipientInfo_specs_1    /* Additional specs */
};

