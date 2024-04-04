#include "ConfigEntries.h"

ConfigEntryBase::ConfigEntryBase(const char *name, const char *description) : _name(name), _description(description) {}

ConfigEntryInt::ConfigEntryInt(const char *name, const char *description, int value)
    : ConfigEntry(name, description), _value(value) {}

ConfigEntryLong::ConfigEntryLong(const char *name, const char *description, long int value)
    : ConfigEntry(name, description), _value(value) {}

ConfigEntryFloat::ConfigEntryFloat(const char *name, const char *description, float value)
    : ConfigEntry(name, description), _value(value) {}

ConfigEntryDouble::ConfigEntryDouble(const char *name, const char *description, double value)
    : ConfigEntry(name, description), _value(value) {}

ConfigEntryBool::ConfigEntryBool(const char *name, const char *description, bool value)
    : ConfigEntry(name, description), _value(value) {}

ConfigEntryString::ConfigEntryString(const char *name, const char *description, const char *value)
    : ConfigEntry(name, description), _value(value) {}

void ConfigEntryInt::writeValue(std::ofstream &datao)
{
    datao << _value;
}

void ConfigEntryLong::writeValue(std::ofstream &datao)
{
    datao << _value;
}

void ConfigEntryFloat::writeValue(std::ofstream &datao)
{
    datao << _value;
}

void ConfigEntryDouble::writeValue(std::ofstream &datao)
{
    datao << _value;
}

void ConfigEntryBool::writeValue(std::ofstream &datao)
{
    datao << _value;
}

void ConfigEntryString::writeValue(std::ofstream &datao)
{
    datao << "\"" << _value << "\"";
}

void ConfigEntryInt::setImpl(int value)
{
    _value = value;
}

void ConfigEntryLong::setImpl(long int value)
{
    _value = value;
}

void ConfigEntryFloat::setImpl(float value)
{
    _value = value;
}

void ConfigEntryDouble::setImpl(double value)
{
    _value = value;
}

void ConfigEntryBool::setImpl(bool value)
{
    _value = value;
}

void ConfigEntryString::setImpl(const char *value)
{
    _value = value;
}

void ConfigEntryBase::write(std::ofstream &file)
{
    file << "\n# " << _description << '\n';
    file << _name << " = ";
    writeValue(file);
    file << '\n';
}

const char *ConfigEntryBase::getName() const
{
    return _name;
}