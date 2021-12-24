#ifndef _LIBFOTA_H_
#define _LIBFOTA_H_

typedef enum {
  FOTA_STATUS_NONE,
  FOTA_STATUS_SEND_DELTA_DATA,
  FOTA_STATUS_UPDATE,
  FOTA_STATUS_UPDATE_COMPLETE,
} fota_status_id;

typedef struct {
  fota_status_id status;
  union {
    int err_code;
    int progress;
  } data;
} __attribute__((__packed__)) fota_status_type;


int fota_update(char* file_name, void (*cb)(fota_status_type* status));

#endif // _LIBFOTA_H_
