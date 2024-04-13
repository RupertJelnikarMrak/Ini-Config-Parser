#include "IniConfEntry.hpp"
#include "helper.hpp"

IniConfEntry::BaseNonTemplate::BaseNonTemplate(std::string const name, std::string const description)
{
    _name = helper::trimWhiteSpaces(name);
    _description = description;
}
std::string IniConfEntry::BaseNonTemplate::getName() const
{
    return _name;
}

void IniConfEntry::BaseNonTemplate::writeToFile(std::ofstream &file) const
{
    file << "# " << helper::addHashBeforeNewline(_description) << '\n';
    if (_name.find(' ') != std::string::npos)
        file << '\"' << _name << "\" = " << getValueAsString() << '\n';
    else
        file << _name << " = " << getValueAsString() << '\n';
}

// * Integer * //

IniConfEntry::Integer::Integer(std::string const name, std::string const description, int const default_value)
    : Base(name, description, default_value) {}

std::string IniConfEntry::Integer::getValueAsString() const
{
    return std::to_string(_value);
}

int IniConfEntry::Integer::setValueFromString(std::string const &value_as_string)
{
    try
    {
        _value = std::stoi(value_as_string);
        return IniConfEntry::ErrorCode::SUCCESS;
    }
    catch (std::invalid_argument &e)
    {
        return IniConfEntry::ErrorCode::INVALID_TOKEN;
    }
    catch (std::out_of_range &e)
    {
        return IniConfEntry::ErrorCode::OUT_OF_RANGE;
    }
    return IniConfEntry::ErrorCode::UNKNOWN;
}

// * Long * //
IniConfEntry::Long::Long(std::string const name, std::string const description, long const default_value)
    : Base(name, description, default_value) {}

std::string IniConfEntry::Long::getValueAsString() const
{
    return std::to_string(_value);
}

int IniConfEntry::Long::setValueFromString(std::string const &value_as_string)
{
    try
    {
        _value = std::stol(value_as_string);
        return IniConfEntry::ErrorCode::SUCCESS;
    }
    catch (std::invalid_argument &e)
    {
        return IniConfEntry::ErrorCode::INVALID_TOKEN;
    }
    catch (std::out_of_range &e)
    {
        return IniConfEntry::ErrorCode::OUT_OF_RANGE;
    }
    return IniConfEntry::ErrorCode::UNKNOWN;
}

// * Float * //
IniConfEntry::Float::Float(std::string const name, std::string const description, float const default_value)
    : Base(name, description, default_value) {}

std::string IniConfEntry::Float::getValueAsString() const
{
    return std::to_string(_value);
}

int IniConfEntry::Float::setValueFromString(std::string const &value_as_string)
{
    try
    {
        _value = std::stof(value_as_string);
        return IniConfEntry::ErrorCode::SUCCESS;
    }
    catch (std::invalid_argument &e)
    {
        return IniConfEntry::ErrorCode::INVALID_TOKEN;
    }
    catch (std::out_of_range &e)
    {
        return IniConfEntry::ErrorCode::OUT_OF_RANGE;
    }
    return IniConfEntry::ErrorCode::UNKNOWN;
}

// * Double * //
IniConfEntry::Double::Double(std::string const name, std::string const description, double const default_value)
    : Base(name, description, default_value) {}

std::string IniConfEntry::Double::getValueAsString() const
{
    return std::to_string(_value);
}

int IniConfEntry::Double::setValueFromString(std::string const &value_as_string)
{
    try
    {
        _value = std::stod(value_as_string);
        return IniConfEntry::ErrorCode::SUCCESS;
    }
    catch (std::invalid_argument &e)
    {
        return IniConfEntry::ErrorCode::INVALID_TOKEN;
    }
    catch (std::out_of_range &e)
    {
        return IniConfEntry::ErrorCode::OUT_OF_RANGE;
    }
    return IniConfEntry::ErrorCode::UNKNOWN;
}

// * Boolean * //
IniConfEntry::Boolean::Boolean(std::string const name, std::string const description, bool const default_value)
    : Base(name, description, default_value) {}

std::string IniConfEntry::Boolean::getValueAsString() const
{
    return std::to_string(_value);
}

int IniConfEntry::Boolean::setValueFromString(std::string const &value_as_string)
{
    if (value_as_string == "true" || value_as_string == "True" || value_as_string == "TRUE" || value_as_string == "1")
        _value = true;
    else if (value_as_string == "false" || value_as_string == "False" || value_as_string == "FALSE" || value_as_string == "0")
        _value = false;
    else
        return IniConfEntry::ErrorCode::INVALID_TOKEN;
    return IniConfEntry::ErrorCode::SUCCESS;
}

// * String * //
IniConfEntry::String::String(std::string const name, std::string const description, std::string const default_value)
    : Base(name, description, default_value) {}

std::string IniConfEntry::String::getValueAsString() const
{
    return "\"" + _value + "\"";
}

std::string removeQuotes(std::string str)
{
    str = str.substr(1, str.size() - 2);
    return str;
}

int IniConfEntry::String::setValueFromString(std::string const &value_as_string)
{
    if (value_as_string[0] == '\"' && value_as_string[value_as_string.size() - 1] == '\"')
        _value = removeQuotes(value_as_string);
    else
        return IniConfEntry::ErrorCode::INVALID_TOKEN;
    return IniConfEntry::ErrorCode::SUCCESS;
}