#ifndef HPINDICATOR_H
#define HPINDICATOR_H

#include <QFrame>
#include <QLabel>
#include <QBoxLayout>

class HpIndicator : public QFrame {
private:
    class IndicatorElement : public QWidget {
    private:
        QLabel* nameLabel, *valueLabel;

    public:
        IndicatorElement(const QString& name, QWidget* parent = nullptr, const QString& value = "0");

        void setValue(const QString&) const;
    };

    IndicatorElement* currentHp, *maxHp, *bonusHp;

public:
    explicit HpIndicator(QWidget* parent = nullptr);

    void setMaxHp(unsigned) const;
    void setCurrentHp(unsigned) const;
    void setBonusHp(unsigned) const;
};

#endif // HPINDICATOR_H
