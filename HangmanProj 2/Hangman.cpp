//Jonathan Goins - 1300 final project
//hangman game, P v CPU , stores games in leaderboard
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <math.h>
#include <time.h>
#include <vector>
#include <sstream>
#include <cstddef>
#include <cmath>
#include <chrono> 
using namespace std;
void displayMenu(){
  cout << "\n=====Menu=====" << endl;
  cout <<  "1. P1 vs CPU" << endl;
  cout << "2. LeaderBoard" << endl;                 // displaying menu
  cout <<  "3. Quit\n" << endl;
}

string displayHint(string &cpword, string &blank)   // passing CPU generated word and "___" by reference
{
    string Hline;           // line of cpu_Gen.txt
		string lilHint;         // holds hint from cpu_gen.txt
    int j = 0;              // to go through line
    vector<string> numLines;        // vector for random word/hint
    srand(time(NULL));
    ifstream file("cpu_Gen.txt");
    int total_lines = 0;    // holds number of random words/hints
        while(getline(file,Hline))      // loops through .txt
        {
    			total_lines++;            //counts lines
    			numLines.push_back(Hline); // stores .txt lines in vector
    		}                             //generate a random number between 0 and count of total lines in cpu gen . txt
    int random_number=rand()%total_lines;       //fetch the line where line index (starting from 0) matches with the random number
    stringstream ss(numLines[random_number]); //  reads random line
    getline(ss, cpword, ','); //  for first word up to , in cpword
    getline(ss, lilHint);     // the rest in hint
          while(getline(file,numLines[random_number])){
                stringstream ss(numLines[random_number]);     // looping through line
                getline(ss, cpword, ',');
                getline(ss, lilHint);
                }
		cout << "\n******HINT*******\n" << lilHint << endl; // prints hint
          while(j < cpword.length()){
                blank = blank + "_";      // uses j to fill blank with appropriate amount of Underscores
                j++;
                }
    cout << "WORD: " << blank << endl;     // prints underscores
  return cpword;
}

 int guesshWord(string &hWord,string &blank, string &cpword, int &maxGuess)
 {
   bool isCorrect = false;
   if (hWord == cpword){      // if user guess the whole word correct set bool true
     cout << "\nCongrats, you won! Check out your spot in the leaderboard.";
     isCorrect = true;
   }
   else{
     maxGuess = maxGuess - 1;    // wrong take of point from maxGuess
     cout << "Wrong, you have " << maxGuess << " more attempts."<< endl;
     cout << "WORD: " << blank << endl;
   }
   return isCorrect;
}
string guessChar(char &guess, string &cpword, int &maxGuess, string &blank)
{
  bool isThere = false;
  for (int i = 0;i < cpword.length();i++){
          if(guess == cpword.at(i)){       // loops through the length of cpword and if user guess is correct is there true
            blank[i] = guess;           // sets blank at position i to char guessed
            isThere = true;
            }
      }
  if (isThere == true){
    cout << "Correct!" << endl;                   // if bool true prints appropriate letter
    cout << "WORD: " << blank << endl;
  }
  else{
    maxGuess = maxGuess - 1;           // wrong, take of point from maxGuess
    cout << "Wrong, you have " << maxGuess << " more attempts."<< endl;
    cout << "WORD: " << blank << endl;
  }
  return blank;
}

void leaderboardChange(string name, double time)
{
  string line = "";
  fstream myFileStream;
  myFileStream.open("leaderboard.txt",ios::out|ios::app);
  if(myFileStream.is_open())            // output and append
  {
    myFileStream << name << ", " << time << endl;     // writing to file
  }
  else
  {
    cout << "Failed to open the file." << endl;
  }
  myFileStream.close();
}
void leaderboardView()      // view leaderboard
{
  string line = "";
  ifstream myFileStream;
  myFileStream.open("leaderboard.txt");
  if(myFileStream.is_open())
  {
    while(getline(myFileStream,line)){      // prints lines in leaderboard
      cout << line << endl;
    }
  }
  else
  {
    cout << "Failed to open the file." << endl;
  }
  myFileStream.close();
}
int main()
{
  int retMenu;
  double totalTime = 0;
  string leadRead = "";          // sets line holder to empty
  fstream filestream; // file intitilization
  string cpword = "";   // computer generated word
  string blank = "";    // Underscores @ .length of CPU word
  int maxGuess = 6;     // max number of guesses
  char guess;           // letter user guessed
  string User = "";          // User in leaderboard
  string Wword = "";        //would you like to guess whole word
  string hWord = "";        // whole word guess
      int choice = 0;          //"1,2,3" for menu options
      while(choice != 3){     // while user is in menu
          displayMenu();        //displaying menu
          cin >> choice;

            switch (choice){       // switch stament for menu options

                                  // if User chooses to play CPU
                    case 1:

                          cout << "Enter User: ";
                          cin >> User;                    //gets User from user
                          //runtime(User,hWord,cpword,maxGuess,endT);
                          cout << cpword << " " << blank << endl;
                          displayHint(cpword, blank);       // displays hint as well as "_ _ _ _"

                                while (maxGuess != 0 && hWord != cpword)
                                {       // while x amount of attempts left is valid and user has not guessed the whole word correct
                               clock_t startTime = clock();
                                //start time
                                  cout << "\nWould you like to guess the whole word? (y/n): ";
                                  cin >> Wword;
                                  if(Wword == "y")
                                  {                   //if guessing whole word
                                      cout << "\nEnter Your Guess: ";
                                      cin >> hWord;                      // gets word from user
                                      bool guessCorrect = guesshWord(hWord, blank, cpword, maxGuess); // sets guesscorrect to guesshword
                                          if(guessCorrect == true)
                                          {
                                            //end time
                                              clock_t endTime = clock();
                                              totalTime = (endTime - startTime)*.09;
                                              cout << "\nTime taken by program is : " << fixed << totalTime << setprecision(-1);
                                              cout << " sec " << endl;
                                              leaderboardChange(User, totalTime);
                                              blank = "";
                                              maxGuess = 6;                                                                          // YOU WON!
                                            break;
                                          }
                                  }
                                  else if(Wword == "n"){            // guessing character
                                    cout << "Guess a Character: ";
                                    cin >> guess;      // gets character from user
                                    guessChar(guess, cpword, maxGuess, blank); //calling function to guess a character
                                    if(blank == cpword){
                                       cout << "\nCongrats, you won! Check out your spot in the leaderboard.";
                                      clock_t endTime = clock();
                                              totalTime = (endTime - startTime)*.09;
                                              cout << "\nTime taken by program is : " << fixed << totalTime << setprecision(-1);
                                              cout << " sec " << endl;
                                              leaderboardChange(User, totalTime);
                                              blank = "";
                                              maxGuess = 6;
                                      break; // you won!
                                    }
                                  }
                                  else{   // did not enter a valid input
                                    cout << "\nInvalid input, please enter either 'y' or 'n'."<< endl;
                                  }
                                }
                                blank = "";
                                if(maxGuess == 0)
                                {
                                  cout << "Too many attempts please try again" << endl;
                                }
                                maxGuess = 6;
                                break;
                    case 2:
                            leaderboardView();
                            break;
                  case 3:
                    cout << "Goodbye!" << endl;
                    break;
                  default:
                  cout << "****Invalid input****\n - Would you like to leave? Enter '3'! -" << endl;      // did not enter a valid menu option
                  break;
}
}
}
