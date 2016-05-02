/*****************************************************************************
 * Name: Lars Knutson II                                                     *
 * Date: December 9, 2015                                                    *
 * Program: Final                                                            *
 * File name: knutson_final                                                  *
 * Summary: This program plays a modified version of Battleship where the    *
 *          user places ships and only the computer tries to find them       *
 * Notes: The termcolor.hpp is copyright (c) 2013 by Igor Kalnitsky          *
 *        All rights reserved                                                *
 *        https://github.com/ikalnitsky/termcolor                            *
 *****************************************************************************/

#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<string>
#include<fstream>
#include<vector>
#include"termcolor.hpp"

using namespace std;

ofstream ofs("knutson_final.txt");

/*****************************************************************************
 * GLOBAL VARIABLES                                                          *
 *****************************************************************************/
const string NAME = "Lars Knutson II",
             DATE = "9 December 2015",
		     LABN = "Final",
             LTITLE = "Final - Battleship",    
			 COURSE = "CIS2542-001",
			 Ls = "| ", sLs = " | ", sL = " |", Cs = ", ", CLs = "; ", DOT = "-",
			 SLSH = "/", SP = " ", FATAL = "Fatal Error",
             eCONTINUE = "Press <ENTER> to continue", exitMessage = "Goodbye",
		     mainT = "Main Menu", returning = "Returning to Main Menu",
			 selectionPrompt = "Selection: ", quit = "Quit",
			 mainError = "Error. Please enter 1, 2, or 3",
			 message = "Any pizza is a personal pizza if you try hard and believe in yourself",
			 theEOF = "EOF message: ", YesNo = "(1:Yes 2:No): ",
		     YesNoError = "Please enter 1:Yes or 2:No", EQL = "=", LL = "||",
             PRD = ".", L = "|", DDDL = "---|";

const int ZERO = 0, error = -1, MENU_DASH = 39,
		  MENU_LINE_T = 35, MENU_LINE = 30,
		  menu1 = 1, menu2 = 2, menu3 = 3, menu4 = 4, menu5 = 5, menu6 = 6,
		  menu7 = 7, menu8 = 8, menu9 = 9, menu0 = 0,
		  choice1 = 1, choice2 = 2, choice3 = 3, choice4 = 4, choice5 = 5,
		  choice6 = 6, choice7 = 7, choice8 = 8, choice9 = 9, choice0 = 0,
		  check1 = 1, check2 = 2, check3 = 3, check4 = 4, check5 = 5,
		  check6 = 6, check7 = 7, check8 = 8, check9 = 9, check0 = 0,
		  ROWS = 10, COLS = 10, NUMBOATS = 7;

int menuSelection, menuChoice, linelength, DASH = 80, LINE = 76, 
	secondTest, minVal, maxVal,
	check1min = 1, check1max = 3, check2min = 1, check2max = 2, 
	aNum, YN, No = 2, check3min = 1, check3max = 7, check4min = 1,
    check4max = 4, check5min = 5, check5max = 20, shipChoice,
	posx, posy, directionChoice;

string theHeader, theFooter, lineOne, menuInput, test2, 
	   menuMain1 = "Play game", menuMain2 = "See Rules", shipInput,
	   spotInput, directionInput;

bool again = true, oncemore = true, placeleft, placeup, placedown, placeright;


/*****************************************************************************
 * FUNCTION PROTOTYPE                                                        *
 *****************************************************************************/
void titlescreen();
void hdr();
void ftr();
void eof();
void dash(int);
void cdash(int);
int checkInput(string, int);
int mainMenu();
void menuReturn();
void quitter();
void fatal();
void lab();
void battleship();
void rules();
void cgrid();
int getx(char);
int gety(char);
int difficultyChoice();
void blankline();


/*****************************************************************************
 * STRUCTURES                                                                *
 *****************************************************************************/
struct ship
{

	char title;
	int size;
	bool sunk;
	int hits;
	bool placed;
	string name;

};//stuct ship

struct space
{

	bool open;
	bool occupied;
	ship* vessal;
	bool goodup;
	bool goodleft;
	bool gooddown;
	bool goodright;

};//struct space

struct moves
{

	string location;
	bool ahit;
	bool shipsunk;

};//struct moves

struct coordinates
{

	int xordinate;
	int yordinate;

};//struct impossible


/*****************************************************************************
 * CLASSES                                                                   *
 *****************************************************************************/
class Game
{

	private:
		ship Boats[NUMBOATS];
		space tile[ROWS][COLS];
		vector<moves> guesses;
		vector<coordinates> storeguesses;
		int sunkcount;
		int openspots;

	public:
		Game();
		void setboard();
		void playgameEasy();
		void playgameNormal();
		void playgameImpossible();
		void recordguess(int, int, bool);
		void seekanddestroy(int, int);
		void displayboard();
		void goup(int, int, int);
		void godown(int, int);
		void godown(int, int, int);
		void goleft(int, int, int);
		void goright(int, int);
		void goright(int, int, int);
		//void cdisplayboard();
		void setupship();
		void setupspot();
		void setupdirection();
		void displayguess();

};//class Game


/*****************************************************************************
 * This vector stores all rounds of the game                                 * 
 *****************************************************************************/
vector<Game> thegame;


/*****************************************************************************
 * MAIN FUNCTION                                                             *
 *****************************************************************************/
int main()
{
	titlescreen();

	lab();

	return 0;

}//main()


/*****************************************************************************
 * This function is the main gateway for the program                         *
 *****************************************************************************/
void lab()
{
	int difficulty;

	do
	{

		menuChoice = mainMenu();

		switch(menuChoice)
		{
			case choice1:
				battleship();
				break;
			case choice2:
				rules();
				break;
			case choice3:
				quitter();
				break;
			default:
				fatal();
				break;
		}

	}while(again);

}//lab()


/*****************************************************************************
 * This function plays the modified game of battle ship                      *
 *****************************************************************************/
void battleship()
{

	int position, YesNoAgain, YesNoDiff, difficulty;

	string YesNoAgainInput, YesNoDiffInput;

	do
	{

		thegame.push_back(Game());	

		position = thegame.size() - 1;

		difficulty = difficultyChoice();

		thegame[position].setboard();

		switch(difficulty)
		{
			case choice1:
				thegame[position].playgameEasy();
				break;
			case choice2:
				thegame[position].playgameNormal();
				break;
			case choice3:
				thegame[position].playgameImpossible();
				break;
			default:
				fatal();
				break;
		}

		do
		{

			cout << endl;
			cout << "Play again?" << endl;
			cout << YesNo;
			getline(cin, YesNoAgainInput);

			YesNoAgain = checkInput(YesNoAgainInput, check2);

			if(YesNoAgain == error)
			{
				cout << YesNoError << endl;
				cout << eCONTINUE;
				cin.get();
			}

		}while(YesNoAgain == error);

		if(YesNoAgain == 2)
			oncemore = false;
	
	}while(oncemore);

	menuReturn();

}//battleship()


/*****************************************************************************
 * This function produces the title screen                                   * 
 *****************************************************************************/
void titlescreen()
{
	string temp;

	vector<string> theTitle;

	ifstream inputFile;

	inputFile.open("knutson_final_title.txt");

	for(int i = 0; i < 28; i++)
	{
		getline(inputFile, temp);

		theTitle.push_back(temp);
	}

	inputFile.close();

	for(int j = 0; j < theTitle.size(); j++)
	{
		if(j != (theTitle.size() - 1))
			cout << theTitle[j] << endl;
		else
			cout << theTitle[j];
	}

	cin.get();
		
}//titlescreen()


/*****************************************************************************
 * This function displays the rules of the game                              *
 *****************************************************************************/
void rules()
{
	string temp;

	vector<string> theRules;

	ifstream inputFile;

	if(theRules.empty())
	{
		inputFile.open("knutson_final_rules.txt");

		for(int i = 0; i < 28; i++)
		{
			getline(inputFile, temp);

			theRules.push_back(temp);
		}

		inputFile.close();
	}

	for(int j = 0; j < theRules.size(); j++)
	{
		if(j != (theRules.size() - 1))
			cout << theRules[j] << endl;
		else
			cout << theRules[j];
	}

	cin.get();

}//rules()


/*****************************************************************************
 * This function produces part of the game grid to the console               *
 *****************************************************************************/
void cgrid()
{

	cout << LL << setw(2) << SP << DOT << L;

	for(int i = 0; i < 10; i++)
		cout << DDDL;

}//cgrid()


/*****************************************************************************
 * This function checks the x coordinate in placement                        *
 *****************************************************************************/
int getx(char letter)
{

	switch(toupper(letter))
	{
		case 'A':
			return 0;
			break;
		case 'B':
			return 1;
			break;
		case 'C':
			return 2;
			break;
		case 'D':
			return 3;
			break;
		case 'E':
			return 4;
			break;
		case 'F':
			return 5;
			break;
		case 'G':
			return 6;
			break;
		case 'H':
			return 7;
			break;
		case 'I':
			return 8;
			break;
		case 'J':
			return 9;
			break;
		default:
			return error;
			break;
	}
	
}//posx()


/*****************************************************************************
 * This function checks the y coordinate in placement                        *
 *****************************************************************************/
int gety(char ynumber)
{

	switch(ynumber)
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return ynumber - '0';
			break;
		default:
			return error;
			break;
	}

}//posy()


/*****************************************************************************
 * This function produces a blank line to the console                        *
 *****************************************************************************/
void blankline()
{
	cout << LL;
	
	for(int i = 0; i < 76; i++)
		cout << SP;

	cout << LL;

}//blankline()


/*****************************************************************************
 * This function produces a dashed line of the passed length to the file     *
 *****************************************************************************/
void dash(int repeat)
{

	for(int i = ZERO; i < repeat; i++)
		ofs << EQL;

}//dash()


/*****************************************************************************
 * This function produces a dashed line of the passed length to the console  *
 *****************************************************************************/
void cdash(int repeat)
{

	for(int i = ZERO; i < repeat; i++)
		cout << EQL;

}//cdash()


/*****************************************************************************
 * This function checks the users selection from a menu                      *
 *****************************************************************************/
int checkInput(string test, int whichTest)
{
	//set mins and maxs
	switch(whichTest)
	{
		case check1:
			minVal = check1min;
			maxVal = check1max;
			break;
		case check2:
			minVal = check2min;
			maxVal = check2max;
			break;
		case check3:
			minVal = check3min;
			maxVal = check3max;
			break;
		case check4:
			minVal = check4min;
			maxVal = check4max;
			break;
		case check5:
			minVal = check5min;
			maxVal = check5max;
			break;
		default:
			fatal();
			break;
	}

	//test to make sure input
	if(test.length() == ZERO)
		return error;

	//convert to int
	secondTest = atoi(test.c_str());

	//check within range
	if(secondTest < minVal || secondTest > maxVal)
		return error;

	//convert new int to string
	test2 = to_string(secondTest);

	//make sure incoming string length matches new string
	if(test.length() != test2.length())
		return error;
	else
		return secondTest;
	
}//checkInput()


/*****************************************************************************
 * This function produces the header                                         *
 *****************************************************************************/
void hdr()
{

	//sets the header message
	theHeader = LTITLE + SP + COURSE;

	dash(DASH);
	ofs << Ls << setw(LINE) << left << theHeader << sL << endl;
	dash(DASH);

}//hdr()


/*****************************************************************************
 * This function produces a main menu and only returns valid selection       *
 *****************************************************************************/
int mainMenu()
{
	int count = 0;

	do
	{
		//produces menu
		cdash(80);
		cout << endl;

		for(int i = 0; i < 7; i++)
		{
			blankline();
			cout << endl;
		}

		cout << LL << setw(31) << SP;
		cdash(14);
		cout << setw(31) << SP << LL << endl;

		cout << LL << setw(33) << SP << mainT << setw(34) << SP << LL << endl;

		cout << LL << setw(31) << SP;
		cdash(14);
		cout << setw(31) << SP << LL << endl;

		cout << LL << setw(32) << SP << menu1 << PRD << SP << menuMain1
			 << setw(32) << SP << LL << endl;
		cout << LL << setw(32) << SP << menu2 << PRD << SP << menuMain2
			 << setw(32) << SP << LL << endl;
		cout << LL << setw(32) << SP << menu3 << PRD << SP << quit     
			 << setw(37) << SP << LL << endl;

		cout << LL << setw(31) << SP;
		cdash(14);
		cout << setw(31) << SP << LL << endl;

		if(count > ZERO)
		{
			cout << LL  << setw(23) << SP << mainError
                 << setw(23) << SP << LL << endl;
			cout << LL << setw(31) << SP;
			cdash(14);
			cout << setw(31) << SP << LL << endl;

			for(int j = 0; j < 9; j++)
			{
				blankline();
				cout << endl;
			}
		}
		else
		{
			cout << LL << setw(31) << SP;
			cdash(14);
			cout << setw(31) << SP << LL << endl;

			for(int j = 0; j < 10; j++)
			{
				blankline();
				cout << endl;
			}
		}

		cdash(80);

		cout << endl;

		cout << setw(2) << SP  << selectionPrompt;
		getline(cin, menuInput);

		//checks to make sure input good
		menuSelection = checkInput(menuInput, check1);

		//if input not good produce error
		if(menuSelection == error)
		{
			count++;
		}

	}while(menuSelection == error);

	count = ZERO;

	return menuSelection;

}//mainMenu()


/*****************************************************************************
 * This function produces the difficulty menu and only returns valid choice  *
 *****************************************************************************/
int difficultyChoice()
{
	int difficultySelection, count = 0;

	string difficultyInput, difficultyT = "Difficulty", 
           easyT = "Easy Mode", easy1 = "Computer gets 5 guesses a turn",
	       easy2 = "You pick how many turns it gets",
		   normalT = "Normal Mode",
		   normal1 = "Computer gets 1 guess a turn",
		   normal2 = "BUT not all gueeses are random",
		   impossibleT = "Impossible Mode",
		   impossible1 = "You will not win.";
	
	do
	{
		//produces menu
		cdash(80);
		cout << endl;

		for(int i = 0; i < 5; i ++)
		{
			blankline();
			cout << endl;
		}

		cout << LL << setw(21) << SP;
		cdash(34);
		cout << setw(21) << SP << LL << endl;

		cout << LL << setw(33) << SP << difficultyT
             << setw(33) << SP << LL << endl;

		cout << LL << setw(21) << SP;
		cdash(34);
		cout << setw(21) << SP << LL << endl;

		cout << LL << setw(21) << SP << menu1 << PRD << SP << easyT
             << setw(43) << SP << LL << endl;
		cout << LL << setw(24) << SP << easy1 << setw(22) << SP << LL << endl;
		cout << LL << setw(24) << SP << easy2 << setw(21) << SP << LL << endl;
		cout << LL << setw(21) << SP << menu2 << PRD << SP << normalT
             << setw(41) << SP << LL << endl;
		cout << LL << setw(24) << SP << normal1 << setw(24) << SP << LL << endl;
		cout << LL << setw(24) << SP << normal2 << setw(22) << SP << LL << endl;
		cout << LL << setw(21) << SP << menu3 << PRD << SP << impossibleT
             << setw(37) << SP << LL << endl;
		cout << LL << setw(24) << SP << impossible1
             << setw(35) << SP << LL << endl;

		cout << LL << setw(21) << SP;
		cdash(34);
		cout << setw(21) << SP << LL << endl;

		if(count != ZERO)
		{
			cout << LL  << setw(23) << SP << mainError
                 << setw(23) << SP << LL << endl;	

			cout << LL << setw(21) << SP;
			cdash(34);
			cout << setw(21) << SP << LL << endl;

			for(int j = 0; j < 6; j++)
			{
				blankline();

				cout << endl;
			}
		}
		else
		{
			cout << LL << setw(21) << SP;
			cdash(34);
			cout << setw(21) << SP << LL << endl;

			for(int k = 0; k < 7; k++)
			{
				blankline();

				cout << endl;
			}
		}

		cdash(80);
		cout << endl;

		cout << setw(2) << SP  << selectionPrompt;
		getline(cin, difficultyInput);

		//checks to make sure input good
		difficultySelection = checkInput(difficultyInput, check1);

		//if input not good produce error
		if(difficultySelection == error)
		{
			count++;
		}

	}while(difficultySelection == error);

	count = ZERO;

	return difficultySelection;

}//difficultyMenu()


/*****************************************************************************
 * This function prompts a return to the main menu                           *
 *****************************************************************************/
void menuReturn()
{

	cout << endl;
	cout << returning;
	cout << eCONTINUE;
	cin.get();

}//menuReturn()


/*****************************************************************************
 * This function exits the program and calls the footer and eof and exit     *
 * message                                                                   *
 *****************************************************************************/
void quitter()
{

	string temp;

	vector<string> theExit;

	ifstream inputFile;

	inputFile.open("knutson_final_exit.txt");

	for(int i = 0; i < 28; i++)	
	{
		getline(inputFile, temp);

		theExit.push_back(temp);
	}

	inputFile.close();

	again = false;
	
	ftr();

	eof();

	for(int j = 0; j < theExit.size(); j++)
		cout << theExit[j] << endl;

}//quitter()


/*****************************************************************************
 * This function produces the fatal error message                            *
 *****************************************************************************/
void fatal()
{

	cout << endl;
	cout << FATAL << endl;
	cout << eCONTINUE;
	cin.get();

}//fatal()


/*****************************************************************************
 * This function produces the footer                                         *
 *****************************************************************************/
void ftr()
{

	//sets the footer line
	theFooter = NAME + CLs + DATE + CLs + LABN + CLs + COURSE;

	dash(DASH);
	ofs << Ls << setw(LINE) << left << theFooter << sL << endl;
	dash(DASH);

}//ftr()


/*****************************************************************************
 * This function produces the end of file message                            *
 *****************************************************************************/
void eof()
{

	//sets the eof top line
	lineOne = theEOF + NAME + Cs + DATE + Cs + LTITLE + Cs + LABN;

	dash(DASH);
	ofs << Ls << left << setw(LINE) << lineOne << sL << endl;
	ofs << Ls << left << setw(LINE) << message << sL << endl; 
	dash(DASH);

}//eof()


/*****************************************************************************
 *  CLASS FUNCTIONS * CLASS FUNCTIONS * CLASS FUNCTIONS * CLASS FUNCTIONS    * 
 *****************************************************************************/
/*****************************************************************************
 * This function sets the inital board state of the game                     * 
 *****************************************************************************/
Game::Game()
{

	Boats[0].title = 'A';
	Boats[0].size = 5;
	Boats[0].sunk = false;
	Boats[0].hits = 0;
	Boats[0].placed = false;
	Boats[0].name = "Aircraft Carrier";

	Boats[1].title = 'B';
	Boats[1].size = 4;
	Boats[1].sunk = false;
	Boats[1].hits = 0;
	Boats[1].placed = false;
	Boats[1].name = "Battleship";      

	Boats[2].title = 'C';
	Boats[2].size = 3;
	Boats[2].sunk = false;
	Boats[2].hits = 0;
	Boats[2].placed = false;
	Boats[2].name = "Cruiser";         

	Boats[3].title = 'D';
	Boats[3].size = 2;
	Boats[3].sunk = false;
	Boats[3].hits = 0;
	Boats[3].placed = false;
	Boats[3].name = "Destroyer";

 	Boats[4].title = 'D';
	Boats[4].size = 2;
	Boats[4].sunk = false;
	Boats[4].hits = 0;
	Boats[4].placed = false;
	Boats[4].name = "Destroyer";

 	Boats[5].title = 'S';
	Boats[5].size = 1;
	Boats[5].sunk = false;
	Boats[5].hits = 0;
	Boats[5].placed = false;
	Boats[5].name = "Sub";

 	Boats[6].title = 'S';
	Boats[6].size = 1;
	Boats[6].sunk = false;
	Boats[6].hits = 0;
	Boats[6].placed = false;
	Boats[6].name = "Sub";

	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			tile[i][j].open = true;
			tile[i][j].occupied = false;
			tile[i][j].vessal = NULL;
			tile[i][j].goodup = false;
			tile[i][j].goodleft = false;
			tile[i][j].gooddown = false;
			tile[i][j].goodright = false;
		}
	}
	
	sunkcount = 0;
	openspots = 82;

}//Game::Game()


/*****************************************************************************
 * This function set pieces on the board                                     * 
 *****************************************************************************/
void Game::setboard()
{
	int placedcount = 0;

	do
	{
		//pick a ship to place
		setupship();

		//pick a spot to place ship
		setupspot();

		tile[posy][posx].occupied = true;
		tile[posy][posx].vessal = &Boats[shipChoice];

		//if ship is not a sub pick direction
		if(shipChoice < 5)
		{
			setupdirection();

			//places the non-sub ships on the board
			switch(directionChoice)
			{
				case 1:
					for(int y = 1; y < Boats[shipChoice].size; y++)
					{
						tile[(posy - y)][posx].occupied = true;
						tile[(posy - y)][posx].vessal = &Boats[shipChoice];
					}
					break;
				case 2:
					for(int x = 1; x < Boats[shipChoice].size; x++)
					{
						tile[posy][(posx - x)].occupied = true;
						tile[posy][(posx - x)].vessal = &Boats[shipChoice];
					}
					break;
				case 3:
					for(int y = 1; y < Boats[shipChoice].size; y++)
					{
						tile[posy + y][posx].occupied = true;
						tile[posy + y][posx].vessal = &Boats[shipChoice];
					}
					break;
				case 4:
					for(int x = 1; x < Boats[shipChoice].size; x++)
					{
						tile[posy][(posx + x)].occupied = true;
						tile[posy][(posx + x)].vessal = &Boats[shipChoice];
					}
					break;
				default:
					fatal();
					break;
			}
		}
		
		Boats[shipChoice].placed = true;	
		placedcount++;
		
		for(int i = 0; i < COLS; i++)
		{
			for(int j = 0; j <ROWS; j++)
			{
				tile[i][j].goodup = false;
				tile[i][j].goodleft = false;
				tile[i][j].gooddown = false;
				tile[i][j].goodright = false;
			}
		}

	}while(placedcount != 7); 

}//Game::setboard()


/*****************************************************************************
 * This function plays the game normally                                     *
 * The computer will guess one space at a time but will seek and destroy a   *
 * if it gets a hit                                                          =
 *****************************************************************************/
void Game::playgameNormal()
{

	bool keepgoing = true, valid = false;

	unsigned seed = time(0);

	int guessx, guessy, initalize, maxValue = 9, minValue = 0;

	srand(seed);

	initalize = (rand() % (maxValue - minValue + 1)) + minValue;

	do
	{

		do
		{

			guessx = (rand() % (maxValue - minValue + 1)) + minValue;

			guessy = (rand() % (maxValue - minValue + 1)) + minValue;

			if(tile[guessy][guessx].open)		
				valid = true;

		}while(!valid);

		if(!tile[guessy][guessx].occupied)
		{
			tile[guessy][guessx].open = false;
			openspots--; 

			recordguess(guessx, guessy, false);

			if(openspots == 0) 
				keepgoing = false;
		}
		else
		{
			tile[guessy][guessx].open = false;

			tile[guessy][guessx].vessal->hits++;

			if(tile[guessy][guessx].vessal->hits == tile[guessy][guessx].vessal->size)
			{
				tile[guessy][guessx].vessal->sunk = true;

				recordguess(guessx, guessy, true);

				sunkcount++;

				if(sunkcount == 7)
					keepgoing = false;
			}
			else
			{
				recordguess(guessx, guessy, false);

				seekanddestroy(guessx, guessy);

				if(sunkcount == 7 || openspots == 0)
					keepgoing = false;
			}			

		}

		valid = false;

	}while(keepgoing);

}//Game::playgame()


/*****************************************************************************
 * If there was a hit this function seeks out the ship                       * 
 *****************************************************************************/
void Game::seekanddestroy(int guessx, int guessy)
{

	//try up
	if(guessy - 1 >= 0)
	{	
		//if the tile above is open and not occupied
		if(tile[(guessy - 1)][guessx].open && !tile[(guessy - 1)][guessx].occupied)
		{
			//set the space to not open and reduce remaining open spots
			tile[(guessy - 1)][guessx].open = false;
			openspots--; 

			//record miss
			recordguess(guessx, (guessy - 1), false);

			//if no more open spots end game
			if(openspots == 0) 
				return;
		}
		//if the tile is open and occupied
		else if(tile[(guessy - 1)][guessx].open && tile[(guessy - 1)][guessx].occupied)
		{
			//set space to not open and mark hit on vessal
			tile[(guessy - 1)][guessx].open = false;
			tile[(guessy - 1)][guessx].vessal->hits++;

			//if the hit count on the vessal equals it size
			if(tile[(guessy - 1)][guessx].vessal->hits == tile[(guessy - 1)][guessx].vessal->size)
			{
				//record sunk ship
				tile[(guessy - 1)][guessx].vessal->sunk = true;
				sunkcount++;

				//record guess and sunk ship
				recordguess(guessx, (guessy - 1), true);
			
				//if the sunk count equals seven all ships hit
				if(sunkcount == 7)
					return;
			}
			//if the space was a hit but did not sink ship
			else
			{
				//record the guess and begin going up
				recordguess(guessx, guessy, false);
				goup(guessx, guessy, (guessy - 1));
				return;
			}
		}
	}

	//try left
	if(guessx - 1 >= 0)
	{
		//if the space is open and not occupied
		if(tile[guessy][(guessx - 1)].open && !tile[guessy][(guessx - 1)].occupied)
		{
			//set space to not open and reduce open spots by one	
			tile[guessy][(guessx - 1)].open = false;
			openspots--; 

			//record the guess
			recordguess((guessx - 1), guessy, false);

			//if no more open sopts return
			if(openspots == 0) 
				return;
		}
		//if the space is open and occupied
		else if(tile[guessy][(guessx - 1)].open && tile[guessy][(guessx - 1)].occupied)
		{
			//set space to not open and mark hit on vessal
			tile[guessy][(guessx - 1)].open = false;
			tile[guessy][(guessx - 1)].vessal->hits++;

			//if hits equal ship size
			if(tile[guessy][(guessx - 1)].vessal->hits == tile[guessy][(guessx - 1)].vessal->size)
			{
				//record sunk ship
				tile[guessy][(guessx - 1)].vessal->sunk = true;
				sunkcount++;

				//record guess
				recordguess((guessx - 1), guessy, true);

				//if no more ships return			
				if(sunkcount == 7)
					return;
			}
			//there was a hit but no sunk ship
			else
			{
				//record the guess
				recordguess((guessx - 1), guessy, false);

				//try left again
				goleft(guessx, guessy, (guessx - 1));
				return;
			}
		}
	}

	//try down
	if(guessy + 1 <= 9)
	{
		//if the spot is open and not occupied
		if(tile[(guessy + 1)][guessx].open && !tile[(guessy + 1)][guessx].occupied)
		{
			//mark spot not open and reduce open spots
			tile[(guessy + 1)][guessx].open = false;
			openspots--; 

			//record guess
			recordguess(guessx, (guessy + 1), false);
	
			//if no more open spots return
			if(openspots == 0) 
				return;
		}
		//if spot is open and occupied
		else if(tile[(guessy + 1)][guessx].open && tile[(guessy + 1)][guessx].occupied)
		{
			//mark spot not open and record hit on vessal
			tile[(guessy + 1)][guessx].open = false;
			tile[(guessy + 1)][guessx].vessal->hits++;

			//if hits on vessal equal size record sunk
			if(tile[(guessy + 1)][guessx].vessal->hits == tile[(guessy + 1)][guessx].vessal->size)
			{
				//change ship sunk to true and increase sunkcount
				tile[(guessy + 1)][guessx].vessal->sunk = true;
				sunkcount++;

				//record the guess
				recordguess(guessx, (guessy + 1), true);
			
				//if all ships shunk return
				if(sunkcount == 7)
					return;
			}
			//if there was a hit and not sunk
			else
			{
				//record the guess
				recordguess(guessx, (guessy + 1), false);
				
				//continue going down
				godown(guessx, guessy, (guessy + 1));
				return;
			}
		}
	}

	//try right
	if(guessx + 1 <= 9)
	{
		//if spot not open and not occupied
		if(tile[guessy][(guessx + 1)].open && !tile[guessy][(guessx + 1)].occupied)
		{
			//mark spot not open and reduce open spots
			tile[guessy][(guessx + 1)].open = false;
			openspots--; 

			//record guess
			recordguess((guessx + 1), guessy, false);

			//if openspots equal 0 return
			if(openspots == 0) 
				return;
		}
		//if spot is open and occupied
		else if(tile[guessy][(guessx + 1)].open && tile[guessy][(guessx + 1)].occupied)
		{
			//mark spot not open and record hit on vessal
			tile[guessy][(guessx + 1)].open = false;
			tile[guessy][(guessx + 1)].vessal->hits++;

			//if hits on vessal equal size
			if(tile[guessy][(guessx + 1)].vessal->hits == tile[guessy][(guessx + 1)].vessal->size)
			{
				//mark vessal sunk and increase sunk count
				tile[guessy][(guessx + 1)].vessal->sunk = true;
				sunkcount++;

				//record guess
				recordguess((guessx + 1), guessy, true);

				//if all ships sunk return			
				if(sunkcount == 7)
					return;
			}
			//if hit and ship not sunk
			else
			{
				//record guess
				recordguess((guessx + 1), guessy, false);
				
				//continue right
				goright(guessx, guessy, (guessx + 1));
				return;
			}
		}
	}

}//Game::seekanddestroy()


/*****************************************************************************
 * This function records the each guess                                      * 
 *****************************************************************************/
void Game::recordguess(int pointx, int pointy, bool sinking)
{

	int spot;

	string thetarget;

	guesses.push_back(moves());

	spot = guesses.size() - 1;	

	if(tile[pointy][pointx].occupied)
		guesses[spot].ahit = true;
	else
		guesses[spot].ahit = false;

	switch(pointx)
	{
		case 0:
			thetarget = "A" + to_string(pointy);
			break;
		case 1:
			thetarget = "B" + to_string(pointy);
			break;
		case 2:
			thetarget = "C" + to_string(pointy);
			break;
		case 3:
			thetarget = "D" + to_string(pointy);
			break;
		case 4:
			thetarget = "E" + to_string(pointy);
			break;
		case 5:
			thetarget = "F" + to_string(pointy);
			break;
		case 6:
			thetarget = "G" + to_string(pointy);
			break;
		case 7:
			thetarget = "H" + to_string(pointy);
			break;
		case 8:
			thetarget = "I" + to_string(pointy);
			break;
		case 9:
			thetarget = "J" + to_string(pointy);
			break;
		default:
			fatal();
			break;
	}

	guesses[spot].location = thetarget;

	displayguess();

}//Game::recordguess()


/*****************************************************************************
 * This function continues guess up till it hits a miss or sinks ship        * 
 *****************************************************************************/
void Game::goup(int startx, int starty, int lasty)
{

	bool tryagain = true;

	int y = lasty - 1;

	do
	{
		//if y is on board
		if(y >= 0)
		{
			//if spot open and occupied
			if(tile[y][startx].occupied && tile[y][startx].open)
			{
				//mark spot not open and increase vessal hits
				tile[y][startx].open = false;
				tile[y][startx].vessal->hits++;
	
				//if vessal hits equal size of ship
				if(tile[y][startx].vessal->hits == tile[y][startx].vessal->size)
				{
					//mark ship sunk and increase sunk count
					tile[y][startx].vessal->sunk = true;
					sunkcount++;

					//record guess
					recordguess(startx, y, true);
					
					//do not try again
					tryagain = false;
				}
				//else ship is hit and not sunk
				else
				{
					//record guess
					recordguess(startx, y, false);
				}
			}
			//if spot open but not occupied
			else if(tile[y][startx].open && !tile[y][startx].occupied)
			{
				//mark spot not open and reduce open spots
				tile[y][startx].open = false;
				openspots--;

				//record guess
				recordguess(startx, y, false);

				//go down
				godown(startx, starty);

				//do not try again
				tryagain =false;
			}
			//if spot is not open and not occupied
			else
			{
				//go down
				godown(startx, starty);

				//do not try again
				tryagain = false;
			}
		}
		//if y not on board
		else
		{
			//go down
			godown(startx, starty);

			//do not try again
			tryagain = false;
		}
		
		//go to next y up
		y--;

	}while(tryagain);		

}//Game::goup()


/*****************************************************************************
 * If the goup function misses without sinking a ship this function goes     *
 * down from the inital start point                                          *
 *****************************************************************************/
void Game::godown(int startx, int starty)
{

	bool letsdothatagain = true;

	int y = starty;

	do
	{
		//if spot on board
		if(y <= 9)
		{
			//if the spot is open and occupied
			if(tile[(y + 1)][startx].open && tile[(y + 1)][startx].occupied)
			{
				//mark spot not open and record vessal hit
				tile[(y + 1)][startx].open = false;
				tile[(y + 1)][startx].vessal->hits++;

				//if vessal hits equal vessal size
				if(tile[(y + 1)][startx].vessal->hits == tile[(y + 1)][startx].vessal->size)
				{
					//mark vessal sunk and increase sunk count
					tile[(y + 1)][startx].vessal->sunk = true;
					sunkcount++;

					//record guess
					recordguess(startx, (y + 1), true);

					//do not go again
					letsdothatagain = false;
				}
				//a hit but not sunk ship
				else
				{
					//record guess
					recordguess(startx, (y + 1), false);

					//go to next y
					y++;
				}
			}
			//if spot is open but not occupied
			else if(tile[(y + 1)][startx].open)
			{
				//mark spot not open and reduce open spots
				tile[(y + 1)][startx].open = false;
				openspots--;

				//record guess
				recordguess(startx, (y + 1), false);

				letsdothatagain = false;
			}
			//if spot not open and not occupied
			else
			{
				letsdothatagain = false;
			}
		}
		//if spot is off board
		else
		{
			letsdothatagain = false;
		}
		
	}while(letsdothatagain);

}//Game::godown(int, int)


/*****************************************************************************
 * This function continues to go down until it sinks a ship                  * 
 *****************************************************************************/
void Game::godown(int startx, int starty, int lasty)
{

	bool tryagain = true;

	int y = lasty + 1;

	do
	{
		//if y is on the board
		if(y <= 9)
		{
			//if spot is open and occupied
			if(tile[y][startx].occupied && tile[y][startx].open)
			{
				//mark spot not open and record hit on vessal
				tile[y][startx].open = false;
				tile[y][startx].vessal->hits++;

				//if the vessal hits equal vessal size
				if(tile[y][startx].vessal->hits == tile[y][startx].vessal->size)
				{
					//mark ship sunk and increase sunk count
					tile[y][startx].vessal->sunk = true;
					sunkcount++;

					//record guess
					recordguess(startx, y, true);
					
					//do not try again
					tryagain = false;
				}
				//ship is hit but not sunk
				else
				{
					//record guess
					recordguess(startx, y, false);
				}
			}
			//if spot is open and not occupied
			else if(tile[y][startx].open && !tile[y][startx].occupied)
			{
				//mark spot not open and reduce open spots
				tile[y][startx].open = false;
				openspots--;

				//record guess
				recordguess(startx, y, false);

				//do not try again
				tryagain =false;
			}
			//if spot not open
			else
			{
				//do not try again
				tryagain = false;
			}
		}
		//if spot is off the board
		else
		{
			//do not try again
			tryagain = false;
		}
		
		//go down one spot
		y++;

	}while(tryagain);		

}//Game::godown()


/*****************************************************************************
 * This function continues to go left until a miss or sunk ship              * 
 *****************************************************************************/
void Game::goleft(int startx, int starty, int lastx)
{

	bool tryagain = true;

	int x = lastx - 1;

	do
	{
		//if x is on the board
		if(x >= 0)
		{
			//if spot open and occupied
			if(tile[starty][x].occupied && tile[starty][x].open)
			{
				//set spot to not open and record vessal hit
				tile[starty][x].open = false;
				tile[starty][x].vessal->hits++;

				//if the hits equal vessal size
				if(tile[starty][x].vessal->hits == tile[starty][x].vessal->size)
				{
					//mark vessal sunk and increase sunk count
					tile[starty][x].vessal->sunk = true;
					sunkcount++;

					//record guess
					recordguess(x, starty, true);

					//do not try again					
					tryagain = false;
				}
				//if boat not sunk
				else
				{
					//record guess
					recordguess(x, starty, false);
				}
			}
			//if open and not occupied
			else if(tile[starty][x].open && !tile[starty][x].occupied)
			{
				//mark spot not open and reduce openspots
				tile[starty][x].open = false;
				openspots--;

				//record guess
				recordguess(x, starty, false);

				//go to the right
				goright(startx, starty);

				//do not try again
				tryagain =false;
			}
			//if not open
			else
			{
				//go to the right
				goright(startx, starty);

				//do not try again
				tryagain = false;
			}
		}
		//if guess not on board
		else
		{
			//go right
			goright(startx, starty);

			//do not try again
			tryagain = false;
		}
		
		//go to next spot to left
		x--;

	}while(tryagain);		

}//Game::goleft()


/*****************************************************************************
 * If the goleft function misses without sinking a ship this function goes   *
 * right from the initial start point                                        *
 *****************************************************************************/
void Game::goright(int startx, int starty)
{

	bool letsdothatagain = true;

	int x = startx;

	do
	{
		//if x is on the board
		if(x <= 9)
		{
			//if spot is open and occupied
			if(tile[starty][(x + 1)].open && tile[starty][(x + 1)].occupied)
			{
				//mark spot closed and increase vessal hit count
				tile[starty][(x + 1)].open = false;
				tile[starty][(x + 1)].vessal->hits++;

				//if vessal hit count equals vessal size
				if(tile[starty][(x + 1)].vessal->hits == tile[starty][(x + 1)].vessal->size)
				{
					//mark vessal sunk and increase sunk count
					tile[starty][(x + 1)].vessal->sunk = true;
					sunkcount++;

					//record guess
					recordguess((x + 1), starty, true);

					//stop going right
					letsdothatagain = false;
				}
				//if vessal is not sunk
				else
				{
					//record guess and increase x
					recordguess((x + 1), starty, false);
					x++;
				}
			}
			//if spot is open and not occupied
			else if(tile[starty][(x + 1)].open)
			{
				//mark spot not open and reduce open spots
				tile[starty][(x + 1)].open = false;
				openspots--;
		
				//record guess
				recordguess((x + 1), starty, false);

				letsdothatagain = false;
			}
			//if not open
			else
			{
				letsdothatagain = false;
			}
		}
		//if X is off the board
		else
		{
			letsdothatagain = false;
		}
		
	}while(letsdothatagain);

}//Game::goright(int, int)


/*****************************************************************************
 * This function goes right until it sinks a ship                            * 
 *****************************************************************************/
void Game::goright(int startx, int starty, int lastx)
{

	bool tryagain = true;

	int x = lastx + 1;

	do
	{
		//if the guess will still be on the board
		if(x <= 9)
		{
			//if the space is open and occupied
			if(tile[starty][x].occupied && tile[starty][x].open)
			{
				//mark space closed and record hit on ship
				tile[starty][x].open = false;
				tile[starty][x].vessal->hits++;
	
				//if the hits equal vessal size
				if(tile[starty][x].vessal->hits == tile[starty][x].vessal->size)
				{
					//mark vessal sunk and increase sunk count
					tile[starty][x].vessal->sunk = true;
					sunkcount++;

					//record the guess
					recordguess(x, starty, true);
					
					//no need to continue right
					tryagain = false;
				}
				//if the ship is not sunk
				else
				{
					//record the guess
					recordguess(x, starty, false);
				}
			}
			//if spot is open but not occupied
			else if(tile[starty][x].open && !tile[starty][x].occupied)
			{
				//set spot to not open and reduce open spot counter
				tile[starty][x].open = false;
				openspots--;

				//record the guess
				recordguess(x, starty, false);

				//if no more open spots return
				tryagain =false;
			}
			//if the spot is not open
			else
			{
				tryagain = false;
			}
		}
		//if the spot would be off the board
		else
		{
			tryagain = false;
		}

		//increase X to next spot
		x++;

	}while(tryagain);		

}//Game::goright()


/*****************************************************************************
 * This function displays the board portion of the prinout                   * 
 *****************************************************************************/
void Game::displayboard()
{
	int count = 0;

	ofs << endl;

	ofs << SP << SP << "A B C D E F G H I J" << endl;

	for(int i = 0; i < 10; i++)
	{
		ofs << count << SP;
		for(int j = 0; j < 10; j++)
		{
			if(tile[i][j].open && !tile[i][j].occupied)
				ofs << "*" << SP;
			else if(!tile[i][j].open && !tile[i][j].occupied)
				ofs << "/" << SP;
			else if(!tile[i][j].open && tile[i][j].occupied)
				ofs << "X" << SP;
			else
				ofs << tile[i][j].vessal->title << SP;
		}
		ofs << endl;
		count++;
	}
}//displayboard()


/*****************************************************************************
 * This function displays the board while placing ships                      * 
 *****************************************************************************/
void Game::setupship()
{

	int row0 = 0, row1 = 1, row2 = 2, row3 = 3, row4 = 4, row5 = 5, row6 = 6,
        row7 = 7, row8 = 8, row9 = 9, count = 0;

	string pickT = "Pick a Ship to Place", placed = "placed", spaces = "spaces",
           space = "space", pickError = "Please pick valid ship";

	do
	{
		//output line 1
		cdash(80);
		cout << endl;
		//output line 2
		blankline();
		cout << endl;
		//output line 3
		cout << LL << setw(5) << SP << 'A'
				   << setw(3) << SP << 'B'
				   << setw(3) << SP << 'C'
				   << setw(3) << SP << 'D'
				   << setw(3) << SP << 'E'
				   << setw(3) << SP << 'F'
				   << setw(3) << SP << 'G'
				   << setw(3) << SP << 'H'
				   << setw(3) << SP << 'I'
				   << setw(3) << SP << 'J' << setw(34) << SP << LL << endl;
		//output line 4
		cgrid();
		cout << setw(5) << SP;
		cdash(22);
		cout << setw(5) << SP << LL << endl;

		//output line 5
		cout << LL << SP << row0 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row0][i].occupied)
			{
				cout << tile[row0][i].vessal->title;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(6) << SP << pickT << setw(6) << SP << LL << endl;

		//output line 6
		cgrid();
		cout << setw(5) << SP;
		cdash(22);
		cout << setw(5) << SP << LL << endl;

		//output line 7
		cout << LL << SP << row1 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row1][i].occupied)
			{
				cout << tile[row1][i].vessal->title;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(5) << SP << row1 << PRD << SP << Boats[row0].name
			 << setw(8) << SP << LL << endl;

		//output line 8
		cgrid();
		cout << setw(8) << SP;
		if(Boats[row0].placed)
		{
			cout << placed << setw(18) << SP << LL << endl;
		}
		else
		{
			cout << Boats[row0].size << SP << spaces
                 << setw(16) << SP << LL << endl;
		}

		//output line 9
		cout << LL << SP << row2 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row2][i].occupied)
			{
				cout << tile[row2][i].vessal->title;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(5) << SP << row2 << PRD << SP << Boats[row1].name
			 << setw(14) << SP << LL << endl;

		//output line 10
		cgrid();
		cout << setw(8) << SP;
		if(Boats[row1].placed)
		{
			cout << placed << setw(18) << SP << LL << endl;
		}
		else
		{
			cout << Boats[row1].size << SP << spaces
                 << setw(16) << SP << LL << endl;
		}

		//output line 11
		cout << LL << SP << row3 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row3][i].occupied)
			{
				cout << tile[row3][i].vessal->title;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(5) << SP << row3 << PRD << SP << Boats[row2].name
			 << setw(17) << SP << LL << endl;

		//output line 12
		cgrid();
		cout << setw(8) << SP;
		if(Boats[row2].placed)
		{
			cout << placed << setw(18) << SP << LL << endl;
		}
		else
		{
			cout << Boats[row2].size << SP  << spaces
                 << setw(16) << SP << LL << endl;
		}

		//output line 13
		cout << LL << SP << row4 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row4][i].occupied)
			{
				cout << tile[row4][i].vessal->title;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(5) << SP << row4 << PRD << SP << Boats[row3].name
			 << setw(15) << SP << LL << endl;

		//output line 14
		cgrid();
		cout << setw(8) << SP;
		if(Boats[row3].placed)
		{
			cout << placed << setw(18) << SP << LL << endl;
		}
		else
		{
			cout << Boats[row3].size << SP << spaces
                 << setw(16) << SP << LL << endl;
		}

		//output line 15
		cout << LL << SP << row5 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row5][i].occupied)
			{
				cout << tile[row5][i].vessal->title;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(5) << SP << row5 << PRD << SP << Boats[row4].name
			 << setw(15) << SP << LL << endl;

		//output line 16
		cgrid();
		cout << setw(8) << SP;
		if(Boats[row4].placed)
		{
			cout << placed << setw(18) << SP << LL << endl;
		}
		else
		{
			cout << Boats[row4].size << SP << spaces
                 << setw(16) << SP << LL << endl;
		}

		//output line 17
		cout << LL << SP << row6 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row6][i].occupied)
			{
				cout << tile[row6][i].vessal->title;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(5) << SP << row6 << PRD << SP << Boats[row5].name << &Boats[row5]
			 << setw(21) << SP << LL << endl;

		//output line 18
		cgrid();
		cout << setw(8) << SP;
		if(Boats[row5].placed)
		{
			cout << placed << setw(18) << SP << LL << endl;
		}
		else
		{
			cout << Boats[row5].size << SP << space << setw(17) << SP << LL << endl;
		}

		//output line 19
		cout << LL << SP << row7 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row7][i].occupied)
			{
				cout << tile[row7][i].vessal->title;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(5) << SP << row7 << PRD << SP << Boats[row6].name << &Boats[row6]
			 << setw(21) << SP << LL << endl;

		//output line 20
		cgrid();
		cout << setw(8) << SP;
		if(Boats[row6].placed)
		{
			cout << placed << setw(18) << SP << LL << endl;
		}
		else
		{
			cout << Boats[row6].size << SP << space
                 << setw(17) << SP  << LL << endl;
		}

		//output line 21
		cout << LL << SP << row8 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row8][i].occupied)
			{
				cout << tile[row8][i].vessal->title;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(5) << SP;
		cdash(22);
		cout << setw(5) << SP << LL << endl;

		//output line 22
		cgrid();
		cout << setw(5) << SP;
		if(count != ZERO)
		{
			cout << pickError << setw(5) << SP << LL << endl;
		}
		else
		{
			cdash(22);
			cout << setw(5) << SP << LL << endl;
		}

		//output line 23
		cout << LL << SP << row9 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row9][i].occupied)
			{
				cout << tile[row9][i].vessal->title;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}

		if(count != ZERO)
		{
			cout << setw(5) << SP;
			cdash(22);
			cout << setw(5) << SP << LL << endl;
		}
		else
		{
			cout << setw(32) << SP << LL << endl;
		}

		//output line 24
		cgrid();
		cout << setw(32) << SP << LL << endl;

		//output line 25
		//output line 26
		for(int m = ZERO; m < 2; m++)
		{
			blankline();
			cout << endl;
		}

		//output line 27
		cdash(80);
		cout << endl;

		//output line 28
		cout << setw(2) << SP << selectionPrompt;
		getline(cin, shipInput);

		shipChoice = checkInput(shipInput, check3) - 1;

		if(shipChoice < ZERO)
		{
			count++;
			shipChoice = error;
		}
		else if(Boats[shipChoice].placed)
		{
			count++;
			shipChoice = error;
		}

	}while(shipChoice == error);

	count = ZERO;

}//Game::cdisplaysetup()


/*****************************************************************************
 * This function displays the board while picking ships spot                 * 
 *****************************************************************************/
void Game::setupspot()
{

	int row0 = 0, row1 = 1, row2 = 2, row3 = 3, row4 = 4, row5 = 5, row6 = 6,
        row7 = 7, row8 = 8, row9 = 9, count = 0;

	string spotT = "Pick a Spot to Place",
           spotError = "Please pick valid spot",
		   spotEx = "(example A1 or H8)";

	do
	{
		//output line 1
		cdash(80);
		cout << endl;
		//output line 2
		blankline();
		cout << endl;
		//output line 3
		cout << LL << setw(5) << SP << 'A'
				   << setw(3) << SP << 'B'
				   << setw(3) << SP << 'C'
				   << setw(3) << SP << 'D'
				   << setw(3) << SP << 'E'
				   << setw(3) << SP << 'F'
				   << setw(3) << SP << 'G'
				   << setw(3) << SP << 'H'
				   << setw(3) << SP << 'I'
				   << setw(3) << SP << 'J' << setw(34) << SP << LL << endl;
		//output line 4
		cgrid();
		cout << setw(5) << SP;
		cdash(22);
		cout << setw(5) << SP << LL << endl;

		//output line 5
		cout << LL << SP << row0 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row0][i].occupied)
			{
				cout << tile[row0][i].vessal->title;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(6) << SP << spotT << setw(6) << SP << LL << endl;

		//output line 6
		cgrid();
		cout << setw(5) << SP;
		cdash(22);
		cout << setw(5) << SP << LL << endl;

		//output line 7
		cout << LL << SP << row1 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row1][i].occupied)
			{
				cout << tile[row1][i].vessal->title;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(6) << SP << spotEx << setw(8) << SP << LL << endl;

		//output line 8
		cgrid();
		cout << setw(5) << SP;
		cdash(22);
		cout << setw(5) << SP << LL << endl;

		//output line 9
		cout << LL << SP << row2 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row2][i].occupied)
			{
				cout << tile[row2][i].vessal->title;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		if(count != 0)
		{
			cout << setw(5) << SP << spotError
                 << setw(5) << SP << LL  << endl;
		}
		else
		{
			cout << setw(5) << SP;
			cdash(22);
			cout << setw(5) << SP << LL << endl;
		}

		//output line 10
		cgrid();
		if(count != ZERO)
		{
			cout << setw(5) << SP;
			cdash(22);
			cout << setw(5) << SP << LL << endl;
		}
		else
		{
			cout << setw(32) << SP << LL << endl;
		}

		//output line 11
		cout << LL << SP << row3 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row3][i].occupied)
			{
				cout << tile[row3][i].vessal->title;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(32) << SP << LL << endl;

		//output line 12
		cgrid();
		cout << setw(32) << SP << LL << endl;

		//output line 13
		cout << LL << SP << row4 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row4][i].occupied)
			{
				cout << tile[row4][i].vessal->title;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(32) << SP << LL << endl;

		//output line 14
		cgrid();
		cout << setw(32) << SP << LL << endl;

		//output line 15
		cout << LL << SP << row5 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row5][i].occupied)
			{
				cout << tile[row5][i].vessal->title;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(32) << SP << LL << endl;

		//output line 16
		cgrid();
		cout << setw(32) << SP << LL << endl;

		//output line 17
		cout << LL << SP << row6 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row6][i].occupied)
			{
				cout << tile[row6][i].vessal->title;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(32) << SP << LL << endl;

		//output line 18
		cgrid();
		cout << setw(32) << SP << LL << endl;

		//output line 19
		cout << LL << SP << row7 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row7][i].occupied)
			{
				cout << tile[row7][i].vessal->title;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(32) << SP << LL << endl;

		//output line 20
		cgrid();
		cout << setw(32) << SP  << LL << endl;

		//output line 21
		cout << LL << SP << row8 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row8][i].occupied)
			{
				cout << tile[row8][i].vessal->title;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(32) << SP << LL << endl;

		//output line 22
		cgrid();
		cout << setw(32) << SP << LL << endl;

		//output line 23
		cout << LL << SP << row9 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row9][i].occupied)
			{
				cout << tile[row9][i].vessal->title;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(32) << SP << LL << endl;

		//output line 24
		cgrid();
		cout << setw(32) << SP << LL << endl;

		//output line 25
		//output line 26
		for(int m = ZERO; m < 2; m++)
		{
			blankline();
			cout << endl;
		}

		//output line 27
		cdash(80);
		cout << endl;

		//output line 28
		cout << setw(2) << SP << selectionPrompt;
		getline(cin, spotInput);

		if(spotInput.length() != 2)
		{
			count++;

			posx = error;
			posy = error;
		}
		else
		{
			posx = getx(spotInput[0]);
			posy = gety(spotInput[1]);
		}

		if(posx == error || posy == error)
		{
			count++;
		}
		else
		{
			placeleft = true;
			placeright = true;
			placeup = true;
			placedown = true;

			if((posx - Boats[shipChoice].size + 1) >= 0)
			{
				for(int a = 0; a < Boats[shipChoice].size; a++)
				{
					if(tile[posy][(posx - a)].occupied)
						placeleft = false;
				}

				if(placeleft)
					tile[posy][(posx - 1)].goodleft = true;
			}
			else
				placeleft = false;

			if((posx + Boats[shipChoice].size - 1) <= 9)
			{
				for(int b = 0; b < Boats[shipChoice].size; b++)
				{
					if(tile[posy][(posx + b)].occupied)
						placeright = false;
				}

				if(placeright)
					tile[posy][(posx + 1)].goodright = true;
			}
			else
				placeright = false;

			if((posy - Boats[shipChoice].size + 1) >= 0)
			{
				for(int c = 0; c < Boats[shipChoice].size; c++)
				{
					if(tile[(posy - c)][posx].occupied)
						placeup = false;
				}

				if(placeup)
					tile[(posy - 1)][posx].goodup = true;
			}
			else
				placeup = false;

			if((posy + Boats[shipChoice].size - 1) <= 9)
			{
				for(int d = 0; d < Boats[shipChoice].size; d++)
				{
					if(tile[(posy + d)][posx].occupied)
						placedown = false;

					if(placedown)
						tile[(posy + 1)][posx].gooddown = true;
				}
			}
			else
				placedown = false;

			if(!placeleft && !placeright && !placeup && !placedown)
			{
				count++;

				posx = error;
				posy = error;
			}
		}

	}while(posx == error || posy == error);

	count = ZERO;

}//Game::setupspot()


/*****************************************************************************
 * This function displays the board while picking ships direction            * 
 *****************************************************************************/
void Game::setupdirection()
{

	int row0 = 0, row1 = 1, row2 = 2, row3 = 3, row4 = 4, row5 = 5, row6 = 6,
        row7 = 7, row8 = 8, row9 = 9, count = 0;

	string directionT = "Pick a Direction",
           directionError = "Pick a valid Direction",
           theUp = "Up (^)", theDown = "Down (v)", theLeft = "Left (<)",
           theRight = "Right (>)", arrowup = "^", arrowdown = "v", 
		   arrowleft = "<", arrowright = ">";

	do
	{
		//output line 1
		cdash(80);
		cout << endl;
		//output line 2
		blankline();
		cout << endl;
		//output line 3
		cout << LL << setw(5) << SP << 'A'
				   << setw(3) << SP << 'B'
				   << setw(3) << SP << 'C'
				   << setw(3) << SP << 'D'
				   << setw(3) << SP << 'E'
				   << setw(3) << SP << 'F'
				   << setw(3) << SP << 'G'
				   << setw(3) << SP << 'H'
				   << setw(3) << SP << 'I'
				   << setw(3) << SP << 'J' << setw(34) << SP << LL << endl;
		//output line 4
		cgrid();
		cout << setw(5) << SP;
		cdash(22);
		cout << setw(5) << SP << LL << endl;

		//output line 5
		cout << LL << SP << row0 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row0][i].occupied)
			{
				cout << tile[row0][i].vessal->title;
			}
			else if(tile[row0][i].goodup)
			{
				cout << arrowup;
			}
			else if(tile[row0][i].goodleft)
			{
				cout << arrowleft;
			}
			else if(tile[row0][i].gooddown)
			{
				cout << arrowdown;
			}
			else if(tile[row0][i].goodright)
			{
				cout << arrowright;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(8) << SP << directionT << setw(8) << SP << LL << endl;

		//output line 6
		cgrid();
		cout << setw(5) << SP;
		cdash(22);
		cout << setw(5) << SP << LL << endl;

		//output line 7
		cout << LL << SP << row1 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row1][i].occupied)
			{
				cout << tile[row1][i].vessal->title;
			}
			else if(tile[row1][i].goodup)
			{
				cout << arrowup;
			}
			else if(tile[row1][i].goodleft)
			{
				cout << arrowleft;
			}
			else if(tile[row1][i].gooddown)
			{
				cout << arrowdown;
			}
			else if(tile[row1][i].goodright)
			{
				cout << arrowright;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(5) << SP << row1 << PRD << SP << theUp
			 << setw(18) << SP << LL << endl;

		//output line 8
		cgrid();
		cout << setw(32) << SP << LL << endl;

		//output line 9
		cout << LL << SP << row2 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row2][i].occupied)
			{
				cout << tile[row2][i].vessal->title;
			}
			else if(tile[row2][i].goodup)
			{
				cout << arrowup;
			}
			else if(tile[row2][i].goodleft)
			{
				cout << arrowleft;
			}
			else if(tile[row2][i].gooddown)
			{
				cout << arrowdown;
			}
			else if(tile[row2][i].goodright)
			{
				cout << arrowright;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(5) << SP << row2 << PRD << SP << theLeft
			 << setw(16) << SP << LL << endl;

		//output line 10
		cgrid();
		cout << setw(32) << SP << LL << endl;

		//output line 11
		cout << LL << SP << row3 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row3][i].occupied)
			{
				cout << tile[row3][i].vessal->title;
			}
			else if(tile[row3][i].goodup)
			{
				cout << arrowup;
			}
			else if(tile[row3][i].goodleft)
			{
				cout << arrowleft;
			}
			else if(tile[row3][i].gooddown)
			{
				cout << arrowdown;
			}
			else if(tile[row3][i].goodright)
			{
				cout << arrowright;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(5) << SP << row3 << PRD << SP << theDown
			 << setw(16) << SP << LL << endl;

		//output line 12
		cgrid();
		cout << setw(32) << SP << LL << endl;

		//output line 13
		cout << LL << SP << row4 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row4][i].occupied)
			{
				cout << tile[row4][i].vessal->title;
			}
			else if(tile[row4][i].goodup)
			{
				cout << arrowup;
			}
			else if(tile[row4][i].goodleft)
			{
				cout << arrowleft;
			}
			else if(tile[row4][i].gooddown)
			{
				cout << arrowdown;
			}
			else if(tile[row4][i].goodright)
			{
				cout << arrowright;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(5) << SP << row4 << PRD << SP << theRight
			 << setw(15) << SP << LL << endl;

		//output line 14
		cgrid();
		cout << setw(5) << SP;
		cdash(22);
		cout << setw(5) << SP << LL << endl;

		//output line 15
		cout << LL << SP << row5 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row5][i].occupied)
			{
				cout << tile[row5][i].vessal->title;
			}
			else if(tile[row5][i].goodup)
			{
				cout << arrowup;
			}
			else if(tile[row5][i].goodleft)
			{
				cout << arrowleft;
			}
			else if(tile[row5][i].gooddown)
			{
				cout << arrowdown;
			}
			else if(tile[row5][i].goodright)
			{
				cout << arrowright;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(5) << SP;

		if(count != ZERO)
		{
			cout << directionError << setw(5) << SP << LL << endl;
		}
		else
		{
			cdash(22);
			cout << setw(5) << SP << LL << endl;
		}

		//output line 16
		cgrid();

		if(count != ZERO)
		{
			cout << setw(5) << SP;
			cdash(22);
			cout << setw(5) << SP << LL << endl;
		}
		else
		{
			cout << setw(32) << SP << LL << endl;
		}

		//output line 17
		cout << LL << SP << row6 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row6][i].occupied)
			{
				cout << tile[row6][i].vessal->title;
			}
			else if(tile[row6][i].goodup)
			{
				cout << arrowup;
			}
			else if(tile[row6][i].goodleft)
			{
				cout << arrowleft;
			}
			else if(tile[row6][i].gooddown)
			{
				cout << arrowdown;
			}
			else if(tile[row6][i].goodright)
			{
				cout << arrowright;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(32) << SP << LL << endl;

		//output line 18
		cgrid();
		cout << setw(32) << SP << LL << endl;

		//output line 19
		cout << LL << SP << row7 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row7][i].occupied)
			{
				cout << tile[row7][i].vessal->title;
			}
			else if(tile[row7][i].goodup)
			{
				cout << arrowup;
			}
			else if(tile[row7][i].goodleft)
			{
				cout << arrowleft;
			}
			else if(tile[row7][i].gooddown)
			{
				cout << arrowdown;
			}
			else if(tile[row7][i].goodright)
			{
				cout << arrowright;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(32) << SP << LL << endl;

		//output line 20
		cgrid();
		cout << setw(32) << SP << LL << endl;

		//output line 21
		cout << LL << SP << row8 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row8][i].occupied)
			{
				cout << tile[row8][i].vessal->title;
			}
			else if(tile[row8][i].goodup)
			{
				cout << arrowup;
			}
			else if(tile[row8][i].goodleft)
			{
				cout << arrowleft;
			}
			else if(tile[row8][i].gooddown)
			{
				cout << arrowdown;
			}
			else if(tile[row8][i].goodright)
			{
				cout << arrowright;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(32) << SP << LL << endl;

		//output line 22
		cgrid();
		cout << setw(32) << SP << LL << endl;

		//output line 23
		cout << LL << SP << row9 << SP << L;
		for(int i = ZERO; i < 10; i++)
		{
			cout << SP;
			if(tile[row9][i].occupied)
			{
				cout << tile[row9][i].vessal->title;
			}
			else if(tile[row9][i].goodup)
			{
				cout << arrowup;
			}
			else if(tile[row9][i].goodleft)
			{
				cout << arrowleft;
			}
			else if(tile[row9][i].gooddown)
			{
				cout << arrowdown;
			}
			else if(tile[row9][i].goodright)
			{
				cout << arrowright;
			}
			else
			{
				cout << SP;
			}
			cout << SP << L;
		}
		cout << setw(32) << SP << LL << endl;

		//output line 24
		cgrid();
		cout << setw(32) << SP << LL << endl;

		//output line 25
		//output line 26
		for(int m = ZERO; m < 2; m++)
		{
			blankline();
			cout << endl;
		}

		//output line 27
		cdash(80);
		cout << endl;

		//output line 28
		cout << setw(2) << SP << selectionPrompt;
		getline(cin, directionInput);

		directionChoice = checkInput(directionInput, check4);

		switch(directionChoice)
		{
			case 1:
				if((posy - Boats[shipChoice].size + 1) < 0)
					directionChoice = error;

				if(directionChoice != error)
				{
					for(int n = 1; n < Boats[shipChoice].size; n++)
					{
						if(tile[(posy - n)][posx].occupied)
							directionChoice = error;
					}
				}
				break;
			case 2:
				if((posx - Boats[shipChoice].size + 1) < 0)
					directionChoice = error;
				
				if(directionChoice != error)
				{
					for(int n = 1; n < Boats[shipChoice].size; n++)
					{
						if(tile[posy][(posx - n)].occupied)
							directionChoice = error;
					}
				}
				break;
			case 3:
				if((posy + Boats[shipChoice].size - 1) > 9)
				{
					directionChoice = error;
					count++;
				}

				if(directionChoice != error)
				{
					for(int n = 1; n < Boats[shipChoice].size; n++)
					{
						if(tile[(posy + n)][posx].occupied)
						{
							directionChoice = error;
							count++;
						}
					}
				}
				break;
			case 4:
				if((posx + Boats[shipChoice].size - 1) > 9)
				{
					directionChoice = error;
					count++;
				}

				if(directionChoice != error)
				{
					for(int n = 1; n < Boats[shipChoice].size; n++)
					{
						if(tile[posy][(posx + n)].occupied)
						{
							directionChoice = error;
							count++;
						}
					}
				}
				break;
			default:
				break;
		}

		if(directionChoice == error)
		{
			count++;
		}

	}while(directionChoice == error);

	count = ZERO;

}//Game::setupdirection


/*****************************************************************************
 * This function plays the game on easy mode                                 * 
 * The computer will get 5 random guesses a turn but a set number of turns   *
 *****************************************************************************/
void Game::playgameEasy()
{
	bool valid = false;

	int turns, initialize, xvalue, yvalue, count;

	string turnInput;

	unsigned seed = time(0);

	vector<coordinates> shots;
	srand(seed);

	initialize = (rand() % (9 - 0 + 1)) + 0;

	do
	{
		cout << "How many turns does the computer get?" << endl;
		cout << "(minium 5 turns): ";
		getline(cin, turnInput);

		turns = checkInput(turnInput, check5);

		if(turns == error)
		{
			cout << "Enter a value between 5 and 20" << endl;
			cout << eCONTINUE;
			cin.get();
		}

	}while(turns == error);

	for(int i = 0; i < turns; i++)
	{
		for(int j = 0; j < 5; j++)
		{
			do
			{
				xvalue = (rand() % (9 - 0 + 1)) + 0;
				yvalue = (rand() % (9 - 0 + 1)) + 0;

				if(tile[yvalue][xvalue].open)
					valid = true;

			}while(!valid);

			shots.push_back(coordinates());
			count = shots.size() - 1;

			shots[count].xordinate = xvalue;
			shots[count].yordinate = yvalue;

			if(tile[shots[count].yordinate][shots[count].xordinate].occupied)
			{
				tile[shots[count].yordinate][shots[count].xordinate].open = false;
				tile[shots[count].yordinate][shots[count].xordinate].vessal->hits++;

				if(tile[shots[count].yordinate][shots[count].xordinate].vessal->hits ==
				   tile[shots[count].yordinate][shots[count].xordinate].vessal->size)
				{
					tile[shots[count].yordinate][shots[count].xordinate].vessal->sunk = true;
					sunkcount++;

					if(sunkcount == 7)
						return;
				}
			}
			else
			{
				tile[shots[count].yordinate][shots[count].xordinate].open = false;
				openspots--;

				if(openspots == 0)
					return;
			}
		}

		recordguess(shots[count].xordinate, shots[count].yordinate, false);
	}

}//Game::playgameEasy()


/*****************************************************************************
 * This function plays the game in impossible mode                           * 
 * The computer cheats and will always win                                   *
 *****************************************************************************/
void Game::playgameImpossible()
{
	int whichone, cheating, maxValue;

	unsigned seed = time(0);

	srand(seed);

	for(int y = 0; y < COLS; y++)
	{
		for(int x = 0; x < ROWS; x++)
		{
			if(tile[y][x].occupied)
			{
				storeguesses.push_back(coordinates());
				
				whichone = storeguesses.size() - 1;

				storeguesses[whichone].xordinate = x;
				storeguesses[whichone].yordinate = y;
			}
		}
	}

	do
	{

		if(storeguesses.size() != 1)
		{
			maxValue = storeguesses.size() - 1;

			cheating = (rand() % (maxValue - 0 + 1)) + 0;
		}
		else
		{
			cheating = 0;
		}

		tile[storeguesses[cheating].yordinate][storeguesses[cheating].xordinate].open = false;
		tile[storeguesses[cheating].yordinate][storeguesses[cheating].xordinate].vessal->hits++;

		if(tile[storeguesses[cheating].yordinate][storeguesses[cheating].xordinate].vessal->hits ==
           tile[storeguesses[cheating].yordinate][storeguesses[cheating].xordinate].vessal->size)
		{
			tile[storeguesses[cheating].yordinate][storeguesses[cheating].xordinate].vessal->sunk = true;
			sunkcount++;

			recordguess(storeguesses[cheating].xordinate, storeguesses[cheating].yordinate, true);
		}
		else
		{
			recordguess(storeguesses[cheating].xordinate, storeguesses[cheating].yordinate, false);
		}

		storeguesses.erase(storeguesses.begin() + cheating);

	}while(!storeguesses.empty());
			
}//Game::playgameImpossible()


/*****************************************************************************
 * This function displays the game state as the computer guesses             * 
 *****************************************************************************/
void Game::displayguess()
{

	int row0 = 0, row1 = 1, row2 = 2, row3 = 3, row4 = 4, row5 = 5, row6 = 6,
        row7 = 7, row8 = 8, row9 = 9, count = 0;

	string shipT = "Ships", sunked = "sunk", lastguess = "Last Guess",
           miss = "/", hit = "X", sunkship = "SS", themiss = "M",
           thehit = "H";

	//output line 1
	cdash(80);
	cout << endl;
	//output line 2
	blankline();
	cout << endl;
	//output line 3
	cout << LL << setw(5) << SP << 'A'
			   << setw(3) << SP << 'B'
			   << setw(3) << SP << 'C'
			   << setw(3) << SP << 'D'
			   << setw(3) << SP << 'E'
			   << setw(3) << SP << 'F'
			   << setw(3) << SP << 'G'
			   << setw(3) << SP << 'H'
			   << setw(3) << SP << 'I'
			   << setw(3) << SP << 'J' << setw(34) << SP << LL << endl;
	//output line 4
	cgrid();
	cout << setw(2) << SP;
	cdash(25);
	cout << setw(5) << SP << LL << endl;

	//output line 5
	cout << LL << SP << row0 << SP << L;
	for(int i = ZERO; i < 10; i++)
	{
		cout << SP;
		if(tile[row0][i].open && tile[row0][i].occupied)
		{
			cout << tile[row0][i].vessal->title;
		}
		else if(!tile[row0][i].open && tile[row0][i].occupied)
		{
			cout << hit;
		}
		else if(!tile[row0][i].open)
		{
			cout << miss;
		}
		else
		{
			cout << SP;
		}
		cout << SP << L;
	}
	cout << setw(3) << SP << shipT << setw(24) << SP << LL << endl;

	//output line 6
	cgrid();
	cout << setw(2) << SP;
	cdash(25);
	cout << setw(5) << SP << LL << endl;

	//output line 7
	cout << LL << SP << row1 << SP << L;
	for(int i = ZERO; i < 10; i++)
	{
		cout << SP;
		if(tile[row1][i].open && tile[row1][i].occupied)
		{
			cout << tile[row1][i].vessal->title;
		}
		else if(!tile[row1][i].open && tile[row1][i].occupied)
		{
			cout << hit;
		}
		else if(!tile[row1][i].open)
		{
			cout << miss;
		}
		else
		{
			cout << SP;
		}
		cout << SP << L;
	}
	cout << setw(2) << SP << row1 << PRD << SP
		 << setw(18) << left << Boats[row0].name;
	if(Boats[row0].sunk)
	{
		cout << sunked << setw(4) << SP << LL << endl;
	}
	else
	{
		cout  << (Boats[row0].size - Boats[row0].hits) << SLSH
			  << Boats[row0].size << setw(5) << SP << LL << endl;
	}

	//output line 8
	cgrid();
	cout << setw(2) << SP << row2 << PRD << SP
		 << setw(18) << left << Boats[row1].name;
	if(Boats[row1].sunk)
	{
		cout << sunked << setw(4) << SP << LL << endl;
	}
	else
	{ 
		cout << (Boats[row1].size - Boats[row1].hits) << SLSH
			 << Boats[row1].size << setw(5) << SP << LL << endl;
	}

	//output line 9
	cout << LL << SP << row2 << SP << L;
	for(int i = ZERO; i < 10; i++)
	{
		cout << SP;
		if(tile[row2][i].open && tile[row2][i].occupied)
		{
			cout << tile[row2][i].vessal->title;
		}
		else if(!tile[row2][i].open && tile[row2][i].occupied)
		{
			cout << hit;
		}
		else if(!tile[row2][i].open)
		{
			cout << miss;
		}
		else
		{
			cout << SP;
		}
		cout << SP << L;
	}
	cout << setw(2) << SP << row3 << PRD << SP 
		 << setw(18) << left << Boats[row2].name;
	if(Boats[row2].sunk)
	{
		cout << sunked << setw(4) << SP << LL << endl;
	}
	else
	{
		cout << (Boats[row2].size - Boats[row2].hits) << SLSH
			 << Boats[row4].size << setw(5) << SP << LL << endl;
	}

	//output line 10
	cgrid();
	cout << setw(2) << SP << row4 << PRD
		 << setw(18) << left << Boats[row3].name;
	if(Boats[row3].sunk)
	{
		cout << sunked << setw(4) << LL << endl;
	}
	else
	{
		cout << (Boats[row3].size - Boats[row3].hits) << SLSH
			 << Boats[row3].size << setw(5) << SP << LL << endl;
	}

	//output line 11
	cout << LL << SP << row3 << SP << L;
	for(int i = ZERO; i < 10; i++)
	{
		cout << SP;
		if(tile[row3][i].open && tile[row3][i].occupied)
		{
			cout << tile[row3][i].vessal->title;
		}
		else if(!tile[row3][i].open && tile[row3][i].occupied)
		{
			cout << hit;
		}
		else if(!tile[row3][i].open)
		{
			cout << miss;
		} 
		else
		{
			cout << SP;
		}
		cout << SP << L;
	}
	cout << setw(2) << SP << row5 << PRD << SP
		 << setw(18) << left << Boats[row4].name;
	if(Boats[row4].sunk)
	{
		cout << sunked << setw(5) << SP << LL << endl;
	}
	else
	{
		cout << (Boats[row4].size - Boats[row4].hits) << SLSH
			 << Boats[row4].size << setw(6) << SP << LL << endl;
	}

	//output line 12
	cgrid();
	cout << setw(2) << SP << row6 << PRD << SP
		 << setw(18) << left << Boats[row5].name;
	if(Boats[row5].sunk)
	{
		cout << sunked << setw(5) << LL << endl;
	}
	else
	{
		cout << (Boats[row5].size - Boats[row5].hits) << SLSH
			 << Boats[row5].size << setw(6) << SP << LL << endl;
	}

	//output line 13
	cout << LL << SP << row4 << SP << L;
	for(int i = ZERO; i < 10; i++)
	{
		cout << SP;
		if(tile[row4][i].open && tile[row4][i].occupied)
		{
			cout << tile[row4][i].vessal->title;
		}
		else if(!tile[row4][i].open && tile[row4][i].occupied)
		{
			cout << hit;
		}
		else if(!tile[row4][i].open)
		{
			cout << miss;
		}
		else
		{
			cout << SP;
		}
		cout << SP << L;
	}
	cout << setw(2) << SP << row7 << PRD << SP 
		 << setw(18) << left << Boats[row6].name;
	if(Boats[row6].sunk)
	{
		cout << sunked << setw(5) << LL << endl;
	}
	else
	{
		cout << (Boats[row6].size - Boats[row6].hits) << SLSH
			 << Boats[row6].size << setw(6) << SP << LL << endl;
	}

	//output line 14
	cgrid();
	cout << setw(2) << SP;
	cdash(25);
	cout << setw(5) << SP << LL << endl;

	//output line 15
	cout << LL << SP << row5 << SP << L;
	for(int i = ZERO; i < 10; i++)
	{
		cout << SP;
		if(tile[row5][i].open && tile[row5][i].occupied)
		{
			cout << tile[row5][i].vessal->title;
		}
		else if(!tile[row5][i].open && tile[row5][i].occupied)
		{
			cout << hit;
		}
		else if(!tile[row5][i].open)
		{
			cout << miss;
		}
		else
		{
			cout << SP;
		}
		cout << SP << L;
	}
	cout << setw(2) << SP;
	cdash(25);
	cout << setw(5) << SP << LL << endl;

	//output line 16
	cgrid();
	cout << setw(3) << SP << lastguess << setw(19) << SP << LL << endl;

	//output line 17
	cout << LL << SP << row6 << SP << L;
	for(int i = ZERO; i < 10; i++)
	{
		cout << SP;
		if(tile[row6][i].open && tile[row6][i].occupied)
		{
			cout << tile[row6][i].vessal->title;
		}
		else if(!tile[row6][i].open && tile[row6][i].occupied)
		{
			cout << hit;
		}
		else if(!tile[row6][i].open)
		{
			cout << miss;
		}
		else
		{
			cout << SP;
		}
		cout << SP << L;
	}
	cout << setw(2) << SP;
	cdash(25);
	cout << setw(5) << SP << LL << endl;

	//output line 18
	cgrid();
	cout << setw(2) << SP << guesses.size() << PRD << SP;
	cout << guesses[(guesses.size() - 1)].location;

	if(guesses[(guesses.size() - 1)].ahit)
		cout << DOT << thehit;
	else
		cout << DOT << themiss;

	if(guesses[(guesses.size() - 1)].shipsunk)
		cout << DOT << sunkship << setw(20) << SP << LL << endl;
	else
		cout << setw(23) << SP << LL << endl;

	//output line 19
	cout << LL << SP << row7 << SP << L;
	for(int i = ZERO; i < 10; i++)
	{
		cout << SP;
		if(tile[row7][i].open && tile[row7][i].occupied)
		{
			cout << tile[row7][i].vessal->title;
		}
		else if(!tile[row7][i].open && tile[row7][i].occupied)
		{
			cout << hit;
		}
		else if(!tile[row7][i].open)
		{
			cout << miss;
		}
		else
		{
			cout << SP;
		}
		cout << SP << L;
	}
	cout << setw(2) << SP;
	cdash(25);
	cout << setw(5) << SP << LL << endl;

	//output line 20
	cgrid();
	cout << setw(2) << SP;
	cdash(25);
	cout << setw(5) << SP << LL << endl;

	//output line 21
	cout << LL << SP << row8 << SP << L;
	for(int i = ZERO; i < 10; i++)
	{
		cout << SP;
		if(tile[row8][i].open && tile[row8][i].occupied)
		{
			cout << tile[row8][i].vessal->title;
		}
		else if(!tile[row8][i].open && tile[row8][i].occupied)
		{
			cout << hit;
		}
		else if(!tile[row8][i].open)
		{
			cout << miss;
		}
		else
		{
			cout << SP;
		}
		cout << SP << L;
	}
	cout << setw(32) << SP << LL << endl;

	//output line 22
	cgrid();
	cout << setw(32) << SP << LL << endl;

	//output line 23
	cout << LL << SP << row9 << SP << L;
	for(int i = ZERO; i < 10; i++)
	{
		cout << SP;
		if(tile[row9][i].open && tile[row9][i].occupied)
		{
			cout << tile[row9][i].vessal->title;
		}
		else if(!tile[row9][i].open && tile[row9][i].occupied)
		{
			cout << hit;
		}
		else if(!tile[row9][i].open)
		{
			cout << miss;
		}
		else
		{
			cout << SP;
		}
		cout << SP << L;
	}
	cout << setw(32) << SP << LL << endl;

	//output line 24
	cgrid();
	cout << setw(32) << SP << LL << endl;

	//output line 25
	//output line 26
	for(int m = ZERO; m < 2; m++)
	{
		blankline();
		cout << endl;
	}

	//output line 27
	cdash(80);
	cout << endl;

	//output line 28
	cout << setw(2) << SP << eCONTINUE;
	cin.get();

}//Game::cdisplaysetup()



