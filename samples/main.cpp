#include"Monom.h"
#include "Polynomial.h"

int main()
{
	/*Monom m(-8, 2, 4, 3);
	Monom m1(2, 2, 7, 3);
	Monom m2(3, 2, 4, 3);
	Monom k(45, 0, 0, 0);
	cout << -k;
	cout << m.solve(2, 1, 1)<<endl;

	Polynomial p;
	Polynomial p2;
	p = p + m;
	p2 = p2 + m;
	Polynomial p3 = p - p2;
	cout << p3 << endl;

	Monom m3(1, -3, 5, 4);
	Monom m4(4, 2, 3, 3);
	Monom m5(7, 1, 1, -4);
	Polynomial p4;
	p4 = p4 + m2;
	p4 = p4 + m3;
	Polynomial p5;
	p5 = p5 + m4;
	p5 = p5 + m5;
	cout << endl;
	cout << endl;
	cout << p5 << endl;
	cout << p4 * p5<<endl;
	cout << p5.solve(3, 4, 5);*/

	Polynomial p = Polynomial("2.2x^2y^3 + x^-2y^3 - 4z^5 + 5");
	
	cout << p;
}