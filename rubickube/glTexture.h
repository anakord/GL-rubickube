#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL2/SOIL2.h>

#include "typedef.h"

namespace OpenGL {
	class glTexture
	{
	public:
		glTexture(const std::string& path);
		GLuint getTexture() { return handle; }
		~glTexture();
	private:
		GLuint handle;
		uchar* image; // data
		int width, height;
	};
}

