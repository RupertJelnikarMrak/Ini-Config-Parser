#include "IniConfManager.hpp"

#include "helper.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <filesystem>

IniConfManager::IniConfManager(std::string file_path)
    : _file_path(file_path) {}

int IniConfManager::save()
{
    std::ofstream file(_file_path, std::ios::trunc);
    if (!file.is_open())
    {
        _latest_error = "Failed to open file: \"" + _file_path + "\". This is likely due to a permissions issue.";
        return ErrorCode::FILE_NOT_FOUND;
    }
    for (std::string &key : _keys)
    {
        auto &entry = _entries[key];
        entry->writeToFile(file);
        file << '\n';
    }
    file.close();
    return ErrorCode::SUCCESS;
}

int IniConfManager::load()
{
    int result = ErrorCode::SUCCESS;
    std::ifstream file(_file_path, std::ios::in);
    if (!file.is_open())
    {
        _latest_error = "Failed to open file: \"" + _file_path + "\". Does the file exist?";
        return ErrorCode::FILE_NOT_FOUND;
    }
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<std::string> tokens = helper::getTokens(helper::removeComments(line), '=');
        if (tokens.size() == 2)
        {
            std::string key = helper::trimWhiteSpaces(tokens[0]);
            if (key[0] == '\"' && key[key.length() - 1] == '\"')
                key = key.substr(1, key.length() - 2);
            std::string value = helper::trimWhiteSpaces(tokens[1]);
            if (_entries.find(key) == _entries.end())
            {
                _latest_error = ("ConfigManager::load() -> Key \"" + key + "\" not found.").c_str();
                result = ErrorCode::KEY_NOT_FOUND;
            }
            else if (_entries[key]->setValueFromString(value))
            {
                _latest_error = "ConfigManager::load() -> Failed to parse value \"" + value + "\" at line \"" + line + "\".";
                result = ErrorCode::INVALID_LINE;
            }
        }
        else
        {
            _latest_error = "ConfigManager::load() -> Invalid line \"" + line + "\".";
            result = ErrorCode::INVALID_LINE;
        }
    }
    return result;
}

int IniConfManager::build()
{
    if (load() == ErrorCode::FILE_NOT_FOUND) // Returns false if file cannot be opened -> does not exist or access denied
    {
        if (save()) // Try to create it, if it cannot be created, it is likely an access error
        {
            _latest_error = "Failed to create file: \"" + _file_path + "\". This is likely due to a permissions issue.";
            return ErrorCode::FILE_CREATION_FAILED;
        }
        else
        {
            _latest_error = "Configuration file did not exist -> Created successfully.";
            return ErrorCode::SUCCESS;
        }
    }
    save();
    return ErrorCode::SUCCESS;
}

int IniConfManager::addEntry(IniConfEntry::BaseNonTemplate *entry)
{
    std::string key = entry->getName();
    if (_entries.find(key) != _entries.end())
    {
        _latest_error = "ConfigManager::add() -> Key \"" + entry->getName() + "\" already exists.";
        return ErrorCode::KEY_ALREADY_EXISTS;
    }
    _entries[key] = entry;
    _keys.push_back(entry->getName());
    return ErrorCode::SUCCESS;
}

std::string IniConfManager::getLatestError() const
{
    return _latest_error;
}