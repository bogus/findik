#ifndef FINDIK_IO_ZLIB_UTIL_HPP
#define FINDIK_IO_ZLIB_UTIL_HPP

#include "findik_config.hpp"

#include <zlib.h>

#include <string>

namespace findik {
	namespace io {

		int zlib_inflate(const std::string & src_, std::string & dest_) {

			int ret, flush;
		    unsigned int have;
			z_stream strm;

			std::stringstream dstream_(dest_);

			unsigned char buffer_[__FC_ZLIB_BUFFER_SIZE];

			/* allocate deflate state */
			strm.zalloc = Z_NULL;
			strm.zfree = Z_NULL;
			strm.opaque = Z_NULL;
			ret = inflateInit(&strm);
			if (ret != Z_OK)
				return ret;

		    /* uncompress until end of file */
		    do {
				strm.avail_in = src_.size();
				strm.next_in = (unsigned char *) src_.c_str();

				do {
					strm.avail_out = __FC_ZLIB_BUFFER_SIZE;
					strm.next_out = buffer_;

					ret = inflate(&strm, flush); /* no bad return value */
					if (ret == Z_STREAM_ERROR)  /* state not clobbered */
						return ret;
					
					have = __FC_ZLIB_BUFFER_SIZE - strm.avail_out;
					
					dstream_.write((const char *)buffer_,have);
				} while (strm.avail_out == 0);

				if (strm.avail_in != 0) /* all input will be used */
					return Z_ERRNO;

				/* done when last data in file processed */
			} while (flush != Z_FINISH);

			if (ret != Z_STREAM_END)  /* stream will be complete */
				return Z_ERRNO;

			/* clean up and return */
		    (void)inflateEnd(&strm);

			return Z_OK;










		}

	}
}


#endif