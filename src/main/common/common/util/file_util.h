/*********************************************************************************
  *Copyright(C),dingbinthu@163.com
  *All rights reserved.
  *
  *FileName:       file_util.h
  *Author:         dingbinthu@163.com
  *Version:        1.0
  *Date:           2021/4/26
  *Description:
**********************************************************************************/
#ifndef __COMMON_FILE_UTIL__H__
#define __COMMON_FILE_UTIL__H__

#include "common/common.h"
#include <iostream>

STD_USE_NAMESPACE;
COMMON_BEGIN_NAMESPACE

class FileUtility {
public:
    static uint64_t GetFileLineNumber(const string& file);
    static bool IsFileExists(const std::string& file);
    static bool IsDirExists(const std::string& dir);
    static bool RecurMakeLocalDir(const string &localDirPath);
    static string GetParentDir(const std::string &currentDir);
    static bool MakeLocalDir(const string &localDirPath, bool recursive = false);
    static bool DeleteLocalFile(const std::string &localFilePath);

    static bool RecurRemoveLocalDir(const std::string &localDirPath);
    static bool RemoveLocalDir(const std::string &localDirPath, bool removeNoneEmptyDir);
private:
    static const char DIR_DELIM = '/';
private:
    TLOG_DECLARE();
};

class RemoveFileRAII {
public:
    RemoveFileRAII() = default;
    RemoveFileRAII(const string& file): file_(file) {}

    ~RemoveFileRAII() {
        if (!file_.empty() && FileUtility::IsFileExists(file_)) {
            FileUtility::DeleteLocalFile(file_);
        }
    }

    void SetFilePath(const string& file) {
        file_ = file;
    }
private:
    string   file_;
};
TYPEDEF_PTR(RemoveFileRAII);


COMMON_END_NAMESPACE
#endif //__COMMON_FILE_UTIL__H__
