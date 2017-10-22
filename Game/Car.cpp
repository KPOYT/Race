#include "Car.h"

Car::Car() :
	width_(OSConfig::CAR_WIDTH),
	height_(OSConfig::CAR_HEIGHT),
	textColor(OSConsole::White),
	borderColor(OSConsole::Black)
{
	position_ = { 0, 0 };
	oldPosition_ = { 0, 0 };
	crashed = false;
	console = OS::GetOSFactory()->GetConsole();
};

Car::Car(const COORD pos) :
	width_(OSConfig::CAR_WIDTH),
	height_(OSConfig::CAR_HEIGHT),
	textColor(OSConsole::White),
	borderColor(OSConsole::Black)
{
	position_ = pos;
	oldPosition_ = pos;
	crashed = false;
	console = OS::GetOSFactory()->GetConsole();
};

Car::Car(const int x,
	const int y) :
	width_(OSConfig::CAR_WIDTH),
	height_(OSConfig::CAR_HEIGHT),
	textColor(OSConsole::White),
	borderColor(OSConsole::Black)
{
	position_ = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	oldPosition_ = position_;
	crashed = false;
	console = OS::GetOSFactory()->GetConsole();
};

Car::~Car()
{
	oldPosition_ = position_;
	clear();
};

bool Car::isCrashed() {
	return crashed;
};

void Car::isCrashed(bool value) {
	crashed = value;
};

void Car::setSpeed(const int value) {
	if (value >= 0 && value <= OSConfig::MAX_SPEED)
		speed_ = value;
};

const int Car::getSpeed() {
	return speed_;
};

const int Car::getWidth() {
	return width_;
};

const int Car::getHeight() {
	return height_;
};

const COORD Car::getPosition() {
	return position_;
};

void Car::setPosition(const COORD pos) {
	oldPosition_ = position_;

	position_ = pos;
};
void Car::setPosition(const int x , const int y) {
	oldPosition_ = position_;

	position_ = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
};

void Car::draw() {
	console->setColor(textColor, borderColor);

	console->fillLine("\xc9", "\xcd", "\xBB", width_, position_.X, position_.Y, true, true, true, textColor, borderColor);
	console->fillSquare("\xba", " ", "\xba", width_, height_ - 2, position_.X, position_.Y + 1, true, true, textColor, borderColor);
	console->fillLine("\xc8", "\xcd", "\xBC", width_, position_.X, position_.Y + height_ - 1, true, true, true, textColor, borderColor);

	if (width_ <= 4) {
		console->drawText(position_.X + 1, position_.Y + 1, "\xc9\xBB", textColor, borderColor);
		console->drawText(position_.X + 1, position_.Y + height_ - 2, "\xc8\xBC", textColor, borderColor);
	}
	else {
		console->fillLine("\xc9", "\xcd", "\xBB", width_ - 2, position_.X + 1, position_.Y + 1, true, true, true, textColor, borderColor);
		console->fillSquare("\xba", " ", "\xba", width_ - 2, height_ - 4, position_.X + 1, position_.Y + 2, true, true, textColor, borderColor);
		console->fillLine("\xc8", "\xcd", "\xBC", width_ - 2, position_.X + 1, position_.Y + height_ - 2, true, true, true, textColor, borderColor);
	}
};

void Car::clear() {
	console->setColor(OSConsole::Black, OSConsole::Black);

	console->fillSquare(" ", width_, height_, oldPosition_.X, oldPosition_.Y);
};

void Car::redraw() {
	if (oldPosition_.X == position_.X && oldPosition_.Y == position_.Y)
		return;

	clear();
	draw();
};