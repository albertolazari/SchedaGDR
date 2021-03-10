#include "Stat.h"
#include <string>

Stat::Stat(const QString &name, QWidget *parent, int value)
    : QFrame(parent),
    nameLabel(new QLabel(name)),
    valueLabel(new QLabel(QString::fromStdString(std::to_string(value)))),
    mainLayout(new QVBoxLayout) {
    mainLayout->setAlignment(Qt::AlignHCenter);
    mainLayout->setContentsMargins(0, 8, 0, 8);

    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setLineWidth(2);

    nameLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(nameLabel);

    valueLabel->setAlignment(Qt::AlignCenter);
    valueLabel->setFont(QFont("Helvetica", 11, QFont::Bold));
    mainLayout->addWidget(valueLabel);

    setLayout(mainLayout);
    setFixedSize(QSize(90, 80));
}

void Stat::setValue(int x) const {
    valueLabel->setText(QString::fromStdString(std::to_string(x)));
}
