#ifndef CLASSINFO_H
#define CLASSINFO_H

#include <QBoxLayout>

#include "ClassesList.h"

class ClassInfo : public QWidget {
    Q_OBJECT
private:
    QPushButton* add, *remove, *levelUp;
    ClassesList* classes;

public:
    explicit ClassInfo(QWidget *parent = nullptr);

    QPushButton* getAddButton() const;
    QPushButton* getRemoveButton() const;
    QPushButton* getLevelUpButton() const;
    QPushButton* getThrowButton(const QString& className) const;

    void addClass(const Character::Class&) const;
    void removeClasses() const;
    void levelUpSelectedClass() const;
    void setHitDiceUsed(const QString& className, unsigned) const;

    QString getCurrentClassName() const;
};

#endif // CLASSINFO_H
