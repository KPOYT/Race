#include <iostream>
#include <windows.h>

#ifndef STATEMENU_H
#define STATEMENU_H
#include "..\Menus\StateMenu.h"
#endif

#ifndef RIGHTPANEL_H
#define RIGHTPANEL_H
#include "..\Panels\RightPanel.h"
#endif

#ifndef MAP_H
#define MAP_H
#include "Map.h"
#endif

using namespace std;

class Game {
	public:
		Game();
		~Game();

		void draw();
	protected:
		OSConsole* console;
		OSConfig* config;
	private:
		Map* map_;
		RightPanel* rightPanel_;
		int status_;
};