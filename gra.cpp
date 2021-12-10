#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <clocale>
#include <time.h>
#include <stdlib.h>

#pragma warning(disable : 4996) //ignorowanie 'błędu' przy getch() przy kompilacji
using namespace std;


//---------------------------------------------------------KLASA GRACZ


class Gracz
{
	int lvl;
	int sila;
	int zycie;
	int szczescie;
	int doswiadczenie;
	int zloto;
	int maxzycie; //maksymalne zycie
	int liczbazadan; //liczba zadan mozliwych do wykonania
	string gracz;
	int zbroja = 0;
	int miecz = 0;
	int helm = 0;
	int tarcza = 0;
public:
	Gracz() //kostruktor
	{
		lvl = 1; sila = 10; zycie = 100; szczescie = 10; doswiadczenie = 0; zloto = 100; maxzycie = 100; liczbazadan = 5;
	}
	//~Gracz(); //destruktor wywalał błędy

	//----------------------------------nazwa gracza
	void setgracz(string g)
	{
		gracz = g;
	}
	string getgracz()
	{
		return gracz;
	}

	//--------------------------------doswiadczenie
	void dodajdoswiadczenie(int d)
	{
		doswiadczenie += d;
	}
	int getdoswiadczenie()
	{
		int d = doswiadczenie;
		return d % 100;
	}
	//--------------------------------------ZŁOTO
	void dodajzloto(int g)
	{
		zloto += g;
	}
	void odejmijzloto(int x)
	{
		zloto -= x;
	}
	int getzloto()
	{
		return zloto;
	}
	//-------------------------------------LVL
	void setlvl()
	{
		if (doswiadczenie < 100) lvl = 1;
		else lvl = doswiadczenie / 100 + 1;
	}
	int getlvl()
	{
		setlvl();
		return lvl;
	}
	//-----------------------------------sila
	int getsila()
	{
		return sila;
	}
	//--------------------------------zycie
	int getzycie()
	{
		return zycie;
	}
	int getmaxzycie()
	{
		return maxzycie;
	}
	void dodajzycie()
	{
		zycie = maxzycie;
	}
	void dodajmaxzycie(int z)
	{
		maxzycie += z;
	}
	//------------------------------szczescie
	int getszczescie()
	{
		if (szczescie * 5 / lvl > 50) return 50;
		else return szczescie * 5 / lvl;
	}
	//-----------------------------zadania
	int getliczbazadan()
	{
		return liczbazadan;
	}
	void dodajliczbazadan()
	{
		liczbazadan = 5;
	}
	void odejmijliczbazadan()
	{
		liczbazadan--;
	}
	//------------------------------ekwipunek
	void zalozzbroje(int x)
	{
		zycie -= zbroja;// zdjecie starej zbroi czyli odjecie zycia
		maxzycie -= zbroja; // to samo dla max zycia
		zbroja = 0; //usuniecie z ekwipunku
		zbroja = x; //zalozenie nowej zbroi
		maxzycie += zbroja;
		zycie += zbroja; //dodanie statystyk

	}
	void zalozmiecz(int x)
	{
		sila -= miecz;
		miecz = 0; // zdjecie starej miecz
		miecz = x; //zalozenie nowej miecz
		sila += miecz;
	}
	void zalozhelm(int x)
	{
		zycie -= helm;
		maxzycie -= helm;
		helm = 0; // zdjecie starej helm
		helm = x; //zalozenie nowej helm
		maxzycie += helm;
		zycie += helm;
	}
	void zaloztarcze(int x)
	{
		szczescie -= tarcza;
		tarcza = 0; // zdjecie starej tarczy
		tarcza = x; //zalozenie nowej tarzcy
		szczescie += tarcza;
	}
	int getzbroja()
	{
		return zbroja;
	}
	int getmiecz()
	{
		return miecz;
	}
	int gethelm()
	{
		return helm;
	}
	int gettarcza()
	{
		return tarcza;
	}
	//---------------------------------walka i lochy
	void wygrana()
	{
		doswiadczenie += 100;
		zloto += 200;
	}
	void walka(int silapotwora, int zyciepotwora)
	{
		bool wygrana = 0;
		int maxzyciepotwora = zyciepotwora;
		system("cls");
		int sz = getszczescie();
		cout << gracz << " VS " << " POTWÓR";
		cout << endl << "siła: " << sila << " - " << silapotwora;
		cout << endl << "życie: [" << zycie << "/" << maxzycie << "] - [" << zyciepotwora << "/" << maxzyciepotwora << "]";
		int l = rand() % 2 + 1; //losowanie kto pierwszy zaczyna walkę
		if (l == 1) {
			cout << endl << gracz << " rozpoczyna walkę!";
			Sleep(3000);
			system("cls");
			cout << gracz << " VS " << " POTWÓR";
			cout << endl << "siła: " << sila << " - " << silapotwora;
			cout << endl << "życie: [" << zycie << "/" << maxzycie << "] - [" << zyciepotwora << "/" << maxzyciepotwora << "]";
			do
			{
				//atakuje gracz
				if ((rand() % 100 + 1) <= sz) {
					zyciepotwora -= 2 * sila;
					cout << endl << gracz << " zadał cios krytyczny! <" << sila * 2 << " pkt. obrażeń>";
				}
				//jezeli wylosowano liczbę równą lub mniejszą od % szczęscia to gracz zadaje podwójne obrażenia

				else {
					zyciepotwora -= sila;
					cout << endl << gracz << " zadał <" << sila << " pkt. obrażeń>";
				}
				Sleep(3000);

				system("cls");
				cout << gracz << " VS " << " POTWÓR";
				cout << endl << "siła: " << sila << " - " << silapotwora;
				cout << endl << "życie: [" << zycie << "/" << maxzycie << "] - [" << zyciepotwora << "/" << maxzyciepotwora << "]";
				if (zyciepotwora <= 0) {
					wygrana = 1; break;
				}
				//atakuje potwor
				if ((rand() % 100 + 1) <= 25) {
					zycie -= 2 * silapotwora;
					cout << endl << "Potwór zadał cios krytyczny! <" << silapotwora * 2 << " pkt. obrażeń>";
				}
				else {
					zycie -= silapotwora;
					cout << endl << "Potwór zadał <" << silapotwora << " pkt. obrażeń>";
				}
				Sleep(3000);
				system("cls");
				cout << gracz << " VS " << " POTWÓR";
				cout << endl << "siła: " << sila << " - " << silapotwora;
				cout << endl << "życie: [" << zycie << "/" << maxzycie << "] - [" << zyciepotwora << "/" << maxzyciepotwora << "]";
			} while (zycie > 0 && zyciepotwora > 0);
			if (zycie <= 0) wygrana = 0;

		}
		else
		{
			cout << endl << "Potwór rozpoczyna walkę!";
			Sleep(3000);
			do {
				//atakuje potwor
				if ((rand() % 100 + 1) <= 25) {
					zycie -= 2 * silapotwora;
					cout << endl << "Potwór zadał cios krytyczny! <" << silapotwora * 2 << " pkt. obrażeń>";
				}
				else {
					zycie -= silapotwora;
					cout << endl << "Potwór zadał <" << silapotwora << " pkt. obrażeń>";
				}
				Sleep(3000);

				system("cls");
				cout << gracz << " VS " << " POTWÓR";
				cout << endl << "siła: " << sila << " - " << silapotwora;
				cout << endl << "życie: [" << zycie << "/" << maxzycie << "] - [" << zyciepotwora << "/" << maxzyciepotwora << "]";
				if (zycie <= 0) {
					wygrana = 0; break;
				}
				//atakuje gracz
				if ((rand() % 100 + 1) <= sz) {
					zyciepotwora -= 2 * sila;
					cout << endl << gracz << " zadał cios krytyczny! <" << sila * 2 << " pkt. obrażeń>";
				}
				else {
					zyciepotwora -= sila;
					cout << endl << gracz << " zadał <" << sila << " pkt. obrażeń>";
				}
				Sleep(3000);
				system("cls");
				cout << gracz << " VS " << " POTWÓR";
				cout << endl << "siła: " << sila << " - " << silapotwora;
				cout << endl << "życie: [" << zycie << "/" << maxzycie << "] - [" << zyciepotwora << "/" << maxzyciepotwora << "]";

			} while (zycie > 0 && zyciepotwora > 0);
			if (zyciepotwora <= 0) wygrana = 1;
		}
		if (wygrana)
		{
			cout << endl << "Wygrałeś! Twoje nagrody to: 100 pkt doświadczenia i 200 złota!";
			dodajdoswiadczenie(100);
			dodajzloto(200);
			Sleep(3000);
		}
		else
			cout << endl << "Niestety przegrałeś!";
		Sleep(3000);
	}
};





//---------------------------------------------------------------------KLASA ZBROJOWNIA





class Zbrojownia
{

	int lvl;
	int los;
	int zbroja; int cenazbroi;  //definicja zmiennych wartosci zbroi, jej ceny 
	int miecz; int cenamiecza;
	int helm; int cenahelmu;
	int tarcza; int cenatarczy;
public:

	Zbrojownia()
	{
		losowaniewzbrojowni(1);
	}

	void setlvl(int l) //pobranie lvl gracza
	{
		lvl = l;
	}

	void losowaniewzbrojowni(int l)
	{
		setlvl(l);
		los = rand() % 2 + 4;
		zbroja = lvl * los;
		cenazbroi = los * 10;
		Sleep(1000);
		los = rand() % 2 + 2;
		miecz = lvl * los;
		cenamiecza = los * 14;
		Sleep(1000);
		los = rand() % 2 + 4;
		helm = lvl * los;
		cenahelmu = los * 10;
		Sleep(1000);
		los = rand() % 2 + 4;
		tarcza = lvl * los;
		cenatarczy = los * 10;
		Sleep(1000);
	}

	int getzbroja()
	{
		return zbroja;
	}
	int getmiecz()
	{
		return miecz;
	}
	int gethelm()
	{
		return helm;
	}
	int gettarcza()
	{
		return tarcza;
	}
	int getcenazbroi()
	{
		return cenazbroi;
	}
	int getcenamiecza()
	{
		return cenamiecza;
	}
	int getcenahelmu()
	{
		return cenahelmu;
	}
	int getcenatarczy()
	{
		return cenatarczy;
	}

};





//-----------------------KLASA LOCHY




class Lochy
{
	int nrLochu = 1;
	int nrPotwora = 1;
public:
	int getNrLochu()
	{
		return nrLochu;
	}
	int getNrPotwora()
	{
		return nrPotwora;
	}
	void setNrLochu()
	{
		if (nrPotwora == 11)
		{
			nrLochu++;
			nrPotwora = 1;
		}
	}
	void setNrPotwora()
	{
		nrPotwora++;
	}
};






//--------------------------------------KLASA POTWORY





class Potwory
{
	int sila = 15;
	int zycie = 110;
	int const szczescie = 25;
public:
	void setsila(int nrlochu, int nrpotwora)
	{
		int s = nrlochu;
		int z = nrpotwora;
		int x = s * z * 5 - 5;
		sila += x;
	}
	void setzycie(int nrlochu, int nrpotwora)
	{
		int s = nrlochu;
		int z = nrpotwora;
		int x = s * z * 10 - 10;
		zycie += x;
	}
	int getsila()
	{
		return sila;
	}
	int getzycie()
	{
		return zycie;
	}

};



//-------------------------------------------KLASA MISJE




class Misje
{
	int los;

public:

	int losujdos()
	{
		los = (rand() % 20) + 1;
		return  los;
	}
	int losujgold()
	{
		los = (rand() % 20) + 1;
		return  los;
	}
	void ladowanie()
	{
		cout << endl;
		for (int i = 1; i < 6; i++)
		{
			cout << i;  Sleep(300); cout << "."; Sleep(300); cout << "."; Sleep(300);
		}
	}


};


//-----------------------------------------

string gracz;
Gracz g;
Misje m;
Zbrojownia z;
Lochy l;
Potwory p;
int m1, m11, m2, m22, m3, m33;
string zbroja, miecz, helm, tarcza; // zmienne potrzebne do sprawdzenia czy są kupione przedmioty (zbrojownia) 
bool czyzbrojaK = 0; //czy zbroja jest już zakupiona
bool czymieczK = 0;
bool czyhelmK = 0;
bool czytarczaK = 0;

void wygrana()
{
	system("cls");
	cout << "UKOŃCZYŁEŚ GRĘ!" << endl << "GRATULACJE!!";
	Sleep(1500);
}

void przegrana()
{
	system("cls");
	cout << "PRZEGRAŁEŚ!" << endl << "NIE MASZ PIENIĘDZY NA WSKRZESZENIE!";
	cout << endl << "TO KONIEC GRY!";
	Sleep(1500);
}

void nowytowar() //funkcja ustawia powyższe zmienne na domyślne
{
	czyzbrojaK = 0;
	czymieczK = 0;
	czyhelmK = 0;
	czytarczaK = 0;
}

int main()
{
	srand(time(NULL));
	setlocale(LC_CTYPE, "Polish"); //j. polski
	//instrukcja();
	cout << "Podaj nazwę gracza: "; cin >> gracz; cout << endl;
	g.setgracz(gracz); //dodanie nazwy gracza do zmiennych 
	cout << "[WCIŚNIJ DOWOLNY PRZYCISK ABY ZACZĄĆ]";
	if (getch()) { //oczekiwanie na wcisniecie klawisza
		system("cls");
	} //usuniecie instrukcji
	system("cls");
menu:
	if (g.getzycie() <= 0 && g.getzloto() < 200) //sprawdzenie czy gracz nie jest martwy i jego stanu zlota
	{
		przegrana();
		goto koniec;
	}
	if (l.getNrLochu() == 4) //sprawdzenie czy gracz wygral gre
	{
		wygrana();
		goto koniec;
	}

	cout << "PRZYGODY RYCERZA" << endl;
	cout << "Gracz: " << g.getgracz() << endl; //wypisanie gracza
	for (int i = 0; i < 80; i++) cout << "_"; // odzielenie kreską
	cout << endl << "LVL: " << g.getlvl(); //wyświetlenie lvl w menu
	cout << " [" << g.getdoswiadczenie() << "/100] "; //wyświetlenie doświadczenia w menu
	cout << "ZŁOTO: " << g.getzloto() << " | "; //wyświetlenie zlota w menu
	cout << "SIŁA: " << g.getsila() << " | "; //wyświetlenie siły w menu
	cout << "ŻYCIE: " << "[" << g.getzycie() << "/" << g.getmaxzycie() << "]" << " | "; //wyświetlenie % szczescia w menu
	cout << "SZCZĘŚCIE: " << g.getszczescie() << "%" << endl; //wyświetlenie lvl w menu
	for (int i = 0; i < 80; i++) cout << "_"; // odzielenie kreską

	cout << endl << "[1] Misje" << endl;
	cout << "[2] Zbrojownia" << endl;
	cout << "[3] Gabinet magii" << endl; //MENU
	cout << "[4] Ekwipunek" << endl;
	cout << "[5] Lochy" << endl;
	cout << "[6] Wyjście z gry" << endl;
	cout << endl << endl << "Wybieram: ";
	int trybswitch; cin >> trybswitch;
	switch (trybswitch)
	{
	case 1: system("cls");
	misje:		cout << "MISJE" << endl;

		for (int i = 0; i < 80; i++) cout << "_"; // odzielenie kreską

		//pomiędzy każdym losem liczby jest sekundowa przerwa aby liczby były różne ( liczba jest losowana na podstawie danej sekundy)

		//sprawdzenie czy gracz nie potrzebuje wskrzeszenia

		if (g.getzycie() <= 0) {
			cout << endl << "Potrzebujesz wskrzeszenia!";
			Sleep(1500);
			system("cls");
			goto menu;
		}

		cout << endl << "Wybierz misję:" << endl; cout << "Ilość misji do wykonania: [" << g.getliczbazadan() << "/5]" << endl;

		//-----------losowanie exp i gold misja 1
		cout << "[1]" << endl;
		m1 = m.losujdos(); Sleep(1000); //przypisanie do zmiennej ilości doswiadczenia
		m11 = m.losujgold(); Sleep(1000); //przypisanie do zmiennej ilości zlota
		cout << "EXP: " << m1 << endl;
		cout << "Złoto: " << m11 << endl << endl;

		//-----------losowanie exp i gold misja 2
		cout << "[2]" << endl;
		m2 = m.losujdos(); Sleep(1000);
		m22 = m.losujgold();Sleep(1000);
		cout << "EXP: " << m2 << endl;
		cout << "Złoto: " << m22 << endl << endl;

		//-----------losowanie exp i gold misja 3
		cout << "[3]" << endl;
		m3 = m.losujdos(); Sleep(1000);
		m33 = m.losujgold();
		cout << "EXP: " << m3 << endl;
		cout << "Złoto: " << m33 << endl << endl;

		//-------------------------------------------
		cout << "[4]" << " Powrót do menu" << endl << endl;

		for (int i = 0; i < 80; i++) cout << "_"; // odzielenie kreską

		if (g.getliczbazadan() == 0) {
			cout << endl << "Ukończono dostępne misje! Zakup pakiet misji z gabinetu magii.";
			Sleep(2000);
			system("cls");
			goto menu;
		}

		int misjaswitch;
		cout << endl << endl << "Wybieram misję nr: "; cin >> misjaswitch;
		switch (misjaswitch)
		{
		case 1:
			m.ladowanie(); //metoda ukazuje animację i odejmuje liczbę misji możliwych do wykonania
			g.dodajdoswiadczenie(m1); //metoda dodaje doświadczenie
			g.dodajzloto(m11); //metoda dodaje złoto
			cout << endl << "Misja ukończona!" << endl << "Zdobyty EXP: " << m1 << " Zdobyte złoto: " << m11; //wypisanie
			g.odejmijliczbazadan(); //odjecie 1 od liczby zadan
			Sleep(3000); //3 sec pauza
			system("cls"); //wyczyszczenie konsoli
			goto misje; //powrót do menu misji
		case 2:
			m.ladowanie();
			g.dodajdoswiadczenie(m2);
			g.dodajzloto(m22);
			cout << endl << "Misja ukończona!" << endl << "Zdobyty EXP: " << m2 << " Zdobyte złoto: " << m22;
			g.odejmijliczbazadan();
			Sleep(3000);
			system("cls");
			goto misje;
		case 3:
			m.ladowanie();
			g.dodajdoswiadczenie(m3);
			g.dodajzloto(m33);
			cout << endl << "Misja ukończona!" << endl << "Zdobyty EXP: " << m3 << " Zdobyte złoto: " << m33;
			g.odejmijliczbazadan();
			Sleep(3000);
			system("cls");
			goto misje;
		case 4:
			system("cls");
			goto menu;
		default:
			system("cls");
			goto misje;
		}
	case 2:
	zbrojownia:
		system("cls");
		cout << "ZBROJOWNIA" << endl << endl;
		cout << "Posiadane złoto: " << g.getzloto() << endl; //wypisuje ilosc zlota
		for (int i = 0; i < 80; i++) cout << "_"; // odzielenie kreską

		//sprawdzenie czy gracz nie potrzebuje wskrzeszenia

		if (g.getzycie() <= 0) {
			cout << endl << "Potrzebujesz wskrzeszenia!";
			Sleep(1500);
			system("cls");
			goto menu;
		}

		if (czyzbrojaK) zbroja = "(zakupiono)"; else zbroja = " "; //sprawdzenie czy dany przedmiot jest już kupiony
		if (czymieczK) miecz = "(zakupiono)"; else miecz = " ";
		if (czyhelmK) helm = "(zakupiono)"; else helm = " ";
		if (czytarczaK) tarcza = "(zakupiono)"; else tarcza = " ";
		cout << endl << "[1] Zbroja    | +" << z.getzbroja() << " życia    -" << z.getcenazbroi() << " złota " << zbroja;
		cout << endl << "[2] Miecz     | +" << z.getmiecz() << " siły    -" << z.getcenamiecza() << " złota " << miecz;
		cout << endl << "[3] Helm      | +" << z.gethelm() << " życia    -" << z.getcenahelmu() << " złota " << helm;
		cout << endl << "[4] Tarcza    | +" << z.gettarcza() << " szczęścia    -" << z.getcenatarczy() << " złota " << tarcza;
		cout << endl << "[5] Nowy towar| " << "-30 złota" << endl;
		cout << "[6]" << " Powrót do menu" << endl << endl;
		for (int i = 0; i < 80; i++) cout << "_"; // odzielenie kreską
		int zbrojowniaswitch;
		cout << endl << endl << "Wybieram: "; cin >> zbrojowniaswitch;
		switch (zbrojowniaswitch)
		{
		case 1:
			if (czyzbrojaK) {
				cout << endl << "Ta zbroja już została zakupiona!";
				Sleep(2000);
				system("cls");
				goto zbrojownia;
			}
			else
			{
				if (g.getzloto() >= z.getcenazbroi())
				{
					g.zalozzbroje(z.getzbroja()); //zalozenie zbroi
					g.odejmijzloto(z.getcenazbroi()); // zapłata za nią
					czyzbrojaK = 1; // znacznik ze zakupiono
					cout << endl << "Zakupiono zbroje!";
					Sleep(2000);
					system("cls");
					goto zbrojownia;
				}
				else
				{
					cout << endl << "Nie masz wystarczająco dużo złota!";
					Sleep(2000);
					system("cls");
					goto zbrojownia;
				}
			}
		case 2:
			if (czymieczK) {
				cout << endl << "Ten miecz już został zakupiony!";
				Sleep(2000);
				system("cls");
				goto zbrojownia;
			}
			else
			{
				if (g.getzloto() >= z.getcenamiecza())
				{
					g.zalozmiecz(z.getmiecz());
					g.odejmijzloto(z.getcenamiecza());
					czymieczK = 1;
					cout << endl << "Zakupiono miecz!";
					Sleep(2000);
					system("cls");
					goto zbrojownia;
				}
				else
				{
					cout << endl << "Nie masz wystarczająco dużo złota!";
					Sleep(2000);
					system("cls");
					goto zbrojownia;
				}
			}
		case 3:
			if (czyhelmK) {
				cout << endl << "Ten helm już został zakupiony!";
				Sleep(2000);
				system("cls");
				goto zbrojownia;
			}
			else
			{
				if (g.getzloto() >= z.getcenahelmu())
				{
					g.zalozhelm(z.gethelm());
					g.odejmijzloto(z.getcenahelmu());
					czyhelmK = 1;
					cout << endl << "Zakupiono helm!";
					Sleep(2000);
					system("cls");
					goto zbrojownia;
				}
				else
				{
					cout << endl << "Nie masz wystarczająco dużo złota!";
					Sleep(2000);
					system("cls");
					goto zbrojownia;
				}
			}
		case 4:
			if (czytarczaK) {
				cout << endl << "Ta tarcza już została zakupiona!";
				Sleep(2000);
				system("cls");
				goto zbrojownia;
			}
			else
			{
				if (g.getzloto() >= z.getcenatarczy())
				{
					g.zaloztarcze(z.gettarcza());
					g.odejmijzloto(z.getcenatarczy());
					czytarczaK = 1;
					cout << endl << "Zakupiono tarczę!";
					Sleep(2000);
					system("cls");
					goto zbrojownia;
				}
				else
				{
					cout << endl << "Nie masz wystarczająco dużo złota!";
					Sleep(2000);
					system("cls");
					goto zbrojownia;
				}
			}
		case 5:	if (g.getzloto() >= 30)
		{
			nowytowar();
			g.odejmijzloto(30);
			cout << endl << "Za chwilę pojawi się nowy towar!";
			z.losowaniewzbrojowni(g.getlvl());
			system("cls");
			goto zbrojownia;
		}
			  else
		{
			cout << endl << "Nie masz wystarczająco dużo złota!";
			Sleep(2000);
			system("cls");
			goto zbrojownia;
		}
		case 6:
			system("cls");
			goto menu;
		default:
			system("cls");
			goto zbrojownia;
		}
	case 3:
	gabinetmagii:
		system("cls");
		cout << "GABINET MAGII" << endl << endl;
		cout << "Posiadane złoto: " << g.getzloto() << endl; //wypisuje ilosc zlota
		for (int i = 0; i < 80; i++) cout << "_"; // odzielenie kreską
		cout << endl << "[1] Dodatkowe misje (nie więcej niż 5) - 50 złota";
		cout << endl << "[2] Eliksir zdrowia (przywraca życie do pełna) - 100 złota";
		cout << endl << "[3] Wskrzeszenie - 200 złota";
		cout << endl << "[4] Wyjście do menu" << endl << endl;
		for (int i = 0; i < 80; i++) cout << "_"; // odzielenie kreską
		cout << endl << endl << "Wybieram: ";
		int sklepowyswitch; cin >> sklepowyswitch;
		switch (sklepowyswitch)
		{
			//zakup misji
		case 1:
			if (g.getzloto() >= 50) // sprawdzenie czy gracza stac na przedmiot
			{
				if (g.getliczbazadan() == 5)
				{
					cout << endl << "Masz maksymalną liczbę możliwych misji!"; //gracz ma 5/5 misji
					Sleep(2000);
					goto gabinetmagii; //powrot do sklepu
				}
				else
				{
					g.dodajliczbazadan(); //sfinalizowanie zakupy czyli 5 misji
					g.odejmijzloto(50); //odjecie zlota za zakup
					cout << endl << "Kupiono pakiet 5 misji!";
					Sleep(2000);
					goto gabinetmagii;
				}
			}
			else
			{
				cout << "Nie masz wystarczająco dużo złota!!";
				Sleep(2000);
				goto gabinetmagii;
			}
			//zakup zdrowia
		case 2:
			if (g.getzloto() >= 100)
			{
				if (g.getzycie() == g.getmaxzycie()) //sprawdzenie czy gracz nie ma maksymalnego poziomu zdrowia
				{
					cout << endl << "Masz max zdrowie!";
					Sleep(2000);
					goto gabinetmagii;
				}
				else
					if (g.getzycie() < 1)
					{
						cout << endl << "Potrzebujesz wskrzeszenia!";
						Sleep(2000);
						goto gabinetmagii;
					}
					else
					{
						g.odejmijzloto(100); //odjecie zlota za zakup
						g.dodajzycie(); //przywrocenie zdrowia
						cout << endl << "Uleczono!";
						Sleep(2000);
						goto gabinetmagii;
					}
			}
			else
			{
				cout << "Nie masz wystarczająco dużo złota!!";
				Sleep(2000);
				goto gabinetmagii;
			}
			//wskrzeszenie
		case 3:
			if (g.getzloto() >= 200)
			{
				if (g.getzycie() >= 1)
				{
					cout << endl << "Nie potrzebujesz wskrzeszenia!";
					Sleep(2000);
					goto gabinetmagii;
				}
				else
				{
					g.odejmijzloto(200);
					g.dodajzycie();
					cout << endl << "Wskrzeszono!";
					Sleep(2000);
					goto gabinetmagii;
				}
			}
			else
			{
				cout << "Nie masz wystarczająco dużo złota!!";
				Sleep(2000);
				goto gabinetmagii;
			}
			//wyjscie do menu
		case 4:
			system("cls");
			goto menu;
		default:
			system("cls");
			goto gabinetmagii;
		}
	case 4:
		system("cls");
		cout << "EKWIPUNEK" << endl;
		for (int i = 0; i < 80; i++) cout << "_"; // odzielenie kreską
		cout << endl << "HEŁM";
		if (g.gethelm() == 0) cout << " (brak)"; else cout << " +" << g.gethelm() << " życia";
		cout << endl << "ZBROJA";
		if (g.getzbroja() == 0) cout << " (brak)"; else cout << " +" << g.getzbroja() << " życia";
		cout << endl << "MIECZ";
		if (g.getmiecz() == 0) cout << " (brak)"; else cout << " +" << g.getmiecz() << " siły";
		cout << endl << "TARCZA";
		if (g.gettarcza() == 0) cout << " (brak)"; else cout << " +" << g.gettarcza() << " szczęścia" << endl << endl;
		cout << endl << endl << "[WCIŚNIJ DOWOLNY PRZYCISK ABY WRÓCIĆ DO MENU]";
		if (getch()) { //oczekiwanie na wcisniecie klawisza
			system("cls");
			goto menu;
		}
	case 5:
	lochy:
		system("cls");
		cout << "LOCHY" << endl;
		for (int i = 0; i < 80; i++) cout << "_"; // odzielenie kreską
		cout << endl << "SIŁA: " << g.getsila() << " | "; //wyświetlenie siły w menu
		cout << "ŻYCIE: " << "[" << g.getzycie() << "/" << g.getmaxzycie() << "]" << endl; //wyświetlenie % szczescia w menu
		cout << endl << "Loch: " << l.getNrLochu() << " " << " Potwór: " << l.getNrPotwora();
		cout << endl << endl << "[1] Zaatakuj potwora.";
		cout << endl << "[2] Wyjdź z lochów.";
		cout << endl << endl << "Wybieram: ";
		int loch; cin >> loch;
		switch (loch)
		{
		case 1:
			if (g.getzycie() > 0)
			{
				g.walka(p.getsila(), p.getzycie());
				if (g.getzycie() > 0)
				{
					l.setNrPotwora(); //zmiana nr potwora po wygranej
					l.setNrLochu(); //zmiana nr lochu po wygranej
					p.setsila(l.getNrLochu(), l.getNrPotwora()); //ustawienie sily nowego potwora
					p.setzycie(l.getNrLochu(), l.getNrPotwora()); //ustawienie zycia nowego potwora
				}
				system("cls");
				goto menu;
			}
			else { cout << "Potrzebujesz wskrzeszenia!"; goto menu; }
		case 2:
			system("cls");
			goto menu;
		default: system("cls"); goto lochy;
		}

	case 6:
		system("cls");
		cout << "CZY NA PEWNO CHCESZ WYJŚĆ Z GRY?" << endl << "TWÓJ POSTĘP NIE ZOSTANIE ZAPISANY!" << endl << "[1] - TAK / [2] - NIE" << endl << endl;
		cout << "Wybieram: ";
		int wyjscie;
		cin >> wyjscie;
		switch (wyjscie)
		{
		case 1: break;
		case 2:
			system("cls");
			goto menu;
		}
		break;
	default: system("cls");
		goto menu;
	}
koniec:
	return 0;
}







