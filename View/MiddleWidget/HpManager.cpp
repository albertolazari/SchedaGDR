#include "HpManager.h"

HpManager::HpManager(QWidget* parent)
    : QFrame(parent), input(new QSpinBox(this)),
      heal(new QPushButton("Cura", this)),
      takeDamage(new QPushButton("Prendi Danno", this)) {
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setLineWidth(2);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    input->setMinimum(0);
    input->setMaximum(99999);
    mainLayout->addWidget(input);

    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    mainLayout->addLayout(buttonsLayout);

    buttonsLayout->addWidget(heal);
    buttonsLayout->addWidget(takeDamage);
}

QPushButton* HpManager::getHealButton() const { return heal; }
QPushButton* HpManager::getDamageButton() const { return takeDamage; }

unsigned HpManager::getValue() const { return input->value(); }
