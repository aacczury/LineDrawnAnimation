#include "canvasControl.h"

GLuint img_tex;

canvasControl::canvasControl(){
}

void canvasControl::read_img(System::String ^filename){
	init_img = gcnew Bitmap(filename);
	bind_img_texture(init_img, img_tex);
}

void canvasControl::draw_img(){
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, img_tex);
	glBegin(GL_POLYGON);
	glTexCoord2d(0.0, 0.0); glVertex2d(-1.0, 1.0);
	glTexCoord2d(1.0, 0.0);	glVertex2d(1.0, 1.0);
	glTexCoord2d(1.0, 1.0);	glVertex2d(1.0, -1.0);
	glTexCoord2d(0.0, 1.0);	glVertex2d(-1.0, -1.0);
	glEnd();
}

void canvasControl::bind_img_texture(Bitmap ^bitmap, GLuint &tex){
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	// 綁定紋理
	Imaging::BitmapData ^data = bitmap->LockBits(System::Drawing::Rectangle(0, 0, bitmap->Width, bitmap->Height), Imaging::ImageLockMode::ReadOnly, Imaging::PixelFormat::Format32bppArgb);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap->Width, bitmap->Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data->Scan0.ToPointer());
	bitmap->UnlockBits(data);

	// 與貼圖尺寸不同時的算法
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 大於
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 小於
}
