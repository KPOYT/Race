#ifndef MENU_H
#define MENU_H
#include "Menu.h"
#endif

class StateMenu : public Menu {
	public:
		StateMenu();

		const int show(
			const int,
			const int);
	protected:
		OSConfig* config;
};