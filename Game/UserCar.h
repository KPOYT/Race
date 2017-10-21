#ifndef CAR_H
#define CAR_H
#include "Car.h"
#endif

#ifndef RIGHTPANEL_H
#define RIGHTPANEL_H
#include "..\Panels\RightPanel.h"
#endif

class UserCar : public Car {
	public:
		UserCar();

		UserCar(const COORD pos);

		UserCar(const int x,
			 const int y);

		void setConfines(const int startX, const int endX);
		void setPanel(RightPanel*);
		const int drive();
		void setDistance(const float);
		const int getDistance();
		void setFuel(const float);
		const int getFuel();

		enum CarState
		{
			Pause = 2,
			Gameover = 0
		};
	private:
		const float MAX_FUEL = 1000.0;

		RightPanel* panel_;

		int startXConfine_;
		int endXConfine_;
		float distance_;
		float fuel_;
};