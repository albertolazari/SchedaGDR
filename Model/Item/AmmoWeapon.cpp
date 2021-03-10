#include "AmmoWeapon.h"

AmmoWeapon::AmmoWeapon(
    const string& n,
    double w,
    const vector<Die>& d,
    const string& dmgType,
    unsigned r,
    const string& ammo,
    int b,
    const vector<string>& p
)
    : Ranged(n, w, d, dmgType, r, b, p), ammoUsed(ammo) {}

AmmoWeapon::AmmoWeapon(const Ranged &ranged, const std::string &ammo)
    : Ranged(ranged), ammoUsed(ammo) {}

const string& AmmoWeapon::getAmmoUsed() const { return ammoUsed; }

AmmoWeapon* AmmoWeapon::clone() const { return new AmmoWeapon(*this); }

bool AmmoWeapon::operator==(const Item &i) const {
    if (!Item::operator==(i))
        return false;
    const AmmoWeapon& a = static_cast<const AmmoWeapon&>(i);
    return (
        Ranged::operator==(a) &&
        ammoUsed == a.ammoUsed
        );
}
bool AmmoWeapon::operator!=(const Item &i) const {
    if (Item::operator!=(i))
        return true;
    const AmmoWeapon& a = static_cast<const AmmoWeapon&>(i);
    return (
        Ranged::operator!=(a) ||
        ammoUsed != a.ammoUsed
        );
}
