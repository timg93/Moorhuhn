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
	double XPos, YPos, ZEbene, Winkel, PfAwX, PfAwY, SkalX, SkalY, Punkte, Höhe, Breite, start_wandern, Faktor_Bewegung;
	string JPG;
	Gosu::Image Bild;

	void draw()
	{
		if (this->Wandern && this->Sichtbarkeit && this->von_links_wandern) { this->XPos = this->XPos + 1 * this->Faktor_Bewegung; }
		if (this->Wandern && this->Sichtbarkeit & !this->von_links_wandern) { this->XPos = this->XPos - 1 * this->Faktor_Bewegung; }
		//else if (this->Wandern && (this->XPos >= 1920+ this->Breite))	{this->XPos = this->start_wandern;}
		if (this->XPos + this->Breite > 1920) { this->Sichtbarkeit = false; this->XPos = this->start_wandern; }
		
		if (this->Sichtbarkeit)	{this->ZEbene = 7;}
		else{this->ZEbene = -7;	}

		

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

	double getroffen(double x, double y)
		// Die Funktion später nur ausführen wenn ein gültiger Klick gemacht wurde
	{

		
		 

		if (((x >= this->XPos) && (x <= (this->XPos + Breite))) &&
			((y >= this->YPos) && (y <= (this->YPos + Höhe))) && this->Sichtbarkeit)
		{

			this->ZEbene = -7;			
			Sichtbarkeit = false;
			if (Wandern)
			{
				this->XPos = this->start_wandern;

			}


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
		
		this->Höhe = this->Bild.height()* this->SkalX;
		this->Breite = this->Bild.height()*this->SkalY;

		this->Sichtbarkeit = sichtbarkeit;
		this->Wandern = wandern;
		this->von_links_wandern = von_wandern;
		this->Faktor_Bewegung = Faktor_speed;
		this->XPos = xpos ;
		this->YPos = ypos ;
		this->ZEbene = zebene;
		this->Winkel = winkel;
		this->PfAwX = pfawx;
		this->PfAwY = pfawy;
		this->SkalX = skalx;
		this->SkalY = skaly;
		this->Punkte = punkte;
		this->JPG = jpg;

		this->Höhe = this->Bild.height()* this->SkalX;
		this->Breite = this->Bild.height()*this->SkalY;

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
	Gosu::Image Schuss;
	Gosu::Sample shot;
	Gosu::Sample reload;
	Gosu::Image ImgH1;
	Gosu::Image ImgH2;
	Gosu::Font punkte;
	Gosu::Font ueberschrift;

	

	GameWindow()
		:Window(1920, 1200)
		, background("Back.jpg"), Schuss("Schuss.png"), ImgH1("H1.jpg"), ImgH2("H1.jpg"), shot("shot.wav"), reload("reload.wav"),
		punkte(80),	ueberschrift(40)

	{
		set_caption("Gosu Tutorial Game");

		Huehner.clear();

		/*Huhn(bool sichtbarkeit, bool wandern, bool von_wandern, double Faktor_speed, double xpos, double ypos, double zebene, double winkel,
		double pfawx, double pfawy, double skalx, double skaly, double punkte, string jpg)
		: Bild(jpg)*/

		Huhn H01(false, false, true, 1, 120, 450, -7, 0, 0, 0, 0.2, 0.2, 25, "H1.jpg");		//Auf Heuballen
		Huhn H02(false, false, true, 1, 245, 620, -7, 0, 0, 0, 0.2, 0.2, 25, "H1.jpg");		//Rechts neben Heuballen
		Huhn H03(false, false, true, 1, 65, 281, -7, 0, 0, 0, 0.2, 0.2, 25, "H1.jpg");		//ganz links Scheunendach
		Huhn H04(false, false, true, 1, 765, 75, -7, 0, 0, 0, 0.2, 0.2, 25, "H1.jpg");		//Eier auf Strommasten
		Huhn H05(false, false, true, 1, 910, 155, -7, 0, 0, 0, 0.2, 0.2, 25, "H1.jpg");		//Schornstein Mitte
		Huhn H06(false, false, true, 1, 1600, 130, -7, 0, 0, 0, 0.2, 0.2, 25, "H1.jpg");		//Schornstein rechts
		Huhn H07(false, false, true, 1, 990, 410, -7, 0, 0, 0, 0.2, 0.2, 25, "H1.jpg");		//Zaun links
		Huhn H08(false, false, true, 1, 1360, 400, -7, 0, 0, 0, 0.2, 0.2, 25, "H1.jpg");		//Zaun mitte
		Huhn H09(false, false, true, 1, 1780, 450, -7, 0, 0, 0, 0.2, 0.2, 25, "H1.jpg");		//Zaun rechts

		Huhn H50(false, true, true, 1, 500, 500, -7, 0, 0, 0, 0.2, 0.2, 25, "H1.jpg");		//fliegende Hühner

		Huehner.push_back(H01);
		Huehner.push_back(H02);
		Huehner.push_back(H03);
		Huehner.push_back(H04);
		Huehner.push_back(H05);
		Huehner.push_back(H06);
		Huehner.push_back(H07);
		Huehner.push_back(H08);
		Huehner.push_back(H09);



	}

	double x, y, Punktestand = 0;
	bool Klick_links, Klick_links_alt, Klick_rechts, Klick_rechts_alt, schiesen, laden;
	bool H1 = true, H2 = true, H3 = true, H4, H5, H6, H7, H8, H9, H10;
	int Schüsse = 5, Zufallszahl_von = 1, Zufallszahl_bis = 9, Zufallszahl, Zi = 0;
	string string_Punktestand;
	vector<Huhn> Huehner;
	
	
	




	void update() override {
		Sleep(10);
		x = input().mouse_x();
		y = input().mouse_y();
		srand(time(NULL));

		// Klicke linke Maustaste
		{
			if (Schüsse >= 1)
			{
				Klick_links = input().down(Gosu::MS_LEFT);
				if (Klick_links && !Klick_links_alt)
				{
					Klick_links_alt = true;
					schiesen = true;
					shot.play(1, 1, false);// hier aktion für Schuss
					Schüsse = Schüsse - 1;

					if (schiesen) // Wird nur durchlaufen wenn ein gültiger Schuss abgegeben wurde
						
						for (Huhn& elem : Huehner)
						{							
							//cout << elem.XPos;

							Punktestand = elem.getroffen(x, y) + Punktestand/*+ Punktestand*/;
							cout << Punktestand << endl;
						}
					//cout << endl;
					//cout << Huehner[0].ZEbene << endl;

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

		

		if (Zi<100)
		{
			Zi++;
			//cout << "     " << i << endl;
		}
		else
		{
			Zufallszahl = (rand() % ((Zufallszahl_bis + 1) - Zufallszahl_von)) + Zufallszahl_von;
			Huehner[Zufallszahl-1].ZEbene = 7;
			Huehner[Zufallszahl-1].Sichtbarkeit = true;
			//cout << Zufallszahl << endl;
			Zi = 0;
		}

		/*
		#include <stdio.h>
		#include <stdlib.h>
		#include <time.h>

		int
		main ()
		{
		const int x = 4, y = 10;
		int random;

		srand (time (NULL));

		/* erzeugt Zufallszahlen zwischen 4 und 10 inklusive
		random = (rand() % ((y + 1) - x)) + x;
		printf("%d\n", random);

		return 0;
		}
		*/








		/*if (schiesen) // Wird nur durchlaufen wenn ein gültiger Schuss abgegeben wurde
			for (Huhn elem : Huehner)
			{
				Punktestand = elem.getroffen(x, y) + Punktestand;
			}*/

		//cout << Punktestand << endl;


		//Klicke rechte Maustaste
		{
			Klick_rechts = input().down(Gosu::MS_RIGHT);
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
	void draw() override {



		for (Huhn& elem : Huehner) {
			elem.draw();
		}	
		//punkt.draw(const std::string & text, double x, double y, ZPOS z, 
		//           double scale_x = 1, double scale_y = 1, Color  c = Color::WHITE, 
		//           AlphaMode  mode= AM_DEFAULT)
		//Draws text, so the top left corner of the text is at (x,y)

		string_Punktestand = Punktestand;
		ueberschrift.draw("Punkte", 1542, 0, 9, 1, 1, Gosu::Color::BLACK);
		punkte.draw(string_Punktestand, 1520, 24, 9, 1, 1, Gosu::Color::BLACK);

		// zeile einfach löschen


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

