#pragma once

// shared AMX/SA:MP stuff
extern void** ppPluginData;
extern void* pAMXFunctions;
typedef void (*logprintf_t)(const char* szFormat, ...);
extern logprintf_t logprintf;
