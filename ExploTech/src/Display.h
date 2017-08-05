#pragma once

struct GLFWwindow;

namespace Display {

	constexpr static int WIDTH = 640;
	constexpr static int HEIGHT = 480;

	void init();
	void close();

	void clear();
	void update();

	bool isOpen();

	GLFWwindow* get();
}