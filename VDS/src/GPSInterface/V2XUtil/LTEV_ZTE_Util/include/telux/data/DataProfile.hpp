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
 * @file       DataProfile.hpp
 * @brief      This is a container class represents single data profile on the modem.
 *
 *
 */

#ifndef DATAPROFILE_HPP
#define DATAPROFILE_HPP

#include <telux/data/DataDefines.hpp>

namespace telux {
namespace data {
/** @addtogroup telematics_data
 * @{ */

/**
 * @brief  DataProfile class represents single data profile on the modem.
 *
 */
class DataProfile {
public:
   DataProfile(int id, const std::string &name, const std::string &apn, const std::string &username,
               const std::string &password, IpFamilyType ipFamilyType, TechPreference techPref,
               AuthProtocolType authType);

   /**
    * Get profile identifier.
    *
    * @returns profile id
    *
    */
   int getId();

   /**
    * Get profile name.
    *
    * @returns profile name
    *
    */
   std::string getName();

   /**
    * Get Access Point Name (APN) name.
    *
    * @returns APN name
    *
    */
   std::string getApn();

   /**
    * Get profile user name.
    *
    * @returns user name
    *
    */
   std::string getUserName();

   /**
    * Get profile password.
    *
    * @returns profile password
    *
    */
   std::string getPassword();

   /**
    * Get technology preference.
    *
    * @returns TechPreference @ref TechPreference
    *
    */
   TechPreference getTechPreference();

   /**
    * Get authentication preference.
    *
    * @returns AuthProtocolType @ref AuthProtocolType
    *
    */
   AuthProtocolType getAuthProtocolType();

   /**
    * Get IP Family type.
    *
    * @returns IpFamilyType @ref IpFamilyType
    *
    */
   IpFamilyType getIpFamilyType();

   /**
    * Get the text related informative representation of this object.
    *
    * @returns String containing informative string.
    *
    */
   std::string toString();

private:
   int id_;
   std::string name_;
   std::string apn_;
   std::string username_;
   std::string password_;
   IpFamilyType ipFamilyType_;
   TechPreference techPref_;
   AuthProtocolType authType_;
};

/** @} */ /* end_addtogroup telematics_data */
}
}

#endif
