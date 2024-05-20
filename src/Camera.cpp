#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Camera::Camera(const glm::vec3& pos)
{
	_position = pos;
	_direction = glm::vec3(1.f, 0.f, 0.f);
	_up = glm::vec3(0.f, 1.f, 0.f);
	_yall = 0.f;
	_pitch = 0.f;
}

Camera::~Camera()
{
	
}
	
void Camera::lookAt(const glm::vec3& target)
{
	_direction = target - _position;
	float length = glm::length(_direction);
	_direction /= length;
	_yall = atan(_direction.z / _direction.x);
	_pitch = asin(_direction.x / length);
}

void Camera::rotate(const glm::vec2& rotation)
{
	_yall += rotation.x;
	_pitch += rotation.y;
	
	if (_pitch > glm::radians(89.9f))
	{
		_pitch = glm::radians(89.9f);
	}
	else if (_pitch < glm::radians(-89.9f))
	{
		_pitch = glm::radians(-89.9f);
	}
	
	_direction.x = cos(_yall) * cos(_pitch);
	_direction.y = sin(_pitch);
	_direction.z = sin(_yall) * cos(_pitch);
}

void Camera::position(const glm::vec3& pos)
{
	_position = pos;
}

glm::mat4 Camera::viewMatrix() const
{
	return glm::lookAt(_position, _position + _direction, _up);
}


