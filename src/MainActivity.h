#ifndef MAIN_ACTIVITY_H
#define MAIN_ACTIVITY_H
#include <ANUT/ANUT.h>
#include <ANUT/ANUT_utils.h>

class Game;

class MainActivity : public anut::Activity
{
public:
	void onSurfaceCreated() override;
	void onSurfaceDestroyed() override;
	int onInputEvent(AInputEvent* event) override;
	void onProcessApp() override;
	
private:
	Game* _game;
	anut::Timer _timer;
};

#endif
