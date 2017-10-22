#include "UserCar.h"

UserCar::UserCar() : Car() {
	textColor = OSConsole::LightBlue;
	distance_ = 0.0;
	fuel_ = MAX_FUEL;
};

UserCar::UserCar(const COORD pos) : Car(pos) {
	textColor = OSConsole::LightBlue;
	distance_ = 0.0;
	fuel_ = MAX_FUEL;
};

UserCar::UserCar(const int x,
	const int y) : Car(x, y) {
	textColor = OSConsole::LightBlue;
	distance_ = 0.0;
	fuel_ = MAX_FUEL;
};

void UserCar::setPanel(RightPanel* panel) {
	panel_ = panel;
};

void UserCar::setConfines(const int startX, const int endX) {
	startXConfine_ = startX;
	endXConfine_ = endX;
};

void UserCar::setDistance(const float distance) {
	distance_ += distance;

	setFuel(-(distance / 10));

	panel_->redrawPanel(getDistance(), getSpeed(), getFuel());
};

const int UserCar::getDistance() {
	return static_cast<int>(distance_);
};

void UserCar::setFuel(const float fuel) {
	fuel_ += fuel;

	if (fuel_ <= 0.0) {
		fuel_ = 0.0;
		speed_ = 0;
		isCrashed(true);
	}
};

const int UserCar::getFuel() {
	return static_cast<int>(fuel_);
};

const int UserCar::drive() {
	do
	{
		if (!isCrashed())
		{	
			int code = console->getCodeFromKeyboard();
			if (code == 224)
			{
				code = console->getCodeFromKeyboard();

				switch (code)
				{
				case 72: {
					setSpeed(speed_ + 1);

					oldPosition_.X = position_.X;
					oldPosition_.Y = position_.Y;

					break;
				}
				case 75: {
					if (position_.X <= startXConfine_) {
						position_.X = startXConfine_;
						break;
					}

					oldPosition_.X = position_.X;
					oldPosition_.Y = position_.Y;

					position_.X--;
					break;
				}
				case 77: {
					if (position_.X >= endXConfine_) {
						position_.X = endXConfine_;
						break;
					}

					oldPosition_.X = position_.X;
					oldPosition_.Y = position_.Y;

					position_.X++;
					break;
				}
				case 80: {
					setSpeed(speed_ - 1);

					oldPosition_.X = position_.X;
					oldPosition_.Y = position_.Y;
					break;
				}
				}

				panel_->redrawPanel(getDistance(), getSpeed(), getFuel());

				redraw();
			}
			else
			{
				switch (code)
				{
					case VK_RETURN:
						return Pause;
						break;
					case VK_ESCAPE:
						return Gameover;
						break;
				}
			}
		}
	} while (!isCrashed());

	return Gameover;
};