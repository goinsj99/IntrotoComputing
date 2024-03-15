#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cctype>
#include <cstdio>
#include <string.h>
#include <fstream>
#include <sstream>
#include<cstdlib>
using namespace std;
const int maxl = 2000.0;
// A program that reads a txt file and computes-- 
//The number of lines in the file
//The most expensive product
//The least expensive product
void setNameAndPrice(string line,string &z,float &v)
{
   z=""; // product
   string priz=""; // price 
   int lev=0; // initializes when to add to which string
   for(int i=0;i<line.length();i++) // loop to iterate through the line
   {
       char ch=line.at(i); // current character in the line
       if(ch==',') // if current character is a comma.. 
       {
           lev++;
           z+="\0"; //signals the end of string
           continue;
       }
       if(lev==0) // if current spots a letter of a prodcut..
       {
           z+=ch; // adds characacters to string
       }
       if(lev==1 && ch!=' ') // if the current spot is a number value and not space...
       {
           priz+=ch; // adding the digit the double string
       }
   }
   priz+='\0'; // signal end of string
   v=atof(priz.c_str()); // changes price string into double
}

int main()
{
   string name[200]; // string array of products
   float pri[200]; // float array of product prices
   float max=0; // most expensive product
   int min = maxl; // cheapest product
   int imax=0; //    Index of Max 
   int imin=0;//                & Min 
   int size=0; // line size
   cout<<"Enter the file name: " << endl;
   string fileName;         // input from user to open file
   cin>>fileName;
   ifstream infile; // initializes file channel
   infile.open(fileName); // opens file with user input
   if(infile.fail()) // if user input is out of bounds..
   {        
       cout << "Could not open file.";
   }
   else     
   {        
       string line; // int. for file lines
       while(getline(infile,line)) // gets lines from file and reads it into line
       {
           if(line!="") // if line is not empty..
           {
               setNameAndPrice(line,name[size],pri[size]); // runs the line, string array, and float array
                                                            // through the function and returns the product string as double and name string
               if(max < pri[size]) // Checks if max...
               {
                   max=pri[size]; // sets max to current element
                   imax=size; // saves max index for print
               }
              
               if(min > pri[size]) // Checks if min...
               {
                   min = pri[size]; // sets min to current element
                   imin = size; // saves min index for print
               }
               size++;
           }
       }
       cout<<"The number of lines: "<<size; // prints the number of lines in the file if so
       cout<<"\nThe most expensive product: "<< name[imax]; // prints the most expensive product if so
       cout<<"\nThe least expensive product: "<< name[imin]; // prints the cheapest product if so
   }
   cout << endl;
   return 0;
}
