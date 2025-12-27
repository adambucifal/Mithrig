#pragma once
#include <maya/MString.h>
#include <sstream>


namespace Mithrig::Conversions
{
    template <typename... Args>
    MString to_mstring(Args&&... args);
}


template <typename... Args>
MString Mithrig::Conversions::to_mstring(Args&&... args)
{
    std::ostringstream oss;
    (oss << ... << args);
    return MString(oss.str().c_str());
}
