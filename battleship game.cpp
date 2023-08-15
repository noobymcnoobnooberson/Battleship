#include<time.h>
#include <iostream>
#include <cstdlib>

void tick(clock_t a)
{
    clock_t start;
    start  = clock();
    while(clock()-start<a)
    {

    }
}


using namespace std;

void PlayAgain(char answer);
bool ChooseMode(bool OnceInvalid);
void delText(int num) {
	cout << "\r";
	for(int i = 0;i < num;i++) {
		cout << " ";
	}
	cout << "\r";
}
void printBoard(int boardState[10][10], bool Fog) {
	for (int i = 0;i < 1;i++) {
		cout << endl;
		for (int i = 0;i < 30;i++) {
			cout << " ";
		}
	}
	cout << "  A B C D E F G H I J" << endl;
	for (int i = 0;i < 30;i++) {
			cout << " ";
		}
	for (int i = 0;i <= 9;i++) {
		cout << i << "|";
		for (int j = 0;j <= 9;j++) {
			if (Fog) {
				switch(boardState[i][j]) {
					case 0:
						cout << " |"; break;
					case 1:
						cout << "X|"; break;
					case 2:
						cout << "!|"; break;
					default:
						cout << " |"; break;
				}
			}
			else if (!Fog) {
				switch(boardState[i][j]) {
					case 0:
						cout << " |"; break;
					case 1:
						cout << "X|"; break;
					case 2:
						cout << "!|"; break;
					case 3:
						cout << "A|"; break;
					case 4:
						cout << "B|"; break;
					case 5:
						cout << "C|"; break;
					case 6:
						cout << "D|"; break;
					case 7:
						cout << "F|"; break;
				}
			}
		}
		cout << endl;
		for (int i = 0;i < 30;i++) {
			cout << " ";
		}
	}
	cout << endl;
}

int PickDirection(bool OnceInvalid, bool Bot) {
	if (!Bot) {
		if (OnceInvalid == false) {
			cout << "Choose a direction: ";
		}
		else {
			cout << "Invalid direction, retry: ";
		}
		char Direction;
		cin >> Direction;
		cout << "\x1b[1A";
		delText(100);
		if (Direction == 'h' || Direction == 'H') {
			return 1;
		}
		else if (Direction == 'v' || Direction == 'V') {
			return 0;
		}
		else {
			PickDirection(true, Bot);
		}
	}
	else {
        cout << "...";
        			delText(100);
		srand(time(0));
		return rand() % 2;
	}
}

bool IsOccupied(int BoardState[10][10],int shipType,int X, int Y, int Horiz) {
	for (int i = 0; i < 9 - shipType;i++) {
		if (shipType == 3) {
			if (Horiz == 1) {
				if (BoardState[Y][X] >= 3 || BoardState[Y][X+1] >= 3 || BoardState[Y][X+2] >= 3 || BoardState[Y+1][X] >= 3 || BoardState[Y+1][X+1] >= 3) {
					return false;
					break;
				}
			}
			else {
				if (BoardState[Y][X] >= 3 || BoardState[Y+1][X] >= 3 || BoardState[Y+1][X+1] >= 3 || BoardState[Y+2][X] >= 3 || BoardState[Y+2][X+1] >= 3) {
					return false;
					break;
				}
			}
		}
		else if (Horiz == 1 && shipType != 3) {
			if (BoardState[Y][X + i] >= 3) {
				return false;
				break;
			}
		}
		else if (Horiz == 0 && shipType != 3){
			if (BoardState[Y + i][X] >= 3) {
				return false;
				break;
			}
		}
	}
	return true;
}

int InputX(int BoardState[10][10],int ShipType,bool OnceInvalid,int Horiz, bool Bot) {
	int X;
	char falseX;
	bool validX = false;
	srand(time(0));
	if (!Bot) {
		if (OnceInvalid == false) {
			cout << "Input a X coordinate: ";
		}
		else {
			cout << "Invalid X coordinate, retry: ";
		}
		cin >> falseX;
	}
	if (ShipType == 3 && Bot) {
        cout << ".....";
        			delText(100);
        if(Horiz) {
			X = rand() % 8;
		}
		else {
			X = rand() % 9;
		}
		if (X + 2 + Horiz<= 10) {
			validX = true;
			return X;
		}
	}
	else if(ShipType == 3 && !Bot) {
		if (!Bot) {
			cout << "\x1b[1A";
			delText(100);
		}
		if (falseX >= 'A' && falseX <= 'J') {
			X = falseX - 'A';
			if (X + 2 + Horiz<= 10) {
				validX = true;
				return X;
			}
		}
		else if (falseX >= 'a' && falseX <= 'j') {
			X = falseX - 'a';
			if (X + 2 + Horiz <= 10) {
				validX = true;
				return X;
			}
		}
		else if (falseX >= '0' && falseX <= '9') {
			X = falseX - '0';
			if (X + 2 + Horiz <= 10) {
				validX = true;
				return X;
			}
		}
	}
	else if (ShipType != 3 && Bot) {
        cout << ".....";
       	delText(100);
        if(Horiz) {
			X = rand() % (ShipType + 2);
		}
		else {
			X = rand() % 10;
		}
		if (X + (9 - ShipType)*Horiz <= 10 - (1 - Horiz)) {
				validX = true;
				return X;
		}
	}
	else if(ShipType != 3 && !Bot) {
		if (!Bot) {
			cout << "\x1b[1A";
			delText(100);
		}
		if (falseX >= 'A' && falseX <= 'J') {
			X = falseX - 'A';
			if (X + (9 - ShipType)*Horiz <= 10 - (1 - Horiz)) {
				validX = true;
				return X;
			}
		}
		else if (falseX >= 'a' && falseX <= 'j') {
			X = falseX - 'a';
			if (X + (9 - ShipType)*Horiz <= 10 - (1 - Horiz)) {
				validX = true;
				return X;
			}
		}
		else if (falseX >= '0' && falseX <= '9') {
			X = falseX - '0';
			if (X + (9 - ShipType)*Horiz <= 10 - (1 - Horiz)) {
				validX = true;
				return X;
			}
		}
	}
	if (validX == false) {
		InputX(BoardState,ShipType, true, Horiz, Bot);
	}
}

int InputY(int BoardState[10][10],int ShipType,bool OnceInvalid,int Horiz,bool Bot) {
	int Y;
	char falseY;
	bool validY = false;
	srand(time(0));
	if (!Bot) {
		if (OnceInvalid == false) {
			cout << "Input a Y coordinate: ";
		}
		else {
			cout << "Invalid Y coordinate, retry: ";
		}
		cin >> falseY;
	}

	if (ShipType == 3 && Bot) {
        cout << ".....";
		delText(100);
		if (!Horiz) {
			Y = rand() % 8;
		}
		else {
			Y = rand() % 9;
		}
		Y = rand() % 10;
		if (Y + 3 - Horiz <= 10) {
				validY = true;
				return Y;
		}
	}
	else if(ShipType == 3 && !Bot) {
		if (!Bot) {
			cout << "\x1b[1A";
			delText(100);
		}
		if (falseY >= 'A' && falseY <= 'J') {
			Y = falseY - 'A';
			if (Y + 3 - Horiz <= 10) {
				validY = true;
				return Y;
			}
		}
		else if (falseY >= 'a' && falseY <= 'j') {
			Y = falseY - 'a';
			if (Y + 3 - Horiz<= 10) {
				validY = true;
				return Y;
			}
		}
		else if (falseY >= '0' && falseY <= '9') {
			Y = falseY - '0';
			if (Y + 3 - Horiz<= 10) {
				validY = true;
				return Y;
			}
		}
	}
	else if (ShipType != 3 && Bot) {
        cout << ".....";
        delText(100);
        if (!Horiz) {
        	Y = rand() % (ShipType + 2);
		}
		else {
			Y = rand() % 10;
		} 
	 if (Y + (9 - ShipType)*(1- Horiz) <= 10 - Horiz) {
				validY = true;
				return Y;
		}
	}
	else if(ShipType != 3 && !Bot) {
		if (!Bot) {
			cout << "\x1b[1A";
			delText(100);
		}
		if (falseY >= 'A' && falseY <= 'J') {
			Y = falseY - 'A';
			if (Y + (9 - ShipType)*(1- Horiz) <= 10 - Horiz) {
				validY = true;
				return Y;
			}
		}
		else if (falseY >= 'a' && falseY <= 'j') {
			Y = falseY - 'a';
			if (Y + (9 - ShipType)*(1 - Horiz) <= 10 - Horiz) {
				validY = true;
				return Y;
			}
		}
		else if (falseY >= '0' && falseY <= '9') {
			Y = falseY - '0';
			if (Y + (9 - ShipType)*(1 - Horiz) <= 10 - Horiz) {
				validY = true;
				return Y;
			}
		}
	}
	if (validY == false) {
		InputY(BoardState,ShipType, true, Horiz, Bot);
	}
}

string Shoot(int BoardState[10][10],bool OnceInvalid,int Psunk[8]) {
	if (OnceInvalid) {
		cout << "Invalid coordinates (already hit)." << endl;
	}
	int X = InputX(BoardState, 3, false, -1, false);
	int Y = InputY(BoardState, 3, false, 2, false);
	char falseY = Y + '0';
	char falseX = X + 'A';
	string Coords =string() + falseX + falseY;
	if (BoardState[Y][X] == 0) {
		BoardState[Y][X] = 1;
	}
	else if(BoardState[Y][X] >= 3) {
		Psunk[BoardState[Y][X]]--;
		BoardState[Y][X] = 2;
	}
	else {
		Shoot(BoardState, true, Psunk);
	}
	return Coords;
}

string BotShoot(int BoardState[10][10]) {
	srand(time(0));
	int X = rand() % 10;
	tick(1000);
	srand(time(0));
	int Y = rand() % 10;
	char falseY = Y + 'A';
	char falseX = X + '0';
	string Coords =string() + falseY + falseX;
	if (BoardState[Y][X] == 0) {
		BoardState[Y][X] = 1;
	}
	else if(BoardState[Y][X] >= 3) {
		BoardState[Y][X] = 2;
	}
	else {
		BotShoot(BoardState);
	}
	return Coords;
}
void shipPlace(int BoardState[10][10],bool Bot) {
	//A: Aircraft Carrier (3);
	//B: Battleship (4);
	//C: Cruiser (5);
	//D: Destroyer (6);
	//F: Frigate (7);
	int shipType,X,Y;
	int Horiz;
	bool Valid = false;
	if (!Bot) {
		printBoard(BoardState, false);
	}
	for (shipType = 3; shipType <= 7;shipType++) {
		cout << "Placing ";
		switch (shipType) {
			case 3:
				cout << "aircraft carrier." << endl;
				break;
			case 4:
				cout << "battleship." << endl;
				break;
			case 5:
				cout << "cruiser." << endl;
				break;
			case 6:
				cout << "destroyer." << endl;
				break;
			case 7:
				cout << "frigate." << endl;
		}
		Horiz = PickDirection(false, Bot);
		X = InputX(BoardState, shipType, false, Horiz, Bot);
		Y = InputY(BoardState, shipType, false, Horiz, Bot);
		Valid = IsOccupied(BoardState, shipType, X, Y, Horiz);
		while (!Valid) {
			if (!Bot) {
				cout << "Space Occupied, re-enter coordinates." << endl;
			}
			Horiz = PickDirection(false, Bot);
			if (!Bot) {
				cout << "\x1b[1A";
				delText(100);
			}
			X = InputX(BoardState, shipType, false, Horiz, Bot);
			Y = InputY(BoardState, shipType, false, Horiz, Bot);
			Valid = IsOccupied(BoardState, shipType, X, Y, Horiz);
		}
		for (int i = 0; i < 9 - shipType;i++) {
			if (shipType == 3) {
				if (Horiz == 1) {
					BoardState[Y][X] = 3;
					BoardState[Y][X+1] = 3;
					BoardState[Y][X+2] = 3;
					BoardState[Y+1][X] = 3;
					BoardState[Y+1][X+1] = 3;
				}
				else {
					BoardState[Y][X] = 3;
					BoardState[Y+1][X] = 3;
					BoardState[Y+1][X+1] = 3;
					BoardState[Y+2][X] = 3;
					BoardState[Y+2][X+1] = 3;
				}
			}
			else if (Horiz == 1 && shipType != 3) {
				BoardState[Y][X + i] = shipType;
			}
			else if (Horiz == 0 && shipType != 3){
				BoardState[Y + i][X] = shipType;
			}
		}
		system("cls");
		if (!Bot) {
			printBoard(BoardState, false);
		}
	}
}

void sinking(int Psunk[8], int player, bool bot) {
	if (!bot) {
		for (int i = 3;i < 8;i++) {
			if (Psunk[i] == 0) {
				Psunk[i] = -1;
				cout << "Sinking Player " << player <<"'s ";
				switch (i) {
					case 3:
						cout << "Aircraft carrier!" << endl;
						break;
					case 4: 
						cout << "Battleship!" << endl;
						break;
					case 5:
						cout << "Cruiser!" << endl;
						break;
					case 6:
						cout << "Destroyer!" << endl;
						break;
					case 7:
						cout << "Frigate!" << endl;
						break;
				}
			}
		}
	}
	if (bot) {
		for (int i = 3;i < 8;i++) {
			if (Psunk[i] == 0) {
				Psunk[i] = -1;
				if (player == 1) {
					cout << ", sinking your ";
				}
				else {
					cout << "You sunk the bot's ";
				}
				switch (i) {
					case 3:
						cout << "Aircraft carrier!" << endl;
						break;
					case 4: 
						cout << "Battleship!" << endl;
						break;
					case 5:
						cout << "Cruiser!" << endl;
						break;
					case 6:
						cout << "Destroyer!" << endl;
						break;
					case 7:
						cout << "Frigate!" << endl;
						break;
				}
			}
		}
	}
}

void PlayWithBot(int turn,int BoardState1[10][10],int BoardState2[10][10],int P1sunk[8],int P2sunk[8]) {
	char answer;
	bool GameOn = false;
	bool P1Win = true; bool P2Win = true;
	for (int i = 3;i < 8;i++) {
		if (P1sunk[i] >= 1) {
			P2Win = false;
		}
		if (P2sunk[i] >= 1) {
			P1Win = false;
		}
		if (P1Win == false && P2Win == false) {
		GameOn = true;
		break;
		}
	}
	if (P1Win) {
		GameOn = false;
		system("cls");
		cout << "Player:";
		printBoard(BoardState1, false);
		cout << "Bot:";
		printBoard(BoardState2, false);
		cout << "Player wins!" << endl << "Play again? Y/N";
		char answer;
		cin >> answer;
		PlayAgain(answer);
	}
	else if (P2Win) {
		GameOn = false;
		system("cls");
		cout << "Player:";
		printBoard(BoardState1, false);
		cout << "Bot:";
		printBoard(BoardState2, false);
		cout << "You got owned by a bot!" << endl << "Play again? Y/N";
		char answer;
		cin >> answer;
		PlayAgain(answer);
	}
	if (GameOn) {
		if (turn == 1) {
			system("cls");
			cout << "Turn " << turn << endl;
			cout << "     Player:";
			printBoard(BoardState1, false);
			cout << "     Bot:";
			printBoard(BoardState2, true);
			Shoot(BoardState2, false,P2sunk);
			system("cls");
		}
		else if (turn > 1) {
			system("cls");
			cout << "Turn " << turn << endl;
			cout << "     Player:";
			printBoard(BoardState1, false);
			cout << "     Bot:";
			printBoard(BoardState2, true);
			sinking(P2sunk, 2, true);
			tick(2000);
			string Coords = BotShoot(BoardState1);
			system("cls");
			cout << "     Player:";
			printBoard(BoardState1, false);
			cout << "     Bot:";
			printBoard(BoardState2, true);
			cout << "Bot shot at: " << Coords << endl;
			sinking(P1sunk, 1, false);
			Shoot(BoardState2, false,P2sunk);
		}
		PlayWithBot(turn + 1,BoardState1,BoardState2,P1sunk,P2sunk);
	}
}
void PlayWithHuman(int turn,int BoardState1[10][10],int BoardState2[10][10],int P1sunk[8],int P2sunk[8]) {
	char answer;
	bool GameOn = false;
	bool P1Win = true; bool P2Win = true;
	for (int i = 3;i < 8;i++) {
		if (P1sunk[i] >= 1) {
			P2Win = false;
		}
		if (P2sunk[i] >= 1) {
			P1Win = false;
		}
		if (P1Win == false && P2Win == false) {
		GameOn = true;
		break;
		}
	}
	if (P1Win) {
		GameOn = false;
		system("cls");
		cout << "     Player 1:";
		printBoard(BoardState1, false);
		cout << "     Player 2:";
		printBoard(BoardState2, false);
		cout << "Player 1 wins!" << endl << "Play again? Y/N   ";
		char answer;
		cin >> answer;
		PlayAgain(answer);
	}
	else if (P2Win) {
		GameOn = false;
		system("cls");
		cout << "     Player 1:";
		printBoard(BoardState1, false);
		cout << "     Player 2:"; 
		printBoard(BoardState2, false);
		cout << "Player 2 wins!" << endl << "Play again? Y/N   ";
		char answer;
		cin >> answer;
		PlayAgain(answer);
	}
	if (GameOn) {
		string Coords;
		if (turn == 1) {
			cout << "Turn " << turn << endl;
			cout << "     Player 1:";
			printBoard(BoardState1, true);
			cout << "     Player 2:";
			printBoard(BoardState2, true);
			cout << "Player 1's turn" << endl;
			Coords = Shoot(BoardState2, false,P2sunk);
			turn = turn + 1;
			system("cls");
			cout << "Turn " << turn << endl;
			cout << "     Player 1:";
			printBoard(BoardState1, true);
			cout << "     Player 2:";
			printBoard(BoardState2, true);
			cout << "Player 1 shot at: " << Coords << ". ";
			sinking(P2sunk, 2, false);
			cout << "Player 2's turn" << endl;
			Coords = Shoot(BoardState1, false,P1sunk);
			system("cls");
			turn = turn + 1;
			cout << "Turn " << turn << endl;
			cout << "     Player 1:";
			printBoard(BoardState1, true);
			cout << "     Player 2:";
			printBoard(BoardState2, true);
			cout << "Player 2 shot at: " << Coords << ". ";
			sinking(P1sunk, 1, false);
			cout << "Player 1's turn" << endl;
		}
		else if (turn % 2 == 1) {
			Coords = Shoot(BoardState2, false,P2sunk);
			system("cls");
			turn = turn + 1;
			cout << "Turn " << turn << endl;
			cout << "     Player 1:";
			printBoard(BoardState1, true);
			cout << "     Player 2:";
			printBoard(BoardState2, true);
			cout << "Player 1 shot at: " << Coords << ". ";
			sinking(P2sunk, 2, false);
			cout << "Player 2's turn" << endl;
			delText(2);
		}
		else if (turn % 2 == 0) {
			Coords = Shoot(BoardState1, false,P1sunk);
			system("cls");
			turn = turn + 1;
			cout << "Turn " << turn << endl;
			cout << "     Player 1:";
			printBoard(BoardState1, true);
			cout << "     Player 2:";
			printBoard(BoardState2, true);
			cout << "Player 2 shot at: " << Coords << ". ";
			sinking(P1sunk, 1, false);
			cout << "Player 1's turn" << endl;
		}
		PlayWithHuman(turn,BoardState1,BoardState2,P1sunk, P2sunk);
	}
}

bool ChooseMode(bool OnceInvalid) {
	int P1sunk[8];
	int P2sunk[8];
	system("cls");
	for (int i = 0;i < 10;i++) {
		cout << endl;
		for (int i = 0;i < 30;i++) {
			cout << " ";
		}
	}
	cout << "Choose a mode: " << endl;
	for (int i = 0;i < 36;i++) {
			cout << " ";
		}
	cout << "1. Play with bot" << endl;
	for (int i = 0;i < 36;i++) {
			cout << " ";
		}
	cout << "2. Play with human" << endl;
	int BoardState1[10][10], BoardState2[10][10];
	for (int i = 0;i <= 9;i++) {
		for (int j = 0;j <= 9;j++) {
			BoardState1[i][j] = 0;
			BoardState2[i][j] = 0;
		}
	}
	P1sunk[3] = 5;
	P2sunk[3] = 5;
	for (int i = 3;i < 8;i++) {
		P1sunk[i] = 9 - i;
		P2sunk[i] = 9 - i;
	}
		for (int i = 0;i < 36;i++) {
			cout << " ";
		}
	cout << "3. Quit" << endl;
	cout << "Chosen mode: ";
	int mode;
	cin >> mode;
	if (mode == 1) {
		system("cls");
		shipPlace(BoardState1, false);
		system("cls");
		shipPlace(BoardState2, true);
		system("cls");
		tick(1000);
		system("cls");
		PlayWithBot(1,BoardState1,BoardState2, P1sunk, P2sunk);
	}
	else if (mode == 2) {
		system("cls");
		shipPlace(BoardState1, false);
		system("cls");
		shipPlace(BoardState2, false);
		system("cls");
		PlayWithHuman(1,BoardState1,BoardState2, P1sunk, P2sunk);
	}
	else if (mode == 3) {
		return true;
	}
	else {
		return true;
	}
}
void PlayAgain(char answer) {
	if (answer == 'y' || answer == 'Y') {
		system("cls");
		ChooseMode(false);
	}
	else {

	}
}
int main() {
	string str = "Battleship";
	bool modeChosen = false;
	for (int i = 0;i < 10;i++) {
		cout << endl;
		for (int i = 0;i < 30;i++) {
			cout << " ";
		}
	}
	for (size_t i = 0;i < str.length();i++) {
		cout << str[i];
		tick(120);
	}

	tick(400);
	system("cls");
	modeChosen = ChooseMode(false);
	while (!modeChosen) {
		ChooseMode(true);
	}
}
// 800
// lines
// of
// code
//baby!!!!!!
