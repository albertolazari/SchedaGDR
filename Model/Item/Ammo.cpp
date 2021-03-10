#include "Ammo.h"

Ammo::Ammo(const string& n, double w, unsigned int a, const string& desc, bool bd, const string& dmg, const Die& d) :
    Object(n, w, a, desc), hasBonusDamage(bd), damageType(dmg), bonusDmg(d) {}

Ammo::Ammo(const Object &o, bool bd, const std::string &dmg, const Die &d)
    : Object(o), hasBonusDamage(bd), damageType(dmg), bonusDmg(d) {}

bool Ammo::dealsBonusDamage() const {
    return hasBonusDamage;
}

std::string Ammo::getDamageType() const {
    if (!hasBonusDamage)
        throw std::runtime_error("La munizione non infligge danno bonus");
    return damageType;
}

const Die &Ammo::getBonusDamage() const {
    if (!hasBonusDamage)
        throw std::runtime_error("La munizione non infligge danno bonus");
    return bonusDmg;
}

int Ammo::use() {
    if (getAmount() == 0) return 0;
    if (hasBonusDamage) {
        Object::use();
        return bonusDmg.roll();
    }
    else
        return Object::use();
}

Ammo *Ammo::clone() const {
    return new Ammo(*this);
}

bool Ammo::operator==(const Item& i) const {
    if (!Item::operator==(i))
        return false;
    const Ammo& w = static_cast<const Ammo&>(i);
    return (hasBonusDamage ? w.hasBonusDamage && damageType == w.damageType && bonusDmg == w.bonusDmg : !w.hasBonusDamage);
}
bool Ammo::operator!=(const Item& i) const {
    if (Item::operator!=(i))
        return true;
    const Ammo& w = static_cast<const Ammo&>(i);
    return (hasBonusDamage ? !w.hasBonusDamage || damageType != w.damageType || bonusDmg != w.bonusDmg : w.hasBonusDamage);
}
