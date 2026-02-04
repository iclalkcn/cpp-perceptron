#pragma once
#include "Process.h"
#include <iostream>
#include <fstream>
#include <string>

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//

			//
		}
		void UpdateErrorPlot()
		{
			if (!ERROR_HISTORY || ERROR_HISTORY_COUNT <= 0)
				return;

			Bitmap^ bmp = gcnew Bitmap(
				errorPictureBox->Width,
				errorPictureBox->Height
			);

			Graphics^ g = Graphics::FromImage(bmp);
			g->Clear(Color::White);

			Pen^ axisPen = gcnew Pen(Color::Black, 1.0f);
			Pen^ curvePen = gcnew Pen(Color::Blue, 2.0f);

			int margin = 20;
			Rectangle rect(
				margin,
				margin,
				bmp->Width - 2 * margin,
				bmp->Height - 2 * margin
			);

			if (rect.Width <= 0 || rect.Height <= 0)
				return;

			g->DrawRectangle(axisPen, rect);

			// max error bul
			float maxErr = ERROR_HISTORY[0];
			for (int i = 1; i < ERROR_HISTORY_COUNT; i++)
				if (ERROR_HISTORY[i] > maxErr)
					maxErr = ERROR_HISTORY[i];

			if (maxErr < 1e-6f)
				maxErr = 1.0f;

			PointF prev = PointF(0, 0);

			for (int i = 0; i < ERROR_HISTORY_COUNT; i++) {

				float err = ERROR_HISTORY[i];
				if (err < 0.0f) err = 0.0f;
				if (err > maxErr) err = maxErr;

				float t = (ERROR_HISTORY_COUNT == 1)
					? 0.0f
					: (float)i / (ERROR_HISTORY_COUNT - 1);

				float x = rect.Left + t * rect.Width;
				float y = rect.Bottom - (err / maxErr) * rect.Height;

				PointF p(x, y);

				if (i > 0)
					g->DrawLine(curvePen, prev, p);

				prev = p;
			}

			errorPictureBox->Image = bmp;
		}


	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	protected:
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Button^ Set_Net;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ ClassCountBox;

	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ComboBox^ ClassNoBox;



	private:
		/// <summary>
		/// User Defined Variables
		int  class_count = 0, numSample = 0, inputDim = 2;
		float* Samples, * targets, * Weights, * bias;
		// ---- Error graph için ----
		float* ERROR_HISTORY = nullptr;
		int ERROR_HISTORY_COUNT = 0;

		bool  showBinaryLine = false;
		float line_w0 = 0.0f;
		float line_w1 = 0.0f;
		float line_b = 0.0f;
		int maxEpoch;
		float learningRate;

		// ---- (MLP için ek değişkenler kaldırıldı; şu an sadece tek katmanlı perceptron kullanılıyor) ----

	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ readDataToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::ToolStripMenuItem^ saveDataToolStripMenuItem;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::ToolStripMenuItem^ processToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ trainingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ testingToolStripMenuItem;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::GroupBox^ groupAktivasyon;
	private: System::Windows::Forms::RadioButton^ radioButton3;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::TextBox^ txtEpochBox;

	private: System::Windows::Forms::Label^ txtEpoch;

	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::TextBox^ txtMomentumBox;

	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ txtEtaBox;

	private: System::Windows::Forms::Label^ txtEta;

	private: System::Windows::Forms::TextBox^ textBox7;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::TextBox^ textBox8;
	private: System::Windows::Forms::PictureBox^ errorPictureBox;
	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;










		   /// </summary>
		   System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Erforderliche Methode für die Designerunterstützung.
		   /// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			   this->label9 = (gcnew System::Windows::Forms::Label());
			   this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			   this->label8 = (gcnew System::Windows::Forms::Label());
			   this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			   this->Set_Net = (gcnew System::Windows::Forms::Button());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->ClassCountBox = (gcnew System::Windows::Forms::ComboBox());
			   this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->ClassNoBox = (gcnew System::Windows::Forms::ComboBox());
			   this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			   this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->readDataToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->saveDataToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->processToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->trainingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->testingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			   this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			   this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			   this->panel1 = (gcnew System::Windows::Forms::Panel());
			   this->groupAktivasyon = (gcnew System::Windows::Forms::GroupBox());
			   this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			   this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			   this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			   this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			   this->txtMomentumBox = (gcnew System::Windows::Forms::TextBox());
			   this->label7 = (gcnew System::Windows::Forms::Label());
			   this->txtEtaBox = (gcnew System::Windows::Forms::TextBox());
			   this->txtEta = (gcnew System::Windows::Forms::Label());
			   this->txtEpochBox = (gcnew System::Windows::Forms::TextBox());
			   this->txtEpoch = (gcnew System::Windows::Forms::Label());
			   this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   this->panel2 = (gcnew System::Windows::Forms::Panel());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->errorPictureBox = (gcnew System::Windows::Forms::PictureBox());
			   this->panel3 = (gcnew System::Windows::Forms::Panel());
			   this->label5 = (gcnew System::Windows::Forms::Label());
			   this->label6 = (gcnew System::Windows::Forms::Label());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   this->groupBox1->SuspendLayout();
			   this->groupBox2->SuspendLayout();
			   this->menuStrip1->SuspendLayout();
			   this->groupAktivasyon->SuspendLayout();
			   this->groupBox3->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorPictureBox))->BeginInit();
			   this->panel3->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // pictureBox1
			   // 
			   this->pictureBox1->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			   this->pictureBox1->Location = System::Drawing::Point(17, 43);
			   this->pictureBox1->Margin = System::Windows::Forms::Padding(4);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(1069, 711);
			   this->pictureBox1->TabIndex = 0;
			   this->pictureBox1->TabStop = false;
			   this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::pictureBox1_Paint);
			   this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseClick);
			   // 
			   // groupBox1
			   // 
			   this->groupBox1->Controls->Add(this->label9);
			   this->groupBox1->Controls->Add(this->textBox8);
			   this->groupBox1->Controls->Add(this->label8);
			   this->groupBox1->Controls->Add(this->textBox7);
			   this->groupBox1->Controls->Add(this->Set_Net);
			   this->groupBox1->Controls->Add(this->label1);
			   this->groupBox1->Controls->Add(this->ClassCountBox);
			   this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(162)));
			   this->groupBox1->Location = System::Drawing::Point(1159, 62);
			   this->groupBox1->Margin = System::Windows::Forms::Padding(4);
			   this->groupBox1->Name = L"groupBox1";
			   this->groupBox1->Padding = System::Windows::Forms::Padding(4);
			   this->groupBox1->Size = System::Drawing::Size(300, 219);
			   this->groupBox1->TabIndex = 1;
			   this->groupBox1->TabStop = false;
			   this->groupBox1->Text = L"Network Architecture";
			   // 
			   // label9
			   // 
			   this->label9->AutoSize = true;
			   this->label9->Location = System::Drawing::Point(114, 118);
			   this->label9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->label9->Name = L"label9";
			   this->label9->Size = System::Drawing::Size(174, 17);
			   this->label9->TabIndex = 6;
			   this->label9->Text = L"Neurons in Each Layer";
			   // 
			   // textBox8
			   // 
			   this->textBox8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->textBox8->Location = System::Drawing::Point(13, 116);
			   this->textBox8->Name = L"textBox8";
			   this->textBox8->Size = System::Drawing::Size(100, 22);
			   this->textBox8->TabIndex = 5;
			   this->textBox8->Tag = L"";
			   // 
			   // label8
			   // 
			   this->label8->AutoSize = true;
			   this->label8->Location = System::Drawing::Point(115, 73);
			   this->label8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->label8->Name = L"label8";
			   this->label8->Size = System::Drawing::Size(152, 17);
			   this->label8->TabIndex = 4;
			   this->label8->Text = L"Hidden Layer Count";
			   this->label8->Click += gcnew System::EventHandler(this, &Form1::label8_Click);
			   // 
			   // textBox7
			   // 
			   this->textBox7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->textBox7->Location = System::Drawing::Point(13, 73);
			   this->textBox7->Name = L"textBox7";
			   this->textBox7->Size = System::Drawing::Size(100, 22);
			   this->textBox7->TabIndex = 3;
			   this->textBox7->Tag = L"";
			   // 
			   // Set_Net
			   // 
			   this->Set_Net->Location = System::Drawing::Point(8, 170);
			   this->Set_Net->Margin = System::Windows::Forms::Padding(4);
			   this->Set_Net->Name = L"Set_Net";
			   this->Set_Net->Size = System::Drawing::Size(175, 41);
			   this->Set_Net->TabIndex = 2;
			   this->Set_Net->Text = L"Network Setting";
			   this->Set_Net->UseVisualStyleBackColor = true;
			   this->Set_Net->Click += gcnew System::EventHandler(this, &Form1::Set_Net_Click);
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Location = System::Drawing::Point(144, 28);
			   this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(88, 17);
			   this->label1->TabIndex = 1;
			   this->label1->Text = L"Sinif Sayisi";
			   this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			   // 
			   // ClassCountBox
			   // 
			   this->ClassCountBox->FormattingEnabled = true;
			   this->ClassCountBox->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"2", L"3", L"4", L"5", L"6", L"7" });
			   this->ClassCountBox->Location = System::Drawing::Point(13, 25);
			   this->ClassCountBox->Margin = System::Windows::Forms::Padding(4);
			   this->ClassCountBox->Name = L"ClassCountBox";
			   this->ClassCountBox->Size = System::Drawing::Size(108, 25);
			   this->ClassCountBox->TabIndex = 0;
			   this->ClassCountBox->Text = L"2";
			   // 
			   // groupBox2
			   // 
			   this->groupBox2->Controls->Add(this->label2);
			   this->groupBox2->Controls->Add(this->ClassNoBox);
			   this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(162)));
			   this->groupBox2->Location = System::Drawing::Point(1159, 304);
			   this->groupBox2->Margin = System::Windows::Forms::Padding(4);
			   this->groupBox2->Name = L"groupBox2";
			   this->groupBox2->Padding = System::Windows::Forms::Padding(4);
			   this->groupBox2->Size = System::Drawing::Size(253, 75);
			   this->groupBox2->TabIndex = 2;
			   this->groupBox2->TabStop = false;
			   this->groupBox2->Text = L"Data Collection";
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Location = System::Drawing::Point(131, 28);
			   this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(102, 17);
			   this->label2->TabIndex = 1;
			   this->label2->Text = L"Örnek Etiketi";
			   // 
			   // ClassNoBox
			   // 
			   this->ClassNoBox->FormattingEnabled = true;
			   this->ClassNoBox->Items->AddRange(gcnew cli::array< System::Object^  >(9) {
				   L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8",
					   L"9"
			   });
			   this->ClassNoBox->Location = System::Drawing::Point(9, 25);
			   this->ClassNoBox->Margin = System::Windows::Forms::Padding(4);
			   this->ClassNoBox->Name = L"ClassNoBox";
			   this->ClassNoBox->Size = System::Drawing::Size(99, 25);
			   this->ClassNoBox->TabIndex = 0;
			   this->ClassNoBox->Text = L"1";
			   // 
			   // menuStrip1
			   // 
			   this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			   this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				   this->fileToolStripMenuItem,
					   this->processToolStripMenuItem
			   });
			   this->menuStrip1->Location = System::Drawing::Point(0, 0);
			   this->menuStrip1->Name = L"menuStrip1";
			   this->menuStrip1->Size = System::Drawing::Size(1924, 28);
			   this->menuStrip1->TabIndex = 4;
			   this->menuStrip1->Text = L"menuStrip1";
			   this->menuStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &Form1::menuStrip1_ItemClicked);
			   // 
			   // fileToolStripMenuItem
			   // 
			   this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				   this->readDataToolStripMenuItem,
					   this->saveDataToolStripMenuItem
			   });
			   this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			   this->fileToolStripMenuItem->Size = System::Drawing::Size(46, 24);
			   this->fileToolStripMenuItem->Text = L"File";
			   // 
			   // readDataToolStripMenuItem
			   // 
			   this->readDataToolStripMenuItem->Name = L"readDataToolStripMenuItem";
			   this->readDataToolStripMenuItem->Size = System::Drawing::Size(164, 26);
			   this->readDataToolStripMenuItem->Text = L"Read_Data";
			   this->readDataToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::readDataToolStripMenuItem_Click);
			   // 
			   // saveDataToolStripMenuItem
			   // 
			   this->saveDataToolStripMenuItem->Name = L"saveDataToolStripMenuItem";
			   this->saveDataToolStripMenuItem->Size = System::Drawing::Size(164, 26);
			   this->saveDataToolStripMenuItem->Text = L"Save_Data";
			   this->saveDataToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saveDataToolStripMenuItem_Click);
			   // 
			   // processToolStripMenuItem
			   // 
			   this->processToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				   this->trainingToolStripMenuItem,
					   this->testingToolStripMenuItem
			   });
			   this->processToolStripMenuItem->Name = L"processToolStripMenuItem";
			   this->processToolStripMenuItem->Size = System::Drawing::Size(72, 24);
			   this->processToolStripMenuItem->Text = L"Process";
			   // 
			   // trainingToolStripMenuItem
			   // 
			   this->trainingToolStripMenuItem->Name = L"trainingToolStripMenuItem";
			   this->trainingToolStripMenuItem->Size = System::Drawing::Size(145, 26);
			   this->trainingToolStripMenuItem->Text = L"Training";
			   this->trainingToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::trainingToolStripMenuItem_Click);
			   // 
			   // testingToolStripMenuItem
			   // 
			   this->testingToolStripMenuItem->Name = L"testingToolStripMenuItem";
			   this->testingToolStripMenuItem->Size = System::Drawing::Size(145, 26);
			   this->testingToolStripMenuItem->Text = L"Testing";
			   this->testingToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::testingToolStripMenuItem_Click);
			   // 
			   // openFileDialog1
			   // 
			   this->openFileDialog1->FileName = L"openFileDialog1";
			   // 
			   // textBox1
			   // 
			   this->textBox1->Location = System::Drawing::Point(1159, 423);
			   this->textBox1->Margin = System::Windows::Forms::Padding(4);
			   this->textBox1->Multiline = true;
			   this->textBox1->Name = L"textBox1";
			   this->textBox1->Size = System::Drawing::Size(266, 292);
			   this->textBox1->TabIndex = 5;
			   // 
			   // panel1
			   // 
			   this->panel1->AccessibleName = L"";
			   this->panel1->Location = System::Drawing::Point(1550, 73);
			   this->panel1->Name = L"panel1";
			   this->panel1->Size = System::Drawing::Size(233, 103);
			   this->panel1->TabIndex = 6;
			   this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::panel1_Paint);
			   // 
			   // groupAktivasyon
			   // 
			   this->groupAktivasyon->Controls->Add(this->radioButton3);
			   this->groupAktivasyon->Controls->Add(this->radioButton2);
			   this->groupAktivasyon->Controls->Add(this->radioButton1);
			   this->groupAktivasyon->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->groupAktivasyon->Location = System::Drawing::Point(1547, 62);
			   this->groupAktivasyon->Name = L"groupAktivasyon";
			   this->groupAktivasyon->Size = System::Drawing::Size(236, 114);
			   this->groupAktivasyon->TabIndex = 0;
			   this->groupAktivasyon->TabStop = false;
			   this->groupAktivasyon->Text = L"Aktivasyon Fonksiyonlari";
			   this->groupAktivasyon->Enter += gcnew System::EventHandler(this, &Form1::groupBox3_Enter_1);
			   // 
			   // radioButton3
			   // 
			   this->radioButton3->AutoSize = true;
			   this->radioButton3->Location = System::Drawing::Point(17, 75);
			   this->radioButton3->Name = L"radioButton3";
			   this->radioButton3->Size = System::Drawing::Size(151, 20);
			   this->radioButton3->TabIndex = 2;
			   this->radioButton3->TabStop = true;
			   this->radioButton3->Text = L"Continuous Button";
			   this->radioButton3->UseVisualStyleBackColor = true;
			   // 
			   // radioButton2
			   // 
			   this->radioButton2->AutoSize = true;
			   this->radioButton2->Location = System::Drawing::Point(17, 48);
			   this->radioButton2->Name = L"radioButton2";
			   this->radioButton2->Size = System::Drawing::Size(91, 20);
			   this->radioButton2->TabIndex = 1;
			   this->radioButton2->TabStop = true;
			   this->radioButton2->Text = L"SIGMOID";
			   this->radioButton2->UseVisualStyleBackColor = true;
			   // 
			   // radioButton1
			   // 
			   this->radioButton1->AutoSize = true;
			   this->radioButton1->Location = System::Drawing::Point(17, 22);
			   this->radioButton1->Name = L"radioButton1";
			   this->radioButton1->Size = System::Drawing::Size(70, 20);
			   this->radioButton1->TabIndex = 0;
			   this->radioButton1->TabStop = true;
			   this->radioButton1->Text = L"TANH";
			   this->radioButton1->UseVisualStyleBackColor = true;
			   // 
			   // groupBox3
			   // 
			   this->groupBox3->Controls->Add(this->txtMomentumBox);
			   this->groupBox3->Controls->Add(this->label7);
			   this->groupBox3->Controls->Add(this->txtEtaBox);
			   this->groupBox3->Controls->Add(this->txtEta);
			   this->groupBox3->Controls->Add(this->txtEpochBox);
			   this->groupBox3->Controls->Add(this->txtEpoch);
			   this->groupBox3->Controls->Add(this->textBox2);
			   this->groupBox3->Controls->Add(this->label4);
			   this->groupBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->groupBox3->Location = System::Drawing::Point(1547, 188);
			   this->groupBox3->Name = L"groupBox3";
			   this->groupBox3->Size = System::Drawing::Size(247, 166);
			   this->groupBox3->TabIndex = 7;
			   this->groupBox3->TabStop = false;
			   this->groupBox3->Text = L"Egitim Parametreleri";
			   // 
			   // txtMomentumBox
			   // 
			   this->txtMomentumBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->txtMomentumBox->Location = System::Drawing::Point(142, 116);
			   this->txtMomentumBox->Name = L"txtMomentumBox";
			   this->txtMomentumBox->Size = System::Drawing::Size(70, 22);
			   this->txtMomentumBox->TabIndex = 7;
			   this->txtMomentumBox->Text = L"0.9";
			   // 
			   // label7
			   // 
			   this->label7->AutoSize = true;
			   this->label7->Location = System::Drawing::Point(145, 97);
			   this->label7->Name = L"label7";
			   this->label7->Size = System::Drawing::Size(81, 16);
			   this->label7->TabIndex = 6;
			   this->label7->Text = L"Momentum";
			   // 
			   // txtEtaBox
			   // 
			   this->txtEtaBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->txtEtaBox->Location = System::Drawing::Point(142, 54);
			   this->txtEtaBox->Name = L"txtEtaBox";
			   this->txtEtaBox->Size = System::Drawing::Size(70, 22);
			   this->txtEtaBox->TabIndex = 5;
			   this->txtEtaBox->Text = L"0.001";
			   // 
			   // txtEta
			   // 
			   this->txtEta->AutoSize = true;
			   this->txtEta->Location = System::Drawing::Point(145, 35);
			   this->txtEta->Name = L"txtEta";
			   this->txtEta->Size = System::Drawing::Size(59, 16);
			   this->txtEta->TabIndex = 4;
			   this->txtEta->Text = L"Eta(LR)";
			   // 
			   // txtEpochBox
			   // 
			   this->txtEpochBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->txtEpochBox->Location = System::Drawing::Point(6, 116);
			   this->txtEpochBox->Name = L"txtEpochBox";
			   this->txtEpochBox->Size = System::Drawing::Size(70, 22);
			   this->txtEpochBox->TabIndex = 3;
			   this->txtEpochBox->Text = L"100";
			   // 
			   // txtEpoch
			   // 
			   this->txtEpoch->AutoSize = true;
			   this->txtEpoch->Location = System::Drawing::Point(3, 97);
			   this->txtEpoch->Name = L"txtEpoch";
			   this->txtEpoch->Size = System::Drawing::Size(51, 16);
			   this->txtEpoch->TabIndex = 2;
			   this->txtEpoch->Text = L"Epoch";
			   this->txtEpoch->Click += gcnew System::EventHandler(this, &Form1::label5_Click);
			   // 
			   // textBox2
			   // 
			   this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->textBox2->Location = System::Drawing::Point(3, 54);
			   this->textBox2->Name = L"textBox2";
			   this->textBox2->Size = System::Drawing::Size(70, 22);
			   this->textBox2->TabIndex = 1;
			   this->textBox2->Tag = L"";
			   this->textBox2->Text = L"0.01";
			   // 
			   // label4
			   // 
			   this->label4->AutoSize = true;
			   this->label4->Location = System::Drawing::Point(6, 35);
			   this->label4->Name = L"label4";
			   this->label4->Size = System::Drawing::Size(73, 16);
			   this->label4->TabIndex = 0;
			   this->label4->Text = L"Max Error";
			   this->label4->Click += gcnew System::EventHandler(this, &Form1::label4_Click);
			   // 
			   // panel2
			   // 
			   this->panel2->Location = System::Drawing::Point(1550, 191);
			   this->panel2->Name = L"panel2";
			   this->panel2->Size = System::Drawing::Size(238, 163);
			   this->panel2->TabIndex = 8;
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->Location = System::Drawing::Point(1156, 392);
			   this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(44, 16);
			   this->label3->TabIndex = 3;
			   this->label3->Text = L"label3";
			   // 
			   // errorPictureBox
			   // 
			   this->errorPictureBox->BackColor = System::Drawing::Color::White;
			   this->errorPictureBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			   this->errorPictureBox->Location = System::Drawing::Point(0, 0);
			   this->errorPictureBox->Name = L"errorPictureBox";
			   this->errorPictureBox->Size = System::Drawing::Size(254, 292);
			   this->errorPictureBox->TabIndex = 10;
			   this->errorPictureBox->TabStop = false;
			   // 
			   // panel3
			   // 
			   this->panel3->Controls->Add(this->label6);
			   this->panel3->Controls->Add(this->label5);
			   this->panel3->Controls->Add(this->errorPictureBox);
			   this->panel3->Location = System::Drawing::Point(1547, 423);
			   this->panel3->Name = L"panel3";
			   this->panel3->Size = System::Drawing::Size(254, 292);
			   this->panel3->TabIndex = 11;
			   // 
			   // label5
			   // 
			   this->label5->AutoSize = true;
			   this->label5->BackColor = System::Drawing::Color::White;
			   this->label5->Location = System::Drawing::Point(6, 3);
			   this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->label5->Name = L"label5";
			   this->label5->Size = System::Drawing::Size(36, 16);
			   this->label5->TabIndex = 11;
			   this->label5->Text = L"Error";
			   this->label5->Click += gcnew System::EventHandler(this, &Form1::label5_Click_1);
			   // 
			   // label6
			   // 
			   this->label6->AutoSize = true;
			   this->label6->BackColor = System::Drawing::Color::White;
			   this->label6->Location = System::Drawing::Point(205, 265);
			   this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->label6->Name = L"label6";
			   this->label6->Size = System::Drawing::Size(45, 16);
			   this->label6->TabIndex = 12;
			   this->label6->Text = L"epoch";
			   // 
			   // Form1
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1924, 779);
			   this->Controls->Add(this->panel3);
			   this->Controls->Add(this->groupBox3);
			   this->Controls->Add(this->groupAktivasyon);
			   this->Controls->Add(this->panel1);
			   this->Controls->Add(this->textBox1);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->groupBox2);
			   this->Controls->Add(this->groupBox1);
			   this->Controls->Add(this->pictureBox1);
			   this->Controls->Add(this->menuStrip1);
			   this->Controls->Add(this->panel2);
			   this->MainMenuStrip = this->menuStrip1;
			   this->Margin = System::Windows::Forms::Padding(4);
			   this->Name = L"Form1";
			   this->Text = L"Form1";
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   this->groupBox1->ResumeLayout(false);
			   this->groupBox1->PerformLayout();
			   this->groupBox2->ResumeLayout(false);
			   this->groupBox2->PerformLayout();
			   this->menuStrip1->ResumeLayout(false);
			   this->menuStrip1->PerformLayout();
			   this->groupAktivasyon->ResumeLayout(false);
			   this->groupAktivasyon->PerformLayout();
			   this->groupBox3->ResumeLayout(false);
			   this->groupBox3->PerformLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorPictureBox))->EndInit();
			   this->panel3->ResumeLayout(false);
			   this->panel3->PerformLayout();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
		   void draw_sample(int temp_x, int temp_y, int label) {
			   Pen^ pen;// = gcnew Pen(Color::Black, 3.0f);
			   switch (label) {
			   case 0: pen = gcnew Pen(Color::Black, 3.0f); break;
			   case 1: pen = gcnew Pen(Color::Red, 3.0f); break;
			   case 2: pen = gcnew Pen(Color::Blue, 3.0f); break;
			   case 3: pen = gcnew Pen(Color::Green, 3.0f); break;
			   case 4: pen = gcnew Pen(Color::Yellow, 3.0f); break;
			   case 5: pen = gcnew Pen(Color::Orange, 3.0f); break;
			   default: pen = gcnew Pen(Color::YellowGreen, 3.0f);
			   }//switch
			   pictureBox1->CreateGraphics()->DrawLine(pen, temp_x - 5, temp_y, temp_x + 5, temp_y);
			   pictureBox1->CreateGraphics()->DrawLine(pen, temp_x, temp_y - 5, temp_x, temp_y + 5);
		   }//draw_sample
#pragma endregion
	private: System::Void pictureBox1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (class_count == 0)
			MessageBox::Show("The Network Architeture should be firtly set up");
		else {
			float* x = new float[inputDim];
			int temp_x = (System::Convert::ToInt32(e->X));
			int temp_y = (System::Convert::ToInt32(e->Y));
			x[0] = float(temp_x - (pictureBox1->Width / 2));
			x[1] = float(pictureBox1->Height / 2 - temp_y);
			int label;
			int numLabel = Convert::ToInt32(ClassNoBox->Text);
			if (numLabel > class_count)
				MessageBox::Show("The class label cannot be greater than the maximum number of classes.");
			else {
				label = numLabel - 1; //Dögüler 0 dan baþladýðýndan, label deðeri 0 dan baþlamasý için bir eksiði alýnmýþtýr
				if (numSample == 0) { //Dinamik alýnan ilk örnek için sadece
					numSample = 1;
					Samples = new float[numSample * inputDim]; targets = new float[numSample];
					for (int i = 0; i < inputDim; i++)
						Samples[i] = x[i];
					targets[0] = float(label);
				}
				else {
					numSample++;
					Samples = Add_Data(Samples, numSample, x, inputDim);
					targets = Add_Labels(targets, numSample, label);
				}//else
				draw_sample(temp_x, temp_y, label);
				label3->Text = "Örnek Sayisi: " + System::Convert::ToString(numSample);
				delete[] x;
			}//else of if (Etiket ...
		}//else
	}//pictureMouseClick
	private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		//Ana eksen doðrularini cizdir
		Pen^ pen = gcnew Pen(Color::Black, 3.0f);
		int center_width, center_height;
		center_width = (int)(pictureBox1->Width / 2);
		center_height = (int)(pictureBox1->Height / 2);
		e->Graphics->DrawLine(pen, center_width, 0, center_width, pictureBox1->Height);
		e->Graphics->DrawLine(pen, 0, center_height, pictureBox1->Width, center_height);

		//Doğru çizimi//
		showBinaryLine = (class_count == 2);
		if (showBinaryLine) {
			Pen^ p = gcnew Pen(Color::Blue, 2.0f);

			int w = pictureBox1->Width;
			int h = pictureBox1->Height;

			float x1 = -w / 2.0f;
			float y1 = -(line_w0 * x1 + line_b) / line_w1;

			float x2 = w / 2.0f;
			float y2 = -(line_w0 * x2 + line_b) / line_w1;

			int px1 = (int)(x1 + w / 2);
			int py1 = (int)(h / 2 - y1);
			int px2 = (int)(x2 + w / 2);
			int py2 = (int)(h / 2 - y2);

			e->Graphics->DrawLine(p, px1, py1, px2, py2);
		}
		// ---- ÖRNEKLERİ TEKRAR ÇİZME ----
		for (int i = 0; i < numSample; i++) {

			Pen^ pen;
			switch ((int)targets[i]) {
			case 0: pen = gcnew Pen(Color::Black, 3.0f); break;
			case 1: pen = gcnew Pen(Color::Red, 3.0f); break;
			case 2: pen = gcnew Pen(Color::Blue, 3.0f); break;
			case 3: pen = gcnew Pen(Color::Green, 3.0f); break;
			default: pen = gcnew Pen(Color::YellowGreen, 3.0f); break;
			}

			int temp_x = (int)(Samples[i * inputDim] + pictureBox1->Width / 2);
			int temp_y = (int)(pictureBox1->Height / 2 - Samples[i * inputDim + 1]);

			e->Graphics->DrawLine(pen, temp_x - 5, temp_y, temp_x + 5, temp_y);
			e->Graphics->DrawLine(pen, temp_x, temp_y - 5, temp_x, temp_y + 5);
		}


	}
	private: System::Void Set_Net_Click(System::Object^ sender, System::EventArgs^ e) {
		// Network is constructed (tek katmanlı perceptron)
		class_count = Convert::ToInt32(ClassCountBox->Text);
		Weights = new float[class_count * inputDim];
		bias = new float[class_count];

		// initialize weights for single layer
		if (class_count > 2) {
			Weights = init_array_random(class_count * inputDim);
			bias = init_array_random(class_count);
		}
		else {
			int numOutNeuron = 1;
			Weights = init_array_random(inputDim);
			bias = init_array_random(numOutNeuron);
		}

		Set_Net->Text = " Network is Ready : ";
	}//Set_Net
	private: System::Void readDataToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		char** c = new char* [2];
		// Veri Kümesini okunacak 
		MessageBox::Show("Veri Kümesini Yükleyin");
		c[0] = "../Data/Samples.txt";
		c[1] = "../Data/weights.txt";
		std::ifstream file;
		int num, w, h, Dim, label;
		file.open(c[0]);
		if (file.is_open()) {
			//MessageBox::Show("Dosya acildi");
			file >> Dim >> w >> h >> num;
			textBox1->Text += "Dimension: " + Convert::ToString(Dim) + "- Width: " + Convert::ToString(w) + " - Height: " + Convert::ToString(h) + " - Number of Class: " + Convert::ToString(num) + "\r\n";
			// Set network values
			class_count = num;
			inputDim = Dim;
			Weights = new float[class_count * inputDim];
			bias = new float[class_count];
			numSample = 0;
			float* x = new float[inputDim];
			while (!file.eof())
			{
				if (numSample == 0) { //ilk örnek için sadece
					numSample = 1;
					Samples = new float[inputDim]; targets = new float[numSample];
					for (int i = 0; i < inputDim; i++)
						file >> Samples[i];
					file >> targets[0];
				}
				else {

					for (int i = 0; i < inputDim; i++)
						file >> x[i];
					file >> label;
					if (!file.eof()) {
						numSample++;
						Samples = Add_Data(Samples, numSample, x, inputDim);
						targets = Add_Labels(targets, numSample, label);
					}
				}//else
			} //while
			delete[]x;
			file.close();
			for (int i = 0; i < numSample; i++) {
				draw_sample(Samples[i * inputDim] + w, h - Samples[i * inputDim + 1], targets[i]);
				for (int j = 0; j < inputDim; j++)
					textBox1->Text += Convert::ToString(Samples[i * inputDim + j]) + " ";
				textBox1->Text += Convert::ToString(targets[i]) + "\r\n";
			}
			//draw_sample(temp_x, temp_y, label);
			label3->Text = "Örnek Sayisi: " + System::Convert::ToString(numSample);
			MessageBox::Show("Dosya basari ile okundu");
		}//file.is_open
		else MessageBox::Show("Dosya acilamadi");
		//Get weights
		int Layer;
		file.open(c[1]);
		if (file.is_open()) {
			file >> Layer >> Dim >> num;
			class_count = num;
			inputDim = Dim;
			Weights = new float[class_count * inputDim];
			bias = new float[class_count];
			textBox1->Text += "Layer: " + Convert::ToString(Layer) + " Dimension: " + Convert::ToString(Dim) + " numClass:" + Convert::ToString(num) + "\r\n";
			while (!file.eof())
			{
				for (int i = 0; i < class_count; i++)
					for (int j = 0; j < inputDim; j++)
						file >> Weights[i * inputDim + j];
				for (int i = 0; i < class_count; i++)
					file >> bias[i];
			}
			file.close();
		}//file.is_open
		delete[]c;
	}//Read_Data
	private: System::Void saveDataToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (numSample != 0) {
			char** c = new char* [2];
			// Veri Kümesi yazýlacak
			c[0] = "../Data/Samples.txt";
			c[1] = "../Data/weights.txt";
			std::ofstream ofs(c[0]);
			if (!ofs.bad()) {
				// Width,  Height, number of Class, data+label
				ofs << inputDim << " " << pictureBox1->Width / 2 << " " << pictureBox1->Height / 2 << " " << class_count << std::endl;
				for (int i = 0; i < numSample; i++) {
					for (int d = 0; d < inputDim; d++)
						ofs << Samples[i * inputDim + d] << " ";
					ofs << targets[i] << std::endl;
				}
				ofs.close();
			}
			else MessageBox::Show("Samples icin dosya acilamadi");
			std::ofstream file(c[1]);
			if (!file.bad()) {
				// #Layer Dimension numClass weights biases
				file << 1 << " " << inputDim << " " << class_count << std::endl;
				for (int k = 0; k < class_count * inputDim; k++)
					file << Weights[k] << " ";
				file << std::endl;
				for (int k = 0; k < class_count; k++)
					file << bias[k] << " ";
				file.close();
			}
			else MessageBox::Show("Weight icin dosya acilamadi");
			delete[]c;
		}
		else MessageBox::Show("At least one sample should be given");
	}//Save_Data

	private: System::Void trainingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		textBox1->Text = "Training started...\r\n";


		if (class_count == 0 || numSample == 0) {
			MessageBox::Show("Önce ağ ve veri girilmeli");
			return;
		}

		maxEpoch = Convert::ToInt32(txtEpochBox->Text);
		learningRate = (float)Convert::ToDouble(txtEtaBox->Text);

		// error dizisi
		if (ERROR_HISTORY) delete[] ERROR_HISTORY;
		ERROR_HISTORY = new float[maxEpoch];
		for (int k = 0; k < maxEpoch; ++k) ERROR_HISTORY[k] = 0.0f;

		// EĞİTİM 
		if (maxEpoch > 0) {
			// SINIFLANDIRMA
			Train_Perceptron(
				Samples,
				targets,
				numSample,
				inputDim,
				Weights,
				bias,
				learningRate,
				maxEpoch,
				ERROR_HISTORY
			);
		}
		else {
			// REGRESSION
			Train_LinearRegression(
				Samples,
				targets,
				numSample,
				inputDim,
				Weights,
				bias,
				learningRate,
				-maxEpoch,
				ERROR_HISTORY
			);
		}


		// Grafik
		showBinaryLine = true;
		line_w0 = Weights[0];
		line_w1 = Weights[1];
		line_b = bias[0];

		ERROR_HISTORY_COUNT = maxEpoch;
		// for (int i = 0; i < maxEpoch; i++) {
		  //   if (ERROR_HISTORY[i] == 0.0f) {
		  //	   ERROR_HISTORY_COUNT = i + 1;
		  //	   break;
			 //}
		  //   }
		  //}




		UpdateErrorPlot();

		textBox1->AppendText("Training finished...\r\n");

		pictureBox1->Invalidate(); // yeniden çizimi tetikle
		errorPictureBox->Invalidate();



	}



	private: System::Void testingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		float* x = new float[2];
		float* mean = new float[2];
		float* std = new float[2];
		//mean ve std tekrar hesaplanıyor
		Z_Score_Parameters(Samples, numSample, inputDim, mean, std);
		//MessageBox::Show("mean: "+System::Convert::ToString(mean[0])+ " "+ System::Convert::ToString(mean[1]));
		int num, temp_x, temp_y;
		Bitmap^ surface = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
		pictureBox1->Image = surface;
		Color c;
		for (int row = 0; row < pictureBox1->Height; row += 2) {
			for (int column = 0; column < pictureBox1->Width; column += 2) {
				x[0] = (float)(column - (pictureBox1->Width / 2));
				x[1] = (float)((pictureBox1->Height / 2) - row);
				//x[0] = (x[0] - mean[0]) / std[0];
				//x[1] = (x[1] - mean[1]) / std[1];
				num = Test_Forward(x, Weights, bias, class_count, inputDim);


				//MessageBox::Show("merhaba: class :" + System::Convert::ToString(numClass));
				switch (num) {
				case 0: c = Color::FromArgb(0, 0, 0); break;
				case 1: c = Color::FromArgb(255, 0, 0); break;
				case 2: c = Color::FromArgb(0, 255, 0); break;
				case 3: c = Color::FromArgb(0, 0, 255); break;
				default: c = Color::FromArgb(0, 255, 255);
				}//switch
				surface->SetPixel(column, row, c);
			}//column
			//MessageBox::Show("merhaba2: class :" + System::Convert::ToString(numClass));
		}
		//Samples Draw
		Pen^ pen;// = gcnew Pen(Color::Black, 3.0f);
		MessageBox::Show("Örnekler cizildi");
		for (int i = 0; i < numSample; i++) {
			switch (int(targets[i])) {
			case 0: pen = gcnew Pen(Color::Black, 3.0f); break;
			case 1: pen = gcnew Pen(Color::Red, 3.0f); break;
			case 2: pen = gcnew Pen(Color::Blue, 3.0f); break;
			case 3: pen = gcnew Pen(Color::Green, 3.0f); break;
			case 4: pen = gcnew Pen(Color::Yellow, 3.0f); break;
			case 5: pen = gcnew Pen(Color::Orange, 3.0f); break;
			default: pen = gcnew Pen(Color::YellowGreen, 3.0f);
			}//switch
			temp_x = int(Samples[i * inputDim]) + pictureBox1->Width / 2;
			temp_y = pictureBox1->Height / 2 - int(Samples[i * inputDim + 1]);
			pictureBox1->CreateGraphics()->DrawLine(pen, temp_x - 5, temp_y, temp_x + 5, temp_y);
			pictureBox1->CreateGraphics()->DrawLine(pen, temp_x, temp_y - 5, temp_x, temp_y + 5);
		}
		delete[] x;
		delete[] mean;
		delete[] std;
	}//Testing


	private: System::Void menuStrip1_ItemClicked(System::Object^ sender, System::Windows::Forms::ToolStripItemClickedEventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void groupBox3_Enter(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void groupBox3_Enter_1(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label8_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label5_Click_1(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
