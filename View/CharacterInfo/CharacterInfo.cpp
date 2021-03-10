#include "CharacterInfo.h"

CharacterInfo::CharacterInfo(QWidget *parent)

    : QWidget(parent), mainLayout(new QHBoxLayout), centralLayout(new QVBoxLayout),modifiers(new ModifierLists),
      abilities(new AbilitiesList(this)){

    setLayout(mainLayout);

    mainLayout->addWidget(abilities);

    addStatistics();
    addModifierLists();

    mainLayout->addLayout(centralLayout);
}

AbilitiesList *CharacterInfo::getAbilitiesList() const { return abilities; }
ModifierLists *CharacterInfo::getModifierLists() const { return modifiers; }

void CharacterInfo::setAbilityScore(ability a, unsigned s) const { abilities->setScore(a, s); }
void CharacterInfo::setAbilityModifier(ability a, int m) const { abilities->setModifier(a, m); }

void CharacterInfo::setProficiencyBonus(unsigned n) const { proficiencyBonus->setValue(n); }
void CharacterInfo::setArmorClass(unsigned n) const { armorClass->setValue(n); }

void CharacterInfo::setMaxHp(unsigned n) const { hp->setMaxHp(n); }
void CharacterInfo::setCurrentHp(unsigned n) const { hp->setCurrentHp(n); }
void CharacterInfo::setBonusHp(unsigned n) const { hp->setBonusHp(n); }


void CharacterInfo::addStatistics() {
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->setSpacing(2);

    proficiencyBonus = new Stat("Bonus\nCompetenza", this);
    hLayout->addWidget(proficiencyBonus);

    armorClass = new Stat("Classe\nArmatura", this);
    hLayout->addWidget(armorClass);

    hp = new HpIndicator(this);
    hLayout->addWidget(hp);

    centralLayout->addLayout(hLayout);
}

void CharacterInfo::addModifierLists() {
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidget(modifiers);
    scrollArea->setWidgetResizable(true);

    centralLayout->addWidget(scrollArea);
}
