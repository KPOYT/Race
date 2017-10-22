#include "Map.h"

typedef struct
{
	TimerPanel* panel;
	UserCar* car;
	Generator* generator;
	Map* map;
	int startTime;
} MsParams;

void panelUpdate(void* pParams) {
	MsParams * ptr = (MsParams *)pParams;
	TimerPanel* panel = ptr->panel;
	UserCar* car = ptr->car;
	Map* map = ptr->map;
	int pauseTime = 0;
	do {
		if (map->getStatus() == map->Play) {
			int speed = car->getSpeed();
			int time = clock() / CLOCKS_PER_SEC - ptr->startTime - pauseTime;
			car->setDistance(speed * 1000 / 60 / 60);
			panel->redrawPanel(time);
			Sleep(1000);
		}
		else if (map->getStatus() == map->Pause) {
			++pauseTime;
			Sleep(1000);
		}
	} while (car && !car->isCrashed());
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
	} while (car && !car->isCrashed());
}

Map::Map():
		width_(30),
		height_(23)
{
	position_ = { 0, 0 };
	status_ = Play;
	startTime_ = clock() / CLOCKS_PER_SEC;
	userCar_ = new UserCar(20, 10);
	timerPanel_ = new TimerPanel(position_.X + width_ + 2, position_.Y + (height_ / 3), "Game time:");
	console = OS::GetOSFactory()->GetConsole();
};

Map::Map(const COORD pos, const int width, const int height) :
	width_(width),
	height_(height)
{
	position_ = pos;
	status_ = Play;
	startTime_ = clock() / CLOCKS_PER_SEC;
	userCar_ = new UserCar(20, 15);
	timerPanel_ = new TimerPanel(position_.X + width_ + 2, position_.Y + (height_ / 3), "Game time:");
	console = OS::GetOSFactory()->GetConsole();
};

Map::Map(const int x, const int y, const int width, const int height) :
	width_(width),
	height_(height)
{
	position_ = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	status_ = Play;
	startTime_ = clock() / CLOCKS_PER_SEC;
	userCar_ = new UserCar(20, 15);
	timerPanel_ = new TimerPanel(position_.X + width_ + 2, position_.Y + (height_ / 3), "Game time:");
	console = OS::GetOSFactory()->GetConsole();
};

Map::~Map() {
	userCar_->isCrashed(true);
	delete userCar_;
	delete statePanel_;
	delete generator_;
}

const int Map::getStatus() {
	return status_;
};

void Map::draw() {
	drawBorder();
	drawCars();
};

void Map::drawCars() {
	userCar_->draw();
	userCar_->setConfines(position_.X + 1, position_.X + width_ - userCar_->getWidth() - 1);

	generator_ = new Generator();
	generator_->setConfines(position_.X + 1, position_.X + width_ - userCar_->getWidth() - 1, position_.Y + height_ - userCar_->getHeight());
	generator_->setUserCar(userCar_);
};

void Map::start() {
	MsParams static params;
	params.car = userCar_;
	params.panel = timerPanel_;
	params.generator = generator_;
	params.startTime = startTime_;
	params.map = this;

	HANDLE hThr = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)panelUpdate, (void*)&params, 0, NULL);
	HANDLE hThr2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)mapUpdate, (void*)&params, 0, NULL);

	generator_->generate();

	statePanel_ = new StatePanel(position_.X + width_ + 6, position_.Y + (height_ / 2), "");
	timerPanel_->show();

	int mode;
	do {
		if (status_ == Play)
			status_ = userCar_->drive();
		else if (status_ == Pause) {
			
			statePanel_->redrawPanel("PAUSE");
			console->getCodeFromKeyboard();
			statePanel_->redrawPanel("     ");
			status_ = Play;
		}
	} while (status_ != Gameover);

	StateMenu menu;
	menu.show(userCar_->getDistance(), timerPanel_->getTime());
	console->getCodeFromKeyboard();
};

void Map::setUserCarPanel(RightPanel* panel) {
	userCar_->setPanel(panel);
};

void Map::drawBorder() {
	console->setColor(console->White, console->Black);

	console->fillSquare("\xba", " ", "\xba", width_, height_, position_.X, position_.Y);
};