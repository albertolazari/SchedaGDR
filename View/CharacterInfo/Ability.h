#ifndef ABILITY_H
#define ABILITY_H

#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>

#include "Stat.h"
#include "View/DieThrowButton.h"
#include "Model/AbilitiesEnums.h"
using enums::ability;

class Ability : public Stat {
private:
   DieThrowButton* button;

public:
    Ability(ability, QWidget *parent = nullptr, unsigned score = 0, int modifier = 0);

    void setModifier(int) const;
    QPushButton* getButton() const;
};

#endif // ABILITY_H
