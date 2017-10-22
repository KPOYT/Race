#include <windows.h>

#ifndef OS_H
#define OS_H
#include "..\ApplicationOS\OS.h"
#endif

using namespace std;

class Car {
	public:
		Car();

		Car(const COORD pos);

		Car(const int x,
			 const int y);

		~Car();

		virtual void draw();
		virtual void redraw();
		virtual void setSpeed(const int);
		virtual const int getSpeed();
		virtual const int getWidth();
		virtual const int getHeight();
		virtual const COORD getPosition();
		virtual void setPosition(const COORD);
		virtual void setPosition(const int, const int);
		virtual bool isCrashed();
		virtual void isCrashed(bool);

	protected:

		bool crashed;

		OSConsole* console;

		virtual void clear();

		int textColor;
		int borderColor;

		COORD position_;
		COORD oldPosition_;
		const int width_;
		const int height_;
		int speed_;
};