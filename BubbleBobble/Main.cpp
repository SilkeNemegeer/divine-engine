//#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "Minigin.h"
#include "Scene.h"

int main(int, char*[]) {
	divengine::Minigin engine;

	engine.Run();
    return 0;
}