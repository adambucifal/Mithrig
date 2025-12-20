#include "strings.h"

#include <maya/MStringArray.h>

#include <format>
#include <string>
#include <algorithm>


MString Mithrig::Strings::get(char c, int count) 
{
	return std::string(c, count).c_str();
}


MString Mithrig::Strings::pad(int num, int padding) 
{
    std::string s = std::format("{:0{}}", num, padding);
    return MString(s.c_str());
}


MString Mithrig::Strings::short_name(const MString& name) 
{
    MStringArray contents;
    name.split('|', contents);

    return contents[contents.length() - 1];
}


int Mithrig::Strings::sequential_count(const MString& str, char c)
{
    if (str.isEmpty()) 
    { 
        return 0;
    }

    std::string s = str.asChar();

    int max_count = 1;
    int current_count = 1;

    for (size_t i = 1; i < s.size(); ++i) 
    {
        if (s[i] == s[i - 1]) 
        {
            current_count++;
            max_count = std::max(max_count, current_count);
        }
        else 
        {
            current_count = 1;
        }
    }

    return max_count;
}
