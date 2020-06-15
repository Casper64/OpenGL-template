#include "pch.h"
#include "core.h"


Application *create_application();

int main(int argc, char **argv)
{
	auto app = create_application();

	app->run();

	delete app;
	return 0;
}