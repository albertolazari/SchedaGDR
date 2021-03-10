#include "ClassDetails.h"
#include <string>

ClassDetails::ClassDetails(const QString& n, unsigned d, QWidget* parent, unsigned l, unsigned used)
    : QWidget(parent),
      level(l),
      nameLabel(new Label("Classe", this, n)),
      levelLabel(new Label("Livello", this, QString::fromStdString(std::to_string(level)))),
      dieLabel(new Label("Dado Vita", this, QString::fromStdString("d" + std::to_string(d)))),
      hitDiceManager(new HitDiceManager(l, this, used)) {
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignTop);
    setLayout(mainLayout);

    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(levelLabel);
    mainLayout->addWidget(dieLabel);
    mainLayout->addWidget(hitDiceManager);
}

void ClassDetails::levelUp() {
    ++level;
    levelLabel->setText(QString::fromStdString(std::to_string(level)));
    hitDiceManager->addSlot();
}

void ClassDetails::setUsedHitDice(unsigned n) const { hitDiceManager->setUsedSlots(n); }

QString ClassDetails::getClassName() const { return nameLabel->getText(); }
QPushButton *ClassDetails::getThrowButton() const { return hitDiceManager->getThrowButton(); }
