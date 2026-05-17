//////////////////////////////////ТЕСТОВАЯ ЗАДАЧА////////////////////////////////////////////////////////////////////////////////////
#include<iostream>
#include<cmath>
#include<fstream>
#include<iomanip>


using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////


double y_1(double t)
{
	return cos(t) / sqrt(1 + exp(2 * t));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double y_2(double t)
{
	return sin(t) / sqrt(1 + exp(2 * t));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double* f(double t, double* yi)//для конкретноего проимера n=2
{
	double* dy = new double[2];
	dy[0] = (-1) * sin(t) / sqrt(1 + exp(2 * t)) + yi[0] * (yi[0] * yi[0] + yi[1] * yi[1] - 1);

	dy[1] =  cos(t) / sqrt(1 + exp(2 * t)) + yi[1] * (yi[0] * yi[0] + yi[1] * yi[1] - 1);

	return dy;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double** RK3(double* (*func)(double, double*), double a, double b, double* y0, int N, int n)
{
	double** Y = new double*[N+1];
	for (int i = 0;i < N + 1;i++)
		Y[i] = new double[n];


	double h = (b - a) / N;

	for (int i = 0;i < n;i++)
		Y[0][i] = y0[i];



	for (int i = 1;i < N + 1;i++)
	{
		double ti = a + (i-1) * h;
		//if (i == N)
		//	ti = b;

		double* k1 = func(ti, Y[i - 1]);//вектор k1 для всего вектора решенния на ti

		double* yp = new double [n];
		for (int l = 0;l < n;l++)
			yp[l] = Y[i - 1][l] + 0.5 *h* k1[l];

		double* k2 = func(ti + 0.5 * h, yp);

		for (int l = 0;l < n;l++)
			yp[l] = Y[i - 1][l] + 0.75*h * k2[l];

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
	f << 't' << '\t' << "y1" << '\t' << "y2" << endl;


	for (int i = 0;i < N;i++)
	{
		f << a + i * h;
		for (int j = 0;j < n;j++)
			f << '\t' << Y[i][j];
		f << endl;
	}

	f  << b;
	for (int j = 0;j < n;j++)
		f << '\t' << Y[N][j];
	f << endl;
}
//////////////////////////////////////////////////////////////////////////
void show_true_sol(ofstream& f, double a, double b, int N)//для конкретного примера
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
double find_e(double** Y, double a, double b, double N)//конкретно для моего примера
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
	ofstream out_t("true solution.txt");
	ofstream out_eh("pogr.txt");
	int n = 2;
	int N =65;
	double a = 0.0;
	double b = 5.0;
	double h = (b - a) / N;


	double* y_0 = new double[n];

	y_0[0] = y_1(0.0);
	y_0[1] = y_2(0.0);


	double** Y = RK3(f, a, b, y_0, N, n);

	show_approx_sol(out, a, b, Y, N, n);
	show_true_sol(out_t, a, b, N);

	out_eh << 'h' << '\t' << "e" << '\t' << "e/h**3" << endl;

	double e = find_e(Y, a, b, N);
	out_eh << h << '\t' << e << '\t' << e/(h*h*h) << endl;



	int count_h = 10;
	int k = 0;
	double** err_h = new double* [count_h];
	for (int i = 0;i < count_h;i++)
		err_h[i] = new double[2];

	err_h[k][0] = h;
	err_h[k][1] = e;
	k++;

	





	for (int i = 0;i < N + 1;i++)
		delete[] Y[i];
	delete[] Y;


	while (k < count_h)
	{
		N *= 2;
		h = (b - a) / N;
		double** Y = RK3(f, a, b, y_0, N, n);
		e = find_e(Y, a, b, N);
		out_eh << h << '\t' << e << '\t' << e / (h * h * h) << endl;

		err_h[k][0] = h;
		err_h[k][1] = e;
		k++;



		for (int i = 0;i < N + 1;i++)
			delete[] Y[i];
		delete[] Y;


	}

	delete[] y_0;


	for (int i = 0;i < count_h / 2;i++)
	{
		double* temp = err_h[i];
		err_h[i] = err_h[count_h - 1 - i];
		err_h[count_h - 1 - i] = temp;
	}

	ofstream out_err_alpha("alpha(h).txt");
	out_err_alpha << "h" << "\t" << "alpha" << endl;

	for (int i = 0;i < count_h - 1;i++)
	{
		double alpha_i = log10(err_h[i + 1][1] / err_h[i][1]) / log10(err_h[i + 1][0] / err_h[i][0]);
		out_err_alpha << err_h[i][0] << '\t' << alpha_i << endl;

	}


	out_err_alpha.close();








	out.close();
	out_t.close();
	out_eh.close();
	return 0;
}