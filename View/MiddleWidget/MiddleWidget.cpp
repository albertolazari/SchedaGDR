#include "MiddleWidget.h"

MiddleWidget::MiddleWidget(QWidget *parent)
    : QWidget(parent),
      rightHand(new HandFrame(true, this)),
      leftHand(new HandFrame(false, this)),
      hp(new HpManager(this)),
      rest(new QPushButton("Riposa", this)),
      classes(new ClassInfo(this)) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    QHBoxLayout* hLayout = new QHBoxLayout;
    mainLayout->addLayout(hLayout);

    hLayout->addWidget(hp);
    hLayout->addWidget(rest);

    mainLayout->addWidget(classes);

    QHBoxLayout* handlayout = new QHBoxLayout;
    handlayout->addWidget(leftHand);
    handlayout->addWidget(rightHand);
    mainLayout->addLayout(handlayout);

    QHBoxLayout* detailsLayout = new QHBoxLayout;
    mainLayout->addLayout(detailsLayout);

    leftHandDetails = new ItemDetails(this);
    QScrollArea* leftScrollArea = new QScrollArea(this);
    leftScrollArea->setWidget(leftHandDetails);
    leftScrollArea->setWidgetResizable(true);
    detailsLayout->addWidget(leftScrollArea);

    rightHandDetails = new ItemDetails(this);
    QScrollArea* rightScrollArea = new QScrollArea(this);
    rightScrollArea->setWidget(rightHandDetails);
    rightScrollArea->setWidgetResizable(true);
    detailsLayout->addWidget(rightScrollArea);
}

HpManager* MiddleWidget::getHpManager() const { return hp; }
QPushButton *MiddleWidget::getRestButton() const { return rest; }
ClassInfo *MiddleWidget::getClasses() const { return classes; }

void MiddleWidget::setRightHand(const Item *item) const {
    if(dynamic_cast<const Weapon*>(item)) rightHand->getUseButton()->setText("Attacca");
    else rightHand->getUseButton()->setText("Usa");

    if(item == nullptr)rightHand->setItem("nessun oggetto");
    else {
        rightHand->setItem(QString::fromStdString(item->getName()));
    }

    rightHandDetails->setItem(item);
}

void MiddleWidget::setLeftHand(const Item *item) const {
    if(dynamic_cast<const Weapon*>(item)) leftHand->getUseButton()->setText("Attacca");
    else leftHand->getUseButton()->setText("Usa");

    if(item == nullptr)leftHand->setItem("nessun oggetto");
    else {
        leftHand->setItem(QString::fromStdString(item->getName()));
    }

    leftHandDetails->setItem(item);
}

HandFrame *MiddleWidget::getRightHand() const{ return rightHand; }
HandFrame *MiddleWidget::getLeftHand() const { return leftHand; }
