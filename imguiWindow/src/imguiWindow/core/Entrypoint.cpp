#include "pch.h"
#include "core.h"


Application *create_application();
#ifdef BUILD_DIST
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
int main(int argc, char **argv)
{
	auto app = create_application();

	app->run();

	delete app;
	return 0;
}