#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

using namespace std;

struct Card{
	int valoare = 0;
	string type = "";
};

struct Player {
	string userName = "";
	unsigned int scor = 0;
	unsigned bet = 0;
	int numberCard = 0;
	Card carti[5];
};

fstream inData;
fstream inScor;
string userPass; //pt a cit datele din fisier
string password, line; //pt a introduce datele de catre user
string userName;

int t[13], aux;
Player users[3];
Player &computer = users[0];
Player &player1 = users[1];
Player &player2 = users[2];

void userAccount(int x, Player users[]){
	
	char option;
	bool found = false;

	cout << "Pentru a incepe jocul trebuie sa alegi o optiune: " <<endl<< endl << "1.Creaza un cont nou." << endl << "2.Am deja un cont creat." << endl;
	cout <<endl<< "Optiune aleasa: ";
	cin >> option;
	cout << endl;

	switch (option)
	{
	case '1':
		cout << "User nou Black Jack \n";
		inData.open("Username.dat.txt", ios::app); //pt a stoca username si parola
		inScor.open("Scor.dat.txt", ios::app); //pt a stoca usename si scorul
		cout << "Introduceti un username (caractere mici):  ";
		cin >> userName;
		users[x].userName = userName; //stocam in fisier
		

		cout << "Introduceti o parola:  ";
		cin >> password;
		cout << endl;

		inData << userName << " " << password << endl;
		inScor << userName << " " << users[x].scor << endl;

		inData.close();
		inScor.close();

		cout << "Felicitari! Tocmai ai fost inregistrat." << endl;
		system("cls");
		cout << "Bine ai revenit, " << userName << " !" << endl;
		cout << "Scorul tau curent este: " << users[x].scor << endl;


		break;

	case '2':
	{
				cout << "Cont existent: \n";
				inData.open("Username.dat.txt", ios::in);
				cout << "Introduceti username-ul (caractere mici): ";
				cin >> userName;
				cout << "Introduceti parola: ";
				cin >> password;
				users[x].userName = userName;
				userPass = userName + " " + password;

				if (inData.is_open())
				while (getline(inData, line) && !found)
				{
					if (line.compare(userPass) == 0){
						found = true;
					}
				}
				inData.close();
				if (found)
				{
					cout << "Bine ai revenit, " << userName << " !" << endl;
					cout << "Scorul tau curent este: " << users[x].scor << endl;

				}
				else
				{
					cout << "UserName-ul si Parola nu au fost gasite in system. Scrieti '1' pentru a reincerca. " << endl;
					cin >> password;
					if (password == "1")
						system("cls");
					userAccount(x, users);
				}
				found = false;

				inScor.open("Scor.dat.txt", ios::in);
				if (inScor.is_open())
				{
					while (getline(inScor, line) && !found)
					{
						if (line.compare(userPass) == 0){ // gasim usernameul si facem conexiunea
							found = true;
							inScor >> users[x].scor;
						}
					}
					inData.close();
					inScor.close();
				}

				break;

	default:
		system("cls");
		cout << "Nu ai introdus o optiune. Mai incearca! " << endl << endl;
		userAccount(x, users);
		break;
	}
	}

}

void cardValue(){
	int  i;
	for (i = 0; i < 13; i++)
		t[i] = i + 1; //atribui valori
		
}

void Shuffle()
{
	srand(time(0));
	for (int j = 1; j <= 2; j++)	// repet de 2 ori
	for (int i = 1; i <= 13; i++) //interschimb fiecare carte cu o poz random
	{
		int poz1 = rand() % 13 + 1;
		aux = t[i];	//default assigment operator
		t[i] = t[poz1];
		t[poz1] = aux;
	}
}

void PlayerCards(Player &player){
	int s = 0;
	srand(time(0));

	for (int i = 0; i < player.numberCard;i++)
	{
		s = rand() % 13 ;
		player.carti[i].valoare = t[s];
	
		aux = rand() % 3;
		switch (aux)
		{
		case 0:
		player.carti[i].type= "spades";
			break;
		case 1:
			player.carti[i].type = "hearts ";
			break;
		case 2:
			player.carti[i].type = "diamonds ";
			break;
		case 3:
			player.carti[i].type = "clubs ";
			break;
		default:
			cout << "error";
			break;
		}
	}
}

void PrintCard(Player &player, int n)
{
	int val, i, aux;
	for (i = 0; i < n; i++)
	{
		val = player.carti[i].valoare;
		switch (val)
		{
		case 1:
			cout << "A -> ";
			break;
		case 11:
			cout << "J -> ";
			break;
		case 12:
			cout << "Q -> ";
			break;
		case 13:
			cout << "K -> ";
			break;
		default:
			cout << val <<" -> ";
			break;
		}

		cout << player.carti[i].type;
		cout << endl;
	}
}

void Hit(Player &player){
	int i,s;
	s = rand() % 13 + 1;
	for (i = 0; i < player.numberCard; i++)
	{
		if (t[s] == player.carti[i].valoare)
		{
			s = rand() % 13 + 1;
			i = 0;
		}
	}
		
		player.carti[player.numberCard].valoare =t[s];
		player.numberCard++;

		aux = rand() % 3;
		switch (aux)
		{
		case 0:
			player.carti[i].type = "spades";
			break;
		case 1:
			player.carti[i].type = "hearts ";
			break;
		case 2:
			player.carti[i].type = "diamonds ";
			break;
		case 3:
			player.carti[i].type = "clubs ";
			break;
		default:
			cout << "error";
			break;
		}

}

int SumaCarti(Player &player)
{
	int suma = 0, i, val = 0;
	for (i = 0; i < player.numberCard; i++)
	{
		if (player.carti[i].valoare == 11 || player.carti[i].valoare == 12 || player.carti[i].valoare == 13)
			suma = suma + 10;
		else
		{
			if (player.carti[i].valoare == 1 && (suma + 11 == 21))
				suma = suma + 11;
			else
				suma = suma + player.carti[i].valoare;
		}
	}
	return suma;
}

int Stand() {
	while (SumaCarti(computer) < 17)
	{
		Hit(computer);
	}
	cout.flush();
	if (SumaCarti(player1) == SumaCarti(computer))
	{
		cout << "Egalitate! \ n";
	}
	else
	if (player2.userName == "")
	{
			if (SumaCarti(player1) > SumaCarti(computer))
			{
				cout << "Castigatorul este Player1 !!! (" << player1.userName << ") " << endl;
				player1.scor *= player1.scor; 
				return 0;
			}
			else
			{
				cout << "Castigatorul este Computer !!! " << endl;
				return 0;
			}
	}
	else
	{
		if (SumaCarti(player1) > SumaCarti(computer))
		{
			if (SumaCarti(player1) > SumaCarti(player2))
			{
				cout << "Castigatorul este Player1 !!! (" << player1.userName << ") " << endl;
				player1.scor *= player1.scor;
				return 0;
			}
			else
			{
				cout << "Castigatorul este Player2 !!! (" << player2.userName << ") " << endl;
				player2.scor *= player2.scor;
				return 0;
			}
		}
		if (SumaCarti(player2) > SumaCarti(computer))
		{
			if (SumaCarti(player1) < SumaCarti(player2))
			{
				cout << "Castigatorul este Player2 !!! (" << player2.userName << ") " << endl;
				player2.scor *= player2.scor;
				return 0;
			}
		}
		if (SumaCarti(player2) < SumaCarti(computer) && SumaCarti(player1) < SumaCarti(computer))
		{
			cout << "Castigatorul este Computer !!! " << endl; 
			return 0;
		}
	}
	return 0;
}

void DoubleDown(Player &player){
	player.bet = player.bet * 2;
	Hit(player);
}

void Surendder(Player &player){
	player.bet = player.bet / 2;
}

int playerWin(Player &player1, Player &player2){
	if (SumaCarti(player1) < SumaCarti(player2))
		return 2;
	else
	if (SumaCarti(player1) > SumaCarti(player2))
		return 1;
	
	return 0;
}

void Optiuni(int ok, Player &player)
{
		switch (ok)
		{
		case 1:
			Hit(player);
			break;
		case 2:
			Stand();
			break;
		case 3:
			DoubleDown(player);
			 break;
		case 4:
			player.scor += player.bet / 2;
			cout << "Sfarsitul jocului. Se va inapoia 1/2 din suma. Suma: " << player.scor << endl; break;
		}
}

void CardDel(Player player){
	for (int i = 0; i <= player.numberCard; i++)
	{
		player.carti[i].valoare=0;
	}
	player.numberCard = 2;
}

int main()
{


	int count = 0, noPlayers = 0, ok = 0, x = 1, sumPlayer1 = 0, sumPlayer2 = 0, sumComputer = 0;
	users[0].scor = 2000;
	users[1].scor = 2000;
	users[2].scor = 2000;


	//Autentificare

	cout << "*** BLACK - JACK ***" << endl << "Bine at venit!" << endl << endl;
nrJucatori:
	cout << "Pentru a incepe jocul trebuie sa: ";
	cout << " -> Introduceti numarul de jucatori ( 1 sau 2 ): ";
	cin >> noPlayers;
	system("cls");
	switch (noPlayers)
	{
	case 1:
	{
			  x = 1;
			  cout << endl << "Autentificare Player 1: " << endl;
			  userAccount(x, users);
			  x++;
			  break;
	}
	case 2:
	{
			  x = 1;
			  cout << endl << "Autentificare Player 1: " << endl;
			  userAccount(x, users);

			  inData.open("Username.dat.txt", ios::app); //pt a stoca username si parola
			  inScor.open("Scor.dat.txt", ios::app); //pt a stoca usename si scorul
			  cout << "Introduceti un username pentru Player 2:  ";
			  cin >> userName;
			  users[x].userName = userName; //stocam in fisier

			  inData.close();
			  inScor.close();
			  break;
	}
	default:
	{
			   cout << "Nu ai introdus un numar. Mai incearca." << endl;
			   goto nrJucatori;
			   break; }
	}


	// Distribuim cartile

	computer.userName = "computer";
	computer.scor = 20000;
	player1.scor = 2000;
	player2.scor = 2000;

incepeJoc:
	if (player1.scor)
	{
		cout << "Pentru a incepe jocul trebuie sa alege suma pe care jucam: ";
		cin >> count;
		if (cin.fail()) {
			//Not an int.
			cout << "\n Introduceti o SUMA!!! \n";
			goto incepeJoc;
		}
		
		//setam banii curenti 
		player1.bet = count;
		player1.scor = player1.scor - player1.bet;
		computer.numberCard = 2;
		player1.numberCard = 2;
		player2.numberCard = 2;

		if (noPlayers == 2)
		{
			player2.bet = count;
			player2.scor = player2.scor - player2.bet;
		}


		CardDel(computer);
		CardDel(player1);
		CardDel(player2);
		//selectam cartile	

		//cartile calculator	
		cardValue();
		Shuffle();
		PlayerCards(computer);
		cout << "Cartile computer sunt: " << endl;
		PrintCard(computer, 1);
		cout << endl;

		//cartile jucatorului 1
		cardValue();
		Shuffle();
		PlayerCards(player1);
		cout << "Cartile player 1 sunt: " << endl;
		PrintCard(player1, player1.numberCard);
		sumPlayer1 = SumaCarti(player1);
		cout << endl << "Suma cartilor dvs. ( " << player1.userName << " ) curenta este: " << sumPlayer1;
		cout << endl << "Suma ramasa: " << player1.scor << endl << endl << endl;

		//cartile jucatorului 2
		if (noPlayers == 2)
		{
			cardValue();
			Shuffle(); Shuffle();
			PlayerCards(player2);
			cout << "Cartile player 2 sunt: " << endl;
			PrintCard(player2, player2.numberCard);
			sumPlayer2 = SumaCarti(player2);
			cout << endl << "Suma cartilor Player 2 curenta este: " << sumPlayer2 << endl << endl << endl;
		}
		// verificam continuarea jocului in cazul in care a trecut cineva peste 21

	verificare:
		int oky = 1;
		sumPlayer1 = SumaCarti(player1);
		sumPlayer2 = SumaCarti(player2);
		sumComputer = SumaCarti(computer);
		if (oky == 1)
		{
			if (sumPlayer1 == 21 && oky)
			{
				cout << "Castigatorul este Player1 !!! (" << player1.userName << ") " << endl;
				player1.scor *= player1.scor;
				oky = 0;
				cout << "Cartile computer sunt: " << endl;
				PrintCard(computer, 2);
				cout << endl;
			}

			if (sumComputer == 21 && oky)
			{
				cout << "Castigatorul este Computer !!!" << endl;
				computer.scor *= computer.scor;
				oky = 0;
				cout << "Cartile computer sunt: " << endl;
				PrintCard(computer, 2);
				cout << endl;
			}


			if (sumPlayer1 == 21 && noPlayers == 2 && oky)
			{
				cout << "Castigatorul este Player2 !!! (" << player2.userName << ")" << endl;
				oky = 0;
				player2.scor *= player2.scor;
				cout << "Cartile computer sunt: " << endl;
				PrintCard(computer, 2);
				cout << endl;
			}

			if (sumComputer > 21 && sumPlayer1 < 21 && oky)
			{
				if (noPlayers == 1)
				{
					cout << "Sfarsitul jocului! Castigatorul este Player 1:  " << player1.userName;
					player1.scor += 25 * player1.bet / 10;
					oky = 0;
					cout << "\n Cartile computer sunt: " << endl;
					PrintCard(computer, 2);
					cout << endl;
				}
				else
				if (sumPlayer1 > sumPlayer2 || sumPlayer2 > 21)
				{
					cout << "Sfarsitul jocului! Castigatorul este Player 1:  " << player1.userName << endl;
					player1.scor += 25 * player1.bet / 10;
					oky = 0;
					cout << "Cartile computer sunt: " << endl;
					PrintCard(computer, 2);
					cout << endl;
				}
				else
				{
					cout << "Sfarsitul jocului! Castigatorul este Player 2" << endl;
					oky = 0;
					cout << "Cartile computer sunt: " << endl;
					PrintCard(computer, 2);
					cout << endl;
				}

			}
			else
			{
				if (sumComputer < 21 && sumPlayer1 > 21 && oky)
				{
					if (noPlayers == 1)
					{
						oky = 0;
						cout << "Sfarsitul jocului! Castigatorul este Computer." << endl;
						cout << "Cartile computer sunt: " << endl;
						PrintCard(computer, 2);
						cout << endl;
					}
					else
					{
						if (sumComputer > sumPlayer2 && sumPlayer2 < 21 && oky)
						{
							oky = 0;
							cout << "Sfarsitul jocului! Castigatorul este Computer." << endl;
							cout << "Cartile computer sunt: " << endl;
							PrintCard(computer, 2);
							cout << endl;
						}
						else
						{
							oky = 0;
							cout << "Sfarsitul jocului! Castigatorul este Player2." << endl;
							cout << "Cartile computer sunt: " << endl;
							PrintCard(computer, 2);
							cout << endl;
						}
					}
				}

				if (sumPlayer2 > 21 && oky)
				if (sumComputer > sumPlayer1 && sumComputer < 21)
				{
					oky = 0;
					cout << "Castigatorul jocului este Computer" << endl;
					cout << "Cartile computer sunt: " << endl;
					PrintCard(computer, 2);
					cout << endl;
				}
				else
				if (sumPlayer1 < 21 && oky)
				{
					oky = 0;
					cout << "Castigatorul jocului este Player1" << endl;
					cout << "Cartile computer sunt: " << endl;
					PrintCard(computer, 2);
					cout << endl;
				}
			}
		}
		if (oky == 0)
		{
		again:
			int okey = 0;
			cout << endl << "Doriti sa mai jucati? Apasa tasta 1 pentru DA si 0 pentru NU: " << endl;
			cout << "Optiune: ";
			cin >> okey;
			switch (okey)
			{
			case 1:
				goto incepeJoc;
				break;
			case 0:
				cout << "\n Felicitari! Ai iesit! \n";
				return 0;
				break;
			default:
				cout << "\n Nu ai ales o optiune corecta! Try again! \n";
				goto again;
				break;
			}
		}

		//Selectati optiunile de continuar a jocului
		//selectarea optiunilor pentru un jucator
		if (noPlayers == 1 && player1.numberCard == 2)
		{
			cout << "1 - Hit" << endl << "2 - Stand" << endl << "3 - Double Down " << endl << "4 - Surrender" << endl;
			cout << endl << "Optiune: ";
			cin >> ok;
			Optiuni(ok, player1);
		}
		else
		{
			if (noPlayers == 1 && player1.numberCard > 2)
			{
				cout << "Selectati optinuea pentru a continua jocul: " << endl;
				cout << "1 - Hit" << endl << "2 - Stand" << endl << "3 - Double Down " << endl;
				cout << endl << "Optiune: ";
				cin >> ok;
				Optiuni(ok, player1);
			}

		}
		if (noPlayers == 2 && player1.numberCard == 2)
		{
			cout << endl << "Player 1 -> Selectati optinuea pentru a continua jocul: " << endl;
			cout << "1 - Hit" << endl << "2 - Stand" << endl << "3 - Double Down " << endl << "4 - Surrender" << endl;
			cout << endl << "Optiune: ";
			cin >> ok;
			if (ok == 2)
			{
				Optiuni(ok, player1);
			}
			else
			{
				Optiuni(ok, player1);
				cout << endl << "Player 2 -> Selectati optinuea pentru a continua jocul: " << endl;
				cout << "Selectati optinuea pentru a continua jocul: " << endl;
				cout << "1 - Hit" << endl << "2 - Stand" << endl << "3 - Double Down " << endl;
				cout << endl << "Optiune: ";
				cin >> ok;
				Optiuni(ok, player2);
			}
		}
		else
		{
			if (noPlayers == 2 && player1.numberCard > 2)
			{

				cout << endl << "Player 1 -> Selectati optinuea pentru a continua jocul: " << endl;
				cout << "Selectati optinuea pentru a continua jocul: " << endl;
				cout << "1 - Hit" << endl << "2 - Stand" << endl << "3 - Double Down " << endl;
				cout << endl << "Optiune: ";
				cin >> ok;
				if (ok == 2)
				{
					Optiuni(ok, player1);
				}
				else
				{
					Optiuni(ok, player1);
					cout << endl << "Player 2 -> Selectati optinuea pentru a continua jocul: " << endl;
					cout << "Selectati optinuea pentru a continua jocul: " << endl;
					cout << "1 - Hit" << endl << "2 - Stand" << endl << "3 - Double Down " << endl;
					cout << endl << "Optiune: ";
					cin >> ok;
					Optiuni(ok, player2);
				}
			}

		}

		system("cls");
		cout << "Cartile computer sunt: " << endl;
		PrintCard(computer, 1);
		cout << endl << endl;

		cout << "Cartile player 1 sunt: " << endl;
		PrintCard(player1, player1.numberCard);
		cout << endl;
		sumPlayer1 = SumaCarti(player1);
		cout << endl << "Suma cartilor dvs. ( " << player1.userName << " ) curenta este: " << sumPlayer1;
		cout << endl << "Suma ramasa: " << player1.scor << endl << endl << endl;

		if (noPlayers == 2)
		{
			cout << "Cartile player2 sunt: " << endl;
			PrintCard(player2, player2.numberCard);
			cout << endl;
			sumPlayer2 = SumaCarti(player2);
			cout << endl << "Suma cartilor Player 2 curenta este: " << sumPlayer2;
			cout << endl << "Suma ramasa: " << player2.scor << endl << endl << endl;
		}


		goto verificare;

		cout << "Mai jucati ? (0 - DA / 1 - NU) : ";
		cin >> ok;
		switch (ok)
		{
		case 0:
			return 0;
			break;
		case 1:
			goto incepeJoc;
			break;
		default:
			goto verificare;
			break;
		}
		system("pause");
	}

}