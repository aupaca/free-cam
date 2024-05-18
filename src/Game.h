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
	
	void draw();
	void update(float dt);
	void onTouchEvent(const anut::MotionEvent& motion);
	
private:
	glm::mat4 _proj;
	glm::vec2 _sensivity;
	glm::vec2 _oldTouchPos;
	float _halfScreenWidth;
	float _velocity;
	int _runFingerId;
	int _camFingerId;
	Camera _freeCam;
	Renderer _renderer;
};

#endif
