#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Game.h"
#include "Shape.h"
#include "World.h"

Game::Game()
	: _renderer("./src/shader/base.vert", "./src/shader/base.frag")
	, _freeCam({0.f, 0.f, 0.f})
{
	_sensivity.x = -glm::radians(90.f) / 500.f;
	_sensivity.y = glm::radians(90.f) / 500.f;
	_velocity = 5.f;
	_halfScreenWidth = anut::Engine::window->width() / 2.f;
	_runFingerId = -1;
	_camFingerId = -1;
	
	_freeCam.lookAt({0.f, 0.f, -1.f});
	
	Box cube({1.f, 1.f, 1.f});
	Pyramid pyramid({1.f, 1.f, 1.f});
	World world;
	
	cube.position({0.f, 0.f, -4.f});
	world.add(cube);
	cube.position({2.f, 0.f, -4.f});
	world.add(cube);
	cube.position({5.f, 0.f, -2.f});
	world.add(cube);
	pyramid.position({5.f, 1.f, -2.f});
	world.add(pyramid);
	pyramid.position({2.f, 0.f, 2.f});
	world.add(pyramid);
	
	_renderer.loadData(world.vertexData(), world.indexData());
	
	_proj = glm::perspective(glm::radians(45.f), anut::Engine::window->aspectRatio(), 0.1f, 100.f);
	_renderer.setUniform("proj", _proj);
	_renderer.setUniform("view", _freeCam.viewMatrix());
	
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}

Game::~Game()
{
	
}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_renderer.draw();
}

void Game::update(float dt)
{
	if (_runFingerId != -1)
	{
		_freeCam.move(_velocity * dt * _freeCam.direction());
	}
	
	_renderer.setUniform("view", _freeCam.viewMatrix());
}

void Game::onTouchEvent(const anut::MotionEvent& motion)
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
					_oldTouchPos = touchPos;
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
				_freeCam.rotate(_sensivity * (_oldTouchPos - touchPos));
				_oldTouchPos = touchPos;
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

