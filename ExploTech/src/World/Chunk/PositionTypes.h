#pragma once

#include <cstdint>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>

namespace PositionTypes {
	typedef sf::Vector3<int8_t>  Small_Position;
	typedef sf::Vector3<int32_t> Large_Position;
}