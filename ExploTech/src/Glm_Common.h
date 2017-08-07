#pragma once

// GLM header includes and typedefs
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef glm::vec2 Vector2;
typedef glm::ivec2 IntVector2;
typedef glm::vec3 Vector3;
typedef glm::ivec3 IntVector3;
typedef glm::vec4 Vector4;
typedef glm::ivec4 IntVector4;

typedef glm::mat4 Matrix4;


// TODO add more entity types (i.e. like animals).
enum class EntityType
{
	Player = 0,
	MovingBlock,
	
	MAX_ELEMENT_COUNT
};