/* 
 Game logic : you have to guess a werd knowing if
 each letter is well placed, wrongly placed or absent.
*/

#pragma once
#include <string>

using FString = std::string;
using int32 = int;

enum class EWordStatus
{
	Ok,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

struct FBullsCowsCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullsNCowsGame
{
public:
	FBullsNCowsGame();
	~FBullsNCowsGame();

	int32 GetCurrentTry() const;
	int32 GetMaxTries() const;
	bool IsGameWon() const;
	int32 GetHiddenWordLength() const;
	bool CheckGuessValidity(FString) const;

	void Reset();
	EWordStatus CheckGuessValidity(FString);
	FBullsCowsCount SubmitValidGuess(FString);

private:
	int32 CurrentTry;
	int32 MaxTries;
	FString HiddenWord;
	bool bIsGameWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

};
