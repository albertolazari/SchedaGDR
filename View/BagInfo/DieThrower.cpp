#include "DieThrower.h"

DieThrower::DieThrower(QWidget* parent)
    : QFrame(parent),
      mainLayout(new QVBoxLayout(this)),
      hLayout(new QHBoxLayout),
      selector(new QComboBox(this)) {
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setLineWidth(2);

    setLayout(mainLayout);

    QLabel* title = new QLabel("Tira un dado", this);
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);

    mainLayout->addLayout(hLayout);

    addSelector();

    button = new QPushButton("Tira", this);
    hLayout->addWidget(button);
}

QPushButton *DieThrower::getButton() const {
    return button;
}

void DieThrower::addSelector() const {
    hLayout->addWidget(selector);

    selector->addItem("d4");
    selector->addItem("d6");
    selector->addItem("d8");
    selector->addItem("d10");
    selector->addItem("d12");
    selector->addItem("d20");
    selector->addItem("d100");
}

Die DieThrower::getSelectedDie() const {
    unsigned dieFaces;
    switch (selector->currentIndex()) {
    case 0:
        dieFaces = 4;
        break;
    case 1:
        dieFaces = 6;
        break;
    case 2:
        dieFaces = 8;
        break;
    case 3:
        dieFaces = 10;
        break;
    case 4:
        dieFaces = 12;
        break;
    case 5:
        dieFaces = 20;
        break;
    case 6:
        dieFaces = 100;
        break;
    default:
        dieFaces = 20;
    }
    return Die(dieFaces);
}
