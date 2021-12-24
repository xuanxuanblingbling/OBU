/*
 * COPYRIGHT (C) 2017-2019, zhllxt
 *
 * author   : zhllxt
 * email    : 37792738@qq.com
 * 
 * Distributed under the GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
 * (See accompanying file LICENSE or see <http://www.gnu.org/licenses/>)
 */

#ifndef __ASIO2_CLIENT_HPP__
#define __ASIO2_CLIENT_HPP__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <cstdint>
#include <memory>
#include <chrono>
#include <functional>
#include <atomic>
#include <string>
#include <string_view>
#include <queue>
#include <any>
#include <future>
#include <tuple>
#include <unordered_map>
#include <type_traits>

#include <asio2/base/selector.hpp>
#include <asio2/base/iopool.hpp>
#include <asio2/base/error.hpp>
#include <asio2/base/listener.hpp>
#include <asio2/base/define.hpp>

#include <asio2/base/detail/object.hpp>
#include <asio2/base/detail/allocator.hpp>
#include <asio2/base/detail/util.hpp>
#include <asio2/base/detail/buffer_wrap.hpp>

#include <asio2/base/component/connect_time_cp.hpp>
#include <asio2/base/component/alive_time_cp.hpp>
#include <asio2/base/component/user_data_cp.hpp>
#include <asio2/base/component/socket_cp.hpp>
#include <asio2/base/component/connect_cp.hpp>
#include <asio2/base/component/disconnect_cp.hpp>
#include <asio2/base/component/local_endpoint_cp.hpp>
#include <asio2/base/component/user_timer_cp.hpp>
#include <asio2/base/component/post_cp.hpp>
#include <asio2/base/component/send_cp.hpp>
#include <asio2/base/component/connect_timeout_cp.hpp>
#include <asio2/base/component/event_queue_cp.hpp>
#include <asio2/base/component/reconnect_timer_cp.hpp>
#include <asio2/base/component/async_event_cp.hpp>
#include <asio2/base/component/rdc_call_cp.hpp>

#include <asio2/util/defer.hpp>

namespace asio2::detail
{
	ASIO2_CLASS_FORWARD_DECLARE_BASE;

	template<class derived_t, class args_t>
	class client_impl_t
		: public object_t              <derived_t        >
		, public iopool_cp
		, public event_queue_cp        <derived_t, args_t>
		, public user_data_cp          <derived_t, args_t>
		, public connect_time_cp       <derived_t, args_t>
		, public alive_time_cp         <derived_t, args_t>
		, public socket_cp             <derived_t, args_t>
		, public connect_cp            <derived_t, args_t>
		, public disconnect_cp         <derived_t, args_t>
		, public local_endpoint_cp     <derived_t, args_t>
		, public reconnect_timer_cp    <derived_t, args_t>
		, public user_timer_cp         <derived_t, args_t>
		, public connect_timeout_cp    <derived_t, args_t>
		, public send_cp               <derived_t, args_t>
		, public post_cp               <derived_t, args_t>
		, public async_event_cp        <derived_t, args_t>
		, public rdc_call_cp           <derived_t, args_t>
	{
		ASIO2_CLASS_FRIEND_DECLARE_BASE;

	public:
		using super = object_t     <derived_t        >;
		using self  = client_impl_t<derived_t, args_t>;

		using buffer_type = typename args_t::buffer_t;

		/**
		 * @constructor
		 */
		template<class ...Args>
		explicit client_impl_t(
			std::size_t concurrency,
			std::size_t init_buffer_size,
			std::size_t max_buffer_size,
			Args&&...   args
		)
			: super()
			, iopool_cp(concurrency)
			, event_queue_cp      <derived_t, args_t>()
			, user_data_cp        <derived_t, args_t>()
			, connect_time_cp     <derived_t, args_t>()
			, alive_time_cp       <derived_t, args_t>()
			, socket_cp           <derived_t, args_t>(iopool_.get(0).context(), std::forward<Args>(args)...)
			, connect_cp          <derived_t, args_t>()
			, disconnect_cp       <derived_t, args_t>()
			, local_endpoint_cp   <derived_t, args_t>()
			, reconnect_timer_cp  <derived_t, args_t>(iopool_.get(0))
			, user_timer_cp       <derived_t, args_t>()
			, connect_timeout_cp  <derived_t, args_t>(iopool_.get(0))
			, send_cp             <derived_t, args_t>()
			, post_cp             <derived_t, args_t>()
			, async_event_cp      <derived_t, args_t>()
			, rdc_call_cp         <derived_t, args_t>()
			, rallocator_()
			, wallocator_()
			, listener_  ()
			, io_        (iopool_.get(0))
			, buffer_    (init_buffer_size, max_buffer_size)
		{
		}

		/**
		 * @destructor
		 */
		~client_impl_t()
		{
		}

		/**
		 * @function : start the client
		 * @param    : async_connect - asynchronous connect to the server or sync
		 * @return   : true  - start successed , false - start failed
		 */
		inline bool start(bool async_connect = true)
		{
			return true;
		}

		/**
		 * @function : stop the client
		 */
		inline void stop()
		{
			if (!this->io_.strand().running_in_this_thread())
			{
				this->derived().post([this, this_ptr = this->derived().selfptr()]() mutable
				{
					this->stop();
				});
				return;
			}

			// close reconnect timer
			this->_stop_reconnect_timer();

			// close connect timeout timer
			this->_stop_connect_timeout_timer(asio::error::operation_aborted);

			// close user custom timers
			this->stop_all_timers();

			// close all posted timed tasks
			this->stop_all_timed_tasks();

			// close all async_events
			this->notify_all_events();

			// destroy user data, maybe the user data is self shared_ptr, if don't destroy it,
			// will cause loop refrence.
			this->user_data_.reset();
		}

		/**
		 * @function : check whether the client is started
		 */
		inline bool is_started() const
		{
			return (this->state_ == state_t::started && this->socket_.lowest_layer().is_open());
		}

		/**
		 * @function : check whether the client is stopped
		 */
		inline bool is_stopped() const
		{
			return (this->state_ == state_t::stopped && !this->socket_.lowest_layer().is_open());
		}

		/**
		 * @function : get the buffer object refrence
		 */
		inline buffer_wrap<buffer_type> & buffer() { return this->buffer_; }

		/**
		 * @function : get the io object refrence
		 */
		inline io_t & io() { return this->io_; }

		/**
		 * @function : set the default remote call timeout for rpc/rdc
		 */
		template<class Rep, class Period>
		inline derived_t & default_timeout(std::chrono::duration<Rep, Period> duration)
		{
			this->rc_timeout_ = duration;
			return (this->derived());
		}

		/**
		 * @function : get the default remote call timeout for rpc/rdc
		 */
		inline std::chrono::steady_clock::duration default_timeout()
		{
			return this->rc_timeout_;
		}

	protected:
		/**
		 * @function : get the recv/read allocator object refrence
		 */
		inline auto & rallocator() { return this->rallocator_; }
		/**
		 * @function : get the send/write allocator object refrence
		 */
		inline auto & wallocator() { return this->wallocator_; }

		inline listener_t                 & listener() { return this->listener_; }
		inline std::atomic<state_t>       & state()    { return this->state_;    }
		inline std::shared_ptr<derived_t>   selfptr()  { return std::shared_ptr<derived_t>{}; }

	protected:
		/// The memory to use for handler-based custom memory allocation. used fo recv/read.
		handler_memory<>                            rallocator_;

		/// The memory to use for handler-based custom memory allocation. used fo send/write.
		handler_memory<size_op<>, std::true_type>   wallocator_;

		/// listener 
		listener_t                                  listener_;

		/// The io (include io_context and strand) used to handle the connect/recv/send event.
		io_t                                      & io_;

		/// buffer
		buffer_wrap<buffer_type>                    buffer_;

		/// state
		std::atomic<state_t>                        state_      = state_t::stopped;

		/// Remote call (rpc/rdc) response timeout.
		std::chrono::steady_clock::duration         rc_timeout_ = std::chrono::milliseconds(http_execute_timeout);
	};
}

#endif // !__ASIO2_CLIENT_HPP__
