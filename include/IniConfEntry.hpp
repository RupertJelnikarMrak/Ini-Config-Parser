#pragma once

#include <fstream>
#include <string>
#include <any>

class IniConfManager;

namespace IniConfEntry
{
    enum ErrorCode
    {
        SUCCESS = 0,
        INVALID_TOKEN = 1,
        OUT_OF_RANGE = 2,
        UNKNOWN = -1
    };

    class BaseNonTemplate
    {
    protected:
        std::string _name;
        std::string _description;

        void writeToFile(std::ofstream &file) const;

        /**
         * @brief Override this function to return however you want the value to be written to the file as a string. Note! Multiline values are not supported. For possible errors returns check the defined enum ErrorCode.
         */
        virtual std::string getValueAsString() const = 0;
        /**
         * @brief Override this function with how you wish to interpret the value from a string. This will be called with the trimmed string of the value read from the file. For possible errors check the defined enum ErrorCode.
         */
        virtual int setValueFromString(std::string const &value_as_string) = 0;

        friend class ::IniConfManager;

    public:
        BaseNonTemplate(std::string const name, std::string const description);
        virtual ~BaseNonTemplate() = default;
        std::string getName() const;
        std::string getDescription() const { return _description; }
    };

    template <class T>
    class Base : public BaseNonTemplate
    {
    protected:
        T _value;
        T _default_value;

    public:
        Base(std::string const name, std::string const description, T const default_value)
            : BaseNonTemplate(name, description), _default_value(default_value), _value(default_value) {}
        virtual ~Base() = default;

        T getValue() const { return _value; }
        T getDefaultValue() const { return _default_value; }
        void setValue(T const &value) { _value = value; }
    };

    class Integer : public Base<int>
    {
        std::string getValueAsString() const override;
        int setValueFromString(std::string const &value_as_string) override;

    public:
        Integer(std::string const name, std::string const description, int const default_value);
    };

    class Long : public Base<long>
    {
        std::string getValueAsString() const override;
        int setValueFromString(std::string const &value_as_string) override;

    public:
        Long(std::string const name, std::string const description, long const default_value);
    };

    class Float : public Base<float>
    {
        std::string getValueAsString() const override;
        int setValueFromString(std::string const &value_as_string) override;

    public:
        Float(std::string const name, std::string const description, float const default_value);
    };

    class Double : public Base<double>
    {
        std::string getValueAsString() const override;
        int setValueFromString(std::string const &value_as_string) override;

    public:
        Double(std::string const name, std::string const description, double const default_value);
    };

    class Boolean : public Base<bool>
    {
        std::string getValueAsString() const override;
        int setValueFromString(std::string const &value_as_string) override;

    public:
        Boolean(std::string const name, std::string const description, bool const default_value);
    };

    class String : public Base<std::string>
    {
        std::string getValueAsString() const override;
        int setValueFromString(std::string const &value_as_string) override;

    public:
        String(std::string const name, std::string const description, std::string const default_value);
    };
}