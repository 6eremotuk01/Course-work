#include "Character.h"
#include "Libraries.h"
#include "Drawing.h"
#include "Menu.h"

///*ССЫЛКИ
void Settings(wstring caption_cursor = L"> ");

void SettingsP(wstring caption_cursor = L"> ");

void MainMenu();

/*ДИАЛОГ*/
void DialogSay(Character &per, wstring line = L"NOTHING_TO_SAY")
{
	per.setText(line);

	Draw drawing;

	while (window.isOpen())
	{
		WindowAdds();

		window.clear(Color::Black);
		RainbowBackground(window, time_second, 60);
		window.draw(per.getCharacter(global_time));
		window.draw(per.getHud());
		window.draw(per.getText(global_time));
		if (per.step == 1)
		{
			window.draw(drawing.textHud());
			window.draw(drawing.getDescription(L"Нажмите ENTER для продолжения"));
		}
		window.display();

		while (window.pollEvent(event))
		{
			EventWindowClose();

			if (OneButtonPressed(Keyboard::Escape)) PauseMenu();

			if (per.step < 3 && OneButtonPressed(Keyboard::Return)) ++per.step;

		}

		if (per.step == 2) break;
	}

}
/*ДИАЛОГ С АНИМАЦИЕЙ ВХОДА*/
void DialogSayIn(Character &per, wstring line = L"NOTHING_TO_SAY")
{
	Draw draw;

	per.setText(line);

	WindowAdds();

	while (window.isOpen())
	{
		WindowAdds();

		while (window.pollEvent(event))
		{
			EventWindowClose();

			if (OneButtonPressed(Keyboard::Escape)) PauseMenu();

			if (per.step < 3 && OneButtonPressed(Keyboard::Return)) ++per.step;

		}

		window.clear(Color::Black);

		RainbowBackground(window, time_second, 60);
		window.draw(per.getCharacter(global_time));
		window.draw(per.getHud());
		window.draw(per.getText(global_time));

		if (per.step == 1)
		{
			window.draw(draw.textHud());
			window.draw(draw.getDescription(L"Нажмите ENTER для продолжения"));
		}

		draw.fades(false, 0.1);
		
		

		window.display();

		if (per.step == 2) break;
	}

	draw.~Draw();
}
/*ДИАЛОГ С АНИМАЦИЕЙ ВЫХОДА*/
void DialogSayOut(Character &per, wstring line = L"NOTHING_TO_SAY")
{
	bool end = false;

	Draw draw;

	per.setText(line);

	WindowAdds();
	
	while (window.isOpen())
	{
		WindowAdds();

		while (window.pollEvent(event))
		{
			EventWindowClose();

			if (OneButtonPressed(Keyboard::Escape)) PauseMenu();

			if (per.step < 3 && OneButtonPressed(Keyboard::Return)) ++per.step;

		}

		window.clear(Color::Black);

		//MainBackground(global_time);
		RainbowBackground(window, time_second, 60);
		window.draw(per.getCharacter(global_time));
		window.draw(per.getHud());
		window.draw(per.getText(global_time));

		if (per.step == 1)
		{
			window.draw(draw.textHud());
			window.draw(draw.getDescription(L"Нажмите ENTER для продолжения"));
		}

		if (end)
		{
			window.draw(draw.fadeOut(global_time, 0.1));
			if (draw.intensivity > 254) break;
		}

		
		window.display();

		if (per.step == 2) end = true;
	}
}
/*ДИАЛОГ С ВОПРОСОМ ДЛЯ ПОЛЬЗОВАТЕЛЯ*/
bool DialogQuestion(Character &per, wstring question, wstring answer1, wstring answer2)
{
	bool end = false;

	Draw draw;

	per.setText(question + "\n\n1. " + answer1 + "\n2. " + answer2);
	per.talking = false;
	per.step = 1;

	WindowAdds();

	while (window.isOpen())
	{
		WindowAdds();

		while (window.pollEvent(event))
		{
			EventWindowClose();

			if (OneButtonPressed(Keyboard::Escape)) PauseMenu();

			if (OneButtonPressed(Keyboard::Return)) { per.step = 1; }

			if (OneButtonPressed(Keyboard::Num1)) 
			{ 
				++per.step; 
				if (per.step == 2) return true;
			}

			if (OneButtonPressed(Keyboard::Num2))
			{
				++per.step;
				if (per.step == 2) return false;
			}
		}

		window.clear(Color::Black);

		//MainBackground(global_time);
		RainbowBackground(window, time_second, 60);
		window.draw(per.getCharacter(global_time));
		window.draw(per.getHud());
		window.draw(per.getText(global_time));

		if (per.step == 1)
		{
			window.draw(draw.textHud());
			window.draw(draw.getDescription(L"Выберите вариант ответа (1 / 2)"));
		}

		
		window.display();

		if (per.step == 2) break;
	}
}

/*ТЕСТ ДИАЛОГА*/
int T()
{
	int pp = 0;

	Character Sokol34, Ivan, Police, Phone;

	Phone.width = Phone.x = 35;
	Phone.height = Phone.y = 66;
	Phone.LoadTexture("Images\\Characters\\Phone.png");
	Phone.setPosition(Left);

	Sokol34.width = Sokol34.x = 54;
	Sokol34.height = Sokol34.y = 67;
	Sokol34.LoadTexture("Images\\Characters\\Sokol34.png");
	Sokol34.setPosition(Left);

	Ivan.width = Ivan.x = 61;
	Ivan.height = Ivan.y = 76;
	Ivan.LoadTexture("Images\\Characters\\IvanGordov.png");
	Ivan.setPosition(Right);

	Police.width = Police.x = 57;
	Police.height = Police.y = 79;
	Police.LoadTexture("Images\\Characters\\Police.png");
	Police.setPosition(Left);

	DialogSayIn(Ivan, L"Здравствуйте, чем я могу помочь?");
	DialogSay(Sokol34, L"Здравствуйте...");
	DialogSay(Ivan, L"Что с вашим компьютером?");
	DialogSay(Sokol34, L"Не работает...");
	while (DialogQuestion(Ivan, L"Что сделать с загадочным мужчиной?", L"Выгнать его из ремонтного центра", L"Принять его копьютер на починку"))
	{
		pp++;
		switch (pp)
		{
		case 2:
			DialogSay(Ivan, L"Вы меня не слышали? \nПожалуйста, уйдите.");
			DialogSay(Sokol34, L"...");
			DialogSay(Ivan, L"...");
			break;

		case 3:
			DialogSay(Ivan, L"НЕМЕДЛЕННО ПОКИНТЕ ПОМЕЩ...");
			DialogSay(Sokol34, L"Ты знаешь зачем я пришел.");
			DialogSay(Ivan, L"...Простите?");
			DialogSay(Sokol34, L"Если ты хочешь, то я уйду. \nНо ты еще пожалеешь об этом, Ваня...");
			break;

		case 4:
			DialogSay(Sokol34, L"Ну что ж... \nТы сделал свой выбор...");
			DialogSayOut(Ivan, L"...");
			return -1;

		default:
			DialogSay(Ivan, L"Простите, но у нас сейчас обед. \nЯ попрошу вас уйти.");
			DialogSay(Sokol34, L"...");
			break;
		}
	}
	DialogSay(Ivan, L"Дайте, я его посмотрю.");
	DialogSay(Ivan, L"Так. \nНy, тут ничего сложного. \n2 часа и он как новый.");
	DialogSayOut(Sokol34, L"Работайте. \nЯ скоро вернусь...");
	return 0;
}

/*МЕНЮ С ВОПРОСОМ*/
bool Question(wstring question_ = L"NO_QUESTION", bool trans = true)
{
	int counter = 2;
	bool end = false;

	RectangleShape rr;
	rr.setSize(Vector2f(window.getSize().x, window.getSize().y));
	rr.setFillColor(Color(0, 0, 0, 150));

	Menu menu[3];
	Draw draw;
	
	menu[0].loadTexture("Images\\Menu icons\\Question.png");

	WindowAdds();

	while (window.isOpen())
	{
		WindowAdds();

		window.clear(Color::Black);

		if (!trans) MainBackground(global_time);
		else DrawLast(window, layer_sp);

		if (trans) window.draw(rr);
		window.draw(menu[0].iconMenu(global_time));
		window.draw(menu[0].textHud());
		window.draw(menu[0].partVertivcal(question_, 0, -1));
		window.draw(menu[counter].textHud());
		window.draw(menu[1].partVertivcal(L"Да", 1, counter, 2));
		window.draw(menu[2].partVertivcal(L"Нет", 2, counter, 3));

		window.draw(draw.textHud());
		window.draw(draw.getDescription(L"ВВЕРХ/ВНИЗ - указатель \tENTER - выбрать"));

		if (draw.fades(end, 0.5)) break;

		window.display();

		while (window.pollEvent(event))
		{
			EventWindowClose();

			if (!end)
			{
				if (OneButtonPressed(Keyboard::Return)) end = true;
				
				VChangeCounter(counter, 1, 2);
			}
		}

	}

	switch (counter)
	{
	case 1: 
		return true;
		break;

	case 2: 
		return false;
		break;

	default: 
		return false;
		break;
	}
}
/*ГЛАВНОЕ МЕНЮ*/
void MainMenu()
{
	int counter = 0;
	bool end = false;

	Menu menu[3];
	Draw draw;

	WindowAdds();

	window.draw(menu[0].partVertivcal(L"Диалог", 0, counter));
	window.draw(menu[1].partVertivcal(L"Настройки", 1, counter));
	window.draw(menu[2].partVertivcal(L"Выход", 2, counter));

	counter = 0;

	while (window.isOpen())
	{
		WindowAdds();

		window.clear(Color::Black);

		MainBackground(global_time);
		
		menu[0].MenuName(L"Главное меню");
		window.draw(menu[counter].textHud());
		window.draw(menu[0].partVertivcal(L"Диалог", 0, counter));
		window.draw(menu[1].partVertivcal(L"Настройки", 1, counter));
		window.draw(menu[2].partVertivcal(L"Выход", 2, counter, 3));

		window.draw(draw.textHud());
		window.draw(draw.getDescription(L"ВВЕРХ/ВНИЗ - указатель \tENTER - выбрать"));

		if (draw.fades(end, 0.5)) break;

		window.display();

		while (window.pollEvent(event))
		{
			EventWindowClose();

			if (!end)
			{
				if (OneButtonPressed(Keyboard::Return)) end = true;
				
				VChangeCounter(counter, 0, 2);
			}
		}
	}


	switch (counter)
	{
	case 0:
		T();
		MainMenu();
		break;

	case 1:
		Settings();
		MainMenu();
		break;

	case 2:
		if (Question(L"Вы действительно хотите выйти?", false))
		{
			window.close();
			main_theme.stop();
			exit(0);
		}
		MainMenu();
		break;

	default: 
		MainMenu();
		break;
	}
}
/*МЕНЮ ПАУЗЫ*/
int PauseMenu(bool trans, bool up)
{
	if (up) SaveLast();

	int counter = 0;
	bool end = false;

	RectangleShape rr;
	rr.setSize(Vector2f(window.getSize().x, window.getSize().y));
	rr.setFillColor(Color(0, 0, 0, 150));

	Menu menu[3];
	Draw draw;

	menu[0].loadTexture("Images\\Menu icons\\Pause.png");

	WindowAdds();

	while (window.isOpen())
	{
		WindowAdds();

		window.clear(Color::Black);
		DrawLast(window, layer_sp);
		window.draw(rr);
		window.draw(menu[0].iconMenu(global_time));
		window.draw(menu[counter].textHud());
		menu[0].MenuName(L"Пауза");
		window.draw(menu[0].partVertivcal(L"Продолжить", 0, counter));
		window.draw(menu[1].partVertivcal(L"Настройки", 1, counter));
		window.draw(menu[2].partVertivcal(L"Выйти в главное меню", 2, counter, 3));
		window.draw(draw.textHud());
		window.draw(draw.getDescription(L"ВВЕРХ/ВНИЗ - указатель \tENTER - выбрать"));
		if (end) break;
		window.display();

		while (window.pollEvent(event))
		{
			EventWindowClose();

			if (!end)
			{
				VChangeCounter(counter, 0, 2);
				if (OneButtonPressed(Keyboard::Return)) end = true;
				if (OneButtonPressed(Keyboard::Escape)) end = true;
			}
		}
	}

	switch (counter)
	{
	case 0:
		break;

	case 1:
		SettingsP();
		PauseMenu(true, false);
		break;

	case 2:
		if (Question(L"Вы действительно хотите выйти в главное меню?", trans)) MainMenu();
		else PauseMenu(true, false);
		break;

	default:
		break;
	}
	return 0;
}
/*МЕНЮ НАСТРОЕК*/
void Settings(wstring caption_cursor)
{
	int counter = 1;
	bool end = false;

	Menu menu[2];
	menu[0].loadTexture("Images\\Menu icons\\Settings.png");
	
	Draw draw;
	WindowAdds();
	player.readFile();
	
	while (window.isOpen())
	{
		WindowAdds();

		window.clear();
		MainBackground(global_time);
		window.draw(menu[0].iconMenu(global_time));
		window.draw(menu[counter].textHud());
		menu[0].MenuName(L"Настройки");
		window.draw(menu[0].partHorizontal(L"Музыка", 0, counter, player.settings[2]));
		window.draw(menu[1].partVertivcal(L"Назад", 1, counter, 2));

		window.draw(draw.textHud());
		window.draw(draw.getDescription(L"ВВЕРХ/ВНИЗ - указатель \tENTER - выбрать \tВЛЕВО/ВПРАВО - изменить"));
		if (draw.fades(end, 0.5)) break;
		window.display();


		while (window.pollEvent(event))
		{
			EventWindowClose();

			if (HChangeCounter(counter == 0, player.settings[2], 0, 100))
				MusicUpdateVolume(main_theme, player.settings[2]);

			VChangeCounter(counter, 0, 1);

			if (OneButtonPressed(Keyboard::Return) && counter == 1) end = true;
		}
	}
	player.writeFile();
}
/*МЕНЮ НАСТРОЕК ДЛЯ ПАУЗЫ*/
void SettingsP(wstring caption_cursor)
{
	int counter = 1;
	bool end = false;

	Menu menu[2];
	menu[0].loadTexture("Images\\Menu icons\\Settings.png");

	RectangleShape rr;
	rr.setSize(Vector2f(window.getSize().x, window.getSize().y));
	rr.setFillColor(Color(0, 0, 0, 150));

	Draw draw;
	WindowAdds();
	player.readFile();

	while (window.isOpen())
	{
		WindowAdds();

		window.clear();

		DrawLast(window, layer_sp);
		window.draw(rr);
		window.draw(menu[0].iconMenu(global_time));
		window.draw(menu[counter].textHud());
		menu[0].MenuName(L"Настройки");
		window.draw(menu[0].partHorizontal(L"Музыка", 0, counter, player.settings[2]));
		window.draw(menu[1].partVertivcal(L"Назад", 1, counter, 2));

		window.draw(draw.textHud());
		window.draw(draw.getDescription(L"ВВЕРХ/ВНИЗ - указатель \tENTER - выбрать \tВЛЕВО/ВПРАВО - изменить"));
		if (draw.fades(end, 0.5)) break;
		window.display();


		while (window.pollEvent(event))
		{
			EventWindowClose();

			if (HChangeCounter(counter == 1, player.settings[2], 0, 100))
				MusicUpdateVolume(main_theme, player.settings[2]);

			VChangeCounter(counter, 0, 1);

			if (OneButtonPressed(Keyboard::Return) && counter == 1) end = true;
		}
	}
	player.writeFile();
}

/*ВХОД ПРОГРАММЫ*/
int main()
{
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

	main_theme.openFromFile("Music\\Main_theme.wav");
	main_theme.setLoop(true);

	if (!IsEmpty("PlayerData.dat")) player.readFile();
	MusicUpdateVolume(main_theme, player.settings[2]);

	Font console_font;
	console_font.loadFromFile("Images\\Fonts\\Pixel.ttf");
	global_font.loadFromFile("Images\\Fonts\\VHS.ttf");

	window.clear(Color::Black);
	window.display();

	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);

	MainMenu();
}