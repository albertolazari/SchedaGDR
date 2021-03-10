#ifndef SAVINGTHROWSLIST_H
#define SAVINGTHROWSLIST_H

#include <QVBoxLayout>

#include "SavingThrows.h"
#include "Model/vector.h"
#include "Model/Character.h"

class SavingThrowsList : public QWidget {
    Q_OBJECT
private:
    vector<SavingThrows*>v;

public:
    explicit SavingThrowsList(QWidget *parent = nullptr);

    SavingThrows* getSavingThrow(ability) const;
};

#endif // SAVINGTHROWSLIST_H
