#include "HandFrame.h"

HandFrame::HandFrame(bool right, QWidget *parent):
    QFrame(parent),whichHand(right ? new QLabel ("Mano Destra",this) : new QLabel ("Mano Sinistra", this)),
    item (new QLabel("item prova",this)),use(new QPushButton("Usa",this)),
    drop(new QPushButton("Riponi",this)) {
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setLineWidth(2);

    whichHand->setFont(QFont("Helvetica", 8, QFont::Bold));

    QVBoxLayout* vlayout = new QVBoxLayout;

    vlayout->addWidget(whichHand);
    vlayout->addWidget(item);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(use);
    buttonLayout->addWidget(drop);
    vlayout->addLayout(buttonLayout);

    setLayout(vlayout);
}

void HandFrame::setItem(const QString &ItemName) const {
    item->setText(ItemName);
}

QPushButton *HandFrame::getUseButton() const { return use; }
QPushButton *HandFrame::getDropButton() const { return drop; }
