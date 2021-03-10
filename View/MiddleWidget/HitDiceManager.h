#ifndef HITDICEMANAGER_H
#define HITDICEMANAGER_H

#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "Model/vector.h"

class HitDiceManager : public QFrame {
private:
    vector<QFrame*> diceSlots;
    QPushButton* throwButton;
    QLabel* indicator;
    QVBoxLayout* squaresLayout;

public:
    static const unsigned squaresPerLine;

    explicit HitDiceManager(unsigned maxDice = 1, QWidget* parent = nullptr, unsigned usedDice = 0);

    QPushButton* getThrowButton() const;

    void setUsedSlots(unsigned) const;
    void addSlot();
};

#endif // HITDICEMANAGER_H
