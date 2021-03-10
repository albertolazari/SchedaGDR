#ifndef LABEL_H
#define LABEL_H

#include <QBoxLayout>
#include <QLabel>

class Label : public QFrame {
private:
    QLabel* titleLabel, *textLabel;

public:
    Label(const QString& title, QWidget *parent = nullptr, const QString& text = "");

    QString getText() const;
    void setText(const QString&) const;
};

#endif // LABEL_H
