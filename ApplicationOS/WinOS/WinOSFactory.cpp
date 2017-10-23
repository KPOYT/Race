#include "WinOSFactory.h"

WinOSConsole* WinOSFactory::GetConsole() {
	return WinOSConsole::Instance();
}

OSConfig* WinOSFactory::GetConfig() {
	return OSConfig::Instance();
}