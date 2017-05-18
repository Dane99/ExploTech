#pragma once

#include "Glm_Common.h"

#include "Entity.h"

class Camera : public Entity
{
	public:
		Camera();

		void updateViewMatrix();

		void keyboardInput(float dt);
		void mouseInput(double xpos, double ypos);

		const Matrix4& getViewMatrix() const;
		const Matrix4& getProjectionMatrix() const;

		Vector3 m_front = Vector3(0.0f, 0.0f, -1.0f);
		Vector3 m_worldUp = Vector3(0.0f, 1.0f, 0.0f);
		Vector3 m_up;
		Vector3 m_right;

		// Returns the direction the player is facing.
		Vector3 getViewVector();

	private:
		// Calculates the front vector from the Camera's (updated) Euler Angles
		void updateCameraVectors();

		Matrix4 m_viewMatrix;
		Matrix4 m_projectionMatrix;

		const float mouseSensitivity = 0.25f;

		double lastX = 0.0;
		double lastY = 0.0;

};