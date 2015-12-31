#include <iostream>

#include <plugin.h>
#include <skyscript.h>
#include <windows.h>
#include <DbgHelp.h>
#include <strsafe.h>

#include <Engine/Game.h>

int GenerateDump(EXCEPTION_POINTERS* pExceptionPointers)
{
	BOOL bMiniDumpSuccessful;
	TCHAR szPath[MAX_PATH];
	TCHAR szFileName[MAX_PATH];
	TCHAR* szAppName = "GameWorld";
	DWORD dwBufferSize = MAX_PATH;
	HANDLE hDumpFile;
	SYSTEMTIME stLocalTime;
	MINIDUMP_EXCEPTION_INFORMATION ExpParam;
	GetLocalTime(&stLocalTime);
	GetTempPath(dwBufferSize, szPath);
	StringCchPrintf(szFileName, MAX_PATH, "%s%s", szPath, szAppName);
	CreateDirectory(szFileName, NULL);
	StringCchPrintf(szFileName, MAX_PATH, "Data\\Online\\%04d%02d%02d-%02d%02d%02d-%ld-%ld.dmp",
		stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay,
		stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond,
		GetCurrentProcessId(), GetCurrentThreadId());
	hDumpFile = CreateFile(szFileName, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_WRITE | FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);
	ExpParam.ThreadId = GetCurrentThreadId();
	ExpParam.ExceptionPointers = pExceptionPointers;
	ExpParam.ClientPointers = TRUE;
	bMiniDumpSuccessful = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
		hDumpFile, MiniDumpWithDataSegs, &ExpParam, NULL, NULL);
	return EXCEPTION_EXECUTE_HANDLER;
}

extern "C" __declspec(dllexport) void main()
{
	__try
	{
		InitializeGame();

		while (true)
		{
			Update();
			ScriptDragon::Wait(0);
		}
	}
	__except (GenerateDump(GetExceptionInformation()))
	{}
}
