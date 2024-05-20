#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>

class Camera
{
public:
	Camera(const glm::vec3& pos);
	~Camera();
	
	const glm::vec3& direction() const;
	
	void lookAt(const glm::vec3& target);
	void rotate(const glm::vec2& rotation);
	void position(const glm::vec3& pos);
	void move(const glm::vec3& displacement);
	glm::mat4 viewMatrix() const;
	
private:
	glm::vec3 _position;
	glm::vec3 _direction;
	glm::vec3 _up;
	float _yall;
	float _pitch;
};

inline void Camera::move(const glm::vec3& displacement)
{
	_position += displacement;
}

inline const glm::vec3& Camera::direction() const
{
	return _direction;
}

#endif

