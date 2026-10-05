#include <iostream>   // Include iostream for input/output operations.
#include <cstdlib>    // Include cstdlib for system functions like clearing the screen.
#include <ctime>      // Include ctime for random number seeding.
using namespace std;  // Use the standard namespace to avoid prefixing std:: before standard functions.

// Enumeration: enGameChoice
// Purpose: Defines the choices available in the game.
enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

// Enumeration: enWinner
// Purpose: Defines possible winners for a round or game.
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

// Structure: stRoundInfo
// Purpose: Stores details of a single round of the game.
struct stRoundInfo
{
	short RoundNumber = 0;          // Round number.
	enGameChoice Player1Choice;     // Player's choice.
	enGameChoice ComputerChoice;    // Computer's choice.
	enWinner Winner;                // Stores the winner of the round.
	string WinnerName;               // Stores the winner's name.
};

// Structure: stGameResults
// Purpose: Stores overall game results after all rounds are played.
struct stGameResults
{
	short GameRounds = 0;        // Number of rounds played.
	short Player1WinTimes = 0;   // Count of Player1's wins.
	short ComputerWinTimes = 0;  // Count of Computer's wins.
	short DrawTimes = 0;         // Number of rounds that ended in a draw.
	enWinner GameWinner;         // Stores the overall game winner.
	string WinnerName = "";      // Name of the game winner.
};

// Function: RandomNumber
// Purpose: Generates a random number within the given range [From, To].
// Parameters:
//   - From: Lower bound of the random range.
//   - To: Upper bound of the random range.
// Returns: A random integer between From and To.
int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

// Function: GetComputerChoice
// Purpose: Randomly selects the computer's choice.
// Returns: An enGameChoice value representing the computer's move.
enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}

// Function: WhoWonTheRound
// Purpose: Determines the winner of a round based on player and computer choices.
enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	// If both choices are the same, it's a draw.
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
		return enWinner::Draw;

	// Determine the winner based on game rules.
	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Stone:
		return (RoundInfo.ComputerChoice == enGameChoice::Paper) ? enWinner::Computer : enWinner::Player1;
	case enGameChoice::Paper:
		return (RoundInfo.ComputerChoice == enGameChoice::Scissors) ? enWinner::Computer : enWinner::Player1;
	case enGameChoice::Scissors:
		return (RoundInfo.ComputerChoice == enGameChoice::Stone) ? enWinner::Computer : enWinner::Player1;
	}
}

// Function: WhoWonTheGame
// Purpose: Determines the final game winner based on win counts.
enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes) return enWinner::Player1;
	else if (ComputerWinTimes > Player1WinTimes) return enWinner::Computer;
	else return enWinner::Draw;
}

// Function: ChoiceName
// Purpose: Converts an enGameChoice enum to a string representation.
string ChoiceName(enGameChoice Choice)
{
	string arrGameChoices[3] = { "Stone", "Paper", "Scissors" };
	return arrGameChoices[Choice - 1];
}

// Function: WinnerName
// Purpose: Converts an enWinner enum to a string representation.
string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player1", "Computer", "No Winner (Draw)" };
	return arrWinnerName[Winner - 1];
}

// Function: ReadPlayer1Choice
// Purpose: Prompts the player to input their choice.
enGameChoice ReadPlayer1Choice()
{
	short Choice;
	do
	{
		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
		cin >> Choice;
	} while (Choice < 1 || Choice > 3);
	return (enGameChoice)Choice;
}

// Function: PrintRoundResults
// Purpose: Displays the results of a single round.
void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
	cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
	cout << "_________________________________________\n" << endl;
}

// Function: PlayGame
// Purpose: Runs the game for a given number of rounds and determines the final winner.
stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins:\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player1)
			Player1WinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResults(RoundInfo);
	}

	return { HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes, WhoWonTheGame(Player1WinTimes, ComputerWinTimes), WinnerName(WhoWonTheGame(Player1WinTimes, ComputerWinTimes)) };
}

// Function: StartGame
// Purpose: Controls the game loop, allowing players to replay the game.
void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		system("cls");  // Clear the screen before starting a new game.
		stGameResults GameResults = PlayGame(3); // Play 3 rounds.
		cout << "\nGame Over! Winner: " << GameResults.WinnerName << endl;

		cout << "\nDo you want to play again? (Y/N): ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

// Main Function
int main()
{
	srand((unsigned)time(NULL));  // Seed random number generator.
	StartGame();  // Start the game.
	return 0;  // Return 0 to indicate successful execution.
}

















/*


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;
enum Symbols { stone = 1, scissor = 2, paper = 3 };
enum Result { Player = 1, Computer = 2, Draw = 3 };

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}
int RoudTimes() {
	int Round = 0;
	cout << "Enter the number of rounds you want to play: ";
	cin >> Round;
	return Round;
}

Symbols PlayerChoice() {
	int choice;
	cout << "Enter your choice (1 for Stone, 2 for Scissor, 3 for Paper): ";
	cin >> choice;
	return Symbols(choice);
}

Symbols ComputerChoice() {

	return (Symbols)RandomNumber(1, 3);
}

string ReturnPlayersChoices(Symbols symbole) {

	if (symbole == Symbols::stone)
		return "Stone";
	else if (symbole == Symbols::scissor)
		return "Scissor";
	else
	{
		return "Paper";
	}
}

void PrintPlayerChoices(Symbols PlayerChoice , Symbols ComputerChoice)
{
	cout << "Player choice : [ " << ReturnPlayersChoices(PlayerChoice )<<" ]"<< endl;
	cout << "Computer choice : [ " << ReturnPlayersChoices(ComputerChoice)<<" ]"<< endl;

}


Result DetermineWinner(Symbols player, Symbols computer) {
	if (player == computer)
		return Result::Draw;

	if ((player == Symbols::stone && computer == Symbols::scissor) ||
		(player == Symbols::scissor && computer == Symbols::paper) ||
		(player == Symbols::paper && computer == Symbols::stone))
		return Result::Player;

	return Result::Computer;
}

void PrintResultEvryRound(Result Resultat) {

	switch (Resultat)
	{
	case Result::Player:
		system("color 2F");
		cout << "Round Winner : [Player]" << endl;
		break;
	case Result::Computer:
		system("color 4F");
		MessageBeep(MB_ICONERROR);
		cout << "Round Winner : [Computer]" << endl;
		break;
	case Result::Draw:
		system("color 6F");
		cout << "Round Winner : [Draw]" << endl;
		break;
	}


}
	
bool TryAgain() {
	char TryAgain = 'x';
	cout << "You wanna Try again Y/N\n";
	cin >> TryAgain;

	if (TryAgain == 'Y' || TryAgain == 'y')
		return true;
	else if (TryAgain == 'N' || TryAgain == 'n')
		return false;
	else
		return 0;
}
void PrintResult(int rounds){
	int WinnerPlayer = 0;
	int WinnerComputer = 0;
	int Draws = 0;
	do {

		for (int i = 1; i <= rounds; i++)
		{
			cout << "Round " << i << " begin" << endl;
			Symbols ChoiceUser = PlayerChoice();
			Symbols ChoiceComputer = ComputerChoice();

			Result resultat = DetermineWinner(ChoiceUser, ChoiceComputer);
			cout << "\n\n\n - - - - - - - - - -Round " << i << "- - - - - - - - - - \n";
			PrintPlayerChoices(ChoiceUser, ChoiceComputer);
			PrintResultEvryRound(resultat);

			if (resultat == Result::Player) ++WinnerPlayer;
			else if (resultat == Result::Computer) ++WinnerComputer;
			else                                 ++Draws;
		}
		cout << "\n----------------------------------\n";
		cout << "               Game Over          ";
		cout << "\n----------------------------------\n";

		cout << " Game Rounds " << rounds << endl;
		cout << " Player Win Times " << WinnerPlayer << endl;
		cout << " Computer win Times " << WinnerComputer << endl;
		cout << " Draw Times " << Draws << endl;

		if (WinnerPlayer > WinnerComputer)
			cout << "Final Winner :  [ PLAYER ] ";
		else if (WinnerPlayer < WinnerComputer)
			cout << "Final Winner :  [ Computer ] ";
		else
			cout << "Final Winner :  [ Draw ] ";

	} while(TryAgain() == true);
	

}


int main()
{
	srand((unsigned)time(NULL));
	PrintResult(RoudTimes());
	return 0;
}
*/
