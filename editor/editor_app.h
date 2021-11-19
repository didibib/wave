#pragma once

#include "app/app.h"
#include "window/window.h"

namespace Editor
{
	class EditorApp : public Wave::App
	{
	public:
		EditorApp() = default;
		~EditorApp() = default;		
		void Init() override;
		Wave::AppState Update(const float&) override;
		void Shutdown() override;

		void Render(const float&);

	private:
		bool HasRunningWindows();

		std::vector<std::unique_ptr<Wave::Window>> m_Windows;
		std::unique_ptr<Wave::Camera> m_Camera;
		Wave::Shader m_Shader;
		Wave::VertexBuffer m_Vb;
		Wave::Model m_Model;
		Wave::Light m_Light;
	};
}