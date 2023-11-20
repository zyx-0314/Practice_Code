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
void DisplayPokemons(string[], string[], string[], int);
void ReleasePokemon(string[], string[], string[], int);
void FeedPokemon(string[], string[], string[], int);
void AddPokemon(string&, string&, string&);
void SortPokemon(string[], string[], string[], int);
void SearchPokemon(string[], string[], string[], int);
void SortPokemonBy(string[], string[], string[], int, string);

// Utility Function
	// helper functions that can be used repeatedly and does specific task
bool LoopDisplayPokemon(string[], string[], string[], int);
int AvailableIndex(string[], int);
void FilterInputChar(int&);
void FilterInputInt(int&);
void SwapValues(string&, string&);

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

	// Variables
	int indexNo;

	// Data holder
	string
		pokemonName[MAX_POKEMON],
		pokemonLevel[MAX_POKEMON],
		pokemonCapturePlace[MAX_POKEMON];

	// use infinite loop to continuesly work until tasked to shut down
	while (true)
	{
		switch (MainMenu())
		{
		case 1:
			// Check if there is available index
			indexNo = AvailableIndex(pokemonName, MAX_POKEMON);

			// if there is no available index, it will display Full message
			if (indexNo == -1) {
				cout << "Storage is Full!" << endl;
				system("pause");
				system("cls");
				continue;
			}
			// if there is available index, it will add the pokemon
			else 
				AddPokemon(pokemonName[indexNo], pokemonLevel[indexNo], pokemonCapturePlace[indexNo]);
			break;
		case 2:
			DisplayPokemons(pokemonName, pokemonLevel, pokemonCapturePlace, MAX_POKEMON);
			break;
		case 3:
			SearchPokemon(pokemonName, pokemonLevel, pokemonCapturePlace, MAX_POKEMON);
			break;
		case 4:
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

	while (true)
	{
		cout << "Enter Pokemon Level: ";
		getline(cin, pokemonLevel);

		int level;

		try
		{
			level = stoi(pokemonLevel);
			pokemonLevel = to_string(level);
			if (level < 1 || level > 100) throw exception();
			break;
		}
		catch (const std::exception&)
		{
			system("cls");
			cout
				<< "Enter Pokemon Name: "
				<< pokemonName << endl;
			continue;
		}
	}

	cout << "Enter Pokemon Capture Place: ";
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
		if (LoopDisplayPokemon(pokemonName, pokemonLevel, pokemonCapturePlace, MAX))
		{
			int pokemonNo;

			cout << "Choose Pokemon to Release: " << endl;

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
			cout << "Catch Pokemon First!" << endl;
	}
}

void FeedPokemon(string pokemonName[], string pokemonLevel[], string pokemonCapturePlace[], int MAX)
{
	while (true)
	{
		PokemonListHeading();
		if (LoopDisplayPokemon(pokemonName, pokemonLevel, pokemonCapturePlace, MAX))
		{
			int pokemonNo;

			cout << "Choose Pokemon to Feed: " << endl;

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

				if (stoi(pokemonLevel[pokemonNo - 1]) >= 100)
				{
					cout << "Pokemon is already at Max Level!" << endl;
					break;
				}

				cout << pokemonName[pokemonNo - 1] << " Level Up!" << endl;

				pokemonLevel[pokemonNo - 1] = to_string(stoi(pokemonLevel[pokemonNo - 1]) + 1);

				break;
			}
		}
		else 
			cout << "Catch Pokemon First!" << endl;
	}
}

void SortPokemon(string pokemonName[], string pokemonLevel[], string pokemonCapturePlace[], int MAX)
{
	while (true)
	{
		switch (SortMenu())
		{
		case 1:
			SortPokemonBy(pokemonName, pokemonLevel, pokemonCapturePlace, MAX, "String");
			break;
		case 2:
			SortPokemonBy(pokemonName, pokemonLevel, pokemonCapturePlace, MAX, "Level");
			break;
		case 3:
			SortPokemonBy(pokemonName, pokemonLevel, pokemonCapturePlace, MAX, "Capture Place");
			break;
		case 4:
			return;
		}
		system("pause");
		system("cls");
	}
}

void SearchPokemon(string pokemonName[], string pokemonLevel[], string pokemonCapturePlace[], int MAX)
{
	string toSearch;
	bool isFound = false;

	cout 
		<< "Search Using Pokemon Name" << endl
		<< "Search:";
	getline(cin, toSearch);

	system("cls");

	cout << "Search Result" << endl;

	for (int i = 0; i < MAX; i++)
	{
		if (pokemonName[i] == toSearch)
		{
			cout
				<< i + 1 << ". " << pokemonName[i] << endl
				<< " | " << pokemonLevel[i] << " - " << pokemonCapturePlace[i] << endl << endl;

			SearchMenu();

			isFound = true;
		}
	}

	if (!isFound) cout << "No Pokemon Found!" << endl;
}

void SortPokemonBy(string pokemonName[], string pokemonLevel[], string pokemonCapturePlace[], int MAX, string by)
{
	for (int i = 0; i < MAX; i++)
	{
		for (int j = i + 1; j < MAX; j++)
		{
			if (pokemonName[i] > pokemonName[j] && pokemonName[j] != "" && by == "String")
			{
				SwapValues(pokemonName[i], pokemonName[j]);
				SwapValues(pokemonLevel[i], pokemonLevel[j]);
				SwapValues(pokemonCapturePlace[i], pokemonCapturePlace[j]);
			}
			else if (pokemonLevel[i] > pokemonLevel[j] && pokemonLevel[j] != "" && by == "Level")
			{
				SwapValues(pokemonName[i], pokemonName[j]);
				SwapValues(pokemonLevel[i], pokemonLevel[j]);
				SwapValues(pokemonCapturePlace[i], pokemonCapturePlace[j]);
			}
			else if (pokemonCapturePlace[i] > pokemonCapturePlace[j] && pokemonCapturePlace[j] != "" && by == "Capture Place")
			{
				SwapValues(pokemonName[i], pokemonName[j]);
				SwapValues(pokemonLevel[i], pokemonLevel[j]);
				SwapValues(pokemonCapturePlace[i], pokemonCapturePlace[j]);
			}
		}
	}

	cout << "Sorted by Name" << endl;

	LoopDisplayPokemon(pokemonName, pokemonLevel, pokemonCapturePlace, MAX);
}

void DisplayPokemons(string pokemonName[], string pokemonLevel[], string pokemonCapturePlace[], int MAX)
{
	while (true)
	{
		switch (DisplayPokemonMenu(pokemonName, pokemonLevel, pokemonCapturePlace, MAX))
		{
		case 1:
			ReleasePokemon(pokemonName, pokemonLevel, pokemonCapturePlace, MAX);
			break;
		case 2:
			FeedPokemon(pokemonName, pokemonLevel, pokemonCapturePlace, MAX);
			break;
		case 3:
			SortPokemon(pokemonName, pokemonLevel, pokemonCapturePlace, MAX);
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
			<< "4. Exit" << endl << endl
			<< "Enter your choice: ";

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
		LoopDisplayPokemon(pokemonName, pokemonLevel, pokemonCapturePlace, MAX);
		cout
			<< "1. Release a Pokemon" << endl
			<< "2. Feed a Pokemon with Rare Candy" << endl
			<< "3. Sort Pokemon" << endl
			<< "4. Back" << endl << endl
			<< "Enter your choice: ";
		FilterInputChar(choice);

		system("cls");
	}

	return choice;
}

int SortMenu()
{
	int choice = 0;
	while (!(choice > 0) || !(choice <= 4)) {
		PokemonListHeading();
		cout
			<< "1. Sort by Name" << endl
			<< "2. Sort by Level" << endl
			<< "3. Sort by Capture Place" << endl
			<< "4. Back" << endl << endl
			<< "Enter your choice: ";
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
	string temp = a;
	a = b;
	b = temp;
}