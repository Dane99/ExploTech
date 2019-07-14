#pragma once

#include "Shader_Program.h"

namespace Shader
{
	class Text_Shader : public Shader_Program
	{
	public:
		Text_Shader();
		void setProjMatrix(const Matrix4& matrix);
		void setColorVector(const Vector3& vector);

	private:
		void getUniformLocations() override;

		GLuint m_locationProjMatrix = 0;
		GLuint m_locationColor = 0;
	};
}