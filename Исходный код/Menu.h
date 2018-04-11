#pragma once

#include"Libraries.h"
/*КЛАСС ПУНКТА МЕНЮ*/
class Menu
{
private:
	static int
		character_size, //Размер шрифта 
		side_off; //Сдвиг между элементами

	float 
		general_position_x, //Смещение относительно экрана по Х
		general_position_y; //Смещение относительно экрана по У

	Text caption_text; //Надпсь строки управления (Информация)
	Color color_text; //Цвет шрифта

	Texture tx_icon; //Текстура иконки главного меню
	Sprite sprite_icon; //Спрайт иконки главного меню

	RectangleShape menu_name_hud; //Подкладка под текст названия главного меню
	Text menu_name; //Текст названия главного меню

public:

	Menu()
	{
		menu_name_hud.setFillColor(Color::Black);
		menu_name_hud.setOrigin(10, 5);
		menu_name_hud.setScale(ScaleWindow(window, 1, 1));

		color_text = Color::White;
		caption_text.setFont(global_font);
		caption_text.setScale(ScaleWindow(window, 1, 1));
		caption_text.setFillColor(color_text);

		menu_name = caption_text;
		menu_name.setCharacterSize(50);
		menu_name.setScale(ScaleWindow(window, 1, 1));

		character_size = 18;

		general_position_x = ScaleWindowX(window, 20);
		general_position_y = ScaleWindowY(window, 13);

		side_off = ScaleWindowY(window, 50.0);
	}

	/*ПРОСТАЯ ЧАСТЬ МЕНЮ*/
	Text partVertivcal(wstring caption, int position, int counter, int pos = NULL)
	{
		if (pos == NULL) pos = position;

		caption_text.setString(caption); //Установка андписи
		caption_text.setPosition(general_position_x, general_position_y + side_off*(pos)); //Установка позиции на экране, в зависимости от порядкового номера

		return caption_text;
	}
	/*ЧАСТЬ МЕНЮ С ПЕРЕКЛЮЧЕНИЕМ НАДПИСИ*/
	Text partHorizontal(wstring captions_horizontal[], wstring caption = L"NO_CAPTION", int position = 0, int ver_counter = -100, int hor_counter = -100, bool first = false)
	{
		caption_text.setString(caption + ": " + captions_horizontal[hor_counter]); //Установка надписи, в зависимости от ее индекса
		caption_text.setPosition(general_position_x, general_position_y + side_off*(position + first)); //Установка позиции на экране, в зависимости от порядкового номера 

		return caption_text;
	}
	/*ПЕРЕГРЗКА ДЛЯ ЧИСЛЕННОГО ЗНАЧЕНИЯ*/
	Text partHorizontal(wstring caption, int position = 0, int ver_counter = -100, int hor_counter = -100, bool first = false)
	{
		static char buffer[3] = "\0";
		wsprintf(buffer, "%i", hor_counter);
		
		caption_text.setString(caption + ": " + buffer);
		caption_text.setPosition(general_position_x, general_position_y + side_off*(position + first));

		return caption_text;
	}
	
	/*НАЗВАНИЕ ГЛАВНОГО МЕНЮ*/
	void MenuName(wstring caption = L"NO_CAPTION")
	{
		menu_name.setString(caption);
		menu_name.setOrigin(menu_name.getLocalBounds().width / 2, menu_name.getLocalBounds().height / 2);
		menu_name.setPosition(window.getSize().x/4*3, window.getSize().y/2);

		menu_name_hud.setSize(Vector2f(menu_name.getLocalBounds().width + 20, menu_name.getLocalBounds().height + 20));
		menu_name_hud.setOrigin(menu_name_hud.getSize().x / 2, menu_name_hud.getSize().y / 2 - 7);
		menu_name_hud.setPosition(menu_name.getPosition().x, menu_name.getPosition().y);

		window.draw(menu_name_hud);
		window.draw(menu_name);
	}

	/*УКАЗАТЕЛЬ*/
	RectangleShape textHud(Color color = Color::Black)
	{
		RectangleShape gg;

		gg.setFillColor(color);
		gg.setSize(Vector2f(caption_text.getLocalBounds().width + 20, caption_text.getLocalBounds().height + 20));
		gg.setPosition(caption_text.getPosition().x, caption_text.getPosition().y);
		gg.setScale(ScaleWindow(window, 1, 1));
		gg.setOrigin(10, 5);

		return gg;
	}
	/*ИКОНКА МЕНЮ*/
	Sprite iconMenu(double time, double minus = 5)
	{
		static double rotate = 0;
		static bool back = true;

		if (back && rotate > -minus / (minus * 10)) rotate -= 0.0001 * time;
		else if (!back && rotate < minus / (minus * 10)) rotate += 0.0001 * time;

		if (sprite_icon.getRotation() < 360 - minus && sprite_icon.getRotation() > 360 - minus * 2) back = false;
		else if (sprite_icon.getRotation() < minus * 2 && sprite_icon.getRotation() > minus) back = true;

		sprite_icon.rotate(rotate);

		return sprite_icon;
	}

	/*ЗАГРУЗКА ТЕКСТУРЫ ДЛЯ ИКОНКИ МЕНЮ*/
	void loadTexture(char *dir_of_file)
	{
		tx_icon.loadFromFile(dir_of_file); //Загружаем из файла

		sprite_icon.setTexture(tx_icon); //Устанавливаем текстуру в спрайт

		sprite_icon.setPosition(window.getSize().x / 2, window.getSize().y / 2); //Ставим по середине по Х и У
		sprite_icon.setScale(ScaleWindow(window, 10, 10)); //Установка масштаба
		sprite_icon.setOrigin(tx_icon.getSize().x/2, tx_icon.getSize().y/2); //Точка ориентирования объекта (если 0, 0 - левый верхний угол)
	}
	/*УСТАНОВКА ОРИЕНТАЦИИ ПУНКТА МЕНЮ*/
	void SetPosition(Position pos)
	{
		if (pos == Position::hCenter) //Установка в центре (по горизонтали)
		{
			general_position_x = window.getSize().x / 2 - caption_text.getLocalBounds().width / 2;
			caption_text.setPosition(general_position_x, caption_text.getPosition().y);
		}
		else if (pos == Position::Right) //Установка справа
		{
			general_position_x = window.getSize().x - general_position_x - caption_text.getLocalBounds().width;
			caption_text.setPosition(general_position_x, caption_text.getPosition().y);
		}
		else if (pos == Position::Left) //Слева
		{
			general_position_x = 20;
			caption_text.setPosition(general_position_x, caption_text.getPosition().y);
		}

	}
};

int Menu::character_size, Menu::side_off; ///Инициализация статических переменных

/*ИЗМЕНЕНИЕ ЗНАЧЕНИЯ УКАЗАТЕЛЯ ПО ВЕРТИКАЛИ*/
bool VChangeCounter(int &counter, int min, int max)
{
	if (OneButtonPressed(Keyboard::Up)) --counter; //По нажатию кнопки вверх
	if (OneButtonPressed(Keyboard::Down)) ++counter; //По нажатию кнопки вниз
	//Обработка по ограничению
	if (counter > max) { counter = min; return false; } 
	else if (counter < min) { counter = max; return false; }
	else return true;
}
/*ИЗМЕНЕНИЕ ЗНАЧЕНИЯ УКАЗАТЕЛЯ ПО ГОРИЗОНТАЛИ*/
bool HChangeCounter(bool to_change, int &counter, int min, int max)
{
	window.setKeyRepeatEnabled(to_change); //Установка повторений по удержанию клавиш

	if (to_change) //Разрешение на выполнение
	{
		if (OneButtonPressed(Keyboard::Left)) --counter; //По нажатию клавиши влево
		if (OneButtonPressed(Keyboard::Right)) ++counter; //По нажатию клавиши вправо
	}
	//Обработка по ограничению
	if (counter > max) { counter = max; return false; }
	else if (counter < min) { counter = min; return false; }
	else return true;
}