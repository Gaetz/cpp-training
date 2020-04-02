/* Console executable that makes use of BullsNCows game class
It is responsible for all views and user int32eraction.
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullsNCowsGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void GuessGame();
FText GetValidGuess();
void PrintGameSummary();
void PrintWin();
void PrintLoss();
void PrintGuess(FText);
bool bAskToPlayAgain();

FBullsNCowsGame Game;

// Main program
int32 main()
{
	PrintIntro();
	do {
		GuessGame();
	} while (bAskToPlayAgain());

	return 0;
}

// Introduce game
void PrintIntro() {
	std::cout << "Bienvenue dans Bulls and Cows" << std::endl;
	std::cout << "Parviendras-tu à deviner à quel mot de " << Game.GetHiddenWordLength() << " lettres je pense ?" << std::endl;
	std::cout << std::endl;
	return;
}

// Main loop
void GuessGame()
{
	Game.Reset();
	// Loop while game is now won and there are tries left
	while (!Game.IsGameWon() && Game.GetCurrentTry() < Game.GetMaxTries())
	{
		FText Guess = GetValidGuess();

		// Submit guess to the game
		FBullsCowsCount Count = Game.SubmitValidGuess(Guess);
		// Print result
		std::cout << "Bulls: " << Count.Bulls << std::endl;
		std::cout << "Cows: " << Count.Cows << std::endl;
		// Reminder
		PrintGuess(Guess);
	}
	PrintGameSummary();
	return;
}

// Loop until getting a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EWordStatus EStatus = EWordStatus::Not_Isogram;
	do
	{
		std::cout << "Essai " << Game.GetCurrentTry() << " sur " << Game.GetMaxTries() <<". Entre ta proposition : ";
		getline(std::cin, Guess);

		// Check guess validity
		EStatus = Game.CheckGuessValidity(Guess);
		switch (EStatus)
		{
		case EWordStatus::Not_Isogram:
			std::cout << "Le mot ne doit pas contenir de lettre qui se repète." << std::endl;
			break;
		case EWordStatus::Wrong_Length:
			std::cout << "Entrez un mot de " << Game.GetHiddenWordLength() << " lettres." << std::endl;
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "Le mot doit être en minuscule." << std::endl;
			break;
		default:
			break;
		}
	} while (EStatus != EWordStatus::Ok);
	std::cout << std::endl;
	return Guess;
}

// Remind player their guess
void PrintGuess(FText guess)
{
	std::cout << "Tu as proposé : " << guess << std::endl;
	std::cout << std::endl;
}

// Play result
void PrintGameSummary()
{
	if (Game.IsGameWon())
		PrintWin();
	else
		PrintLoss();
}

// Win result
void PrintWin()
{
	std::cout << "BRAVO !!!Tu as trouvé :)" << std::endl;
	std::cout << std::endl;
}

// Loss result
void PrintLoss()
{
	std::cout << "Tu as épuisé tout tes essais. C'est une terrible défaite." << std::endl;
	std::cout << std::endl;
}

// Will the player play again ?
bool bAskToPlayAgain()
{
	FText DoesWantToPlay = "";
	std::cout << "Souhaites-tu jouer encore ? (O/N)" << std::endl;
	std::getline(std::cin, DoesWantToPlay);
	if (DoesWantToPlay[0] == 'O' || DoesWantToPlay[0] == 'Y' || DoesWantToPlay[0] == 'o' || DoesWantToPlay[0] == 'y')
	{
		std::cout << std::endl;
		return true;
	}
	return false;
}
