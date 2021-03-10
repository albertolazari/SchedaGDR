#include "AttackThrow.h"

AttackThrow::AttackThrow(
    unsigned dieScore,
    unsigned dmg,
    const string& dtype,
    int abilityMod,
    unsigned wpb,
    unsigned bdmg,
    const string& bdt,
    bool proficient,
    unsigned bonus
)
    : NormalThrow(dieScore, 20, abilityMod, proficient, bonus),
     // In dmg è già stato sommato Weapon Bonus(wpb)
      damage(dmg - wpb),
      bonusDamage(bdmg),
      weaponBonus(wpb),
      damageType(dtype),
      bonusDamageType(bdt) {}

unsigned AttackThrow::getDamage() const { return damage; }
unsigned AttackThrow::getBonusDamage() const { return bonusDamage; }
unsigned AttackThrow::getWeaponBonus() const { return weaponBonus; }
std::string AttackThrow::getDamageType() const { return damageType; }
std::string AttackThrow::getBonusDamageType() const { return bonusDamageType; }

int AttackThrow::getThrow() const {
    int result = getDieScore() + getAbilityModifier() +
            (isProficiencyApplied() ? getProficiencyBonus() : 0) + weaponBonus;
    return result < 1 ? 1 : result;
}
unsigned AttackThrow::getTotalDamage() const {
    int n = damage + weaponBonus + bonusDamage + getAbilityModifier();
    return (n < 0 ? 0 : n);
}
