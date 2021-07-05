#include <SFML/Graphics.hpp>
#include <string>

#include "Tower.hpp"
#include "Enemy.hpp"
#include "Modifier.hpp"
#include "Assets.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	window.setFramerateLimit(60);

	sf::Font demoFont;
	demoFont.loadFromFile(get_assets_path() + "/ProggyClean.ttf");
	sf::Text demoText;
	demoText.setPosition(sf::Vector2f(640, 360));
	demoText.setFont(demoFont);
	demoText.setCharacterSize(32);
	demoText.setString("hello demo text");

	Modifier noModifier;
	noModifier.toggleTowerScalarModeAndClear();
	noModifier.setEnemyHealth(1);

	std::vector<Tower> towerVector;
	std::vector<Enemy> enemyVector;

	Tower testTower;
	testTower.createTowerType("Test", 0, sf::Vector2f(640, 360), noModifier);
	towerVector.push_back(testTower);

	Enemy testEnemy;
	testEnemy.createEnemyType("Green", 0, sf::Vector2f(200, 100), noModifier);
	enemyVector.push_back(testEnemy);

	Enemy testEnemy2;
	testEnemy2.createEnemyType("Red", 0, sf::Vector2f(400, 100), noModifier);
	enemyVector.push_back(testEnemy2);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		for (int j = 0; j < enemyVector.size(); j++) {
			for (int i = 0; i < towerVector.size(); i++) {
				float damage = towerVector[i].bulletUpdate(enemyVector[j]);
				enemyVector[j].update(damage);
				towerVector[i].increaseTowerDamageDone(damage);
				if (enemyVector[j].getDead()) {
					towerVector[i].killCountIncrement();
				}
			}
			if (enemyVector[j].getDead()) {
				enemyVector[j].clear();
				enemyVector.erase(enemyVector.begin() + j);
			}
		}

		for (int i = 0; i < towerVector.size(); i++) {
			towerVector[i].update(window);
		}

		window.clear();

		for (int i = 0; i < enemyVector.size(); i++) {
			enemyVector[i].draw(window);
		}

		for (int i = 0; i < towerVector.size(); i++) {
			towerVector[i].draw(window);
		}

		window.draw(demoText);

		window.display();
	}

	return 0;
}
