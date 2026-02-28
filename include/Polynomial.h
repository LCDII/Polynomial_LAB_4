#pragma once

#include <string>
#include<iostream>
#include"SkipList.h"
#include"Monom.h"
using namespace std;


class Polynomial
{	
	SkipList<Monom, powerCompare> monoms;
	void deleteZeroMonoms();
public:
	Polynomial();
	Polynomial(const Polynomial& other);
	Polynomial& operator=(const Polynomial& other);
	Polynomial(string expression);


	Polynomial operator+(Monom other);
	Polynomial operator-(Monom other);
	Polynomial operator*(Monom other);

	Polynomial operator+(Polynomial other);
	Polynomial operator-(Polynomial other);
	Polynomial operator*(Polynomial other);

	double solve(double _x, double  _y, double _z);

	friend ostream& operator<<(ostream& ostr, const Polynomial& p);
};