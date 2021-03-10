#include "AbilitiesList.h"

AbilitiesList::AbilitiesList(QWidget *parent)
    : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    for (unsigned i = 0; i < enums::abilitiesNumber; ++i)
        abilities.push_back(new Ability(static_cast<ability>(i), this));

    for (Ability* a : abilities)
        mainLayout->addWidget(a);
}

QPushButton *AbilitiesList::getButton(ability a) const { return abilities[a]->getButton(); }

void AbilitiesList::setScore(ability a, unsigned s) const {
    abilities[a]->setValue(s);
}
void AbilitiesList::setModifier(ability a, int m) const {
    abilities[a]->setModifier(m);
}
