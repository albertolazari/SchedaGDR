#include "Ability.h"
#include <string>

Ability::Ability(ability a, QWidget *parent, unsigned score, int modifier)
    : Stat(QString::fromStdString(enums::fromAbilityToString(a)), parent, score), button(new DieThrowButton(modifier, this)) {
    // Il layout serve per rendere il pulsante centrato
    QHBoxLayout* layout = new QHBoxLayout;

    button->setFixedSize(QSize(35, 23));

    layout->addWidget(button);
    mainLayout->addLayout(layout);
}

void Ability::setModifier(int x) const { button->updateBonus(x); }
QPushButton *Ability::getButton() const { return button->getButton(); }
