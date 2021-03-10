#ifndef ATTACKTHROW_H
#define ATTACKTHROW_H

#include <string>
using std::string;

#include "NormalThrow.h"

class AttackThrow : public NormalThrow {
private:
    unsigned damage, bonusDamage, weaponBonus;
    string damageType, bonusDamageType;

public:
    AttackThrow(
        unsigned dieScore,
        unsigned damage,
        const string& damageType,
        int abilityMod = 0,
        unsigned weaponBonus = 0,
        unsigned bonusDamage = 0,
        const string& bonusDamageType = "",
        bool proficient = false,
        unsigned proficiencyBonus = 0
    );

    unsigned getDamage() const;
    unsigned getBonusDamage() const;
    unsigned getWeaponBonus() const;
    string getDamageType() const;
    string getBonusDamageType() const;

    int getThrow() const;
    unsigned getTotalDamage() const;
};

#endif // ATTACKTHROW_H
