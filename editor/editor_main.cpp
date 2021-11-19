#include "pch/editorpch.h"
#include "editor_app.h"

using namespace Editor;

int main()
{
	std::unique_ptr<EditorApp> editorApp = std::make_unique<EditorApp>();

	Wave::Engine& engine = Wave::Engine::GetInstance();
	engine.StartUp(std::move(editorApp));
	engine.Run();
	engine.Shutdown();

	return 0;
}
