/*
 * COPYRIGHT (C) 2017-2019, zhllxt
 *
 * author   : zhllxt
 * email    : 37792738@qq.com
 *
 * Distributed under the GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007
 * (See accompanying file LICENSE or see <http://www.gnu.org/licenses/>)
 */

#ifndef __ASIO2_INI_HPP__
#define __ASIO2_INI_HPP__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <cstring>
#include <cctype>
#include <cstdarg>
#include <clocale>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include <memory>
#include <string>
#include <locale>
#include <string_view>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <fstream>
#include <sstream>
#include <type_traits>
#include <system_error>
#include <limits>
#include <algorithm>
#include <tuple>
#include <filesystem>

#if defined(__unix__) || defined(__linux__)
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <dirent.h>
#elif defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS_) || defined(WIN32)
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#include <Windows.h>
	#include <tchar.h>
	#include <io.h>
	#include <direct.h>
#endif

/*
 * mutex:
 * Linux platform needs to add -lpthread option in link libraries
 */

namespace asio2
{
	template<class T>
	struct convert;

	template<>
	struct convert<bool>
	{
		template<typename = void>
		inline static char ascii_tolower(char c)
		{
			return char(((static_cast<unsigned>(c) - 65U) < 26) ? c + 'a' - 'A' : c);
		}

		/**
		 * @function : Returns `true` if two strings are equal, using a case-insensitive comparison.
		 */
		template<typename = void>
		inline static bool iequals(std::string_view lhs, std::string_view rhs)
		{
			auto n = lhs.size();
			if (rhs.size() != n)
				return false;
			auto p1 = lhs.data();
			auto p2 = rhs.data();
			char a, b;
			// fast loop
			while (n--)
			{
				a = *p1++;
				b = *p2++;
				if (a != b)
					goto slow;
			}
			return true;
		slow:
			do
			{
				if (detail::ascii_tolower(a) != detail::ascii_tolower(b))
					return false;
				a = *p1++;
				b = *p2++;
			} while (n--);
			return true;
		}

		template<class ...Args>
		inline static bool stov(Args&&... args)
		{ return (!(std::stoi(std::forward<Args>(args)...) == 0)); }

		template<
			class CharT,
			class Traits = std::char_traits<CharT>,
			class Allocator = std::allocator<CharT>
		>
		inline static bool stov(std::basic_string<CharT, Traits, Allocator>&& val)
		{
			if (iequals(val, "true"))
				return true;
			if (iequals(val, "false"))
				return false;
			return (!(std::stoi(val) == 0));
		}
	};

	template<>
	struct convert<char>
	{
		template<class ...Args>
		inline static char stov(Args&&... args)
		{ return static_cast<char>(std::stoi(std::forward<Args>(args)...)); }
	};

	template<>
	struct convert<unsigned char>
	{
		template<class ...Args>
		inline static unsigned char stov(Args&&... args)
		{ return static_cast<unsigned char>(std::stoul(std::forward<Args>(args)...)); }
	};

	template<>
	struct convert<short>
	{
		template<class ...Args>
		inline static short stov(Args&&... args)
		{ return static_cast<short>(std::stoi(std::forward<Args>(args)...)); }
	};

	template<>
	struct convert<unsigned short>
	{
		template<class ...Args>
		inline static unsigned short stov(Args&&... args)
		{ return static_cast<unsigned short>(std::stoul(std::forward<Args>(args)...)); }
	};

	template<>
	struct convert<int>
	{
		template<class ...Args>
		inline static int stov(Args&&... args)
		{ return std::stoi(std::forward<Args>(args)...); }
	};

	template<>
	struct convert<unsigned int>
	{
		template<class ...Args>
		inline static unsigned int stov(Args&&... args)
		{ return static_cast<unsigned int>(std::stoul(std::forward<Args>(args)...)); }
	};

	template<>
	struct convert<long>
	{
		template<class ...Args>
		inline static long stov(Args&&... args)
		{ return std::stol(std::forward<Args>(args)...); }
	};

	template<>
	struct convert<unsigned long>
	{
		template<class ...Args>
		inline static unsigned long stov(Args&&... args)
		{ return std::stoul(std::forward<Args>(args)...); }
	};

	template<>
	struct convert<long long>
	{
		template<class ...Args>
		inline static long long stov(Args&&... args)
		{ return std::stoll(std::forward<Args>(args)...); }
	};

	template<>
	struct convert<unsigned long long>
	{
		template<class ...Args>
		inline static unsigned long long stov(Args&&... args)
		{ return std::stoull(std::forward<Args>(args)...); }
	};

	template<>
	struct convert<float>
	{
		template<class ...Args>
		inline static float stov(Args&&... args)
		{ return std::stof(std::forward<Args>(args)...); }
	};

	template<>
	struct convert<double>
	{
		template<class ...Args>
		inline static double stov(Args&&... args)
		{ return std::stod(std::forward<Args>(args)...); }
	};

	template<>
	struct convert<long double>
	{
		template<class ...Args>
		inline static long double stov(Args&&... args)
		{ return std::stold(std::forward<Args>(args)...); }
	};

	template<class CharT, class Traits, class Allocator>
	struct convert<std::basic_string<CharT, Traits, Allocator>>
	{
		template<class ...Args>
		inline static std::basic_string<CharT, Traits, Allocator> stov(Args&&... args)
		{ return std::basic_string<CharT, Traits, Allocator>(std::forward<Args>(args)...); }
	};

	template<class CharT, class Traits>
	struct convert<std::basic_string_view<CharT, Traits>>
	{
		template<class ...Args>
		inline static std::basic_string_view<CharT, Traits> stov(Args&&... args)
		{ return std::basic_string_view<CharT, Traits>(std::forward<Args>(args)...); }
	};
}

namespace asio2
{
	namespace detail
	{
		template<typename, typename = void>
		struct is_fstream : std::false_type {};

		template<typename T>
		struct is_fstream<T, std::void_t<typename T::char_type, typename T::traits_type,
			typename std::enable_if_t<std::is_same_v<T,
			std::basic_fstream<typename T::char_type, typename T::traits_type>>>>> : std::true_type {};

		template<class T>
		inline constexpr bool is_fstream_v = is_fstream<std::remove_cv_t<std::remove_reference_t<T>>>::value;

		template<typename, typename = void>
		struct is_ifstream : std::false_type {};

		template<typename T>
		struct is_ifstream<T, std::void_t<typename T::char_type, typename T::traits_type,
			typename std::enable_if_t<std::is_same_v<T,
			std::basic_ifstream<typename T::char_type, typename T::traits_type>>>>> : std::true_type {};

		template<class T>
		inline constexpr bool is_ifstream_v = is_ifstream<std::remove_cv_t<std::remove_reference_t<T>>>::value;

		template<typename, typename = void>
		struct is_ofstream : std::false_type {};

		template<typename T>
		struct is_ofstream<T, std::void_t<typename T::char_type, typename T::traits_type,
			typename std::enable_if_t<std::is_same_v<T,
			std::basic_ofstream<typename T::char_type, typename T::traits_type>>>>> : std::true_type {};

		template<class T>
		inline constexpr bool is_ofstream_v = is_ofstream<std::remove_cv_t<std::remove_reference_t<T>>>::value;

		template<class T>
		inline constexpr bool is_file_stream_v = is_fstream_v<T> || is_ifstream_v<T> || is_ofstream_v<T>;
	}

	namespace detail
	{
		template<class Stream>
		class basic_file_ini_impl : public Stream
		{
		public:
			template<class ...Args>
			basic_file_ini_impl(Args&&... args)
			{
				std::ios_base::openmode mode{};

				if constexpr /**/ (sizeof...(Args) == 0)
				{
#if defined(__unix__) || defined(__linux__)
					filepath_.resize(PATH_MAX);
					readlink("/proc/self/exe", (char *)filepath_.data(), PATH_MAX);
#elif defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS_) || defined(WIN32)
					filepath_.resize(MAX_PATH);
					filepath_.resize(::GetModuleFileNameA(NULL, (LPSTR)filepath_.data(), MAX_PATH));
#endif
					auto pos = filepath_.rfind('.');
					if (pos != std::string::npos)
					{
						filepath_.erase(pos);
					}

					filepath_ += ".ini";
				}
				else if constexpr (sizeof...(Args) == 1)
				{
					filepath_ = std::move(std::get<0>(std::make_tuple(std::forward<Args>(args)...)));
				}
				else if constexpr (sizeof...(Args) == 2)
				{
					auto t = std::make_tuple(std::forward<Args>(args)...);

					filepath_ = std::move(std::get<0>(t));
					mode |= std::get<1>(t);
				}
				else
				{
					std::ignore = true;
				}

				try
				{
					// if file is not exists, create it
					if (!std::filesystem::exists(filepath_))
					{
						Stream f(filepath_, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
					}

					if constexpr /**/ (detail::is_fstream_v<Stream>)
					{
						mode |= std::ios_base::in | std::ios_base::out | std::ios_base::binary;
					}
					else if constexpr (detail::is_ifstream_v<Stream>)
					{
						mode |= std::ios_base::in | std::ios_base::binary;
					}
					else if constexpr (detail::is_ofstream_v<Stream>)
					{
						mode |= std::ios_base::out | std::ios_base::binary;
					}
					else
					{
						mode |= std::ios_base::in | std::ios_base::out | std::ios_base::binary;
					}

					Stream::open(filepath_, mode);
				}
				catch (std::exception const&) {}
			}

			~basic_file_ini_impl()
			{
				using pos_type = typename Stream::pos_type;

				Stream::clear();
				Stream::seekg(0, std::ios::end);
				auto filesize = Stream::tellg();

				if (filesize)
				{
					pos_type spaces = pos_type(0);

					do
					{
						Stream::clear();
						Stream::seekg(filesize - spaces - pos_type(1));

						char c;
						if (!Stream::get(c))
							break;

						if (c == ' ' || c == '\0')
							spaces = spaces + pos_type(1);
						else
							break;

					} while (true);

					if (spaces)
					{
						std::error_code ec;
						std::filesystem::resize_file(filepath_, filesize - spaces, ec);
					}
				}
			}

		protected:
			std::string                  filepath_;
		};

		template<class Stream>
		class basic_ini_impl : public Stream
		{
		public:
			template<class ...Args>
			basic_ini_impl(Args&&... args) : Stream(std::forward<Args>(args)...) {}
		};

		template<class... Ts>
		class basic_ini_impl<std::basic_fstream<Ts...>> : public basic_file_ini_impl<std::basic_fstream<Ts...>>
		{
		public:
			template<class ...Args>
			basic_ini_impl(Args&&... args) : basic_file_ini_impl<std::basic_fstream<Ts...>>(std::forward<Args>(args)...) {}
		};

		template<class... Ts>
		class basic_ini_impl<std::basic_ifstream<Ts...>> : public basic_file_ini_impl<std::basic_ifstream<Ts...>>
		{
		public:
			template<class ...Args>
			basic_ini_impl(Args&&... args) : basic_file_ini_impl<std::basic_ifstream<Ts...>>(std::forward<Args>(args)...) {}
		};

		template<class... Ts>
		class basic_ini_impl<std::basic_ofstream<Ts...>> : public basic_file_ini_impl<std::basic_ofstream<Ts...>>
		{
		public:
			template<class ...Args>
			basic_ini_impl(Args&&... args) : basic_file_ini_impl<std::basic_ofstream<Ts...>>(std::forward<Args>(args)...) {}
		};
	}

	/**
	 * basic_ini operator class
	 */
	template<class Stream>
	class basic_ini : public detail::basic_ini_impl<Stream>
	{
	public:
		using char_type = typename Stream::char_type;
		using pos_type  = typename Stream::pos_type;
		using size_type = typename std::basic_string<char_type>::size_type;

		template<class ...Args>
		basic_ini(Args&&... args) : detail::basic_ini_impl<Stream>(std::forward<Args>(args)...)
		{
#if defined(__unix__) || defined(__linux__)
			this->endl_ = { '\n' };
#elif defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS_) || defined(WIN32)
			this->endl_ = { '\r','\n' };
#	endif
		}

	protected:
		template<class Traits = std::char_traits<char_type>, class Allocator = std::allocator<char_type>>
		bool _get(
			std::basic_string_view<char_type, Traits> sec,
			std::basic_string_view<char_type, Traits> key,
			std::basic_string<char_type, Traits, Allocator> & val)
		{
			std::shared_lock<std::shared_mutex> guard(this->mutex_);
			Stream::clear();
			if (Stream::operator bool())
			{
				std::basic_string<char_type, Traits, Allocator> line;
				std::basic_string<char_type, Traits, Allocator> s, k, v;
				pos_type posg;

				Stream::seekg(0, std::ios::beg);

				char ret;
				while ((ret = this->_getline(line, s, k, v, posg)) != 'n')
				{
					switch (ret)
					{
					case 'a':break;
					case 's':
						if (s == sec)
						{
							do
							{
								ret = this->_getline(line, s, k, v, posg);
								if (ret == 'k' && k == key)
								{
									val = std::move(v);
									return true;
								}
							} while (ret == 'k' || ret == 'a' || ret == 'o');

							return false;
						}
						break;
					case 'k':
						if (s == sec)
						{
							if (k == key)
							{
								val = std::move(v);
								return true;
							}
						}
						break;
					case 'o':break;
					default:break;
					}
				}
			}
			return false;
		}

	public:
		template<class R, class Sec, class Key, class Traits = std::char_traits<char_type>>
		inline typename std::enable_if_t<std::is_same_v<decltype(
			std::basic_string_view<char_type, Traits>(std::declval<Sec>()),
			std::basic_string_view<char_type, Traits>(std::declval<Key>()),
			std::true_type()), std::true_type>, R>
			get(const Sec& sec, const Key& key, R default_val = R())
		{
			return this->get<R>(
				std::basic_string_view<char_type, Traits>(sec),
				std::basic_string_view<char_type, Traits>(key),
				default_val);
		}

		template<class R, class Traits = std::char_traits<char_type>,
			class Allocator = std::allocator<char_type>>
		inline typename std::enable_if_t<std::is_same_v<decltype(
			asio2::convert<R>::stov(std::basic_string<char_type, Traits, Allocator>()),
			std::true_type()), std::true_type>, R>
			get(std::basic_string_view<char_type, Traits> sec,
				std::basic_string_view<char_type, Traits> key, R default_val = R())
		{
			try
			{
				std::basic_string<char_type, Traits, Allocator> val;
				if (this->_get(sec, key, val))
					default_val = asio2::convert<R>::stov(std::move(val));
			}
			catch (std::exception &) {}
			return default_val;
		}

		template<class R, class Sec, class Key, class Traits = std::char_traits<char_type>>
		inline typename std::enable_if_t<std::is_same_v<decltype(
			std::basic_string_view<char_type, Traits>(std::declval<Sec>()),
			std::basic_string_view<char_type, Traits>(std::declval<Key>()),
			std::true_type()), std::true_type>, R>
			get(const Sec& sec, const Key& key, std::error_code & ec, R default_val = R())
		{
			return this->get<R>(
				std::basic_string_view<char_type, Traits>(sec),
				std::basic_string_view<char_type, Traits>(key),
				ec, default_val);
		}

		template<class R, class Traits = std::char_traits<char_type>,
			class Allocator = std::allocator<char_type>>
		inline typename std::enable_if_t<std::is_same_v<decltype(
			asio2::convert<R>::stov(std::basic_string<char_type, Traits, Allocator>()),
			std::true_type()), std::true_type>, R>
			get(std::basic_string_view<char_type, Traits> sec,
				std::basic_string_view<char_type, Traits> key,
				std::error_code & ec, R default_val = R())
		{
			try
			{
				std::basic_string<char_type, Traits, Allocator> val;
				if (this->_get(sec, key, val))
					default_val = asio2::convert<R>::stov(std::move(val));
			}
			catch (std::invalid_argument &)
			{
				ec = std::make_error_code(std::errc::invalid_argument);
			}
			catch (std::out_of_range &)
			{
				ec = std::make_error_code(std::errc::result_out_of_range);
			}
			catch (std::exception &)
			{
				ec = std::make_error_code(std::errc::invalid_argument);
			}
			return default_val;
		}

		template<class Sec, class Key, class Val, class Traits = std::char_traits<char_type>>
		inline typename std::enable_if_t<std::is_same_v<decltype(
			std::basic_string_view<char_type, Traits>(std::declval<Sec>()),
			std::basic_string_view<char_type, Traits>(std::declval<Key>()),
			std::basic_string_view<char_type, Traits>(std::declval<Val>()),
			std::true_type()), std::true_type>, bool>
			set(const Sec& sec, const Key& key, const Val& val)
		{
			return this->set(
				std::basic_string_view<char_type, Traits>(sec),
				std::basic_string_view<char_type, Traits>(key),
				std::basic_string_view<char_type, Traits>(val));
		}

		template<class Sec, class Key, class Val, class Traits = std::char_traits<char_type>>
		inline typename std::enable_if_t<std::is_same_v<decltype(
			std::basic_string_view<char_type, Traits>(std::declval<Sec>()),
			std::basic_string_view<char_type, Traits>(std::declval<Key>()),
			std::to_string(std::declval<Val>()),
			std::true_type()), std::true_type>, bool>
			set(const Sec& sec, const Key& key, Val val)
		{
			std::basic_string<char_type, Traits> v = std::to_string(val);
			return this->set(
				std::basic_string_view<char_type, Traits>(sec),
				std::basic_string_view<char_type, Traits>(key),
				std::basic_string_view<char_type, Traits>(v));
		}

		template<class Traits = std::char_traits<char_type>, class Allocator = std::allocator<char_type>>
		bool set(
			std::basic_string_view<char_type, Traits> sec,
			std::basic_string_view<char_type, Traits> key,
			std::basic_string_view<char_type, Traits> val)
		{
			std::unique_lock<std::shared_mutex> guard(this->mutex_);
			Stream::clear();
			if (Stream::operator bool())
			{
				std::basic_string<char_type, Traits, Allocator> line;
				std::basic_string<char_type, Traits, Allocator> s, k, v;
				pos_type posg = 0;
				char ret;

				auto update_v = [&]() -> bool
				{
					try
					{
						if (val != v)
						{
							Stream::clear();
							Stream::seekg(0, std::ios::end);
							auto filesize = Stream::tellg();

							std::basic_string<char_type, Traits, Allocator> content;
							auto pos = line.find_first_of('=');
							++pos;
							while (pos < line.size() && (line[pos] == ' ' || line[pos] == '\t'))
								++pos;
							content += line.substr(0, pos);
							content += val;
							content += this->endl_;

							int pos_diff = int(line.size() + 1 - content.size());

							Stream::clear();
							Stream::seekg(posg + pos_type(line.size() + 1));

							int remain = int(filesize - (posg + pos_type(line.size() + 1)));
							if (remain > 0)
							{
								content.resize(size_type(content.size() + remain));
								Stream::read(content.data() + content.size() - remain, remain);
							}

							if (pos_diff > 0) content.append(pos_diff, ' ');

							while (!content.empty() &&
								(pos_type(content.size()) + posg > filesize) &&
								content.back() == ' ')
							{
								content.erase(content.size() - 1);
							}

							Stream::clear();
							Stream::seekp(posg);
							//*this << content;
							Stream::write(content.data(), content.size());
							Stream::flush();
						}
						return true;
					}
					catch (std::exception &) {}
					return false;
				};

				Stream::seekg(0, std::ios::beg);

				while ((ret = this->_getline(line, s, k, v, posg)) != 'n')
				{
					switch (ret)
					{
					case 'a':break;
					case 's':
						if (s == sec)
						{
							do
							{
								ret = this->_getline(line, s, k, v, posg);
								if (ret == 'k' && k == key)
								{
									return update_v();
								}
							} while (ret == 'k' || ret == 'a' || ret == 'o');

							// can't find the key, add a new key
							std::basic_string<char_type, Traits, Allocator> content;

							if (posg == pos_type(-1))
							{
								Stream::clear();
								Stream::seekg(0, std::ios::end);
								posg = Stream::tellg();
							}

							content += this->endl_;
							content += key;
							content += '=';
							content += val;
							content += this->endl_;

							Stream::clear();
							Stream::seekg(0, std::ios::end);
							auto filesize = Stream::tellg();

							Stream::clear();
							Stream::seekg(posg);

							int remain = int(filesize - posg);
							if (remain > 0)
							{
								content.resize(size_type(content.size() + remain));
								Stream::read(content.data() + content.size() - remain, remain);
							}

							while (!content.empty() &&
								(pos_type(content.size()) + posg > filesize) &&
								content.back() == ' ')
							{
								content.erase(content.size() - 1);
							}

							Stream::clear();
							Stream::seekp(posg);
							//*this << content;
							Stream::write(content.data(), content.size());
							Stream::flush();

							return true;
						}
						break;
					case 'k':
						if (s == sec)
						{
							if (k == key)
							{
								return update_v();
							}
						}
						break;
					case 'o':break;
					default:break;
					}
				}

				// can't find the sec and key, add a new sec and key.
				std::basic_string<char_type, Traits, Allocator> content;

				Stream::clear();
				Stream::seekg(0, std::ios::end);
				auto filesize = Stream::tellg();
				content.resize(size_type(filesize));

				Stream::clear();
				Stream::seekg(0, std::ios::beg);
				Stream::read(content.data(), content.size());

				if (!content.empty() && content.back() == '\n') content.erase(content.size() - 1);
				if (!content.empty() && content.back() == '\r') content.erase(content.size() - 1);

				std::basic_string<char_type, Traits, Allocator> buffer;

				if (!sec.empty())
				{
					buffer += '[';
					buffer += sec;
					buffer += ']';
					buffer += this->endl_;
				}

				buffer += key;
				buffer += '=';
				buffer += val;
				buffer += this->endl_;

				if (!sec.empty())
				{
					if (content.empty())
						content = std::move(buffer);
					else
						content = content + this->endl_ + buffer;
				}
				// if the sec is empty ( mean global), must add the key at the begin.
				else
				{
					if (content.empty())
						content = std::move(buffer);
					else
						content = buffer + content;
				}

				while (!content.empty() &&
					(pos_type(content.size()) > filesize) &&
					content.back() == ' ')
				{
					content.erase(content.size() - 1);
				}

				Stream::clear();
				Stream::seekp(0, std::ios::beg);
				//*this << content;
				Stream::write(content.data(), content.size());
				Stream::flush();

				return true;
			}
			return false;
		}

	protected:
		template<class Traits = std::char_traits<char_type>, class Allocator = std::allocator<char_type>>
		char _getline(
			std::basic_string<char_type, Traits, Allocator> & line,
			std::basic_string<char_type, Traits, Allocator> & sec,
			std::basic_string<char_type, Traits, Allocator> & key,
			std::basic_string<char_type, Traits, Allocator> & val,
			pos_type & posg)
		{
			Stream::clear();
			if (Stream::good() && !Stream::eof())
			{
				posg = Stream::tellg();

				if (posg != pos_type(-1) && std::getline(*this, line, this->endl_.back()))
				{
					auto trim_line = line;

					trim_left(trim_line);
					trim_right(trim_line);

					if (trim_line.empty())
					{
						return 'o'; // other
					}

					// current line is code annotation
					if (
						(trim_line.size() > 0 && (trim_line[0] == ';' || trim_line[0] == '#' || trim_line[0] == ':'))
						||
						(trim_line.size() > 1 && trim_line[0] == '/' && trim_line[1] == '/')
						)
					{
						return 'a'; // annotation
					}

					auto pos1 = trim_line.find_first_of('[');
					auto pos2 = trim_line.find_first_of(']');

					// current line is section
					if (
						pos1 == 0
						&&
						pos2 != std::basic_string<char_type, Traits, Allocator>::npos
						&&
						pos2 > pos1
						)
					{
						sec = trim_line.substr(pos1 + 1, pos2 - pos1 - 1);

						trim_left(sec);
						trim_right(sec);

						return 's'; // section
					}

					auto sep = trim_line.find_first_of('=');

					// current line is key and val
					if (sep != std::basic_string<char_type, Traits, Allocator>::npos && sep > 0)
					{
						key = trim_line.substr(0, sep);
						trim_left(key);
						trim_right(key);

						val = trim_line.substr(sep + 1);
						trim_left(val);
						trim_right(val);

						return 'k'; // kv
					}

					return 'o'; // other
				}
			}

			return 'n'; // null
		}

		template<
			class CharT,
			class Traits = std::char_traits<CharT>,
			class Allocator = std::allocator<CharT>
		>
		std::basic_string<CharT, Traits, Allocator>& trim_left(std::basic_string<CharT, Traits, Allocator>& s)
		{
			if (s.empty())
				return s;
			using size_type = typename std::basic_string<CharT, Traits, Allocator>::size_type;
			size_type pos = 0;
			for (; pos < s.size(); ++pos)
			{
				if (!std::isspace(static_cast<unsigned char>(s[pos])))
					break;
			}
			s.erase(0, pos);
			return s;
		}

		template<
			class CharT,
			class Traits = std::char_traits<CharT>,
			class Allocator = std::allocator<CharT>
		>
		std::basic_string<CharT, Traits, Allocator>& trim_right(std::basic_string<CharT, Traits, Allocator>& s)
		{
			if (s.empty())
				return s;
			using size_type = typename std::basic_string<CharT, Traits, Allocator>::size_type;
			size_type pos = s.size() - 1;
			for (; pos != size_type(-1); pos--)
			{
				if (!std::isspace(static_cast<unsigned char>(s[pos])))
					break;
			}
			s.erase(pos + 1);
			return s;
		}

	protected:
		std::shared_mutex            mutex_;

		std::basic_string<char_type> endl_;
	};

	using ini     = basic_ini<std::fstream>;
}

#endif // !__ASIO2_INI_HPP__
