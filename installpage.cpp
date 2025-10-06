#include "installpage.h"
#include <QProcess>
#include <QTemporaryDir>
#include <QDebug>
#include <QMessageBox>

InstallPage::InstallPage(QWidget *parent)
    : QWidget{parent},
    packagesDir(":/packages"), // Директория ресурсов с пакетами
    fileExtensionFilter("*.deb") // Расширение пакетов
{
    labelChoosePackage = new QLabel("Выберите пакет для установки", this);
    comboBoxPackages = new QComboBox(this);

    labelChoosePackage->setGeometry(QRect(QPoint(50, 200), QSize(400, 100)));
    comboBoxPackages->setGeometry(QRect(QPoint(300, 230), QSize(400, 40)));

    // Добавление имеющихся в ресурсах пакетов в выпадающий список
    QStringList files = packagesDir.entryList(fileExtensionFilter, QDir::NoDotAndDotDot | QDir::Files);
    comboBoxPackages->addItems(files);
}

bool InstallPage::installPackage() {
    if (checkPackageForInstall()) {
        QMessageBox::information(this, "Информация", "Пакет уже установлен");
        qDebug() << "Пакет уже установлен";
        return true; // Если пакет уже установлен, прерываем установку
    }

    QProcess instalPackage;

    QString packageFullName = comboBoxPackages->currentText();
    QString resourcePackagePath = packagesDir.path() + "/" + packageFullName; // Путь к выбранному пакету в ресурсах

    // Создаём временную директорию и копируем выбранный пакет из ресурсов во временную директорию для установки
    QTemporaryDir tempDir;
    QString tempPackagePath;

    tempPackagePath = tempDir.path() + "/" + packageFullName;
    QFile::copy(resourcePackagePath, tempPackagePath);

    QStringList command;
    command << "sudo" << "dpkg" << "-i" << tempPackagePath;

    // Запускаем команду установки выбранного пакета с запросом пароля у пользователя
    instalPackage.start("pkexec", command);

    if (!instalPackage.waitForStarted(2000)) {
        qDebug() << "Не удалось запустить процесс";
        return false;
    }

    if (!instalPackage.waitForFinished(10000)) {
        qDebug() << "Процесс не завершился вовремя";
        return false;
    }

    switch (instalPackage.exitCode()) {
    case 126:  // Пользователь нажал "Отмена" при запросе пароля
        return false;
        break;
    case 127: // Пользователь ввёл неверный пароль
        return false;
        break;
    default:
        break;
    }

    qDebug() << "Ошибки:" << instalPackage.readAllStandardError();

    return true;
}

bool InstallPage::checkPackageForInstall() {
    QString packageFullName = comboBoxPackages->currentText();
    QString packageName = packageFullName.left(packageFullName.indexOf('_'));

    QProcess checkPackageForInstall;
    checkPackageForInstall.start("dpkg", QStringList() << "-s" << packageName);
    checkPackageForInstall.waitForFinished();

    if (checkPackageForInstall.exitCode() == 0) {
        return true;
    } else {
        return false;
    }
}
