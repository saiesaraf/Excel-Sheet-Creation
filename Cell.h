#include<string>
#include "list.h"
#include <limits>
using namespace std;
class Cell{
public:
	int num1;
	//string representation of data in the string
	virtual std::string tostring();
	std::string a;
	int b;

};
class numericCell :public Cell{
public:
	numericCell();
	std::string tostring();
	numericCell(double x);
	double contents2;
	double getvalue();
};

class nonnumericCell :public Cell{
public:
	std::string tostring();
	nonnumericCell(std::string str);
	std::string contents3;

};
nonnumericCell::nonnumericCell(std::string contents_string)
{
	contents3 = contents_string;
	
}



numericCell::numericCell(double x)

{
	contents2 = x;
	
}

std::string numericCell::tostring(){

	return to_string(contents2);
}
std::string numericCell::tostring(){

	return to_string(contents2);
}
std::string FunctionCells::tostring(){

	return to_string(FunctionCells::fval);
}

std::string nonnumericCell::tostring(){

	return contents3;
}

std::string Cell::tostring(){

	return a;
}
double numericCell::getvalue()
{
	return contents2;
}
std::string FunctionCells::tostring()
{
	return contents_function;
}

class FunctionCells :public numericCell{

public:
	//need to define tostring function for functioncells
	//std::string tostring();
	//Declaring the values that are being passed to the FunctionCells
	std::string tostring();
	int in_Row;
	int begin_offset;
	int last_offset;
	std::string typen;
	double fval;
	std::string contents_function;
	
	//Function cell constructor
	//FunctionCells(string, int, int, int, LList<LList<Cell*>>&) :numericCell(contents2);
	FunctionCells(double);

//Function cells for calculating min max and mean


FunctionCells::FunctionCells(string type1, int inR1, int offset1, int fiR1, LList<LList<Cell*>>&rows) : numericCell(contents2)
{

	//int h1, w1;
	int in_Row = inR1;
	int begin_offset = offset1;
	int last_offset = fiR1;
	string typen = type1;
	//Stoaring the pointers for e in a spreadsheet
	LList<LList<Cell*>>* lpointer = &rows;
	LList<LList<Cell*>>::iterator funr = lpointer->begin();
	LList<Cell*>::iterator beginoffset = (*funr).begin();
	LList<Cell*>::iterator endoffset = (*funr).begin();
	if (typen == "mean")
	{
		//initial value when the stirg or bad input is given-NaN
		double m = std::numeric_limits < double >::quiet_NaN();		
		//start iterating till you reach the given row
		int h = 0;
		int w = 0;
		for (LList<LList<Cell*>>::iterator I = rows.begin(); I != rows.end(); ++I)
		{
			int r = 0;
			double p = 0;		
			if (h == in_Row)
			{
				for (LList<Cell*>::iterator J = (*I).begin(); J != (*I).end(); ++J)
				{
					if (w == begin_offset)
					{

						for (int w = begin_offset; w <= last_offset; ++w, J++)
						{

							if (dynamic_cast<numericCell*>(*J) != NULL){
								double x1 = dynamic_cast<numericCell*>(*J)->getvalue();
								r++;
								p = p + x1;
							}
						}
						break;
					}
					w++;
				}//first for loop
				break;
				for (LList<LList<Cell*>>::iterator I = rows.begin(); I != rows.end(); ++I)
				{
					for (LList<Cell*>::iterator J = (*I).begin(); J != (*I).end(); ++J)
					{
						*J = new FunctionCells(p/r);
					}
				}
			}
			h++;
			
		}//second for loop
	    
	}//if mean brance
	else if (typen == "min")
	{
		//initial value when the stirg or bad input is given-NaN
		double m = std::numeric_limits < double >::quiet_NaN();
	}//if min brance
	else if (typen == "max")
	{
		//initial value when the string or bad input is given-NaN
		double m = std::numeric_limits < double >::quiet_NaN();
	}//if max brance
	else
	{
		std::cout << "Error: Unknown command\n";
	}
}//Function cell brance*/

};//Function cell class ends