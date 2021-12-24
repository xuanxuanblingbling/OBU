/*
 *  Copyright (c) 2018, The Linux Foundation. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 *    * Neither the name of The Linux Foundation nor the names of its
 *      contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 *  BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 *  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 *  IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file       CellInfo.hpp
 * @brief      CellInfo is a container class for information about a Cell such as
 *             Cell Identify and Signal Strength.
 */

#ifndef CELLINFO_HPP
#define CELLINFO_HPP

#include <memory>

#include "../../../../_01_AG15Layer/Include/telux/tel/SignalStrength.hpp"

namespace telux {

namespace tel {

/** @addtogroup telematics_phone
 * @{ */

/**
 * Defines all the cell info types.
 */
enum class CellType {
   GSM = 1,
   CDMA = 2,
   LTE = 3,
   WCDMA = 4,
   TDSCDMA = 5,
};

/**
 * GsmCellIdentity class provides methods to get mobile country code, mobile network
 * code, location area code, cell identity, absolute RF channel number and
 * base station identity code.
 */
class GsmCellIdentity {
public:
   GsmCellIdentity(int mcc, int mnc, int lac, int cid, int arfcn, int bsic);
   /**
    * Get the Mobile Country Code.
    *
    * @returns Mcc value.
    */
   const int getMcc();

   /**
    * Get the Mobile Network Code.
    *
    * @returns Mnc value.
    */
   const int getMnc();

   /**
    * Get the location area code.
    *
    * @returns Location area code.
    */
   const int getLac();

   /**
    * Get the cell identity.
    *
    * @returns Cell identity.
    */
   const int getIdentity();

   /**
    * Get the absolute RF channel number.
    *
    * @returns Absolute RF channel number.
    */
   const int getArfcn();

   /**
    * Get the base station identity code.
    *
    * @returns Base station identity code.
    */
   const int getBaseStationIdentityCode();

private:
   int mcc_;
   int mnc_;
   int lac_;
   int cid_;
   int arfcn_;
   int bsic_;
};

/**
 * CdmaCellIdentity class provides methods to get the network identifier, system identifier, base
 * station identifier, longitude and latitude.
 */
class CdmaCellIdentity {
public:
   CdmaCellIdentity(int networkId, int systemId, int baseStationId, int longitude, int latitude);
   /**
    * Get the network identifier.
    *
    * @returns Network identifier.
    */
   const int getNid();

   /**
    * Get the system identifier.
    *
    * @returns System identifier.
    */
   const int getSid();

   /**
    * Get the base station identifier.
    *
    * @returns Base station identifier.
    */
   const int getBaseStationId();

   /**
    * Get the longitude.
    *
    * @returns Longitude.
    */
   const int getLongitude();

   /**
    * Get the latitude.
    *
    * @returns Latitude.
    */
   const int getLatitude();

private:
   int nid_;
   int sid_;
   int stationId_;
   int longitude_;
   int latitude_;
};

/**
 * LteCellIdentity class provides methods to get the mobile country code, mobile network
 * code, cell identity, physical cell identifier, tracking area code and absolute Rf channel number.
 */
class LteCellIdentity {
public:
   LteCellIdentity(int mcc, int mnc, int ci, int pci, int tac, int earfcn);
   /**
    * Get the Mobile Country Code.
    *
    * @returns Mcc value.
    */
   const int getMcc();

   /**
    * Get the Mobile Network Code.
    *
    * @returns Mnc value.
    */
   const int getMnc();

   /**
    * Get the cell identity.
    *
    * @returns Cell identity.
    */
   const int getIdentity();

   /**
    * Get the physical cell identifier.
    *
    * @returns Physical cell identifier.
    */
   const int getPhysicalCellId();

   /**
    * Get the tracking area code.
    *
    * @returns Tracking area code.
    */
   const int getTrackingAreaCode();

   /**
    * Get the absolute RF channel number.
    *
    * @returns Absolute RF channel number.
    */
   const int getEarfcn();

private:
   int mcc_;
   int mnc_;
   int ci_;
   int pci_;
   int tac_;
   int earfcn_;
};

/**
 * WcdmaCellIdentity class provides methods to get the mobile country code, mobile network
 * code, location area code, cell identitifier, primary scrambling code and absolute RF channel
 * number.
 */
class WcdmaCellIdentity {
public:
   WcdmaCellIdentity(int mcc, int mnc, int lac, int cid, int psc, int uarfcn);
   /**
    * Get the Mobile Country Code.
    *
    * @returns Mcc value.
    */
   const int getMcc();

   /**
    * Get the Mobile Network Code.
    *
    * @returns Mnc value.
    */
   const int getMnc();

   /**
    * Get the location area code.
    *
    * @returns Location area code.
    */
   const int getLac();

   /**
    * Get the cell identity.
    *
    * @returns Cell identity.
    */
   const int getIdentity();

   /**
    * Get the primary scrambling code.
    *
    * @returns Primary scrambling code.
    */
   const int getPrimaryScramblingCode();

   /**
    * Get the absolute RF channel number.
    *
    * @returns Absolute RF channel number.
    */
   const int getUarfcn();

private:
   int mcc_;
   int mnc_;
   int lac_;
   int cid_;
   int psc_;
   int uarfcn_;
};

/**
 * TdscdmaCellIdentity class provides methods to get the mobile country code, mobile
 * network code, location area code, cell identity and cell parameters identifier.
 */
class TdscdmaCellIdentity {
public:
   TdscdmaCellIdentity(int mcc, int mnc, int lac, int cid, int cpid);
   /**
    * Get the Mobile Country Code.
    *
    * @returns Mcc value.
    */
   const int getMcc();

   /**
    * Get the Mobile Network Code.
    *
    * @returns Mnc value.
    */
   const int getMnc();

   /**
    * Get the location area code
    *
    * @returns Location area code.
    */
   const int getLac();

   /**
    * Get the cell identity.
    *
    * @returns Cell identity.
    */
   const int getIdentity();

   /**
    * Get the cell parameters identifier.
    *
    * @returns Cell parameters identifier.
    */
   const int getParametersId();

private:
   int mcc_;
   int mnc_;
   int lac_;
   int cid_;
   int cpid_;
};

/**
 * CellInfo class provides cell info type and checks whether the current cell is registered
 * or not.
 */
class CellInfo {
public:
   /**
    * Get the cell type.
    *
    * @returns CellType.
    */
   virtual CellType getType();

   /**
    * Checks whether the current cell is registered or not.
    *
    * @returns If true cell is registered or vice-versa.
    */
   virtual bool isRegistered();

protected:
   CellType type_;
   int registered_;
};

/**
 *GsmCellInfo class provides methods to get cell type, cell registration status, cell
 *identity and signal strength information.
 */
class GsmCellInfo : public CellInfo {
public:
   /**
    * GsmCellInfo constructor.
    * @param [in] registered - Registration status of the cell.
    * @param [in] id - GSM cell identity.
    * @param [in] ssInfo - GSM cell signal strength.
    */
   GsmCellInfo(int registered, GsmCellIdentity id, GsmSignalStrengthInfo ssInfo);

   /**
    * Get GSM cell identity information.
    *
    * @returns GsmCellIdentity.
    */
   GsmCellIdentity getCellIdentity();

   /**
    * Get GSM cell signal strength information.
    *
    * @returns GsmSignalStrengthInfo.
    */
   GsmSignalStrengthInfo getSignalStrengthInfo();

private:
   GsmCellIdentity id_;
   GsmSignalStrengthInfo ssInfo_;
};

/**
 *CdmaCellInfo class provides methods to get cell type, cell registration status, cell
 *identity and signal strength information.
 */
class CdmaCellInfo : public CellInfo {
public:
   /**
    * CdmaCellInfo constructor
    * @param [in] registered - Registration status of the cell.
    * @param [in] id - CDMA cell identity.
    * @param [in] ssInfo - CDMA cell signal strength.
    */
   CdmaCellInfo(int registered, CdmaCellIdentity id, CdmaSignalStrengthInfo ssInfo);

   /**
    * Get CDMA cell identity information.
    *
    * @returns CdmaCellIdentity.
    */
   CdmaCellIdentity getCellIdentity();

   /**
    * Get CDMA cell signal strength information.
    *
    * @returns CdmaSignalStrengthInfo.
    */
   CdmaSignalStrengthInfo getSignalStrengthInfo();

private:
   CdmaCellIdentity id_;
   CdmaSignalStrengthInfo ssInfo_;
};

/**
 *LteCellInfo class provides methods to get cell type, cell registration status, cell
 *identity and signal strength information.
 */
class LteCellInfo : public CellInfo {
public:
   /**
    * LteCellInfo constructor.
    * @param [in] registered - Registration status of the cell.
    * @param [in] id - LTE cell identity class.
    * @param [in] ssInfo - LTE cell signal strength.
    */
   LteCellInfo(int registered, LteCellIdentity id, LteSignalStrengthInfo ssInfo);

   /**
    * Get LTE cell identity information.
    *
    * @returns LteCellIdentity.
    */
   LteCellIdentity getCellIdentity();

   /**
    * Get LTE cell signal strength information.
    *
    * @returns LteSignalStrengthInfo.
    */
   LteSignalStrengthInfo getSignalStrengthInfo();

private:
   LteCellIdentity id_;
   LteSignalStrengthInfo ssInfo_;
};

/**
 *WcdmaCellInfo class provides methods to get cell type, cell registration status, cell
 *identity and signal strength information.
 */
class WcdmaCellInfo : public CellInfo {
public:
   /**
    * WcdmaCellInfo constructor.
    * @param [in] registered - Registration status of the cell.
    * @param [in] id - WCDMA cell identity.
    * @param [in] ssInfo - WCDMA cell signal strength.
    */
   WcdmaCellInfo(int registered, WcdmaCellIdentity id, WcdmaSignalStrengthInfo ssInfo);

   /**
    * Get WCDMA cell identity information.
    *
    * @returns WcdmaCellIdentity.
    */
   WcdmaCellIdentity getCellIdentity();

   /**
    * Get WCDMA cell signal strength information.
    *
    * @returns WcdmaSignalStrengthInfo.
    */
   WcdmaSignalStrengthInfo getSignalStrengthInfo();

private:
   WcdmaCellIdentity id_;
   WcdmaSignalStrengthInfo ssInfo_;
};

/**
 *TdscdmaCellInfo class provides methods to get cell type, cell registration status, cell
 *identity and signal strength information.
 */
class TdscdmaCellInfo : public CellInfo {
public:
   /**
    * TdscdmaCellInfo constructor.
    * @param [in] registered - Registration status of the cell
    * @param [in] id - TDSCDMA cell identity.
    * @param [in] ssInfo - TDSCDMA cell signal strength.
    */
   TdscdmaCellInfo(int registered, TdscdmaCellIdentity id, TdscdmaSignalStrengthInfo ssInfo);

   /**
    * Get TDSCDMA cell identity information.
    *
    * @returns TdscdmaCellIdentity.
    */
   TdscdmaCellIdentity getCellIdentity();

   /**
    * Get TDSCDMA cell signal strength information.
    *
    * @returns TdscdmaSignalStrengthInfo.
    */
   TdscdmaSignalStrengthInfo getSignalStrengthInfo();

private:
   TdscdmaCellIdentity id_;
   TdscdmaSignalStrengthInfo ssInfo_;
};

/** @} */ /* end_addtogroup telematics_phone */

}  // End of namespace tel

}  // End of namespace telux

#endif
