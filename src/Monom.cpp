#include"Monom.h"
#define BOTTOM_POWER_FLOOR -5
#define TOP_POWER_FLOOR 10
#define E 1e-6
#define ALL_POWERS_ZERO_HASHED 328965

double Monom::solve(double _x, double  _y, double _z)
{
	return coefficient * pow(_x, getXPower()) * pow(_y, getYPower()) * pow(_z, getZPower());
}

double Monom::pow(double x, int power)
{
	if (power == 0) return 1.0;
	if (power < 0) return 1.0 / pow(x, -power);

	if (power % 2 == 0) {
		double half = pow(x, power / 2);
		return half * half;
	}
	else {
		return x * pow(x, power - 1);
	}
}


Monom::Monom(double _coefficent, int x, int y, int z)
{
	if (x < BOTTOM_POWER_FLOOR || x > TOP_POWER_FLOOR)
		throw - 2;
	if (y < BOTTOM_POWER_FLOOR || y > TOP_POWER_FLOOR)
		throw - 2;
	if (z < BOTTOM_POWER_FLOOR || z > TOP_POWER_FLOOR)
		throw - 2;
	
	coefficient = _coefficent;
	data.hashed = 0;
	data.powers[2] = x - BOTTOM_POWER_FLOOR;
	data.powers[1] = y - BOTTOM_POWER_FLOOR;
	data.powers[0] = z - BOTTOM_POWER_FLOOR;
}
Monom::Monom(double _coefficent, int x, int y) 
{
	if (x < BOTTOM_POWER_FLOOR || x > TOP_POWER_FLOOR)
		throw - 2;
	if (y < BOTTOM_POWER_FLOOR || y > TOP_POWER_FLOOR)
		throw - 2;
	
	coefficient = _coefficent;
	data.hashed = 0;
	data.powers[2] = x - BOTTOM_POWER_FLOOR;
	data.powers[1] = y - BOTTOM_POWER_FLOOR;
	data.powers[0] -= BOTTOM_POWER_FLOOR;
}
Monom::Monom(double _coefficent, int x) 
{
	if (x < BOTTOM_POWER_FLOOR || x > TOP_POWER_FLOOR)
		throw - 2;
	
	coefficient = _coefficent;
	data.hashed = 0;
	data.powers[2] = x - BOTTOM_POWER_FLOOR;
	data.powers[1] -= BOTTOM_POWER_FLOOR;
	data.powers[0] -= BOTTOM_POWER_FLOOR;
}
Monom::Monom(double _coefficent) 
{
	
	coefficient = _coefficent;
	data.hashed = 0;
	data.powers[2] -= BOTTOM_POWER_FLOOR;
	data.powers[1] -= BOTTOM_POWER_FLOOR;
	data.powers[0] -= BOTTOM_POWER_FLOOR;
}	

Monom::Monom()
{
	coefficient = 0;
	data.hashed = 0;
	data.powers[2] -= BOTTOM_POWER_FLOOR;
	data.powers[1] -= BOTTOM_POWER_FLOOR;
	data.powers[0] -= BOTTOM_POWER_FLOOR;
}

Monom::Monom(const Monom& other)
{
	coefficient = other.coefficient;
	data.hashed = other.data.hashed;
}




//#####################################################################################################

Monom Monom::operator*(const Monom& m)
{
	double resCoefficent = this->coefficient * m.coefficient;
	int resX = getXPower() + m.getXPower();
	int resY = getYPower() + m.getYPower();
	int resZ = getZPower() + m.getZPower();

	return Monom(resCoefficent, resX, resY, resZ);
}

Monom Monom::operator+(const Monom& m)
{
	if (data.hashed == m.data.hashed)
	{
		return Monom(coefficient + m.coefficient, getXPower(), getYPower(), getZPower());
	}
	throw - 1;
}

Monom Monom::operator-(const Monom& m)
{
	if (data.hashed == m.data.hashed)
	{
		return Monom(coefficient - m.coefficient, getXPower(), getYPower(), getZPower());
	}
	throw - 1;
}


//#####################################################################################################

bool Monom::operator==(Monom m) const noexcept
{
	
	if (fabs(coefficient - m.coefficient) < E && data.hashed == m.data.hashed)
		return true;
	return false;
}
bool Monom::operator!=(Monom m) const noexcept
{
	return !(*this == m);
}
bool Monom::operator>(Monom m) const noexcept
{
	if (data.hashed > m.data.hashed)
		return true;
	else if (data.hashed == m.data.hashed)
		if (coefficient - m.coefficient > E)
			return true;
	return false;
}
bool Monom::operator<(Monom m) const noexcept
{
	if (data.hashed < m.data.hashed)
		return true;
	else if (data.hashed == m.data.hashed)
		if (m.coefficient - coefficient > E)
			return true;
	return false;
}
bool Monom::operator>=(Monom m) const noexcept
{
	return !(*this < m);
}
bool Monom::operator<=(Monom m) const noexcept
{
	return !(*this > m);
}

//#####################################################################################################

double Monom::getCoefficent() const noexcept
{
	return coefficient;
}

int Monom::getXPower() const
{
	return data.powers[2] + BOTTOM_POWER_FLOOR;
}
int Monom::getYPower() const
{
	return data.powers[1] + BOTTOM_POWER_FLOOR;
}
int Monom::getZPower() const
{
	return data.powers[0] + BOTTOM_POWER_FLOOR;
}

bool Monom::isNull() const noexcept
{
	return abs(coefficient) < E;
}

bool Monom::isNegative() const noexcept
{
	return coefficient < 0;
}


//#####################################################################################################

ostream& operator<<(ostream& ostr, Monom m)
{
	ostr << m.coefficient;
	if(m.data.hashed != ALL_POWERS_ZERO_HASHED)
		for (int i = 0; i < 3; i++)
		{
			char vars[3] = { 'x', 'y', 'z' };
			ostr << vars[i] <<'^'<< '('<<m.data.powers[3 - i - 1] + BOTTOM_POWER_FLOOR<<')';
		}
	return ostr;
}

Monom operator-(Monom other)
{
	other.coefficient *= -1;
	return Monom(other);
}