// Pawel Jasinski grupa 5 semestr 1, rok 1, informatyka zaoczne
// Zadanie nr 150
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

void gotoxy(int x, int y);
int wherex();
int wherey();
int max_width();
int max_height();
void HideCursor();
const int Esq = 27; // Kod ASCII klawisza ESQ

int main(int argc, char* argv[])
{
	int x, y, x1, y1, bok, max_x, max_y;
	x = max_width(); // pobranie szerokosci okna konsoli
	y = max_height(); // pobranie wysokosci okna konsoli
	cout << "Podaj znak kodu ASCII\n";
	char znak = _getch();
	cout << "Wybrales znak: " << znak << endl;
	cout << "Wprowadz rozmiar figury\n";
	while (!(cin >> bok) || bok <= 0 || bok > y + 1) // Walidacja danych wejsciowych - rozmiar figury
	{
			cin.clear();
			while (cin.get() != '\n')
				continue;
			cout << "Wprowadzono niepoprawne dane. Wprowadz rozmiar figury\n";
	}
	HideCursor(); // ukryj kursor
	char klawisz;
	do
	{
		system("cls"); // czyszczenie ekranu
		x1 = x;
		y1 = y;
		gotoxy(x1, y1); // przejdz do wsp x, y
		cout << znak;
		for (int i = 1; i < bok; i++) //Rysuj prawa krawedz
		{
			x1--;
			y1--;
			gotoxy(x1, y1);
			cout << znak;

		}
		for (int i = 1; i < bok; i++) // Rysuj lewa krawedz
		{
			x1--;
			y1++;
			gotoxy(x1, y1);
			cout << znak;
		}

		if (bok % 2) // Warunek do rysowania belki w literze A (w zaleznosci czy rozmiar jest parzysty- aby lepiej wygladalo)
		{
			gotoxy(x1 + bok / 2 + 1, y1 - bok / 2); // Ustawiam kursor do rysowania belki
			for (int i = 0; i < (bok - 2); i++) // belka A
				cout << znak;
		}
		else
		{
			gotoxy(x1 + bok / 2, y1 - bok / 2 + 1); // Ustawiam kursor do rysowania belki A
			for (int i = 0; i < (bok - 1); i++) // belka A
				cout << znak;
		}
		max_x = max_width(); // pobranie szerokosci okna konsoli
		max_y = max_height(); // pobranie wysokosci okna konsoli
		gotoxy(x, y); // przejdz do wsp x, y
		klawisz = _getch();
		switch (klawisz)
		{
		case '+':
		{
			if ((x > bok * 2) && (y > bok - 1) && y < max_y && x < max_x) // warunki, aby figura nie wysz³a poza konsole
			{
				bok = bok + 2; // powiekszenie figury
				//Zmiana wspolrzednych poczatku figury, aby powiekszala sie wzgledem swojego srodka
				x++;
				y++;
			}
			break;
		}
		case '-':
		{
			if (bok > 2)
			{
				bok = bok - 2; // zmniejszenie figury
				//Zmiana wspolrzednych poczatku figury, aby zmniejszala sie wzgledem swojego srodka
				x--;
				y--;
			}
			break;
		} // przesuniecie w lewo
		case 75: // kod ASCII strzalki w lewo
		{
			if (x > bok * 2 - 2) // warunek, aby figura nie wyszla poza zakres konsoli
				x--;
			break;
		}  // przesuniecie w prawo
		case 77: // kod ASCII strzalki w prawo
		{
			if (x < max_x) // warunek, aby figura nie wyszla poza zakres konsoli
				x++;
			break;
		} // przesuniecie do gory
		case 72: // kod ASCII strzalki w gore
		{
			if (y > bok - 1) // warunek, aby figura nie wyszla poza zakres konsoli
				y--;
			break;
		}  // przesuniecie do dolu
		case 80: // kod ASCII strzalki w dol
		{
			if (y < max_y) // warunek, aby figura nie wyszla poza zakres konsoli
				y++;
			break;
		}
		case Esq:
		{
			break;
		} // wyjscie
		default: break;
		}

	} while (klawisz != Esq);
	return EXIT_SUCCESS;
}


// Funkcja gotoxy(int x, int y) ustawia kursor w punkcie (x,y) konsoli
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
// Funkcja wherex zwraca wspolrzedna x kursora
int wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X;
}
// Funkcja wherey zwraca wspolrzedna y kursora
int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.Y;
}
// Funkcja "ukrywa kursor"
void HideCursor()
{
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	hCCI.bVisible = FALSE;
	::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}
// Funkcja zwraca aktualny rozmiar okna konsoli (szerokosc)
int max_width()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Right;
}
// Funkcja zwraca aktualny rozmiar okna konsoli (wysokosc)
int max_height()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.srWindow.Bottom;
}