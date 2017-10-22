#ifndef MENU_H
#define MENU_H
#include "Menu.h"
#endif

class StateMenu : public Menu {
	public:
		StateMenu();

		const int show(
			const int score);
	protected:
		OSConfig* config;
};