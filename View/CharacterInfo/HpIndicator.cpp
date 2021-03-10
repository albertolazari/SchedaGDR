#include "HpIndicator.h"
#include <string>

// HpIndicator::IndicatorElement
// ================================================================================================
HpIndicator::IndicatorElement::IndicatorElement(const QString&n, QWidget* parent, const QString& v)
    : QWidget(parent), nameLabel(new QLabel(n, this)), valueLabel(new QLabel(v, this)) {
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    nameLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(nameLabel);

    valueLabel->setAlignment(Qt::AlignCenter);
    valueLabel->setFont(QFont("Helvetica", 11, QFont::Bold));
    mainLayout->addWidget(valueLabel);
}

void HpIndicator::IndicatorElement::setValue(const QString& val) const { valueLabel->setText(val); }

// HpIndicator
// ================================================================================================
HpIndicator::HpIndicator(QWidget* parent)
    : QFrame(parent),
      // Current e max Hp sono 1 di default perché Character viene costruito con Hp 1/1
      currentHp(new IndicatorElement("Attuali", this, "1")),
      maxHp(new IndicatorElement("Massimi", this, "1")),
      bonusHp(new IndicatorElement("Temporanei", this, "-")) {
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setLineWidth(2);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
    setLayout(mainLayout);

    QLabel* name = new QLabel("Punti Ferita", this);
    name->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(name);

    QHBoxLayout* statsLayout = new QHBoxLayout;
    mainLayout->addLayout(statsLayout);

    statsLayout->addWidget(currentHp);

    IndicatorElement* separator = new IndicatorElement("", this, "/");
    statsLayout->addWidget(separator);

    statsLayout->addWidget(maxHp);
    statsLayout->addWidget(bonusHp);

    setMaximumHeight(80);
}

void HpIndicator::setMaxHp(unsigned x) const { maxHp->setValue(QString::fromStdString(std::to_string(x))); }

void HpIndicator::setCurrentHp(unsigned x) const { currentHp->setValue(QString::fromStdString(std::to_string(x))); }

void HpIndicator::setBonusHp(unsigned x) const {
    if (x == 0)
        bonusHp->setValue("-");
    else
        bonusHp->setValue(QString::fromStdString(std::to_string(x)));
}
