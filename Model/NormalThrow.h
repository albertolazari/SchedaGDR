#ifndef NORMALTHROW_H
#define NORMALTHROW_H

class NormalThrow {
private:
    unsigned dieScore, dieFaces, proficiencyBonus;
    int abilityModifier;
    bool isProficient;

public:
    virtual ~NormalThrow() = default;
    NormalThrow(unsigned dieScore, unsigned dieFaces, int abilityMod, bool proficient = false, unsigned bonus = 0);

    unsigned getDieScore() const;
    unsigned getDieFaces() const;
    unsigned getProficiencyBonus() const;
    int getAbilityModifier() const;
    bool isProficiencyApplied() const;

    int getThrow() const;
};

#endif // NORMALTHROW_H
