// ConsoleApplication1C.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <windows.h>
#include <stdbool.h>



int main()
{
	

	// additional information
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE mainHANDLE;
	DWORD menuPid = GetCurrentProcessId();

	

	// set the size of the structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// start the program up
	CreateProcess("C:\\Users\\Vinnie\\source\\repos\\Blackout\\Blackout\\bin\\Release\\net6.0 - windows\\Blackout.exe",   // the path
		NULL,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
	);
	mainHANDLE = pi.hProcess;
	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	while (true)
	{
		LPDWORD lpExitCode;
		GetExitCodeProcess(mainHANDLE, lpExitCode);
		if (lpExitCode != STILL_ACTIVE)
			lghlhjhgl
		sleep(1000);
	}
}

HWND g_HWND = NULL;

BOOL CALLBACK EnumWindowsProcMy(HWND hwnd, LPARAM lParam)
{
	DWORD lpdwProcessId;
	GetWindowThreadProcessId(hwnd, &lpdwProcessId);
	if (lpdwProcessId == lParam)
	{
		g_HWND = hwnd;
		return FALSE;
	}
	return TRUE;
}


static void ForceToForeground(HWND window)
{
	DWORD currentThread = GetCurrentThreadId();

	HWND activeWindow = GetForegroundWindow();
	DWORD activeProcess;
	DWORD activeThread = GetWindowProccessThreadId(activeWindow, activeProcess);

	DWORD windowProcess;
	DWORD windowThread = GetWindowThreadProcessId(window, windowProcess);

	if (currentThread != activeThread)
		AttachThreadInput(currentThread, activeThread, true);
	if (windowThread != currentThread)
		AttachThreadInput(windowThread, currentThread, true);

	DWORD oldTimeout = 0, newTimeout = 0;
	SystemParametersInfo(SPI_GETFOREGROUNDLOCKTIMEOUT, 0, oldTimeout, 0);
	SystemParametersInfo(SPI_SETFOREGROUNDLOCKTIMEOUT, 0, newTimeout, 0);
	LockSetForegroundWindow(LSFW_UNLOCK);
	AllowSetForegroundWindow(ASFW_ANY);

	SetForegroundWindow(window);
	ShowWindow(window, SW_RESTORE);

	SystemParametersInfo(SPI_SETFOREGROUNDLOCKTIMEOUT, 0, oldTimeout, 0);

	if (currentThread != activeThread)
		AttachThreadInput(currentThread, activeThread, false);
	if (windowThread != currentThread)
		AttachThreadInput(windowThread, currentThread, false);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
