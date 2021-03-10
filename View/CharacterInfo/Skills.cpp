#include "Skills.h"

Skills::Skills(ability Ability, skill Skill, QWidget *parent, int Bonus)
    : QFrame(parent),
      prof(0),
      skillEnum(Skill),
      associatedAbility(Ability),
      skillLayout(new QHBoxLayout(this)),
      tick(new QPushButton(this)),
      LName(new QLabel(QString::fromStdString(fromAbilityToString(Ability)), this)),
      LSkill(new QLabel(QString::fromStdString(fromSkillToString(Skill)), this)),
      PBonus(new DieThrowButton(Bonus, this)) {
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setLineWidth(2);
    setFixedHeight(40);

    setLayout(skillLayout);

    tick->setFixedSize(15,15);
    tick->setStyleSheet("QPushButton {background-color: white;}");
    skillLayout->addWidget(tick);

    PBonus->setFixedSize(35,23);

    skillLayout->addWidget(LSkill);
    skillLayout->addWidget(LName);
    skillLayout->addWidget(PBonus);
}

QPushButton* Skills::getTick() const { return tick; }
QPushButton *Skills::getModifierButton() const { return PBonus; }

enums::skill Skills::getSkill() const { return skillEnum; }
enums::ability Skills::getAssociatedAbility() const { return associatedAbility; }

void Skills::setBonus(int n) const { PBonus->updateBonus(n); }

void Skills::setProf(bool proficiency, bool mastery) {
    if (proficiency) {
        if (mastery) {
            prof = 2;
            tick->setStyleSheet("QPushButton {background-color: black;}");
        }
        else {
            prof = 1;
            tick->setStyleSheet("QPushButton {background-color: grey;}");
        }
    }
    else {
        prof = 0;
        tick->setStyleSheet("QPushButton {background-color: white;}");
    }
}
void Skills::changeProf() {
    if(prof == 0) {
        prof = 1;
        tick->setStyleSheet("QPushButton {background-color: grey;}");
    }
    else if (prof == 1) {
        prof = 2;
        tick->setStyleSheet("QPushButton {background-color: black;}");
    }
    else {
        prof = 0;
        tick->setStyleSheet("QPushButton {background-color: white;}");
    }
}
