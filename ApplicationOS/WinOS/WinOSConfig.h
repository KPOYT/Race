#ifndef OSCONFIG_H
#define OSCONFIG_H
#include "..\OSConfig.h"
#endif // !OSCONFIG_H

class WinOSConfig : public OSConfig {
	public:
		static WinOSConfig* Instance();
		
		static const int WINDOW_WIDTH = 80;
		static const int WINDOW_HEIGHT = 25;

		static const int MAP_X = 15;
		static const int MAP_Y = 1;
		static const int MAP_WIDTH = 30;
		static const int MAP_HEIGHT = 23;
		static const int TIMER_SLEEP = 1000;
		static const int SPEED_SLEEP = 100;
		static const int DISTANCE_TO_LEVEL_UP = 300;

		static const int CAR_POSITION_X = 24;
		static const int CAR_POSITION_Y = 15;

		static const int CAR_WIDTH = 4;
		static const int CAR_HEIGHT = 4;
		static const int MAX_SPEED = 200;
		static const int PROPORTION_FUEL_TO_SPEED = 10;

		static const int RIGHT_PANEL_WIDTH = 20;

		static const int EXIT_MENU_X = 33;
		static const int EXIT_MENU_Y = 10;

	protected:
		WinOSConfig();
		virtual ~WinOSConfig();

	private:
		static WinOSConfig* _instance;
};