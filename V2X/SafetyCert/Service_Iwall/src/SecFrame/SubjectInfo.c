/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "CER"
 *     found in "CER.asn"
 *     `asn1c -gen-PER`
 */

#include "SubjectInfo.h"

static int
memb_subjectName_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
            asn_app_constraint_failed_f *ctfailcb, void *app_key) {
    const OCTET_STRING_t *st = (const OCTET_STRING_t *)sptr;
    size_t size;

    if(!sptr) {
        ASN__CTFAIL(app_key, td, sptr,
            "%s: value not given (%s:%d)",
            td->name, __FILE__, __LINE__);
        return -1;
    }

    size = st->size;

    if((size <= 32)) {
        /* Constraint check succeeded */
        return 0;
    } else {
        ASN__CTFAIL(app_key, td, sptr,
            "%s: constraint failed (%s:%d)",
            td->name, __FILE__, __LINE__);
        return -1;
    }
}

static asn_oer_constraints_t asn_OER_memb_subjectName_constr_3 CC_NOTUSED = {
    { 0, 0 },
    -1    /* (SIZE(0..32)) */};
static asn_per_constraints_t asn_PER_memb_subjectName_constr_3 CC_NOTUSED = {
    { APC_UNCONSTRAINED,    -1, -1,  0,  0 },
    { APC_CONSTRAINED,     6,  6,  0,  32 }    /* (SIZE(0..32)) */,
    0, 0    /* No PER value map */
};
asn_TYPE_member_t asn_MBR_SubjectInfo_1[] = {
    { ATF_NOFLAGS, 0, offsetof(struct SubjectInfo, subjectType),
        (ASN_TAG_CLASS_CONTEXT | (0 << 2)),
        -1,    /* IMPLICIT tag at current level */
        &asn_DEF_SubjectType,
        0,
        { 0, 0, 0 },
        0, 0, /* No default value */
        "subjectType"
        },
    { ATF_NOFLAGS, 0, offsetof(struct SubjectInfo, subjectName),
        (ASN_TAG_CLASS_CONTEXT | (1 << 2)),
        -1,    /* IMPLICIT tag at current level */
        &asn_DEF_OCTET_STRING,
        0,
        { &asn_OER_memb_subjectName_constr_3, &asn_PER_memb_subjectName_constr_3,  memb_subjectName_constraint_1 },
        0, 0, /* No default value */
        "subjectName"
        },
};
static const ber_tlv_tag_t asn_DEF_SubjectInfo_tags_1[] = {
    (ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_SubjectInfo_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* subjectType */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* subjectName */
};
asn_SEQUENCE_specifics_t asn_SPC_SubjectInfo_specs_1 = {
    sizeof(struct SubjectInfo),
    offsetof(struct SubjectInfo, _asn_ctx),
    asn_MAP_SubjectInfo_tag2el_1,
    2,    /* Count of tags in the map */
    0, 0, 0,    /* Optional elements (not needed) */
    -1,    /* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_SubjectInfo = {
    "SubjectInfo",
    "SubjectInfo",
    &asn_OP_SEQUENCE,
    asn_DEF_SubjectInfo_tags_1,
    sizeof(asn_DEF_SubjectInfo_tags_1)
        /sizeof(asn_DEF_SubjectInfo_tags_1[0]), /* 1 */
    asn_DEF_SubjectInfo_tags_1,    /* Same as above */
    sizeof(asn_DEF_SubjectInfo_tags_1)
        /sizeof(asn_DEF_SubjectInfo_tags_1[0]), /* 1 */
    { 0, 0, SEQUENCE_constraint },
    asn_MBR_SubjectInfo_1,
    2,    /* Elements count */
    &asn_SPC_SubjectInfo_specs_1    /* Additional specs */
};

