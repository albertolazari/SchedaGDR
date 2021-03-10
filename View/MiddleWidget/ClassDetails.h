#ifndef CLASSDETAILS_H
#define CLASSDETAILS_H

#include <QBoxLayout>

#include "View/Label.h"
#include "HitDiceManager.h"

class ClassDetails : public QWidget {
    Q_OBJECT
private:
    unsigned level;
    Label* nameLabel, *levelLabel, *dieLabel;
    HitDiceManager* hitDiceManager;

public:
    ClassDetails(
        const QString& name,
        unsigned hitDieFaces,
        QWidget *parent = nullptr,
        unsigned level = 1,
        unsigned hitDiceUsed = 0
    );

    QString getClassName() const;
    QPushButton* getThrowButton() const;
    void levelUp();
    void setUsedHitDice(unsigned) const;
};

#endif // CLASSDETAILS_H
