#include "Camera.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Display.h"

#include "Input/Input_Manager.h"
#include <GLFW/glfw3.h>

// pitch is rotation.x
// yaw is rotation.y



Camera::Camera()
{
	rotation.y = -90.0f;
	updateCameraVectors();
}

void Camera::keyboardInput(float dt)
{
	Vector3 change;
	float speed = 2.0f;
	
	Vector3 frontDirection = glm::normalize(glm::vec3(m_front.x, 0.0f, m_front.z));
	Vector3 rightDirection = glm::normalize(glm::vec3(m_right.x, 0.0f, m_right.z));

	if (Input_Manager::keys[GLFW_KEY_W]) 
	{
		change += frontDirection * speed;
	}

	if (Input_Manager::keys[GLFW_KEY_S])
	{
		change -= frontDirection * speed;
	}

	if (Input_Manager::keys[GLFW_KEY_A])
	{
		change -= rightDirection * speed;
	}

	if (Input_Manager::keys[GLFW_KEY_D])
	{
		change += rightDirection * speed;
	}

	if (Input_Manager::keys[GLFW_KEY_SPACE])
	{
		change += m_worldUp * speed * 2.0f;
	}

	if (Input_Manager::keys[GLFW_KEY_LEFT_CONTROL])
	{
		change -= m_worldUp * speed;
	}

	position += change * dt;

}

void Camera::mouseInput(double xpos, double ypos)
{
	static bool firstMouseInput = true;

	if (firstMouseInput)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouseInput = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	xoffset *= this->mouseSensitivity;
	yoffset *= this->mouseSensitivity;

	this->rotation.y += xoffset;
	this->rotation.x += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped

	if (this->rotation.x > 89.0f) this->rotation.x = 89.0f;

	if (this->rotation.x < -89.0f) this->rotation.x = -89.0f;


	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	Vector3 front;
	front.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
	front.y = sin(glm::radians(rotation.x));
	front.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
	m_front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_up = glm::normalize(glm::cross(m_right, m_front));

}