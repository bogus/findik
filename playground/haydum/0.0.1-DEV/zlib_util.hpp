#ifndef FINDIK_IO_ZLIB_UTIL_HPP
#define FINDIK_IO_ZLIB_UTIL_HPP

#include "findik_config.hpp"

#include <zlib.h>

#include <string>

#include <iostream>

namespace findik {
	namespace io {

		int zlib_inflate(const std::string & src_, std::string & dest_) {

			int ret = 0;
		    unsigned int have = 0;
			z_stream strm;

			dest_.clear();

			unsigned char buffer_[__FC_ZLIB_BUFFER_SIZE];

			/* allocate deflate state */
			strm.zalloc = Z_NULL;
			strm.zfree = Z_NULL;
			strm.opaque = Z_NULL;

			strm.avail_in = 0;
		    strm.next_in = Z_NULL;

			ret = inflateInit2(&strm, 47);

			if (ret != Z_OK)
				return ret;

		    /* uncompress until end of file */
		    do {
				strm.avail_in = src_.size();
				strm.next_in = (unsigned char *) src_.data();

				if (strm.avail_in == 0)
		            break;

				do {
					strm.avail_out = __FC_ZLIB_BUFFER_SIZE;
					strm.next_out = buffer_;

					ret = inflate(&strm, Z_NO_FLUSH); /* no bad return value */
					
					switch (ret) 
					{
						case Z_STREAM_ERROR:
							return ret;
						case Z_NEED_DICT:
							ret = Z_DATA_ERROR;     /* and fall through */
						case Z_DATA_ERROR: 
						case Z_MEM_ERROR:
							(void)inflateEnd(&strm);
							return ret;
					}

					have = __FC_ZLIB_BUFFER_SIZE - strm.avail_out;
					
					dest_.append((const char *)buffer_, have);

				} while (strm.avail_out == 0);

				/* done when last data in file processed */
			} while (ret != Z_STREAM_END);

			/* clean up and return */
		    (void)inflateEnd(&strm);

			return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
		}

	}
}


#endif