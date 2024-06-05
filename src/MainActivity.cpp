#include "MainActivity.h"
#include "Game.h"

void MainActivity::onSurfaceCreated()
{
	anut::Engine::window->setFlags(AWINDOW_FLAG_FULLSCREEN, AWINDOW_FLAG_FULLSCREEN);
	_game = new Game;
	_timer.start();
}

void MainActivity::onSurfaceDestroyed()
{
	delete _game;
}

int MainActivity::onInputEvent(AInputEvent* event)
{
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
	{
		anut::MotionEvent motion(event);
		if (motion.action != anut::MotionEvent::ACTION_MOVE)
		{
			_game->handleTouch(motion);
			return 1;
		}
		
		int pointersCount = AMotionEvent_getPointerCount(event);
		for (int i = 0; i < pointersCount; i++)
		{
			motion.id = AMotionEvent_getPointerId(event, i);
			motion.x = AMotionEvent_getX(event, i);
			motion.y = AMotionEvent_getY(event, i);
			_game->handleTouch(motion);
		}
		return 1;
	}
	return 0;
}

void MainActivity::onProcessApp()
{
	if (_game->needRedraw())
	{
		_game->draw();
		anut::Engine::window->display();
	}
	_game->update(_timer.restart());
}

