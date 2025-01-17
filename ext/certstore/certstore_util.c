/* certstore_c */
/* Licensed under the Apache License, Version 2.0 (the "License"); */
/* you may not use this file except in compliance with the License. */
/* You may obtain a copy of the License at */
/*     http://www.apache.org/licenses/LICENSE-2.0 */
/* Unless required by applicable law or agreed to in writing, software */
/* distributed under the License is distributed on an "AS IS" BASIS, */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. */
/* See the License for the specific language governing permissions and */
/* limitations under the License. */

#include <certstore.h>

char*
wstr_to_mbstr(UINT cp, const WCHAR *wstr, int clen)
{
    char *ptr;
    int len = WideCharToMultiByte(cp, 0, wstr, clen, NULL, 0, NULL, NULL);
    if (!(ptr = xmalloc(len))) return NULL;
    WideCharToMultiByte(cp, 0, wstr, clen, ptr, len, NULL, NULL);

    return ptr;
}

TCHAR*
handle_error_code(VALUE self, DWORD errCode)
{
  DWORD ret;
  static TCHAR buffer[1024];

  ret = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
                      NULL,
                      errCode,
                      MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
                      buffer,
                      sizeof(buffer)/sizeof(buffer[0]),
                      NULL);

  if (ret) {
    rb_ivar_set(self, rb_intern("@error_code"), INT2NUM(errCode));
    rb_ivar_set(self, rb_intern("@error_message"), rb_utf8_str_new_cstr(buffer));
  }

  return buffer;
}
