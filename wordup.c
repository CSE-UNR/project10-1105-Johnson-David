//Author: Davie Johnson
//Purpose: Project 10

#include <stdio.h>
#include <stdbool.h>

#define WORD_LENGTH 5
#define MAX_ATTEMPTS 6

bool loadMysteryWord(char *word);
bool isValidGuess(const char *guess);
void convertToLowercase(char *word);
void displayPreviousGuesses(char guesses[][WORD_LENGTH + 1], int numGuesses, const char *mysteryWord);
void compareWords(const char *guess, const char *mystery, char *result);
bool isGameWon(const char *guess, const char *mysteryWord);
void displayGameResult(bool won, const char *mysteryWord, int attempts);
void clearInputBuffer();
int stringLength(const char *str);
bool isAlpha(char c);
void stringCopy(char *dest, const char *src);
int stringCompare(const char *s1, const char *s2);

int main(){
    char mysteryWord[WORD_LENGTH + 1];
    char guesses[MAX_ATTEMPTS][WORD_LENGTH + 1];
    char currentGuess[100];
    int attempts = 0;
    bool gameWon = false;

    if(!loadMysteryWord(mysteryWord)){
        printf("Error loading mystery word. Exiting program.\n");
        return 1;
    }

    while(attempts < MAX_ATTEMPTS && !gameWon){
        printf("GUESS %d! Enter your guess: ", attempts + 1);
        if(scanf("%99s", currentGuess) != 1){
            clearInputBuffer();
            printf("Invalid input. Please try again.\n");
            continue;
        }

        if(!isValidGuess(currentGuess)){
            printf("Your guess must be %d letters long.\nPlease try again: ", WORD_LENGTH);
            continue;
        }

        convertToLowercase(currentGuess);
        
        stringCopy(guesses[attempts], currentGuess);
        attempts++;

        displayPreviousGuesses(guesses, attempts, mysteryWord);

        if(isGameWon(currentGuess, mysteryWord)){
            gameWon = true;
        }
    }

    displayGameResult(gameWon, mysteryWord, attempts);
        
    return 0;
}

bool loadMysteryWord(char *word){
    FILE *file = fopen("word.txt", "r");
    if(file == NULL){
        return false;
    }

    if(fscanf(file, "%5s", word) != 1){
        fclose(file);
        return false;
    }

    fclose(file);
    convertToLowercase(word);
    return true;
}

int stringLength(const char *str){
    int length = 0;
    while(str[length] != '\0'){
        length++;
    }
    return length;
}


bool isAlpha(char c){
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

void stringCopy(char *dest, const char *src){
    int i = 0;
    while(src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int stringCompare(const char *s1, const char *s2){
    int i = 0;
    while(s1[i] != '\0' && s2[i] != '\0'){
        if(s1[i] != s2[i]){
            return s1[i] - s2[i];
        }
        i++;
    }
    return s1[i] - s2[i];
}

bool isValidGuess(const char *guess) {
    int length = stringLength(guess);
    if(length != WORD_LENGTH){
        return false;
    }

    for(int i = 0; i < length; i++){
        if(!isAlpha(guess[i])){
            return false;
        }
    }

    return true;
}

void convertToLowercase(char *word){
    for(int i = 0; word[i]; i++){
        if(word[i] >= 'A' && word[i] <= 'Z'){
            word[i] = word[i] + 32;
            }
    }
}

void displayPreviousGuesses(char guesses[][WORD_LENGTH + 1], int numGuesses, const char *mysteryWord) {
    printf("================================\n");
    
    for(int i = 0; i < numGuesses; i++){
        char result[WORD_LENGTH * 2 + 1] = {0};
        
        compareWords(guesses[i], mysteryWord, result);
        
        for(int j = 0; j < WORD_LENGTH; j++){
            if(guesses[i][j] == mysteryWord[j]){
                if(guesses[i][j] >= 'a' && guesses[i][j] <= 'z'){
                    printf("%c", guesses[i][j] - 32);
                } else{
                    printf("%c", guesses[i][j]);
                }
            } else{
                printf("%c", guesses[i][j]);
            }
        }
        printf("\n%s\n", result);
    }
}

void compareWords(const char *guess, const char *mystery, char *result){
    bool letterUsed[WORD_LENGTH] = {false};

    for(int i = 0; i < WORD_LENGTH; i++){
        if(guess[i] == mystery[i]){
            letterUsed[i] = true;
            result[i] = ' ';
        } else{
            result[i] = ' ';
        }
    }
    
    for(int i = 0; i < WORD_LENGTH; i++){
        if(guess[i] != mystery[i]){
            bool found = false;
            
            for(int j = 0; j < WORD_LENGTH && !found; j++){
                if(!letterUsed[j] && guess[i] == mystery[j]){
                    result[i] = '^';
                    letterUsed[j] = true;
                    found = true;
                }
            }
        }
    }
}

bool isGameWon(const char *guess, const char *mysteryWord){
    return stringCompare(guess, mysteryWord) == 0;
}

void displayGameResult(bool won, const char *mysteryWord, int attempts){
    if(won){
        printf("================================");
        printf("\n		%s\n", mysteryWord);
        printf("	You won in %d guesses!\n", attempts);
        
        if(attempts == 1){
            printf("		GOATED!\n");
        }
        else if(attempts == 2 || attempts == 3){
            printf("		Amazing!\n");
        }
        else if(attempts == 4 || attempts == 5){
            printf("		Nice!\n");
        }
    } else {
        printf("================================");
        printf("\nYou lost, better luck next time!\n");
    }
}

void clearInputBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
