#include "Polynomial.h"

Polynomial::Polynomial()
{

}

Polynomial::Polynomial(string expression)
{

}

Polynomial::Polynomial(const Polynomial& other)
{
	monoms = other.monoms;
}

Polynomial& Polynomial::operator=(const Polynomial& other)
{
	if (this == &other) return *this;
	monoms = other.monoms;
	return *this;
}

void Polynomial::deleteZeroMonoms()
{
	for (auto it = monoms.begin(); it != monoms.end(); )
	{
		if ((*it).isNull())
			it = monoms.erase(it);
		else
			++it;
	}
}



Polynomial Polynomial::operator+(Monom other)
{
	Polynomial res = Polynomial(*this);
	auto it = res.monoms.find(other);
	if (it != res.monoms.end() && !monoms.empty())
	{
		*it = *it + other;
	}
	else
	{
		res.monoms.insert(other);
	}
	res.deleteZeroMonoms();
	return res;
}

Polynomial Polynomial::operator-(Monom other)
{
	Polynomial res = Polynomial(*this);
	auto it = res.monoms.find(other);
	if (it != res.monoms.end())
	{
		*it = *it - other;
	}
	else
	{
		res.monoms.insert(-other);
	}
	res.deleteZeroMonoms();
	return res;
}
Polynomial Polynomial::operator*(Monom other)
{
	Polynomial res = Polynomial(*this);
	for (auto it = res.monoms.begin(); it != res.monoms.end(); )
	{
		try
		{
			*it = *it * other;
			++it;
		}
		catch (...)
		{
			it = res.monoms.erase(it);
		}
	}
	return res;
}

Polynomial Polynomial::operator+(Polynomial other)
{
	Polynomial res = Polynomial(*this);
	res.monoms = res.monoms + other.monoms;
	res.deleteZeroMonoms();
	return res;
}
Polynomial Polynomial::operator-(Polynomial other)
{
	Polynomial res = Polynomial(*this);
	Polynomial tmp = Polynomial(other);
	for (auto it = tmp.monoms.begin(); it != tmp.monoms.end(); ++it)
	{
		*it = -(*it);
	}
	res.monoms = res.monoms + tmp.monoms;
	res.deleteZeroMonoms();
	return res;
}
Polynomial Polynomial::operator*(Polynomial other)
{
	Polynomial res = Polynomial(*this);
	res.monoms.clear();
	for (auto it = other.monoms.begin(); it != other.monoms.end(); ++it)
	{
		res = res + (*this) * (*it);
	}
	return res;
}



double Polynomial::solve(double _x, double  _y, double _z)
{
	double res = 0;
	for (auto it = monoms.begin(); it != monoms.end(); ++it)
	{
		res += (*it).solve(_x, _y, _z);
	}
	return res;
}

ostream& operator<<(ostream& ostr, const Polynomial& p)
{
	
	if (p.monoms.begin() != p.monoms.end())
	{
		auto it = p.monoms.begin();
		ostr << *it;
		++it;

		while (it != p.monoms.end())
		{
			ostr << " + " << *it;
			++it;
		}
	}
	return ostr;
}
