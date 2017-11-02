// ConsoleApplication1.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
// geändert, damit die Verzeichnisse stimmten
// https://www.libgosu.org/cpp/namespace_gosu.html

#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>


#include <vector>
#include <iostream>
#include <math.h>
#include "string.h"
#include <memory>
#include <string>
#include <forward_list>
#include <fstream> 
#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;



class Huhn
{
public:
	bool Sichtbarkeit, Wandern, von_links_wandern;
	double XPos, YPos, ZEbene, Winkel, PfAwX, PfAwY, SkalX, SkalY,  Höhe, Breite, start_wandern, Faktor_Bewegung, Punkte;
	
	string JPG;
	Gosu::Image Bild;

	void draw()
	{
		if (this->Wandern && this->Sichtbarkeit && this->von_links_wandern) { this->XPos = this->XPos +( 1 * this->Faktor_Bewegung); }
		if (this->Wandern && this->Sichtbarkeit && !(this->von_links_wandern)) { this->XPos = this->XPos -( 1 * this->Faktor_Bewegung); }
		//else if (this->Wandern && (this->XPos >= 1920+ this->Breite))	{this->XPos = this->start_wandern;}
		if (this->XPos + this->Breite > 1920) { this->Sichtbarkeit = false; this->XPos = this->start_wandern; }

		if (this->Sichtbarkeit) { this->ZEbene = 7; }
		else { this->ZEbene = -7; }



		Bild.draw_rot(
			this->XPos,				//X-Position
			this->YPos,				//Y-Position
			this->ZEbene,				//Z-Ebene
			this->Winkel,					//Winkel
			this->PfAwX,				// Punkt für Angriffswinkel X
			this->PfAwY,				// Punkt für Angriffswinkel X
			this->SkalX,				// Skalierung X
			this->SkalY,				// Skalierung Y
			Gosu::Color::WHITE
			//Gosu::AlphaMode::AM_INTERPOLATE
		);

	}

	int getroffen(double x, double y)
		// Die Funktion später nur ausführen wenn ein gültiger Klick gemacht wurde
	{




		if (((x >= this->XPos) && (x <= (this->XPos + Breite))) &&
			((y >= this->YPos) && (y <= (this->YPos + Höhe))) && this->Sichtbarkeit)
		{
			cout << "XPos: " << this->XPos << endl;
			cout << "YPos: " << this->YPos << endl;
			cout << "Breite: " << this->Breite << endl;
			cout << "Höhe: " << this->Höhe << endl;

			this->ZEbene = -7;
			Sichtbarkeit = false;
			if (this->Wandern && this->von_links_wandern)	{this->XPos = - this->Breite;}
			if (this->Wandern && !this->von_links_wandern) { this->XPos = 1920 + this->Breite; }

			return this->Punkte;

		}
		else
		{
			return 0;
		}

	}
	Huhn(bool sichtbarkeit, bool wandern, bool von_wandern, double Faktor_speed, double xpos, double ypos, double zebene, double winkel,
		double pfawx, double pfawy, double skalx, double skaly, double punkte, string jpg)
		: Bild(jpg)


	{
		this->SkalX = skalx;
		this->SkalY = skaly;

		this->Höhe = this->Bild.height() * this->SkalY;
		this->Breite = this->Bild.width() * this->SkalX;

		cout << "Höhe: " << this->Höhe << endl;
		cout << "Breite: " << this->Breite << endl;

		this->Sichtbarkeit = sichtbarkeit;
		this->Wandern = wandern;
		this->von_links_wandern = von_wandern;
		this->Faktor_Bewegung = Faktor_speed;
		this->XPos = xpos;
		this->YPos = ypos;
		this->ZEbene = zebene;
		this->Winkel = winkel;
		this->PfAwX = pfawx;
		this->PfAwY = pfawy;

		this->Punkte = punkte;
		this->JPG = jpg;

		if (this->Wandern && this->von_links_wandern) { this->XPos = - this->Breite; }
		if (this->Wandern && !this->von_links_wandern) { this->XPos = 1920 +this->Breite; }



		// #tim muss noch unterscheidung rein, wenns von rechts wandern soll muss es anderen Startwert haben...
		if (this->Wandern)
		{
			this->start_wandern = -this->Breite;
			this->XPos = this->start_wandern;
		}

	}

};




class GameWindow : public Gosu::Window {
public:
	Gosu::Image background;
	Gosu::Image background_finished;
	Gosu::Image Schuss;
	Gosu::Sample shot;
	Gosu::Sample reload;
	Gosu::Sample empty;
	//Gosu::Image ImgH1;
	//Gosu::Image ImgH2;
	Gosu::Font Punkte_Anzeige;
	Gosu::Font Punkte_Überschrift;
	Gosu::Font Zeit_Anzeige;
	Gosu::Font Zeit_Überschrift;



	GameWindow()
		:Window(1920, 1200)
		, background("Back.jpg"), background_finished("Screen_finished.png"), Schuss("Schuss.png"), /*ImgH1("H1.jpg"), ImgH2("H1.jpg"),*/ shot("shot.wav"), reload("reload.wav"), empty("leer.wav"),
		Punkte_Anzeige(80), Punkte_Überschrift(40), Zeit_Anzeige(80), Zeit_Überschrift(40)

	{
		set_caption("Gosu Tutorial Game");

		Huehner.clear();

		/*Huhn(bool sichtbarkeit, bool wandern, bool von_wandern, double Faktor_speed, double xpos, double ypos, double zebene, double winkel,
		double pfawx, double pfawy, double skalx, double skaly, double punkte, string jpg)
		: Bild(jpg)*/

		Huhn H01(false, false, true, 1, 120, 450, -7, 0, 0, 0, 0.2, 0.2, 25, "MH_Zeitung.png");		//Auf Heuballen
		Huhn H02(false, false, true, 1, 245, 620, -7, 0, 0, 0, 0.5, 0.5, 25, "MH_Gangsta.png");		//Rechts neben Heuballen
		Huhn H03(false, false, true, 1, 65, 281, -7, 0, 0, 0, 0.2, 0.2, 25, "MH_Zeitung.png");		//ganz links Scheunendach
		Huhn H04(false, false, true, 1, 765, 75, -7, 0, 0, 0, 0.2, 0.2, 25, "MH_Zeitung.png");		//Eier auf Strommasten
		Huhn H05(false, false, true, 1, 910, 155, -7, 0, 0, 0, 0.2, 0.2, 25, "MH_Zeitung.png");		//Schornstein Mitte
		Huhn H06(false, false, true, 1, 1600, 130, -7, 0, 0, 0, 0.2, 0.2, 25, "MH_Zeitung.png");		//Schornstein rechts
		Huhn H07(false, false, true, 1, 990, 410, -7, 0, 0, 0, 0.2, 0.2, 25, "MH_Zeitung.png");		//Zaun links
		Huhn H08(false, false, true, 1, 1360, 400, -7, 0, 0, 0, 0.2, 0.2, 25, "MH_Zeitung.png");		//Zaun mitte
		Huhn H09(false, false, true, 1, 1780, 450, -7, 0, 0, 0, 0.2, 0.2, 25, "MH_Zeitung.png");		//Zaun rechts
		Huhn H10(false, false, true, 1, 800, 600, -7, 0, 0, 0, 1, 1, 1, "MH_Gangsta.png");		//Rechts neben Heuballen*/

		Huhn H50(false, true, true, 3, 0, 50, -7, 0, 0, 0, 0.1, 0.1, 100, "MH_fliegt_vonlinks.png");		//fliegende Hühner
		Huhn H51(false, true, true, 2, 0, 250, -7, 0, 0, 0, 0.2, 0.2, 25, "MH_fliegt_vonlinks.png");		//fliegende Hühner
		Huhn H52(false, true, true, 5, 0, 500, -7, 0, 0, 0, 0.3, 0.3, 5, "MH_fliegt_vonlinks.png");		//fliegende Hühner

		Huehner.push_back(H01);
		Huehner.push_back(H02);
		Huehner.push_back(H03);
		Huehner.push_back(H04);
		Huehner.push_back(H05);
		Huehner.push_back(H06);
		Huehner.push_back(H07);
		Huehner.push_back(H08);
		Huehner.push_back(H09);
		Huehner.push_back(H10);

		Huehner.push_back(H50);
		Huehner.push_back(H51);
		Huehner.push_back(H52);

	}

	double x, y, Punktestand = 0;
	bool Klick_links, Klick_links_alt, Klick_rechts, Klick_rechts_alt, schiesen, laden;
	bool H1 = true, H2 = true, H3 = true, spiel_läuft=true;
	int Schüsse = 5, Zufallszahl_von = 1, Zufallszahl_bis = 13, Zufallszahl, Zi = 0, Zeit_sec, Zeit_msec = 10*60;
	string string_Punktestand, string_Zeit;
	vector<Huhn> Huehner;
	








	void update() override {
		//Sleep(10);
		x = input().mouse_x();
		y = input().mouse_y();
		srand(time(NULL));
		if (Zeit_msec >= 0) { spiel_läuft = true; }
		else 
		{ 
			spiel_läuft = false; 
			
		}
		
		if ((input().down(Gosu::KB_ENTER)|| input().down(Gosu::KB_N))&& !(spiel_läuft))
		{
			Punktestand = 0;
			Zeit_msec = 3 * 60;
			Schüsse = 5;
			
		}

		if (spiel_läuft)
		{
			// Klicke linke Maustaste
			

			
			{
				if (Schüsse >= 0)
				{
					Klick_links = input().down(Gosu::MS_LEFT);
					if (Klick_links && !Klick_links_alt &&  (Schüsse>=1))
					{
						Klick_links_alt = true;
						
						shot.play(1, 1, false);// hier aktion für Schuss
						Schüsse = Schüsse - 1;

						if (schiesen) // Wird nur durchlaufen wenn ein gültiger Schuss abgegeben wurde
							for (Huhn& elem : Huehner)
							{
								Punktestand = elem.getroffen(x, y) + Punktestand;
							}


					}
					else if (Klick_links && !Klick_links_alt && (Schüsse == 0))
					{
						Klick_links_alt = true;
						empty.play(1, 1, false);
					}
					else if (!Klick_links)
					{
						Klick_links_alt = false;
						schiesen = false;

					}

					else
					{
						Klick_links = false;
					}

				}
				else
				{
					schiesen = false;
				}

				

			}
			{
				if (Schüsse >= 1)
				{
					Klick_links = input().down(Gosu::MS_LEFT);
					if (Klick_links && !Klick_links_alt)
					{
						Klick_links_alt = true;

						shot.play(1, 1, false);// hier aktion für Schuss
						Schüsse = Schüsse - 1;

						if (schiesen) // Wird nur durchlaufen wenn ein gültiger Schuss abgegeben wurde
							for (Huhn& elem : Huehner)
							{
								Punktestand = elem.getroffen(x, y) + Punktestand;
							}


					}
					else if (!Klick_links)
					{
						Klick_links_alt = false;
						schiesen = false;

					}

					else
					{
						Klick_links = false;
					}

				}
				else
				{
					schiesen = false;
				}



			}

			

			// Hühner wieder auftauchen lassen
			{
				if (Zi < 50)
				{
					Zi++;

				}
				else
				{
					Zufallszahl = (rand() % ((Zufallszahl_bis + 1) - Zufallszahl_von)) + Zufallszahl_von;
					Huehner[Zufallszahl - 1].ZEbene = 7;
					Huehner[Zufallszahl - 1].Sichtbarkeit = true;

					Zi = 0;
				}
			}



			//Klicke rechte Maustaste
			{
				Klick_rechts = input().down(Gosu::KB_SPACE) || input().down(Gosu::MS_RIGHT);
				if (Klick_rechts && !Klick_rechts_alt)
				{
					Klick_rechts_alt = true;
					laden = true;
					Schüsse = 5;
					reload.play(1, 1.9, false);

				}
				else if (!Klick_rechts)
				{
					Klick_rechts_alt = false;
					laden = false;
				}

				else
				{
					Klick_rechts = false;
				}
			}

			//

		}

		
	}


	void draw() override {


		if (spiel_läuft)
		{
			Zeit_msec = Zeit_msec - 1;
			cout << Zeit_msec << endl;

			for (Huhn& elem : Huehner) {
				elem.draw();
			}

			//punkt.draw(const std::string & text, double x, double y, ZPOS z, 
			//           double scale_x = 1, double scale_y = 1, Color  c = Color::WHITE, 
			//           AlphaMode  mode= AM_DEFAULT)
			//Draws text, so the top left corner of the text is at (x,y)


			string_Punktestand = to_string(int(Punktestand));

			Punkte_Überschrift.draw("Punkte", 1542, 0, 9, 1, 1, Gosu::Color::BLACK);
			Punkte_Anzeige.draw(string_Punktestand, 1520, 24, 9, 1, 1, Gosu::Color::BLACK);

			
			string_Zeit = to_string(Zeit_msec/60);

			Zeit_Überschrift.draw("Zeit", 1350, 0, 9, 1, 1, Gosu::Color::BLACK);
			Zeit_Anzeige.draw(string_Zeit, 1350, 24, 9, 1, 1, Gosu::Color::BLACK);

			// Fadenkreuz
			{
				double ZEbene = 10;
				// X Fadenkreuz
				{ // X Fadenkreuz
					graphics().draw_line(
						(x - 25), y, Gosu::Color::BLACK,
						(x + 25), y, Gosu::Color::BLACK,
						ZEbene
					);
					graphics().draw_line(
						(x - 25), y + 1, Gosu::Color::BLACK,
						(x + 25), y + 1, Gosu::Color::BLACK,
						ZEbene
					);
					graphics().draw_line(
						(x - 25), y - 1, Gosu::Color::BLACK,
						(x + 25), y - 1, Gosu::Color::BLACK,
						ZEbene
					);
				}

				// Y Fadenkreuz
				{
					graphics().draw_line(
						x, (y - 25), Gosu::Color::BLACK,
						x, (y + 25), Gosu::Color::BLACK,
						ZEbene
					);
					graphics().draw_line(
						x + 1, (y - 25), Gosu::Color::BLACK,
						x + 1, (y + 25), Gosu::Color::BLACK,
						ZEbene
					);
					graphics().draw_line(
						x - 1, (y - 25), Gosu::Color::BLACK,
						x - 1, (y + 25), Gosu::Color::BLACK,
						ZEbene
					);
				}

			}

			// Schüsse
			{

				//alle Werte der Patronen können hier zentral geändert werden
				double Patrone_X = 1750;
				double Patrone_Y = 1050;
				double Patrone_Z = 7;
				double Winkel_Patrone = -30;
				double skalierungX = 0.35;
				double skalierungY = 0.35;

				//Schuss 1
				if (Schüsse >= 1)
				{
					Schuss.draw_rot(
						Patrone_X,
						Patrone_Y,
						Patrone_Z,
						Winkel_Patrone,
						0.5,
						0.5,
						skalierungX,
						0.35,
						Gosu::Color::WHITE
						//Gosu::AlphaMode::AM_INTERPOLATE
					);
				}
				if (Schüsse >= 2)
				{
					Schuss.draw_rot(
						Patrone_X - 75,
						Patrone_Y,
						Patrone_Z,
						Winkel_Patrone,
						0.5,
						0.5,
						skalierungX,
						0.35,
						Gosu::Color::WHITE
						//Gosu::AlphaMode::AM_INTERPOLATE
					);
				}
				if (Schüsse >= 3)
				{
					Schuss.draw_rot(
						Patrone_X - 150,
						Patrone_Y,
						Patrone_Z,
						Winkel_Patrone,
						0.5,
						0.5,
						skalierungX,
						0.35,
						Gosu::Color::WHITE
						//Gosu::AlphaMode::AM_INTERPOLATE
					);
				}
				if (Schüsse >= 4)
				{
					Schuss.draw_rot(
						Patrone_X - 225,
						Patrone_Y,
						Patrone_Z,
						Winkel_Patrone,
						0.5,
						0.5,
						skalierungX,
						0.35,
						Gosu::Color::WHITE
						//Gosu::AlphaMode::AM_INTERPOLATE
					);
				}
				if (Schüsse >= 5)
				{
					Schuss.draw_rot(
						Patrone_X - 300,
						Patrone_Y,
						Patrone_Z,
						Winkel_Patrone,
						0.5,
						0.5,
						skalierungX,
						0.35,
						Gosu::Color::WHITE
						//Gosu::AlphaMode::AM_INTERPOLATE
					);
				}

			};

			
			background.draw_rot(
				0, 0, 0.0,
				0.0,
				0.0, 0.0
			);

		}
		else
		{
			background_finished.draw_rot(0, 0, 11, 0);

			Punkte_Überschrift.draw("Endpunktestand", 500, 500, 12, 1, 1, Gosu::Color::WHITE);
			Punkte_Anzeige.draw(string_Punktestand, 800, 450, 12, 1, 1, Gosu::Color::WHITE);
			// Spiel fertig
		}


		


	};
};



int main()
{
	GameWindow window;
	window.show();

	//int32_t stop;
	//cin >> stop;



	return 0;
}

