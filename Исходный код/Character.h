#pragma once

#include "Libraries.h"
/*КЛАСС ПЕРСОНАЖА*/
class Character
{
private:
	Text text_to_say; //Текст для диалога
	RectangleShape hud; //Текстовое поле
	wstring string_to_say; ///Строка для добавки пробелов
	Texture texture; //Текстура персонажа
	Sprite sprite; //Спрайт для персонажа

	static double breathing, posy; //Переменные дыхания
	static bool up_point; //Триггер вниз/вверх

	double char_to_say = 0, current_frame = 0; //Кол-во символов и текущий кадр
	bool mirror = false; //Отзеркаливание
		
public:
	bool talking = false; //Триггер анимации разговора
	int x = 0, y = 0, width = 0, height = 0; //Размеры и позиция
	int step = 0; //Стадия разговора

	Character()
	{
		text_to_say.setFont(global_font);
		text_to_say.setCharacterSize(18);

		hud.setFillColor(Color::Black);
		hud.setOutlineColor(Color::White);
		hud.setOutlineThickness(10);
		hud.setSize(Vector2f(610, 100));
		hud.setOrigin(hud.getSize().x / 2, 0);

		text_to_say.setScale(ScaleWindow(window, 1, 1));
		hud.setScale(ScaleWindow(window, 1, 1));
		sprite.setScale(ScaleWindow(window, 6, 6));
		
		hud.setPosition(window.getSize().x / 2, window.getSize().y - hud.getSize().y*hud.getScale().y - hud.getOutlineThickness() - 75);
	}
	/*ТЕКСТ (УРЕЗАННЫЙ ИЛИ ПОЛНЫЙ, В ЗАВИСИМОСТИ ОТ СТАДИИ)*/
	Text getText(double time)
	{
		if (char_to_say < string_to_say.length()) char_to_say += 0.01*time;
		text_to_say.setString(string_to_say.substr(0, int(char_to_say)));
		if (char_to_say > string_to_say.length()) step = 1;

		return text_to_say;
	}
	/*ПЕРСОНАЖ С ОБНОВЛЕНИЕМ*/
	Sprite getCharacter(double time, bool ready = false)
	{
		current_frame += 0.005*time;
		if (current_frame > 4) current_frame = 0;
		sprite.setTextureRect(IntRect(x*int(current_frame) + mirror*x, y * !talking, width - mirror*2*width, height));

		if (up_point) breathing -= 0.001 * time;
		else if (!up_point) breathing += 0.001 *time;
		if (breathing > 1) up_point = true;
		else if (breathing < -1) up_point = false;

		sprite.setPosition(sprite.getPosition().x, posy);
		sprite.move(0, breathing);
		posy = sprite.getPosition().y;

		if (step == 1)
		{
			char_to_say = string_to_say.length();
			talking = false;
		}

		return sprite;
	}
	/*ТЕКСТОВОЕ ПОЛЕ*/
	RectangleShape getHud()
	{	
		text_to_say.setOrigin(hud.getSize().x / 2, 0);
		text_to_say.setPosition(hud.getPosition().x + 10, hud.getPosition().y + 10);

		return hud;
	}

	/*ЗАГРУЗКА ТЕКСТУРЫ*/
	void LoadTexture(string texture_)
	{
		texture.loadFromFile(texture_);
		sprite.setTexture(texture);
		
		sprite.setOrigin(Vector2f(width / 2, height / 2));
	}
	/*УСТАНОВКА ПОЗИЦИИ*/
	void setPosition(Position pos)
	{
		if (pos == Position::Right) mirror = true;
		else mirror = false;

		sprite.setPosition(window.getSize().x / 4 * pos, window.getSize().y / 2);
		
		posy = sprite.getPosition().y;
	}
	/*УСТАНОВКА ТЕКСТА C Добавлением переноса*/
	void setText(wstring line_to_say)
	{
		int symbols = 0;

		char_to_say = 0;
		if (line_to_say == "...") talking = false;
		else talking = true;

		string_to_say = line_to_say;
		for (int i = 0; i < string_to_say.length(); i++)
		{
			if (string_to_say[i] == '\t') symbols += 4;
			else if (string_to_say[i] != '\n') symbols = 0;
			else symbols = 0;

			if (symbols >= 30)
			{
				string_to_say = string_to_say.substr(0, i) + '\n' + string_to_say.substr(i, string_to_say.length());
				symbols = 0;
			}
		}

		step = 0;
	}

	~Character() { }
};

double Character::breathing = 0,
	Character::posy = 0;

bool Character::up_point = true;