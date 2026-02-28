#pragma once
#include<iostream>
#include<vector>
using namespace std;

union Data {
	unsigned int hashed;
	unsigned char powers[3];
};

struct powerCompare;

class Monom {
	friend powerCompare;
	double coefficient;

	double pow(double x, int power);

	int getXPower() const;
	int getYPower() const;
	int getZPower() const;
	double getCoefficent() const noexcept;
	Data data;
public:


	Monom(double _coefficent, int x, int y, int z);
	Monom(double _coefficent, int x, int y);
	Monom(double _coefficent, int x);
	Monom(double _coefficent);
	Monom();
	Monom(const Monom& other);

	double solve(double _x, double  _y, double _z);

	Monom operator*(const Monom& m);
	Monom operator+(const Monom& m);
	Monom operator-(const Monom& m);


	bool operator==(Monom m) const noexcept;
	bool operator!=(Monom m) const noexcept;
	bool operator>(Monom m) const noexcept;
	bool operator<(Monom m) const noexcept;
	bool operator>=(Monom m) const noexcept;
	bool operator<=(Monom m) const noexcept;

	friend ostream& operator<<(ostream& ostr, Monom m);
	friend Monom operator-(Monom other);
	bool isNull() const noexcept;
};

struct powerCompare
{
	bool operator() (const Monom& a, const Monom& b)const
	{
		return a.data.hashed > b.data.hashed;
	}
};

