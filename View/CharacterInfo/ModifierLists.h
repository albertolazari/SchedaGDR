#ifndef MODIFIERLISTS_H
#define MODIFIERLISTS_H

#include <QWidget>
#include <QBoxLayout>

#include "Stat.h"
#include "SkillsList.h"
#include "SavingThrowsList.h"

class ModifierLists : public QWidget {
    Q_OBJECT
private:
    SavingThrowsList* S2;
    SkillsList* S;

public:
    explicit ModifierLists(QWidget* parent = nullptr);

    SavingThrowsList* getSavingThrowsList() const;
    SkillsList* getSkillsList() const;
};

#endif // MODIFIERLISTS_H
