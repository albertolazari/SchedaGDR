#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
#include "../vector.h"
#include "../Die.h"

class Weapon : public Item {
private:
    vector<Die> dice;
    string damageType;
    vector<string> properties;
    int bonus;
public:
    Weapon(
        const string& Name,
        double Weight,
        const vector<Die>& Dice,
        const string& DamageType,
        int Bonus = 0,
        const vector<string>& Properties = vector<string>()
    );

    const vector<Die>& getDice() const;
    int getBonus() const;
    const string& getDamageType() const;
    const vector<string>& getProperties() const;

    int use() override;
    Weapon* clone() const override;

    bool operator== (const Item &)const override;
    bool operator!= (const Item &)const override;
};

#endif // WEAPON_H
