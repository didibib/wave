#include "sandboxpch.h"
#include "app.h"

int main()
{
	sandbox::app* m_app = new sandbox::app(800, 600, "sandbox");
	m_app->run();
	delete m_app;
	return 0;
}