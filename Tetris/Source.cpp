#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace sf;

const int M  = 20;
const int N = 10;
int field[M][N] = { 0 };
int Colors[7][3] = {
	0,0,0,
	0,90,255,
	0,255,255,
	0,255,0,
	230,90,255,
	255,5,0,
	255,250,0,
};
int figures[7][4] = {
	1,3,5,7,
	2,4,5,7,
	3,5,4,6,
	3,5,4,7,
	2,3,5,7,
	3,5,7,6,
	2,3,4,5,
}; 
struct Point {
	int x, y;
}a[4], b[4];
bool check() {
	for (int i = 0; i < 4; i++) {
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
		if (field[a[i].y][a[i].x]) return 0;
	}
	return 1;
}
int main(){
	
	srand(time(0));
	RenderWindow window(VideoMode(600, 720), "Best Tetris");
	//window.clear(Color::White);

	Texture texture7;
	texture7.loadFromFile("enter.jpg");
	Sprite sprite7(texture7);
	sprite7.setPosition(240, 360);

	Texture texture77;
	texture77.loadFromFile("Background0.jpg");
	Sprite sprite77(texture77);
	sprite77.setPosition(0, 0);

	String playerInput;
	Text playerText;
	Font font;
	font.loadFromFile("times-new-roman.ttf");
	playerText.setFont(font);
	playerText.setCharacterSize(30);
	playerText.setFillColor(sf::Color::White);
	playerText.setOutlineColor(sf::Color::Black);
	playerText.setOutlineThickness(1);
	playerText.setStyle(sf::Text::Bold);
	playerText.setPosition(185, 300);

	RectangleShape rectangle(Vector2f(240.f, 40.f));
	rectangle.setPosition(180, 300); // перемещаем его в нижний ряд справа от многоугольника
	rectangle.setFillColor(Color::White); // устанавливаем цвет прямоугольника
	rectangle.setOutlineThickness(1);
	rectangle.setOutlineColor(Color::Black);
	 // отрисовка прямоугольника

	Text textn;
	textn.setFont(font);
	textn.setString("Enter nickname(max 8 characters):");
	textn.setCharacterSize(26);
	textn.setFillColor(sf::Color::White);
	textn.setOutlineColor(sf::Color::Black);
	textn.setOutlineThickness(1);
	textn.setStyle(sf::Text::Bold | sf::Text::Underlined);
	textn.setPosition(100, 250);


	Event preevent;
	int k = 0,g=0;
	while (window.isOpen() && k == 0)
	{
		std::string tmp = playerText.getString();
		while (window.pollEvent(preevent))
		{
			if (preevent.type == Event::Closed) window.close();
			if (sprite7.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				texture7.loadFromFile("enter_on.jpg");
				sprite7.setTexture(texture7);
			}
			else {
				texture7.loadFromFile("enter.jpg");
				sprite7.setTexture(texture7);
			}
			if (preevent.type == sf::Event::TextEntered && preevent.text.unicode > 31 && preevent.text.unicode < 127 && preevent.text.unicode != 32 && tmp.length() < 8)
			{
				playerInput += preevent.text.unicode;
				playerText.setString(playerInput);
			}
			if (preevent.type == Event::KeyPressed && preevent.key.code == Keyboard::BackSpace && tmp.length() > 0) {
				std::string temp = playerInput;
				playerInput = temp.substr(0, temp.length() - 1);
				playerText.setString(playerInput);
			}
			if (preevent.mouseButton.button == Mouse::Left && sprite7.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y) || (preevent.type == Event::KeyPressed && preevent.key.code == Keyboard::Enter)){
				k++;
			}
		}
		window.clear(Color::Green);
		window.draw(sprite77);
		window.draw(rectangle);
		window.draw(textn);
		window.draw(playerText);
		window.draw(sprite7);
		window.display();
	}
	Music music;
	if (!music.openFromFile("mark-cook-pump-it-up.ogg"))
		return -1;
	music.play();
	music.setVolume(10);
	music.setLoop(true);
	Clock clock;
	if (playerInput == "") playerInput = "default";
	String user = "User: " + playerInput;
	Texture texture11;
	texture11.loadFromFile("minus.jpg");
	Sprite sprite11(texture11);
	sprite11.setPosition(380, 405);
	Texture texture12;
	texture12.loadFromFile("plus.jpg");
	Sprite sprite12(texture12);
	sprite12.setPosition(520, 405);

	Texture texture111;
	texture111.loadFromFile("1.jpg");
	Sprite sprite111(texture111);
	sprite111.setPosition(380, 500);
	Texture texture112;
	texture112.loadFromFile("2.jpg");
	Sprite sprite112(texture112);
	sprite112.setPosition(450, 500);
	Texture texture113;
	texture113.loadFromFile("3.jpg");
	Sprite sprite113(texture113);
	sprite113.setPosition(520, 500);


	Texture texture;
	texture.loadFromFile("newtilefromdima.jpg");
	Sprite sprite1(texture);
	float timer = 0, delay = 0.5;
	int dx = 0, colornum = 1 + rand() % 6 , n = rand() % 7, score = 0, delay_v = 0;
	bool rotate = 0, pause = 0, begin_game = true;
	bool end_game = 0;
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		Event event;
		while (window.pollEvent(event)) {
			if (sprite11.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				texture11.loadFromFile("minus_on.jpg");
				sprite11.setTexture(texture11);
			}
			else {
				texture11.loadFromFile("minus.jpg");
				sprite11.setTexture(texture11);
			}
			if (sprite12.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				texture12.loadFromFile("plus_on.jpg");
				sprite12.setTexture(texture12);
			}
			else {
				texture12.loadFromFile("plus.jpg");
				sprite12.setTexture(texture12);
			}
			if (sprite111.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				texture111.loadFromFile("1_on.jpg");
				sprite111.setTexture(texture111);
			}
			else {
				texture111.loadFromFile("1.jpg");
				sprite111.setTexture(texture111);
			}
			if (sprite112.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				texture112.loadFromFile("2_on.jpg");
				sprite112.setTexture(texture112);
			}
			else {
				texture112.loadFromFile("2.jpg");
				sprite112.setTexture(texture112);
			}
			if (sprite113.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
				texture113.loadFromFile("3_on.jpg");
				sprite113.setTexture(texture113);
			}
			else {
				texture113.loadFromFile("3.jpg");
				sprite113.setTexture(texture113);
			}
			if (event.type == Event::Closed) window.close();
			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left && sprite12.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y) && music.getVolume() <= 100.f - 1) {
					music.setVolume(music.getVolume() + 5);
				}
				if (event.mouseButton.button == Mouse::Left && sprite11.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
					if(music.getVolume() <= 5.f) music.setVolume(0);
					else music.setVolume(music.getVolume() - 5);
				}
				if (event.mouseButton.button == Mouse::Left && sprite111.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
					delay_v = 0;
					event.type = Event::KeyPressed;
					event.key.code = Keyboard::R;
				}
				if (event.mouseButton.button == Mouse::Left && sprite112.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
					delay_v = 1;
					event.type = Event::KeyPressed;
					event.key.code = Keyboard::R;
				}
				if (event.mouseButton.button == Mouse::Left && sprite113.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
					delay_v = 2;
					event.type = Event::KeyPressed;
					event.key.code = Keyboard::R;
				}
			}

			if (event.type == Event::KeyPressed) {
				if (!pause && !end_game){
					if (event.key.code == Keyboard::Up) rotate = true;
					if (event.key.code == Keyboard::Left) dx = -1;
					if (event.key.code == Keyboard::Right) dx = 1;
					if (event.key.code == Keyboard::Down) delay = 0.05;
				}
				if (event.key.code == Keyboard::P) {
					if (!end_game) {
						pause = !pause;
						if (pause) music.pause();
						else music.play();
					}
				}
				if (event.key.code == Keyboard::R) {
					int k = M - 1;
					for (int i = M - 1; i > 0; i--)
					{
						int count = 0;
						for (int j = 0; j < N; j++)
						{
							if (field[i][j]) field[i][j] = 0;
							//field[k][j] = field[i][j];
						}
						//if (count = 0) k--;
					}
					    timer = 0;
						switch (delay_v) {
						case 0:
							delay = 0.5;
							break;
						case 1:
							delay = 0.35;
							break;
						case 2:
							delay = 0.15;
							break;
						}
						dx = 0;
						rotate = 0, pause = 0;
						colornum = 1 + rand() % 6;
						score = 0;
						n = rand() % 7;
						begin_game = true;
						end_game = false;
						music.play();
						window.clear(Color::White);
						//start_cycle = 0;
				}
			}
		}

		Texture texture;
		texture.loadFromFile("newtilefromdima.jpg");
		Sprite sprite1(texture);
		Texture texture2;
		texture2.loadFromFile("Background.jpg");
		Sprite sprite2(texture2);
		sprite2.setPosition(0, 0);
		Texture texture222;
		texture222.loadFromFile("Background2.jpg");
		Sprite sprite222(texture222);
		sprite222.setPosition(360, 0);

		
		window.clear(Color::Green);
		window.draw(sprite222);

		Text text0;
		text0.setFont(font);
		text0.setString(user);
		text0.setCharacterSize(26);
		text0.setFillColor(sf::Color::White);
		text0.setOutlineColor(sf::Color::Black);
		text0.setOutlineThickness(1);
		text0.setStyle(sf::Text::Bold);
		text0.setPosition(380, 10);
		
		Text text;
		text.setFont(font);
		text.setString("Records:");
		text.setCharacterSize(30);
		text.setFillColor(sf::Color::White);
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(1);
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		text.setPosition(425, 50);

		Text text6;
		text6.setFont(font);
		text6.setString(std::to_string(score));
		text6.setCharacterSize(26);
		text6.setFillColor(sf::Color::White);
		text6.setOutlineColor(sf::Color::Black);
		text6.setOutlineThickness(1);
		text6.setStyle(sf::Text::Bold);
		text6.setPosition(380, 270);
		if (!pause && !end_game) {
			for (int i = 0; i < 4; i++) {
				b[i] = a[i];
				a[i].x += dx;
			}
			if (!check()) {
				for (int i = 0; i < 4; i++) a[i] = b[i];
			}
			if (rotate) {
				Point p = a[1];
				for (int i = 0; i < 4; i++) {
					int x = a[i].y - p.y;
					int y = a[i].x - p.x;
					a[i].x = p.x - x;
					a[i].y = p.y + y;
				}
				if (!check()) {
					for (int i = 0; i < 4; i++) a[i] = b[i];
				}
			}
			dx = 0;
			rotate = false;
			if (timer > delay) {
				for (int i = 0; i < 4; i++) {
					b[i] = a[i];
					a[i].y += 1;
				}
				if (!check()) {
					for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colornum;
					colornum = 1 + rand() % 6;
					n = rand() % 7;
					for (int i = 0; i < 4; i++) {
						a[i].x = figures[n][i] % 2;
						a[i].y = figures[n][i] / 2;
					}
				}
				timer = 0;
			}
			int k = M - 1;
			for (int i = M - 1; i > 0; i--)
			{
				int count = 0;
				for (int j = 0; j < N; j++)
				{
					if (field[i][j]) count++;
					field[k][j] = field[i][j];
				}
				if (count < N) { 
					k--;
				}
				if (count == N) {
					switch (delay_v) {
					case 0:
						score += 100;
						break;
					case 1:
						score += 200;
						break;
					case 2:
						score += 300;
						break;
					}
					
					
					text6.setString(std::to_string(score));
					
					
				}
			}
			if (begin_game) {
				begin_game = false;
				n = rand() % 7;
				for (int i = 0; i < 4; i++) {
					a[i].x = figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}
			}
			if (!begin_game) {
				int count = 0;
				for (int j = 0; j < N; j++)
				{
					if (field[1][j]) count++;
				}
				if (count > 0) {
					music.stop();
					end_game = true;
					std::ifstream fin("records.TXT"); // открыли файл для чтения
					std::string record_array[3];
					getline(fin, record_array[0]); // считали строку из файла
					getline(fin, record_array[1]); // считали строку из файла
					getline(fin, record_array[2]); // считали строку из файла
					fin.close();

					for (int i = 0; i < 3; i++) {
						size_t digits = record_array[i].find_first_of("1234567890");
						int numbers = atoi(record_array[i].c_str() + digits);
						if (score > numbers) {
							record_array[i] = playerInput + " : " + std::to_string(score);
							break;
						}
					}
					std::ofstream fout("records.TXT");
					fout.open("records.TXT", std::ofstream::out | std::ofstream::trunc);
					fout.close();
					std::ofstream fout2("records.TXT");
					fout2 << record_array[0] << std::endl;
					fout2 << record_array[1] << std::endl;
					fout2 << record_array[2] << std::endl;;
					fout2.close();

					
				}
			}
			switch (delay_v) {
			case 0:
				delay = 0.5;
				break;
			case 1:
				delay = 0.35;
				break;
			case 2:
				delay = 0.15;
				break;
			}
			
			

			

			std::string record_array[3];

			std::ifstream fin("records.TXT"); // открыли файл для чтения

			getline(fin, record_array[0]); // считали строку из файла
			getline(fin, record_array[1]); // считали строку из файла
			getline(fin, record_array[2]); // считали строку из файла
			fin.close();

			Text text2;
			text2.setFont(font);
			text2.setString(record_array[0]);
			text2.setCharacterSize(26);
			text2.setFillColor(sf::Color::White);
			text2.setOutlineColor(sf::Color::Black);
			text2.setOutlineThickness(1);
			text2.setStyle(sf::Text::Bold);
			text2.setPosition(380, 100);

			Text text3;
			text3.setFont(font);
			text3.setString(record_array[1]);
			text3.setCharacterSize(26);
			text3.setFillColor(sf::Color::White);
			text3.setOutlineColor(sf::Color::Black);
			text3.setOutlineThickness(1);
			text3.setStyle(sf::Text::Bold);
			text3.setPosition(380, 140);

			Text text4;
			text4.setFont(font);
			text4.setString(record_array[2]);
			text4.setCharacterSize(26);
			text4.setFillColor(sf::Color::White);
			text4.setOutlineColor(sf::Color::Black);
			text4.setOutlineThickness(1);
			text4.setStyle(sf::Text::Bold);
			text4.setPosition(380, 180);

			Text text55;
			text55.setFont(font);
			text55.setString("Score:");
			text55.setCharacterSize(30);
			text55.setFillColor(sf::Color::White);
			text55.setOutlineColor(sf::Color::Black);
			text55.setOutlineThickness(1);
			text55.setStyle(sf::Text::Bold | sf::Text::Underlined);
			text55.setPosition(440, 220);

			Text text5;
			text5.setFont(font);
			text5.setString("Settings:");
			text5.setCharacterSize(30);
			text5.setFillColor(sf::Color::White);
			text5.setOutlineColor(sf::Color::Black);
			text5.setOutlineThickness(1);
			text5.setStyle(sf::Text::Bold | sf::Text::Underlined);
			text5.setPosition(425, 310);

			Text text52;
			text52.setFont(font);
			text52.setString("Music volume:");
			text52.setCharacterSize(26);
			text52.setFillColor(sf::Color::White);
			text52.setOutlineColor(sf::Color::Black);
			text52.setOutlineThickness(1);
			text52.setStyle(sf::Text::Bold);
			text52.setPosition(380, 360);

			Text text53;
			text53.setFont(font);
			text53.setString("Difficulty level:");
			text53.setCharacterSize(26);
			text53.setFillColor(sf::Color::White);
			text53.setOutlineColor(sf::Color::Black);
			text53.setOutlineThickness(1);
			text53.setStyle(sf::Text::Bold);
			text53.setPosition(380, 455);


			Text text7;
			text7.setFont(font);
			if(music.getVolume() <= 3.f) text7.setString(std::to_string((int)music.getVolume()));
			else text7.setString(std::to_string((int)music.getVolume() + 1));
			text7.setCharacterSize(26);
			text7.setFillColor(sf::Color::White);
			text7.setOutlineColor(sf::Color::Black);
			text7.setOutlineThickness(1);
			text7.setStyle(sf::Text::Bold);
			text7.setPosition(465, 405);
			

			window.draw(text0); window.draw(text); window.draw(text2); window.draw(text3); window.draw(text4); window.draw(text5); window.draw(text55); window.draw(text52); window.draw(text53); window.draw(text6); window.draw(text7);
			window.draw(sprite2); window.draw(sprite11); window.draw(sprite12); window.draw(sprite111); window.draw(sprite112); window.draw(sprite113); 

				for (int i = 0; i < M; i++) {
					for (int j = 0; j < N; j++)
					{
						if (field[i][j] == 0) continue;
						sprite1.setColor(Color(Colors[field[i][j]][0], Colors[field[i][j]][1], Colors[field[i][j]][2], 255));
						sprite1.setPosition(j * 36, i * 36);
						window.draw(sprite1);
					}
				}
			for (int i = 0; i < 4; i++)
			{
				// Разукрашиваем тетрамино
				//sprite1.setTextureRect(IntRect(colornum * 36, 0, 36, 36));
				sprite1.setColor(Color(Colors[colornum][0], Colors[colornum][1], Colors[colornum][2], 255));
				// Устанавливаем позицию каждого кусочка тетрамино
				sprite1.setPosition(a[i].x * 36, a[i].y * 36);

				// Отрисовка спрайта
				window.draw(sprite1);
			}
			
			window.display();
		}
	}
	return 0;
}