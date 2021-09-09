#pragma once

namespace wave
{
	class input_handler
	{
	public:
		class input_event
		{
		public:
			enum class type { KEY, MOUSE, CURSOR, SCROLL };
			input_event(type type) : m_type(type) {}
		public:
			type get_type() { return m_type; }
		private:
			type m_type;
		};

		class key_event : public input_event
		{
		public:
			key_event() = delete;
			key_event(int key, int scancode, int action, int mods) :
				input_event(type::KEY), m_key(key), m_scancode(scancode), m_action(action), m_mods(mods)
			{
			}
		public:
			int get_key() { return m_key; }
			int get_scanCode() { return m_scancode; }
			int get_action() { return m_action; }
			int get_mods() { return m_mods; }
		private:
			int m_key;
			int m_scancode;
			int m_action;
			int m_mods;
		};

		class mouse_event : public input_event
		{
		public:
			mouse_event() = delete;
			mouse_event(int button, int action, int mods) :
				input_event(type::MOUSE), m_button(button), m_action(action), m_mods(mods)
			{
			}
			int get_button() { return m_button; }
			int get_action() { return m_action; }
			int get_mods() { return m_mods; }
		private:
			int m_button;
			int m_action;
			int m_mods;
		};

		class cursor_event : public input_event
		{
		public:
			cursor_event() = delete;
			cursor_event(float x_pos, float y_pos) :
				input_event(type::CURSOR), m_xPos(x_pos), m_yPos(y_pos)
			{
			}
		public:
			float get_x_pos() { return m_xPos; }
			float get_y_pos() { return m_yPos; }
		private:
			float m_xPos;
			float m_yPos;
		};

		class scroll_event : public input_event
		{
		public:
			scroll_event() = delete;
			scroll_event(float x_offset, float y_offset) :
				input_event(type::SCROLL), m_x_offset(x_offset), m_y_offset(y_offset)
			{
			}
		public:
			float get_x_offset() { return m_x_offset; }
			float get_y_offset() { return m_y_offset; }
		private:
			float m_x_offset;
			float m_y_offset;
		};

		class cursor
		{
		public:
		public:
			void translate(double x_pos, double y_pos)
			{
				if (m_reset)
				{
					m_xPos = x_pos;
					m_yPos = y_pos;
					m_reset = false;
				}
				m_xOffset = x_pos - m_xPos;
				m_yOffset = m_yPos - y_pos;
				m_xPos = x_pos;
				m_yPos = y_pos;
			}
			void reset()
			{
				m_xOffset = 0;
				m_yOffset = 0;
			}
			void set_state(int state)
			{
				m_reset = state;
			}
		private:
			double m_xPos = 0;
			double m_yPos = 0;
			double m_xOffset = 0;
			double m_yOffset = 0;
			bool m_reset = false;
		};

		class scroll
		{
		public:
			float get_x_offset() { return m_x_offset; }
			float get_y_offset() { return m_y_offset; }
			void set(float x_offset, float y_offset)
			{
				m_x_offset = x_offset;
				m_y_offset = y_offset;
			}
			void reset()
			{
				m_x_offset = 0;
				m_y_offset = 0;
			}
		private:
			float m_x_offset = 0;
			float m_y_offset = 0;
		};

	public:
		input_handler() = default;
		void update(std::queue<std::unique_ptr<input_event>>& event_buffer);
		void flush();

		cursor& get_cursor() { return m_cursor; }
		scroll get_scroll() { return m_scroll; }

		bool is_key_pressed(int key);
		bool is_key_repeat(int key);
		bool is_key_released(int key);

		bool is_mouse_pressed(int button);
		bool is_mouse_repeat(int button);
		bool is_mouse_released(int button);

	private:
		cursor m_cursor;
		scroll m_scroll;
		std::map<int, int> m_key_states;
		std::map<int, int> m_mouse_states;
	};
}