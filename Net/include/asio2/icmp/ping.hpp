/*
 * COPYRIGHT (C) 2017-2019, zhllxt
 *
 * author   : zhllxt
 * email    : 37792738@qq.com
 * 
 * Distributed under the GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
 * (See accompanying file LICENSE or see <http://www.gnu.org/licenses/>)
 */

#ifndef __ASIO2_PING_HPP__
#define __ASIO2_PING_HPP__

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

#include <asio2/base/selector.hpp>
#include <asio2/base/iopool.hpp>
#include <asio2/base/error.hpp>
#include <asio2/base/listener.hpp>
#include <asio2/base/define.hpp>

#include <asio2/base/detail/object.hpp>
#include <asio2/base/detail/allocator.hpp>
#include <asio2/base/detail/util.hpp>

#include <asio2/base/component/user_data_cp.hpp>
#include <asio2/base/component/socket_cp.hpp>
#include <asio2/base/component/user_timer_cp.hpp>
#include <asio2/base/component/post_cp.hpp>
#include <asio2/base/component/async_event_cp.hpp>

#include <asio2/icmp/detail/icmp_header.hpp>
#include <asio2/icmp/detail/ipv4_header.hpp>
#include <asio2/icmp/detail/ipv6_header.hpp>

#include <asio2/util/defer.hpp>

namespace asio2
{
	class icmp_rep : public detail::ipv4_header, /*public detail::ipv6_header,*/ public detail::icmp_header
	{
	public:
		std::chrono::steady_clock::duration lag{ std::chrono::steady_clock::duration(-1) };

		inline bool is_timeout() { return (this->lag.count() == -1); }

		inline auto milliseconds()
		{
			return this->lag.count() == -1 ? -1 :
				std::chrono::duration_cast<std::chrono::milliseconds>(this->lag).count();
		}

		detail::ipv4_header& base_ipv4() { return static_cast<detail::ipv4_header&>(*this); }
		//detail::ipv6_header& base_ipv6() { return static_cast<detail::ipv6_header&>(*this); }
		detail::icmp_header& base_icmp() { return static_cast<detail::icmp_header&>(*this); }

	protected:

	};
}

namespace asio2::detail
{
	struct template_args_icmp
	{
		using socket_t = asio::ip::icmp::socket;
		using buffer_t = asio::streambuf;
	};

	ASIO2_CLASS_FORWARD_DECLARE_BASE;

	template<class derived_t, class args_t>
	class ping_impl_t
		: public object_t       <derived_t        >
		, public iopool_cp
		, public user_data_cp   <derived_t, args_t>
		, public user_timer_cp  <derived_t, args_t>
		, public post_cp        <derived_t, args_t>
		, public async_event_cp <derived_t, args_t>
	{
		ASIO2_CLASS_FRIEND_DECLARE_BASE;

	public:
		using super = object_t   <derived_t        >;
		using self  = ping_impl_t<derived_t, args_t>;

		using socket_type = typename args_t::socket_t;
		using buffer_type = typename args_t::buffer_t;

		/**
		 * @constructor
		 * @param send_count Total number of echo packets you want to send
		 * send_count equals -1 for infinite send
		 * Other parameters should use default values.
		 */
		ping_impl_t(
			std::size_t send_count       = -1,
			std::size_t init_buffer_size = 64 * 1024, // We prepare the buffer to receive up to 64KB.
			std::size_t max_buffer_size  = (std::numeric_limits<std::size_t>::max)()
		)
			: super()
			, iopool_cp(1)
			, user_data_cp   <derived_t, args_t>()
			, user_timer_cp  <derived_t, args_t>()
			, post_cp        <derived_t, args_t>()
			, async_event_cp <derived_t, args_t>()
			, socket_    (iopool_.get(0).context())
			, rallocator_()
			, wallocator_()
			, listener_  ()
			, io_        (iopool_.get(0))
			, buffer_    (init_buffer_size, max_buffer_size)
			, timer_     (iopool_.get(0).context())
			, ncount_    (send_count)
		{
		}

		/**
		 * @destructor
		 */
		~ping_impl_t()
		{
			this->stop();
		}

		/**
		 * @function : start
		 * @param host A string identifying a location. May be a descriptive name or
		 * a numeric address string.  example : "151.101.193.69" or "www.google.com"
		 */
		inline bool start(std::string_view host)
		{
			return this->derived()._do_start(host);
		}

		/**
		 * @function : stop
		 */
		inline void stop()
		{
			this->derived()._do_stop(asio::error::operation_aborted);

			this->iopool_.stop();
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
	public:
		template<class Rep, class Period>
		static inline icmp_rep execute(std::string_view host, std::chrono::duration<Rep, Period> timeout,
			std::string body, error_code& ec)
		{
			icmp_rep rep;
			try
			{
				// First assign default value timed_out to ec
				ec = asio::error::timed_out;

				// The io_context is required for all I/O
				asio::io_context ioc;

				// These objects perform our I/O
				asio::ip::icmp::resolver resolver{ ioc };
				asio::ip::icmp::socket socket{ ioc };

				asio::streambuf request_buffer;
				asio::streambuf reply_buffer;

				std::ostream os(&request_buffer);
				std::istream is(&reply_buffer);

				icmp_header echo_request;

				unsigned short id = static_cast<unsigned short>(0);
				unsigned short sequence_number = static_cast<unsigned short>(0);

				decltype(std::chrono::steady_clock::now()) time_sent;

				// Look up the domain name
				resolver.async_resolve(host, "",
					[&](const error_code& ec1, const asio::ip::icmp::resolver::results_type& endpoints) mutable
				{
					if (ec1) { ec = ec1; return; }

					for (auto& dest : endpoints)
					{
						struct socket_guard
						{
							socket_guard(
								asio::ip::icmp::socket& s,
								const asio::ip::basic_resolver_entry<asio::ip::icmp>& d
							) : socket(s), dest(d)
							{
								socket.close(ec_ignore);
								socket.open(dest.endpoint().protocol());
							}
							~socket_guard()
							{
								// Gracefully close the socket
								socket.shutdown(asio::ip::tcp::socket::shutdown_both, ec_ignore);
								socket.close(ec_ignore);
							}
							asio::ip::icmp::socket& socket;
							const asio::ip::basic_resolver_entry<asio::ip::icmp>& dest;
						};

						std::unique_ptr<socket_guard> guarder = std::make_unique<socket_guard>(socket, dest);

						// Create an ICMP header for an echo request.
						echo_request.type(icmp_header::echo_request);
						echo_request.code(0);
#if defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS_)
						id = static_cast<unsigned short>(::GetCurrentProcessId());
#else
						id = static_cast<unsigned short>(::getpid());
#endif
						echo_request.identifier(id);
						auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
							std::chrono::steady_clock::now().time_since_epoch()).count();
						sequence_number = static_cast<unsigned short>(ms % (std::numeric_limits<unsigned short>::max)());
						echo_request.sequence_number(sequence_number);
						compute_checksum(echo_request, body.begin(), body.end());

						// Encode the request packet.
						os << echo_request << body;

						// Send the request.
						time_sent = std::chrono::steady_clock::now();

						socket.async_send_to(request_buffer.data(), dest, [&, guarder = std::move(guarder)]
						(const error_code& ec2, std::size_t) mutable
						{
							if (ec2) { ec = ec2; return; }

							// Discard any data already in the buffer.
							reply_buffer.consume(reply_buffer.size());

							std::size_t length = sizeof(ipv4_header) + sizeof(icmp_header) + body.size();

							// Wait for a reply. We prepare the buffer to receive up to 64KB.
							socket.async_receive(reply_buffer.prepare(length), [&, guarder = std::move(guarder)]
							(const error_code& ec3, std::size_t bytes_recvd) mutable
							{
								ec = ec3;

								// The actual number of bytes received is committed to the buffer so that we
								// can extract it using a std::istream object.
								reply_buffer.commit(bytes_recvd);

								// Decode the reply packet.
								ipv4_header& ipv4_hdr = rep.base_ipv4();
								icmp_header& icmp_hdr = rep.base_icmp();
								is >> ipv4_hdr >> icmp_hdr;

								ASIO2_ASSERT(ipv4_hdr.total_length() == bytes_recvd);

								// We can receive all ICMP packets received by the host, so we need to
								// filter out only the echo replies that match the our identifier and
								// expected sequence number.
								if (is && icmp_hdr.type() == icmp_header::echo_reply
									&& icmp_hdr.identifier() == id
									&& icmp_hdr.sequence_number() == sequence_number)
								{
									// Print out some information about the reply packet.
									rep.lag = std::chrono::steady_clock::now() - time_sent;
								}
							});
						});

						break;
					}
				});

				// timedout run
				ioc.run_for(timeout);
			}
			catch (system_error & e)
			{
				ec = e.code();
			}

			return rep;
		}

		template<class Rep, class Period>
		static inline icmp_rep execute(std::string_view host, std::chrono::duration<Rep, Period> timeout, std::string body)
		{
			error_code ec;
			icmp_rep rep = execute(host, timeout, std::move(body), ec);
			asio::detail::throw_error(ec);
			return rep;
		}

		template<class Rep, class Period>
		static inline icmp_rep execute(std::string_view host, std::chrono::duration<Rep, Period> timeout)
		{
			error_code ec;
			icmp_rep rep = execute(host, timeout, R"("Hello!" from Asio ping.)", ec);
			asio::detail::throw_error(ec);
			return rep;
		}

		static inline icmp_rep execute(std::string_view host)
		{
			error_code ec;
			icmp_rep rep = execute(host, std::chrono::seconds(3), R"("Hello!" from Asio ping.)", ec);
			asio::detail::throw_error(ec);
			return rep;
		}

		static inline icmp_rep execute(std::string_view host, error_code& ec)
		{
			return execute(host, std::chrono::seconds(3), R"("Hello!" from Asio ping.)", ec);
		}

		template<class Rep, class Period>
		static inline icmp_rep execute(std::string_view host, std::chrono::duration<Rep, Period> timeout, error_code& ec)
		{
			return execute(host, timeout, R"("Hello!" from Asio ping.)", ec);
		}

	public:
		/**
		 * @function : bind recv listener
		 * @param    : fun - a user defined callback function
		 * void on_recv(asio2::icmp_rep& rep){...}
		 * or a lumbda function like this :
		 * [&](asio2::icmp_rep& rep){...}
		 */
		template<class F, class ...C>
		inline derived_t & bind_recv(F&& fun, C&&... obj)
		{
			this->listener_.bind(event_type::recv,
				observer_t<icmp_rep&>(std::forward<F>(fun), std::forward<C>(obj)...));
			return (this->derived());
		}

		/**
		 * @function : bind init listener,we should set socket options at here
		 * @param    : fun - a user defined callback function
		 * This notification is called after the socket is opened.
		 * You can set the socket option in this notification.
		 * Function signature : void()
		 */
		template<class F, class ...C>
		inline derived_t & bind_init(F&& fun, C&&... obj)
		{
			this->listener_.bind(event_type::init,
				observer_t<>(std::forward<F>(fun), std::forward<C>(obj)...));
			return (this->derived());
		}

		/**
		 * @function : bind start listener
		 * @param    : fun - a user defined callback function
		 * This notification is called after the server starts up, whether successful or unsuccessful
		 * Function signature : void(asio2::error_code ec)
		 */
		template<class F, class ...C>
		inline derived_t & bind_start(F&& fun, C&&... obj)
		{
			this->listener_.bind(event_type::start,
				observer_t<error_code>(std::forward<F>(fun), std::forward<C>(obj)...));
			return (this->derived());
		}

		/**
		 * @function : bind stop listener
		 * @param    : fun - a user defined callback function
		 * This notification is called before the server is ready to stop
		 * Function signature : void(asio2::error_code ec)
		 */
		template<class F, class ...C>
		inline derived_t & bind_stop(F&& fun, C&&... obj)
		{
			this->listener_.bind(event_type::stop,
				observer_t<error_code>(std::forward<F>(fun), std::forward<C>(obj)...));
			return (this->derived());
		}

	public:
		/**
		 * @function : get the socket object refrence
		 */
		inline socket_type & socket() { return this->socket_; }

		/**
		 * @function : get the stream object refrence
		 */
		inline socket_type & stream() { return this->socket_; }

	public:
		/**
		 * @function : set reply timeout duration value
		 */
		template<class Rep, class Period>
		inline derived_t & timeout(std::chrono::duration<Rep, Period> duration)
		{
			this->timeout_ = duration;
			return (this->derived());
		}

		/**
		 * @function : get reply timeout duration value
		 */
		inline std::chrono::steady_clock::duration timeout()
		{
			return this->timeout_;
		}

		/**
		 * @function : set send interval duration value
		 */
		template<class Rep, class Period>
		inline derived_t & interval(std::chrono::duration<Rep, Period> duration)
		{
			this->interval_ = duration;
			return (this->derived());
		}

		/**
		 * @function : set icmp payload body
		 * This function is the same as the "payload()" function
		 */
		inline derived_t & body(std::string_view body)
		{
			this->body_ = body;
			if (this->body_.size() > 65500)
				this->body_.resize(65500);
			return (this->derived());
		}

		/**
		 * @function : set icmp payload body
		 * This function is the same as the "body()" function
		 */
		inline derived_t & payload(std::string_view body)
		{
			return this->derived().body(std::move(body));
		}

		/**
		 * @function : get the resolved host ip
		 */
		inline std::string host_ip() { return this->destination_.address().to_string(); }

		/**
		 * @function : Set the total number of echo packets you want to send
		 */
		inline derived_t & ncount(std::size_t send_count)
		{
			this->ncount_ = send_count;
			return (this->derived());
		}

		/**
		 * @function : Get the total number of echo packets has sent
		 */
		inline std::size_t total_send() { return this->total_send_; }

		/**
		 * @function : Get the total number of reply packets has recved
		 */
		inline std::size_t total_recv() { return this->total_recv_; }

		/**
		 * @function : Get the packet loss probability (loss rate)
		 */
		inline double plp()
		{
			if (this->total_send_ == static_cast<std::size_t>(0))
				return 0.0;
			return (((double)(total_send_ - total_recv_)) / (double)total_send_ * 100.0);
		}

		/**
		 * @function : Get the average duration of elapsed when recved reply packets
		 */
		inline std::chrono::steady_clock::duration avg_lag()
		{
			if (this->total_recv_ == static_cast<std::size_t>(0))
				return std::chrono::steady_clock::duration(0);
			return std::chrono::steady_clock::duration(
				long((double)this->total_time_.count() / (double)this->total_recv_));
		}

	protected:
		bool _do_start(std::string_view host)
		{
			state_t expected = state_t::stopped;
			if (!this->state_.compare_exchange_strong(expected, state_t::starting))
			{
				set_last_error(asio::error::already_started);
				return false;
			}

			try
			{
				clear_last_error();

				this->iopool_.start();

				if (this->iopool_.is_stopped())
				{
					set_last_error(asio::error::shut_down);
					return false;
				}

				this->seq_ = 0;
				this->total_send_ = 0;
				this->total_recv_ = 0;
				this->total_time_ = std::chrono::steady_clock::duration{ 0 };
#if defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS_)
				this->identifier_ = static_cast<unsigned short>(::GetCurrentProcessId());
#else
				this->identifier_ = static_cast<unsigned short>(::getpid());
#endif
				asio::ip::icmp::resolver resolver(this->io_.context());
				this->destination_ = *resolver.resolve(host, "").begin();

				this->socket_.close(ec_ignore);
				this->socket_.open(this->destination_.protocol());

				this->derived()._fire_init();

				this->derived()._handle_start(error_code{});

				return (this->is_started());
			}
			catch (system_error & e)
			{
				this->derived()._handle_start(e.code());
			}
			return false;
		}

		void _handle_start(error_code ec)
		{
			try
			{
				// Whether the startup succeeds or fails, always call fire_start notification
				state_t expected = state_t::starting;
				if (!ec)
					if (!this->state_.compare_exchange_strong(expected, state_t::started))
						ec = asio::error::operation_aborted;

				set_last_error(ec);

				this->derived()._fire_start(ec);

				expected = state_t::started;
				if (!ec)
					if (!this->state_.compare_exchange_strong(expected, state_t::started))
						asio::detail::throw_error(asio::error::operation_aborted);

				asio::detail::throw_error(ec);

				asio::post(this->io_.strand(), [this]()
				{
					this->buffer_.consume(this->buffer_.size());
					this->derived()._post_send();
					this->derived()._post_recv();
				});
			}
			catch (system_error & e)
			{
				set_last_error(e);
				this->derived()._do_stop(e.code());
			}
		}

		inline void _do_stop(const error_code& ec)
		{
			state_t expected = state_t::starting;
			if (this->state_.compare_exchange_strong(expected, state_t::stopping))
				return this->derived()._post_stop(ec, this->derived().selfptr(), expected);

			expected = state_t::started;
			if (this->state_.compare_exchange_strong(expected, state_t::stopping))
				return this->derived()._post_stop(ec, this->derived().selfptr(), expected);
		}

		inline void _post_stop(const error_code& ec, std::shared_ptr<derived_t> self_ptr, state_t old_state)
		{
			// asio don't allow operate the same socket in multi thread,
			// if you close socket in one thread and another thread is 
			// calling socket's async_... function,it will crash.so we
			// must care for operate the socket.when need close the 
			// socket ,we use the strand to post a event,make sure the
			// socket's close operation is in the same thread.
			asio::post(this->io_.strand(), [this, ec, this_ptr = std::move(self_ptr), old_state]()
			{
				detail::ignore_unused(old_state);

				set_last_error(ec);

				state_t expected = state_t::stopping;
				if (this->state_.compare_exchange_strong(expected, state_t::stopped))
				{
					this->derived()._fire_stop(ec);

					// call CRTP polymorphic stop
					this->derived()._handle_stop(ec, std::move(this_ptr));
				}
				else
				{
					ASIO2_ASSERT(false);
				}
			});
		}

		inline void _handle_stop(const error_code& ec, std::shared_ptr<derived_t> this_ptr)
		{
			detail::ignore_unused(ec, this_ptr);

			// close user custom timers
			this->stop_all_timers();

			// close all posted timed tasks
			this->stop_all_timed_tasks();

			// close all async_events
			this->notify_all_events();

			// destroy user data, maybe the user data is self shared_ptr,
			// if don't destroy it, will cause loop refrence.
			this->user_data_.reset();

			this->timer_.cancel(ec_ignore);

			// Call close,otherwise the _handle_recv will never return
			this->socket_.close(ec_ignore);
		}

		void _post_send()
		{
			// if ncount_ is equal to max, infinite send
			if (this->ncount_ != std::size_t(-1))
			{
				if (this->total_send_ >= this->ncount_)
				{
					this->derived()._do_stop(asio::error::eof);
					return;
				}
			}

			// Create an ICMP header for an echo request.
			icmp_header req;
			req.type(icmp_header::echo_request);
			req.code(0);
			req.identifier(this->identifier_);
			req.sequence_number(++seq_);
			compute_checksum(req, this->body_.begin(), this->body_.end());

			// Encode the request packet.
			asio::streambuf buffer;
			std::ostream os(&buffer);
			os << req << this->body_;

			// Send the request.
			error_code ec;
			this->time_sent_ = std::chrono::steady_clock::now();
			this->socket_.send_to(buffer.data(), this->destination_, 0, ec);
			set_last_error(ec);
			if (!ec)
				this->total_send_++;

			// Wait up to five seconds for a reply.
			this->replies_ = 0;
			this->timer_.expires_after(this->timeout_);
			this->timer_.async_wait(asio::bind_executor(this->io_.strand(),
				make_allocator(this->wallocator_,
					std::bind(&self::_handle_timer, this, std::placeholders::_1))));
		}

		void _handle_timer(const error_code & ec)
		{
			detail::ignore_unused(ec);

			if (this->replies_ == 0)
			{
				detail::condition_wrap<void> dummy{};
				this->rep_.lag = std::chrono::steady_clock::duration(-1);
				this->derived()._fire_recv(this->rep_, dummy);
			}

			// Requests must be sent no less than one second apart.
			if (this->is_started())
			{
				this->timer_.expires_after(this->interval_);
				this->timer_.async_wait(asio::bind_executor(this->io_.strand(),
					make_allocator(this->wallocator_,
						std::bind(&self::_post_send, this))));
			}
		}

		void _post_recv()
		{
			if (!this->is_started())
				return;
			try
			{
				// Wait for a reply. We prepare the buffer to receive up to 64KB.
				this->socket_.async_receive(this->buffer_.prepare(this->buffer_.pre_size()),
					asio::bind_executor(this->io_.strand(), make_allocator(this->rallocator_,
						std::bind(&self::_handle_recv, this,
							std::placeholders::_1, std::placeholders::_2))));
			}
			catch (system_error & e)
			{
				set_last_error(e);
				this->derived()._do_stop(e.code());
			}
		}

		void _handle_recv(const error_code& ec, std::size_t bytes_recvd)
		{
			set_last_error(ec);

			if (ec == asio::error::operation_aborted)
			{
				this->derived()._do_stop(ec);
				return;
			}

			if (ec && bytes_recvd == 0)
			{
				this->derived()._do_stop(ec);
				return;
			}

			if (!this->is_started())
				return;

			// The actual number of bytes received is committed to the buffer so that we
			// can extract it using a std::istream object.
			this->buffer_.commit(bytes_recvd);

			// Decode the reply packet.
			std::istream is(&this->buffer_);
			ipv4_header& ipv4_hdr = this->rep_.base_ipv4();
			icmp_header& icmp_hdr = this->rep_.base_icmp();
			is >> ipv4_hdr >> icmp_hdr;

			ASIO2_ASSERT(ipv4_hdr.total_length() == bytes_recvd);

			// We can receive all ICMP packets received by the host, so we need to
			// filter out only the echo replies that match the our identifier and
			// expected sequence number.
			if (is
				&& icmp_hdr.type() == icmp_header::echo_reply
				&& icmp_hdr.identifier() == this->identifier_
				&& icmp_hdr.sequence_number() == this->seq_)
			{
				// If this is the first reply, interrupt the five second timeout.
				if (this->replies_++ == 0)
					this->timer_.cancel(ec_ignore);

				this->total_recv_++;
				this->rep_.lag = std::chrono::steady_clock::now() - this->time_sent_;
				this->total_time_ += this->rep_.lag;

				detail::condition_wrap<void> dummy{};
				this->derived()._fire_recv(this->rep_, dummy);
			}

			// Discard any data already in the buffer.
			this->buffer_.consume(this->buffer_.size());

			this->derived()._post_recv();
		}

		inline void _fire_init()
		{
			this->listener_.notify(event_type::init);
		}

		inline void _fire_start(error_code ec)
		{
			this->listener_.notify(event_type::start, ec);
		}

		inline void _fire_stop(error_code ec)
		{
			this->listener_.notify(event_type::stop, ec);
		}

		template<typename MatchCondition>
		inline void _fire_recv(icmp_rep& rep, condition_wrap<MatchCondition>& condition)
		{
			detail::ignore_unused(condition);

			this->listener_.notify(event_type::recv, rep);
		}

	public:
		/**
		 * @function : get the buffer object refrence
		 */
		inline buffer_wrap<buffer_type> & buffer() { return this->buffer_; }
		/**
		 * @function : get the io object refrence
		 */
		inline io_t & io() { return this->io_; }

	protected:
		/**
		 * @function : get the recv/read allocator object refrence
		 */
		inline auto & rallocator() { return this->rallocator_; }
		/**
		 * @function : get the timer/post allocator object refrence
		 */
		inline auto & wallocator() { return this->wallocator_; }

		inline listener_t                 & listener() { return this->listener_; }
		inline std::atomic<state_t>       & state()    { return this->state_;    }
		inline std::shared_ptr<derived_t>   selfptr()  { return std::shared_ptr<derived_t>{}; }

	protected:
		/// socket 
		socket_type                                 socket_;

		/// The memory to use for handler-based custom memory allocation. used fo recv/read.
		handler_memory<>                            rallocator_;

		/// The memory to use for handler-based custom memory allocation. used fo timer/post.
		handler_memory<size_op<>, std::true_type>   wallocator_;

		/// listener
		listener_t                                  listener_;

		/// The io (include io_context and strand) used to handle the accept event.
		io_t                                      & io_;

		/// buffer
		buffer_wrap<buffer_type>                    buffer_;

		/// state
		std::atomic<state_t>                        state_ = state_t::stopped;

		asio::steady_timer                          timer_;
		std::string                                 body_{ R"("Hello!" from Asio ping.)" };
		unsigned short                              seq_ = 0;
		std::size_t                                 replies_ = 0;
		icmp_rep                                    rep_;
		asio::ip::icmp::endpoint                    destination_;
		unsigned short                              identifier_;

		std::size_t                                 ncount_    { std::size_t(-1) };
		std::size_t                                 total_send_{ 0 };
		std::size_t                                 total_recv_{ 0 };
		std::chrono::steady_clock::duration         total_time_{ 0 };

		std::chrono::steady_clock::duration         timeout_  = std::chrono::seconds(3);
		std::chrono::steady_clock::duration         interval_ = std::chrono::seconds(1);
		std::chrono::steady_clock::time_point       time_sent_;
	};
}

namespace asio2
{
	/**
	 * @constructor Parameter description
	 * @param send_count Total number of echo packets you want to send
	 * send_count equals -1 for infinite send
	 * Other parameters should use default values.
	 */
	class ping : public detail::ping_impl_t<ping, detail::template_args_icmp>
	{
	public:
		using ping_impl_t<ping, detail::template_args_icmp>::ping_impl_t;
	};
}

#endif // !__ASIO2_PING_HPP__
