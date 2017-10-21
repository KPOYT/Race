#include "OSConsole.h"

OSConsole::OSConsole() {};
OSConsole::~OSConsole() {};

OSConsole* OSConsole::_instance = 0;
bool OSConsole::_status = Free;

OSConsole* OSConsole::Instance() {
	return _instance;
}

const bool OSConsole::status() { return _status; }