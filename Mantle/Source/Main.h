#pragma once
#include "MEngine.h"
#include "Log.h"

//#ifdef MTL_PLATFORM_WINDOWS
	//class MEngine;
	// Implemented in Client.
	extern mtl::MEngine* mtl::StartClient();

int main(int argc, char** argv)
{
	mtl::Log::InitLog();
	
	LOG_MTL_WARN("Init LOG_MTL done.");
	
	std::string a = "YES";
	LOG_APP_INFO("Init LOG_APP done. = {0}", a);

	auto app = mtl::StartClient();
	app->Run();
	delete app;
}

//#endif