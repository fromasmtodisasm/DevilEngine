#pragma once

#ifdef WIN32
	#ifdef DEVILGAME_EXPORTS
		#define CRYGAME_API __declspec(dllexport)
	#else
		#define DEVILGAME_API __declspec(dllimport)
	#endif
#else
	#define DEVILGAME_API
#endif