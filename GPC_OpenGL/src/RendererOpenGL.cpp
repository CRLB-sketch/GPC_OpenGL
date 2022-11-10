#include "Shaders.h"
#include "Shaderm.h"
#include "Camera.h"

class RendererOpenGL
{
public:
	Shaderm theShader();

	RendererOpenGL() {

	}

	void setShaders(Shaderm newShader) {
		theShader = newShader;
	}
};