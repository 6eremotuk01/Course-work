#pragma once

#include"Libraries.h"
/*����� ������ ����*/
class Menu
{
private:
	static int
		character_size, //������ ������ 
		side_off; //����� ����� ����������

	float 
		general_position_x, //�������� ������������ ������ �� �
		general_position_y; //�������� ������������ ������ �� �

	Text caption_text; //������ ������ ���������� (����������)
	Color color_text; //���� ������

	Texture tx_icon; //�������� ������ �������� ����
	Sprite sprite_icon; //������ ������ �������� ����

	RectangleShape menu_name_hud; //��������� ��� ����� �������� �������� ����
	Text menu_name; //����� �������� �������� ����

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

	/*������� ����� ����*/
	Text partVertivcal(wstring caption, int position, int counter, int pos = NULL)
	{
		if (pos == NULL) pos = position;

		caption_text.setString(caption); //��������� �������
		caption_text.setPosition(general_position_x, general_position_y + side_off*(pos)); //��������� ������� �� ������, � ����������� �� ����������� ������

		return caption_text;
	}
	/*����� ���� � ������������� �������*/
	Text partHorizontal(wstring captions_horizontal[], wstring caption = L"NO_CAPTION", int position = 0, int ver_counter = -100, int hor_counter = -100, bool first = false)
	{
		caption_text.setString(caption + ": " + captions_horizontal[hor_counter]); //��������� �������, � ����������� �� �� �������
		caption_text.setPosition(general_position_x, general_position_y + side_off*(position + first)); //��������� ������� �� ������, � ����������� �� ����������� ������ 

		return caption_text;
	}
	/*��������� ��� ���������� ��������*/
	Text partHorizontal(wstring caption, int position = 0, int ver_counter = -100, int hor_counter = -100, bool first = false)
	{
		static char buffer[3] = "\0";
		wsprintf(buffer, "%i", hor_counter);
		
		caption_text.setString(caption + ": " + buffer);
		caption_text.setPosition(general_position_x, general_position_y + side_off*(position + first));

		return caption_text;
	}
	
	/*�������� �������� ����*/
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

	/*���������*/
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
	/*������ ����*/
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

	/*�������� �������� ��� ������ ����*/
	void loadTexture(char *dir_of_file)
	{
		tx_icon.loadFromFile(dir_of_file); //��������� �� �����

		sprite_icon.setTexture(tx_icon); //������������� �������� � ������

		sprite_icon.setPosition(window.getSize().x / 2, window.getSize().y / 2); //������ �� �������� �� � � �
		sprite_icon.setScale(ScaleWindow(window, 10, 10)); //��������� ��������
		sprite_icon.setOrigin(tx_icon.getSize().x/2, tx_icon.getSize().y/2); //����� �������������� ������� (���� 0, 0 - ����� ������� ����)
	}
	/*��������� ���������� ������ ����*/
	void SetPosition(Position pos)
	{
		if (pos == Position::hCenter) //��������� � ������ (�� �����������)
		{
			general_position_x = window.getSize().x / 2 - caption_text.getLocalBounds().width / 2;
			caption_text.setPosition(general_position_x, caption_text.getPosition().y);
		}
		else if (pos == Position::Right) //��������� ������
		{
			general_position_x = window.getSize().x - general_position_x - caption_text.getLocalBounds().width;
			caption_text.setPosition(general_position_x, caption_text.getPosition().y);
		}
		else if (pos == Position::Left) //�����
		{
			general_position_x = 20;
			caption_text.setPosition(general_position_x, caption_text.getPosition().y);
		}

	}
};

int Menu::character_size, Menu::side_off; ///������������� ����������� ����������

/*��������� �������� ��������� �� ���������*/
bool VChangeCounter(int &counter, int min, int max)
{
	if (OneButtonPressed(Keyboard::Up)) --counter; //�� ������� ������ �����
	if (OneButtonPressed(Keyboard::Down)) ++counter; //�� ������� ������ ����
	//��������� �� �����������
	if (counter > max) { counter = min; return false; } 
	else if (counter < min) { counter = max; return false; }
	else return true;
}
/*��������� �������� ��������� �� �����������*/
bool HChangeCounter(bool to_change, int &counter, int min, int max)
{
	window.setKeyRepeatEnabled(to_change); //��������� ���������� �� ��������� ������

	if (to_change) //���������� �� ����������
	{
		if (OneButtonPressed(Keyboard::Left)) --counter; //�� ������� ������� �����
		if (OneButtonPressed(Keyboard::Right)) ++counter; //�� ������� ������� ������
	}
	//��������� �� �����������
	if (counter > max) { counter = max; return false; }
	else if (counter < min) { counter = min; return false; }
	else return true;
}