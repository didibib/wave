#include "pch/editorpch.h"
#include "editor_app.h"

int main()
{
	Wave::Engine& engine = Wave::Engine::GetInstance();
	Editor::EditorApp editorApp;

	Wave::EngineSettings settings;
	settings.Width = 800;
	settings.Height = 600;
	settings.Title = "WAVE";
	engine.StartUp(editorApp, settings);
	engine.Run();
	engine.Shutdown();

	return 0;
}
