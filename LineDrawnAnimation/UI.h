#pragma once

#include <Windows.h>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <cstdio>


namespace LineDrawnAnimation {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	static HWND hwnd;
	static HDC hdc;
	static HGLRC hrc;

	[DllImport("opengl32.dll")]
	extern HDC wglSwapBuffers(HDC hdc);

	glm::vec3 eye_position(0.01, 0.01, 20);
	glm::vec3 look_at_position(0, 0, 0);
	GLuint img_tex;

	/// <summary>
	/// UI 的摘要
	/// </summary>
	public ref class UI : public System::Windows::Forms::Form
	{
	public:
		UI(void);
		
	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~UI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  canvas;
	private: System::Windows::Forms::Label^  image_label;
	private: System::Windows::Forms::Label^  graph_label;
	private: System::Windows::Forms::Label^  sample_label;
	private: System::Windows::Forms::Timer^  frame_refresh_timer;
	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>

		void init_opengl();
		void reshape(int, int);
		void init_texture(Bitmap ^, GLuint &);
		void render_gl_canvas();
		void draw_test();
		void draw_img();

		bool left_mouse_down;
		unsigned int prev_x, prev_y;
		Bitmap ^init_bitmap;
		System::Void canvas_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
		System::Void canvas_DragDrop(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e);
		System::Void canvas_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void canvas_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void canvas_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
		System::Void frame_refresh_timer_Tick(System::Object^ sender, System::EventArgs^ e);

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
		/// 修改這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->canvas = (gcnew System::Windows::Forms::PictureBox());
			this->image_label = (gcnew System::Windows::Forms::Label());
			this->graph_label = (gcnew System::Windows::Forms::Label());
			this->sample_label = (gcnew System::Windows::Forms::Label());
			this->frame_refresh_timer = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->canvas))->BeginInit();
			this->SuspendLayout();
			// 
			// canvas
			// 
			this->canvas->AllowDrop = true;
			this->canvas->BackColor = System::Drawing::Color::Black;
			this->canvas->Location = System::Drawing::Point(0, 0);
			this->canvas->Name = L"canvas";
			this->canvas->Size = System::Drawing::Size(865, 860);
			this->canvas->TabIndex = 0;
			this->canvas->TabStop = false;
			this->canvas->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &UI::canvas_DragDrop);
			this->canvas->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &UI::canvas_DragEnter);
			this->canvas->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &UI::canvas_MouseDown);
			this->canvas->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &UI::canvas_MouseMove);
			this->canvas->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &UI::canvas_MouseUp);
			// 
			// image_label
			// 
			this->image_label->BackColor = System::Drawing::Color::Gray;
			this->image_label->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->image_label->ForeColor = System::Drawing::Color::White;
			this->image_label->Location = System::Drawing::Point(871, 9);
			this->image_label->Name = L"image_label";
			this->image_label->Size = System::Drawing::Size(301, 35);
			this->image_label->TabIndex = 1;
			this->image_label->Text = L"Image";
			this->image_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// graph_label
			// 
			this->graph_label->BackColor = System::Drawing::Color::Gray;
			this->graph_label->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->graph_label->ForeColor = System::Drawing::Color::White;
			this->graph_label->Location = System::Drawing::Point(871, 53);
			this->graph_label->Name = L"graph_label";
			this->graph_label->Size = System::Drawing::Size(301, 35);
			this->graph_label->TabIndex = 1;
			this->graph_label->Text = L"Graph";
			this->graph_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// sample_label
			// 
			this->sample_label->BackColor = System::Drawing::Color::Gray;
			this->sample_label->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->sample_label->ForeColor = System::Drawing::Color::White;
			this->sample_label->Location = System::Drawing::Point(871, 97);
			this->sample_label->Name = L"sample_label";
			this->sample_label->Size = System::Drawing::Size(301, 35);
			this->sample_label->TabIndex = 1;
			this->sample_label->Text = L"Sample";
			this->sample_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// frame_refresh_timer
			// 
			this->frame_refresh_timer->Enabled = true;
			this->frame_refresh_timer->Tick += gcnew System::EventHandler(this, &UI::frame_refresh_timer_Tick);
			// 
			// UI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1184, 861);
			this->Controls->Add(this->sample_label);
			this->Controls->Add(this->graph_label);
			this->Controls->Add(this->image_label);
			this->Controls->Add(this->canvas);
			this->Name = L"UI";
			this->Text = L"LineDrawnAnimation";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->canvas))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
