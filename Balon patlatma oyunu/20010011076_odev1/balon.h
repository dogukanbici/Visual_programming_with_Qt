#ifndef BALON_H
#define BALON_H

#include <QPushButton>

class balon : public QPushButton
{
    Q_OBJECT
public:
    balon(QWidget *parrent=0);
    bool clickballon;
public slots:
    void tikla();
};

#endif // BALON_H
