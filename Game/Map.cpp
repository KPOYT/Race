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
		if (map->getStatus() != map->Gameover && car->isCrashed())
			map->setStatus(map->Gameover);

		if (map->getStatus() == map->Play) {
			int speed = car->getSpeed();
			int time = clock() / CLOCKS_PER_SEC - ptr->startTime - pauseTime;
			float metersInSecond = speed * 1000 / 60 / 60;
			car->setDistance(metersInSecond);
			panel->redrawPanel(time);
			Sleep(OSConfig::TIMER_SLEEP);
		}
		else if (map->getStatus() == map->Pause) {
			++pauseTime;
			Sleep(OSConfig::TIMER_SLEEP);
		}
	} while (map->getStatus() != map->Gameover);
	ExitThread(0);
}

void mapUpdate(void* pParams) {
	MsParams * ptr = (MsParams *)pParams;
	UserCar* car = ptr->car;
	Generator* generator = ptr->generator;
	Map* map = ptr->map;
	int count = 1;
	do {
		if (map->getStatus() != map->Gameover && car->isCrashed())
			map->setStatus(map->Gameover);

		if (map->getStatus() == map->Play) {
			int speed = car->getSpeed();

			generator->checkCars(speed);

			if (car->getDistance() / OSConfig::DISTANCE_TO_LEVEL_UP > count) {
				count = car->getDistance() / OSConfig::DISTANCE_TO_LEVEL_UP;
				generator->levelUp();
				generator->generate();
			}

			Sleep(OSConfig::SPEED_SLEEP - car->getSpeed() / 3);
		}
	} while (map->getStatus() != map->Gameover);
	ExitThread(0);
}

Map::Map() :
	width_(OSConfig::MAP_WIDTH),
	height_(OSConfig::MAP_HEIGHT)
{
	position_ = { 0, 0 };
	status_ = Play;
	startTime_ = clock() / CLOCKS_PER_SEC;
	userCar_ = new UserCar(OSConfig::CAR_POSITION_X, OSConfig::CAR_POSITION_Y);
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
	userCar_ = new UserCar(OSConfig::CAR_POSITION_X, OSConfig::CAR_POSITION_Y);
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
	userCar_ = new UserCar(OSConfig::CAR_POSITION_X, OSConfig::CAR_POSITION_Y);
	timerPanel_ = new TimerPanel(position_.X + width_ + 2, position_.Y + (height_ / 3), "Game time:");
	console = OS::GetOSFactory()->GetConsole();
};

Map::~Map() {
	setStatus(Gameover);
	userCar_->isCrashed(true);
	delete userCar_;
	delete statePanel_;
	delete generator_;
}

const int Map::getStatus() {
	return status_;
};

void Map::setStatus(const int status) {
	status_ = status;
}

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

	panelThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)panelUpdate, (void*)&params, 0, NULL);
	mapThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)mapUpdate, (void*)&params, 0, NULL);

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