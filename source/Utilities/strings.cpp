#include "strings.h"

#include <format>
#include <string>
#include <algorithm>


MString Mithrig::Utilities::Strings::get(char c, int count) 
{
	return std::string(c, count).c_str();
}


MString Mithrig::Utilities::Strings::pad(int num, int padding) 
{
	return std::format("{:0{}}", num, padding).c_str();
}


int Mithrig::Utilities::Strings::sequential_count(const MString& str, char c)
{
    


    if (str.isEmpty()) 
    { 
        return 0;
    }

    std::string s = str.asChar();

    int max_count = 1;
    int current_count = 1;

    for (size_t i = 1; i < s.size(); ++i) {
        if (s[i] == s[i - 1]) {
            current_count++;
            max_count = std::max(max_count, current_count);
        }
        else {
            current_count = 1;
        }
    }

    return max_count;
}
