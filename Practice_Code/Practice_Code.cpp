#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Design Function
	// functions that all does is for display
void ApplicationHeading();
void PokemonListHeading();

// Functional Function
	// functions that does bigger specific task
void DisplayPokemons(
	string[], string[], string[], int,
	string[], int
);
void ReleasePokemon(string[], string[], string[], int);
void FeedPokemon(string[], string[], string[], int);
void AddPokemon(string&, string&, string&);
void SortPokemon(
	string[], string[], string[], int,
	string[], int
);
void SearchPokemon(string[], string[], string[], int);
void SortPokemonBy(string[], string[], string[], int, string);
void LogHistory(string, string[], int);

// Utility Function
	// helper functions that can be used repeatedly and does specific task
bool LoopDisplayPokemon(string[], string[], string[], int);
int AvailableIndex(string[], int);
void FilterInputChar(int&);
void FilterInputInt(int&);
void SwapValues(string&, string&);
void DisplayHistory(string[], int);

// Menu Function
	// it aims to display the menu and return the user input
int DisplayPokemonMenu(string[], string[], string[], int);
int MainMenu();
int SortMenu();
int SearchMenu();


int main()
{
	// Constant
	const int MAX_POKEMON = 5;
	const int MAX_HISTORY = 50;

	// Variables
	int indexNo;

	// Data holder
	string
		pokemonName[MAX_POKEMON],
		pokemonLevel[MAX_POKEMON],
		pokemonCapturePlace[MAX_POKEMON],
		pokedexHistory[MAX_HISTORY];

	// use infinite loop to continuesly work until tasked to shut down
	while (true)
	{
		// it calls MainMenu Function and waits for return value
		switch (MainMenu())
		{
		case 1:
			// will call AvailableIndex function to check if there is an available index
			indexNo = AvailableIndex(pokemonName, MAX_POKEMON);

			// if there is no available index, it will display Full message
			if (indexNo == -1) {
				// log to history that it fails to add pokemon
				LogHistory("Failed to Add Pokemon", pokedexHistory, MAX_HISTORY);

				cout << "Storage is Full!" << endl;
				system("pause");
				system("cls");
				continue;
			}
			// if there is available index, it will add the pokemon
			else
			{
				// this will call AddPokemon function
				AddPokemon(pokemonName[indexNo], pokemonLevel[indexNo], pokemonCapturePlace[indexNo]);

				// log to history that it successfully added pokemon
				LogHistory("Added Pokemon: " + pokemonName[indexNo], pokedexHistory, MAX_HISTORY);
			}

			break;
		case 2:
			// this will call DisplayPokemon function
			DisplayPokemons(pokemonName, pokemonLevel, pokemonCapturePlace, MAX_POKEMON, pokedexHistory, MAX_HISTORY);
			break;
		case 3:
			// this will call SearchPokemon function
			SearchPokemon(pokemonName, pokemonLevel, pokemonCapturePlace, MAX_POKEMON);
			break;
		case 4:
			// this will call History function
			DisplayHistory(pokedexHistory, MAX_HISTORY);
			break;
		case 5:
			cout << "Exit" << endl;
			return 0;
		}
	}
}

// Design Function
void ApplicationHeading()
{
	cout
		<< "-----------------------------------" << endl << endl
		<< "             POKEDEX               " << endl << endl
		<< "-----------------------------------" << endl;
}

void PokemonListHeading()
{
	cout
		<< "-----------------------------------" << endl << endl
		<< "          Caputed Pokemon          " << endl << endl
		<< "-----------------------------------" << endl;
}

// Functional Function
void AddPokemon(string& pokemonName, string& pokemonLevel, string& pokemonCapturePlace)
{
	cout << "Enter Pokemon Name: ";
	getline(cin, pokemonName);

	// this loop is to check if the user input is valid
		// if not valid it will loop
	while (true)
	{
		cout << "Enter Pokemon Level: ";
		getline(cin, pokemonLevel);

		int level;

		// try catch: this is to prevent the program from crashing
			// if the user input is not a number, it will loop
			// if the user input is a number, it will convert it to integer
		try
		{
			// stoi: this converts string to integer
			level = stoi(pokemonLevel);
			pokemonLevel = to_string(level);

			// this is to check if the user input is range
				// if not valid it will cause error which will go to catch
			if (level < 1 || level > 100) throw exception();
			break;
		}
		catch (const std::exception&)
		{
			// this is used only for consitency of the asthetics
			system("cls");
			cout
				<< "Enter Pokemon Name: "
				<< pokemonName << endl;
			continue;
		}
	}

	cout << "Enter Pokemon Capture Place: ";
	// you can change this with simple:
		// cin >> pokemonCapturePlace;
	getline(cin, pokemonCapturePlace);

	system("cls");

	cout << pokemonName << " Added!" << endl;

	system("pause");
	system("cls");

}

void ReleasePokemon(string pokemonName[], string pokemonLevel[], string pokemonCapturePlace[], int MAX)
{

	while (true)
	{
		PokemonListHeading();
		// this will call and wait on return value of LoopDisplayPokemon
			// if it returns true, it means you captured pokemon
			// if it returns false, it means you did not capture pokemon, you must capture first
		if (LoopDisplayPokemon(pokemonName, pokemonLevel, pokemonCapturePlace, MAX))
		{
			int pokemonNo;

			cout << "Choose Pokemon to Release: " << endl;

			// you can change this with simple:
				// cin >> pokemonNo;
			FilterInputInt(pokemonNo);

			if (pokemonNo == -1)
			{
				cout << "Invalid Input!" << endl;
				system("pause");
				system("cls");
				continue;
			}
			else
			{
				system("cls");

				cout << pokemonName[pokemonNo - 1] << " Released!" << endl;

				pokemonName[pokemonNo - 1] = "";
				pokemonLevel[pokemonNo - 1] = "";
				pokemonCapturePlace[pokemonNo - 1] = "";

				break;
			}

		}
		else
		{
			cout << "Catch Pokemon First!" << endl;
			break;
		}
	}
}

void FeedPokemon(string pokemonName[], string pokemonLevel[], string pokemonCapturePlace[], int MAX)
{
	while (true)
	{
		PokemonListHeading();
		// this will LoopDisplayPokemon
			// if it returns true, it means you captured pokemon
			// if it returns false, it means you did not capture pokemon, you must capture first
		if (LoopDisplayPokemon(pokemonName, pokemonLevel, pokemonCapturePlace, MAX))
		{
			int pokemonNo;

			cout << "Choose Pokemon to Feed: " << endl;

			// you can change this with simple:
				// cin >> pokemonNo;
			FilterInputInt(pokemonNo);
			pokemonNo--;

			// check if the input is valid
				// check if the input is in range
				// check if error number is return
			if (pokemonNo < 0 || pokemonName[pokemonNo] == "")
			{
				cout << "Invalid Input!" << endl;
				system("pause");
				system("cls");

				// will skip the other code below and continue the loop
				continue;
			}
			else
			{
				system("cls");

				// check pokemon if it is already at max level
				if (stoi(pokemonLevel[pokemonNo]) >= 100)
				{
					cout << "Pokemon is already at Max Level!" << endl;
					break;
				}

				cout << pokemonName[pokemonNo] << " Level Up!" << endl;

				// add 1 to the pokemon level
					// stoi: this converts string to integer then add 1
					// to_string: this converts integer to string
				pokemonLevel[pokemonNo] = to_string(stoi(pokemonLevel[pokemonNo]) + 1);

				break;
			}
		}
		else
		{
			cout << "Catch Pokemon First!" << endl;
			break;
		}
	}
}

void SortPokemon(
	string pokemonName[], string pokemonLevel[], string pokemonCapturePlace[], int MAX,
	string pokedexHistory[], int MAX_HISTORY
)
{
	// what I did here is I made a loop that will loop until the user chooses to go back
		// this is to prevent the user from going back to main menu and display the pokemon again
		// this will display the pokemon once and will not display it again until the user chooses to go back
	while (true)
	{
		// here I just made a switch case to choose which sorting method to use
			// using DRY principle, I made a function that will sort the pokemon where it can be used multiple times
		switch (SortMenu())
		{
		case 1:
			SortPokemonBy(pokemonName, pokemonLevel, pokemonCapturePlace, MAX, "String");

			// log to history that it successfully sorted pokemon
			LogHistory("Sorted Pokemon by Name", pokedexHistory, MAX_HISTORY);
			break;
		case 2:
			SortPokemonBy(pokemonName, pokemonLevel, pokemonCapturePlace, MAX, "Level");

			// log to history that it successfully sorted pokemon
			LogHistory("Sorted Pokemon by Level", pokedexHistory, MAX_HISTORY);
			break;
		case 3:
			SortPokemonBy(pokemonName, pokemonLevel, pokemonCapturePlace, MAX, "Capture Place");
			break;
		case 4:
			return;
		}
	}
}

void SearchPokemon(string pokemonName[], string pokemonLevel[], string pokemonCapturePlace[], int MAX)
{
	string toSearch;
	bool isFound = false;

	cout 
		<< "Search Using Pokemon Name" << endl
		<< "Search:";
	// you can change this with simple:
		// cin >> toSearch;
	getline(cin, toSearch);

	system("cls");

	cout << "Search Result" << endl;

	// this loop in the array and check which matches 1 by 1
		// if it matches, it will display the pokemon
		// if it does not match, it will display no pokemon found
	for (int i = 0; i < MAX; i++)
	{
		if (pokemonName[i] == toSearch)
		{
			cout
				<< i + 1 << ". " << pokemonName[i] << endl
				<< " | " << pokemonLevel[i] << " - " << pokemonCapturePlace[i] << endl << endl;

			// this will call SearchMenu function
			SearchMenu();

			isFound = true;
		}
	}

	// if no pokemon is found, it will display no pokemon found
	if (!isFound) cout << "No Pokemon Found!" << endl;
}

void SortPokemonBy(string pokemonName[], string pokemonLevel[], string pokemonCapturePlace[], int MAX, string by)
{
	// this uses bubble sort
		// it compares 2 values and swap them if the condition is met
		// it will loop until all values are sorted
	for (int i = 0; i < MAX; i++)
	{
		for (int j = i + 1; j < MAX; j++)
		{
			// sort by name
			if (pokemonName[i] > pokemonName[j] && pokemonName[j] != "" && by == "String")
			{
				// this will call SwapValues function
				SwapValues(pokemonName[i], pokemonName[j]);
				SwapValues(pokemonLevel[i], pokemonLevel[j]);
				SwapValues(pokemonCapturePlace[i], pokemonCapturePlace[j]);
				cout << "Sorted by Name" << endl;
			}
			// sort by level
			else if (pokemonLevel[i] > pokemonLevel[j] && pokemonLevel[j] != "" && by == "Level")
			{
				SwapValues(pokemonName[i], pokemonName[j]);
				SwapValues(pokemonLevel[i], pokemonLevel[j]);
				SwapValues(pokemonCapturePlace[i], pokemonCapturePlace[j]);
				cout << "Sorted by Level" << endl;
			}
			// sort by capture place
			else if (pokemonCapturePlace[i] > pokemonCapturePlace[j] && pokemonCapturePlace[j] != "" && by == "Capture Place")
			{
				SwapValues(pokemonName[i], pokemonName[j]);
				SwapValues(pokemonLevel[i], pokemonLevel[j]);
				SwapValues(pokemonCapturePlace[i], pokemonCapturePlace[j]);
				cout << "Sorted by Capture Place" << endl;
			}
		}
	}

	// this will display the pokemon after sorting
	LoopDisplayPokemon(pokemonName, pokemonLevel, pokemonCapturePlace, MAX);
}

void LogHistory(string transaction, string transactionStorage[], int MAX_TRANSACTION)
{
	// this will move every transactions down by 1
	for (int i = 0; i < MAX_TRANSACTION; i++)
	{
		if (transactionStorage[i] == "")
		{
			for (int j = i; j > 0; j--)
			{
				SwapValues(transactionStorage[j], transactionStorage[j - 1]);
			}

			transactionStorage[0] = transaction;
			break;
		}
	}
}

void DisplayPokemons(
	string pokemonName[], string pokemonLevel[], string pokemonCapturePlace[], int MAX,
	string pokedexHistory[], int MAX_HISTORY
)
{
	while (true)
	{
		switch (DisplayPokemonMenu(pokemonName, pokemonLevel, pokemonCapturePlace, MAX))
		{
		case 1:
			// call ReleasePokemon function
			ReleasePokemon(pokemonName, pokemonLevel, pokemonCapturePlace, MAX);
			break;
		case 2:
			// call FeedPokemon function
			FeedPokemon(pokemonName, pokemonLevel, pokemonCapturePlace, MAX);
			break;
		case 3:
			// call SortPokemon function
			SortPokemon(pokemonName, pokemonLevel, pokemonCapturePlace, MAX, pokedexHistory, MAX_HISTORY);
			break;
		case 4:
			return;
		}
		system("pause");
		system("cls");
	}
}

// Menu Function
int MainMenu()
{
	int choice = 0;

	// this loop is to check if the user input is valid
		// if not valid it will loop
		// i_choice > 0: this is to prevent the user from inputting a negative number
		// i_choice <= 4: this is to prevent the user from inputting a number greater than 5
		// if one of the 2 condition is violated, it will loop
	while (!(choice > 0) || !(choice <= 4)) {
		ApplicationHeading();
		cout
			<< "1. Add a Pokemon in Storage" << endl
			<< "2. View Pokemon in Storage" << endl
			<< "3. Search Pokemon in Storage" << endl
			<< "4. History Check" << endl << endl
			<< "5. Exit" << endl << endl
			<< "Enter your choice: ";

		// can be changed to cin >> choice;
		FilterInputChar(choice);

		system("cls");
	}
	return choice;
}

int DisplayPokemonMenu(string pokemonName[], string pokemonLevel[], string pokemonCapturePlace[], int MAX)
{
	int choice = 0;

	while (!(choice > 0) || !(choice <= 4)) {
		PokemonListHeading();

		// this will call LoopDisplayPokemon function
		LoopDisplayPokemon(pokemonName, pokemonLevel, pokemonCapturePlace, MAX);
		// then display the menu
		cout
			<< "1. Release a Pokemon" << endl
			<< "2. Feed a Pokemon with Rare Candy" << endl
			<< "3. Sort Pokemon" << endl
			<< "4. Back" << endl << endl
			<< "Enter your choice: ";
		// can be changed to cin >> choice;
		FilterInputChar(choice);

		system("cls");
	}

	return choice;
}

int SortMenu()
{
	int choice = 0;
	while (!(choice > 0) || !(choice <= 4)) {
		// this will call PokemonListHeading function
		PokemonListHeading();

		// then display the menu
		cout
			<< "1. Sort by Name" << endl
			<< "2. Sort by Level" << endl
			<< "3. Sort by Capture Place" << endl
			<< "4. Back" << endl << endl
			<< "Enter your choice: ";
		// can be changed to cin >> choice;
		FilterInputChar(choice);

		system("cls");
	}

	return choice;
}

int SearchMenu()
{
	int choice = 0;
	while (!(choice > 0) || !(choice <= 4)) {
		cout
			<< "1. Feed Pokemon" << endl
			<< "2. Release Pokemon" << endl
			<< "3. Back" << endl << endl
			<< "Enter your choice: ";
		// can be changed to cin >> choice;
		FilterInputChar(choice);

		system("cls");
	}
	return 0;
}

// Utility Function
int AvailableIndex(string listOfPokemon[], int MAX)
{
	// this loop is to check if there is an available index
		// if there is, it will return the index
		// if there is not, it will return -1
	for (int i = 0; i < MAX; i++)
		if (listOfPokemon[i] == "") return i;

	return -1;
}

bool LoopDisplayPokemon(string pokemonName[], string pokemonLevel[], string pokemonCapturePlace[], int MAX)
{
	bool isThereACatched = false;

	// loop and display only the arrays with value
	for (int i = 0; i < MAX; i++)
	{
		if (pokemonName[i] == "") {
			continue;
		}

		isThereACatched = true;

		cout
			<< i + 1 << ". " << pokemonName[i] << endl
			<< " | " << pokemonLevel[i] << " - " << pokemonCapturePlace[i] << endl;
	}

	if (!isThereACatched) cout << setw(25) << "No Pokemon Catched Yet!" << endl;

	cout << endl;

	return isThereACatched;
}

void FilterInputChar(int& choice)
{
	string input;

	// getlin(cin, variable_name): this gets all inserted data until the user presses enter
		// this controls anything that user might input and overflow to next input
	getline(cin, input);

	/*
	choice[0]: this filters the input to only the first character
		this is to prevent the user from inputting more than one character
		it uses indexing and declaring only to accept the first character
	choice[0] - '0': this converts the character to integer
		this is to prevent the user from inputting a character that is not a number
		it uses ASCII table to convert the character to integer
		ASCII table: https://www.asciitable.com/
	*/
	choice = input[0] - '0';
}

void FilterInputInt(int& choice)
{
	// Filter Input accepts String value
		// checks if the input is a number
		// if it is a number, it will convert it to integer
		// if it is not a number, it will return -1
	string input;

	getline(cin, input);

	// try catch: this is to prevent the program from crashing
		// if the user input is not a number, it will return -1
		// if the user input is a number, it will convert it to integer
	try
	{
		// stoi: this converts string to integer
		choice = stoi(input);
	}
	catch (const std::exception&)
	{
		choice = -1;
	}
}

void SwapValues(string& a, string& b)
{
	// this is to swap the values of 2 variables
		// it uses a temporary variable to store the value of one of the variable
		// then it will swap the values of the 2 variables
		// from a to b and b to a
	string temp = a;
	a = b;
	b = temp;
}

void DisplayHistory(string history[], int MAX)
{
	cout << "History" << endl << endl;

	for (int i = 0; i < MAX; i++)
	{
		if (history[i] == "") break;
		cout << history[i] << endl;
	}
	
	system("pause");
	system("cls");
}


