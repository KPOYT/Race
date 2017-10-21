#include <vector>
#include <time.h>

#ifndef USERCAR_H
#define USERCAR_H
#include "UserCar.h"
#endif

using namespace std;

class Generator {
	public:
		Generator();
		~Generator();

		void generate();
		void checkCars(const int);
		void addCar();
		void removeCar(const int index);
		void levelUp();

		void setUserCar(UserCar*);
		void setConfines(
			const int startX,
			const int endX,
			const int endY);
	private:
		bool checkAccident(COORD);
		bool checkPlace(COORD);
		COORD randomPlace();
		const int randomSpeed();

		vector<Car*> list_;
		UserCar* userCar_;

		int level_;
		int startX_;
		int endX_;
		int endY_;
};