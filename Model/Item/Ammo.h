#ifndef AMMO_H
#define AMMO_H

#include <stdexcept>

#include "Object.h"
#include "../Die.h"

class Ammo : public Object {
private:
    bool hasBonusDamage;
    string damageType;
    Die bonusDmg;

public:
    Ammo(
        const string& n,
        double w,
        unsigned int a = 1,
        const string& desc = "",
        bool bonusDmg = false,
        const string& dmg = "",
        const Die &d = Die(0)
    );
    Ammo (const Object& o, bool bonusDmg = false, const string& dmg = "", const Die &d = 0);

    bool dealsBonusDamage() const;
    string getDamageType() const;
    const Die& getBonusDamage () const;

    int use() override;
    Ammo* clone() const override;
    bool operator== (const Item &)const override;
    bool operator!= (const Item &)const override;
};

#endif // AMMO_H
