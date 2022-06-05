#define GLFW_INCLUDE_NONE	

#include "glApp.h"

// APPLICATION RUNNER
int main()
{
	OpenGL::glApp app(DEFAULT_WIDTH, DEFAULT_HEIGTH);
	app.run();
	return 0;
}


