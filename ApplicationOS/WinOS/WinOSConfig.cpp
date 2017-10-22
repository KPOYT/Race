#include "WinOSConfig.h"

WinOSConfig::WinOSConfig() {};
WinOSConfig::~WinOSConfig() {};

WinOSConfig* WinOSConfig::_instance = 0;

WinOSConfig* WinOSConfig::Instance() {
	if (_instance == 0) {
		_instance = new WinOSConfig();
	}
	return _instance;
}