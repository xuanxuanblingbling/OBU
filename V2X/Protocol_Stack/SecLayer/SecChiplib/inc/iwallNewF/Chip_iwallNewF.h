#ifndef IWALL_NEW_FOUR_CROSS_H
#define IWALL_NEW_FOUR_CROSS_H

#include <stdint.h>
#define MODULE_NAME "Chip_iwallNewF"
uint32_t SecChipFactoryCheck();
int32_t SecChip_Init(seclayer_status_callback cb, void *cb_para, const char *fileName);
int32_t SecDataSign_RSU(uint64_t p_u64Aid,
                                        uint8_t *pdu, int32_t pdu_size,
                                        uint8_t *spdu, int32_t *spdu_size);

int32_t SecDataSign_OBU(uint64_t aid, int32_t emergency_event_flag,
                                  double longitude, double latitude,
                                  uint8_t *pdu, int32_t pdu_size, uint8_t *spdu, int32_t *spdu_size);


int32_t SecDataVerify(uint8_t *spdu, int32_t spdu_size,
                                 uint8_t *pdu, int32_t *pdu_size,
                                 uint64_t *p_pu64AID);  
int32_t SecChipDeinit(void);

#endif