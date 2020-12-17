#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
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
	Music music;
	if (!music.openFromFile("mark-cook-pump-it-up.ogg"))
		return -1;
	music.play();
	music.setVolume(10.f);
	music.setLoop(true);
	srand(time(0));
	RenderWindow window(VideoMode(1000, 1000), "Best Tetris");
	Clock clock;
	Texture texture;
	texture.loadFromFile("newtilefromdima.jpg");
	Sprite sprite1(texture);
	float timer = 0, timer2 = 0, delay = 0.5;
	int dx = 0, colornum = 1 + rand() % 6 , n = rand() % 7;
	bool rotate = 0, pause = 0, begingame = true;
	int start_cycle = 1;
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		timer2 += time;
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) { window.close(); return false; }
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Up) rotate = true;
				if (event.key.code == Keyboard::Left) dx = -1;
				if (event.key.code == Keyboard::Right) dx = 1;
				if (event.key.code == Keyboard::Down) delay = 0.05;
				if (event.key.code == Keyboard::P) {
					pause = !pause;
					if (pause) music.pause();
					else music.play();
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
						timer = 0, delay = 0.5;
						dx = 0;
						rotate = 0, pause = 0;
						colornum = 1 + rand() % 6;
						n = rand() % 7;
						begingame = true;
						window.clear(Color::White);
						//start_cycle = 0;
				}
			}
		}
		if (!pause /*&& start_cycle!=0*/) {
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
				if (count < N) k--;
			}
			if (begingame) {
				begingame = false;
				n = rand() % 7;
				for (int i = 0; i < 4; i++) {
					a[i].x = figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}
			}
			if (!begingame) {
				int count = 0;
				for (int j = 0; j < N; j++)
				{
					if (field[1][j]) count++;
				}
				if (count > 0) {
					music.stop();
					pause = true;
				}
			}
			delay = 0.5;
			Texture texture;
			texture.loadFromFile("newtilefromdima.jpg");
			Sprite sprite1(texture);
			//sprite1.setTextureRect(IntRect(0, 0, 36, 36));
			//window.clear(Color(25, 165, 250, 0));
			window.clear(Color::White);

				for (int i = 0; i < M; i++) {
					for (int j = 0; j < N; j++)
					{
						if (field[i][j] == 0) continue;
						sprite1.setColor(Color(Colors[field[i][j]][0], Colors[field[i][j]][1], Colors[field[i][j]][2], 100));
						sprite1.setPosition(j * 36, i * 36);
						window.draw(sprite1);
					}
				}
			for (int i = 0; i < 4; i++)
			{
				// Разукрашиваем тетрамино
				//sprite1.setTextureRect(IntRect(colornum * 36, 0, 36, 36));
				sprite1.setColor(Color(Colors[colornum][0], Colors[colornum][1], Colors[colornum][2], 100));
				// Устанавливаем позицию каждого кусочка тетрамино
				sprite1.setPosition(a[i].x * 36, a[i].y * 36);

				// Отрисовка спрайта
				window.draw(sprite1);
			}
			
			//Texture texture;
			//texture.loadFromFile("C:\\Users\\Владимир\\source\\repos\\Tetris\\x64\\Debug\\tetris.jpg");
			//Sprite sprite(texture);
			//sprite.move(75, 125);
			//window.draw(sprite);

			//Sprite sprite2(texture);
			//Sprite sprite3(texture);

			//sprite1.setTextureRect(IntRect(0, 0, 18, 18));
			//sprite2.setTextureRect(IntRect(0, 0, 18, 18));
			//sprite3.setTextureRect(IntRect(0, 0, 18, 18));
			//
			//sprite2.setPosition(30, 0);
			//sprite2.scale(2.f, 2.f);

			//sprite3.setPosition(0, 0);
			//sprite3.scale(3.f, 3.f);

			//window.draw(sprite1);
			//window.draw(sprite2);
			//window.draw(sprite3);
			window.display();
		}
	}
	return 0;
}