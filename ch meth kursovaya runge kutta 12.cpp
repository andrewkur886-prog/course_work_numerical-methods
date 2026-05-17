////////////////////////////////////////////////ОСНОВНАЯ ЗАДАЧА СХЕМЫ ХИЩНИК ЖЕРТВА///////////////////////////////////////////////
#include<iostream>
#include<cmath>
#include<fstream>
#include<iomanip>


using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double alpha = 1.0;
double beta = 0.13;
double gamma = 5.0;





double y_1(double t)//нужно было для тестовой
{
	return cos(t) / sqrt(1 + exp(2 * t));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double y_2(double t)//нужно было для тестовой
{
	return sin(t) / sqrt(1 + exp(2 * t));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double* f(double t, double* yi)//для конкретноего приимера n=2 нашей задачи модели хищник-жертва	
{
	double* dy = new double[2];
	dy[0] = gamma*(1-yi[0])*yi[0]-((alpha* yi[0]* yi[1])/(beta+ yi[0]));

	dy[1] = (1-(yi[1]/ yi[0]))* yi[1];

	return dy;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double** RK3(double* (*func)(double, double*), double a, double b, double* y0, int N, int n)
{
	double** Y = new double* [N + 1];
	for (int i = 0;i < N + 1;i++)
		Y[i] = new double[n];


	double h = (b - a) / N;

	for (int i = 0;i < n;i++)
		Y[0][i] = y0[i];



	for (int i = 1;i < N + 1;i++)
	{
		double ti = a + (i - 1) * h;


		double* k1 = func(ti, Y[i - 1]);//вектор k1 для всего вектора решенния на ti

		double* yp = new double[n];
		for (int l = 0;l < n;l++)
			yp[l] = Y[i - 1][l] + 0.5 * h * k1[l];

		double* k2 = func(ti + 0.5 * h, yp);

		for (int l = 0;l < n;l++)
			yp[l] = Y[i - 1][l] + 0.75 * h * k2[l];

		double* k3 = func(ti + 0.75 * h, yp);


		for (int j = 0;j < n;j++)
			Y[i][j] = Y[i - 1][j] + h * (2 * k1[j] + 3 * k2[j] + 4 * k3[j]) / 9;




		delete[]k1;
		delete[]k2;
		delete[]k3;
		delete[]yp;

	}
	return Y;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void show_matr(ofstream& f, double** Y, int m, int n)
{
	for (int i = 0;i < m;i++)
	{
		for (int j = 0;j < n;j++)
			f << setw(10) << Y[i][j];
		f << endl;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void show_approx_sol(ofstream& f, double a, double b, double** Y, int N, int n)
{
	double h = (b - a) / N;
	f << 't' << '\t' << "X" << '\t' << "Y" << endl;


	for (int i = 0;i < N;i++)
	{
		f << a + i * h;
		for (int j = 0;j < n;j++)
			f << '\t' << Y[i][j];
		f << endl;
	}

	f << b;
	for (int j = 0;j < n;j++)
		f << '\t' << Y[N][j];
	f << endl;
}
//////////////////////////////////////////////////////////////////////////
void show_true_sol(ofstream& f, double a, double b, int N)//для тестовой нужно было
{
	double h = (b - a) / N;
	double t = a;
	f << 't' << '\t' << "u1" << '\t' << "u2" << endl;

	for (int i = 0;i < N;i++)
	{
		t = a + h * i;
		f << t << '\t' << y_1(t) << '\t' << y_2(t) << endl;

	}

	f << b << '\t' << y_1(b) << '\t' << y_2(b) << endl;
}
////////////////////////////////////////////////////////////////////
double find_e(double** Y, double a, double b, double N)//нужно было для тестовой
{
	double e = 0.0;
	double h = (b - a) / N;

	for (int i = 1;i < N + 1;i++)
	{
		double t = a + h * i;
		if (i == N)
			t = b;

		double e1 = fabs(Y[i][0] - y_1(t));
		double e2 = fabs(Y[i][1] - y_2(t));
		if (e1 > e)
			e = e1;
		if (e2 > e)
			e = e2;
	}
	return e;
}

int main()
{
	ofstream out("out.txt");

	int n = 2;
	int N = 15000;
	double a = 0.0;
	double b = 150;
	double h = (b - a) / N;


	double* y_0 = new double[n];

	y_0[0] = 0.5;//начальные
	y_0[1] = 0.5;


	while (alpha < 31)
	{
		out << "alpha = " << alpha << endl;
		double** Y = RK3(f, a, b, y_0, N, n);

		show_approx_sol(out, a, b, Y, N, n);
		out << endl << endl;



		for (int i = 0;i < N + 1;i++)
			delete[] Y[i];
		delete[] Y;
		alpha++;

	}
	


	delete[] y_0;



	out.close();

	return 0;
}	