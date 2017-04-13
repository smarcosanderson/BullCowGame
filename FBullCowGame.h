/*
This acts as a Model in the MVC pattern
This class is reponsible for the game logic definition for implementation see the .cpp file
*/

#pragma once
#include <string>

using FString = std::string;
using int32 = int;


struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EWordStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame
{
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EWordStatus CheckGuessValidity(FString) const;

	void Reset(int32); 
	FBullCowCount SubmitValidGuess(FString);

private:
	//see constructor to initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bIsWonGame;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

	void DefineHiddenWord(int32);
};