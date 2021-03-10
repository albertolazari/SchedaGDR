#include "DieThrowButton.h"
#include <string>

DieThrowButton::DieThrowButton(int bonus, QWidget *parent)
    : QPushButton(
          QString::fromStdString(bonus < 0 ? std::to_string(bonus) : "+" + std::to_string(bonus)),
          parent
      ) {}

void DieThrowButton::updateBonus(int x) {
    setText(QString::fromStdString(x < 0 ? std::to_string(x) : "+" + std::to_string(x)));
}

QPushButton *DieThrowButton::getButton() { return this; }
