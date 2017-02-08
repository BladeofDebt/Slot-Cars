#include "Application2D.h"

#include "Level.h"

int main() {
	
	auto app = new Application2D();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}