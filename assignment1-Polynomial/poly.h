#ifndef POLY_H_
#define POLY_H_
#include <iostream>
using namespace std;

const int kDefaultValue = 0;						//set the default of an array to 0
const int kDefaultSize = 1;							//set the default size to 1

class Poly
{
public:
	//constructor
	Poly(int = kDefaultValue, int = kDefaultValue);	//normal constructor, if only one parameter is passed in then assume that it is the coefficient and power is 0
	Poly(const Poly& rhs_poly);						//deep copy constructor
	
	//destructor
	~Poly();

	//getters-setters
	int getCoeff(int power_) const;
	void setCoeff(int coefficient_, int power_);

	//overloading opeartors
	Poly operator=(const Poly& rhs);				//assign poly

	Poly operator* (const Poly& rhs) const;			//right hand side
	Poly& operator*= (const Poly& rhs);

	Poly operator+ (const Poly& rhs) const;
	Poly& operator+= (const Poly& rhs);

	Poly operator- (const Poly& rhs) const;
	Poly& operator-= (const Poly& rhs);

	bool operator== (const Poly& rhs) const;
	bool operator!= (const Poly& rhs) const;

	//input-output
	friend ostream& operator<< (ostream& stream, const Poly& rhs);
	friend istream& operator>> (istream& stream, Poly& rhs);

private:
	int coefficient_;								//private parameter
	int power_;										//private parameter
	int* array = nullptr;							//dynamic array
	int size;										//size of array
	void Copy(const Poly& rhs_poly);				//copy another polynomial
};
#endif