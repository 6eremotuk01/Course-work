#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include <Windows.h>
#include <iostream>
#include <fstream>

using namespace std;
using namespace sf;

double time_second; //Переменная, которое хранит себе значение для одной секунды

//RenderWindow window(VideoMode(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), L"Курсовой проект", Style::Fullscreen);
RenderWindow window(VideoMode(1000, 600), L"Тестирование курсового проекта", Style::Close);

double global_time; //Переменная времени в микросекундах
Clock global_clock; //Объект измеряющий время за один такт

Texture last_draw; //Буфер окна
Sprite layer_sp; //Спрйт для буффера окна

Event event; //Класс србытия
Font global_font; //Класс, который хранит в себе универсальный шрифт
Music main_theme; //Класс, отвечающий за вопроизведение музыки

/*ФУНКЦИЯ ИЗМЕНЕНИЯ ГРОМКОСТИ ЗВУКА*/
void MusicUpdateVolume(Music &music, int &volume)
{
	if (volume > 0)
	{
		music.setVolume(volume); //Установка громкости звука
		/*Проверка на игру музыки. Если она не играет, то мы ее запускаем.
		Это сделано для того, чтобы избежать воспроизведения сначала, если музыка играет*/
		if (!(music.getStatus() == Music::Playing))  
			music.play(); //Запуск музыки
	}
	else music.stop();//Остановка музыки (полная остановка)
}

/*ФУНКЦИЯ ПРОВЕРКИ ФАЙЛА НА ПУСТОТУ*/
bool IsEmpty(string dir_file)
{
	ifstream file(dir_file);
	if (!file) return true;
	else return false;
}
/*КЛАСС ХРАНЕНИЯ ПОЛЬЗОВАТЕЛЬСКИХ ДАННЫХ (НАСТРОЕК)*/
class PlayerData
{
private:
	/*ФУНКЦИЯ КОДИРОВАНИЯ ПРОБЕЛА, ДЛЯ ЕГО СОХРАНЕНИЯ В ФАЙЛЕ*/
	string code(string line)
	{
		string buffer = line;

		for (int i = 0; i < buffer.length(); i++)
			if (buffer[i] == ' ') buffer[i] = '_';
			else if (buffer[i] == '_') buffer[i] = '*';
			
		return buffer;
	}
	/*ФУНКЦИЯ ДЕКОДИРОВАНИЯ ПРОБЕЛА, ДЛЯ ЕГО СОХРАНЕНИЯ В ФАЙЛЕ*/
	string decode(string line)
	{
		string buffer = line;

		for (int i = 0; i < buffer.length(); i++)
			if (buffer[i] == '_') buffer[i] = ' ';
			else if (buffer[i] == '*') buffer[i] = '_';


		return buffer;
	}

public:
	int settings[3] = { 1, 100, 75 }; //Массив настроек
	/*ЗАПИСЬ ДАННЫХ В ФАЙЛ*/
	void writeFile()
	{
		ofstream file_date("Settings.dat"); //Указываем имя файла для записи и открываем его для записи
		file_date.clear(); //Очистка перед записью

		for (int i = 0; i < 3; i++) //Запись массива поочередно
			file_date << settings[i] << endl;

		file_date.close(); //Закрытие файла после записи
	}
	/*ЧТЕНИЕ ДАННЫХ ИЗ ФАЛА*/
	int readFile()
	{
		ifstream file_date("Settings.dat");//Устанавливаем имя файла и открываем его для чтения

		if (!file_date)//Проверяем его на пустоту
		{
			for (int i = 0; i < 3; i++) //Считываем поочередно
				file_date >> settings[i];

			file_date.close(); //Закрываем файл после чтения
		}
		else
		{
			file_date.close(); //Закрываем файл
			writeFile(); //Записываем данные, которые есть.
		}
		return 0;
	}

}player; //Создаем глобальный объект "ИГРОК"


int PauseMenu(bool trans = true, bool up = true); ///Ссылка на функцию

/*ФУНКЦИЯ РАСЧЁТА МАСШТАБА, ЗАВИСИЩЕГО ОТ РАЗМЕРА ЭКРАНА*/
Vector2f ScaleWindow(RenderWindow &window, float scale_x, float scale_y) 
{
	Vector2f v = Vector2f(float(window.getSize().x) / 1366.0 * scale_x, float(window.getSize().y) / 768.0 * scale_y); 
	return v;
}
/*ФУНКЦИЯ РАСЧЁТА МАСШТАБА ПО У, ЗАВИСИЩЕГО ОТ РАЗМЕРА ЭКРАНА*/
double ScaleWindowY(RenderWindow &window, float scale_Y)
{
	return float(window.getSize().y) / 768.0 * scale_Y;
}
/*ФУНКЦИЯ РАСЧЁТА МАСШТАБА ПО Х, ЗАВИСИЩЕГО ОТ РАЗМЕРА ЭКРАНА*/
double ScaleWindowX(RenderWindow &window, float scale_X)
{
	return float(window.getSize().x) / 1366.0 * scale_X;
}

/*ФУНКЦИЯ СОХРАНЕНИЯ В БУФЕР*/
void SaveLast()
{
	last_draw.create(window.getSize().x, window.getSize().y); //Очистка буфера
	last_draw.update(window); //Запись содержимого экрана
	layer_sp.setTexture(last_draw); //Установка текстуры буфера в спрайт
}
/*ФУНКЦИЯ ПРОРИСКОВКИ БУФЕРА*/
void DrawLast(RenderWindow &window, Sprite sp)
{
	window.draw(sp); //Прорисовка буфера
}

/*ФУНКЦИЯ РАСЧЕТА ВРЕМЕНИ (ЦИКЛИЧЕСКАЯ)*/
void WindowAdds()
{
		time_second = global_clock.getElapsedTime().asSeconds(); //Берем время в секундах

		global_time = global_clock.getElapsedTime().asMicroseconds(); //Берем время в микросекундах
		global_time /= 800; //Ускоряем в 800 раз (т.к. слишком малое)

		global_clock.restart();	//Перезапускаем таймер
}
/*ОБРАБОТЧИК СОБЫТИЯ "ЗАКРИТИЕ ОКНА"*/
void EventWindowClose()
{
	if (event.type == Event::Closed)
		exit(0);
}
/*ОБРАБОТЧИК НАЖАТИЯ КЛАВИШИ С ОПРЕДЕЛЕННЫМ КОДОМ*/
bool OneButtonPressed(Keyboard::Key button)
{
	if (event.type == Event::KeyPressed && event.key.code == button) return true;
	
	return false;
}
/*ПЕРЕГРУЗКА ДЛЯ ВВОДА КОДА В РУЧНУЮ*/
bool OneButtonPressed(int button)
{
	if (event.type == Event::KeyPressed && event.key.code == button) return true;

	return false;
}

/*ПСЕВДОПРОСТРАНСТВО ИМЕН ПОЗИЦИЙ*/
enum Position
{
	Left = 1,
	hCenter = 2,
	Right = 3,

	Top = 10,
	vCenter = 20,
	Bottom = 30
};