#define GLFW_INCLUDE_NONE	

#include "glApp.h"
#include "glFigure.h"

// APPLICATION RUNNER
int main()
{
	OpenGL::glApp app(800, 600);
	app.run();
	return 0;
}


