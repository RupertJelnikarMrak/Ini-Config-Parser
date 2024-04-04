#pragma once

#include <fstream>

template <typename Derived, typename T>
class ConfigEntry
{
public:
    ConfigEntry();
    virtual ~ConfigEntry();

    virtual void write(std::ofstream &file) = 0;

    void set(const T &value)
    {
        static_cast<Derived *>(this)->setImpl(value);
    }
};

class ConfigEntryInt : public ConfigEntry<ConfigEntryInt, int>
{
    int value;

public:
    ConfigEntryInt(int);
    ~ConfigEntryInt() override;
    void write(std::ofstream &file) override;
};

class ConfigEntryLong : public ConfigEntry<ConfigEntryLong, float>
{
    long int value;

public:
    ConfigEntryLong(long int);
    ~ConfigEntryLong();
};

class ConfigEntryFloat : public ConfigEntry<ConfigEntryFloat, float>
{
    float value;

public:
    ConfigEntryFloat(float);
    ~ConfigEntryFloat() override;
    void write(std::ofstream &file) override;
};

class ConfigEntryDouble : public ConfigEntry<ConfigEntryDouble, double>
{
    double value;

public:
    ConfigEntryDouble(double);
    ~ConfigEntryDouble() override;
    void write(std::ofstream &file) override;
};

class ConfigEntryString : public ConfigEntry<ConfigEntryString, const char *>
{
    const char *value;

public:
    ConfigEntryString(const char *);
    ~ConfigEntryString() override;
    void write(std::ofstream &file) override;
};