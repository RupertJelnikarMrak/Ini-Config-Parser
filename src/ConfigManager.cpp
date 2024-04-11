#include "ConfigManager.h"

ConfigManager::ConfigManager(const char *p_file_path)
    : _file_path(p_file_path)
{
}

int ConfigManager::addEntry(ConfigEntryBase *entry)
{
    if (_entries.find(entry->getName()) != _entries.end())
        _entries[entry->getName()] = entry;
}

void ConfigManager::load()
{

}

void ConfigManager::write()
{

}

void ConfigManager::build()
{

}