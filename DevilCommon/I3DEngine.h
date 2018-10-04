#pragma once

#ifdef WIN32
	#ifdef DEVIL3DENGINE_EXPORTS
		#define DEVIL3DENGINE_API __declspec(dllexport)
	#else
		#define DEVIL3DENGINE __declspec(dllimport)
	#endif
#else
	#define DEVIL3DENGINE
#endif