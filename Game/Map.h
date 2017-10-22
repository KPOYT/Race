#include <process.h>
#include <vector>

#ifndef OS_H
#define OS_H
#include "..\ApplicationOS\OS.h"
#endif

#ifndef TIMERPANEL_H
#define TIMERPANEL_H
#include "..\Panels\TimerPanel.h"
#endif

#ifndef STATEMENU_H
#define STATEMENU_H
#include "..\Menus\StateMenu.h"
#endif

#ifndef GENERATOR_H
#define GENERATOR_H
#include "Generator.h"
#endif

#ifndef CAR_H
#define CAR_H
#include "Car.h"
#endif

#ifndef USERCAR_H
#define USERCAR_H
#include "UserCar.h"
#endif

using namespace std;

class Map {
	public:
		Map();

		Map(const COORD pos, const int width = 30, const int height = 23);
		
		Map(const int x, const int y, const int width = 30, const int height = 23);

		~Map();

		void draw();
		void start();
		void setUserCarPanel(RightPanel*);
		const int getStatus();

		enum MapState
		{
			Play = 1,
			Pause = 2,
			Gameover = 0
		};
	protected:
		OSConsole* console;

	private:
		TimerPanel* timerPanel_;
		StatePanel* statePanel_;
		UserCar* userCar_;
		Generator* generator_;

		void drawBorder();
		void drawCars();

		COORD position_;
		const int width_;
		const int height_;
		int startTime_;
		int status_;

};