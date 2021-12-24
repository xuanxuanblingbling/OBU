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
 * @file       LocationFactory.hpp
 * @brief      LocationFactory allows creation of location manager.
 */

#ifndef LOCATIONFACTORY_HPP
#define LOCATIONFACTORY_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../../../../_01_AG15Layer/Include/telux/loc/LocationDefines.hpp"
#include "../../../../_01_AG15Layer/Include/telux/loc/LocationManager.hpp"

namespace telux {

namespace loc {
/** @addtogroup telematics_location
 * @{ */

/**
 * @brief   LocationFactory allows creation of location manager.
 */
class LocationFactory {
public:
   /**
    * Get Location Factory instance.
    */
   static LocationFactory &getInstance();

   /**
    * Get instance of Location Manager
    *
    * @returns Pointer of ILocationManager object.
    */
   std::shared_ptr<ILocationManager> getLocationManager();

   ~LocationFactory();

private:
   std::shared_ptr<ILocationManager> locationManager_;
   std::mutex locationFactoryMutex_;
   LocationFactory();
   LocationFactory(const LocationFactory &) = delete;
   LocationFactory &operator=(const LocationFactory &) = delete;
};
/** @} */ /* end_addtogroup telematics_location */
}  // end of namespace loc

}  // end of namespace telux

#endif  // LocationFactory_HPP
