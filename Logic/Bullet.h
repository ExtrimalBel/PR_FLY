#ifndef GAMEBULLET_H
#define GAMEBULLET_H
#include <SFML/Graphics.hpp>
class Bullet
{
	double cox, coy;
	sf::Image bulletimg;
	sf::Texture bullettext;
	sf::Sprite bulletrect;
	int direction; // Направление 1 - право 2 - лево
	double speed; // Скорость пули
	double demage; // Урон пули
	
public:
	bool Is_For_Delete = false;
	Bullet(sf::Vector2f position, double cx, double cy, const char *image, int dir, float speed, double demage);
	Bullet(sf::Vector2f position, double cx, double cy, sf::Texture &text, int dir, float speed, double demage);
	void Bullet::Move(float time);
	void Draw(sf::RenderWindow &window) { window.draw(bulletrect); }
	double GetDemage() { return demage; }
	void SetDelete(bool value); // Устанавливает пулю для удаления
	bool IsForDelete(); // Проверка на то надо ли удалять пулю
	sf::IntRect ReturnBulletRect();
	sf::Sprite& GetSprite() { return bulletrect; }
	sf::Image& GetImage() { return bulletimg; }
};
#endif