#include "ModifierLists.h"

ModifierLists::ModifierLists(QWidget *parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout;

    S2 = new SavingThrowsList(this);
    mainLayout->addWidget(S2);

    S = new SkillsList(this);
    mainLayout->addWidget(S);

    setLayout(mainLayout);
}

SavingThrowsList *ModifierLists::getSavingThrowsList() const { return S2; }
SkillsList *ModifierLists::getSkillsList() const { return S; }
