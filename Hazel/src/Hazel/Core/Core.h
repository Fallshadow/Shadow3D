#pragma once

namespace Hazel {
	void InitializeCore();
	void ShutdownCore();
}

#ifdef HAZEL_BUILD_DLL
	#define HAZEL_API __declspec(dllexport)
#else 
	#define HAZEL_API __declspec(dllimport)
#endif