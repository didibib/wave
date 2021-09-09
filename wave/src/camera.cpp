#include "wavepch.h"
#include "camera.h"

namespace wave
{
	camera::camera(int width, int height)
	{

	}

	void camera::move(direction dir, float delta_time)
	{
		float velocity = m_speed * delta_time;
		switch (dir)
		{
		case direction::forward:
			break;
		case direction::backward:
			break;
		case direction::left:
			break;
		case direction::right:
			break;
		case direction::up:
			break;
		case direction::down:
			break;
		default:
			break;
		}
	}

	void camera::follow_cursor(float cursor_x_offset, float cursor_y_offset)
	{
	}
}