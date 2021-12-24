/*
 *  Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
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
 * @file       DataProfileListener.hpp
 *
 * @brief      Listener interface for receiving data profile change events.
 *
 * @note       Eval: This is a new API and is being evaluated.It is subject to change
 *             and could break backwards compatibility.
 */

#ifndef DATAPROFILELISTENER_HPP
#define DATAPROFILELISTENER_HPP

#include "telux/data/DataDefines.hpp"

namespace telux {

namespace data {

/** @addtogroup telematics_data
 * @{ */

/**
 * @brief Listener class for getting profile change notification
 *
 *        The methods in the listener can be invoked from multiple threads.
 *        It is client's responsibility to make sure the implementation is thread safe.
 *
 * @note  Eval: This is a new API and is being evaluated.It is subject to change
 *        and could break backwards compatibility.
 */
class IDataProfileListener {
public:
   /**
    * This function is called when profile change happens.
    *
    * @param [in] profileId - ID of the updated profile.
    * @param [in] techPreference - @Ref TechPreference.
    * @param [in] event - Event that caused the change in profile.
    *
    * @note    Eval: This is a new API and is being evaluated. It is subject to change
    *          and could break backwards compatibility.
    */
   virtual void onProfileUpdate(int profileId, TechPreference techPreference,
      ProfileChangeEvent event) {
   }

   /**
    * Destructor of IDataProfileListener
    */
   virtual ~IDataProfileListener() {
   }
};
/** @} */ /* end_addtogroup telematics_data */
}  // end of namespace data

}  // end of namespace telux

#endif  // DATAPROFILELISTENER_HPP
