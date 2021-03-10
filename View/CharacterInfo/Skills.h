#ifndef SKILLS_H
#define SKILLS_H

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "View/DieThrowButton.h"
#include "Model/AbilitiesEnums.h"
using enums::ability;
using enums::skill;

class Skills: public QFrame {
private:
    int prof;
    skill skillEnum;
    ability associatedAbility;

    QHBoxLayout* skillLayout;
    QPushButton* tick;
    QLabel* LName;
    QLabel* LSkill;
    DieThrowButton* PBonus;

public:
    explicit Skills(ability associatedAbility, skill Skill, QWidget *parent = nullptr, int Bonus = 0);

    QPushButton* getTick() const;
    QPushButton* getModifierButton() const;

    skill getSkill() const;
    ability getAssociatedAbility() const;

    void setBonus(int) const;
    void setProf(bool proficiency, bool mastery = false);
    void changeProf();
};

#endif // SKILLS_H
