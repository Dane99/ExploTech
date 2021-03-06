#pragma once
#include "GL/glew.h"

#include <vector>

class Model 
{
	public:
		Model() = default;

		Model(const std::vector<GLfloat>& vertexPositions,
			  const std::vector<GLfloat>& textureCoordinates,
			  const std::vector<GLuint>& indices);

		~Model();

		void addData(const std::vector<GLfloat>& vertexPositions,
			 		 const std::vector<GLfloat>& textureCoordinates,
					 const std::vector<GLfloat>& layers,
	  			 	 const std::vector<GLuint>& indices);

		void addData(const std::vector<GLfloat>& vertexPositions,
					 const std::vector<GLfloat>& textureCoordinates,
					 const std::vector<GLuint>& indices);

		void bind() const;
		void unbind() const;

		void reset();

		GLuint getIndicesCount() const;

	private:
		void addVBO(int dim, const std::vector<GLfloat>& data);
		void addVBO(int dim, const std::vector<GLuint>& data);
		void addEBO(const std::vector<GLuint>& indices);

		std::vector<GLuint> m_buffers;

		GLuint m_vao = 0;
		GLuint m_vboCount = 0;
		GLuint m_indicesCount = 0;
};