#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include <Windows.h>
#include <iostream>
#include <fstream>

using namespace std;
using namespace sf;

double time_second; //����������, ������� ������ ���� �������� ��� ����� �������

//RenderWindow window(VideoMode(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), L"�������� ������", Style::Fullscreen);
RenderWindow window(VideoMode(1000, 600), L"������������ ��������� �������", Style::Close);

double global_time; //���������� ������� � �������������
Clock global_clock; //������ ���������� ����� �� ���� ����

Texture last_draw; //����� ����
Sprite layer_sp; //����� ��� ������� ����

Event event; //����� �������
Font global_font; //�����, ������� ������ � ���� ������������� �����
Music main_theme; //�����, ���������� �� �������������� ������

/*������� ��������� ��������� �����*/
void MusicUpdateVolume(Music &music, int &volume)
{
	if (volume > 0)
	{
		music.setVolume(volume); //��������� ��������� �����
		/*�������� �� ���� ������. ���� ��� �� ������, �� �� �� ���������.
		��� ������� ��� ����, ����� �������� ��������������� �������, ���� ������ ������*/
		if (!(music.getStatus() == Music::Playing))  
			music.play(); //������ ������
	}
	else music.stop();//��������� ������ (������ ���������)
}

/*������� �������� ����� �� �������*/
bool IsEmpty(string dir_file)
{
	ifstream file(dir_file);
	if (!file) return true;
	else return false;
}
/*����� �������� ���������������� ������ (��������)*/
class PlayerData
{
private:
	/*������� ����������� �������, ��� ��� ���������� � �����*/
	string code(string line)
	{
		string buffer = line;

		for (int i = 0; i < buffer.length(); i++)
			if (buffer[i] == ' ') buffer[i] = '_';
			else if (buffer[i] == '_') buffer[i] = '*';
			
		return buffer;
	}
	/*������� ������������� �������, ��� ��� ���������� � �����*/
	string decode(string line)
	{
		string buffer = line;

		for (int i = 0; i < buffer.length(); i++)
			if (buffer[i] == '_') buffer[i] = ' ';
			else if (buffer[i] == '*') buffer[i] = '_';


		return buffer;
	}

public:
	int settings[3] = { 1, 100, 75 }; //������ ��������
	/*������ ������ � ����*/
	void writeFile()
	{
		ofstream file_date("Settings.dat"); //��������� ��� ����� ��� ������ � ��������� ��� ��� ������
		file_date.clear(); //������� ����� �������

		for (int i = 0; i < 3; i++) //������ ������� ����������
			file_date << settings[i] << endl;

		file_date.close(); //�������� ����� ����� ������
	}
	/*������ ������ �� ����*/
	int readFile()
	{
		ifstream file_date("Settings.dat");//������������� ��� ����� � ��������� ��� ��� ������

		if (!file_date)//��������� ��� �� �������
		{
			for (int i = 0; i < 3; i++) //��������� ����������
				file_date >> settings[i];

			file_date.close(); //��������� ���� ����� ������
		}
		else
		{
			file_date.close(); //��������� ����
			writeFile(); //���������� ������, ������� ����.
		}
		return 0;
	}

}player; //������� ���������� ������ "�����"


int PauseMenu(bool trans = true, bool up = true); ///������ �� �������

/*������� ���ר�� ��������, ���������� �� ������� ������*/
Vector2f ScaleWindow(RenderWindow &window, float scale_x, float scale_y) 
{
	Vector2f v = Vector2f(float(window.getSize().x) / 1366.0 * scale_x, float(window.getSize().y) / 768.0 * scale_y); 
	return v;
}
/*������� ���ר�� �������� �� �, ���������� �� ������� ������*/
double ScaleWindowY(RenderWindow &window, float scale_Y)
{
	return float(window.getSize().y) / 768.0 * scale_Y;
}
/*������� ���ר�� �������� �� �, ���������� �� ������� ������*/
double ScaleWindowX(RenderWindow &window, float scale_X)
{
	return float(window.getSize().x) / 1366.0 * scale_X;
}

/*������� ���������� � �����*/
void SaveLast()
{
	last_draw.create(window.getSize().x, window.getSize().y); //������� ������
	last_draw.update(window); //������ ����������� ������
	layer_sp.setTexture(last_draw); //��������� �������� ������ � ������
}
/*������� ����������� ������*/
void DrawLast(RenderWindow &window, Sprite sp)
{
	window.draw(sp); //���������� ������
}

/*������� ������� ������� (�����������)*/
void WindowAdds()
{
		time_second = global_clock.getElapsedTime().asSeconds(); //����� ����� � ��������

		global_time = global_clock.getElapsedTime().asMicroseconds(); //����� ����� � �������������
		global_time /= 800; //�������� � 800 ��� (�.�. ������� �����)

		global_clock.restart();	//������������� ������
}
/*���������� ������� "�������� ����"*/
void EventWindowClose()
{
	if (event.type == Event::Closed)
		exit(0);
}
/*���������� ������� ������� � ������������ �����*/
bool OneButtonPressed(Keyboard::Key button)
{
	if (event.type == Event::KeyPressed && event.key.code == button) return true;
	
	return false;
}
/*���������� ��� ����� ���� � ������*/
bool OneButtonPressed(int button)
{
	if (event.type == Event::KeyPressed && event.key.code == button) return true;

	return false;
}

/*������������������ ���� �������*/
enum Position
{
	Left = 1,
	hCenter = 2,
	Right = 3,

	Top = 10,
	vCenter = 20,
	Bottom = 30
};