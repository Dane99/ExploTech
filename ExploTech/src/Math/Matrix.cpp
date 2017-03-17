#include "Matrix.h"

#include "../Entity.h"
#include "../Display.h"
#include "../Camera.h"

namespace Math
{
	Matrix4 createViewMatrix(const Camera& entity)
	{
		return glm::lookAt(entity.position, entity.position + entity.m_front, entity.m_up);
	}
	
	Matrix4 createModelMatrix(const Entity& entity)
	{
		Matrix4 matrix;

		matrix = glm::translate(matrix, entity.position);

		matrix = glm::rotate(matrix, glm::radians(entity.rotation.x), { 1, 0, 0 });
		matrix = glm::rotate(matrix, glm::radians(entity.rotation.y), { 0, 1, 0 });
		matrix = glm::rotate(matrix, glm::radians(entity.rotation.z), { 0, 0, 1 });

		return matrix;
	}
	
	Matrix4 createProjMatrix()
	{
		return glm::perspective(glm::radians(70.0f),
								((float)Display::WIDTH / (float)Display::HEIGHT),
								0.001f,
								1000.0f);
	}
}
