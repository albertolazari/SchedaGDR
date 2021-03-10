#ifndef HPMANAGER_H
#define HPMANAGER_H

#include <QFrame>
#include <QBoxLayout>
#include <QSpinBox>
#include <QPushButton>

class HpManager : public QFrame {
private:
    QSpinBox* input;
    QPushButton* heal, *takeDamage;

public:
    explicit HpManager(QWidget* parent = nullptr);

    QPushButton* getHealButton() const;
    QPushButton* getDamageButton() const;

    unsigned getValue() const;
};

#endif // HPMANAGER_H
