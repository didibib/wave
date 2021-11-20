#include "pch/editorpch.h"
#include "editor_app.h"

using namespace Editor;
using namespace Wave;

int main()
{
	EditorApp* editorApp = new EditorApp();

	Engine& engine = Engine::GetInstance();
	WindowParams params;
	params.SetWidth(800);
	params.SetHeight(600);
	params.SetTitle("Wave");

	engine.Init();
	engine.StartUp(editorApp, params);
	engine.Run();
	engine.Shutdown();

	return 0;
}
