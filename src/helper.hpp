#pragma once

#include <string>
#include <vector>

namespace helper
{
    std::string removeWhiteSpaces(std::string str);
    std::string trimWhiteSpaces(std::string str);
    std::string removeComments(std::string str);
    std::vector<std::string> getTokens(std::string const &str, char delimiter);
    std::string addHashBeforeNewline(std::string str);
}