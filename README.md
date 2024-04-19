# INI Config Parser C++ library

## Installation
You can install it using cmake or include it like a static or shared library.

## Usage
### 1. Include
```c++
#include <IniCM/IniConfManager.hpp>
```

### 2. Creating the manager
Each IniConfManager object represents a file. To create a manager call it's constructor along with the path/name of the file you wish to write to. For example:
```c++
IniConfManager manager("/path_to_file/options.ini");
```

### 3. Defining the entries
The configuration manager uses classes derived from `IniConfEntry::Base`. Classes for Integer, Long, Float, Double, Boolean and String have been pre-made.
You can define your entry objects anywhere you like like so:
```c++
namespace options
{
    IniConfEntry::Integer integerEntry("Integer Entry", "This is an integer entry", 7);
    IniConfEntry::Long longEntry("Long Entry", "This is a long entry", 42);
    IniConfEntry::Float floatEntry("Float Entry", "This is a float entry", 3.14159);
    IniConfEntry::Double doubleEntry("Double Entry", "This is a double entry", 2.71828);
    IniConfEntry::Boolean booleanEntry("Boolean Entry", "This is a boolean entry", true);
    IniConfEntry::String stringEntry("String Entry", "This is a string entry", "Hello World!");
}
```

### 4. Adding entries to the manager
You can add entries to a manager by calling it's add() method and passing a pointer to the entry. The entries will be written in the same order they had been added in.
```c++
manager.addEntry(&integerEntry);
manager.addEntry(&longEntry);
manager.addEntry(&floatEntry);
manager.addEntry(&doubleEntry);
manager.addEntry(&booleanEntry);
manager.addEntry(&stringEntry);
```

### 5. Build the file
Calling `manager.build()` will load the configuration file if it exists or create it if it doesn't. Alternatively calling `manager.save()` will overwrite the file with the current values of the entries and `manager.load()` will read the values from the file and load them to the entries.

### 6. Defining custom entries
To define a custom entry create a class which inherits from `IniConfEntry::Base<T>` T being your entry type.
You will need to overload 2 methods and the constructor like so:
```c++
class CustomType
{
    /* Your class */
};

class CustomEntry : public IniConfEntry::Base<CustomType>
{
    int setValueFromString(std::string const &value_as_string) override
    {
        /* Code to parse the value from the string and set this->_value to it */
        /* Check the enum IniConfEntry::ErrorCode for all return codes*/
    }
    std::string getValueAsString() const override
    {
        /* Code to return the value as a string */
    }
public:
    // Call the parent constructor with the name, description and default value
    CustomEntry(std::string const name, std::string const description, CustomType const default_value)
        : Base(name, description, default_value) {}
};
```

## Example
```c++
#include <IniConfManager.hpp>

namespace options
{
    IniConfEntry::Integer integerEntry("Integer Entry", "This is an integer entry", 7);
    IniConfEntry::Long longEntry("Long Entry", "This is a long entry", 42);
    IniConfEntry::Float floatEntry("Float Entry", "This is a float entry", 3.14159);
    IniConfEntry::Double doubleEntry("Double Entry", "This is a double entry", 2.71828);
    IniConfEntry::Boolean booleanEntry("Boolean Entry", "This is a boolean entry", true);
    IniConfEntry::String stringEntry("String Entry", "This is a string entry", "Hello World!");

    void init()
    {
        IniConfManager manager("options.ini");

        manager.addEntry(&integerEntry);
        manager.addEntry(&longEntry);
        manager.addEntry(&floatEntry);
        manager.addEntry(&doubleEntry);
        manager.addEntry(&booleanEntry);
        manager.addEntry(&stringEntry);

        manager.build();
    }
}
```
