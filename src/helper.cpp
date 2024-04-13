#include "helper.hpp"

#include <algorithm>
#include <sstream>
#include <cctype>
#include <algorithm>

std::string helper::removeWhiteSpaces(std::string str)
{
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end()); // remove all white spaces
    return str;
}

std::string helper::trimWhiteSpaces(std::string str)
{
    auto start_pos = std::find_if(str.begin(), str.end(), [](unsigned char c) { return !std::isspace(c); });
    if (start_pos != str.end())
        str.erase(str.begin(), start_pos);

    auto endpos = std::find_if(str.rbegin(), str.rend(), [](unsigned char c) { return !std::isspace(c); });
    if (endpos != str.rend())
        str.erase(endpos.base(), str.end());

    return str;
}

std::string helper::removeComments(std::string str)
{
    size_t pos = str.find('#');
    if (pos != std::string::npos)
        str = str.substr(0, pos);
    return str;
}

std::vector<std::string> helper::getTokens(std::string const &str, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

std::string helper::addHashBeforeNewline(std::string str)
{
    size_t pos = 0;
    while ((pos = str.find('\n', pos)) != std::string::npos)
    {
        str.insert(pos + 1, "#");
        pos += 1;
    }
    return str;
}