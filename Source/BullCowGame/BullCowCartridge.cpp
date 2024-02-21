// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();  
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else // Checking PlayerGuess
    {
        ProcessGuess(PlayerInput);
    }


}

void UBullCowCartridge::SetupGame() 
{
    // Welcoming the Player
    PrintLine(TEXT("Welcome to Bulls and Cows!"));

    HiddenWord = GetValidWords(Words)[FMath::RandRange(0, GetValidWords(Words).Num() - 1)];
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue..."));
    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); // Debug Line

}

void UBullCowCartridge::EndGame() 
{
    bGameOver = true;
    PrintLine(TEXT("Press Enter to play again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have won!"));
        // WinGame();
        EndGame();
        return;
    }
    
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The Hidden Word is %i characters long, try again!"), HiddenWord.Len());
        PrintLine(TEXT("You have %i lives remaining."), Lives);
        return;
    }

    // Check if Isogram
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again!"));
        return;
    }

    // Remove Life
    PrintLine(TEXT("You have lost a life!"));
    --Lives;

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The Hidden Word was: %s"), *HiddenWord);
        // LoseGame();
        EndGame();
        return;
    }

    // Show Lives
    PrintLine(TEXT("You have %i lives remaining."), Lives);
        
}

// void UBullCowCartridge::WinGame()
// {
//     bGameOver = true;
//     PrintLine(TEXT("You have reached my Win Screen! \nPress Enter to play again..."));
//     if (bGameOver)
//     {
//         ClearScreen();
//         SetupGame();
//     }
// }

// void UBullCowCartridge::LoseGame()
// {
//     bGameOver = true;
//     PrintLine(TEXT("You have reached my Lose Screen! \nPress Enter to play again..."));
//     if (bGameOver)
//     {
//         ClearScreen();
//         SetupGame();
//     }
// }

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;
    
    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
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
