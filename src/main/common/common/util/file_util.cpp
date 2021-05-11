/*********************************************************************************
  *Copyright(C),dingbinthu@163.com
  *All rights reserved.
  *
  *FileName:       file_util.cpp
  *Author:         dingbinthu@163.com
  *Version:        1.0
  *Date:           2021/4/26
  *Description:
**********************************************************************************/
#include "common/util/file_util.h"
#include <sys/stat.h>
#include <dirent.h>
#include <fstream>

STD_USE_NAMESPACE;
COMMON_BEGIN_NAMESPACE

TLOG_SETUP(COMMON_NS,FileUtility);

uint64_t FileUtility::GetFileLineNumber(const string& file) {
    ifstream ifs(file);
    if (!ifs) return 0;
    char ch;
    uint64_t count = 0;
    while (ifs.get(ch)) {
        if (ch == '\n')
            ++count;
    }
    return count;
}

bool FileUtility::IsFileExists(const std::string& file){
    if (access(file.c_str(), F_OK) == 0) { return true; }
    return false;
}

bool FileUtility::IsDirExists(const std::string& dir){
    struct stat st;
    if (stat(dir.c_str(), &st) != 0) { return false; }
    if (!S_ISDIR(st.st_mode)) { return false; }
    return true;
}

bool FileUtility::RecurMakeLocalDir(const string &localDirPath) {
    if (localDirPath.empty()) {
        return false;
    }
    if (IsDirExists(localDirPath)) {
        return true;
    }
    string currentDir = localDirPath;
    string parentDir = GetParentDir(currentDir);

    if (parentDir != "" && !IsDirExists(parentDir)) {
        bool ret = RecurMakeLocalDir(parentDir);
        if (!ret) {
            TLOG_LOG(ERROR, "recursive make local dir error, dir:[%s]", parentDir.c_str());
            return false;
        }
    }

    int mkdirRet = mkdir(currentDir.c_str(), S_IRWXU);
    if (mkdirRet != 0) {
        TLOG_LOG(ERROR, "mkdir error, dir:[%s], errno:%d", currentDir.c_str(), errno);
        return false;
    }
    return true;
}

std::string FileUtility::GetParentDir(const std::string &currentDir)
{
    if (currentDir.empty()) { return ""; }

    size_t delimPos = string::npos;
    if (DIR_DELIM == *(currentDir.rbegin())) {
        delimPos = currentDir.rfind(DIR_DELIM, currentDir.size() - 2);
    } else {
        delimPos = currentDir.rfind(DIR_DELIM);
    }
    if (string::npos == delimPos) { return ""; }
    string parentDir = currentDir.substr(0, delimPos);
    return parentDir;
}

bool FileUtility::MakeLocalDir(const string &localDirPath, bool recursive)
{
    if (recursive) {
        return RecurMakeLocalDir(localDirPath);
    }
    if (IsDirExists(localDirPath)) {
        TLOG_LOG(ERROR, "the directory[%s] is already exist", localDirPath.c_str());
        return false;
    }
    int mkdirRet = mkdir(localDirPath.c_str(), S_IRWXU);
    if (mkdirRet != 0) {
        TLOG_LOG(ERROR, "mkdir error, dir:[%s], errno:%d", localDirPath.c_str(), errno);
        return false;
    }
    return true;
}

bool FileUtility::DeleteLocalFile(const std::string &localFilePath)
{
    return (0 == unlink(localFilePath.c_str()));
}


bool FileUtility::RemoveLocalDir(const std::string &localDirPath,
                              bool removeNoneEmptyDir)
{
    bool dirExist = FileUtility::IsDirExists(localDirPath);
    if (!dirExist) {
        TLOG_LOG(ERROR, "the dir:[%s] is not exist", localDirPath.c_str());
        return false;
    }

    if (removeNoneEmptyDir) {
        return RecurRemoveLocalDir(localDirPath);
    } else if (rmdir(localDirPath.c_str()) != 0) {
        TLOG_LOG(ERROR, "localDirPath[%s] may not an empty dir", localDirPath.c_str());
        return false;
    }
    return true;
}

bool FileUtility::RecurRemoveLocalDir(const std::string &localDirPath){
    DIR *dir = NULL;
    struct dirent *dp = NULL;

    if ((dir = opendir(localDirPath.c_str())) == NULL) {
        TLOG_LOG(ERROR, "opendir error, localDirPath:[%s]", localDirPath.c_str());
        return false;
    }

    bool retFlag = false;
    while((dp = readdir(dir)) != NULL) {
        if (dp->d_type & DT_DIR) {
            if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
                retFlag = true;
                continue;
            } else {
                string childDirPath = localDirPath + DIR_DELIM + string(dp->d_name);
                retFlag = RecurRemoveLocalDir(childDirPath);
            }
        } else {
            string childFilePath = localDirPath + DIR_DELIM + string(dp->d_name);
            retFlag = DeleteLocalFile(childFilePath);
        }

        if (!retFlag) {
            break;
        }
    }
    closedir(dir);

    //rm itself
    if (retFlag && rmdir(localDirPath.c_str()) != 0) {
        TLOG_LOG(ERROR, "rmdir error, localDirPath[%s]", localDirPath.c_str());
        return false;
    }
    return retFlag;
}

COMMON_END_NAMESPACE
