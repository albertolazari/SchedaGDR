#ifndef HANDFRAME_H
#define HANDFRAME_H

#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>

class HandFrame: public QFrame {
    Q_OBJECT
private:
    QLabel* whichHand;
    QLabel* item;
    QPushButton* use;
    QPushButton* drop;

public:
    explicit HandFrame(bool right = true, QWidget *parent = nullptr);

    void setItem (const QString& ItemName) const;
    QPushButton* getUseButton () const;
    QPushButton* getDropButton () const;
};

#endif // HANDFRAME_H
