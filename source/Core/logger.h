#pragma once

#include <iostream>
#include <maya/MStreamUtils.h>
#include <maya/MString.h>
#include <maya/MGlobal.h>

#include "conversions.h"


inline MString _log_prefix(const char* level, const char* file, int line) {
    MString out;
    out.format("[^1s] ^2s: ^3s - ", MString(level), MString(file), Mithrig::Conversions::to_mstring(line));
    return out;
}


#ifdef MITHRIG_DIST

#define LOG_DEBUG(...)

#define LOG_INFO(...) \
    MGlobal::displayInfo(Mithrig::Conversions::to_mstring(__VA_ARGS__))

#define LOG_WARN(...) \
    MGlobal::displayWarning(Mithrig::Conversions::to_mstring(__VA_ARGS__))

#define LOG_ERROR(...) \
    MGlobal::displayError(Mithrig::Conversions::to_mstring(__VA_ARGS__))


#elif MITHRIG_DEBUG || MITHRIG_RELEASE

#define LOG_DEBUG(...) \
        MStreamUtils::stdOutStream() << _log_prefix("DEBUG", __FILE__, __LINE__) << __VA_ARGS__ << "\n"

#define LOG_INFO(...) \
        MStreamUtils::stdOutStream() << _log_prefix("INFO", __FILE__, __LINE__) << __VA_ARGS__ << "\n" \
        MGlobal::displayInfo(Mithrig::Conversions::to_mstring(__VA_ARGS__))

#define LOG_WARN(...) \
        MStreamUtils::stdErrorStream() << _log_prefix("WARN", __FILE__, __LINE__) << __VA_ARGS__ << "\n" \
        MGlobal::displayWarning(Mithrig::Conversions::to_mstring(__VA_ARGS__))

#define LOG_ERROR(...) \
        MStreamUtils::stdErrorStream() << _log_prefix("ERROR", __FILE__, __LINE__) << __VA_ARGS__ << "\n" \
        MGlobal::displayError(Mithrig::Conversions::to_mstring(__VA_ARGS__))

#endif