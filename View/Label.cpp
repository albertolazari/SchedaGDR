#include "Label.h"

Label::Label(const QString &title, QWidget *parent, const QString &text)
    : QFrame(parent), titleLabel(new QLabel(title + ":")), textLabel(new QLabel(text)) {
    QHBoxLayout* layout = new QHBoxLayout;
    layout->setAlignment(Qt::AlignLeading);

    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setLineWidth(2);

    titleLabel->setFont(QFont("Helvetica", 10, QFont::Bold));

    layout->addWidget(titleLabel);
    layout->addWidget(textLabel);

    setLayout(layout);
}

QString Label::getText() const { return textLabel->text(); }
void Label::setText(const QString &t) const { textLabel->setText(t); }
