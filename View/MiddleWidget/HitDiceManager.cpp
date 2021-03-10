#include "HitDiceManager.h"
#include <string>

const unsigned HitDiceManager::squaresPerLine = 10;

HitDiceManager::HitDiceManager(unsigned maxDice, QWidget* parent, unsigned usedDice)
    : QFrame(parent),
      throwButton(new QPushButton("Tira", this)),
      indicator(new QLabel(
          QString::fromStdString(std::to_string(maxDice - usedDice) + "/" + std::to_string(maxDice)), this
      )),
      squaresLayout(new QVBoxLayout) {
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setLineWidth(2);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QLabel* title = new QLabel("Dadi Vita", this);
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);

    QHBoxLayout* indicatorLayout = new QHBoxLayout;
    indicatorLayout->setAlignment(Qt::AlignLeft);
    mainLayout->addLayout(indicatorLayout);

    indicatorLayout->addWidget(new QLabel("Disponibili:", this));
    indicatorLayout->addWidget(indicator);

    QHBoxLayout* hLayout = new QHBoxLayout;
    mainLayout->addLayout(hLayout);

    squaresLayout->setAlignment(Qt::AlignLeft);
    squaresLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->addLayout(squaresLayout);

    for (unsigned i = 0; i < maxDice; ++i)
        diceSlots.push_back(new QFrame(this));

    unsigned i = 0;

    QHBoxLayout* l = new QHBoxLayout;
    l->setAlignment(Qt::AlignLeft);
    squaresLayout->addLayout(l);

    for (QFrame* slot : diceSlots) {
        if (i % squaresPerLine == 0 && i > 0) {
            l = new QHBoxLayout;
            l->setAlignment(Qt::AlignLeft);
            squaresLayout->addLayout(l);
        }

        slot->setFixedSize(QSize(15, 15));
        slot->setFrameStyle(QFrame::Panel);
        if (i < usedDice)
            slot->setStyleSheet("QFrame {background-color: black;}");
        else
            slot->setStyleSheet("QFrame {background-color: white;}");

        l->addWidget(slot);

        ++i;
    }

    QVBoxLayout* buttonLayout = new QVBoxLayout;
    buttonLayout->setAlignment(Qt::AlignRight);
    hLayout->addLayout(buttonLayout);

    buttonLayout->addWidget(throwButton);
}

QPushButton *HitDiceManager::getThrowButton() const { return throwButton; }

void HitDiceManager::setUsedSlots(unsigned n) const {
    unsigned i = 0;
    for (QFrame* slot : diceSlots) {
        if (i < n)
            slot->setStyleSheet("QFrame {background-color: black;}");
        else
            slot->setStyleSheet("QFrame {background-color: white;}");

        ++i;
    }
    indicator->setText(
        QString::fromStdString(std::to_string(diceSlots.size() - n) + "/" + std::to_string(diceSlots.size()))
    );
}

void HitDiceManager::addSlot() {
    QFrame* newSlot = new QFrame(this);
    newSlot->setFixedSize(QSize(15, 15));
    newSlot->setFrameStyle(QFrame::Panel);
    newSlot->setStyleSheet("QFrame {background-color: white;}");
    diceSlots.push_back(newSlot);

    if ((diceSlots.size() - 1) % squaresPerLine == 0) {
        QHBoxLayout* l = new QHBoxLayout;
        l->setAlignment(Qt::AlignLeft);
        squaresLayout->addLayout(l);
    }
    QLayout* l = dynamic_cast<QLayout*>(squaresLayout->itemAt((diceSlots.size() - 1) / squaresPerLine));
    if (l != nullptr)
        l->addWidget(newSlot);
}
