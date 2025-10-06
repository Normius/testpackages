#include "startpage.h"

StartPage::StartPage(QWidget *parent)
    : QWidget{parent} {
    labelCandidateName = new QLabel("Акимов", this);
    labelCandidateName->setGeometry(QRect(QPoint(350, 50), QSize(400, 100)));
}
