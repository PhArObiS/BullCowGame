// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms = GetValidWords(Words);

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

    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = HiddenWord.Len() * 2;
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    // PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); // Debug Line
    UE_LOG(LogTemp, Warning, TEXT("The HiddenWord is: %s."), *HiddenWord); // Debug Line
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue..."));

}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord)
    {
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
        LoseGame();
        return;
    }

    // Show the Bulls and Cows
    FBullCowCount Score = GetBullCows(Guess);

    PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);
    PrintLine(TEXT("You have %i lives remaining."), Lives);
        
}

void UBullCowCartridge::WinGame()
{
    ClearScreen();
    bGameOver = true;
    PrintLine(TEXT("You Win! \nPress Enter to play again..."));
}

void UBullCowCartridge::LoseGame()
{
    ClearScreen();
    bGameOver = true;
    PrintLine(TEXT("You Lose! \nPress Enter to play again..."));
}

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

FBullCowCount UBullCowCartridge::GetBullCows(const FString &Guess) const
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue; // Skip to the next iteration

        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break; // Skip to the next GuessIndex
            }
        }
    }

    return Count;
}