#ifndef RANGED_H
#define RANGED_H

#include "Weapon.h"

class Ranged : public Weapon {
private:
    unsigned range;
public:
    Ranged(
        const string& Name,
        double Weight,
        const vector<Die>& Dice,
        const string& damageType,
        unsigned Range,
        int Bonus = 0,
        const vector<string>& Properties = vector<string>()
    );

    Ranged(const Weapon& weapon, unsigned r);

    unsigned getRange() const;
    Ranged* clone() const override;
    bool operator== (const Item&) const override;
    bool operator!= (const Item&) const override;
};

#endif // RANGED_H
