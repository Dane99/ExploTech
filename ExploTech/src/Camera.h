#pragma once
#include "Entity.h"

class Camera : public Entity
{
	public:
		

		void keyboardInput(float dt);
		void mouseInput(double xpos, double ypos);

		Vector3 m_front = Vector3(0.0f, 0.0f, 1.0f);
		Vector3 m_worldUp = Vector3(0.0f, 1.0f, 0.0f);
		Vector3 m_up;
		Vector3 m_right;


	private:
		// Calculates the front vector from the Camera's (updated) Eular Angles
		void updateCameraVectors();

		const float mouseSensitivity = 0.25f;

		double lastX = 0.0;
		double lastY = 0.0;

};