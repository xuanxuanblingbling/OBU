/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VPM"
 * 	found in "VPM.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_ChannelRs_H_
#define	_ChannelRs_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ChannelID.h"
#include "ApduList.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ChannelRs */
typedef struct ChannelRs {
	ChannelID_t	 channelid;
	ApduList_t	 apdu;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ChannelRs_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ChannelRs;
extern asn_SEQUENCE_specifics_t asn_SPC_ChannelRs_specs_1;
extern asn_TYPE_member_t asn_MBR_ChannelRs_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _ChannelRs_H_ */
#include <asn_internal.h>
