#include "pch/sandboxpch.h"
#include "app/app.h"

int main()
{
	sandbox::App* mApp = new sandbox::App(800, 600, "Sandbox");
	mApp->Run();
	delete mApp;
	return 0;
}