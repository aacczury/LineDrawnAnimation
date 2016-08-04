#include "UI.h"

using namespace System;
using namespace System::Windows::Forms;

// 建立Form
[STAThread]
void main(){
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	LineDrawnAnimation::UI form;
	Application::Run(%form);
}

namespace LineDrawnAnimation {

	// UI 建構子
	UI::UI(){
		InitializeComponent();
		init_opengl();
		reshape(this->canvas->Width, this->canvas->Height);


		left_mouse_down = false;
	}

	void UI::init_opengl(){
		// Get Handle
		hwnd = (HWND)this->canvas->Handle.ToInt32();
		hdc = GetDC(hwnd);
		wglSwapBuffers(hdc);

		// Set pixel format
		PIXELFORMATDESCRIPTOR pfd;
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = (byte)(PFD_TYPE_RGBA);
		pfd.cColorBits = 32;
		pfd.cDepthBits = 32;
		pfd.iLayerType = (byte)(PFD_MAIN_PLANE);
		SetPixelFormat(hdc, ChoosePixelFormat(hdc, &pfd), &pfd);

		// Create OpenGL Rendering Context
		if (!(hrc = wglCreateContext(hdc))) printf("wglCreateContext failed.\n");
		// Assign OpenGL Rendering Context
		if (!wglMakeCurrent(hdc, hrc)) printf("wglMakeCurrent failed.\n");
		// init glew
		if (glewInit() != GLEW_OK) printf("OpenGL initialize failed.\n");

		glewExperimental = GL_TRUE;

		glEnable(GL_COLOR_MATERIAL); // 可以用顏色貼物體
		glEnable(GL_TEXTURE_2D);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL); // Z1 <= Z2 才畫
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // 最高畫量選項

		glClearColor(0, 0, 0, 1);
		//glClearDepth(1.0);
	}

	void UI::reshape(int width, int height){
		glViewport(0, 0, width, height);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		float aspect_ratio = width * 1.0 / height;
		if (width <= height)
			gluOrtho2D(-1.0, 1.0, -1.0 / aspect_ratio, 1.0 / aspect_ratio);
		else
			gluOrtho2D(-1.0 * aspect_ratio, 1.0 * aspect_ratio, -1.0, 1.0);
	}

	void UI::init_texture(Bitmap ^bitmap, GLuint &tex){
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

	void UI::render_gl_canvas(){
		wglMakeCurrent(hdc, hrc);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		cc.draw_img();

		SwapBuffers(hdc);
	}

	// 定時更新FRAME
	System::Void UI::frame_refresh_timer_Tick(System::Object^  sender, System::EventArgs^  e) {
		render_gl_canvas();
	}

	// 有東西拖到畫布上
	System::Void UI::canvas_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e){
		e->Effect = e->Data->GetDataPresent(DataFormats::FileDrop) ? DragDropEffects::Copy : DragDropEffects::None;
	}
	
	// 有東西拖到畫布上放下
	System::Void UI::canvas_DragDrop(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e){
		if (e->Data->GetDataPresent(DataFormats::FileDrop)){
			array<System::String^>^files = (array<System::String^>^)e->Data->GetData(DataFormats::FileDrop);
			System::String ^imgExt = ".jpg|.png|.bmp|.jpeg|.gif";
			try{
				for (unsigned int i = 0; i < files->Length; ++i){
					System::String ^ext = System::IO::Path::GetExtension(files[i]);
					if (imgExt->IndexOf(ext) >= 0){
						cc.read_img(files[i]);
					}
				}
			}
			catch (System::Exception^ ex){
				MessageBox::Show(ex->Message);
				return;
			}
		}
	}

	System::Void UI::canvas_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e){
		if (e->Button == System::Windows::Forms::MouseButtons::Left){
			left_mouse_down = true;
			prev_x = e->X;
			prev_y = e->Y;
		}
	}

	System::Void UI::canvas_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e){
		if (left_mouse_down){
			prev_x = e->X, prev_y = e -> Y;
		}
	}

	System::Void UI::canvas_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e){
		left_mouse_down = false;
	}
}
