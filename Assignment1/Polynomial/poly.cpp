#include "poly.h"

//assumption: only accept positive int coeff and power, if either coeff or power is negative then default coeff to 0
Poly::Poly(int coefficient, int power)
{
	//get size of the array based on the power_ > 0 then size is power_ + 1, else size = 1
	if (power >= kDefaultValue)
		size = power + 1;
	else
		size = kDefaultSize;

	//decalre a new dynamic array
	array = new int[size];

	//positive exponent
	if (power >= kDefaultValue)
	{
		for (int i = 0; i < size; i++)
		{
			array[i] = kDefaultValue;
		}
		//set input exponent's to its coefficient
		array[power] = coefficient;
	}
	//otherwise, set coefficient to 0
	else
		array[0] = kDefaultValue;
}

//end of Poly constructor
//------------------------------------------------------------------------------------------

Poly::Poly(const Poly& rhs_poly)
{
	Copy(rhs_poly);
}

//end of deep copy constructor
//------------------------------------------------------------------------------------------

Poly::~Poly()	//delete array, set *array to null
{
	delete[] array;
	array = nullptr;
}

//end of Poly destructor
//------------------------------------------------------------------------------------------

int Poly::getCoeff(int power) const
{
	if (power >= size || power < 0)
		return 0;
	else
		return array[power];
}

//end of getCoeff method
//------------------------------------------------------------------------------------------

void Poly::setCoeff(int coefficient, int power)
{
	//resize if exponent is greater than the curr size
	if (power >= size)
	{
		int newSize = power + 1;
		int* temp = array;			//points to the old array
		array = new int[newSize];	//array now points to new array

		//put new value to the new array
		for (int i = 0; i < newSize; i++)
		{
			//copy old array to new array
			if (i < size)
				array[i] = temp[i];
			//else, set default value for new array
			else
				array[i] = kDefaultValue;
		}
		array[power] = coefficient;		//set coeff for corresponding power
		size = newSize;					//set new size

		//delete temp
		delete[] temp;
		temp = nullptr;
	}
	//else, in range and positive exponent
	else if (power >= 0)
		array[power] = coefficient;
}

//end of setCoeff method
//------------------------------------------------------------------------------------------

//asign poly for example A = B = C
Poly Poly::operator=(const Poly& rhs)
{
	//check if two objects !=
	if (&rhs != this)
	{
		delete[] array;
		//copy rhs array into this array
		Copy(rhs);
	}
	return *this;
}

//end of = operator
//------------------------------------------------------------------------------------------

Poly Poly::operator*(const Poly& rhs) const
{
	int sum = size + rhs.size - 2;			//sum of two size
	Poly tmp(kDefaultValue, sum);			//return poly

	//iterate from the back of the array
	for (int i = size - 1; i >= 0; i--)
	{
		//check if first polynomial coefficient != 0
		if (array[i] != 0)
		{
			//rhs poly
			for (int j = rhs.size - 1; j >= 0; j--)
			{
				//check if second polynomial coefficient != 0
				if (rhs.array[j] != 0)
					//calculation
					tmp.array[i + j] += (array[i] * rhs.array[j]);
			}
		}
	}
	return tmp;
}

//end of * operator
//------------------------------------------------------------------------------------------

Poly& Poly::operator*=(const Poly& rhs)
{
	int sum = size + rhs.size - 2;			//sum of two size
	setCoeff(kDefaultValue, sum);			//set size for return poly
	
	//iterate from the back of the array
	for (int i = size - 1; i >= 0; i--)
	{
		//check if first polynomial coefficient != 0
		if (array[i] != 0)
		{
			//rhs poly
			for (int j = rhs.size - 1; j >= 0; j--)
			{
				//check if second polynomial coefficient != 0
				if (rhs.array[j] != 0)
					//calculation
					array[i + j] += (array[i] * rhs.array[j]);
			}
		}
	}
	return *this;
}

//end of *= operator
//------------------------------------------------------------------------------------------

Poly Poly::operator+(const Poly& rhs) const
{
	int maxSize;
	//compare two sizes and get the bigger one to be the array size
	size < rhs.size ? maxSize = rhs.size : maxSize = size;
	Poly tmp(kDefaultValue, maxSize);	//a temporary poly

	//calculation: adding polynomial until the end of array
	for (int i = maxSize - 1; i >= 0; i--)
	{
		//iterate from last index to equal index
		if (i >= size)
			tmp.array[i] = rhs.array[i];
		else
		{
			if (i >= rhs.size)
				tmp.array[i] = array[i];	//copy value
			else
				tmp.array[i] = array[i] + rhs.array[i];	//adding the two arrays
		}
	}
	return tmp;
}

//end of + operator
//------------------------------------------------------------------------------------------

Poly& Poly::operator+=(const Poly& rhs)
{
	int maxSize;
	//compare two sizes and get the bigger one to be the array size
	size < rhs.size ? maxSize = rhs.size : maxSize = size;
	
	//calculation: adding polynomial until the end of array
	for (int i = maxSize - 1; i >= 0; i--)
	{
		//iterate from last index to equal index
		if (i >= size)
			setCoeff(rhs.array[i], i);	//resize poly
		else
			array[i] += rhs.array[i];
	}
	return *this;
}

//end of += operator
//------------------------------------------------------------------------------------------

Poly Poly::operator-(const Poly& rhs) const
{
	int maxSize;
	//compare two sizes and get the bigger one to be the array size
	size < rhs.size ? maxSize = rhs.size : maxSize = size;
	Poly tmp(kDefaultValue, maxSize);	//a temporary poly

	//calculation: adding polynomial until the end of array
	for (int i = maxSize - 1; i >= 0; i--)
	{
		//iterate from last index to equal index
		if (i >= size)
			tmp.array[i] = rhs.array[i];
		else
		{
			if (i >= rhs.size)
				tmp.array[i] = array[i];				//copy value
			else
				tmp.array[i] = array[i] - rhs.array[i];	//subtracting the two arrays
		}
	}
	return tmp;
}

//end of - operator
//------------------------------------------------------------------------------------------

Poly& Poly::operator-=(const Poly& rhs)
{
	int maxSize;

	//compare two sizes and get the bigger one to be the array size
	size < rhs.size ? maxSize = rhs.size : maxSize = size;

	//calculation: subtracting polynomial until the end of array
	for (int i = maxSize - 1; i >= 0; i--)
	{
		//iterate from last index to equal index
		if (i >= size)
			setCoeff(-rhs.array[i], i);
		else
			array[i] -= rhs.array[i];
	}
	return *this;
}

//end of -= operator
//------------------------------------------------------------------------------------------

bool Poly::operator==(const Poly& rhs) const
{
	bool isEqual = true;

	//if the two polys are identical then return true
	if (&rhs == this)
		return isEqual;
	else
	{
		//set max and min size
		int minS = kDefaultValue;
		int maxS = kDefaultValue;

		//get max and min size
		size < rhs.size ? minS = size : minS = rhs.size;
		size > rhs.size ? maxS = size : maxS = rhs.size;

		//check for equal
		for (int i = 0; (i < maxS) && (isEqual == true); i++)
		{
			//check from max to min size
			if (i < minS)
			{
				if (array[i] != rhs.array[i])
					isEqual = false;
			}
			//check from min to max size
			else
			{
				//check first array
				if (size > rhs.size)
				{
					if (array[i] != 0)
						isEqual = false;
				}
				//check second array
				else
				{
					if (rhs.array[i] != 0)
						isEqual = false;
				}
			}
		}
	}
	return isEqual;
}

//end of == operator
//------------------------------------------------------------------------------------------

bool Poly::operator!=(const Poly& rhs) const
{
	return !(*this == rhs);
}

//end of != operator
//------------------------------------------------------------------------------------------

void Poly::Copy(const Poly& rhs_poly)
{
	size = rhs_poly.size;		//set equal size
	array = new int[size];		//new dynamic array

	//copy each elements of the array
	for (int i = 0; i < rhs_poly.size; i++)
	{
		array[i] = rhs_poly.array[i];
	}
}

//end of Copy method
//------------------------------------------------------------------------------------------

ostream& operator<<(ostream& stream, const Poly& rhs)
{
	//check if poly is zero
	bool isZero = true;

	//check each exponent
	for (int i = rhs.size - 1; i >= 0; i--)
	{
		//check for nonzero coefficient to print
		if (rhs.array[i] != 0)
		{
			//insert one space between each term
			stream << ' ';
			//if coefficient is positive, put a plus sign before it
			if (rhs.array[i] > 0)
				stream << '+';
			//print power if > 1
			if (i > 1)
				stream << rhs.array[i] << "x^" << i;
			//don't print power if == 1
			else if (i == 1)
				stream << rhs.array[i] << 'x';
			//last case: power = 0, print coefficient
			else
				stream << rhs.array[i];

			//polynomial is not zero
			isZero = false;
		}
	}
	//if poly is zero then return 0
	if (isZero)
		stream << 0;
	return stream;
}

//end of output stream
//------------------------------------------------------------------------------------------

istream& operator>>(istream& stream, Poly& rhs)
{
	//set coefficient, power
	int coefficient = kDefaultValue, power = kDefaultValue;

	//wait until user input is -1 -1
	while (!(coefficient == -1 && power == -1))
	{
		//get coefficient and power
		stream >> coefficient >> power;

		//stop if input is wrong and clean buffer
		if (stream.fail())
		{
			stream.clear();
			stream.ignore(99, '\n');

			//break out of loop
			coefficient = -1;
			power = -1;
		}

		//else, set poly
		else
			rhs.setCoeff(coefficient, power);
	}
	return stream;
}
//end of input stream
//------------------------------------------------------------------------------------------