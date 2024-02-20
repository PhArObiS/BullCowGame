// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();  

    PrintLine(TEXT("The number of possible words is: %i."), Words.Num()); // Debug Line  
    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); // Debug Line

    // TArray<FString> ValidWords;

    // for (int32 Index = 0; Index < 10; Index++)
    // {
    //     if (Words[Index].Len() >= 4 && Words[Index].Len() <= 8)
    //     {
    //         ValidWords.Emplace(Words[Index]);
    //         // PrintLine(TEXT("%s"), *Words[Index]);
    //     }
    // }

    // for (int32 Index = 0; Index < ValidWords.Num(); Index++)
    // {
    //     PrintLine(TEXT("%s"), *ValidWords[Index]);
    // }
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
    PrintLine(TEXT("Press Enter to play again..."));
    // if (bGameOver)
    // {
    //     ClearScreen();
    //     SetupGame();
    // }
    
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
    
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The Hidden Word is %i characters long, try again!"), HiddenWord.Len());
        PrintLine(TEXT("You have %i lives remaining."), Lives);
        return;
    }

    // Check if Isogram
    if (!isIsogram(Guess))
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
        EndGame();
        LoseGame();
        return;
    }

    // Show Lives
    PrintLine(TEXT("You have %i lives remaining."), Lives);
        
}

void UBullCowCartridge::WinGame()
{
    bGameOver = true;
    PrintLine(TEXT("You have reached my Win Screen! \nPress Enter to play again..."));
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
}

void UBullCowCartridge::LoseGame()
{
    bGameOver = true;
    PrintLine(TEXT("You have reached my Lose Screen! \nPress Enter to play again..."));
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
}

bool UBullCowCartridge::isIsogram(const FString Word)
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

void UBullCowCartridge::GetValidWords(const TArray<FString> Words)
{
    for (int32 Index = 0; Index < Words.Num(); Index++)
    {
        if (Words[Index].Len() >= 4 && Words[Index].Len() <= 8)
        {
            PrintLine(TEXT("%s"), *Words[Index]);
        }
    }
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
