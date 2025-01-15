#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

// Function to read high score from file
int getHighScore() {
    ifstream inFile("highscore.txt");
    int score = 999; // Default high score if file doesn't exist
    
    if (inFile.is_open()) {
        inFile >> score;
        inFile.close();
    }
    return score;
}

// Function to save high score to file
void saveHighScore(int score) {
    ofstream outFile("highscore.txt");
    if (outFile.is_open()) {
        outFile << score;
        outFile.close();
    }
}

int main() {
    // Variables
    int number, guess, attempts;
    char playAgain;
    int highScore = getHighScore(); // Read high score from file
    
    // Seed the random number generator
    srand(time(0));
    
    do {
        // Generate random number between 1 and 100
        number = rand() % 100 + 1;
        attempts = 0;
        
        cout << "\n=== Welcome to the Number Guessing Game! ===\n";
        cout << "Current High Score: " << highScore << " attempts\n";
        cout << "I have chosen a number between 1 and 100.\n";
        
        do {
            // Get player's guess
            cout << "\nEnter your guess: ";
            cin >> guess;
            attempts++;
            
            // Provide feedback
            if (guess > number) {
                cout << "Too high! Try again.\n";
            } else if (guess < number) {
                cout << "Too low! Try again.\n";
            } else {
                cout << "\nCongratulations! You guessed it in " << attempts << " attempts!\n";
                
                // Update high score
                if (attempts < highScore) {
                    highScore = attempts;
                    cout << "New High Score: " << highScore << " attempts!\n";
                    saveHighScore(highScore); // Save new high score to file
                }
            }
            
        } while (guess != number);
        
        // Ask to play again
        cout << "\nWould you like to play again? (y/n): ";
        cin >> playAgain;
        
    } while (playAgain == 'y' || playAgain == 'Y');
    
    cout << "\nThanks for playing! Best score: " << highScore << " attempts\n";
    return 0;
}
