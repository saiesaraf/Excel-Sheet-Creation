/*Final Project:Generation of Spreadsheet*/
/*Written by Saie Saraf*/
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<typeinfo>
#include<algorithm>
#include<limits.h>
#include<exception>
#include "list.h"
#include "node.h"
#include "Cell.h"
using namespace std;
std::string line;


int main(int argc, char **argv)
{
	//Defining the variables
	int height;
	int width;
	string type;
	std::string addrow;
	std::string removerow;
	std::string print;
	std::string set;
	std::string quit;
	//If less number of arguments are provided by user then return1
	if (argc < 3)
	{
		std::cout << "You have entered nothing,enter rows and columns\n";
		return 1;
	}
	//Catching the exceptions in case the values of rows and columns are non numeric
	try
	{
		width = std::stoi(std::string(argv[1]));
		height = std::stoi(std::string(argv[2]));
		if (width == 0 || height == 0)
		{
			std::cout << "got the values 0\n";
			return 1;
		}
	}
	catch (std::exception e)
	{
		//handle failure of the stoi function
		//If the values given by the user are not numbers,then exception is catched
		std::cout << "Got the bad values for rows and columns\n";
		return 1;
	}

	//Reading the entire line from the user
	std::string line;
	LList<LList<Cell*>>rows;
	for (int i = 0; i < height; ++i)
	{
		//std::cout << "value of i is"<<i<<'\n';
		LList<Cell*>empty;
		rows.push_back(empty);
		for (int j = 0; j < width; ++j)
		{
			rows.back().push_back(new Cell());//assigned memory:need to delete it
		}
	}
	while (std::getline(std::cin, line))
	{
		//converting the string into the input stream 
		std::istringstream ss(line);
		//Take command as input from the user
		std::string command;
		//Take command input from user
		ss >> command;
		if (command == "print")
		{
			//first here empty spreadsheet is printed
			for (LList<LList<Cell*>>::iterator I = rows.begin(); I != rows.end(); ++I)
			{
				for (LList<Cell*>::iterator J = (*I).begin(); J != (*I).end(); ++J)
				{			
					if ((*J) != (*I).back()){
						std::cout << (**J).tostring() << ',';
					}
					else{
						std::cout << (**J).tostring();
					}
				}
				std::cout << "\n";
			}
		}
		//For set command
		//When the type is number,then value is taken from the user
		//User will specify the location of row and colmn,where to set the number
		//If user enters the value of rows and columns out of the spreadsheet limit-bad input
		else if (command == "set")
		{
			//Taking values from user-row and column
			std::string row;
			std::string column;
			ss >> column;
			ss >> row;
			//Catching the exception if the number is nonnumeric
			try{
				int r = (std::stoi(std::string(row))) + 1;
				int c = (std::stoi(std::string(column))) + 1;
				//Catching the exception if the rows and column is less than zero
				if (r - 1 >= height || c - 1 >= width)
				{
					std::cout << "Error: cell out of range\n";
				}
				//If the columns and rows entered by user are less than zero then printing error message
				if (c < 0 || r < 0)
				{
					std::cout << "Error: cell out of range\n";
				}
				//Taking type as an input from user
				ss >> type;
				if (type == "number")
				{					
					std::string num_contents;
					int h = 0;
					int w = 0;
					//Taking input of number type's contents from user
					ss >> num_contents;
					//Throwing an exception when number given by user is non numeric
					try
					{
						double x = std::stod(std::string(num_contents));
						//Iterating throgh the loop to find out the location of row and column entered by the user
						for (LList<LList<Cell*>>::iterator I = rows.begin(); I != rows.end(); ++I)
						{
							h++;
							w = 0;							
							for (LList<Cell*>::iterator J = (*I).begin(); J != (*I).end(); ++J)
							{							
								w++;
								if (h == r && w == c)
								{									
									delete *J;
									//Value of iterator J is assigned with the new value returned by numeric cell
									*J = new numericCell(x);
								}//if loop
							}//for loop1
						}//for loop2
					}
					catch (exception e)
					{
						std::cout << "Error: Bad input for set number\n";						
					}
				}//if loop
				else if (type == "string")
				{					
					int h = 0;
					int w = 0;					
					//Setting the value at the location provided by the user
					//iterating through the loop to find out row and column location provided by the user
					for (LList<LList<Cell*>>::iterator I = rows.begin(); I != rows.end(); ++I)
					{
						h++;
						w = 0;						
						for (LList<Cell*>::iterator J = (*I).begin(); J != (*I).end(); ++J)
						{						
							w++;
							if (h == r && w == c)
							{							
								delete *J;
								//Getting the entire line from the user
								std::string contents_string;
								std::getline(ss, contents_string);
								if (contents_string.empty())
								{
									//No string input
									//return 1;
								}
								else
								{
									//value at the iterator J will be assigned the value retturned from nonnumericcell
									*J = new nonnumericCell(contents_string);
								}
							}//if loop
						}//first for loop
					}//second for loop
				}//string else if*/
			
				else if (type == "mean" || "min" || "max")
				{
					//defining the values to pass to functionCells
					std::string type1;
					type1 = type;
					std::string inR;
					std::string offset;
					std::string fiR;
					ss >> inR;
					ss >> offset;
					ss >> fiR;
					
					//Catching the exception,if the values given by the user are non numeric
					try
					{
						int inR1 = stoi(std::string(inR));
						int offset1 = stoi(std::string(offset));
						int fiR1 = stoi(std::string(fiR));
						if ((inR1 < 0 || inR1>height - 1) || (offset1 < 0 || offset1>height - 1) || (fiR1<0 || fiR1>height - 1))
						{
							std::cout << "Error: Bad function cell\n";
						}
						FunctionCells(type1, inR1, offset1, fiR1, rows);
					}
					catch (exception e)
					{
						std::cout << "Error: Bad input for function cells\n";
					}				
				}//else if of type min,max and mean				
				else
				{
					std::cout << type;
					std::cout << "Error: Unknown command";
					return 1;
				}//else statement for string-if it is other than min,max or mean 
			
			}//First try loop
			catch (exception e){
				cout << "Error: cell out of range\n";
			}			
		}//set command else if
		else if (command == "addrow")
		{
			int row1;
			ss >> row1;
			if (row1 > height - 1 || row1 < 0)
			{
				std::cout << "Error: row out of range\n";
				
			}
            //Iterating through loop to find out the given row,before which to add
			LList<LList<Cell*>>::iterator I = rows.begin();
			for (int i = 0; i != row1; i++){
				++I;
				
			}
			LList<Cell*> newRow;
			//Using insert function and passing the row to add
			I = rows.insert(I, newRow, row1);			
			for (int j = 0; j < width; j++) {
				(*I).push_back(new Cell());				
			}
		}
		else if (command == "removerow")
		{
			//Taking the number of row to remove from user
			int num;
			ss >> num;
			//int num1 = num + 1;
			if (num>height - 1 || num < 0)
			{
				std::cout << "Error: row out of range\n";
				//return 1;
			}
			//iterating through the loop to find out the given row to remove
			LList<LList<Cell*>>::iterator I = rows.begin();
			for (int i = 0; i < height; i++, I++)
			{
				LList<Cell*>::iterator J = (*I).begin();
				//Finding the row and erasing it
				if (i == num){
					I = rows.erase(I, num, height);
					height--;
				}
			}		
		}//else if of removerow
		else if (command == "quit")
		{
			return 0;
		}
		else{
			cout << "Error: unknown command\n";			
		}
	}// while loop

}// main