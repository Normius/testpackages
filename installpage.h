#ifndef INSTALLPAGE_H
#define INSTALLPAGE_H

#include <QComboBox>
#include <QDir>
#include <QLabel>
#include <QWidget>

class InstallPage : public QWidget
{
    Q_OBJECT
public:
    explicit InstallPage(QWidget *parent = nullptr);

    bool installPackage();
private:
    QLabel *labelChoosePackage;
    QComboBox *comboBoxPackages;

    QDir packagesDir;
    QStringList fileExtensionFilter;

    bool checkPackageForInstall();
signals:
};

#endif // INSTALLPAGE_H
