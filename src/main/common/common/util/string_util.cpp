/*********************************************************************************
  *Copyright(C),dingbinthu@163.com
  *All rights reserved.
  *
  *FileName:       string_util.cpp
  *Author:         dingbinthu@163.com
  *Version:        1.0
  *Date:           4/27/21
  *Description:
**********************************************************************************/
#include "common/util/string_util.h"
#include <assert.h>

STD_USE_NAMESPACE;
COMMON_BEGIN_NAMESPACE



void Utf8Util::Bytes2utf8(const vector<uint8_t>& bytes, vector<string>& utf8strVec) {
    string s;
    for (uint8_t ch: bytes) {
        s.push_back(ch);
    }
    String2utf8(s,utf8strVec);
}

void Utf8Util::String2utf8(const string& str, vector<string>& utf8strVec) {
    utf8strVec.clear();
    string s;
    uint32_t nByte;
    for (char ch: str) {
        if (IsUtf8Beginning(ch,nByte)) {
            if (!s.empty()) utf8strVec.push_back(s);
            s.clear();
        }
        s.push_back(ch);
    }
    utf8strVec.push_back(s);
}

bool Utf8Util::IsAscii(uint8_t ch) {
    return (ch & 0x80) == 0 ;
}

/*
 *  Unicode符号范围     |        UTF-8编码方式
 *  (十六进制)        |              （二进制）
 *  ----------------------+---------------------------------------------
 *  0000 0000-0000 007F | 0xxxxxxx
 *  0000 0080-0000 07FF | 110xxxxx 10xxxxxx
 *  0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
 *  0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 */
bool Utf8Util::IsUtf8Beginning(uint8_t ch,uint32_t& nByteCnt) {
    if ((ch & 0xFC) == 0xFC) {
        nByteCnt = 6;
        return true;
    }
    else if ((ch &0xF8) == 0xF8) {
        nByteCnt = 5;
        return true;
    }
    else if ((ch &0xF0) == 0xF0) {
        nByteCnt = 4;
        return true;
    }
    else if ((ch &0xE0) == 0xE0) {
        nByteCnt = 3;
        return true;
    }
    else if ((ch &0xC0) == 0xC0) {
        nByteCnt = 2;
        return true;
    }
    else if ((ch &0x80) == 0) {
        nByteCnt = 1;
        return true;
    }
    return false;
}

void StringUtil::Split( const std::string& text, const std::string &sepStr,
                  std::vector<std::string>& vec, bool ignoreEmpty)
{
    vec.clear();
    std::string str(text);
    std::string sep(sepStr);
    size_t n = 0, old = 0;
    while (n != std::string::npos)
    {
        n = str.find(sep,n);
        if (n != std::string::npos)
        {
            if (!ignoreEmpty || n != old)
                vec.push_back(str.substr(old, n-old));
            n += sep.length();
            old = n;
        }
    }

    if (!ignoreEmpty || old < str.length()) {
        vec.push_back(str.substr(old, str.length() - old));
    }
}
string StringUtil::TrimString(const std::string& s)
{
    static const char* whiteSpace = " \t\r\n";

    // test for null string
    if (s.empty())
        return s;

    // find first non-space character
    std::string::size_type b = s.find_first_not_of(whiteSpace);
    if (b == std::string::npos) // No non-spaces
        return "";

    // find last non-space character
    std::string::size_type e = s.find_last_not_of(whiteSpace);

    // return the remaining characters
    return std::string(s, b, e - b + 1);

}

COMMON_END_NAMESPACE
