#include "ClassInfo.h"

ClassInfo::ClassInfo(QWidget *parent)
    : QWidget(parent),
      add(new QPushButton("Aggiungi", this)),
      remove(new QPushButton("Rimuovi", this)),
      levelUp(new QPushButton("Aumenta Livello", this)),
      classes(new ClassesList(this)) {
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    QLabel* title = new QLabel("Classi", this);
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);

    mainLayout->addWidget(classes);

    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    mainLayout->addLayout(buttonsLayout);

    buttonsLayout->addWidget(add);
    buttonsLayout->addWidget(remove);
    buttonsLayout->addWidget(levelUp);
}

QPushButton *ClassInfo::getAddButton() const { return add; }
QPushButton *ClassInfo::getRemoveButton() const { return remove; }
QPushButton *ClassInfo::getLevelUpButton() const { return levelUp; }

QPushButton *ClassInfo::getThrowButton(const QString& className) const { return classes->getThrowButton(className); }

void ClassInfo::addClass(const Character::Class& c) const { classes->addClass(c); }
void ClassInfo::removeClasses() const { classes->removeClasses(); }
void ClassInfo::levelUpSelectedClass() const { classes->levelUpSelectedClass(); }
void ClassInfo::setHitDiceUsed(const QString& className, unsigned n) const { classes->setHitDiceUsed(className, n); }

QString ClassInfo::getCurrentClassName() const { return classes->getCurrentClassName(); }
