#include "Generator.h"

Generator::Generator() {
	level_ = 1;
};
Generator::~Generator() { 
	list_.clear();
};

void Generator::generate() {
	for (int i = 0; i < level_; i++) {
		if (list_.size() < level_) {
			addCar();
		}
	};
};

void Generator::checkCars(const int speed) {
	srand(GetTickCount());
	for (int i = 0; i < list_.size(); i++) {
		COORD pos = list_[i]->getPosition();
		
		if (list_[i]->getSpeed() < speed) {
			pos.Y += 1;

			if (pos.Y >= endY_) {
				removeCar(i);
				addCar();
			} else if (checkAccident(pos)) {
				userCar_->isCrashed(true);
			} else {
				list_[i]->setPosition(pos);
				list_[i]->redraw();
			}
		} else
			list_[i]->setSpeed(list_[i]->getSpeed() - 1);
	};
};

void Generator::addCar() {
	Car* car = new Car(randomPlace());
	car->setSpeed(randomSpeed());
	list_.push_back(car);
};

void Generator::removeCar(const int index) {
	Car* car = list_[index];
	list_.erase(list_.begin() + index);
	list_.swap(list_);
	delete car;
};

void Generator::levelUp() {
	if (level_ >= 3)
		return;

	++level_;
};

COORD Generator::randomPlace() {
	bool isFind = false;
	COORD coord = { 0, 0 };

	srand(GetTickCount());

	do {
		coord.X = startX_ + rand() % endX_;

		if (checkPlace(coord))
			isFind = true;

	} while (!isFind);

	return coord;
};

bool Generator::checkAccident(COORD coord) {
	COORD pos = userCar_->getPosition();
	int width = userCar_->getWidth();
	int height = userCar_->getHeight();

	if (((coord.X + width > pos.X && coord.X <= pos.X) 
		|| (coord.X < pos.X + width && coord.X >= pos.X))
		&& ((coord.Y + height - 1 > pos.Y && coord.Y < pos.Y) 
		|| (coord.Y < pos.Y + height && coord.Y > pos.Y)))
		return true;

	else if (((coord.X + width > pos.X && coord.X <= pos.X)
		|| (coord.X < pos.X + width && coord.X >= pos.X))
		&& ((coord.Y + height - 1 > pos.Y && coord.Y < pos.Y)
		|| (coord.Y < pos.Y + height && coord.Y > pos.Y)))
		return true;

	return false;
};

bool Generator::checkPlace(COORD coord) {
	if (coord.X < startX_ || coord.X > endX_)
		return false;

	for (int i = 0; i < list_.size(); i++) {
		COORD pos = list_[i]->getPosition();
		int width = list_[i]->getWidth();

		if (coord.X <= pos.X + width && coord.X >= pos.X)
			return false;

		else if (coord.X + width >= pos.X && coord.X < pos.X)
			return false;
	}

	return true;
};

void Generator::setUserCar(UserCar* userCar) {
	userCar_ = userCar;
};

const int Generator::randomSpeed() {
	bool isFind = false;
	int speed = 0;
	int randLevel = 2 * level_ * level_;

	srand(GetTickCount());

	do {
		speed = userCar_->getSpeed() - rand() % randLevel;
		if (speed > 0 && speed < userCar_->getSpeed())
			isFind = true;
		else if (userCar_->getSpeed() <= 2) {
			speed = 1;
			isFind = true;
		}

	} while (!isFind);

	return speed;
};

void Generator::setConfines(
	const int startX,
	const int endX,
	const int endY) {
	startX_ = startX;
	endX_ = endX;
	endY_ = endY;
};