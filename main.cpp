#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;


const int 
	WIDTH = 316,
	HEIGHT = 73,
	CENTER_X = WIDTH / 2,
	CENTER_Y = HEIGHT / 2,
	DIGIT_COUNT = 4;
	
const char 
	HORIZONTAL_LINE = '-',
	VERTICAL_LINE = '|',
	CROSS = '+',
	F1_POINT = '@',
	F2_POINT = '#',
	INTERSECTION = 'X';
	
const double
	D1 = -1.190250,
	D2 = 0.108880,
	A = 0.654,
	B = 0.988,
	MIN_X = -3,
	MAX_X = 3,
	MIN_Y = -3,
	MAX_Y = 3,
	K_X = (MAX_X - MIN_X) / WIDTH,
	K_Y = (MAX_Y - MIN_Y) / HEIGHT,
	P = 0.01,
	EPS = min((MAX_X - MIN_X) * P, (MAX_Y - MIN_Y) * P),
	FR_X = 10,
	FR_Y = 10;


char a[HEIGHT][WIDTH]{};
ofstream file("output.txt");


void output_to_file();
void draw_x_axis();
void draw_y_axis();
bool on_f1(double x, double y);
bool on_f2(double x, double y);
double convert_x(int j);
double convert_y(int i);
void draw_f1();
void draw_f2();
void draw_numbers_x();
void draw_numbers_y();


int main()
{
	draw_x_axis();
	draw_y_axis();
	draw_f1();
	draw_f2();
	draw_numbers_x();
	draw_numbers_y();
    output_to_file();
    return 0;
}


void output_to_file()
{
	for (int i = 0; i < HEIGHT; i++)
    {
    	for (int j = 0; j < WIDTH; j++)
    	{
    		file << a[i][j];
		}
		file << '\n';
	}
    file.close();
}


void draw_x_axis()
{
	int i = CENTER_Y;
	for (int j = 0; j < WIDTH; j++)
	{
		a[i][j] = HORIZONTAL_LINE;
	}
}


void draw_y_axis()
{
	int j = CENTER_X;
	for (int i = 0; i < HEIGHT; i++)
	{
		a[i][j] = VERTICAL_LINE;
	}
}


bool on_f1(double x, double y)
{
	double value = cosh(0.4 * y * y - x) - x * y - x + y + D1;
	return abs(value) <= EPS;
}


bool on_f2(double x, double y)
{
	double value = pow(x * x + y * y - A * A - A * x, 2) - B * B * (x * x + y * y) + D2;
	return abs(value) <= EPS;
}


double convert_x(int j)
{
	return (j - CENTER_X) * K_X;
}


double convert_y(int i)
{
	return -(i - CENTER_Y) * K_Y;
}


void draw_f1()
{
	for (int i = 0; i < HEIGHT; i++)
    {
    	for (int j = 0; j < WIDTH; j++)
    	{
    		double 
				x = convert_x(j),
				y = convert_y(i);
    		if (on_f1(x, y))
    		{
    			a[i][j] = F1_POINT;
			}
		}
	}
}


void draw_f2()
{
	for (int i = 0; i < HEIGHT; i++)
    {
    	for (int j = 0; j < WIDTH; j++)
    	{
    		double 
				x = convert_x(j),
				y = convert_y(i);
    		if (on_f2(x, y) && a[i][j] == F1_POINT)
    		{
    			a[i][j] = INTERSECTION;
			}
			else if (on_f2(x, y))
			{
				a[i][j] = F2_POINT;
			}
		}
	}
}


void draw_numbers_x()
{
	int i = CENTER_Y;
	for (int j = CENTER_X; j < WIDTH; j += FR_X)
	{
		double value = convert_x(j);
		string number = to_string(value);
		a[i][j] = CROSS;
		for (int ch_i = 0; ch_i < DIGIT_COUNT; ch_i++)
		{
			a[i + 1][j - DIGIT_COUNT / 2 + ch_i] = number[ch_i];
		}
	}
	for (int j = CENTER_X; j > 0; j -= FR_X)
	{
		double value = convert_x(j);
		string number = to_string(value);
		a[i][j] = CROSS;
		for (int ch_i = 0; ch_i < DIGIT_COUNT + 1; ch_i++)
		{
			a[i + 1][j - DIGIT_COUNT / 2 + ch_i] = number[ch_i];
		}
	}
}


void draw_numbers_y()
{
	int j = CENTER_X;
	for (int i = CENTER_Y; i > 0; i -= FR_Y)
	{
		double value = convert_y(i);
		string number = to_string(value);
		a[i][j] = CROSS;
		for (int ch_i = 0; ch_i < DIGIT_COUNT; ch_i++)
		{
			a[i][j + ch_i + 1] = number[ch_i];
		}
	}
	for (int i = CENTER_Y; i < HEIGHT; i += FR_Y)
	{
		double value = convert_y(i);
		string number = to_string(value);
		a[i][j] = CROSS;
		for (int ch_i = 0; ch_i < DIGIT_COUNT + 1; ch_i++)
		{
			a[i][j + ch_i + 1] = number[ch_i];
		}
	}
}