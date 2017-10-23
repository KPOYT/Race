#ifndef OSFACTORY_H
#define OSFACTORY_H
#include "../OSFactory.h"
#endif // !OSFACTORY_H

#ifndef WINOSCONSOLE_H
#define WINOSCONSOLE_H
#include "WinOSConsole.h"
#endif // !WINOSCONSOLE_H

#ifndef OSCONFIG_H
#define OSCONFIG_H
#include "../OSConfig.h"
#endif // !OSCONFIG_H


class WinOSFactory : public OSFactory{
	public:
		virtual WinOSConsole* GetConsole();
		virtual OSConfig* GetConfig();
};