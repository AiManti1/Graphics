#include "mtlpch.h"
#include "Log.h"
#include "spdlog/sinks//stdout_color_sinks.h"


namespace mtl {
	
	std::shared_ptr<spdlog::logger> Log::s_MantleLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::InitLog()
	{
		// Custom Formatting [see Wiki -> custom formatting on GitHub].
		// %Time stamp %name of the Log (Core or Client) %log message
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_MantleLogger = spdlog::stdout_color_mt("LOG_MTL");
		// Keep level at trace, i.e. for printing everything.
		s_MantleLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("LOG_APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}