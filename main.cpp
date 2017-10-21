#include <windows.h>

#ifndef OS_H
#define OS_H
#include "ApplicationOS\OS.h"
#endif

#ifndef RACE_H
#define RACE_H
#include "Game\Race.h"
#endif

const BOOL ShowConsoleCursor(const BOOL bShow)
{
    CONSOLE_CURSOR_INFO cci;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if(hStdOut == INVALID_HANDLE_VALUE)
        return FALSE;

    if(!GetConsoleCursorInfo(hStdOut, &cci))
        return FALSE;

    cci.bVisible = bShow;

    if(!SetConsoleCursorInfo(hStdOut,&cci))
        return FALSE;

    return TRUE;
}

const BOOL SetConsoleSize(const int width, const int height) {
	string params = "mode con";
	params += " cols=" + to_string(width);
	params += " lines=" + to_string(height);

	if (!system(params.c_str()))
		return FALSE;

	return TRUE;
}

void main() {
	OSConfig* config = OS::GetOSFactory()->GetConfig();
	OSConsole* console = OS::GetOSFactory()->GetConsole();

	SetConsoleSize(config->WINDOW_WIDTH, config->WINDOW_HEIGHT);
	ShowConsoleCursor(FALSE);

	Race* race = Race::Instance();
	race->startGame();
}