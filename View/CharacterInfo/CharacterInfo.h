#ifndef CHARACTERINFO_H
#define CHARACTERINFO_H

#include <QWidget>
#include <QHBoxLayout>
#include <QScrollArea>

#include "AbilitiesList.h"
#include "ModifierLists.h"
#include "HpIndicator.h"

class CharacterInfo : public QWidget {
    Q_OBJECT
private:
    QHBoxLayout* mainLayout;
    QVBoxLayout* centralLayout;

    ModifierLists* modifiers;

    AbilitiesList* abilities;
    Stat* proficiencyBonus, *armorClass;
    HpIndicator* hp;

    void addStatistics();
    void addModifierLists();

public:
    explicit CharacterInfo(QWidget *parent = nullptr);

    AbilitiesList* getAbilitiesList() const;
    ModifierLists* getModifierLists() const;

    void setAbilityScore(ability, unsigned) const;
    void setAbilityModifier(ability, int) const;

    void setProficiencyBonus(unsigned) const;
    void setArmorClass(unsigned) const;

    void setMaxHp(unsigned) const;
    void setCurrentHp(unsigned) const;
    void setBonusHp(unsigned) const;
};

#endif // CHARACTERINFO_H
