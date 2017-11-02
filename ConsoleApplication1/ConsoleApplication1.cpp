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
class GameWindow : public Gosu::Window {
public:
	Gosu::Image background;
	Gosu::Image Schuss;
	Gosu::Sample shot;
	Gosu::Sample reload;
	Gosu::Font punkte;
	Gosu::Font ueberschrift;
	

	

	GameWindow()
		:Window(1920, 1200)
		,background("Back.jpg"),
		Schuss("Schuss.png"),
		shot("shot.wav"),
		reload("reload.wav"),
		punkte(80),
		ueberschrift(40)

		{		
			set_caption("Gosu Tutorial Game");
		}

	double x,y;
	bool Klick_links, Klick_links_alt, Klick_rechts, Klick_rechts_alt, schiesen, laden;
	int Schüsse = 5;
	void update() override {
		x = input().mouse_x();
		y = input().mouse_y();
		


		// Klicke linke Maustaste
		{
			Klick_links = input().down(Gosu::MS_LEFT);
			if (Klick_links && !Klick_links_alt)
			{
				Klick_links_alt = true;				
				schiesen = true;
				Schüsse = Schüsse - 1;
				shot.play(1, 1, false);

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
				laden= true;
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

		

		//punkt.draw(const std::string & text, double x, double y, ZPOS z, 
		//           double scale_x = 1, double scale_y = 1, Color  c = Color::WHITE, 
		//           AlphaMode  mode= AM_DEFAULT)
		//Draws text, so the top left corner of the text is at (x,y)

		ueberschrift.draw("Punkte", 1542, 0, 9, 1, 1, Gosu::Color::BLACK);
		punkte.draw( "1050" , 1520, 24, 9, 1, 1, Gosu::Color::BLACK);

		// zeile einfach löschen


		// Fadenkreuz
		{
			// X Fadenkreuz
			{ // X Fadenkreuz
				graphics().draw_line(
					(x - 25), y, Gosu::Color::BLACK,
					(x + 25), y, Gosu::Color::BLACK,
					1.0
				);
				graphics().draw_line(
					(x - 25), y + 1, Gosu::Color::BLACK,
					(x + 25), y + 1, Gosu::Color::BLACK,
					1.0
				);
				graphics().draw_line(
					(x - 25), y - 1, Gosu::Color::BLACK,
					(x + 25), y - 1, Gosu::Color::BLACK,
					1.0
				);
			}

			// Y Fadenkreuz
			{
				graphics().draw_line(
					x, (y - 25), Gosu::Color::BLACK,
					x, (y + 25), Gosu::Color::BLACK,
					1.0
				);
				graphics().draw_line(
					x + 1, (y - 25), Gosu::Color::BLACK,
					x + 1, (y + 25), Gosu::Color::BLACK,
					1.0
				);
				graphics().draw_line(
					x - 1, (y - 25), Gosu::Color::BLACK,
					x - 1, (y + 25), Gosu::Color::BLACK,
					1.0
				);

				/*graphics().draw_line(

					x, (y - 20), Gosu::Color::BLACK,
					x, (y + 25), Gosu::Color::BLACK,
					1.0
				);*/

			}



			//Font(unsigned  font_height, const std:: string & font_name = default_font_name(), unsigned font_flags = FF_BOLD );
			//shot.play(1, 1, false);
			//font.punkte();


		}

		// Schüsse
		{
		//Schuss 1
		//Laage der Patronen
		int Patrone_X = 1750;
		int Patrone_Y = 1050;



		if (Schüsse >= 1)
		{
			Schuss.draw_rot(
				Patrone_X,
				Patrone_Y,
				0.5,
				-30,
				0.5,
				0.5,
				0.35,
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
				0.5,
				-30,
				0.5,
				0.5,
				0.35,
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
				0.5,
				-30,
				0.5,
				0.5,
				0.35,
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
				0.5,
				-30,
				0.5,
				0.5,
				0.35,
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
				0.5,
				-30,
				0.5,
				0.5,
				0.35,
				0.35,
				Gosu::Color::WHITE
				//Gosu::AlphaMode::AM_INTERPOLATE
			);
		}
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

