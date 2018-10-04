#ifdef DLL
	#define CALL_API extern "C" __declspec( dllexport )
#else
#ifdef STATIC
	#define CALL_API extern "C"
#else
	#define CALL_API __declspec( dllimport )
#endif
#endif