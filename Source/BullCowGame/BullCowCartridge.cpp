// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();  
        
    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); // Debug Line
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }


}

void UBullCowCartridge::SetupGame()
{
    // Welcoming the Player
    PrintLine(TEXT("Welcome to Bulls and Cows!"));

    HiddenWord = TEXT("cakes");
    Lives = 4;
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess. \nPress Enter to continue..."));

}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("You have won! \nPress Enter to play again..."));
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    
}

void UBullCowCartridge::ProcessGuess(const FString Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have won!"));
        EndGame();
        WinGame();
        return;
    }
    else
    {
        PrintLine(TEXT("You have lost a life!"));
        if (Lives > 0)
        {
            if (Guess.Len() != HiddenWord.Len())
            {
                PrintLine(TEXT("Sorry, try again. You have %i lives remaining."), --Lives);
                PrintLine(TEXT("The Hidden Word is %i characters long."), HiddenWord.Len());
            }
        }
        else
        {
            PrintLine(TEXT("You have no lives left! \nThe hidden word was: %s. Game Over."), *HiddenWord);
            EndGame();
            LoseGame();
        }
    }
}

void UBullCowCartridge::WinGame()
{
    bGameOver = true;
    PrintLine(TEXT("You have won! \nPress Enter to play again..."));
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
}

void UBullCowCartridge::LoseGame()
{
    bGameOver = true;
    PrintLine(TEXT("You have lost! \nPress Enter to play again..."));
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
}

bool UBullCowCartridge::isIsogram(const FString Word) const
{
    return true;
}

// Prompt to guess again
// Check right number of characters
// Prompt to guess again
// Remove Life
// Check if Lives > 0
// If yes, GuessAgain
// Show Lives
// If Lives <= 0, show GameOver and HiddenWord?
// Prompt to play again, Press Enter to play again?
// Check user input
// Play again or quit
// ClearScreen();   
// EndGame();
