#ifndef SAVINGTHROWS_H
#define SAVINGTHROWS_H

#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "View/DieThrowButton.h"
#include "Model/AbilitiesEnums.h"
using enums::ability;

class SavingThrows : public QFrame {
    Q_OBJECT
private:
    bool prof;

    QHBoxLayout* SavingThrowsLayout;
    QLabel* LName;

    DieThrowButton* PBonus;
    QPushButton* tick;

public:
    explicit SavingThrows(ability, QWidget *parent = nullptr, int Bonus = 0);

    QPushButton* getTick() const;
    QPushButton* getModifierButton() const;

    void setProf(bool);
    void changeProf();
    void updateBonus(int n) const;
};

#endif // SAVINGTHROWS_H
