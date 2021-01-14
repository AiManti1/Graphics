#pragma once

#ifdef MTL_PLATFORM_WINDOWS
	// Defined only for Mantle project.
	#ifdef MTL_BUILD_DLL							
		#define MTL __declspec(dllexport)
	#else
		#define MTL __declspec(dllimport)
	#endif

#else
		#error MTL DLL only supports Windows.

#endif









