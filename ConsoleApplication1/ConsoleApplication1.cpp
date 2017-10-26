// ConsoleApplication1.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
// geändert, damit die Verzeichnisse stimmten

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
using namespace std;

class Huhn
{
public:
	bool Sichtbarkeit, Wandern;
	double XPos, YPos, ZEbene, Winkel, PfAwX, PfAwY, SkalX, SkalY,Punkte;
	Gosu::Image Bild;

	void draw()
	{

		{

			if (this->Sichtbarkeit) { this->ZEbene = 7.0; }
			else { this->ZEbene = -7.0; }
			this->
				Bild.draw_rot(
				100,				//X-Position
				450,				//Y-Position
				ZEbene,				//Z-Ebene
				0,					//Winkel
				0.5,				// Punkt für Angriffswinkel X
				0.5,				// Punkt für Angriffswinkel X
				0.5,				// Skalierung X
				0.5,				// Skalierung Y
				Gosu::Color::WHITE
				//Gosu::AlphaMode::AM_INTERPOLATE
			);
		}

	}
	double getroffen() {}
	Huhn(bool sichtbarkeit,bool wandern , double xpos, double ypos, double zebene, double winkel, 
		double pfawx, double pfawy, double skalx, double skaly,double punkte, Gosu::Image bild)
		:Gosu::Image Bild (bild)

	{
		this->Sichtbarkeit = sichtbarkeit;
		this->Wandern = wandern;
		this->XPos = xpos;
		this->YPos = ypos;
		this->ZEbene = zebene;
		this->Winkel = winkel;
		this->PfAwX = pfawx;
		this->PfAwY = pfawy;
		this->SkalX = skalx;
		this->SkalY = skaly;
		this->Punkte = punkte;
		this->Bild = bild;

	}

};



	



class GameWindow : public Gosu::Window {
public:
	Gosu::Image background;
	Gosu::Image Schuss;
	Gosu::Image ImgH1;
	Gosu::Image ImgH2;

	GameWindow()
		:Window(1920, 1200)
		, background("Back.jpg"), Schuss("Schuss.png"), ImgH1("H1.jpg"), ImgH2("H1.jpg")
	{
		set_caption("Gosu Tutorial Game");
	}

	double x, y;
	bool Klick_links, Klick_links_alt, Klick_rechts, Klick_rechts_alt, schiesen, laden;
	bool H1=true, H2=true, H3=true, H4, H5, H6, H7, H8, H9, H10;
	int Schüsse = 5;
	vector<Huhn> Hühner;
	




	void update() override {
		x = input().mouse_x();
		y = input().mouse_y();

		Huhn H1(true, false, 100, 100, 10, 0, 0, 0, 1, 1, 25, "H1.jpg");
		Huhn H2(true, false, 150, 150, 10, 0, 0, 0, 1, 1, 25, "H1.jpg");
		Huhn H3(true, false, 250, 250, 10, 0, 0, 0, 1, 1, 25, "H1.jpg");

		Hühner.push_back(H1);
		Hühner.push_back(H2);
		Hühner.push_back(H3);

		

		// Klicke linke Maustaste
		{
			Klick_links = input().down(Gosu::MS_LEFT);
			if (Klick_links && !Klick_links_alt)
			{
				Klick_links_alt = true;
				schiesen = true;
				Schüsse = Schüsse - 1;

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

		//Klicke rechte Maustaste
		{
			Klick_rechts = input().down(Gosu::MS_RIGHT);
			if (Klick_rechts && !Klick_rechts_alt)
			{
				Klick_rechts_alt = true;
				laden = true;
				Schüsse = 5;

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
/*
	Ebenen, die Ebene 0 ist der Hintergrund -nach hinten + nach vorne 
			
			-0.5 
			
			0   = Hintergrund

			7	= Patronen
			10  = Fadenkreuz			
			

			void Gosu::Image::draw_rot	(	
			double 	x,						Position
			double 	y,
			ZPos 	z,
			double 	angle,
			double 	center_x = 0.5,
			double 	center_y = 0.5,
			double 	scale_x = 1,			skalieren
			double 	scale_y = 1,
			Color 	c = Color::WHITE,
			AlphaMode 	mode = AM_DEFAULT
			)	

		


*/
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
			double Winkel_Patrone =-30;
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

		//Hühner
		{
			//Hier können die Werte für alle Hühner verändert werden
			double Pos_Huhn_X = 0.0;
			double Pos_Huhn_Y = 0.0;
			double ZEbene;
			//double Winkel= 0.0;

			// Huhn 1 Heuballen oben
			{
				
				if(H1)	{	ZEbene = 7.0;		}
				else	{	ZEbene = -7.0;		}				
				ImgH1.draw_rot(
					100,				//X-Position
					450,				//Y-Position
					ZEbene,				//Z-Ebene
					0,					//Winkel
					0.5,				// Punkt für Angriffswinkel X
					0.5,				// Punkt für Angriffswinkel X
					0.5,				// Skalierung X
					0.5,				// Skalierung Y
					Gosu::Color::WHITE
					//Gosu::AlphaMode::AM_INTERPOLATE
								);
			}
			// Huhn 2 Heuballen rechts
			{

				if (H2) { ZEbene = 7.0; }
				else { ZEbene = -7.0; }
				ImgH2.draw_rot(
					240,				//X-Position
					610,				//Y-Position
					ZEbene,				//Z-Ebene
					0,					//Winkel
					0.5,				// Punkt für Angriffswinkel X
					0.5,				// Punkt für Angriffswinkel X
					0.5,				// Skalierung X
					0.5,				// Skalierung Y
					Gosu::Color::WHITE
					//Gosu::AlphaMode::AM_INTERPOLATE
							);
			}
			// Huhn 3 Scheune ganz links
			{

				if (H2) { ZEbene = 7.0; }
				else { ZEbene = -7.0; }
				ImgH2.draw_rot(
					50,				//X-Position
					280,				//Y-Position
					ZEbene,				//Z-Ebene
					0,					//Winkel
					0.5,				// Punkt für Angriffswinkel X
					0.5,				// Punkt für Angriffswinkel X
					0.5,				// Skalierung X
					0.5,				// Skalierung Y
					Gosu::Color::WHITE
					//Gosu::AlphaMode::AM_INTERPOLATE
				);
			}
			




			// hier die anderen Hühner noch einfügen
		}


		

		//void Gosu::Image::draw(double  	x,
		//	double  	y,
		//	ZPos  	z,
		//	double  	scale_x = 1,
		//	double  	scale_y = 1,
		//	Color  	c = Color::WHITE,
		//	AlphaMode  	mode = AM_DEFAULT
		//);		const

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

