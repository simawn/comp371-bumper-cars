#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <FreeImageIO.h>

#include "EventManager.h"
#include "Renderer.h"

using namespace glm;
using namespace std;

int main() {
	EventManager::Initialize();
	Renderer::Initialize();

	while (EventManager::ExitRequested() == false) {
		EventManager::Update();
		float dt = EventManager::GetFrameTime();
	}

	Renderer::Shutdown();
	EventManager::Shutdown();

	return 0;
}
