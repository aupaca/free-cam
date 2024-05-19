#ifndef GAME_H
#define GAME_H
#include <ANUT/ANUT.h>
#include <glm/glm.hpp>
#include "Renderer.h"
#include "Camera.h"

class Game
{
public:
	Game();
	~Game();
	
	bool needRedraw() const;
	
	void draw();
	void update(float dt);
	void onTouchEvent(const anut::MotionEvent& motion);
	
private:
	void loadWorld();
	
	glm::vec2 _sensivity;
	glm::vec2 _prevTouchPos;
	float _halfScreenWidth;
	float _velocity;
	int _runFingerId;
	int _camFingerId;
	Camera _freeCam;
	Renderer _renderer;
	bool _updateFrame;
};


inline bool Game::needRedraw() const
{
	return _updateFrame;
}

#endif
