/*********************************************************************************
  *Copyright(C),dingbinthu@163.com
  *All rights reserved.
  *
  *FileName:       hash_util.cpp
  *Author:         dingbinthu@163.com
  *Version:        1.0
  *Date:           4/27/21
  *Description:    file implements hash function and other method on hash
**********************************************************************************/
#include "common/util/hash_util.h"
#include "common/util/string_util.h"

STD_USE_NAMESPACE;
COMMON_BEGIN_NAMESPACE


uint32_t HashAlgorithm::HashStringWithLen(const char* str, uint32_t dwHashType, uint32_t len)
{
    uint32_t cKey;
    uint8_t* key = (uint8_t*)str;
    uint32_t seed1 = 0x7FED7FED, seed2 = 0xEEEEEEEE;

    for(uint32_t i=0; i<len; i++)
    {
        cKey = *key++;
        seed1 = CRYPT_TABLE[(dwHashType << 8) + cKey] ^ (seed1 + seed2);
        seed2 = cKey + seed1 + seed2 + (seed2 << 5) + 3;
    }

    return seed1;
}

uint32_t HashAlgorithm::HashString(const char* str, uint32_t dwHashType)
{
    uint32_t cKey;
    uint8_t* key = (uint8_t*)str;
    uint32_t seed1 = 0x7FED7FED, seed2 = 0xEEEEEEEE;

    while (*key != 0) {
        cKey = *key++;
        seed1 = CRYPT_TABLE[(dwHashType << 8) + cKey] ^ (seed1 + seed2);
        seed2 = cKey + seed1 + seed2 + (seed2 << 5) + 3;
    }

    return seed1;
}

uint32_t HashAlgorithm::HashString(const char* str, size_t len, uint32_t dwHashType)
{
    uint32_t cKey;
    uint8_t* key = (uint8_t*)str;
    uint32_t seed1 = 0x7FED7FED, seed2 = 0xEEEEEEEE;

    for (size_t i = 0; i < len; ++i) {
        cKey = *key++;
        seed1 = CRYPT_TABLE[(dwHashType << 8) + cKey] ^ (seed1 + seed2);
        seed2 = cKey + seed1 + seed2 + (seed2 << 5) + 3;
    }

    return seed1;
}

uint64_t HashAlgorithm::HashString64WithLen(const char* str, uint32_t len)
{
    uint64_t h = HashStringWithLen(str, 0, len);
    h <<= 32;
    h |= HashStringWithLen(str, 1, len);
    return h;
}

uint64_t HashAlgorithm::HashString64(const char* str)
{
    uint64_t h = HashString(str, 0);
    h <<= 32;
    h |= HashString(str, 1);
    return h;
}

uint64_t HashAlgorithm::HashString64(const char* str, size_t len)
{
    uint64_t h = HashString(str, len, 0);
    h <<= 32;
    h |= HashString(str, len, 1);
    return h;
}

uint64_t HashAlgorithm::HashNumber64(int32_t number) {
    uint64_t nKeyHash;
    if (number < 0) {
        nKeyHash = (uint64_t)(-number);
        nKeyHash = ~nKeyHash & 0x7FFFFFFFFFFFFFFFLL;
    } else {
        nKeyHash = (uint64_t)number;
        nKeyHash |= 0x8000000000000000LL;
    }
    return nKeyHash;
}

COMMON_END_NAMESPACE
