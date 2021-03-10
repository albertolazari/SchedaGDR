#ifndef STAT_H
#define STAT_H

#include <QBoxLayout>
#include <QLabel>

class Stat : public QFrame {
private:
    QString name;
    QLabel* nameLabel, *valueLabel;

protected:
    QVBoxLayout* mainLayout;

public:
    Stat(const QString& name, QWidget *parent = nullptr, int value = 0);

    void setValue(int) const;
};

#endif // STAT_H
