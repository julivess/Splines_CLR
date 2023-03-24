
#include "MyForm.h"
#include "solution.h"

using namespace System;
using namespace System::Windows::Forms; 

[STAThreadAttribute]
void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	SplinesCLRlab1::MyForm form;
	Application::Run(% form);
}

System::Void SplinesCLRlab1::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e) //кнопка выполнить 
{
	clear();
	this->chart1->Series[0]->Points->Clear(); //Стереть график 
	this->chart1->ChartAreas[0]->AxisX->MajorGrid->Enabled = false;
	this->chart1->ChartAreas[0]->AxisY->MajorGrid->Enabled = false;

	if (checkBox1->Checked == false && checkBox2->Checked == false && checkBox3->Checked == false) {
		MessageBox::Show("Выберете задачу!", "Внимание!");
	}

	if ((checkBox1->Checked == true && checkBox2->Checked == true) || (checkBox1->Checked == true && checkBox3->Checked == true) || (checkBox2->Checked == true && checkBox3->Checked == true)) {
		MessageBox::Show("Выберете только одну задачу!", "Внимание!");
	}

	if (checkBox4->Checked == false && checkBox5->Checked == false && checkBox6->Checked == false) {
		MessageBox::Show("Выберете задачу!", "Внимание!");
	}

	if ((checkBox4->Checked == true && checkBox5->Checked == true) || (checkBox4->Checked == true && checkBox6->Checked == true) || (checkBox5->Checked == true && checkBox6->Checked == true)) {
		MessageBox::Show("Выберете только одну задачу!", "Внимание!");
	}

	//тестовая задача
	if (checkBox4->Checked == true && checkBox5->Checked == false && checkBox6->Checked == false) {
		clear();
			m1 = -1;
			m2 = 1;
			n = Convert::ToInt16(textBox_n->Text);
			h = (m2 - m1) / n;
			creation();
			vector_F_test();
			sweep();
			odds_test();
			this->chart1->Series[0]->Points->Clear();
			this->chart1->Series[1]->Points->Clear();
			this->chart1->Series[2]->Points->Clear();
			this->chart1->Series[3]->Points->Clear();
			this->chart1->Series[4]->Points->Clear();
			this->chart1->Series[5]->Points->Clear();
			dataGridView1->AutoResizeRowHeadersWidth(DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders); //выравниваем
			dataGridView1->AutoResizeColumns(); //выравниваем
			dataGridView2->AutoResizeRowHeadersWidth(DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders); //выравниваем
			dataGridView2->AutoResizeColumns(); //выравниваем
			dataGridView1->AutoResizeRows(DataGridViewAutoSizeRowsMode::AllCellsExceptHeaders);
			dataGridView1->AutoResizeColumns();
			dataGridView2->AutoResizeRows(DataGridViewAutoSizeRowsMode::AllCellsExceptHeaders);
			dataGridView2->AutoResizeColumns();
			Header1();
			Header2();
			Header3();
			dataGridView1->ColumnCount = 7;
			dataGridView1->RowCount = n + 1;
			dataGridView2->ColumnCount = 8;
			dataGridView2->RowCount = n + 1;
			dataGridView3->ColumnCount = 5;
			dataGridView3->RowCount = n + 1;

			for (int i = 0; i < n; i++) {

				dataGridView1->Rows[i]->Cells[0]->Value = i + 1;
				dataGridView1->Rows[i]->Cells[1]->Value = x(i);
				dataGridView1->Rows[i]->Cells[2]->Value = x(i + 1);
				dataGridView1->Rows[i]->Cells[3]->Value = a[i + 1];
				dataGridView1->Rows[i]->Cells[4]->Value = b[i + 1];
				dataGridView1->Rows[i]->Cells[5]->Value = c[i + 1];
				dataGridView1->Rows[i]->Cells[6]->Value = d[i + 1];

			}
			double max = 0; 
			double max1 = 0; 
			double max2 = 0; 
			double xi, xi1, xi2; 
			for (int j = 0; j < n; j++) {
				dataGridView2->Rows[j]->Cells[0]->Value = j + 1;
				dataGridView2->Rows[j]->Cells[1]->Value = y(j);
				dataGridView2->Rows[j]->Cells[2]->Value = f_test(y(j));
				dataGridView2->Rows[j]->Cells[3]->Value = spline(y(j), j + 1);
				dataGridView2->Rows[j]->Cells[4]->Value = f_test(y(j)) - spline(y(j), j + 1);
				dataGridView2->Rows[j]->Cells[5]->Value = f_test_1(y(j));
				dataGridView2->Rows[j]->Cells[6]->Value = spline1(y(j), j + 1);
				dataGridView2->Rows[j]->Cells[7]->Value = f_test_1(y(j)) - spline1(y(j), j + 1);
				if (max < fabs(f_test(y(j)) - spline(y(j), j + 1))) {
					max = fabs(f_test(y(j)) - spline(y(j), j + 1));
					xi = y(j);
				}
				if (max1 < fabs(f_test_1(y(j)) - spline1(y(j), j + 1))) {
					max1 = fabs(f_test_1(y(j)) - spline1(y(j), j + 1));
					xi1 = y(j);
				}
			}

			for (int j = 0; j < n; j++) {
				dataGridView3->Rows[j]->Cells[0]->Value = j + 1;
				dataGridView3->Rows[j]->Cells[1]->Value = y(j);
				dataGridView3->Rows[j]->Cells[2]->Value = f_test_2(y(j));
				dataGridView3->Rows[j]->Cells[3]->Value = spline2(y(j), j + 1);
				dataGridView3->Rows[j]->Cells[4]->Value = f_test_2(y(j)) - spline2(y(j), j + 1);
				if (max2 < fabs(f_test_2(y(j)) - spline2(y(j), j + 1))) {
					max2 = fabs(f_test_2(y(j)) - spline2(y(j), j + 1));
					xi2 = y(j);
				}
		
			}
		if (checkBox1->Checked == true && checkBox2->Checked == false && checkBox3->Checked == false) { //график функции
			for (int i = 0; i < n + 1; i++) {
				chart1->Series[1]->Points->AddXY(x(i), f_test(x(i)));
			}
			for (int i = 1; i < n + 1; i++) { 
				chart1->Series[0]->Points->AddXY(x(i - 1), spline(x(i - 1), i));
			}
			chart1->Series[0]->Points->AddXY(x(n), spline(x(n), n));
		}
		if (checkBox1->Checked == false && checkBox2->Checked == true && checkBox3->Checked == false) { //график первой производной 
			
			for (int i = 0; i < n + 1; i++) {
				chart1->Series[3]->Points->AddXY(x(i), f_test_1(x(i)));
			}
			for (int i = 1; i < n + 1; i++) { 
				chart1->Series[2]->Points->AddXY(x(i - 1), spline1(x(i - 1), i));
			}
			chart1->Series[2]->Points->AddXY(x(n), spline1(x(n), n));
		}
		if (checkBox1->Checked == false && checkBox2->Checked == false && checkBox3->Checked == true) { //график второй поизводной 
			for (int i = 0; i < n + 1; i++) {
				chart1->Series[5]->Points->AddXY(x(i), f_test_2(x(i)));
			}
			chart1->Series[4]->Points->AddXY(- 1, 0);
			for (int i = 1; i < n+1; i++) { 
				chart1->Series[4]->Points->AddXY(x(i-1), spline2(x(i-1), i));
			}
			
			chart1->Series[4]->Points->AddXY(1, 0);
		}
		
		label6->Text =
			L"Погрешность на контрольной сетке: " + "\n" +
			L"max|F(xj) - S(xj)| = " + System::Convert::ToString(max) + "\n" + L" при x= " + System::Convert::ToString(xi) + "\n" +
			L"max|F'(xj) - S'(xj)| = " + System::Convert::ToString(max1) + "\n" + L" при x= " + System::Convert::ToString(xi1) + "\n" +
			L"max|F''(xj) - S''(xj)| = " + System::Convert::ToString(max2) + "\n" + L" при x= " + System::Convert::ToString(xi2) + "\n";
		
	}
	if (checkBox4->Checked == false && checkBox5->Checked == true && checkBox6->Checked == false) {
		clear();
		m1 = Convert::ToDouble(textBox_a->Text);
		m2 = Convert::ToDouble(textBox_b->Text);
		n = Convert::ToInt16(textBox_n->Text);
		h = (m2 - m1) / n;
		creation();
		vector_F_basic();
		sweep();
		odds_basic();
		this->chart1->Series[0]->Points->Clear();
		this->chart1->Series[1]->Points->Clear();
		this->chart1->Series[2]->Points->Clear();
		this->chart1->Series[3]->Points->Clear();
		this->chart1->Series[4]->Points->Clear();
		this->chart1->Series[5]->Points->Clear();
		dataGridView1->AutoResizeRowHeadersWidth(DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders); //выравниваем
		dataGridView1->AutoResizeColumns(); //выравниваем
		dataGridView2->AutoResizeRowHeadersWidth(DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders); //выравниваем
		dataGridView2->AutoResizeColumns(); //выравниваем
		dataGridView1->AutoResizeRows(DataGridViewAutoSizeRowsMode::AllCellsExceptHeaders);
		dataGridView1->AutoResizeColumns();
		dataGridView2->AutoResizeRows(DataGridViewAutoSizeRowsMode::AllCellsExceptHeaders);
		dataGridView2->AutoResizeColumns();
		Header1();
		Header2();
		Header3();
		dataGridView1->ColumnCount = 7;
		dataGridView1->RowCount = n + 1;
		dataGridView2->ColumnCount = 8;
		dataGridView2->RowCount = n + 1;
		dataGridView3->ColumnCount = 5;
		dataGridView3->RowCount = n + 1;
		double max = 0;
		double max1 = 0;
		double max2 = 0;
		double xi, xi1, xi2;
		for (int i = 0; i < n; i++) {

			dataGridView1->Rows[i]->Cells[0]->Value = i + 1;
			dataGridView1->Rows[i]->Cells[1]->Value = x(i);
			dataGridView1->Rows[i]->Cells[2]->Value = x(i + 1);
			dataGridView1->Rows[i]->Cells[3]->Value = a[i + 1];
			dataGridView1->Rows[i]->Cells[4]->Value = b[i + 1];
			dataGridView1->Rows[i]->Cells[5]->Value = c[i + 1];
			dataGridView1->Rows[i]->Cells[6]->Value = d[i + 1];

		}
		for (int j = 0; j < n; j++) {
			dataGridView2->Rows[j]->Cells[0]->Value = j + 1;
			dataGridView2->Rows[j]->Cells[1]->Value = y(j);
			dataGridView2->Rows[j]->Cells[2]->Value = f_basic(y(j));
			dataGridView2->Rows[j]->Cells[3]->Value = spline(y(j), j + 1);
			dataGridView2->Rows[j]->Cells[4]->Value = f_basic(y(j)) - spline(y(j), j + 1);
			dataGridView2->Rows[j]->Cells[5]->Value = f_basic_1(y(j));
			dataGridView2->Rows[j]->Cells[6]->Value = spline1(y(j), j + 1);
			dataGridView2->Rows[j]->Cells[7]->Value = f_basic_1(y(j)) - spline1(y(j), j + 1);
			if (max < fabs(f_basic(y(j)) - spline(y(j), j + 1))) {
				max = fabs(f_basic(y(j)) - spline(y(j), j + 1));
				xi = y(j);
			}
			if (max1 < fabs(f_basic_1(y(j)) - spline1(y(j), j + 1))) {
				max1 = fabs(f_basic_1(y(j)) - spline1(y(j), j + 1));
				xi1 = y(j);
			}
		}

		for (int j = 0; j < n; j++) {
			dataGridView3->Rows[j]->Cells[0]->Value = j + 1;
			dataGridView3->Rows[j]->Cells[1]->Value = y(j);
			dataGridView3->Rows[j]->Cells[2]->Value = f_basic_2(y(j));
			dataGridView3->Rows[j]->Cells[3]->Value = spline2(y(j), j + 1);
			dataGridView3->Rows[j]->Cells[4]->Value = f_basic_2(y(j)) - spline2(y(j), j + 1);
			if (max2 < fabs(f_basic_2(y(j)) - spline2(y(j), j + 1))) {
				max2 = fabs(f_basic_2(y(j)) - spline2(y(j), j + 1));
				xi2 = y(j);
			}
		}
		if (checkBox1->Checked == true && checkBox2->Checked == false && checkBox3->Checked == false) { //график функции
			for (int i = 0; i < n + 1; i++) {
				chart1->Series[1]->Points->AddXY(x(i), f_basic(x(i)));
			}
			for (int i = 1; i < n + 1; i++) { 
				chart1->Series[0]->Points->AddXY(x(i - 1), spline(x(i - 1), i));
			}
			chart1->Series[0]->Points->AddXY(x(n), spline(x(n), n));
		}
		if (checkBox1->Checked == false && checkBox2->Checked == true && checkBox3->Checked == false) { //график первой производной 

			for (int i = 0; i < n + 1; i++) {
				chart1->Series[3]->Points->AddXY(x(i), f_basic_1(x(i)));
			}
			for (int i = 1; i < n+1; i++) { 
				chart1->Series[2]->Points->AddXY(x(i - 1), spline1(x(i - 1), i));
			}
			chart1->Series[2]->Points->AddXY(x(n), spline1(x(n), n));
		}
		if (checkBox1->Checked == false && checkBox2->Checked == false && checkBox3->Checked == true) { //график второй поизводной 
			for (int i = 0; i < n + 1; i++) {
				chart1->Series[5]->Points->AddXY(x(i), f_basic_2(x(i)));
			}
			chart1->Series[4]->Points->AddXY(m1, 0);
			for (int i = 2; i < n+1; i++) { 
				chart1->Series[4]->Points->AddXY(x(i-1), spline2(x(i-1), i));
			}
			chart1->Series[4]->Points->AddXY(m2, 0);
			/*chart1->Series[4]->Points->AddXY(x(1), spline2(x(1), 2));
			chart1->Series[4]->Points->AddXY(x(2), spline2(x(2), 3));
			chart1->Series[4]->Points->AddXY(x(3), spline2(x(3), 4));
			chart1->Series[4]->Points->AddXY(x(4), spline2(x(4), 5));*/
		}
		label6->Text =
			L"Погрешность на контрольной сетке: " + "\n" +
			L"max|F(xj) - S(xj)| = " + System::Convert::ToString(max) + "\n" + L" при x= " + System::Convert::ToString(xi) + "\n" +
			L"max|F'(xj) - S'(xj)| = " + System::Convert::ToString(max1) + "\n" + L" при x= " + System::Convert::ToString(xi1) + "\n" +
			L"max|F''(xj) - S''(xj)| = " + System::Convert::ToString(max2) + "\n" + L" при x= " + System::Convert::ToString(xi2) + "\n";
		

	}
	if (checkBox4->Checked == false && checkBox5->Checked == false && checkBox6->Checked == true) { //осциллирующая функция
		clear();
		m1 = Convert::ToDouble(textBox_a->Text);
		m2 = Convert::ToDouble(textBox_b->Text);
		n = Convert::ToInt16(textBox_n->Text);
		h = (m2 - m1) / n;
		creation();
		vector_F_oscillating();
		sweep();
		odds_oscillating();
		this->chart1->Series[0]->Points->Clear();
		this->chart1->Series[1]->Points->Clear();
		this->chart1->Series[2]->Points->Clear();
		this->chart1->Series[3]->Points->Clear();
		this->chart1->Series[4]->Points->Clear();
		this->chart1->Series[5]->Points->Clear();
		dataGridView1->AutoResizeRowHeadersWidth(DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders); //выравниваем
		dataGridView1->AutoResizeColumns(); //выравниваем
		dataGridView2->AutoResizeRowHeadersWidth(DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders); //выравниваем
		dataGridView2->AutoResizeColumns(); //выравниваем
		dataGridView1->AutoResizeRows(DataGridViewAutoSizeRowsMode::AllCellsExceptHeaders);
		dataGridView1->AutoResizeColumns();
		dataGridView2->AutoResizeRows(DataGridViewAutoSizeRowsMode::AllCellsExceptHeaders);
		dataGridView2->AutoResizeColumns();
		Header1();
		Header2();
		Header3();
		dataGridView1->ColumnCount = 7;
		dataGridView1->RowCount = n + 1;
		dataGridView2->ColumnCount = 8;
		dataGridView2->RowCount = n + 1;
		dataGridView3->ColumnCount = 5;
		dataGridView3->RowCount = n + 1;
		double max = 0;
		double max1 = 0;
		double max2 = 0;
		double xi, xi1, xi2;
		for (int i = 0; i < n; i++) {

			dataGridView1->Rows[i]->Cells[0]->Value = i + 1;
			dataGridView1->Rows[i]->Cells[1]->Value = x(i);
			dataGridView1->Rows[i]->Cells[2]->Value = x(i + 1);
			dataGridView1->Rows[i]->Cells[3]->Value = a[i + 1];
			dataGridView1->Rows[i]->Cells[4]->Value = b[i + 1];
			dataGridView1->Rows[i]->Cells[5]->Value = c[i + 1];
			dataGridView1->Rows[i]->Cells[6]->Value = d[i + 1];

		}
		for (int j = 0; j < n; j++) {
			dataGridView2->Rows[j]->Cells[0]->Value = j + 1;
			dataGridView2->Rows[j]->Cells[1]->Value = y(j);
			dataGridView2->Rows[j]->Cells[2]->Value = f_oscillating(y(j));
			dataGridView2->Rows[j]->Cells[3]->Value = spline(y(j), j + 1);
			dataGridView2->Rows[j]->Cells[4]->Value = f_oscillating(y(j)) - spline(y(j), j + 1);
			dataGridView2->Rows[j]->Cells[5]->Value = f_oscillating_1(y(j));
			dataGridView2->Rows[j]->Cells[6]->Value = spline1(y(j), j + 1);
			dataGridView2->Rows[j]->Cells[7]->Value = f_oscillating_1(y(j)) - spline1(y(j), j + 1);
			if (max < fabs(f_oscillating(y(j)) - spline(y(j), j + 1))) {
				max = fabs(f_oscillating(y(j)) - spline(y(j), j + 1));
				xi = y(j);
			}
			if (max1 < fabs(f_oscillating_1(y(j)) - spline1(y(j), j + 1))) {
				max1 = fabs(f_oscillating_1(y(j)) - spline1(y(j), j + 1));
				xi1 = y(j);
			}
		}

		for (int j = 0; j < n; j++) {
			dataGridView3->Rows[j]->Cells[0]->Value = j + 1;
			dataGridView3->Rows[j]->Cells[1]->Value = y(j);
			dataGridView3->Rows[j]->Cells[2]->Value = f_oscillating_2(y(j));
			dataGridView3->Rows[j]->Cells[3]->Value = spline2(y(j), j + 1);
			dataGridView3->Rows[j]->Cells[4]->Value = f_oscillating_2(y(j)) - spline2(y(j), j + 1);
			if (max2 < fabs(f_oscillating_2(y(j)) - spline2(y(j), j + 1))) {
				max2 = fabs(f_oscillating_2(y(j)) - spline2(y(j), j + 1));
				xi2 = y(j);
			}
		}
		if (checkBox1->Checked == true && checkBox2->Checked == false && checkBox3->Checked == false) { //график функции
			for (int i = 0; i < n + 1; i++) {
				chart1->Series[1]->Points->AddXY(x(i), f_oscillating(x(i)));
			}
			for (int i = 1; i < n + 1; i++) { 
				chart1->Series[0]->Points->AddXY(x(i - 1), spline(x(i - 1), i));
			}
			chart1->Series[0]->Points->AddXY(x(n), spline(x(n), n));
		}
		if (checkBox1->Checked == false && checkBox2->Checked == true && checkBox3->Checked == false) { //график первой производной 

			for (int i = 0; i < n + 1; i++) {
				chart1->Series[3]->Points->AddXY(x(i), f_oscillating_1(x(i)));
			}
			for (int i = 1; i < n + 1; i++) { 
				chart1->Series[2]->Points->AddXY(x(i-1), spline1(x(i-1), i));
			}
			chart1->Series[2]->Points->AddXY(x(n), spline1(x(n), n));
		}
		if (checkBox1->Checked == false && checkBox2->Checked == false && checkBox3->Checked == true) { //график второй поизводной 
			for (int i = 0; i < n + 1; i++) {
				chart1->Series[5]->Points->AddXY(x(i), f_oscillating_2(x(i)));
			}
			chart1->Series[4]->Points->AddXY(m1, 0);
			for (int i = 2; i < n; i++) { 
				chart1->Series[4]->Points->AddXY(x(i-1), spline2(x(i-1), i));
			}
			chart1->Series[4]->Points->AddXY(m2, 0);
		}
		label6->Text =
			L"Погрешность на контрольной сетке: " + "\n" +
			L"max|F(xj) - S(xj)| = " + System::Convert::ToString(max) + "\n" + L" при x= " + System::Convert::ToString(xi) + "\n" +
			L"max|F'(xj) - S'(xj)| = " + System::Convert::ToString(max1) + "\n" + L" при x= " + System::Convert::ToString(xi1) + "\n" +
			L"max|F''(xj) - S''(xj)| = " + System::Convert::ToString(max2) + "\n" + L" при x= " + System::Convert::ToString(xi2) + "\n";
		

	}

}

System::Void SplinesCLRlab1::MyForm::button2_Click(System::Object^ sender, System::EventArgs^ e) //кнопка выйти 
{
	Application::Exit();
}

void SplinesCLRlab1::MyForm::Header1(){ //шапка

	DataGridViewTextBoxColumn^ c1 = gcnew DataGridViewTextBoxColumn();
	c1->Name = "i";
	c1->HeaderText = "i";
	c1->Width = 100;
	dataGridView1->Columns->Add(c1);

	DataGridViewTextBoxColumn^ c2 = gcnew DataGridViewTextBoxColumn();
	c2->Name = "x(i-1)";
	c2->HeaderText = "x( i-1 )";
	c2->Width = 100;
	dataGridView1->Columns->Add(c2);

	DataGridViewTextBoxColumn^ c3 = gcnew DataGridViewTextBoxColumn();
	c3->Name = "x(i)";
	c3->HeaderText = "x( i )";
	c3->Width = 100;
	dataGridView1->Columns->Add(c3);

	DataGridViewTextBoxColumn^ c4 = gcnew DataGridViewTextBoxColumn();
	c4->Name = "a(i)";
	c4->HeaderText = "a( i )";
	c4->Width = 100;
	dataGridView1->Columns->Add(c4);

	DataGridViewTextBoxColumn^ c5 = gcnew DataGridViewTextBoxColumn();
	c5->Name = "b(i)";
	c5->HeaderText = "b( i )";
	c5->Width = 100;
	dataGridView1->Columns->Add(c5);

	DataGridViewTextBoxColumn^ c6 = gcnew DataGridViewTextBoxColumn();
	c6->Name = "c(i)";
	c6->HeaderText = "c( i )";
	c6->Width = 100;
	dataGridView1->Columns->Add(c6);

	DataGridViewTextBoxColumn^ c7 = gcnew DataGridViewTextBoxColumn();
	c7->Name = "d(i)";
	c7->HeaderText = "d( i )";
	c7->Width = 100;
	dataGridView1->Columns->Add(c7);
}

void SplinesCLRlab1::MyForm::Header2() //шапка второй таблицы 
{
	DataGridViewTextBoxColumn^ c1 = gcnew DataGridViewTextBoxColumn();
	c1->Name = "j";
	c1->HeaderText = "j";
	c1->Width = 100;
	dataGridView2->Columns->Add(c1);

	DataGridViewTextBoxColumn^ c2 = gcnew DataGridViewTextBoxColumn();
	c2->Name = "x(j)";
	c2->HeaderText = "x( j )";
	c2->Width = 100;
	dataGridView2->Columns->Add(c2);

	DataGridViewTextBoxColumn^ c3 = gcnew DataGridViewTextBoxColumn();
	c3->Name = "f(j)";
	c3->HeaderText = "F( j )";
	c3->Width = 100;
	dataGridView2->Columns->Add(c3);

	DataGridViewTextBoxColumn^ c4 = gcnew DataGridViewTextBoxColumn();
	c4->Name = "S(j)";
	c4->HeaderText = "S( j )";
	c4->Width = 100;
	dataGridView2->Columns->Add(c4);

	DataGridViewTextBoxColumn^ c5 = gcnew DataGridViewTextBoxColumn();
	c5->Name = "f(j)";
	c5->HeaderText = "F( j ) - S( j )";
	c5->Width = 100;
	dataGridView2->Columns->Add(c5);

	DataGridViewTextBoxColumn^ c6 = gcnew DataGridViewTextBoxColumn();
	c6->Name = "f'(j)";
	c6->HeaderText = "F'( j )";
	c6->Width = 100;
	dataGridView2->Columns->Add(c6);

	DataGridViewTextBoxColumn^ c7 = gcnew DataGridViewTextBoxColumn();
	c7->Name = "S'(j)";
	c7->HeaderText = "S'( j )";
	c7->Width = 100;
	dataGridView2->Columns->Add(c7);

	DataGridViewTextBoxColumn^ c8 = gcnew DataGridViewTextBoxColumn();
	c8->Name = "f'(j)";
	c8->HeaderText = "F'( j ) - S'( j )";
	c8->Width = 100;
	dataGridView2->Columns->Add(c8);

}

void SplinesCLRlab1::MyForm::Header3() //шапка третьей таблицы 
{
	DataGridViewTextBoxColumn^ c1 = gcnew DataGridViewTextBoxColumn();
	c1->Name = "j";
	c1->HeaderText = "j";
	c1->Width = 100;
	dataGridView3->Columns->Add(c1);

	DataGridViewTextBoxColumn^ c2 = gcnew DataGridViewTextBoxColumn();
	c2->Name = "x(j)";
	c2->HeaderText = "x( j )";
	c2->Width = 100;
	dataGridView3->Columns->Add(c2);

	DataGridViewTextBoxColumn^ c3 = gcnew DataGridViewTextBoxColumn();
	c3->Name = "f'(j)";
	c3->HeaderText = "F'( j )";
	c3->Width = 100;
	dataGridView3->Columns->Add(c3);

	DataGridViewTextBoxColumn^ c4 = gcnew DataGridViewTextBoxColumn();
	c4->Name = "S'(j)";
	c4->HeaderText = "S'( j )";
	c4->Width = 100;
	dataGridView3->Columns->Add(c4);

	DataGridViewTextBoxColumn^ c5 = gcnew DataGridViewTextBoxColumn();
	c5->Name = "f'(j)";
	c5->HeaderText = "F'( j ) - S'( j )";
	c5->Width = 100;
	dataGridView3->Columns->Add(c5);
	
}
