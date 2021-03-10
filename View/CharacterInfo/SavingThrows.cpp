#include "SavingThrows.h"

SavingThrows::SavingThrows(ability a, QWidget *parent, int Bonus)
    : QFrame(parent),
      prof(false),
      SavingThrowsLayout(new QHBoxLayout(this)),
      LName(new QLabel(QString::fromStdString(enums::fromAbilityToString(a)))),
      PBonus(new DieThrowButton(Bonus)),
      tick(new QPushButton(this)) {
    setLayout(SavingThrowsLayout);

    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setLineWidth(2);
    setFixedHeight(40);

    tick->setFixedSize(15, 15);
    tick->setStyleSheet("QPushButton {background-color: white;}");
    SavingThrowsLayout->addWidget(tick);

    PBonus->setFixedSize(35,23);

    SavingThrowsLayout->addWidget(LName);
    SavingThrowsLayout->addWidget(PBonus);
}

void SavingThrows::updateBonus(int n) const { PBonus->updateBonus(n); }

void SavingThrows::changeProf() {
    if (!prof) {
        prof = true;
        tick->setStyleSheet("QPushButton {background-color: grey;}");
    }
    else {
        prof = false;
        tick->setStyleSheet("QPushButton {background-color: white;}");
    }
}

QPushButton *SavingThrows::getTick() const { return tick; }
QPushButton *SavingThrows::getModifierButton() const { return PBonus; }

void SavingThrows::setProf(bool p) {
    prof = p;
    if (prof)
        tick->setStyleSheet("QPushButton {background-color: grey;}");
    else
        tick->setStyleSheet("QPushButton {background-color: white;}");
}

