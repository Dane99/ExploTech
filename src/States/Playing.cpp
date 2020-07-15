#include "Playing.h"

namespace State {
	
	sf::Clock generalClock;
	sf::Clock randClock;

	Playing::Playing()
		: Game_State()
		, worldManager()
	{
		worldManager.addChunk(IntVector3(0, 0, 0));

		srand(time(NULL));
	}

	void Playing::input()
	{
	}

	void Playing::update(float dt)
	{
		worldManager.update(Application::get().getCamera().position);
	}

	void Playing::draw(Renderer::Master& renderer)
	{
		renderer.addToMasterRenderList(worldManager);
		renderer.addToMasterRenderList(hud);
		renderer.addToMasterRenderList(Text_Manager::get());
	}

	void Playing::updateMouseClickInput(bool left, bool right)
	{
		if (raycasting) 
		{
			Vector3 facingDirection = Application::get().getCamera().getViewVector() * REACH_RESOLUTION;
			Vector3 currentPosition = Application::get().getCamera().position;
			if (left) 
			{
				for (int i = 0; i < static_cast<int>((1.0f / REACH_RESOLUTION) * PLAYER_REACH_DISTANCE); ++i)
				{
					currentPosition.x += facingDirection.x;
					currentPosition.y += facingDirection.y;
					currentPosition.z += facingDirection.z;

					if (worldManager.GetBlock(Vector3(currentPosition.x, currentPosition.y, currentPosition.z)) != Block::ID::Air) 
					{
						worldManager.setBlock(Vector3(currentPosition.x, currentPosition.y, currentPosition.z), Block::ID::Air);
						break;
					}
				}
			}
			if (right) 
			{
				for (int i = 0; i < static_cast<int>((1.0f / REACH_RESOLUTION) * PLAYER_REACH_DISTANCE); ++i)
				{
					currentPosition.x += facingDirection.x;
					currentPosition.y += facingDirection.y;
					currentPosition.z += facingDirection.z;

					if (worldManager.GetBlock(Vector3(currentPosition.x, currentPosition.y, currentPosition.z)) != Block::ID::Air)
					{
						currentPosition.x -= facingDirection.x;
						currentPosition.y -= facingDirection.y;
						currentPosition.z -= facingDirection.z;
						worldManager.setBlock(Vector3(currentPosition.x, currentPosition.y, currentPosition.z), Block::ID::Grass);

						
						break;
					}
				}
			}
		}
		else 
		{
			GLfloat depth;

			glReadPixels(Display::WIDTH / 2, Display::HEIGHT / 2, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

			glm::vec4 viewport = glm::vec4(0, 0, Display::WIDTH, Display::HEIGHT);
			glm::vec3 wincoord = glm::vec3(Display::WIDTH / 2, Display::HEIGHT / 2, depth);
			glm::vec3 objcoord = glm::unProject(wincoord, Application::get().getCamera().getViewMatrix(), Application::get().getCamera().getProjectionMatrix(), viewport);

			Vector3 facingDirection = Application::get().getCamera().getViewVector() * 0.07f;

			if (right) 
			{
				worldManager.setBlock(objcoord - facingDirection, Block::ID::Grass);
			}
			if (left)
			{
				worldManager.setBlock(objcoord + facingDirection, Block::ID::Air);
			}
		}

	}

	void Playing::updateMouseInput(double xpos, double ypos)
	{
		Application::get().getCamera().mouseInput(xpos, ypos);
	}

	void Playing::updateKeyboardInput(float dt)
	{
		Application::get().getCamera().keyboardInput(dt);
	}
}