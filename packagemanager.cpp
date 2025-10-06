#include "packagemanager.h"

#include <QDebug>
#include <QProcess>
#include <QTemporaryDir>
#include <QMessageBox>

PackageManager::PackageManager(QWidget *parent)
    : QWidget(parent) {

    stackWidgetPages = new QStackedWidget(this);

    startPage = new StartPage(this);
    installPage = new InstallPage(this);

    stackWidgetPages->addWidget(startPage);
    stackWidgetPages->addWidget(installPage);

    setPage(Pages::STARTPAGE);
    stackWidgetPages->setGeometry(0, 0, 800, 600);

    buttonPrev = new QPushButton("Назад", this);
    buttonPrev->hide();
    buttonNext = new QPushButton("Далее", this);

    buttonPrev->setGeometry(QRect(QPoint(20, 530), QSize(200, 50)));
    buttonNext->setGeometry(QRect(QPoint(580, 530), QSize(200, 50)));

    connect(buttonPrev, &QPushButton::clicked, this, &PackageManager::buttonPrevClicked);
    connect(buttonNext, &QPushButton::clicked, this, &PackageManager::buttonNextClicked);
}

void PackageManager::buttonPrevClicked() {
    switch (currentPage) {
    case Pages::INSTALLPAGE:
        setPage(Pages::STARTPAGE);
        break;
    default:
        break;
    }
}

void PackageManager::buttonNextClicked() {
    switch (currentPage) {
    case Pages::STARTPAGE:
        setPage(Pages::INSTALLPAGE);
        break;
    case Pages::INSTALLPAGE: {
        bool result = installPage->installPackage();
        if (result) {
            qDebug() << "Пакет установлен";
            QMessageBox::information(this, " Информация", "Пакет установлен");
        }
        else {
            qDebug() << "Пакет не установлен";
            QMessageBox::information(this, " Информация", "Пакет не установлен");
        }
    }
        break;
    default:
        break;
    }
}

void PackageManager::setPage(const Pages page) {
    switch (page) {
    case Pages::INSTALLPAGE:
        if (currentPage == page) {
            return;
        }
        buttonPrev->show();
        buttonNext->setText("Установить");
        stackWidgetPages->setCurrentWidget(installPage);
        currentPage = page;
        break;
    case Pages::STARTPAGE:
        if (currentPage == page) {
            return;
        }
        buttonPrev->hide();
        buttonNext->setText("Далее");
        stackWidgetPages->setCurrentWidget(startPage);
        currentPage = page;
        break;
    default:
        break;
    }
}

PackageManager::~PackageManager() {}
