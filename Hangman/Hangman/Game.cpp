//Importing libraries for rand(), strcmp(), etc.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <cstring>
#include <ctype.h>

//Declaring the functions
int gameLoop();
int displayMenu();
char takeInput(char hiddenWord[], char revealedWord[], int &wordLength, int &guessesRemaining, int &score, char wrongLetters[], int &gameMode, bool &displayGuesses);
void generateWord(char hiddenWord[], char revealedWord[], int &stopRepeat, int &gameMode, int &wordLength);
void displayGallows(char hiddenWord[], char revealedWord[], int &wordLength, int &guessesRemaining, bool &displayGuesses, int &score, char wrongLetters[], int &gameMode);
int checkLetter(char hiddenWord[], char revealedWord[], int wordLength, int guessesRemaining, char guess, char wrongLetters[], int &nextLtr);
void exitGame();
void displayHelp();
int checkWin(char hiddenWord[], char revealedWord[], int &guessesRemaining, int &score, int &gameMode, bool &secretUnlocked, bool &displayGuesses, int &wordLength, char wrongLetters[]);
int displayOptions(int &score, int gameMode);

int main(void)
{
	//Starting up the game loop
	gameLoop();

	return 0;
}

int gameLoop()
{
	//Declaring the variables
	int guessesRemaining = 6;
	int wordLength;
	char hiddenWord[20] = { 0 };
	char revealedWord[20] = { 0 };
	char wrongLetters[20] = { 0 };
	int nextLtr = 0;
	char guess;
	int decider;
	char tryAgain = 'y';
	int stopRepeat;
	int score = 0;
	int gameMode = 1;
	bool secretUnlocked = false;
	bool displayGuesses = false;

	do
	{
		//Refreshing the Variables
		system("cls");
		tryAgain = 'y';
		decider = 0;
		guessesRemaining = 6;
		nextLtr = 0;
		for (int i = 0; i < 20; ++i)
		{
			wrongLetters[i] = 0;
		}

		//This loop is designed to cycle through the menu and its options
		while (decider == 0 || decider == 1 || decider == 2 || decider == 3)
		{
			decider = 0;

			if (decider == 0)
			{
				//calls a function that displays the menu options and takes the users input
				decider = displayMenu();
			}

			switch (decider)
			{
				case 1:
				{
					//selects a word from a text document for the user to try and guess
					generateWord(hiddenWord, revealedWord, stopRepeat, gameMode, wordLength);

					while (decider == 1)
					{
						//takes the users guessed letter and checks whether it's a valid input or an exit key
						guess = takeInput(hiddenWord, revealedWord, wordLength, guessesRemaining, score, wrongLetters, gameMode, displayGuesses);

						if (guess == '4')
						{
							//this statement will trigger if the user wants to quit the game, causing the screen to be cleared and the game to be finished
							system("cls");
							exitGame();
							return 0;
						}

						//checks the users input and matches it against the hidden word's letters 
						//from this it determines whether to reduce the remaining guesses or not
						guessesRemaining = checkLetter(hiddenWord, revealedWord, wordLength, guessesRemaining, guess, wrongLetters, nextLtr);

						//checks to see if the user has matched all of their input letters to the hidden word and whether they have enough guesses remaining
						//if the user has run out of guesses it will return 5 to the decider and cause the game loop to break
						//it will also return 5 to the decider if the user has won, also causing the loop to break
						decider = checkWin(hiddenWord, revealedWord, guessesRemaining, score, gameMode, secretUnlocked, displayGuesses, wordLength, wrongLetters);
					}

					break;

				}

				case 2:
				{
					//displays helpful information to the screen
					displayHelp();
					break;
				}

				case 3:
				{
					//allows the user to change themes or the game difficulty
					gameMode = displayOptions(score, gameMode);
					break;
				}

				case 4:
				{
					//prints an exit message to the screen and then quits the game
					exitGame();
					return 0;
				}

				default:
				{
					//this message will only show up if there's a bug in the switch statement
					std::cout << "Error in case statement." << std::endl;
					return 0;
				}
			}
		}

		//offers the user to enter the game loop again and continue playing
		std::cout << "\nWould you like to play again? \n(Enter 'y' if you'd like to play again.)\n\nInput:> ";
		std::cin >> tryAgain;

	} 
	while (tryAgain == 'y' || tryAgain == 'Y');
	
	//prints an exit message to the screen and then quits the game
	exitGame();
	return 0;
}

void generateWord(char hiddenWord[], char revealedWord[], int &stopRepeat, int &gameMode, int &wordLength)
{
	//creates variables for accessing the text files, picking a word from them, and then storing it within an array
	std::ifstream file;
	int wordPicker;
	char word[20] = { 0 };
	
	//clears the word-containing arrays from a previous round
	for (int i = 0; i < 20; ++i)
	{
		hiddenWord[i] = 0;
		revealedWord[i] = 0;
	}

	//selects a random number to determine which word will be used for the game
	do
	{
		srand(time(NULL));
		if (gameMode == 7)
		{
			//this will only trigger if the user is on Very Hard mode
			wordPicker = rand() % 8;
		}
		else
		{
			wordPicker = rand() % 15;
		}
	} 
	while (wordPicker == stopRepeat);
	
	//this prevents the same word being selected twice consecutively
	stopRepeat = wordPicker;

	//this switch statement will select a text file of words based on the game mode currently chosen
	switch (gameMode)
	{
		case 1:
		{
			file.open("EasyWords.txt");
			break;
		}

		case 2:
		{
			file.open("NormalWords.txt");
			break;
		}

		case 3:
		{
			file.open("HardWords.txt");
			break;
		}

		case 4:
		{
			file.open("Cities.txt");
			break;
		}

		case 5:
		{
			file.open("Characters.txt");
			break;
		}

		case 6:
		{
			file.open("Food.txt");
			break;
		}

		case 7:
		{
			file.open("VeryHardWords.txt");
			break;
		}

		default:
		{
			//this message will only appear if there's a problem with selecting a file to open
			std::cout << "Error in file opening" << std::endl;
		}
	}

	//cycles through the words in the selected text file and picks one out
	for (int i = 0; i <= wordPicker; ++i)
	{
		file >> word;
	}

	//closes the text file
	file.close();

	//copies the selected word into the array that will be compared against user inputs
	strcpy(&hiddenWord[0], &word[0]);

	//obtains the length of the word
	wordLength = strlen(hiddenWord);

	//fills the shown word with blank spaces for the user to uncover
	for (int i = 0; i < wordLength; ++i)
	{
		revealedWord[i] = '_';
	}
}

int displayMenu()
{
	char input;
	int decider;

	do
	{
		//takes an input from the user and checks to see if it's a number
		do
		{
			//displays the welcome message and shows the user their options
			std::cout << "---Welcome to Hang Man---" << std::endl;
			std::cout << "Please choose an option by entering the corresponding number:\n\nStart Game - 1\nHelp       - 2\nOptions    - 3\nExit Game  - 4" << std::endl;
			std::cout << "\nYour Input:> ";
			std::cin >> input;
			system("cls");
		} 
		while (!isdigit(input));

		//converts numbers from their ascii value to their real value
		decider = (int)input - 48;
 
		//warns users if they enter numbers that weren't displayed
		if (decider != 1 && decider != 2 && decider != 3)
		{
			std::cout << "Please only enter 1, 2 or 3." << std::endl;
		}

	} 
	while (decider != 1 && decider != 2 && decider != 3);

	//sends the users choice back to the main game loop
	return decider;
}

int displayOptions(int &score, int gameMode)
{
	char input;

	std::cout << "---Options---" << std::endl;
	std::cout << "Here you can choose the difficulty or theme that will be used \nwhen you play the game.\n" << std::endl;

	//displays the current game mode to the screen
	switch (gameMode)
	{
		case 1:
		{
			std::cout << "Current mode: Easy" << std::endl;
			break;
		}

		case 2:
		{
			std::cout << "Current mode: Normal" << std::endl;
			break;
		}

		case 3:
		{
			std::cout << "Current mode: Hard" << std::endl;
			break;
		}

		case 4:
		{
			std::cout << "Current mode: Cities of The World" << std::endl;
			break;
		}

		case 5:
		{
			std::cout << "Current mode: Video Game Characters" << std::endl;
			break;
		}

		case 6:
		{
			std::cout << "Current mode: Food and Drinks" << std::endl;
			break;
		}

		case 7:
		{
			std::cout << "Current mode: Very Hard" << std::endl;
			break;
		}

		default:
		{
			//this message will only display if there's a problem with the current game mode
			std::cout << "Error in current game mode" << std::endl;
		}
	}
	
	do
	{
		do
		{
			//shows the user their theme/difficulty options
			std::cout << "Easy mode                   - 1" << std::endl;
			std::cout << "Normal mode                 - 2" << std::endl;
			std::cout << "Hard mode                   - 3" << std::endl;
			std::cout << "Cities of The World theme   - 4" << std::endl;
			std::cout << "Video Game Characters theme - 5" << std::endl;
			std::cout << "Food and Drinks theme       - 6" << std::endl;
			if (score >= 15)
			{
				//this option only becomes available if the user reaches 15 or more score
				std::cout << "New! Very Hard mode         - 7" << std::endl;
			}

			//takes user input for the theme/difficulty choice
			std::cout << "\nPlease choose a difficulty for standard play or a different theme." << std::endl;
			std::cout << "\nYour input:> ";
			std::cin >> input;
			system("cls");
		} 
		while (!isdigit(input));

		//converts numbers from their ascii value to their real value
		gameMode = (int)input - 48;

		//returns the game mode choice back to the game loop immediately if the user has selected Very Hard and their score is 15 or above
		if (gameMode == 7 && score >= 15)
		{
			return gameMode;
		}

		//warns the user if they enter a numeric value that isn't listed as an option for a game mode
		if (gameMode != 1 && gameMode != 2 && gameMode != 3 && gameMode != 4 && gameMode != 5 && gameMode != 6)
		{
			std::cout << "---Options---" << std::endl;
			std::cout << "Please only enter one of the numbers below.\n\n\n" << std::endl;
		}
	} 
	while (gameMode != 1 && gameMode != 2 && gameMode != 3 && gameMode != 4 && gameMode != 5 && gameMode != 6); //checks to see whether the users input matches one of the game modes
	
	//returns the chosen game mode back to the game loop
	return gameMode;
}

char takeInput(char hiddenWord[], char revealedWord[], int &wordLength, int &guessesRemaining, int &score, char wrongLetters[], int &gameMode, bool &displayGuesses)
{
	char input[100];
	int length;
	char guess;

	while (true)
	{
		//gets user input and checks if it's a valid input
		do
		{
			//clears the screen and displays the gallows with the user input section
			system("cls");
			displayGallows(hiddenWord, revealedWord, wordLength, guessesRemaining, displayGuesses, score, wrongLetters, gameMode);
			std::cout << "Enter a single letter to guess: \n(Or enter '4' if you wish to quit.)\n\nYour Input:> ";
			std::cin >> input;

			//obtains the length of the users input to check later in the loop
			length = strlen(input);

			//converts the users input into a single char variable
			guess = input[0];

			//checks to see if the user has chosen entered "4" to quit
			if (guess == '4')
			{
				return guess;
			}
			else
				if (guess == '9') //checks to see if the user has entered "9" to display the exact amount of guesses remaining
				{
					if (displayGuesses != true) //if the guesses aren't already displayed then this will display them
					{
						displayGuesses = true;
					}
					else
					{
						displayGuesses = false;
					}
				}
		} 
		while (!isalpha(guess) || length != 1); //checks to see if the users input is a letter and the length is no longer than 1

		//returns the users guess back to the main game loop
		return guess;
	}
}

void displayHelp()
{
	//displays lots of information about the game
	std::cout << "---HELP---\n" << std::endl;
	std::cout << "This is Hangman!" << std::endl;
	std::cout << "In this game you must correctly guess the letters of a hidden word to \nprevent the man being hanged.";
	std::cout << " But beware! If you get too many incorrect \nguesses the executioner will slowly hang the man up.\n";

	std::cout << "\nYou can input '1' on the menu to start the game or input '3' to access \nthe options and change how the game works.";
	std::cout << "\n\nOn the options menu, you can choose from various difficulties and \ndifferent themes of your choice.";
	std::cout << " Changing these options will affect the \nwords that you will have to guess in order to save the man.\n";
	
	std::cout << "\nWhen you input '1' on the menu and begin the game you will be shown a \nscreen displaying various information.";
	std::cout << "\n\n'Game Mode' shows what theme/difficulty the game has been set to.\n\n'Score' shows how many points you have accumulated by correctly \nguessing the words.";
	std::cout << "\n\n'Wrong guesses' shows all of the letters you have tried to enter thus \nfar but weren't in the correct word.\n\nBelow that is the gallows which shows the state of execution - meaning \nthe amount of guesses you have left.\n";
	std::cout << "\nThe input box below all of that is where you put the letters that you \nthink are in the hidden word. \n\nGood luck! Try and get a high score!\n";

	std::cout << "\nHint: You can enter 9 when guessing letters of a word to reveal \nexactly how many guesses you have left." << std::endl;
	std::cout << "\n---HELP---" << std::endl;

	std::cout << "\nPress enter to return to the menu." << std::endl;
	std::cin.get();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	system("cls");

}

void displayGallows(char hiddenWord[], char revealedWord[], int &wordLength, int &guessesRemaining, bool &displayGuesses, int &score, char wrongLetters[], int &gameMode)
{
	//displays the current game mode whilst the user is guessing the word
	switch (gameMode)
	{
		case 1:
		{
			std::cout << "Game mode: Easy" << std::endl;
			break;
		}

		case 2:
		{
			std::cout << "Game mode: Normal" << std::endl;
			break;
		}

		case 3:
		{
			std::cout << "Game mode: Hard" << std::endl;
			break;
		}

		case 4:
		{
			std::cout << "Game mode: Cities of The World" << std::endl;
			break;
		}

		case 5:
		{
			std::cout << "Game mode: Video Game Characters" << std::endl;
			break;
		}

		case 6:
		{
			std::cout << "Game mode: Food and Drinks" << std::endl;
			break;
		}

		case 7:
		{
			std::cout << "Game mode: Very Hard" << std::endl;
			break;
		}

		default:
		{
			std::cout << "Error in showing game mode" << std::endl;
		}
	}

	//displays the current score and letters that have been guesses wrongly
	std::cout << "Score: " << score << "\t" << "Wrong guesses: " << wrongLetters << std::endl;

	//displays the amount of the hidden word that has been revealed
	std::cout << "Guess the word: " << revealedWord << std::endl;

	//displays the state of the hanging man's execution
	switch (guessesRemaining)
	{
		case 6:
		{
			std::cout << "\t   ________  " << std::endl;
			std::cout << "\t   | /    |  " << std::endl;
			std::cout << "\t   |/        " << std::endl;
			std::cout << "\t   |         " << std::endl;
			std::cout << "\t   |         " << std::endl;
			std::cout << "\t   |         " << std::endl;
			std::cout << "\t   |         " << std::endl;
			std::cout << "\t__ | ______  " << std::endl;
			break;
		}

		case 5:
		{
			std::cout << "\t   ________  " << std::endl;
			std::cout << "\t   | /    |  " << std::endl;
			std::cout << "\t   |/    (_) " << std::endl;
			std::cout << "\t   |         " << std::endl;
			std::cout << "\t   |         " << std::endl;
			std::cout << "\t   |         " << std::endl;
			std::cout << "\t   |         " << std::endl;
			std::cout << "\t__ | ______  " << std::endl;
			break;
		}

		case 4:
		{
			std::cout << "\t   ________  " << std::endl;
			std::cout << "\t   | /    |  " << std::endl;
			std::cout << "\t   |/    (_) " << std::endl;
			std::cout << "\t   |      |  " << std::endl;
			std::cout << "\t   |      |  " << std::endl;
			std::cout << "\t   |         " << std::endl;
			std::cout << "\t   |         " << std::endl;
			std::cout << "\t__ | ______  " << std::endl;
			break;
		}

		case 3:
		{
			std::cout << "\t   ________  " << std::endl;
			std::cout << "\t   | /    |  " << std::endl;
			std::cout << "\t   |/    (_) " << std::endl;
			std::cout << "\t   |    \\ |  " << std::endl;
			std::cout << "\t   |      |  " << std::endl;
			std::cout << "\t   |         " << std::endl;
			std::cout << "\t   |         " << std::endl;
			std::cout << "\t__ | ______  " << std::endl;
			break;
		}

		case 2:
		{
			std::cout << "\t   ________  " << std::endl;
			std::cout << "\t   | /    |  " << std::endl;
			std::cout << "\t   |/    (_) " << std::endl;
			std::cout << "\t   |    \\ | /" << std::endl;
			std::cout << "\t   |      |  " << std::endl;
			std::cout << "\t   |         " << std::endl;
			std::cout << "\t   |         " << std::endl;
			std::cout << "\t__ | ______  " << std::endl;
			break;
		}

		case 1:
		{
			std::cout << "\t   ________  " << std::endl;
			std::cout << "\t   | /    |  " << std::endl;
			std::cout << "\t   |/    (_) " << std::endl;
			std::cout << "\t   |    \\ | /" << std::endl;
			std::cout << "\t   |      |  " << std::endl;
			std::cout << "\t   |     /   " << std::endl;
			std::cout << "\t   |         " << std::endl;
			std::cout << "\t__ | ______  " << std::endl;
			break;
		}

		case 0:
		{
			std::cout << "\t   ________  " << std::endl;
			std::cout << "\t   | /    |  " << std::endl;
			std::cout << "\t   |/    (_) " << std::endl;
			std::cout << "\t   |    \\ | /" << std::endl;
			std::cout << "\t   |      |  " << std::endl;
			std::cout << "\t   |     / \\ " << std::endl;
			std::cout << "\t   |         " << std::endl;
			std::cout << "\t__ | ______  " << std::endl;
			break;
		}

		default:
		{
			//this message will only appear is there is a problem with displaying the gallows
			std::cout << "Error in displaying gallows" << std::endl;
		}
	}

	//displays the exact guesses remaining before the man is hung if the option was turned on
	if (displayGuesses == true)
	{
		if (guessesRemaining == 1)
		{
			std::cout << "\t" << guessesRemaining << " guess remaining." << std::endl;
		}
		else
		{
			std::cout << "\t" << guessesRemaining << " guesses remaining." << std::endl;
		}
	}
}

int checkLetter(char hiddenWord[], char revealedWord[], int wordLength, int guessesRemaining, char guess, char wrongLetters[], int &nextLtr)
{
	//creates variables to check if the guessed letter is correct or if it's a repeated letter that has already been used
	bool isCorrect = false;
	bool repeatedLetter = false;

	//checks to see if the letter is correct and/or a repeated letter
	for (int i = 0; i < wordLength; ++i)
	{
		if (guess == hiddenWord[i])
		{
			isCorrect = true;

			if (guess == revealedWord[i])
			{
				repeatedLetter = true;
			}
			else
			{
				revealedWord[i] = hiddenWord[i];
			}
		}
	}

	//if the guessed letter is found to be correct then it will enter this statement
	if (isCorrect == true)
	{
		//if the letter is found to be a repeat then the user will be informed and one guess will be removed
		if (repeatedLetter == true)
		{
			std::cout << "\n\tINCORRECT" << std::endl;
			std::cout << "You've already found that letter." << std::endl;
			--guessesRemaining;
			std::cout << "\nPress enter to continue." << std::endl;

			std::cin.get();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
			if (repeatedLetter == false) //if the letter is not a repeat then it is correct and the user is informed
			{
				std::cout << "\n\tCORRECT" << std::endl;
				std::cout << "\"" << guess << "\"" << " is a part of the word." << std::endl;
				std::cout << "\nPress enter to continue." << std::endl;

				std::cin.get();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
	}
	else
		if (isCorrect == false) //if the letter is not correct then the user will be informed and a guess will be removed
		{
			std::cout << "\n\tINCORRECT" << std::endl;
			std::cout << "\"" << guess << "\"" << " is not a part of the word." << std::endl;
			--guessesRemaining;

			//adds the incorrect letter to the list of wrongly guessed letters
			wrongLetters[nextLtr] = guess;
			wrongLetters[nextLtr + 1] = ' ';
			nextLtr += 2;
			
			std::cout << "\nPress enter to continue." << std::endl;

			std::cin.get();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

	//returns the amount of guesses remaining to the main game loop
	return guessesRemaining;
}

void exitGame()
{
	//displays a message when the user decides to exit the game
	std::cout << "Exiting game... Thank you for playing!" << std::endl;

	std::cin.get();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int checkWin(char hiddenWord[], char revealedWord[], int &guessesRemaining, int &score, int &gameMode, bool &secretUnlocked, bool &displayGuesses, int &wordLength, char wrongLetters[])
{
	int decider;

	//checks to see if the user has run out of guesses
	if (guessesRemaining <= 0)
	{
		//clears the screen and redisplays the gallows whilst also informing the user that they have lost
		system("cls");
		displayGallows(hiddenWord, revealedWord, wordLength, guessesRemaining, displayGuesses, score, wrongLetters, gameMode);
		std::cout << "You've run out of guesses. Game Over." << std::endl;
		std::cout << "The word was " << hiddenWord << "." << std::endl;

		//reduces the users score based on which game mode is currently being used
		switch (gameMode)
		{
			case 1:
			{
				--score;
				break;
			}

			case 2:
			{
				score -= 2;
				break;
			}

			case 3:
			{
				score -= 4;
				break;
			}

			case 4:
			{
				score -= 2;
				break;
			}

			case 5:
			{
				score -= 2;
				break;
			}

			case 6:
			{
				score -= 2;
				break;
			}

			case 7:
			{
				score -= 10;
				break;
			}

			default:
			{
				//this message will only appear is there's a problem with reducing the user's score
				std::cout << "Error in score reduction" << std::endl;
			}
		}

		//change the decider to 5 so that it can exit the game loop
		decider = 5;
		return decider;
	}

	//checks to see if the winning conditions are met
	if (guessesRemaining > 0 && strcmp(hiddenWord, revealedWord) == 0)
	{
		//updates the gallows and shows a winning message to the user
		system("cls");
		displayGallows(hiddenWord, revealedWord, wordLength, guessesRemaining, displayGuesses, score, wrongLetters, gameMode);
		std::cout << "You win!" << std::endl;
		std::cout << "The completed word is " << revealedWord << "." << std::endl;

		//increases the user's score based on the game mode that is currently being used
		switch (gameMode)
		{
			case 1:
			{
				++score;
				break;
			}

			case 2:
			{
				score += 2;
				break;
			}

			case 3:
			{
				score += 4;
				break;
			}

			case 4:
			{
				score += 2;
				break;
			}

			case 5:
			{
				score += 2;
				break;
			}

			case 6:
			{
				score += 2;
				break;
			}

			case 7:
			{
				score += 10;
				break;
			}

			default:
			{
				//this message will only display if there's a problem with increasing the user's score
				std::cout << "Error in score increasing" << std::endl;
			}
		}

		//displays a special message and unlocks Very Hard mode if the user obtains 15 or more score
		if (score >= 15 && secretUnlocked == false)
		{
			std::cout << "\nPsst... Hey you. You've unlocked a new secret mode in the options menu." << std::endl;
			std::cout << "You should go check it out. Good luck..." << std::endl;
			secretUnlocked = true;
		}

		//changes the decider to 5 so that it can exit the game loop
		decider = 5;
		return decider;
	}

	//changes the decider to 1 so that it continues looping until it finds that the user has won or lost
	decider = 1;
	return decider;
}