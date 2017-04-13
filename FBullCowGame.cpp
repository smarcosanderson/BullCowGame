/*
This acts as a Controller in MVC pattern.
Here we implement the functionalities needed for the game.
*/

#pragma once

#include "FBullCowGame.h"
#include <algorithm>
#include <map>
#define TMap std::map

using int32 = int;



FBullCowGame::FBullCowGame() { Reset(0); } // Constructor 

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const { return bIsWonGame; }

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordToMaxTries{ {1,2}, {2,3}, {3,3}, {4,5}, {5,5}, {6,7}, {7,7}, {8,7}, {9,8} };
	return WordToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::Reset(int32 WordLength)
{
	//const FString HIDDEN_WORD = "planet";
	//MyHiddenWord = "";
	DefineHiddenWord(WordLength);
	MyCurrentTry = 1;
	bIsWonGame = false;
	return;
}

void FBullCowGame::DefineHiddenWord(int32 WordLength)
{
	TMap<int32, FString> HiddenWords = { {0, ""},
										{ 1,"g"},
										{ 2,"of" },
										{ 3,"tea" },
										{ 4,"case" },
										{ 5,"brief" },
										{ 6,"planet" },
										{ 7,"isogram" },
										{ 8,"algorism" },
										{ 9,"alchmists" } };

	MyHiddenWord = HiddenWords[std::max(std::min(WordLength, 9), 0)];
}

EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (Guess.length() != GetHiddenWordLength()) { return EWordStatus::Wrong_Length; }// if the guess length is wrong
	else if (!IsLowercase(Guess)) { return EWordStatus::Not_Lowercase; }// if the guess isnt lowercase
	else if (!IsIsogram(Guess)) { return EWordStatus::Not_Isogram; }// if the guess isnt isogram
	

	return EWordStatus::OK;

}

//receives a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length(); //assumin same length as guess

	// loop through all letters in the hidden word
	for (int32 i = 0; i < WordLength; i++)
	{
		// compare letters against the guess
		for (int32 j = 0; j < WordLength; j++)
		{
			//if they match
			if (MyHiddenWord[i] == Guess[j])
			{
				BullCowCount.Bulls += (i == j) ? 1 : 0;//increment bulls it they're same place
				BullCowCount.Cows += (i == j) ? 0 : 1;//increment cows if not
			}
		}
	}

	if (BullCowCount.Bulls == WordLength)
		bIsWonGame = true;

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//consider 0 or 1 word length as isogram
	if (Word.length() < 2) return true;

	//setup a map
	TMap<char, bool> LetterSeen;
	//loop through the letters of the guess word
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (!LetterSeen[Letter])//if it is not in map
			LetterSeen[Letter] = true;//insert it on the map
		else
			return false; //break -> It is not an isogram
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	//consider 0 word lenth as lowercase
	if (Word.length() < 1) return true;

	for (auto Letter : Word)
	{
		if (isupper(Letter))
			return false;//break -> it is not lowercase
	}

	return true;
}
