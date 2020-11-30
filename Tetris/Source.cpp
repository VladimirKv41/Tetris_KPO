#include <SFML/Graphics.hpp>
using namespace sf;

const int M  = 20;
const int N = 10;
int field[M][N] = { 0 };
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

int main(){
	ContextSettings settings;
	settings.antialiasingLevel = 4;
	RenderWindow window(VideoMode(500, 500), "Best Tetris");
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
		}
		window.clear(Color(25,165,250,0));
		int n = 3;
		for (int i = 0; i < 4; i++) {
			a[i].x = figures[n][i] % 2;
			a[i].y = figures[n][i] / 2;
		}
		Texture texture;
		texture.loadFromFile("C:\\Users\\Владимир\\source\\repos\\Tetris\\x64\\Debug\\tiles.png");
		Sprite sprite1(texture);
		sprite1.setTextureRect(IntRect(0, 0, 18, 18));
		for (int i = 0; i < 4; i++) {
			sprite1.setPosition(a[i].x * 18, a[i].y * 18);
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