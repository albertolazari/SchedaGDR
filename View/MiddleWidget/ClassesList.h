#ifndef CLASSESLIST_H
#define CLASSESLIST_H

#include <QTabWidget>

#include "ClassDetails.h"
#include "Model/Character.h"

class ClassesList : public QTabWidget {
public:
    explicit ClassesList(QWidget* parent = nullptr);

    QPushButton* getThrowButton(const QString& className) const;

    void addClass(const Character::Class&);
    void removeClasses();
    void levelUpSelectedClass() const;
    void setHitDiceUsed(const QString& className, unsigned) const;

    QString getCurrentClassName() const;
};

#endif // CLASSESLIST_H
