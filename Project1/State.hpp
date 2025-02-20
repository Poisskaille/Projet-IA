#ifndef STATE_HPP
#define STATE_HPP
#include <SFML/Graphics.hpp>

class State {
public:
	int ammo;
	bool empthy = false;
	bool ammoFind = false;

	int Ammo() const { return ammo; }
	bool Empthy() const { return empthy; }
	bool AmmoFind() const { return ammoFind; }

	void Reload(int munitions, bool vide) { ammo = munitions; empthy = vide; }
	void Shoot(int munitions) { ammo - munitions; }
};

#endif