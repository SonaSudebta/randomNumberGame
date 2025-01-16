#include <cmath>	 // For abs()
#include <cstdlib>	 // For rand() and srand()
#include <ctime>	 // For time()
#include <fstream>	 // For file I/O
#include <iostream>	 // For cin, cout

using namespace std;  // Using the standard namespace

// Function to read high score from file
int getHighScore() {
	// Open file for reading
	ifstream inFile("highscore.txt");

	int score = 999;  // Default high score if file doesn't exist

	if (inFile.is_open()) {
		inFile >> score;
		inFile.close();
	}
	return score;
}

// Function to save high score to file
void saveHighScore(int score) {
	// Open file for writing
	ofstream outFile("highscore.txt");

	if (outFile.is_open()) {
		outFile << score;
		outFile.close();
	}
}

// Function to give hot/cold hint based on difference
string getTemperatureHint(int difference, int lastDifference) {
	// Define temperature ranges
	if (difference == 0)
		return "You got it!";

	string hint;

	// Determine how hot/cold based on absolute distance
	if (difference <= 5)
		hint = "Very Hot!";
	else if (difference <= 10)
		hint = "Hot!";
	else if (difference <= 20)
		hint = "Warm";
	else if (difference <= 40)
		hint = "Cold";
	else
		hint = "Very Cold!";

	// Add getting warmer/colder if not first guess
	if (lastDifference != -1) {	 // -1 indicates first guess
		// Compare current difference to last difference
		if (difference < lastDifference) {
			hint += " (Getting Warmer!)";
		} else if (difference > lastDifference) {
			hint += " (Getting Colder!)";
		}
	}

	return hint;
}

int main() {
	// Variables
	int number, guess, attempts;
	char playAgain;
	int highScore = getHighScore();	 // Get high score from file
	int lastDifference = -1;		 // Track last guess difference

	// Seed the random number generator
	srand(time(0));

	// Main game loop (including messages)
	do {
		number = rand() % 100 + 1;	// Generate random number between 1 and 100
		attempts = 0;				// Reset attempts
		lastDifference = -1;		// Reset for new game

		// Display welcome message
		cout << "\n=== Welcome to the Number Guessing Game! ===\n";
		cout << "Current High Score: " << highScore << " attempts\n";
		cout << "I have chosen a number between 1 and 100.\n";
		cout << "I'll tell you if you're hot or cold!\n";

		// Game loop
		do {
			// Get player's guess
			cout << "\nEnter your guess: ";
			cin >> guess;
			attempts++;	 // Increment attempts

			int difference = abs(guess - number);  // Calculate difference from target

			// Get temperature hint
			string hint = getTemperatureHint(difference, lastDifference);
			cout << hint << "\n";

			// Store current difference for next comparison
			lastDifference = difference;

			// If correct guess
			if (difference == 0) {
				// Display number of attempts
				cout << "\nCongratulations! You guessed it in " << attempts << " attempts!\n";

				// Update high score
				if (attempts < highScore) {
					highScore = attempts;  // Update high score
					cout << "New High Score: " << highScore << " attempts!\n";
					saveHighScore(highScore);  // Save high score to file
				}
			}

		} while (guess != number);	// Repeat until correct guess

		// Ask to play again
		cout << "\nWould you like to play again? (y/n): ";
		cin >> playAgain;

	} while (playAgain == 'y' || playAgain == 'Y');	 // Repeat if 'y' or 'Y'

	// Display goodbye message
	cout << "\nThanks for playing!\nBest score: " << highScore << " attempts\n";
	return 0;
}