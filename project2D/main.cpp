#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "Application2D.h"
#include "Level.h"


int main() {

	#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	auto app = new Application2D();
	app->run("AIE", 1280, 720, false);
	delete app;

	_CrtDumpMemoryLeaks();
	return 0;
}