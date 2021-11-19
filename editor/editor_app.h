#pragma once

#include "app/app.h"

namespace Editor
{
	class EditorApp : public Wave::App
	{
	public:
		EditorApp() = default;
		~EditorApp() = default;
		
		void Init() override;
		void Update(const float&) override;
		void Render(const float&);

	private:
		std::unique_ptr<Wave::Camera> m_Camera;
		Wave::Shader m_Shader;
		Wave::VertexBuffer m_Vb;
		Wave::Model m_Model;
		Wave::Light m_Light;
	};
}