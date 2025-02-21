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

	void Reload(int munition) {
		ammo = munition;
		empthy = (ammo == 0);
		ammoFind = false;
	}
	void Shoot(int munitions) {
		ammo = std::max(0, ammo - munitions);
		if (ammo == 0) empthy = true;
	}
	void SetEmpthy(bool vide) { empthy = vide; }
};

#endif