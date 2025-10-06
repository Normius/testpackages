#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>
#include <QComboBox>
#include <QDir>
#include <QStringList>
#include "startpage.h"
#include "installpage.h"

class PackageManager : public QWidget
{
    Q_OBJECT

public:
    PackageManager(QWidget *parent = nullptr);
    ~PackageManager();

private slots:
    void buttonPrevClicked();
    void buttonNextClicked();

private:
    // Страницы установщика
    enum class Pages {
        STARTPAGE,
        INSTALLPAGE
    };

    Pages currentPage; // Текущая страница

    QStackedWidget* stackWidgetPages;
    StartPage* startPage;
    InstallPage* installPage;

    QPushButton *buttonPrev;
    QPushButton *buttonNext;

    void setPage(const Pages page); // Установка новой страницы
};
#endif // PACKAGEMANAGER_H
