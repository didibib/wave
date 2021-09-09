#pragma once

namespace wave
{
	class camera
	{
	public:
		enum class direction { forward, backward, left, right, up, down };
	public:
		camera(int width, int height);
		void move(direction dir, float delta_time);
		void follow_cursor(float cursor_x_offset, float cursor_y_offset);
	private:
		float m_near;
		float m_far;
		int m_view_width;
		int m_view_height;
	private:
		float m_speed = 10;
		float m_sensivity = 0.5f;
	};
}