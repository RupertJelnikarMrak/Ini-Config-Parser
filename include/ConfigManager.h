#pragma once

#include "ConfigEntries.h"

#include <unordered_map>

/**
 * @class ConfigManager
 * @brief Manages multiple "entries" in a configuration file.
 */
class ConfigManager
{
private:
    const char *_file_path;
    std::unordered_map<const char*, ConfigEntryBase*> _entries;
public:
    /**
     * @brief Constructs a new ConfigManager.
     * @param p_file_path The path to the configuration file the manager will use.
     */
    ConfigManager(const char *p_file_path);

    int addEntry(ConfigEntryBase *p_entry);

    void load();

    void write();

    void build();
};
