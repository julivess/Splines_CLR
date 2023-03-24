#pragma once
#include <vector>
#include <math.h>
#include <iostream>

double n;
double h;
double m1;
double m2;

std::vector<double> F;
std::vector<double> A;
std::vector<double> B;
std::vector<double> c;
std::vector<double> a;
std::vector<double> b;
std::vector<double> d;
std::vector<std::vector<double>> Spl;

double f_test(double x) {
	if (x >= -1 && x <= 0) {
		return pow(x, 3) + 3 * pow(x, 2);
	}
	if (x > 0 && x <= 1) {
		return -pow(x, 3) + 3 * pow(x, 2);
	}
}
double f_test_1(double x) { //первая производная
	if (x >= -1 && x <= 0) {
		return 3*  pow(x, 2) + 6 * x;
	}
	if (x > 0 && x <= 1) {
		return -3 * pow(x, 2) + 6 * x;
	}
}
double f_test_2(double x) { 
	if (x >= -1 && x <= 0) {
		return 6 * x + 6;
	}
	if (x > 0 && x <= 1) {
		return -6 * x + 6;
	}
}

double f_basic(double x) {
	return log(x + 1) / (x + 1); 
}
double f_basic_1(double x) {
	return (1 - log(x + 1)) / ((x + 1)*(x + 1) );
}
double f_basic_2(double x) {
	return (-2 * (x + 1) * (1 - log(x + 1)) - x - 1) / pow((x + 1), 4);
}

double f_oscillating(double x) {
	return (log(x + 1)) / (x + 1) + cos(10*x);
}
double f_oscillating_1(double x) {
	return (1-log(x+1))/pow((x+1),2) - 10*sin(10*x);
}
double f_oscillating_2(double x) {
	return (-2 * (x + 1) * (1 - log(x + 1)) - x - 1) / pow((x + 1), 4) - 100 * cos(10 * x);
}


double x(int i) {
	return m1 + h * i;
}

double y(int i) {
	return m1 + h/2  + h * i;
}

double spline(double x_, int i) {
	return a[i] + b[i] * (x_ - x(i)) + c[i] / 2 * pow((x_ - x(i)), 2) + d[i] / 6 * pow((x_ - x(i)), 3);
}

double spline1(double x_, int i) {
	return b[i] + c[i] * (x_ - x(i)) + d[i] / 2 * pow((x_ - x(i)), 2); //первая производная 
}

double spline2(double x_, int i) {
	return c[i] + d[i] * (x_ - x(i)); //вторая производная 

}
void creation() { 
	for (int i = 0; i < n + 1; i++) { 
		std::vector<double> Vec;
		for (int j = 0; j < n + 1; j++) {
			Vec.push_back(0);
		}
		Spl.push_back(Vec);
	}

	Spl[0][0] = 1;
	Spl[n][n] = 1;

	for (int i = 1; i < n; ++i) {
		Spl[i][i - 1] = h;
		Spl[i][i] = 4 * h;
		Spl[i][i + 1] = h;
	}
	
	for (int i = 0; i < n + 1; i++) {
		F.push_back(0);
		A.push_back(0);
		B.push_back(0);
		c.push_back(0);
		a.push_back(0);
		b.push_back(0);
		d.push_back(0);
	}
}
void clear() {
	F.clear();
	A.clear();
	B.clear();
	c.clear();
	a.clear();
	b.clear();
	d.clear();
}
void vector_F_test() { //заполнение вектора F для тестовой функции 
	F[0] = 0;
	F[n] = 0;
	for (int i = 1; i < n; i++) {
		F[i] = 6 * ((f_test(x(i + 1)) - f_test(x(i))) / h - (f_test(x(i)) - f_test(x(i - 1))) / h);
	}
}
void vector_F_basic() { //F для основной 
	F[0] = 0;
	F[n] = 0;
	for (int i = 1; i < n; i++) {
		F[i] = 6 * ((f_basic(x(i + 1)) - f_basic(x(i))) / h - (f_basic(x(i)) - f_basic(x(i - 1))) / h);
	}
}
void vector_F_oscillating() {
	F[0] = 0;
	F[n] = 0;
	for (int i = 1; i < n; i++) {
		F[i] = 6 * ((f_oscillating(x(i + 1)) - f_oscillating(x(i))) / h - (f_oscillating(x(i)) - f_oscillating(x(i - 1))) / h);
	}
}
void sweep() { //метод прогонки 

	A[0] = Spl[0][1];
	B[0] = 0; //*
	for (int i = 1; i < n; i++) {
		A[i] = Spl[i][i + 1] / (-Spl[i][i] - Spl[i][i - 1] * A[i - 1]);
		B[i] = (-F[i] + Spl[i][i - 1] * B[i - 1]) / (-Spl[i][i] - Spl[i][i - 1] * A[i - 1]);
	}
	c[n] = 0; //*
	for (int i = n - 1; i >= 0; i--) {
		c[i] = A[i] * c[i + 1] + B[i];
	}
}

void odds_test() { //коэффициенты для тестовой функции 
	for (int i = 1; i <= n; i++) {
		a[i] = f_test(x(i));
		d[i] = (c[i] - c[i - 1]) / h;
		b[i] = (f_test(x(i)) - f_test(x(i - 1))) / h + c[i] * h / 3 + c[i - 1] * h / 6;
	}
}

void odds_basic() {
	for (int i = 1; i <= n; i++) {
		a[i] = f_basic(x(i));
		d[i] = (c[i] - c[i - 1]) / h;
		b[i] = (f_basic(x(i)) - f_basic(x(i - 1))) / h + c[i] * h / 3 + c[i - 1] * h / 6;
	}
}

void odds_oscillating() {
	for (int i = 1; i <= n; i++) {
		a[i] = f_oscillating(x(i));
		d[i] = (c[i] - c[i - 1]) / h;
		b[i] = (f_oscillating(x(i)) - f_oscillating(x(i - 1))) / h + c[i] * h / 3 + c[i - 1] * h / 6;
	}
}




