#pragma once

#include <fstream>
#include "ConfigEntries.h"

/**
 * @brief Base class for configuration entries.
 */
class ConfigEntryBase
{
protected:
    const char *_name;
    const char *_description;

    virtual void writeValue(std::ofstream &file) = 0;

public:
    ConfigEntryBase(const char *name, const char *description);
    virtual ~ConfigEntryBase() = default;
    void write(std::ofstream &file);
    const char *getName() const;
};

/**
 * @brief Base template class for configuration entries.
 *
 * @tparam Derived The derived class type.
 * @tparam T The value type of the configuration entry.
 */
template <typename Derived, typename T>
class ConfigEntry : public ConfigEntryBase
{
public:
    /**
     * @brief Constructor.
     *
     * @param name The name of the configuration entry.
     * @param description The description of the configuration entry.
     */
    ConfigEntry(const char *name, const char *description) : ConfigEntryBase(name, description){};

    /**
     * @brief Sets the value of the configuration entry.
     *
     * @param value The new value.
     */
    void set(const T &value)
    {
        static_cast<Derived *>(this)->setImpl(value);
    }
};

/**
 * @brief Configuration entry for integer values.
 */
class ConfigEntryInt : public ConfigEntry<ConfigEntryInt, int>
{
    int _value;

    /**
     * @brief Writes the configuration entry to a file.
     *
     * @param file The output file stream.
     */
    void writeValue(std::ofstream &file) override;

public:
    /**
     * @brief Constructor.
     *
     * @param value The default value.
     * @param name The name of the configuration entry.
     * @param description The description of the configuration entry.
     */
    ConfigEntryInt(const char *name, const char *description, int value);

    /**
     * @brief Sets the value of the configuration entry.
     *
     * @param value The new value.
     */
    void setImpl(int value);
};

/**
 * @brief Configuration entry for long integer values.
 */
class ConfigEntryLong : public ConfigEntry<ConfigEntryLong, long int>
{
    long int _value;

    /**
     * @brief Writes the configuration entry to a file.
     *
     * @param file The output file stream.
     */
    void writeValue(std::ofstream &file) override;

public:
    /**
     * @brief Constructor.
     *
     * @param value The default value.
     * @param name The name of the configuration entry.
     * @param description The description of the configuration entry.
     */
    ConfigEntryLong(const char *name, const char *description, long int value);

    /**
     * @brief Sets the value of the configuration entry.
     *
     * @param value The new value.
     */
    void setImpl(long int value);
};

/**
 * @brief Configuration entry for floating-point values.
 */
class ConfigEntryFloat : public ConfigEntry<ConfigEntryFloat, float>
{
    float _value;

    /**
     * @brief Writes the configuration entry to a file.
     *
     * @param file The output file stream.
     */
    void writeValue(std::ofstream &file) override;

public:
    /**
     * @brief Constructor.
     *
     * @param value The default value.
     * @param name The name of the configuration entry.
     * @param description The description of the configuration entry.
     */
    ConfigEntryFloat(const char *name, const char *description, float value);

    /**
     * @brief Sets the value of the configuration entry.
     *
     * @param value The new value.
     */
    void setImpl(float value);
};

/**
 * @brief Configuration entry for double precision floating-point values.
 */
class ConfigEntryDouble : public ConfigEntry<ConfigEntryDouble, double>
{
    double _value;

    /**
     * @brief Writes the configuration entry to a file.
     *
     * @param file The output file stream.
     */
    void writeValue(std::ofstream &file) override;

public:
    /**
     * @brief Constructor.
     *
     * @param value The default value.
     * @param name The name of the configuration entry.
     * @param description The description of the configuration entry.
     */
    ConfigEntryDouble(const char *name, const char *description, double value);

    /**
     * @brief Sets the value of the configuration entry.
     *
     * @param value The new value.
     */
    void setImpl(double value);
};

/**
 * @brief Configuration entry for boolean values.
 */
class ConfigEntryBool : public ConfigEntry<ConfigEntryBool, bool>
{
    bool _value;

    /**
     * @brief Writes the configuration entry to a file.
     *
     * @param file The output file stream.
     */
    void writeValue(std::ofstream &file) override;

public:
    /**
     * @brief Constructor.
     *
     * @param value The default value.
     * @param name The name of the configuration entry.
     * @param description The description of the configuration entry.
     */
    ConfigEntryBool(const char *name, const char *description, bool value);

    /**
     * @brief Sets the value of the configuration entry.
     *
     * @param value The new value.
     */
    void setImpl(bool value);
};

/**
 * @brief Configuration entry for string values.
 */
class ConfigEntryString : public ConfigEntry<ConfigEntryString, const char *>
{
    const char *_value;

    /**
     * @brief Writes the configuration entry to a file.
     *
     * @param file The output file stream.
     */
    void writeValue(std::ofstream &file) override;

public:
    /**
     * @brief Constructor.
     *
     * @param value The default value.
     * @param name The name of the configuration entry.
     * @param description The description of the configuration entry.
     */
    ConfigEntryString(const char *name, const char *description, const char *value);

    /**
     * @brief Sets the value of the configuration entry.
     *
     * @param value The new value.
     */
    void setImpl(const char *value);
};