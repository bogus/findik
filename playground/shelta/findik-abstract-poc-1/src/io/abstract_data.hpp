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

#ifndef FINDIK_IO_ABSTRACT_DATA_HPP
#define FINDIK_IO_ABSTRACT_DATA_HPP

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

namespace findik
{
	namespace io
	{
		/*!
		Abstract data encapsulator.
		\extends boost::enable_shared_from_this<abstract_data> to use boost shared pointers.
		@author H. Kerem Cevahir (shelta)
		*/
		class abstract_data :
			public boost::enable_shared_from_this<abstract_data>
		{
		public:

		protected:

		}
		
		typedef boost::shared_ptr<abstract_data> abstract_data_ptr;
	}
}

#endif

