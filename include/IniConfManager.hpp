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
    std::unordered_map<std::string, IniConfEntry::BaseNonTemplate *> _entries;
    std::string _file_path;

    std::string _latest_error;

public:
    IniConfManager(std::string file_path);

    /**
     * @brief Loads the configuration file if it exists or creates it if it doesn't.
     */
    int build();
    /**
     * @brief Saves the current value of all entries to the configuration file overwriting any previous changes.
     */
    int save();
    /**
     * Loads values from the configuration file.
    */
    int load();

    /**
     * @brief Adds the entry to the configuration file in the order it was called.
     * @param entry Pointer to the entry to be added.
    */
    int addEntry(IniConfEntry::BaseNonTemplate *entry);

    /**
     * Returns the latest error message as a string.
    */
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