//# represents a preprocessor directive
// #include copies-and-pastes other code
//			 use <> for standard libraries
//			 use " " for files created by myself

/*
 This is the console executable, that makes use of the BullCow class.
 This acts as the view in a MVC pattern, and is responsible for all user interaction.
 For game logic see the FBullCowGame class
*/

#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "FBullCowGame.h"


using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
int32 GetElegantInt(FString);

FBullCowGame BCGame; //instantiate a game, which we will re-use

//entry point of the application
int main()
{	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());
	
	return 0; //exit the app
}

//introduce the game
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;

	return;
}

void PlayGame()
{
	
	BCGame.Reset(GetElegantInt("Select the number of letters in the hidden words (1 - 9): "));
	
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I am thinking of?" << std::endl;
	std::cout << std::endl;
	
	int32 MaxTries = BCGame.GetMaxTries();
	
	//loop asking for guesses while the game is not WON  and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		//submit valid guess to the game, and receives counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls: " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows: " << BullCowCount.Cows << std::endl << std::endl;
	}
	
	PrintGameSummary();
	return;
}

//loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EWordStatus WordStatus = EWordStatus::Invalid_Status;
	do {
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() <<  ".  Enter your guess: ";
		
		std::getline(std::cin, Guess);

		WordStatus = BCGame.CheckGuessValidity(Guess);
		switch (WordStatus)
		{
		case EWordStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EWordStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default: //assuming the guess is valid
			break;
		}
	} while (WordStatus != EWordStatus::OK); //keep looping until get no errors

	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << std::endl << "Do you wanna play again with the same hidden word? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);

	return  (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary() 
{
	if (BCGame.IsGameWon())
		std::cout << "WELL DONE! You won!\n";
	else
	{
		std::cout << "Better luck next time!\n";
	}
}

int32 GetElegantInt(FString message)
{
	int32 result = 0;
	while (true)
	{ 
		FString input = "";
		std::cout << message;
		
		std::getline(std::cin, input);
		std::stringstream mystream(input);
		if (mystream >> result)
		{
			if (result > 0)
				break;
		}
		std::cout << "Not a valid option!\n\n";
	}
	std::cout << std::endl;
	return result;
}