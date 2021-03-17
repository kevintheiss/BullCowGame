// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    GetValidWords(Words);
    SetupGame(); // Set up game

    PrintLine(TEXT("The number of possible words is: %i"), Words.Num());
    //PrintLine(TEXT("The first 5 words are: \n"));
    PrintLine(TEXT("The number of valid words is: %i."), GetValidWords(Words).Num());
    PrintLine(TEXT("The hidden word is: %s"), *HiddenWord); // Debug line

    //TArray<FString> ValidWords;

    /*for(int32 Index = 0; Index < 10; Index++)
    {
        if(Words[Index].Len() >= 4 && Words[Index].Len() <= 8)
        {
            ValidWords.Emplace(Words[Index]);
            //PrintLine(TEXT("%s"), *Words[Index]);
        }
    }

    for(int32 Index = 0; Index < ValidWords.Num(); Index++)
    {
        PrintLine(TEXT("%s."), *ValidWords[Index]);
    }*/
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    // if the game is over, ClearScreen() and SetupGame()
    // else check PlayerGuess
    if(bGameOver)
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
    bGameOver = false;
    HiddenWord = TEXT("cakes"); // Set the hidden word
    Lives = HiddenWord.Len();

    // Welcome the player
    // Prompt player for guess
    PrintLine(TEXT("Welcome to the Bull Cow game!"));
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i Lives"), Lives);
    PrintLine(TEXT("Type in your guess \nand press Enter to continue..."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    // Check PlayerGuess
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You win!"));
        EndGame();
        return;
    }

    // Check right number of characters
    if(Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i letters long."), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try again \nYou have %i Lives left."), Lives);
        return;
    }

    // Check if isogram
    if(!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters allowed, try again."));
        return;
    }

    // Prompt to guess again
    // Remove Life
    PrintLine(TEXT("Lost a life!"));
    --Lives;

    if(Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left \nYou lose..."));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
    }

    // Check if hidden word is correct
    // If hidden word is correct, print win message
    // If hidden word is incorrect, remove life
    // Check if lives are > 0
    // If yes, prompt player to guess again, repeat above steps
    // Show lives left
    // If no, print lose message
    // Ask if player wants to play again
    // Prompt to play again
    // If yes, play again
    // If no, quit game
    PrintLine(TEXT("Sorry, try again \nYou have %i Lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    for(int32 Index = 0; Index < Word.Len(); Index++)
    {
        for(int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if(Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }

    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordList) const
{
    TArray<FString> ValidWords;
    
    //for(int32 Index = 0; Index < WordList.Num(); Index++)
    //{
    for(FString Word : WordList)
    {
        if(Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }
    //}
    return ValidWords;
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress Enter to play again..."));
}