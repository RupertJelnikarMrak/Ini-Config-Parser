#pragma once

#include "IniConfEntry.hpp"

#include <vector>
#include <unordered_map>
#include <memory>
#include <string>

class IniConfManager
{
private:
    std::vector<std::string> _keys;
    std::unordered_map<std::string, IniConfEntry::BaseNonTemplate*> _entries;
    std::string _file_path;

    std::string _latest_error;
public:
    IniConfManager(std::string file_path);

    int build();
    int save();
    int load();

    int addEntry(IniConfEntry::BaseNonTemplate *entry);

    std::string getLatestError() const;
    
    enum ErrorCode
    {
        SUCCESS = 0,
        FILE_NOT_FOUND = 1,
        INVALID_LINE = 2,
        KEY_NOT_FOUND = 3,
        KEY_ALREADY_EXISTS = 4,
        FILE_CREATION_FAILED = 5,
        UNKNOWN = -1
    };
};