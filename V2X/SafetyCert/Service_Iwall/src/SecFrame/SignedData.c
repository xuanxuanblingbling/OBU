/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SecMsg"
 *     found in "SecMsg.asn"
 *     `asn1c -gen-PER`
 */

#include "SignedData.h"

asn_TYPE_member_t asn_MBR_SignedData_1[] = {
    { ATF_NOFLAGS, 0, offsetof(struct SignedData, signer),
        (ASN_TAG_CLASS_CONTEXT | (0 << 2)),
        +1,    /* EXPLICIT tag at current level */
        &asn_DEF_SignerInfo,
        0,
        { 0, 0, 0 },
        0, 0, /* No default value */
        "signer"
        },
    { ATF_NOFLAGS, 0, offsetof(struct SignedData, tbs),
        (ASN_TAG_CLASS_CONTEXT | (1 << 2)),
        -1,    /* IMPLICIT tag at current level */
        &asn_DEF_TBSData,
        0,
        { 0, 0, 0 },
        0, 0, /* No default value */
        "tbs"
        },
    { ATF_NOFLAGS, 0, offsetof(struct SignedData, sign),
        (ASN_TAG_CLASS_CONTEXT | (2 << 2)),
        -1,    /* IMPLICIT tag at current level */
        &asn_DEF_Signature,
        0,
        { 0, 0, 0 },
        0, 0, /* No default value */
        "sign"
        },
};
static const ber_tlv_tag_t asn_DEF_SignedData_tags_1[] = {
    (ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_SignedData_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* signer */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* tbs */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* sign */
};
asn_SEQUENCE_specifics_t asn_SPC_SignedData_specs_1 = {
    sizeof(struct SignedData),
    offsetof(struct SignedData, _asn_ctx),
    asn_MAP_SignedData_tag2el_1,
    3,    /* Count of tags in the map */
    0, 0, 0,    /* Optional elements (not needed) */
    -1,    /* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_SignedData = {
    "SignedData",
    "SignedData",
    &asn_OP_SEQUENCE,
    asn_DEF_SignedData_tags_1,
    sizeof(asn_DEF_SignedData_tags_1)
        /sizeof(asn_DEF_SignedData_tags_1[0]), /* 1 */
    asn_DEF_SignedData_tags_1,    /* Same as above */
    sizeof(asn_DEF_SignedData_tags_1)
        /sizeof(asn_DEF_SignedData_tags_1[0]), /* 1 */
    { 0, 0, SEQUENCE_constraint },
    asn_MBR_SignedData_1,
    3,    /* Elements count */
    &asn_SPC_SignedData_specs_1    /* Additional specs */
};
