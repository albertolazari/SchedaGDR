#include "Ranged.h"

Ranged::Ranged(
    const string& n,
    double w,
    const vector<Die>& d,
    const string& dmgType,
    unsigned r,
    int b,
    const vector<string>& p
)
    : Weapon(n, w, d, dmgType, b, p), range(r) {}

Ranged::Ranged(const Weapon &weapon, unsigned r)
    : Weapon(weapon), range(r) {}

unsigned Ranged::getRange() const { return range; }

Ranged* Ranged::clone() const { return new Ranged(*this); }

bool Ranged::operator==(const Item& i) const {
    if (!Item::operator==(i))
        return false;
    const Ranged& r = static_cast<const Ranged&>(i);
    return (
        Weapon::operator==(r) &&
        range == r.range
        );
}
bool Ranged::operator!=(const Item& i) const {
    if (Item::operator!=(i))
        return true;
    const Ranged& r = static_cast<const Ranged&>(i);
    return (
        Weapon::operator!=(r) ||
        range != r.range
        );
}
