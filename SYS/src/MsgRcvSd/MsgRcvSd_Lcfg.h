/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of WJ. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from WJ.
********************************************************************************
*   File Name:       MsgRcvSd_Lcfg.h
********************************************************************************
*   Project/Product : sysM programme
*   Title:          : MsgRcvSd_Lcfg.h
*   Author:         : wensheng.zhang       2020
********************************************************************************
*   Limitations:      None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version       Date       Initials        CR#        Descriptions
*   -------   ----------  --------------    ------    -------------------
*   01.00.00  07/07/2020  wensheng.zhang      N/A         Original
********************************************************************************
*END_FILE_HDR*/

#ifndef MSGRCVSD_LCFG_H
#define MSGRCVSD_LCFG_H

#include "sys_dbus.h"
#include "MsgRcvSd.h"

static guint signals[LAST_SIGNAL];
V2xObu *obj;

typedef enum  _t_MsgMValidityType
{
	MSGM_INVALID,
	MSGM_VALID,
} t_MsgMValidityType;

#define MSGM_TAG_BYTE_SIZE               2
#define MSGM_LENGTH_BYTE_SIZE            2
#define MSGM_BCC_BYTE_SIZE               1

#define MSGM_TAG_POS                     0
#define MSGM_LENGTH_POS                  2
#define MSGM_DATA_POS                    4

#define MSGM_VDS_VEHDATA_TAG             0x1001
#define MSGM_VDS_STATE_TAG               0x1002
#define MSGM_VDS_DTC_TAG                 0x1003
#define MSGM_MCU_DTC_TAG                 0x1004
#define MSGM_MCU_POWRQ_TAG               0x1005
#define MSGM_VDS_CFGRESP_TAG             0x1006
#define MSGM_MCU_CFGRESP_TAG             0x1007

#define MSGM_V2X_STATE_TAG               0x2002
#define MSGM_V2X_DTC_TAG                 0x2003
#define MSGM_V2X_CFGRESP_TAG             0x2004

#define MSGM_APP_CFGRESP_TAG             0x3004
#define MSGM_APP_DTC_TAG                 0x3005

#define MSGM_NET_STATE_TAG               0x5002
#define MSGM_NET_CFGRESP_TAG             0x5003
#define MSGM_NET_FAULT_TAG               0x5004

#define MSGM_VDS_DATADECODE_STATE_POS        MSGM_DATA_POS+0
#define MSGM_VDS_DATADECODE_STATE_LEN        1
#define MSGM_VDS_MCUSD_STATE_POS             MSGM_DATA_POS+1
#define MSGM_VDS_MCUSD_STATE_LEN             1
#define MSGM_VDS_MCURCV_STATE_POS            MSGM_DATA_POS+2
#define MSGM_VDS_MCURCV_STATE_LEN            1
#define MSGM_VDS_GNSSRCV_STATE_POS           MSGM_DATA_POS+3
#define MSGM_VDS_GNSSRCV_STATE_LEN           1
#define MSGM_VDS_GNSS_STATE_POS              MSGM_DATA_POS+4
#define MSGM_VDS_GNSS_STATE_LEN              1
#define MSGM_VDS_QTYSVUSED_STATE_POS         MSGM_DATA_POS+5
#define MSGM_VDS_QTYSVUSED_STATE_LEN         1

#define MSGM_VDS_LATITUDEINT_STATE_POS       MSGM_DATA_POS+6
#define MSGM_VDS_LATITUDEINT_STATE_LEN       4
#define MSGM_VDS_LONGTUDEINT_STATE_POS       MSGM_DATA_POS+10
#define MSGM_VDS_LONGTUDEINT_STATE_LEN       4

#define MSGM_VDS_LATITUDE_STATE_POS          MSGM_DATA_POS+32
#define MSGM_VDS_LATITUDE_STATE_LEN          4
#define MSGM_VDS_LONGITUDE_STATE_POS         MSGM_DATA_POS+36
#define MSGM_VDS_LONGITUDE_STATE_LEN         4

#define MSGM_VDS_AG35COM_DTC_POS             MSGM_DATA_POS+0
#define MSGM_VDS_AG35COM_DTC_LEN             1
#define MSGM_VDS_GNSSCOM_DTC_POS             MSGM_DATA_POS+1
#define MSGM_VDS_GNSSCOM_DTC_LEN             1
#define MSGM_VDS_GNSSDATA_DTCE_POS           MSGM_DATA_POS+2
#define MSGM_VDS_GNSSDATA_DTC_LEN            1
#define MSGM_VDS_IMUCOM_DTC_POS              MSGM_DATA_POS+3
#define MSGM_VDS_IMUCOM_DTC_LEN              1
#define MSGM_VDS_MCUCOM_DTC_POS              MSGM_DATA_POS+4
#define MSGM_VDS_MCUCOM_DTC_LEN              1
#define MSGM_VDS_G4ERROR_DTC_POS             MSGM_DATA_POS+5
#define MSGM_VDS_G4ERROR_DTC_LEN             1

#define MSGM_VDS_DATA_POS          		     MSGM_DATA_POS+0
#define MSGM_VDS_DATA_LEN                    60

#define MSGM_VDS_DATA_SPEED_POS          	 MSGM_DATA_POS+47
#define MSGM_VDS_DATA_SPEED_LEN              2

#define MSGM_MCU_CANBUSOFF_DTC_POS           MSGM_DATA_POS+0
#define MSGM_MCU_CANBUSOFF_DTC_LEN           1
#define MSGM_MCU_HIGHVOLTAGE_DTC_POS         MSGM_DATA_POS+1
#define MSGM_MCU_HIGHVOLTAGE_DTC_LEN         1
#define MSGM_MCU_LOWVOLTAGE_DTC_POS          MSGM_DATA_POS+2
#define MSGM_MCU_LOWVOLTAGE_DTC_LEN          1

#define MSGM_MCUCFG_PWRUP_DELAYTIME_POS           MSGM_DATA_POS+0
#define MSGM_MCUCFG_PWRUP_DELAYTIME_LEN           2
#define MSGM_MCUCFG_PWRUP_DELAYTIME_FLAG_POS      MSGM_DATA_POS+2
#define MSGM_MCUCFG_PWRUP_DELAYTIME_FLAG_LEN      1
#define MSGM_MCUCFG_DIAG_DELAYTIME_POS         	  MSGM_DATA_POS+3
#define MSGM_MCUCFG_DIAG_DELAYTIME_LEN         	  2
#define MSGM_MCUCFG_DIAG_DELAYTIME_FLAG_POS       MSGM_DATA_POS+5
#define MSGM_MCUCFG_DIAG_DELAYTIME_FLAG_LEN       1
#define MSGM_MCUCFG_DIAG_VMIN_POS          		  MSGM_DATA_POS+6
#define MSGM_MCUCFG_DIAG_VMIN_LEN                 2
#define MSGM_MCUCFG_DIAG_VMIN_FLAG_POS            MSGM_DATA_POS+8
#define MSGM_MCUCFG_DIAG_VMIN_FLAG_LEN            1
#define MSGM_MCUCFG_DIAG_VMAX_POS          		  MSGM_DATA_POS+9
#define MSGM_MCUCFG_DIAG_VMAX_LEN                 2
#define MSGM_MCUCFG_DIAG_VMAX_FLAG_POS            MSGM_DATA_POS+11
#define MSGM_MCUCFG_DIAG_VMAX_FLAG_LEN            1
#define MSGM_MCUCFG_DIAG_VUP_DELAY_POS            MSGM_DATA_POS+12
#define MSGM_MCUCFG_DIAG_VUP_DELAY_LEN            2
#define MSGM_MCUCFG_DIAG_VUP_DELAY_FLAG_POS       MSGM_DATA_POS+14
#define MSGM_MCUCFG_DIAG_VUP_DELAY_FLAG_LEN       1
#define MSGM_MCUCFG_DIAG_VDOME_DELAY_POS          MSGM_DATA_POS+15
#define MSGM_MCUCFG_DIAG_VDOME_DELAY_LEN          2
#define MSGM_MCUCFG_DIAG_VDOME_DELAY_FLAG_POS     MSGM_DATA_POS+17
#define MSGM_MCUCFG_DIAG_VDOME_DELAY_FLAG_LEN     1

#define MSGM_V2X_V2XSTACKTX_STATE_POS         MSGM_DATA_POS+0
#define MSGM_V2X_V2XSTACKTX_STATE_LEN         1
#define MSGM_V2X_V2XSTACKRX_STATE_POS         MSGM_DATA_POS+1
#define MSGM_V2X_V2XSTACKRX_STATE_LEN         1
#define MSGM_V2X_BSMTX_STATE_POS         	  MSGM_DATA_POS+2
#define MSGM_V2X_BSMTX_STATE_LEN          	  1
#define MSGM_V2X_CERTM_STATE_POS           	  MSGM_DATA_POS+3
#define MSGM_V2X_CERTM_STATE_LEN           	  1
#define MSGM_V2X_DBUSINTERFACE_STATE_POS      MSGM_DATA_POS+4
#define MSGM_V2X_DBUSINTERFACE_STATE_LEN      1


#define MSGM_V2X_AG15Com_DTC_POS              MSGM_DATA_POS+0
#define MSGM_V2X_AG15Com_DTC_LEN              1
#define MSGM_V2X_HSM_DTC_POS                  MSGM_DATA_POS+1
#define MSGM_V2X_HSM_DTC_LEN                  1


#define MSGM_APP_GPSDATA_DTC_POS              MSGM_DATA_POS+0
#define MSGM_APP_GPSDATA_DTC_LEN              1
#define MSGM_APP_CANDATA_DTC_POS              MSGM_DATA_POS+1
#define MSGM_APP_CANDATA_DTC_LEN              1
#define MSGM_APP_RSUDATA_DTC_POS              MSGM_DATA_POS+2
#define MSGM_APP_RSUDATA_DTC_LEN              1

#define MSGM_NET_LINKCLIENTNUM_STATE_POS         MSGM_DATA_POS+0
#define MSGM_NET_LINKCLIENTNUM_STATE_LEN         4
#define MSGM_NET_TCPRCVNUM_STATE_POS             MSGM_DATA_POS+4
#define MSGM_NET_TCPRCVNUM_STATE_LEN             4
#define MSGM_NET_TCPSDNUM_STATE_POS         	 MSGM_DATA_POS+8
#define MSGM_NET_TCPSDNUM_STATE_LEN          	 4
#define MSGM_NET_UDPSDNUM_STATE_POS           	 MSGM_DATA_POS+12
#define MSGM_NET_UDPSDNUM_STATE_LEN           	 4

#define MSGM_NET_PAD_FAULT_POS           	     MSGM_DATA_POS+0
#define MSGM_NET_PAD_FAULT_LEN           	     1
#define MSGM_NET_HTTP_FAULT_POS           	     MSGM_DATA_POS+1
#define MSGM_NET_HTTP_FAULT_LEN           	     1



#define MSGM_MCU_PWRDWN_RQ_POS           	 	 MSGM_DATA_POS+0
#define MSGM_MCU_PWRDWN_RQ_LEN           		 1

#define MSGM_MCU_CFG_RESP_POS           	 	 MSGM_DATA_POS+0
#define MSGM_MCU_CFG_RESP_LEN           		 1
#define MSGM_VDS_CFG_RESP_POS           	 	 MSGM_DATA_POS+1
#define MSGM_VDS_CFG_RESP_LEN           		 1
#define MSGM_AG35_CFG_RESP_POS           	 	 MSGM_DATA_POS+2
#define MSGM_AG35_CFG_RESP_LEN           		 1

#define MSGM_APP_CFG_RESP_POS           	 	 MSGM_DATA_POS+0
#define MSGM_APP_CFG_RESP_LEN           		 1

#define MSGM_V2X_CFG_RESP_POS           	 	 MSGM_DATA_POS+0
#define MSGM_V2X_CFG_RESP_LEN           		 1

#define MSGM_NET_CFG_RESP_POS           	 	 MSGM_DATA_POS+0
#define MSGM_NET_CFG_RESP_LEN           		 1
#endif


