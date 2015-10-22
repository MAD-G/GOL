#include <SFML/Graphics.hpp>
#include <iostream>

void draw_grid(sf::RenderWindow &window)
{
	for (int i = 1; i <= 30; i++)
	{
		sf::Vertex line1[] =
		{
			sf::Vertex(sf::Vector2f(i * 20, 0)),
			sf::Vertex(sf::Vector2f(i * 20, 600))
		};
		sf::Vertex line2[] =
		{
			sf::Vertex(sf::Vector2f(0, i * 20)),
			sf::Vertex(sf::Vector2f(600, i * 20))
		};
		window.draw(line1, 2, sf::Lines);
		window.draw(line2, 2, sf::Lines);
	}
}

void check(bool cells[31][31])
{
	int changex[900];
	int changey[900];
	int a=0;
	for (int i = 1; i < 30; i++)
		for (int j = 1; j < 30; j++)
		{
			int n = 0;
			if (cells[i + 1][j] == true)
				n += 1;
			if (cells[i - 1][j] == true)
				n += 1;
			if (cells[i][j + 1] == true)
				n += 1;
			if (cells[i][j - 1] == true)
				n += 1;
			if (cells[i + 1][j + 1] == true)
				n += 1;
			if (cells[i - 1][j - 1] == true)
				n += 1;
			if (cells[i - 1][j + 1] == true)
				n += 1;
			if (cells[i + 1][j - 1] == true)
				n += 1;
			if (cells[i][j] == true)
			{
				if (n < 2 || n > 3)
				{
					changex[a] = i;
					changey[a] = j;
					a++;
				}
			}
			else
			{
				if (n == 3)
				{
					changex[a] = i;
					changey[a] = j;
					a++;
				}
			}
		}
	for (int i = 0; i < a; i++)
		cells[changex[i]][changey[i]] = !cells[changex[i]][changey[i]];
}

void redraw(bool cells[31][31], sf::RenderWindow &window)
{
	window.clear();
	draw_grid(window);
	for (int i=1;i<30;i++)
		for (int j=1;j<30;j++)
			if (cells[i][j] == true)
			{
				sf::RectangleShape rect(sf::Vector2f(20, 20));
				rect.setPosition(i * 20, j * 20);
				window.draw(rect);
			}
	window.display();
}

void change(sf::Vector2i pos, bool cells[31][31])
{
	int cellx = pos.x / 20;
	int celly = pos.y / 20;
	cells[cellx][celly] = !cells[cellx][celly];
}
int main()
{
	bool started = false;
	bool cells[31][31];
	for (int i = 0; i < 31; i++)
		for (int j = 0; j < 31; j++)
			cells[i][j] = false;
	sf::RenderWindow window(sf::VideoMode(600, 600), "Game Of Life");
	draw_grid(window);
	window.display();
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left && started==false)
				{
					sf::Vector2i position = sf::Mouse::getPosition(window);
					change(position, cells);
					redraw(cells, window);
				}
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::F)
				{
					if (started == false)
					{
						clock.restart();
					}
					started = !started;
				}
			}
		}
		if (started==true)
			if (clock.getElapsedTime().asMilliseconds() > 500)
			{
				check(cells);
				redraw(cells, window);
				clock.restart();
			}
	}

	return 0;
}