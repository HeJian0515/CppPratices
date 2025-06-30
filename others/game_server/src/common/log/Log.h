#ifndef LOG_H
#define LOG_H

#pragma once

#include "LogDef.h"
#include "../base/platform.h"

#include <spdlog/spdlog.h>

#include <string>

namespace HGS {
    DLL_EXPORT_DECL void SetLogLevel(LogLevel lev);

    DLL_EXPORT_DECL void SetPattern(const std::string &pattern);

    DLL_EXPORT_DECL void LogTrace(const std::string &message);

    DLL_EXPORT_DECL void LogDebug(const std::string &message);

    DLL_EXPORT_DECL void LogInfo(const std::string &message);

    DLL_EXPORT_DECL void LogWarning(const std::string &message);

    DLL_EXPORT_DECL void LogError(const std::string &message);

    DLL_EXPORT_DECL void Critical(const std::string &message);

#define LOG_TRACE(params) SPDLOG_TRACE(params)
#define LOG_DEBUG(params) SPDLOG_DEBUG(params)
#define LOG_INFO(params) SPDLOG_TRACE(params)
#define LOG_WARNING(params) SPDLOG_WARN(params)
#define LOG_CRITICAL(params) SPDLOG_CRITICAL(params)
}


#endif //LOG_H
