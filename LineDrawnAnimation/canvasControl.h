#ifndef _CANVAS_CONTROL_H_
#define _CANVAS_CONTROL_H_

#include <GL/glew.h>

#include "utility.h"

using namespace System::Drawing;

ref class canvasControl
{
public:
	canvasControl();
	void read_img(System::String ^filename);
	void draw_img();

private:
	// Opengl ¬ÛÃö
	Bitmap ^init_img;
	void bind_img_texture(Bitmap ^bitmap, GLuint &tex);
};

#endif