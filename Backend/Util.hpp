#pragma once
#include <sstream>
#include <vector>

class Util
{
public:
    static std::vector<std::string> splitString(const std::string& string)
    {
        std::vector<std::string> arr;

        std::stringstream ss(string);

        std::string word;

        while (ss >> word)
        {
            arr.push_back(word);
        }

        return arr;
    }
};

inline Util util;