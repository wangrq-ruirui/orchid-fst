/*********************************************************************************
  *Copyright(C),dingbinthu@163.com
  *All rights reserved.
  *
  *FileName:       string_util.h
  *Author:         dingbinthu@163.com
  *Version:        1.0
  *Date:           4/27/21
  *Description:
**********************************************************************************/
#ifndef __COMMON_STRING_UTIL__H__
#define __COMMON_STRING_UTIL__H__
#include "common/common.h"
#include <iostream>

STD_USE_NAMESPACE;
COMMON_BEGIN_NAMESPACE

/**
 *@brief     class to convert for utf8 code convert
 *@author    dingbinthu@163.com
 *@date      5/11/21, 2:35 AM
 */
class Utf8Util {
public:
    static bool IsAscii(uint8_t ch);
    static bool IsUtf8Beginning(uint8_t ch,uint32_t& nByteCnt);
    static void String2utf8(const string& str, vector<string>& utf8strVec);
    static void Bytes2utf8(const vector<uint8_t>& bytes, vector<string>& utf8strVec);
};

class StringUtil {
public:
    static void Split( const std::string& text, const std::string &sepStr,
                std::vector<std::string>& vec, bool ignoreEmpty);

    static string TrimString(const std::string& s);
};





COMMON_END_NAMESPACE
#endif //__COMMON_STRING_UTIL__H__
