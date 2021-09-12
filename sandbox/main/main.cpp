#include "pch/sandboxpch.h"
#include "app/app.h"

int main()
{
	Sandbox::App* mApp = new Sandbox::App(800, 600, "Sandbox");
	mApp->Run();
	delete mApp;
	return 0;
}