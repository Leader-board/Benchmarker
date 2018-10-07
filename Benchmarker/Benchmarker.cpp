// Benchmarker.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <ctime>
#include <exception>
#include <conio.h>
using namespace std;
int check = 2;
double a, b, powcheck, k, d, x, y;// x and y are the squares of a and b.
int verify = 0;
int percentage = 0;// declaring variable to update percentage
double c;
float score[5], totalscore = 0;
// This program prints all the Pythagorean triplets from 1 to k , which the user will enter.
void selection()
{
	int choose;
	base:cout << "Type 1 to start benchmarking." << '\n';
	try
	{
		cin >> (int) choose;
		if (cin.fail())
			throw 2;
		if (choose != 1)
		{
			throw "Invalid number, try again \n";
		}
	}
	catch (char* msg)
	{
		cout << msg << '\n';
		goto base;
	}
	catch (int x)
	{
		cout << "Invalid entry. Program will close now. \n";
		_getch();
		exit(1);
	}
}
void mainbase()
{
	long count;
	double timetake[5];
	// check is meant to find out if we should also include an explaination as to why a triplet is indeed a Pythagorean one.
	// D will represent C for greatest pythagorean triplet purposes.
	// k is the number which the user will enter. This value limits the value of a and b through which the program can search.
	for (int q = 1; q <= 5; q++)
	{
		for (int p = 1; p <= 5; p++)
		{
			clock_t begin = clock();
			a = 1;
			b = 1;
			c = 1;
			d = 1;
			count = 0;// a and b are the base/height.
			if (p == 1)
				k = 100;
			else if (p == 2)
				k = 250;
			else if (p == 3)
				k = 500;
			else if (p == 4)
				k = 1000;
			else if (p == 5)
				k = 1500;
			while (b <= k)
			{
				while (a <= k)
				{
					x = a*a;
					y = b*b;
					c = x + y;
					powcheck = b;	// b as starting point. Meant to speed up execution
					while (powcheck <= ceil(1.42*k)) // Max value of c with relation to a and b is c = root2 of a , b
					{
						if (c == pow(powcheck, 2))
						{
							if (c >= d)
								d = c;
							++count;
							powcheck = 2 * k + 1;
						}
						else
						++powcheck;
					}
					++a;
				}
				a = 1;
				++b;
			}
			clock_t end = clock();
			double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
			timetake[p - 1] = elapsed_secs;
			float r;
			if (p == 1)
				r = 0.003;
			if (p == 2)
				r = 0.035;
			if (p == 3)
				r = 0.273;
			if (p == 4)
				r = 2.225;
			if (p == 5)
				r = 7.536;
			score[p - 1] = 200 * (r / timetake[p - 1]);
			totalscore = totalscore + (0.2*(score[p - 1]));
			cout << p * 4 + (q - 1) * 20 << " % complete!" << '\n';
			cout << "Time taken for that stage:- " << timetake[p - 1] << '\n';
			cout << "Score obtained for that stage:- " << score[p - 1] * 5 << '\n';
		}
	} 
}
void main()
{
	selection();
	mainbase();
	cout << "Your system has scored a total of " << totalscore << " points!" << '\n';
	system("pause");
}