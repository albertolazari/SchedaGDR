#include "Weapon.h"
#include <typeinfo>

Weapon::Weapon(
    const string& n,
    double w,
    const vector<Die>& d,
    const string& dmgType,
    int b,
    const vector<string>& p
)
    : Item(n, w), dice(d), damageType(dmgType), properties(p), bonus(b) {
    dice.sort();
    properties.sort();
}

const vector<Die>& Weapon::getDice() const { return dice; }
int Weapon::getBonus() const { return bonus; }
const string& Weapon::getDamageType() const { return damageType; }
const vector<string>& Weapon::getProperties() const { return properties; }

int Weapon::use() {
    int sum = 0;
    for (Die d : dice)
        sum += d.roll();
    sum += bonus;
    return sum < 0 ? 0 : sum;
}

Weapon* Weapon::clone() const { return new Weapon(*this); }

bool Weapon::operator==(const Item& i) const {
    if (!Item::operator==(i))
        return false;
    const Weapon& w = static_cast<const Weapon&>(i);
    return (
        dice == w.dice &&
        damageType == w.damageType &&
        properties == w.properties &&
        bonus == w.bonus
        );
}
bool Weapon::operator!=(const Item& i) const {
    if (Item::operator!=(i))
        return true;
    const Weapon& w = static_cast<const Weapon&>(i);
    return (
        dice != w.dice ||
        damageType != w.damageType ||
        properties != w.properties ||
        bonus != w.bonus
        );
}
