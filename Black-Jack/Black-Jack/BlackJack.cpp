#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include <cstring>
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
fstream scorAux;
string userPass; //pt a cit datele din fisier
string password, line; //pt a introduce datele de catre user
string userName1, userName2, userName3;

int t[13], aux;
Player users[3];
Player &computer = users[0];
Player &player1 = users[1];
Player &player2 = users[2];


void userAccount(int x, Player users[])
{

	char option;
	bool found1 = false, found2 = false;

	cout << "Pentru a incepe jocul trebuie sa alegi o optiune: " << endl << endl << "1.Creaza un cont nou." << endl << "2.Am deja un cont creat." << endl;
	cout << endl << "Optiune aleasa: ";
	cin >> option;
	cout << endl;

	switch (option)
	{
		case '1':
			cout << "User nou Black Jack \n";
			inData.open("Username.dat.txt", ios::app); //pt a stoca username si parola
			inScor.open("Scor.dat.txt", ios::app); //pt a stoca usename si scorul
			cout << "Introduceti un username (caractere mici):  ";
			cin >> userName1;
			users[x].userName = userName1; //stocam in fisier


			cout << "Introduceti o parola:  ";
			cin >> password;
			cout << endl;

			inData << userName1 << " " << password << endl;
			inScor << userName1 << " " << users[x].scor << endl;

			inData.close();
			inScor.close();

			cout << "Felicitari! Tocmai ai fost inregistrat." << endl;
			system("cls");
			cout << "Bine ai revenit, " << userName1 << " !" << endl;
			cout << "Scorul tau curent este: " << users[x].scor << endl;
			break;
		case '2':
					cout << "Cont existent: \n";
					inData.open("Username.dat.txt", ios::in);
					cout << "Introduceti username-ul (caractere mici): ";
					cin >> userName1;
					cout << "Introduceti parola: ";
					cin >> password;
					users[x].userName = userName1;
					userPass = userName1 + " " + password;

					if (inData.is_open())
					{
						while (getline(inData, line) && !found1)// gasim usernameul si parola
						{
							if (line.compare(userPass) == 0){
								found1 = true;
							}
						}
						inData.close();

						inScor.open("Scor.dat.txt", ios::in); //cautam username si aflam scorul ramas
						if (inScor.is_open() && found1 == true)
						{
							while (getline(inScor, line) && !found2)
							{
								char *linie = (char *)alloca(line.size() + 1);
								memcpy(linie, line.c_str(), line.size() + 1);

								char *userN = (char *)alloca(userName1.size() + 1);
								memcpy(userN, userName1.c_str(), userName1.size() + 1);

								char *user, *score;
								user = strtok(linie, " ");
								score = strtok(NULL, "\n");

								if (strcmp(user, userN) == 0){ // gasim usernameul si facem conexiunea
									found2 = true;
									users[x].scor = atoi(score);
								}
							}
							inScor.close();
						}
					}
					if (found1)
					{
						cout << "Bine ai revenit, " << userName1 << " !" << endl;
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

					break;

		default:
			system("cls");
			cout << "Nu ai introdus o optiune. Mai incearca! " << endl << endl;
			userAccount(x, users);
			break;
	
	}

}

void introduceScorRamas(Player player)
{
	bool found2 = false;
	userPass = userName1;

	inScor.open("Scor.dat.txt", ios::in); //cautam username si aflam scorul ramas
	scorAux.open("scorAux.dat.txt", ios::in);
	if (inScor.is_open())
	{
		while (getline(inScor, line))
		{

			char *linie = (char *)alloca(line.size() + 1);
			memcpy(linie, line.c_str(), line.size() + 1);

			char *userN = (char *)alloca(userName1.size() + 1);
			memcpy(userN, userName1.c_str(), userName1.size() + 1);

			char *user;
			user = strtok(linie, " ");
			//score = strtok(NULL, "\n");

			if (strcmp(user, userN) > 0 && strcmp(user, userN) < 0){ 
				scorAux << line << endl;
				//	found2 = true;
				//	inScor>> 
				//	player.scor = atoi(score);
			}
			scorAux << player.userName << " " << player.scor << endl;
			inScor.close();
			scorAux.close();
			//remove("Scor.dat.txt");
			rename("scorAux.dat.txt", "Scor.dat.txt");

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
	for (int j = 1; j <= 3; j++)	// repet de 3 ori
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
	srand(time(0)); // pt a nu se repeta cartile

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
	s = rand() % 13 + 1; // caut o carte care nu a mai fost luata
	for (i = 0; i < player.numberCard; i++)
	{
		if (t[s] == player.carti[i].valoare) 
		{
			s = rand() % 13 + 1;
			i = 0;
		}
	}
		
		player.carti[player.numberCard].valoare =t[s]; //  gasesc o carte diferita o iau
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
		if (player.carti[i].valoare == 11 || player.carti[i].valoare == 12 || player.carti[i].valoare == 13) // pt Q,J,K
			suma = suma + 10;
		else
		{
			if (player.carti[i].valoare == 1 && ((21 - suma - 11) < (21 - suma - 1) && (21 - suma - 11) > 0)) //Pt AS
				suma = suma + 11;
			else
				suma = suma + player.carti[i].valoare;
		}
	}
	return suma;
}

int Stand(Player &computer, Player &player1, Player &player2) {
	int sumaCom = 0;
	sumaCom = SumaCarti(computer);

	while (SumaCarti(computer) < 17)
	{
		Hit(computer);
	}

	if (SumaCarti(player1) == SumaCarti(computer))
	{
		return 1;

	}
	else
	if (player2.userName == "")
	{
			if (SumaCarti(player1) > SumaCarti(computer))
			{
				cout << "Castigatorul este Player1 !!! (" << player1.userName << ") " << endl;
				player1.scor += player1.scor*3/2; 
				return 1;
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
				player1.scor += player1.scor*3/2;
				return 0;
			}
			else
			{
				cout << "Castigatorul este Player2 !!! (" << player2.userName << ") " << endl;
				player2.scor += player2.scor*3/2;
				return 0;
			}
		}
		if (SumaCarti(player2) > SumaCarti(computer))
		{
			if (SumaCarti(player1) < SumaCarti(player2))
			{
				cout << "Castigatorul este Player2 !!! (" << player2.userName << ") " << endl;
				player2.scor += player2.scor*3/2;
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

int Optiuni(int ok, Player &player, Player &computer,Player &player2)
{
	int aux;
		switch (ok)
		{
		case 1:
			Hit(player);
			break;
		case 2:
			aux=Stand(computer, player,player2);
			if (aux == 0)
			return 0;
		case 3:
			DoubleDown(player);
			 break;
		case 4:
			Surendder(player);
			player.scor += player.bet;
			cout << "Sfarsitul jocului. Se va inapoia 1/2 din suma. Suma: " << player.scor << endl;
			return 0;
			break;
		}
}

int Optiuni2(int ok, Player &player, Player &computer, Player &player2)
{
	int aux;
	switch (ok)
	{
	case 1:
		Hit(player2);
		break;
	case 2:
		aux = Stand(computer, player, player2);
		if (aux == 0)
		return 0;
	case 3:
		DoubleDown(player2);
		break;
	case 4:
		Surendder(player2);
		player2.scor += player2.bet;
		cout << "Sfarsitul jocului. Se va inapoia 1/2 din suma. Suma: " << player.scor << endl;
		return 0;
		break;
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
	users[0].scor = 20000;
	users[1].scor = 5000;
	users[2].scor = 5000;


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
			  cin >> userName3;
		

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
	player2.scor = 5000;

incepeJoc:
	if (player1.scor>0)
	{
		cout << "Pentru a incepe jocul trebuie sa alege suma pe care jucam: ";
		cin >> count;
		if (cin.fail()) {
			//Not an int.
			cout << "\n Introduceti o SUMA!!! \n";
			goto incepeJoc;
		}
		if (count > player1.scor)
		{
			cout << "Suma e prea mare!" << endl;
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
		Shuffle();
		PlayerCards(computer);
		cout << "Cartile computer sunt: " << endl;
		PrintCard(computer, 1);
		cout << endl;

		//cartile jucatorului 1
		cardValue();
		Shuffle();
		Shuffle(); Shuffle();
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
			if (sumPlayer1 == 21 && sumComputer == 21)
			{
				cout << "Egalitate!" << endl;
				goto again;
			}
			if (sumPlayer1 == 21 && oky)
			{
				cout << "Castigatorul este Player1 !!! (" << player1.userName << ") " << endl;
				player1.scor += player1.bet;
				oky = 0;
				cout << "Cartile computer sunt: " << endl;
				PrintCard(computer, 2);
				cout << endl;
			}

			if (sumComputer == 21 && oky)
			{
				cout << "Castigatorul este Computer !!!" << endl;
				computer.scor += computer.bet;
				oky = 0;
				cout << "Cartile computer sunt: " << endl;
				PrintCard(computer, 2);
				cout << endl;
			}


			if (sumPlayer2 == 21 && noPlayers == 2 && oky)
			{
				cout << "Castigatorul este Player2 !!! (" << player2.userName << ")" << endl;
				oky = 0;
				player2.scor += player2.bet;
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
				introduceScorRamas(player1);
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
		int ex,var;
		if (noPlayers == 1 && player1.numberCard == 2)
		{
			cout << "1 - Hit" << endl << "2 - Stand" << endl << "3 - Double Down " << endl << "4 - Surrender" << endl;
			cout << endl << "Optiune: ";
			cin >> ok;
			ex=Optiuni(ok, player1, computer, player2);
		}
		else
		{
			if (noPlayers == 1 && player1.numberCard > 2)
			{
				cout << "Selectati optinuea pentru a continua jocul: " << endl;
				cout << "1 - Hit" << endl << "2 - Stand" << endl << "3 - Double Down " << endl;
				cout << endl << "Optiune: ";
				cin >> ok;
				ex=Optiuni(ok, player1, computer, player2);
			}

		}
		if (noPlayers == 2 && player1.numberCard == 2)
		{
			cout << endl << "Player 1 -> Selectati optinuea pentru a continua jocul: " << endl;
			cout << "1 - Hit" << endl << "2 - Stand" << endl << "3 - Double Down " << endl << "4 - Surrender" << endl;
			cout << endl << "Optiune: ";
			cin >> ok;			
			ex = Optiuni(ok, player1, computer, player2);
			
			cout << endl << "Player 2 -> Selectati optinuea pentru a continua jocul: " << endl;
			cout << "Selectati optinuea pentru a continua jocul: " << endl;
			cout << "1 - Hit" << endl << "2 - Stand" << endl << "3 - Double Down " << endl << "4 - Surrender" << endl;
			cout << endl << "Optiune: ";
			cin >> ok;
			Optiuni2(ok, player1, computer, player2);
			
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
				ex = Optiuni(ok, player1, computer, player2);

				cout << endl << "Player 2 -> Selectati optinuea pentru a continua jocul: " << endl;
				cout << "Selectati optinuea pentru a continua jocul: " << endl;
				cout << "1 - Hit" << endl << "2 - Stand" << endl << "3 - Double Down " << endl;
				cout << endl << "Optiune: ";
				cin >> ok;
				Optiuni2(ok, player1, computer, player2);
				
			}

		}
		if (ex == 0)
			goto again;

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

		cout << "Mai jucati ? (1 - DA / 0 - NU) : ";
		cin >> ok;
		switch (ok)
		{
		case 0:
			introduceScorRamas(player1);
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