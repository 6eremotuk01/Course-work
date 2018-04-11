#pragma once

#include "Libraries.h"
/*КЛАСС РИСОВАНИЯ ОБЩЕГО НАЗНАЧЕНИЯ*/
class Draw
{
private:
	Text text; //Текст для подсказок
	RectangleShape gg; //Подкладка под текст подсказки

public:
	double intensivity; //Прозрачность для перехода
	bool fade_in; //переключатель между анимацией входа и выхода

	Draw()
	{
		intensivity = 0;
		fade_in = true;
	}
	/*ПОДСКАЗКА*/
	Text getDescription(wstring description)
	{
		text.setFont(global_font);
		text.setCharacterSize(18);
		text.setString(description);

		text.setPosition(window.getSize().x / 2, window.getSize().y - 15 - 35);
		text.setOrigin(gg.getSize().x/2, 0);

		text.setOutlineColor(Color::Black);
		text.setScale(ScaleWindow(window, 1, 1));

		return text;
	}
	/*ПОДКЛАДКА ПОД ПОДСКАЗКУ*/
	RectangleShape textHud(Color color = Color::Black)
	{
		gg.setFillColor(color);
		gg.setSize(Vector2f(text.getLocalBounds().width + 20, text.getLocalBounds().height + 25));
		gg.setPosition(text.getPosition().x, text.getPosition().y);
		gg.setOrigin(gg.getSize().x / 2 + 10, 10);
		gg.setScale(ScaleWindow(window, 1, 1));

		return gg;
	}

	/*ПЕРЕХОД ИЗ*/
	RectangleShape fadeOut(double time, double speed = 0.5)
	{
		RectangleShape rect;

		if (intensivity < 254)
		{
			intensivity += speed * time;
			if (intensivity > 255) intensivity = 255;
			rect.setFillColor(Color(0, 0, 0, intensivity));
		}
		else rect.setFillColor(Color::Black);

		rect.setSize(Vector2f(window.getSize().x, window.getSize().y));
		rect.setPosition(0, 0);

		return rect;
	}
	/*ПЕРЕХОД В*/
	RectangleShape fadeIn(double time, double speed = 0.5)
	{
		RectangleShape rect;

		if (intensivity < 254)
		{
			if (intensivity < 255) intensivity += speed * time;
			if (intensivity > 255) intensivity = 255;
			rect.setFillColor(Color(0, 0, 0, 255 - intensivity));
		}
		else rect.setFillColor(Color(0, 0, 0, 0));

		rect.setSize(Vector2f(window.getSize().x, window.getSize().y));
		rect.setPosition(0, 0);

		return rect;
	}

	/*ОБЪЕДЕНЕННЫЕ ПЕРЕХОДЫ С ТРИГЕРОМ В ВИДЕ ЛОГИЧЕСКОЙ ПЕРЕМЕННОЙ*/
	bool fades(bool end, double speed = 0.5)
	{
		if (end)
		{
			window.draw(fadeOut(global_time, speed));
			if (intensivity > 254) return true;
		}
		else if (fade_in)
		{
			window.draw(fadeIn(global_time, speed));
			if (intensivity > 254)
			{
				intensivity = 0;
				fade_in = false;
			}
		}
		return false;
	}

	~Draw(){ }

};
/*КЛАСС АНИМАЦИИ*/
class Animation
{
private:
	Texture txt; //Текстура для анимации
	int x = 0, y = 0, width = 0, height = 0, frames = 0; //Размеры и положения квадрата, а так же кадры
	bool mirror = false; //Отзеркаливание

public:
	double current_frame = 0; //Текущий кадр
	Sprite sprite; //Спрайт для анимации

	
	Animation(const char *dir_of_file, int x, int y, int width, int height, double scale_X = 1, double scale_Y = 1, float posX = 0, float posY = 0)
	{
		txt.loadFromFile(dir_of_file);
		
		sprite.setTexture(txt);
		sprite.setScale(ScaleWindow(window, scale_X, scale_Y));

		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;

		sprite.setPosition(posX, posY);
		
		update();
	}

	/*ОБНОЛВЛЕНИЕ АНИМАЦИИ (СМЕНА КАДРОВ)*/
	void update(double time = 0)
	{
		current_frame += time;

		if (mirror)
		{
			if (current_frame > 2*frames) current_frame = 0;
			
			if (current_frame < frames) sprite.setTextureRect(IntRect(int(current_frame)*x, y, width, height));
			else sprite.setTextureRect(IntRect(x*int(2*frames - current_frame) + x, y, -width, height));
		}
		else
		{
			if (current_frame > frames) current_frame = 0;
			sprite.setTextureRect(IntRect(int(current_frame)*x, y, width, height));
		}
	}
	/*УСТАНОВИТЬ ОПРЕДЕЛЕННЫЙ КАДР*/
	void setFrame(double frame)
	{	
		current_frame = frame;

		if (mirror)
		{
			if (current_frame < frames) sprite.setTextureRect(IntRect(int(current_frame)*x, y, width, height));
			else sprite.setTextureRect(IntRect(x*int(2 * frames - current_frame) + x, y, -width, height));
		}
		else sprite.setTextureRect(IntRect(int(current_frame)*x, y, width, height));
	}
	/*УСТАНОВКА ОРИЕНТАЦИИ*/
	void setOrigin(Position pos = Position::Bottom)
	{
		 if(pos == Position::Bottom) sprite.setOrigin(width/2,height);
	}
	
	int setMirror(bool mirror) { this->mirror = mirror; return 0; }

	int setFrames(int frames) { this->frames = frames; return 0; }

	int getWidth() { return width; }

	int getHeight() { return height; }

	float getScaleX() { return sprite.getScale().x; }
	
	float getScaleY() { return sprite.getScale().y; }
};
/*РИСОВАНИЕ КРАСНО-ЧЕРНОГО ГРАДИЕНТА*/
void SGradientRB()
{
	Vertex rect[4] =
	{
		Vertex(Vector2f(0, 0), Color(25, 0, 0)),
		Vertex(Vector2f(window.getSize().x, 0), Color(25, 0, 0)),
		Vertex(Vector2f(window.getSize().x, window.getSize().y), Color(196, 0, 0, 150)),
		Vertex(Vector2f(0, window.getSize().y), Color(196, 0, 0))
	};

	window.draw(rect, 4, Quads);
}
/*АНИМАЦИИ "ЛИНИИ РАДУГИ"*/
void RainbowBackground(sf::RenderWindow &window, double time, double speed)
{
	//красный 220 20 0
	//оранжевый 255 140 0
	//желтый 255 215 0
	//зеленый 50 205 50
	//голубой 0 191 255
	//синий 65 105 255
	//фиолетовый 160 32 240

	static sf::Vertex rect[4];

	static sf::Color COLOR_A, COLOR_B;

	static double
		color_a[3] = { 220, 20, 0 },
		color_b[3] = { 220, 20, 0 };

	static short stage = 0;

	switch (stage)
	{
	case 0:
		if (color_b[0] < 255) color_b[0] += speed*time;
		else color_b[0] = 255;

		if (color_b[1] < 140) color_b[1] += speed*time;
		else color_b[1] = 140;

		if (color_b[1] == 140 && color_b[0] == 255) ++stage;
		break;

	case 1:
		if (color_a[0] < 255) color_a[0] += speed*time;
		else color_a[0] = 255;

		if (color_a[1] < 140) color_a[1] += speed*time;
		else color_a[1] = 140;

		if (color_a[1] == 140 && color_a[0] == 255) ++stage;
		break;

	case 2:
		if (color_b[1] < 215) color_b[1] += speed*time;
		else color_b[1] = 215;

		if (color_b[1] == 215) ++stage;
		break;

	case 3:
		if (color_a[1] < 215) color_a[1] += speed*time;
		else color_a[1] = 215;

		if (color_a[1] == 215) ++stage;
		break;

	case 4:
		if (color_b[0] > 50) color_b[0] -= speed*time;
		else color_b[0] = 50;

		if (color_b[1] > 205) color_b[1] -= speed*time;
		else color_b[1] = 205;

		if (color_b[2] < 50) color_b[2] += speed*time;
		else color_b[2] = 50;

		if (color_b[0] == 50 && color_b[1] == 205 && color_b[2] == 50) ++stage;
		break;

	case 5:
		if (color_a[0] > 50) color_a[0] -= speed*time;
		else color_a[0] = 50;

		if (color_a[1] > 205) color_a[1] -= speed*time;
		else color_a[1] = 205;

		if (color_a[2] < 50) color_a[2] += speed*time;
		else color_a[2] = 50;

		if (color_a[0] == 50 && color_a[1] == 205 && color_a[2] == 50) ++stage;
		break;

	case 6:
		if (color_b[0] > 0) color_b[0] -= speed*time;
		else color_b[0] = 0;

		if (color_b[1] > 191) color_b[1] -= speed*time;
		else color_b[1] = 191;

		if (color_b[2] < 255) color_b[2] += speed*time;
		else color_b[2] = 255;

		if (color_b[0] == 0 && color_b[1] == 191 && color_b[2] == 255) ++stage;
		break;

	case 7:
		if (color_a[0] > 0) color_a[0] -= speed*time;
		else color_a[0] = 0;

		if (color_a[1] > 191) color_a[1] -= speed*time;
		else color_a[1] = 191;

		if (color_a[2] < 255) color_a[2] += speed*time;
		else color_a[2] = 255;

		if (color_a[0] == 0 && color_a[1] == 191 && color_a[2] == 255) ++stage;
		break;

	case 8:
		if (color_b[0] < 65) color_b[0] += speed*time;
		else color_b[0] = 65;

		if (color_b[1] > 105) color_b[1] -= speed*time;
		else color_b[1] = 105;

		if (color_b[0] == 65 && color_b[1] == 105) ++stage;
		break;

	case 9:
		if (color_a[0] < 65) color_a[0] += speed*time;
		else color_a[0] = 65;

		if (color_a[1] > 105) color_a[1] -= speed*time;
		else color_a[1] = 105;

		if (color_a[0] == 65 && color_a[1] == 105) ++stage;
		break;

	case 10:
		if (color_b[0] < 160) color_b[0] += speed*time;
		else color_b[0] = 160;

		if (color_b[1] > 32) color_b[1] -= speed*time;
		else color_b[1] = 32;

		if (color_b[2] > 240) color_b[2] -= speed*time;
		else color_b[2] = 240;

		if (color_b[0] == 160 && color_b[1] == 32 && color_b[2] == 240) ++stage;
		break;

	case 11:
		if (color_a[0] < 160) color_a[0] += speed*time;
		else color_a[0] = 160;

		if (color_a[1] > 32) color_a[1] -= speed*time;
		else color_a[1] = 32;

		if (color_a[2] > 240) color_a[2] -= speed*time;
		else color_a[2] = 240;

		if (color_a[0] == 160 && color_a[1] == 32 && color_a[2] == 240) ++stage;
		break;

	case 12:
		if (color_b[0] < 220) color_b[0] += speed*time;
		else color_b[0] = 220;

		if (color_b[1] > 20) color_b[1] -= speed*time;
		else color_b[1] = 20;

		if (color_b[2] > 0) color_b[2] -= speed*time;
		else color_b[2] = 0;

		if (color_b[0] == 220 && color_b[1] == 20 && color_b[2] == 0) ++stage;
		break;

	case 13:
		if (color_a[0] < 220) color_a[0] += speed*time;
		else color_a[0] = 220;

		if (color_a[1] > 20) color_a[1] -= speed*time;
		else color_a[1] = 20;

		if (color_a[2] > 0) color_a[2] -= speed*time;
		else color_a[2] = 0;

		if (color_a[0] == 220 && color_a[1] == 20 && color_a[2] == 0) stage = 0;
		break;
	}

	/*cout << "cl1: " << (int)color_a[0] << " " << (int)color_a[1] << " " << (int)color_a[2] <<
	", cl2: " << (int)color_b[0] << " " << (int)color_b[1] << " " << (int)color_b[2] << "                                   \r";
	*/
	COLOR_A = sf::Color(color_a[0], color_a[1], color_a[2]);
	COLOR_B = sf::Color(color_b[0], color_b[1], color_b[2]);

	rect[0] = sf::Vertex(sf::Vector2f(0, window.getSize().y), COLOR_A);
	rect[1] = sf::Vertex(sf::Vector2f(0, 0), COLOR_A);
	rect[2] = sf::Vertex(sf::Vector2f(window.getSize().x, 0), COLOR_B);
	rect[3] = sf::Vertex(sf::Vector2f(window.getSize().x, window.getSize().y), COLOR_B);

	window.draw(rect, 4, sf::Quads);

}
/*ГЛАВНЙ ФОН (ПРОЕЗД МИМО БАШЕН)*/
void MainBackground(double time, bool reset = false)
{
	const int n_of = 5;

	static Animation Panel[n_of] =
	{
		Animation("Images\\Backgrounds\\Tower.png", 94, 0, 94, 79, 4, 9, window.getSize().x / (n_of - 1) * 0, window.getSize().y + 10 * 9),
		Animation("Images\\Backgrounds\\Tower.png", 94, 0, 94, 79, 4, 5, window.getSize().x / (n_of - 1), window.getSize().y + 10 * 5),
		Animation("Images\\Backgrounds\\Tower.png", 94, 0, 94, 79, 4, 7, window.getSize().x / (n_of - 1) * 2, window.getSize().y + 10 * 7),
		Animation("Images\\Backgrounds\\Tower.png", 94, 0, 94, 79, 4, 9, window.getSize().x / (n_of - 1) * 3, window.getSize().y + 10 * 9),
		Animation("Images\\Backgrounds\\Tower.png", 94, 0, 94, 79, 4, 5, window.getSize().x / (n_of - 1) * 4, window.getSize().y + 10 * 5),
	};

	if (reset) for (int i = 0; i < n_of; i++)
		Panel[i].sprite.setPosition(window.getSize().x / (n_of - 1) * i, window.getSize().y + 10*Panel[i].getScaleY());
	
	for (int i = 0; i < n_of; i++)
	{
		Panel[i].setOrigin(Position::Bottom);
		Panel[i].setMirror(true);
		Panel[i].setFrames(5);

		if (Panel[i].sprite.getPosition().x - Panel[i].getWidth() / 2 * Panel[i].getScaleX() > window.getSize().x)
			Panel[i].sprite.setPosition(0 - Panel[i].getWidth() / 2 * Panel[i].getScaleX(), Panel[i].sprite.getPosition().y);

		Panel[i].sprite.move(ScaleWindowX(window, 60 * time_second), 0);
	
		if (Panel[i].sprite.getPosition().x <= double(window.getSize().x / 2)) Panel[i].setFrame(0);

		if (Panel[i].sprite.getPosition().x >= double(window.getSize().x / 2 - window.getSize().x / 4)) Panel[i].setFrame(1);
		if (Panel[i].sprite.getPosition().x >= double(window.getSize().x / 2 - window.getSize().x / 6)) Panel[i].setFrame(2);
		if (Panel[i].sprite.getPosition().x >= double(window.getSize().x / 2 - window.getSize().x / 8)) Panel[i].setFrame(3);

		if (Panel[i].sprite.getPosition().x >= double(window.getSize().x / 2) - Panel[i].getWidth() / 2) Panel[i].setFrame(4);
		if (Panel[i].sprite.getPosition().x >= double(window.getSize().x / 2) + Panel[i].getWidth() / 2) Panel[i].setFrame(7);

		if (Panel[i].sprite.getPosition().x >= double(window.getSize().x / 2 + window.getSize().x / 8)) Panel[i].setFrame(8);
		if (Panel[i].sprite.getPosition().x >= double(window.getSize().x / 2 + window.getSize().x / 6)) Panel[i].setFrame(9);
		if (Panel[i].sprite.getPosition().x >= double(window.getSize().x / 2 + window.getSize().x / 4)) Panel[i].setFrame(10);
	}
	
	SGradientRB(); 
	for (int i = 0; i < n_of; i++)
		window.draw(Panel[i].sprite);
}