/*
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

#ifndef FINDIK_IO_PARSER_UTIL_HPP
#define FINDIK_IO_PARSER_UTIL_HPP

namespace findik {
	namespace io {

/// Check if a byte is an HTTP character.
static bool is_char(int c)
{
  return c >= 0 && c <= 127;
}

/// Check if a byte is an HTTP control character.
static bool is_ctl(int c)
{
  return c >= 0 && c <= 31 || c == 127;
}

/// Check if a byte is defined as an HTTP tspecial character.
static bool is_tspecial(int c)
{
  switch (c)
  {
  case '(': case ')': case '<': case '>': case '@':
  case ',': case ';': case ':': case '\\': case '"':
  case '/': case '[': case ']': case '?': case '=':
  case '{': case '}': case ' ': case '\t':
    return true;
  default:
    return false;
  }
}

/// Check if a byte is a digit.
static bool is_digit(int c)
{
  return c >= '0' && c <= '9';
}

static bool is_hex(int c)
{
  if (is_digit(c) ||
	  ( c >= 'a' && c <= 'f' ) ||
	  ( c >= 'A' && c <= 'F' )
	  )
	  return true;
  else
    return false;

}

static int hex2int(std::string hex){
// take a string which contains and int as hex and turn it into the int..
// of course this won't work if you parse a non hex number string
   std::stringstream ss(hex);
   int i;
   ss>>std::hex>>i;
   return i;
}

static bool is_uri_char_unreserved(int c)
{
	if (is_digit(c) || isalpha(c))
		return true;
	switch (c)
    {
    case '-': case '_': case '.': case '~':
      return true;
    }
	return false;
}

static bool is_uri_char_reserved(int c) {
	switch (c)
    {
    case '!': case '*': case '\'': case '(': case ')':
	case ';': case ':': case '@': case '&': case '=':
    case '+': case '$': case ',': case '?': case '/':
	case '%': case '#': case '[': case ']':
      return true;
    }
	return false;
}

static bool is_uri_char(int c)
{
	return is_uri_char_unreserved(c) || is_uri_char_reserved(c);
}

	}
}


#endif

