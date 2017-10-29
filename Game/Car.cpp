#include "Car.h"

Car::Car() :
	width(OSConfig::CAR_WIDTH),
	height(OSConfig::CAR_HEIGHT),
	textColor(OSConsole::White),
	borderColor(OSConsole::Black)
{
	position = { 0, 0 };
	oldPosition = { 0, 0 };
	crashed = false;
	console = OS::GetOSFactory()->GetConsole();
};

Car::Car(const COORD pos) :
	width(OSConfig::CAR_WIDTH),
	height(OSConfig::CAR_HEIGHT),
	textColor(OSConsole::White),
	borderColor(OSConsole::Black)
{
	position = pos;
	oldPosition = pos;
	crashed = false;
	console = OS::GetOSFactory()->GetConsole();
};

Car::Car(const int x,
	const int y) :
	width(OSConfig::CAR_WIDTH),
	height(OSConfig::CAR_HEIGHT),
	textColor(OSConsole::White),
	borderColor(OSConsole::Black)
{
	position = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	oldPosition = position;
	crashed = false;
	console = OS::GetOSFactory()->GetConsole();
};

Car::~Car()
{
	oldPosition = position;
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
		speed = value;
};

const int Car::getSpeed() {
	return speed;
};

const int Car::getWidth() {
	return width;
};

const int Car::getHeight() {
	return height;
};

const COORD Car::getPosition() {
	return position;
};

void Car::setPosition(const COORD pos) {
	oldPosition = position;

	position = pos;
};
void Car::setPosition(const int x , const int y) {
	oldPosition = position;

	position = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
};

void Car::draw() {
	console->setColor(textColor, borderColor);

	console->fillLine("\xc9", "\xcd", "\xBB", width, position.X, position.Y, true, true, true, textColor, borderColor);
	console->fillSquare("\xba", " ", "\xba", width, height - 2, position.X, position.Y + 1, true, true, textColor, borderColor);
	console->fillLine("\xc8", "\xcd", "\xBC", width, position.X, position.Y + height - 1, true, true, true, textColor, borderColor);

	if (width <= 4) {
		console->drawText(position.X + 1, position.Y + 1, "\xc9\xBB", textColor, borderColor);
		console->drawText(position.X + 1, position.Y + height - 2, "\xc8\xBC", textColor, borderColor);
	}
	else {
		console->fillLine("\xc9", "\xcd", "\xBB", width - 2, position.X + 1, position.Y + 1, true, true, true, textColor, borderColor);
		console->fillSquare("\xba", " ", "\xba", width - 2, height - 4, position.X + 1, position.Y + 2, true, true, textColor, borderColor);
		console->fillLine("\xc8", "\xcd", "\xBC", width - 2, position.X + 1, position.Y + height - 2, true, true, true, textColor, borderColor);
	}
};

void Car::clear() {
	console->setColor(OSConsole::Black, OSConsole::Black);

	console->fillSquare(" ", width, height, oldPosition.X, oldPosition.Y);
};

void Car::redraw() {
	if (oldPosition.X == position.X && oldPosition.Y == position.Y)
		return;

	clear();
	draw();
};