#ifndef AMMOWEAPON_H
#define AMMOWEAPON_H

#include "Ranged.h"

class AmmoWeapon : public Ranged {
private:
    string ammoUsed;
public:
    AmmoWeapon(
        const string& Name,
        double Weight,
        const vector<Die>& Dice,
        const string& DamageType,
        unsigned Range,
        const string& AmmoUsed,
        int Bonus = 0,
        const vector<string>& Properties = vector<string>()
    );

    AmmoWeapon(const Ranged& ranged, const string& ammo);

    const string& getAmmoUsed() const;
    AmmoWeapon* clone() const override;
    bool operator==(const Item&) const override;
    bool operator!=(const Item&) const override;
};

#endif // AMMOWEAPON_H
