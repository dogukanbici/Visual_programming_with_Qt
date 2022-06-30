#include "balon.h"

balon::balon(QWidget *parrent):QPushButton(parrent)
{
    clickballon=false;
    connect(this,&QPushButton::clicked,this,&balon::tikla);
}

void balon::tikla()
{
    clickballon=!clickballon;
}
