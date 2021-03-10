#include "NormalThrow.h"

NormalThrow::NormalThrow(unsigned score, unsigned faces, int abilityMod, bool proficient, unsigned bonus)
    : dieScore(score), dieFaces(faces), proficiencyBonus(bonus), abilityModifier(abilityMod), isProficient(proficient) {}

unsigned NormalThrow::getDieScore() const { return dieScore; }
unsigned NormalThrow::getDieFaces() const { return dieFaces; }
unsigned NormalThrow::getProficiencyBonus() const { return proficiencyBonus; }
int NormalThrow::getAbilityModifier() const { return abilityModifier; }
bool NormalThrow::isProficiencyApplied() const { return isProficient; }

int NormalThrow::getThrow() const {
    int result = dieScore + abilityModifier + (isProficient ? proficiencyBonus : 0);
    return result < 1 ? 1 : result;
}
