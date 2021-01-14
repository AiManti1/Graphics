#pragma once
#include "Macros.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace mtl {

	class MTL Log
	{
	public:
		static void InitLog();
	
		// Pass by reference, i.e. we don't need reference counting, no ownership, just access.
		inline static std::shared_ptr<spdlog::logger>& GetMantleLogger() { return s_MantleLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		// static, i.e. lifetime moduled.
		static std::shared_ptr<spdlog::logger> s_MantleLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Mantle log macros.
// [mtl::Log::GetMantleLogger()->warn]("Init Mantle Log done.");
 
#define LOG_MTL_TRACE(...)    ::mtl::Log::GetMantleLogger()->trace(__VA_ARGS__)		// C++20: (__VA_OPT__)
#define LOG_MTL_INFO(...)     ::mtl::Log::GetMantleLogger()->info(__VA_ARGS__)
#define LOG_MTL_WARN(...)     ::mtl::Log::GetMantleLogger()->warn(__VA_ARGS__)
#define LOG_MTL_ERROR(...)    ::mtl::Log::GetMantleLogger()->error(__VA_ARGS__)
#define LOG_MTL_FATAL(...)    ::mtl::Log::GetMantleLogger()->fatal(__VA_ARGS__)

// Client log macros.
// [mtl::Log::GetClientLogger()->info]("Init Client Log done. = {0}", a);

#define LOG_APP_TRACE(...)	      ::mtl::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_APP_INFO(...)	      ::mtl::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_APP_WARN(...)	      ::mtl::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_APP_ERROR(...)	      ::mtl::Log::GetClientLogger()->error(__VA_ARGS__)
#define LOG_APP_FATAL(...)	      ::mtl::Log::GetClientLogger()->fatal(__VA_ARGS__)

// If dist-release build.
// define MTL_Mantle_INFO // designe as nothing