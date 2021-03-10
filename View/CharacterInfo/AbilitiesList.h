#ifndef ABILITIESLIST_H
#define ABILITIESLIST_H

#include <QWidget>

#include "Ability.h"
#include "Model/vector.h"
#include "Model/AbilitiesEnums.h"
using enums::ability;

class AbilitiesList : public QWidget {
    Q_OBJECT
private:
    vector<Ability*> abilities;

public:
    explicit AbilitiesList(QWidget* parent = nullptr);

    QPushButton* getButton(ability) const;

    void setScore(ability, unsigned) const;
    void setModifier(ability, int) const;
};

#endif // ABILITIESLIST_H
