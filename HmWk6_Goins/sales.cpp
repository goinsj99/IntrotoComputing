#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cctype>
#include <cstdio>
#include <string.h>
#include <fstream>
#include <sstream>
#define SIZE 10
using namespace std;
//  reads the txt file and stores the names and sales in two separate arrays.
int readSales(string file, string names[], int sales[][12], int size)
{
    ifstream infile; // int. for file channel
    infile.open(file); // opens file with user input
 
    int count = 0;
    if (infile.is_open()){ // if file is open.. 
    
        string line = ""; // initializes line being read from file
        int i = 0;
        while (getline(infile, line)) // gets lines from file and reads it into line
        {
            if (count == size)
            {
                return size;
            }
            if (int(line[0]) >= 65 && int(line[0]) <= 90) // check if first character of line is a letter...
            {
                names[count] = line; // adds current line to names array
                count++; // increase number of employee count
            }
            else //if the line is numbers... 
            {
                string token; // 
                stringstream ss(line); // feeds line into string stream object
                int j = 0; 
                while (getline(ss, token, ','))
                {
                    sales[count-1][j] = stoi(token);
                    j++;
                }
            }
            
        }
             
    }
    else{
        return -1;
    }
    return count;
}

int main()
{
    // prompts user to enter file name
    cout << "Enter the file name: " << endl;
    string file; // string for user input
    cin >> file; // uses input = string

    string names[SIZE]; // string array for employee names
    int sales[SIZE][12]; // A 2D integer array with 12 columns to store sales of employees
    int numemploy = readSales(file,names, sales, SIZE); // call for function
    cout << "Returned value (number of employees): " << numemploy << endl;
    if(numemploy !=-1)
    {
        int i = 0;
        while(i < numemploy)
        {
            cout << "Name[" << i<<"] = " <<names[i]<<endl;  // iterates through array and prints name
            for(int j = 0; j < 12; j++)
            {
                cout << "sales["<<i<<"]["<<j<<"] = "<<sales[i][j]<<endl;
            }
            i++; // continues
        }
    }
    
return 0;
}
