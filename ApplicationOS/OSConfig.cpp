#include "OSConfig.h"

OSConfig::OSConfig() {};
OSConfig::~OSConfig() {};

OSConfig* OSConfig::_instance = 0;

OSConfig* OSConfig::Instance() {
	if (_instance == 0) {
		_instance = new OSConfig();
	}
	return _instance;
}