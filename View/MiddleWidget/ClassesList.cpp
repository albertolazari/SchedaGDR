#include "ClassesList.h"

ClassesList::ClassesList(QWidget *parent) : QTabWidget(parent) {}

QPushButton *ClassesList::getThrowButton(const QString& className) const {
    for (int i = 0; i < count(); ++i) {
        ClassDetails* c = dynamic_cast<ClassDetails*>(widget(i));
        if (c != nullptr)
            if (c->getClassName() == className)
                return c->getThrowButton();
    }
    return nullptr;
}

void ClassesList::addClass(const Character::Class& c) {
    addTab(
        new ClassDetails(
            QString::fromStdString(c.getName()),
            c.getHitDieFaces(),
            this,
            c.getLevel(),
            c.getHitDiceUsed()
        ),
        QString::fromStdString(c.getName())
    );
}

void ClassesList::removeClasses() {
    for (int i = 0; i < count(); ++i) {
        delete widget(0);
    }
    clear();
}
void ClassesList::levelUpSelectedClass() const {
    ClassDetails* currentClass = dynamic_cast<ClassDetails*>(currentWidget());
    if (currentClass != nullptr)
        currentClass->levelUp();
}
void ClassesList::setHitDiceUsed(const QString& className, unsigned n) const {
    for (int i = 0; i < count(); ++i) {
        ClassDetails* c = dynamic_cast<ClassDetails*>(widget(i));
        if (c != nullptr)
            if (c->getClassName() == className)
                c->setUsedHitDice(n);
    }
}

QString ClassesList::getCurrentClassName() const {
    ClassDetails* currentClass = dynamic_cast<ClassDetails*>(currentWidget());
    if (currentClass != nullptr)
        return currentClass->getClassName();
    return "";
}
