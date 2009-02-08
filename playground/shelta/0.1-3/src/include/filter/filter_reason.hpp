/*
  Copyright (C) 2008 H. Kerem Cevahir (shelta) <findikmail@gmail.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef FINDIK_FILTER_FILTER_REASON_HPP
#define FINDIK_FILTER_FILTER_REASON_HPP

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include <string>

namespace findik
{
	namespace filter
	{
		/*!
		Filter reason type to return for denying content with a filter.
		\extends boost::enable_shared_from_this<filter_reason> to use boost shared pointers.
		@author H. Kerem Cevahir (shelta)
		*/
		class filter_reason :
			public boost::enable_shared_from_this<filter_reason>
		{
		public:
			/*!
			Factory method.
			\param code code of reason.
			\returns a new filter reason instance
			*/
			static boost::shared_ptr<filter_reason> create_reason(unsigned int code)
			{
				boost::shared_ptr<filter_reason> p(new filter_reason(code));
				return p;
			}

			/*
			Factory method.
			\param code code of reason.
			\param reason_str detail of reason.
			\returns a new filter reason instance
			*/
			static boost::shared_ptr<filter_reason> create_reason(
					unsigned int code, const std::string & reason_str)
			{
				boost::shared_ptr<filter_reason> p(new filter_reason(code, reason_str));
				return p;
			}

			/*!
			Destructor.
			*/
			~filter_reason();

			/*!
			Detail of reason.
			\returns reason details
			*/
			const std::string & reason_str();

			/*!
			Code of reason. 
			\returns reason code
			*/
			unsigned int code();

		protected:
			/*!
			Constructor.
			*/
			filter_reason(unsigned int code);

			/*!
			Constructor.
			*/
			filter_reason(unsigned int code, const std::string & reason_str);

			/*!
			Reason code.
			*/
			unsigned int code_;

			/*!
			Reason detail in a string.
			*/
			std::string reason_str_;
		};
		
		typedef boost::shared_ptr<filter_reason> filter_reason_ptr;
	}
}

#endif

