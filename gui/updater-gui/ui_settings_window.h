/********************************************************************************
** Form generated from reading UI file 'settings_window.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_WINDOW_H
#define UI_SETTINGS_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_Settings_window
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Settings_window)
    {
        if (Settings_window->objectName().isEmpty())
            Settings_window->setObjectName(QStringLiteral("Settings_window"));
        Settings_window->resize(400, 300);
        buttonBox = new QDialogButtonBox(Settings_window);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(Settings_window);
        QObject::connect(buttonBox, SIGNAL(accepted()), Settings_window, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Settings_window, SLOT(reject()));

        QMetaObject::connectSlotsByName(Settings_window);
    } // setupUi

    void retranslateUi(QDialog *Settings_window)
    {
        Settings_window->setWindowTitle(QApplication::translate("Settings_window", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class Settings_window: public Ui_Settings_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_WINDOW_H
