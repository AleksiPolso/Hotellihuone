#include <iostream>
#include <string>
#include <vector>

struct hotellihuone {	//structi hotellihuoneelle
	int huonenumero;
	int varausnumero;
	std::string ostaja;	//huoneen varaajan nimi
	bool varattu = true;	//true = vapaa, false = varattu
};

int valikko();
void grafiikka();
int varausvalinta();
bool varmistus(int, int, std::string, int);
int varausnumero();
void huonetiedot(hotellihuone);

int main() {
	hotellihuone ykshuoneet[150];	//Yhden henkilön huoneet
	hotellihuone kakshuoneet[150];	//Kahden henkilön huoneet
	int huoneidenmaara = rand() % 520 / 2 + 40;	//Arvotaan huoneiden maara väliltä 40-300, vain parillisia lukuja
	int varatutykshuoneet = 0;	//Talletetaan varattujen yhden henkilön huoneiden määrät
	int varatutkakshuoneet = 0;	//Sama, mutta kahden henkilön huoneille
	int valinta;	//Valikon ohjaukseen käytettävä muuttuja
	int valinta2;	//Toinen muuttuja
	int valinta3;	//Kolmas muuttuja
	bool tarkistaja = false;	// Käytetään tarkistamaan asioita
	std::string nimi;	//Huoneen varaajan nimi
	int ykskaks;	//Aliohjelmalle syötettävä muuttuja, joka kertoo onko huone 1 vai 2 henkilön huone
	std::vector<int> varausnumerot;	//Valmiiksi käytetyt varausnumerot



	for (int i = 0; i <= huoneidenmaara / 2 - 1; i++) {		//Asetetaan huoneille numerot
		ykshuoneet[i].huonenumero = i + 1;
		kakshuoneet[i].huonenumero = i + 1 + huoneidenmaara / 2;
	}


	grafiikka();

	std::cout << "\n Hei, tervetuloa huoneenvarausohjelmaan! Mitä haluaisit tehdä?\n";
	while (1 == 1) {	//Varmistetaan ettei hauska lopu koskaan
		valinta = NULL;	//Otetaan muuttujilta arvot pois aina loopin alussa
		valinta2 = NULL;
		valinta3 = NULL;
		tarkistaja = false;


		valinta = valikko();	//Kutsutaan aliohjelma, jonka avulla saadaan käyttäjältä tieto, mitä tehdään

		switch (valinta) {
		case 1:
			std::cout << "\nHaluatko varata yhden vai kahden henkilön huoneen?\n 1. Yhden henkilön huone\n 2. Kahden henkilön huone\n 3. Peruuta\n"; //Uusi hieno valikko
			valinta = varausvalinta();	//Otetaan aliohjelmalla pätevä arvo

			switch (valinta) {

			case 1:	//Varataan yhden henkilön huone
				ykskaks = 1;
				grafiikka();
				if (varatutykshuoneet == huoneidenmaara / 2) {	//Tarkistetaan, että huoneita on vapaana
					std::cout << "\n Valitettavasti meillä ei ole vapaita yhden henkilön huoneita\n";
					break;
				}

				std::cout << "\nMontako yötä?";	//Otetaan käyttäjältä öiden määrä
				while (std::cout << "\n Valinta: " && !(std::cin >> valinta2)) {	//Looppi, joka estää käyttäjää asettamasta int muuttujalle arvoa, joka ei ole numero
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					grafiikka();
					std::cout << "\nValitse jokin numero";
				}
				grafiikka();
				std::cout << "\nHaluatko valita huoneesi?\n 1. Kyllä \n 2. En \n 3. Peruuta\n";
				valinta = varausvalinta(); //Otetaan aliohjelmalla pätevä arvo
				switch (valinta) {
				case 1:
					grafiikka();
					std::cout << "\nVapaana olevat huoneet: ";
					for (int i = 0; i <= huoneidenmaara / 2 - 1; i++) {		//Kerrotaan  vapaana olevat huoneet
						switch (ykshuoneet[i].varattu) {	//En saanut tätä toimimaan if lauseella, mutta switchin kanssa ei ollut ongelmia
						case 1:
							std::cout << ykshuoneet[i].huonenumero << " ";
							break;
						}
					}
					while (tarkistaja == false) {	//Kysytään käyttäjältä, mikä huone varataan
						while (std::cout << "\n Valinta: " && !(std::cin >> valinta3)) {	//Looppi, joka estää käyttäjää asettamasta int muuttujalle arvoa, joka ei ole numero
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							grafiikka();
							std::cout << "\nValitse jokin numero";
						}
						if (valinta3 < 1 || valinta3 > huoneidenmaara / 2) {	//Tarkistetaan, että huone on olemassa
							grafiikka();
							std::cout << "\nValtise jokin edellä mainituista huoneista";
						}
						else if (ykshuoneet[valinta3 - 1].varattu == true) {
							tarkistaja = true;
						}
						else {
							std::cout << "Huone on varattu";
						}

					}
					break;
				case 2:	//Tehdään satunnainen huonenumero
					grafiikka();
					while (tarkistaja == false) {	//Arvotaan satunnaisia numeroita, kunnes saadaan vapaa huone
						valinta3 = rand() % (huoneidenmaara / 2) + 1;
						switch (ykshuoneet[valinta3 - 1].varattu) {	//En saanut tätä toimimaan if lauseella, mutta switchin kanssa ei ollut ongelmia
						case 1:
							tarkistaja = true;
							break;
						}
					}
					std::cout << "\nHuonenumerosi on " << valinta3 << "\n";
					break;
				case 3:	//Keskeytetään varauksen teko
					break;
				}
				grafiikka();
				std::cout << "\nMillä nimellä huone varataan?\n Valinta: ";	//Otetaan varaajan nimi
				std::cin.ignore();
				std::getline(std::cin, nimi);

				tarkistaja = varmistus(valinta2, valinta3, nimi, ykskaks);	//Varmistetaan, että käyttäjä haluaa varata huoneen asettamillaan tiedoilla
				if (tarkistaja == true) {	//Kirjataan varauksen tiedot huoneeseen
					ykshuoneet[valinta3 - 1].ostaja = nimi;
					ykshuoneet[valinta3 - 1].varattu = false;
					varatutykshuoneet++;	//Lisätään varattujen huoneiden määrään 1
					valinta = varausnumerot.size();	//Otetaan varausnumero vektorin koko talteen
					grafiikka();
					do {
						tarkistaja = true;
						valinta2 = varausnumero();	//Talletetaan muuttujaan satunnainen varausnumero
						for (int i = 0; i < valinta; i++) {	//Tarkistetaan, ettei satunnaista varausnumeroa ole vielä käytössä
							if (varausnumerot[i] == valinta2) {
								tarkistaja == false;
							}
						}
					} while (tarkistaja == false);
					ykshuoneet[valinta3 - 1].varausnumero = valinta2;
					varausnumerot.push_back(valinta2);

					std::cout << "\nHuone " << valinta3 << " on nyt varattu nimellä " << nimi << " ja varausnumerolla " << valinta2 << "\n";
				}
				else { std::cout << "\n"; }
				break;



			case 2:	//Varataan 2 henkilön huone
				ykskaks = 2;
				grafiikka();
				if (varatutkakshuoneet == huoneidenmaara / 2) {	//Tarkistetaan, että huoneita on vapaana
					std::cout << "\n Valitettavasti meillä ei ole vapaita kahden henkilön huoneita\n";
					break;
				}

				std::cout << "\nMontako yötä?";	//Otetaan käyttäjältä öiden määrä
				while (std::cout << "\n Valinta: " && !(std::cin >> valinta2)) {	//Looppi, joka estää käyttäjää asettamasta int muuttujalle arvoa, joka ei ole numero
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					grafiikka();
					std::cout << "\nValitse jokin numero";
				}
				grafiikka();
				std::cout << "\nHaluatko valita huoneesi?\n 1. Kyllä \n 2. En \n 3. Peruuta\n";
				valinta = varausvalinta(); //Otetaan aliohjelmalla pätevä arvo
				switch (valinta) {
				case 1:
					grafiikka();
					std::cout << "\nVapaana olevat huoneet: ";
					for (int i = 0; i <= huoneidenmaara / 2 - 1; i++) {		//Kerrotaan  vapaana olevat huoneet
						switch (kakshuoneet[i].varattu) {
						case 1:
							std::cout << kakshuoneet[i].huonenumero << " ";
							break;
						}
					}
					while (tarkistaja == false) {	//Kysytään käyttäjältä, mikä huone varataan
						while (std::cout << "\n Valinta: " && !(std::cin >> valinta3)) {	//Looppi, joka estää käyttäjää asettamasta int muuttujalle arvoa, joka ei ole numero
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							grafiikka();
							std::cout << "\nValitse jokin numero";
						}
						if (valinta3 < huoneidenmaara / 2 + 1 || valinta3 > huoneidenmaara) {	//Tarkistetaan, että huone on olemassa
							grafiikka();
							std::cout << "\nValtise jokin edellä mainituista huoneista";
						}
						else if (kakshuoneet[valinta3 - 31].varattu == true) {
							tarkistaja = true;
						}
						else {
							std::cout << "Huone on varattu";
						}

					}
					break;
				case 2:	//Tehdään satunnainen huonenumero
					grafiikka();
					while (tarkistaja == false) {	//Arvotaan satunnaisia numeroita, kunnes saadaan vapaa huone
						valinta3 = rand() % (huoneidenmaara / 2) + 31;
						switch (kakshuoneet[valinta3 - 31].varattu) {	//En saanut tätä toimimaan if lauseella, mutta switchin kanssa ei ollut ongelmia
						case 1:
							tarkistaja = true;
							break;
						}
					}
					std::cout << "\nHuonenumerosi on " << valinta3 << "\n";
					break;
				case 3:	//Keskeytetään varauksen teko
					break;
				}
				grafiikka();
				std::cout << "\nMillä nimellä huone varataan?\n Valinta: ";	//Otetaan varaajan nimi
				std::cin.ignore();
				std::getline(std::cin, nimi);

				tarkistaja = varmistus(valinta2, valinta3, nimi, ykskaks);	//Varmistetaan, että käyttäjä haluaa varata huoneen asettamillaan tiedoilla
				if (tarkistaja == true) {	//Kirjataan varauksen tiedot huoneeseen
					kakshuoneet[valinta3 - 31].ostaja = nimi;
					kakshuoneet[valinta3 - 31].varattu = false;
					varatutkakshuoneet++;	//Lisätään varattujen huoneiden määrään 1
					valinta = varausnumerot.size();	//Otetaan varausnumero vektorin koko talteen
					grafiikka();
					do {
						tarkistaja = true;
						valinta2 = varausnumero();	//Talletetaan muuttujaan satunnainen varausnumero
						for (int i = 0; i < valinta; i++) {	//Tarkistetaan, ettei satunnaista varausnumeroa ole vielä käytössä
							if (varausnumerot[i] == valinta2) {
								tarkistaja == false;
							}
						}
					} while (tarkistaja == false);
					kakshuoneet[valinta3 - 31].varausnumero = valinta2;
					varausnumerot.push_back(valinta2);

					std::cout << "\nHuone " << valinta3 << " on nyt varattu nimellä " << nimi << " ja varausnumerolla " << valinta2 << "\n";
				}
				else { std::cout << "\n"; }
				break;
			case 3:	//Keskeytetään varausken teko
				break;
			}
			break;



		case 2:	//Tarkistetaan vapaana olevat huoneet
			std::cout << "\nVapaita huoneita on yhteensä " << huoneidenmaara - varatutykshuoneet - varatutkakshuoneet;
			std::cout << "\nVapaana olevat yhden henkilönhuoneet ovat: \n";	//Ilmoitetaan vapaana olevat huoneet
			for (int i = 0; i <= huoneidenmaara / 2 - 1; i++) {		//Kerrotaan ensiksi vapaana olevat yhden henkilön huoneet
				switch (ykshuoneet[i].varattu) {
				case 1:
					std::cout << ykshuoneet[i].huonenumero << " ";
					break;
				}
			}
			std::cout << "\nVapaana olevat kahden henkilönhuoneet ovat: \n"; //Kerrotaan toiseksi vapaana olevat kahden henkilön huoneet
			for (int i = 0; i <= huoneidenmaara / 2 - 1; i++) {


				switch (kakshuoneet[i].varattu) {
				case 1:
					std::cout << kakshuoneet[i].huonenumero << " ";
					break;
				}

			}
			std::cout << "\n";
			break;


		case 3:	//Tarkistetaan varatut huoneet
			std::cout << "\nVarattuja huoneita on yhteensä " << varatutykshuoneet + varatutkakshuoneet;
			std::cout << "\nVaratut yhden henkilönhuoneet ovat: \n";	//Ilmoitetaan varatuthuoneet
			for (int i = 0; i <= huoneidenmaara / 2 - 1; i++) {		//Kerrotaan ensiksi varatut yhden henkilön huoneet
				switch (ykshuoneet[i].varattu) {
				case 0:
					std::cout << ykshuoneet[i].huonenumero << " ";
				}
			}
			std::cout << "\nVaratut kahden henkilönhuoneet ovat: \n";
			for (int i = 0; i <= huoneidenmaara / 2 - 1; i++) {		//Kerrotaan toiseksi varatut kahden henkilön huoneet
				switch (kakshuoneet[i].varattu) {
				case 0:
					std::cout << kakshuoneet[i].huonenumero << " ";
				}
			}
			std::cout << "\n";

			break;


		case 4:	//Etsitään huoneita
			std::cout << "\nMiten haluat etsiä huoneita?\n 1. Huonenumero\n 2. Varausnumero\n 3. Varaajan nimi\n 4. Peruuta\n";		//Kiva valikko taas vaihteeksi
			valinta = 0;	//Nollataan valinta
			while (valinta < 1 || valinta > 4) {	//Looppi, kunnes käyttäjä antaa pätevän arvon
				while (std::cout << " Valinta: " && !(std::cin >> valinta)) {	//Looppi, joka estää käyttäjää asettamasta int muuttujalle arvoa, joka ei ole numero
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					grafiikka();
					std::cout << " \nValitse 1,2,3 tai 4\n";
				}
				if (valinta < 1 || valinta > 4) {
					grafiikka();
					std::cout << " \nValitse 1,2,3 tai 4\n";
				}
			}
			grafiikka();
			switch (valinta) {
			case 1:	//Etsitään huonenumeron perusteella
				std::cout << "\nEtsitään huonenumeron perusteella\n";
				while (std::cout << " Valinta: " && !(std::cin >> valinta)) {	//Looppi, joka estää käyttäjää asettamasta int muuttujalle arvoa, joka ei ole numero
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					grafiikka();
					std::cout << " \nValitse numero\n";
				}
				if (valinta >= 1 && valinta <= 30) {	//Katsotaan onko huone 1 hengen huone
					huonetiedot(ykshuoneet[valinta - 1]);
				}
				else if (valinta >= 31 && valinta <= 60) {	//Vaiko 2 hengen huone
					huonetiedot(kakshuoneet[valinta - 31]);
				}
				else {	//Virhetilanne
					grafiikka();
					std::cout << "\nHuonetta, jonka huonenumero on " << valinta << " ei ole olemassa\n";
				}
				break;
			case 2: //Etsitään Varausnumeron perusteella
				std::cout << "\nEtsitään varausnumeron perusteella\n";
				while (std::cout << " Valinta: " && !(std::cin >> valinta)) {	//Looppi, joka estää käyttäjää asettamasta int muuttujalle arvoa, joka ei ole numero
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					grafiikka();
					std::cout << " \nValitse numero\n";
				}
				tarkistaja = false;		//Asetetaan tarkistaja 
				for (int i = 0; i <= huoneidenmaara / 2 - 1; i++) {	//Katsotaan onko varausnumerolla yhden henkilön huoneita
					if (ykshuoneet[i].varausnumero == valinta) {
						huonetiedot(ykshuoneet[i]);	// Jos on tulostetaan tiedot ja asetetaan tarkistaja trueksi
						tarkistaja = true;
					}
				}
				for (int i = 0; i <= huoneidenmaara / 2 - 1; i++) {	//Sama kun äskeinen, mutta kahden henkilön huoneilla
					if (kakshuoneet[i].varausnumero == valinta) {
						huonetiedot(kakshuoneet[i]);
						tarkistaja = true;
					}

				}
				if (tarkistaja == false) {	//Mikäli huonetta ei löytynyt 
					grafiikka();
					std::cout << "\nKyseisellä numerolla ei ole varauksia\n";
				}

				break;
			case 3:
				std::cout << "\nEtsitään nimen perusteella\n Valinta: ";
				std::cin.ignore();
				std::getline(std::cin, nimi);
				tarkistaja = false;		//Asetetaan tarkistaja 
				for (int i = 0; i <= huoneidenmaara / 2 - 1; i++) {	//Katsotaan onko nimellä yhden henkilön huoneita
					if (ykshuoneet[i].ostaja == nimi) {
						huonetiedot(ykshuoneet[i]);	// Jos on tulostetaan tiedot ja asetetaan tarkistaja trueksi
						tarkistaja = true;
					}
				}
				for (int i = 0; i <= huoneidenmaara / 2 - 1; i++) {	//Sama kun äskeinen, mutta kahden henkilön huoneilla
					if (kakshuoneet[i].ostaja == nimi) {
						huonetiedot(kakshuoneet[i]);
						tarkistaja = true;
					}

				}
				if (tarkistaja == false) {	//Mikäli huonetta ei löytynyt 
					grafiikka();
					std::cout << "\nKyseisellä nimellä ei ole varauksia\n";
				}

			}
			break;


		case 5:std::cout << "\nValitsit 5\n";	//Checkout
			grafiikka();
			std::cout << "\nMiten haluat luovuttaa huoneesi?\n 1. Huonenumero\n 2. Varausnumero\n 3. Varaajan nimi\n 4. Peruuta\n";		//Kiva valikko taas vaihteeksi
			valinta = 0;	//Nollataan valinta
			while (valinta < 1 || valinta > 4) {	//Looppi, kunnes käyttäjä antaa pätevän arvon
				while (std::cout << " Valinta: " && !(std::cin >> valinta)) {	//Looppi, joka estää käyttäjää asettamasta int muuttujalle arvoa, joka ei ole numero
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					grafiikka();
					std::cout << " \nValitse 1,2,3 tai 4\n";
				}
				if (valinta < 1 || valinta > 4) {
					grafiikka();
					std::cout << " \nValitse 1,2,3 tai 4\n";
				}
			}
			grafiikka();
			switch (valinta) {
			case 1:	//Etsitään huonenumeron perusteella
				std::cout << "\nLuovutetaan huonenumeron perusteella\n";
				while (std::cout << " Valinta: " && !(std::cin >> valinta)) {	//Looppi, joka estää käyttäjää asettamasta int muuttujalle arvoa, joka ei ole numero
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					grafiikka();
					std::cout << " \nValitse numero\n";
				}
				tarkistaja = false;		//Asetetaan tarkistaja 
				for (int i = 0; i <= huoneidenmaara / 2 - 1; i++) {	//Katsotaan onko huonenumerolla yhden henkilön huoneita
					if (ykshuoneet[i].huonenumero == valinta && ykshuoneet[i].varattu == false) {	// Jos on poistetaan huoneesta varaukseen liittyvät arvot
						ykshuoneet[i].ostaja = "";
						ykshuoneet[i].varattu = true;
						ykshuoneet[i].varausnumero = NULL;
						varatutykshuoneet--;	//Otetaan varattujen huoneiden määrästä 1 pois
						grafiikka();
						std::cout << "\n Huone on luovutettu\n";	//Ilmoitetaan onnistumisesta ja asetetaan tarkistaja trueksi
						tarkistaja = true;
					}
				}
				for (int i = 0; i <= huoneidenmaara / 2 - 1; i++) {	//Sama kun äskeinen, mutta kahden henkilön huoneilla
					if (kakshuoneet[i].huonenumero == valinta && kakshuoneet[i].varattu == false) {
						kakshuoneet[i].ostaja = "";
						kakshuoneet[i].varattu = true;
						kakshuoneet[i].varausnumero = NULL;
						varatutkakshuoneet--;
						grafiikka();
						std::cout << "\n Huone on luovutettu\n";
						tarkistaja = true;
					}

				}
				if (tarkistaja == false) {	//Mikäli huonetta ei löytynyt 
					grafiikka();
					std::cout << "\nKyseiseistä huonetta ei ole varattu\n";
				}

				break;
			case 2: //Etsitään Varausnumeron perusteella
				std::cout << "\Luovutetaan varausnumeron perusteella\n";
				while (std::cout << " Valinta: " && !(std::cin >> valinta)) {	//Looppi, joka estää käyttäjää asettamasta int muuttujalle arvoa, joka ei ole numero
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					grafiikka();
					std::cout << " \nValitse numero\n";
				}
				tarkistaja = false;		//Asetetaan tarkistaja 
				for (int i = 0; i <= huoneidenmaara / 2 - 1; i++) {	//Katsotaan onko varausnumerolla yhden henkilön huoneita
					if (ykshuoneet[i].varausnumero == valinta && ykshuoneet[i].varattu == false) {	// Jos on poistetaan huoneesta varaukseen liittyvät arvot
						ykshuoneet[i].ostaja = "";
						ykshuoneet[i].varattu = true;
						ykshuoneet[i].varausnumero = NULL;
						varatutykshuoneet--;	//Otetaan varattujen huoneiden määrästä 1 pois
						grafiikka();
						std::cout << "\n Huone on luovutettu\n";	//Ilmoitetaan onnistumisesta ja asetetaan tarkistaja trueksi
						tarkistaja = true;
					}
				}
				for (int i = 0; i <= huoneidenmaara / 2 - 1; i++) {	//Sama kun äskeinen, mutta kahden henkilön huoneilla
					if (kakshuoneet[i].varausnumero == valinta && kakshuoneet[i].varattu == false) {
						kakshuoneet[i].ostaja = "";
						kakshuoneet[i].varattu = true;
						kakshuoneet[i].varausnumero = NULL;
						varatutkakshuoneet--;
						grafiikka();
						std::cout << "\n Huone on luovutettu\n";
						tarkistaja = true;
					}

				}
				if (tarkistaja == false) {	//Mikäli huonetta ei löytynyt 
					grafiikka();
					std::cout << "\nKyseisellä numerolla ei ole varauksia\n";
				}

				break;
			case 3:
				std::cout << "\Luovutetaan nimen perusteella\n Valinta: ";
				std::cin.ignore();
				std::getline(std::cin, nimi);
				tarkistaja = false;		//Asetetaan tarkistaja 
				for (int i = 0; i <= huoneidenmaara / 2 - 1; i++) {	//Katsotaan onko nimellä yhden henkilön huoneita
					if (ykshuoneet[i].ostaja == nimi && ykshuoneet[i].varattu == false) {	// Jos on poistetaan huoneesta varaukseen liittyvät arvot
						ykshuoneet[i].ostaja = "";
						ykshuoneet[i].varattu = true;
						ykshuoneet[i].varausnumero = NULL;
						varatutykshuoneet--;	//Otetaan varattujen huoneiden määrästä 1 pois
						grafiikka();
						std::cout << "\n Huone on luovutettu\n";	//Ilmoitetaan onnistumisesta ja asetetaan tarkistaja trueksi
						tarkistaja = true;
					}
				}
				for (int i = 0; i <= huoneidenmaara / 2 - 1; i++) {	//Sama kun äskeinen, mutta kahden henkilön huoneilla
					if (kakshuoneet[i].ostaja == nimi && kakshuoneet[i].varattu == false) {
						kakshuoneet[i].ostaja = "";
						kakshuoneet[i].varattu = true;
						kakshuoneet[i].varausnumero = NULL;
						varatutkakshuoneet--;
						grafiikka();
						std::cout << "\n Huone on luovutettu\n";
						tarkistaja = true;
					}

				}
				if (tarkistaja == false) {	//Mikäli huonetta ei löytynyt 
					grafiikka();
					std::cout << "\nKyseisellä nimellä ei ole varauksia\n";
				}

			}
			break;
			break;
		case 6:std::cout << "\nKiitos kun käytit hotellinvarausohjelmaa!\nTervetula uudelleen!\n";	//Lopetetaan ohjelman käyttö
			grafiikka();
			std::cout << "\n\n";
			return 0;
		}
	}
}


void grafiikka() {		//Tehdään tällä kivoja viivoja valikoihin
	for (int i = 1; i <= 70; i++) {
		std::cout << "-";
	}
}


int valikko() {
	int valinta = 0; //Muuttuja, jonka arvo palautetaan pääohjelmaan

	grafiikka();
	std::cout << "\n 1. Varaa huone \n 2. Tarkista vapaana olevat huoneet \n 3. Tarkista varatut huoneet \n 4. Etsi varattuja huoneita \n 5. Checkout\n 6. Sulje ohjelma\n"; //Valikko


	while (valinta < 1 || valinta > 6) {	//Looppi, kunnes käyttäjä antaa pätevän arvon
		while (std::cout << " Valinta: " && !(std::cin >> valinta)) {	//Looppi, joka estää käyttäjää asettamasta int muuttujalle arvoa, joka ei ole numero
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			grafiikka();
			std::cout << " \nValitse 1,2,3,4,5 tai 6\n";
		}
		if (valinta < 1 || valinta > 6) {
			grafiikka();
			std::cout << " \nValitse 1,2,3,4,5 tai 6\n";
		}
	}
	grafiikka();
	return valinta;
}



int varausvalinta() {
	int valinta = 0;
	while (valinta < 1 || valinta > 3) {	//Looppi, kunnes käyttäjä antaa pätevän arvon
		while (std::cout << " Valinta: " && !(std::cin >> valinta)) {	//Looppi, joka estää käyttäjää asettamasta int muuttujalle arvoa, joka ei ole numero
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			grafiikka();
			std::cout << " \nValitse 1,2 tai 3\n";
		}
		if (valinta < 1 || valinta > 3) {
			grafiikka();
			std::cout << " \nValitse 1,2 tai 3\n";
		}
	}
	return valinta;
}


bool varmistus(int valinta2, int valinta3, std::string nimi, int ykskaks) {	//Kerrotaan käyttäjälle varattavan huoneen tiedot ja hinta
	double alennus = rand() % 2;	//Katostaan satunnainen alennus
	int hinta;	//Otetaan huoneen hinta
	int valinta = 0; //Käyttäjältä kysytään taas valinta

	if (ykskaks == 1) {
		hinta = 100;
	}
	else if (ykskaks == 2) {
		hinta = 150;
	}
	grafiikka();

	std::cout << "\nOlet varaamassa huoneen " << valinta3 << ", " << valinta2 << " yön ajaksi nimellä " << nimi << "\n"; //Ilmoitetaan huoneen tiedot
	if (alennus == 0) {	//Jos ei alennusta
		std::cout << "Huoneesi hinta on " << hinta * valinta2 << "€\n";
	}
	else if (alennus == 1) {
		std::cout << "Olet saanut huoneeseesi 10% alennuksen.\nHuoneesi hinta on " << hinta * valinta2 - (hinta * valinta2 * 0.1) << "€\n";
	}
	else if (alennus == 2) {
		std::cout << "Olet saanut huoneeseesi 20% alennuksen.\nHuoneesi hinta on " << hinta * valinta2 - (hinta * valinta2 * 0.2) << "€\n";
	}
	std::cout << "Haluatko varata huoneen näillä tiedoilla?\n 1. Kyllä\n 2. En\n";

	while (valinta < 1 || valinta > 2) {	//Looppi, kunnes käyttäjä antaa pätevän arvon
		while (std::cout << " Valinta: " && !(std::cin >> valinta)) {	//Looppi, joka estää käyttäjää asettamasta int muuttujalle arvoa, joka ei ole numero
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			grafiikka();
			std::cout << " \nValitse 1 tai 2\n";
		}
		if (valinta < 1 || valinta > 5) {
			grafiikka();
			std::cout << " \nValitse 1 tai 2\n";
		}
	}
	if (valinta == 1) {
		return true;
	}
	else if (valinta == 2) {
		return false;
	}

}
int varausnumero() {
	return (rand() % 89999 + 10000);
}

void huonetiedot(hotellihuone huone) {
	grafiikka();
	std::cout << "\nHuonenumero: " << huone.huonenumero;
	if (huone.varattu == false) {
		std::cout << "\nVarausnumero: " << huone.varausnumero << "\nHuoneen on varannut " << huone.ostaja << "\n";
	}
	else {
		std::cout << "\nHuone ei ole tällä hetkellä varattu\n";
	}
}