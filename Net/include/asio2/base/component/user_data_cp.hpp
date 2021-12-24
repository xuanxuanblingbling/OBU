/*
 * COPYRIGHT (C) 2017-2019, zhllxt
 *
 * author   : zhllxt
 * email    : 37792738@qq.com
 * 
 * Distributed under the GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
 * (See accompanying file LICENSE or see <http://www.gnu.org/licenses/>)
 */

#ifndef __ASIO2_USER_DATA_COMPONENT_HPP__
#define __ASIO2_USER_DATA_COMPONENT_HPP__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <any>

#include <asio2/base/error.hpp>

namespace asio2::detail
{
	template<class derived_t, class args_t = void>
	class user_data_cp
	{
	public:
		/**
		 * @constructor
		 */
		user_data_cp() {}

		/**
		 * @destructor
		 */
		~user_data_cp() = default;

	public:
		/**
		 * @function : set user data, internal use std::any to storage, you can set any type of data
		 */
		template<class DataT>
		inline derived_t & user_data(DataT && data)
		{
			this->user_data_ = std::forward<DataT>(data);
			return (static_cast<derived_t &>(*this));
		}

		/**
		 * @function : get user data
		 * example : MyStruct my = user_data<MyStruct>(); MyStruct* my = user_data<MyStruct*>();
		 */
		template<class DataT>
		inline DataT user_data()
		{
			try
			{
				if constexpr (std::is_pointer_v<DataT>)
				{
					// user_data_ is pointer, and DataT is pointer too.
					if (this->user_data_.type() == typeid(DataT))
						return std::any_cast<DataT>(this->user_data_);

					// user_data_ is not pointer, but DataT is pointer.
					return std::any_cast<std::remove_pointer_t<DataT>>(&(this->user_data_));
				}
				else
				{
					return std::any_cast<DataT>(this->user_data_);
				}
			}
			catch (const std::bad_any_cast&)
			{
				if (this->user_data_.has_value())
				{
					ASIO2_ASSERT(false);
				}
			}
			return DataT{};
		}

		inline std::any& user_data_any() { return this->user_data_; }

	protected:
		/// user data
		std::any user_data_;
	};
}

#endif // !__ASIO2_USER_DATA_COMPONENT_HPP__
