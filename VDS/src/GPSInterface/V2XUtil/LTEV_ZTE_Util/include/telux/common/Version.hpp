/*
 *  Copyright (c) 2017-2019, The Linux Foundation. All rights reserved.
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
 * @file       Version.hpp
 * @brief      Provide APIs to query the version of the SDK
 */

#ifndef VERSION_HPP
#define VERSION_HPP

#include <string>

#define DEFAULT_VALUE -1

namespace telux {
namespace common {

/** @addtogroup telematics_common
 * @{ */

/**
 * Structure of major, minor and patch version
 */
struct SdkVersion {
   int major = DEFAULT_VALUE; /**< Major Version: This number will be incremented whenever
                                   significant changes  or features are introduced */
   int minor = DEFAULT_VALUE; /**< Minor Version: This number will be incremented when smaller
                                   features with some new APIs are introduced. */
   int patch = DEFAULT_VALUE; /**< Patch Version: If the release only contains bug fixes,
                                   but no API change then the patch version would be incremented.*/
};

/**
 * @brief Provides version of SDK.
 */
class Version {
public:
   /**
    * Get the release name.
    *
    * @returns String contains release name
    */
   static std::string getReleaseName();

   /**
    * Get the Telematics SDK version, for example: 01.00.00
    *
    * @returns @ref SdkVersion structure of major, minor and patch version
    */
   static SdkVersion getSdkVersion();
};
/** @} */ /* end_addtogroup telematics_common */
}
}

#endif
