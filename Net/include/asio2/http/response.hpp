/*
 * COPYRIGHT (C) 2017-2019, zhllxt
 *
 * author   : zhllxt
 * email    : 37792738@qq.com
 * 
 * Distributed under the GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
 * (See accompanying file LICENSE or see <http://www.gnu.org/licenses/>)
 */

#ifndef __ASIO2_HTTP_RESPONSE_IMPL_HPP__
#define __ASIO2_HTTP_RESPONSE_IMPL_HPP__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#ifdef EXPERIMENT_FILESYS
#define STDFILESYS std::experimental::filesystem
#include <experimental/filesystem>
#else
#define STDFILESYS std::filesystem
#include <experimental/filesystem>
#endif


#include <asio2/base/component/user_data_cp.hpp>

#include <asio2/http/detail/flex_body.hpp>
#include <asio2/http/detail/http_util.hpp>

#ifdef BEAST_HEADER_ONLY
namespace beast::http
#else
namespace boost::beast::http
#endif
{
	class response_defer
	{
	public:
		response_defer(std::function<void()> cb) : cb_(std::move(cb))
		{
		}
		~response_defer()
		{
			if (cb_) { cb_(); }
		}

	protected:
		std::function<void()> cb_;
	};
}

namespace asio2::detail
{
	ASIO2_CLASS_FORWARD_DECLARE_BASE;
	ASIO2_CLASS_FORWARD_DECLARE_TCP_BASE;
	ASIO2_CLASS_FORWARD_DECLARE_TCP_CLIENT;
	ASIO2_CLASS_FORWARD_DECLARE_TCP_SESSION;

	template<bool isRequest, class Body, class Fields = http::fields>
	class http_response_impl_t
		: public http::message<isRequest, Body, Fields>
#ifndef ASIO2_DISABLE_HTTP_RESPONSE_USER_DATA_CP
		, public user_data_cp<http_response_impl_t<isRequest, Body, Fields>>
#endif
	{
		ASIO2_CLASS_FRIEND_DECLARE_BASE;
		ASIO2_CLASS_FRIEND_DECLARE_TCP_BASE;
		ASIO2_CLASS_FRIEND_DECLARE_TCP_CLIENT;
		ASIO2_CLASS_FRIEND_DECLARE_TCP_SESSION;

	public:
		using self = http_response_impl_t<isRequest, Body, Fields>;
		using super = http::message<isRequest, Body, Fields>;
		using header_type = typename super::header_type;
		using body_type = typename super::body_type;

	public:
		/**
		 * @constructor
		 */
		template<typename... Args>
		explicit http_response_impl_t(Args&&... args)
			: super(std::forward<Args>(args)...)
		{
		}

		http_response_impl_t(const http_response_impl_t& o)
		{
			this->base() = o.base();
			this->root_directory_ = o.root_directory_;
			this->defer_callback_ = o.defer_callback_;
			this->defer_guard_    = o.defer_guard_;
		}

		http_response_impl_t(http_response_impl_t&& o)
		{
			this->base() = std::move(o.base());
			this->root_directory_ = o.root_directory_;
			this->defer_callback_ = o.defer_callback_;
			this->defer_guard_    = o.defer_guard_;
		}

		self& operator=(const http_response_impl_t& o)
		{
			this->base() = o.base();
			this->root_directory_ = o.root_directory_;
			this->defer_callback_ = o.defer_callback_;
			this->defer_guard_    = o.defer_guard_;
			return *this;
		}

		self& operator=(http_response_impl_t&& o)
		{
			this->base() = std::move(o.base());
			this->root_directory_ = o.root_directory_;
			this->defer_callback_ = o.defer_callback_;
			this->defer_guard_    = o.defer_guard_;
			return *this;
		}

		template<class BodyT = Body>
		http_response_impl_t(const http::message<isRequest, BodyT, Fields>& rep)
		{
			this->base() = rep;
		}

		template<class BodyT = Body>
		http_response_impl_t(http::message<isRequest, BodyT, Fields>&& rep)
		{
			this->base() = std::move(rep);
		}

		template<class BodyT = Body>
		self& operator=(const http::message<isRequest, BodyT, Fields>& rep)
		{
			this->base() = rep;
			return *this;
		}

		template<class BodyT = Body>
		self& operator=(http::message<isRequest, BodyT, Fields>&& rep)
		{
			this->base() = std::move(rep);
			return *this;
		}

		//-------------------------------------------------

		http_response_impl_t(const http::message<isRequest, http::string_body, Fields>& rep)
		{
			this->base().base() = rep.base();
			this->body().text() = rep.body();
			this->prepare_payload();
		}

		http_response_impl_t(http::message<isRequest, http::string_body, Fields>&& rep)
		{
			this->base().base() = std::move(rep.base());
			this->body().text() = std::move(rep.body());
			this->prepare_payload();
		}

		self& operator=(const http::message<isRequest, http::string_body, Fields>& rep)
		{
			this->base().base() = rep.base();
			this->body().text() = rep.body();
			this->prepare_payload();
			return *this;
		}

		self& operator=(http::message<isRequest, http::string_body, Fields>&& rep)
		{
			this->base().base() = std::move(rep.base());
			this->body().text() = std::move(rep.body());
			this->prepare_payload();
			return *this;
		}

		//-------------------------------------------------

		http_response_impl_t(const http::message<isRequest, http::file_body, Fields>& rep)
		{
			this->base().base() = rep.base();
			this->body().file() = rep.body();
			this->prepare_payload();
		}

		http_response_impl_t(http::message<isRequest, http::file_body, Fields>&& rep)
		{
			this->base().base() = std::move(rep.base());
			this->body().file() = std::move(rep.body());
			this->prepare_payload();
		}

		self& operator=(const http::message<isRequest, http::file_body, Fields>& rep)
		{
			this->base().base() = rep.base();
			this->body().file() = rep.body();
			this->prepare_payload();
			return *this;
		}

		self& operator=(http::message<isRequest, http::file_body, Fields>&& rep)
		{
			this->base().base() = std::move(rep.base());
			this->body().file() = std::move(rep.body());
			this->prepare_payload();
			return *this;
		}

		/**
		 * @destructor
		 */
		~http_response_impl_t()
		{
		}

		/// Returns the base portion of the message
		inline super const& base() const
		{
			return *this;
		}

		/// Returns the base portion of the message
		inline super& base()
		{
			return *this;
		}

		inline void reset()
		{
			static_cast<super&>(*this) = {};

			this->result(http::status::unknown);
		}

		/**
		 * @function : set the root directory where we load the files.
		 */
		inline self& root_directory(STDFILESYS::path path)
		{
			this->root_directory_ = std::move(path);
			return *this;
		}
		/**
		 * @function : get the root directory where we load the files.
		 */
		inline const STDFILESYS::path& root_directory()
		{
			return this->root_directory_;
		}

		inline std::shared_ptr<http::response_defer> defer()
		{
			this->defer_guard_ = std::make_shared<http::response_defer>(this->defer_callback_);
			return this->defer_guard_;
		}

	public:
		/**
		 * @function : Respond to http request with plain text content
		 * @param : content - the response body, it's usually a simple string,
		 * and the content-type is "text/plain" by default.
		 */
		inline self& fill_text(std::string content, http::status result = http::status::ok,
			std::string_view mimetype = "text/plain", unsigned version = 11)
		{
			// must clear file_body
			this->body().file().close();

			this->set(http::field::server, BEAST_VERSION_STRING);
			this->set(http::field::content_type, mimetype.empty() ? "text/plain" : mimetype);

			this->result(result);
			this->version(version < 10 ? 11 : version);

			this->body().text() = std::move(content);
			this->prepare_payload();

			return (*this);
		}

		/**
		 * @function : Respond to http request with json content
		 */
		inline self& fill_json(std::string content, http::status result = http::status::ok,
			std::string_view mimetype = "application/json", unsigned version = 11)
		{
			return this->fill_text(std::move(content), result,
				mimetype.empty() ? "application/json" : mimetype, version);
		}

		/**
		 * @function : Respond to http request with html content
		 * @param : content - the response body, may be a plain text string, or a stardand
		 * <html>...</html> string, it's just that the content-type is "text/html" by default.
		 */
		inline self& fill_html(std::string content, http::status result = http::status::ok,
			std::string_view mimetype = "text/html", unsigned version = 11)
		{
			return this->fill_text(std::move(content), result,
				mimetype.empty() ? "text/html" : mimetype, version);
		}

		/**
		 * @function : Respond to http request with pre-prepared error page content
		 * Generated a standard html error page automatically use the status coe 'result',
		 * like <html>...</html>, and the content-type is "text/html" by default.
		 */
		inline self& fill_page(http::status result, std::string desc = {},
			std::string_view mimetype = "text/html", unsigned version = 11)
		{
			return this->fill_text(http::error_page(result, std::move(desc)), result,
				mimetype.empty() ? "text/html" : mimetype, version);
		}

		/**
		 * @function : Respond to http request with local file
		 */
		inline self& fill_file(const STDFILESYS::path& path,
			http::status result = http::status::ok, unsigned version = 11)
		{
			// Build the path to the requested file
			STDFILESYS::path filepath = root_directory_;
			filepath /= path;

			// Attempt to open the file
			
			beast::error_code ec;
			this->body().file().open(filepath.string().c_str(), beast::file_mode::scan, ec);

			// Handle the case where the file doesn't exist
			if (ec == beast::errc::no_such_file_or_directory)
				return this->fill_page(http::status::not_found, {}, {}, version);

			// Handle an unknown error
			if (ec)
				return this->fill_page(http::status::internal_server_error, ec.message(), {}, version);

			// Cache the size since we need it after the move
			auto const size = this->body().size();

			// Respond to GET request
			this->content_length(size);

			this->set(http::field::server, BEAST_VERSION_STRING);
			this->set(http::field::content_type, http::extension_to_mimetype(path.extension().string()));

			this->result(result);
			this->version(version < 10 ? 11 : version);

			return (*this);
		}

		/**
		 * @function : Returns `true` if this HTTP response's Content-Type is "multipart/form-data";
		 */
		inline bool has_multipart()
		{
			return http::has_multipart(*this);
		}

		/**
		 * @function : Get the "multipart/form-data" body content.
		 */
		inline decltype(auto) multipart()
		{
			return http::multipart(*this);
		}

	protected:
		STDFILESYS::path                    root_directory_     = STDFILESYS::current_path();

		std::function<void()>                    defer_callback_;

		std::shared_ptr<http::response_defer>    defer_guard_;
	};
}

#ifdef BEAST_HEADER_ONLY
namespace beast::http
#else
namespace boost::beast::http
#endif
{
	using response = asio2::detail::http_response_impl_t<false, http::flex_body>;
}

#endif // !__ASIO2_HTTP_RESPONSE_IMPL_HPP__
