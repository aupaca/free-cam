#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Game.h"
#include "Shape.h"
#include "World.h"

Game::Game()
	: _freeCam({0.f, 0.f, 0.f})
{
	_sensivity.x = glm::radians(90.f) / 500.f;
	_sensivity.y = -glm::radians(90.f) / 500.f;
	_velocity = 5.f;
	_halfScreenWidth = anut::Engine::window->width() / 2.f;
	_runFingerId = -1;
	_camFingerId = -1;
	_updateFrame = true;
	_freeCam.lookAt({0.f, 0.f, -1.f});
	loadWorld();
}

Game::~Game()
{
	
}

void Game::loadWorld()
{
	Box cube({1.f, 1.f, 1.f});
	Pyramid pyramid({1.f, 1.f, 1.f});
	World world;
	world.add(cube, {0.f, 0.f, -4.f});
	world.add(cube, {2.f, 0.f, -4.f});
	world.add(cube, {5.f, 0.f, -2.f});
	world.add(pyramid, {5.f, 1.f, -2.f});
	world.add(pyramid, {2.f, 0.f, 2.f});
	_renderer.loadData(world.vertexData(), world.indexData());
}

void Game::draw()
{
	_updateFrame = false;
	_renderer.setUniform("view", _freeCam.viewMatrix());
	_renderer.draw();
}

void Game::update(float dt)
{
	if (_runFingerId != -1)
	{
		_freeCam.move(_velocity * dt * _freeCam.direction());
		_updateFrame = true;
	}
}

void Game::handleTouch(const anut::MotionEvent& motion)
{
	glm::vec2 touchPos = glm::vec2(motion.x, motion.y);
	switch (motion.action)
	{
		case anut::MotionEvent::ACTION_DOWN:
			if (touchPos.x > _halfScreenWidth)
			{
				if (_camFingerId == -1)
				{
					_camFingerId = motion.id;
					_prevTouchPos = touchPos;
				}
			}
			else if (_runFingerId == -1)
			{
				_runFingerId = motion.id;
			}
			
			break;
			
		case anut::MotionEvent::ACTION_MOVE:
			if (motion.id == _camFingerId)
			{
				_freeCam.rotate(_sensivity * (touchPos - _prevTouchPos));
				_prevTouchPos = touchPos;
				_updateFrame = true;
			}
			break;
			
		case anut::MotionEvent::ACTION_UP:
			if (motion.id == _camFingerId)
			{
				_camFingerId = -1;
			}
			else if (motion.id == _runFingerId)
			{
				_runFingerId = -1;
			}
			break;
	}
}

