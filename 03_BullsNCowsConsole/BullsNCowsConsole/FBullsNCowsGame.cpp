#include "FBullsNCowsGame.h"
#include <map>
#include <algorithm>
#define TMap std::map

int32 FBullsNCowsGame::GetCurrentTry() const { return CurrentTry; }
int32 FBullsNCowsGame::GetMaxTries() const { return MaxTries; }
bool FBullsNCowsGame::IsGameWon() const { return bIsGameWon; }

FBullsNCowsGame::FBullsNCowsGame()
{
	Reset();
}

FBullsNCowsGame::~FBullsNCowsGame()
{
}


int32 FBullsNCowsGame::GetHiddenWordLength() const
{
	return static_cast<int32>(HiddenWord.length());
}

void FBullsNCowsGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "magic"; // Must be an isogram (no repeated letter)

	bIsGameWon = false;
	HiddenWord = HIDDEN_WORD;
	CurrentTry = 1;
	MaxTries = MAX_TRIES;
	return;
}

EWordStatus FBullsNCowsGame::CheckGuessValidity(FString Guess)
{
	// Not an isogram error
	if (!IsIsogram(Guess)) {
		return EWordStatus::Not_Isogram;
	}
	// Wrong length error
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EWordStatus::Wrong_Length;
	}
	// Not lowercase error
	else if (!IsLowercase(Guess)) {
		return EWordStatus::Not_Lowercase;
	}
	// Seems ok 
	return EWordStatus::Ok;
}

// receives a VALID guess, incrementsturn and return counts
FBullsCowsCount FBullsNCowsGame::SubmitValidGuess(FString Guess)
{
	CurrentTry++;
	// Loop through all letters in the hidden word and compare
	int32 WordLength = GetHiddenWordLength();
	FBullsCowsCount Count;
	// Assume Guess and HiddenWord have same length
	for (int32 i = 0; i < WordLength; i++)
	{
		for (int32 j = 0; j < WordLength; j++)
		{
			// If letters match, increment bulls if they are at the same place, cows else
			if (HiddenWord[i] == Guess[j])
			{
				if (i == j)
					Count.Bulls++;
				else
					Count.Cows++;
			}
		}
	}
	// Set win condition
	bIsGameWon = (Count.Bulls == WordLength);
	// return result
	return Count;
}

// Check if a word is an isogram (no repeated letter)
bool FBullsNCowsGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1) return true;

	TMap<char, bool> map;
	FString SortedGuess = Guess;
	std::sort(SortedGuess.begin(), SortedGuess.end());
	for (auto letter : SortedGuess) 
	{
		// If letter was never encountered, ok, else guess is not an isogram
		if (!map[letter])
			map[letter] = true;
		else
			return false;
	}
	return true;
}

// Check if guess is lowercase
bool FBullsNCowsGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter)) return false;
	}
	return true;
}
