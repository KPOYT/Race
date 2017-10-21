#include "Map.h"

typedef struct
{
	UserCar* car;
	Generator* generator;
	Map* map;
} MsParams;

void panelUpdate(void* pParams) {
	MsParams * ptr = (MsParams *)pParams;
	UserCar* car = ptr->car;
	Generator* generator = ptr->generator;
	Map* map = ptr->map;
	do {
		if (map->getStatus() == map->Play) {
			int speed = car->getSpeed();
			car->setDistance(speed * 1000 / 60 / 60);
			Sleep(1000);
		}
	} while (!car->isCrashed());
}

void mapUpdate(void* pParams) {
	MsParams * ptr = (MsParams *)pParams;
	UserCar* car = ptr->car;
	Generator* generator = ptr->generator;
	Map* map = ptr->map;
	do {
		if (map->getStatus() == map->Play) {
			int speed = car->getSpeed();
			static int count = 1;

			generator->checkCars(speed);

			if (car->getDistance() / 300 > count) {
				count = car->getDistance() / 300;
				generator->levelUp();
				generator->generate();
			}

			Sleep(100);
		}
	} while (!car->isCrashed());
}

Map::Map():
		width_(30),
		height_(23)
{
	position_ = { 0, 0 };
	userCar = new UserCar(20, 10);
	console = OS::GetOSFactory()->GetConsole();
};

Map::Map(const COORD pos, const int width, const int height) :
	width_(width),
	height_(height)
{
	position_ = pos;
	status_ = Play;
	userCar = new UserCar(20, 10);
	console = OS::GetOSFactory()->GetConsole();
};

Map::Map(const int x, const int y, const int width, const int height) :
	width_(width),
	height_(height)
{
	position_ = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	status_ = Play;
	userCar = new UserCar(20, 15);
	console = OS::GetOSFactory()->GetConsole();
};

const int Map::getStatus() {
	return status_;
};

void Map::draw() {
	drawBorder();
	drawCars();
};

void Map::drawCars() {
	userCar->draw();
	userCar->setConfines(position_.X + 1, position_.X + width_ - userCar->getWidth() - 1);

	generator = new Generator();
	generator->setConfines(position_.X + 1, position_.X + width_ - userCar->getWidth() - 1, position_.Y + height_ - userCar->getHeight());
	generator->setUserCar(userCar);
};

void Map::start() {
	MsParams static params;
	params.car = userCar;
	params.generator = generator;
	params.map = this;

	HANDLE hThr = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)panelUpdate, (void*)&params, 0, NULL);
	HANDLE hThr2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)mapUpdate, (void*)&params, 0, NULL);

	generator->generate();
	int mode;
	do {
		if (status_ == Play)
			status_ = userCar->drive();
		else if (status_ == Pause) {
			console->getCodeFromKeyboard();
			status_ = Play;
		}
	} while (status_ != Gameover);
	
};

void Map::setUserCarPanel(RightPanel* panel) {
	userCar->setPanel(panel);
};

void Map::drawBorder() {
	console->setColor(console->White, console->Black);

	console->fillSquare("\xba", " ", "\xba", width_, height_, position_.X, position_.Y);
};