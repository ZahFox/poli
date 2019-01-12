#pragma once

#include <memory>
#include "logging_export.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

class LOGGING_EXPORT Log {
public:
  static void Init();

  inline static std::shared_ptr<spdlog::logger> &GetLogger() {
    return s_Logger;
  }

private:
  static std::shared_ptr<spdlog::logger> s_Logger;
};

#define LOG_TRACE(...) Log::GetLogger()->trace(__VA_ARGS__);

#define LOG_INFO(...) Log::GetLogger()->info(__VA_ARGS__);

#define LOG_WARN(...) Log::GetLogger()->warn(__VA_ARGS__);

#define LOG_ERROR(...) Log::GetLogger()->error(__VA_ARGS__);

#define LOG_FATAL(...) Log::GetLogger()->fatal(__VA_ARGS__);
