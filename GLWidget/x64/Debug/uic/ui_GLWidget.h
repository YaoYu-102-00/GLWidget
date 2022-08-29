/********************************************************************************
** Form generated from reading UI file 'GLWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLWIDGET_H
#define UI_GLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GLWidgetClass
{
public:

    void setupUi(QWidget *GLWidgetClass)
    {
        if (GLWidgetClass->objectName().isEmpty())
            GLWidgetClass->setObjectName(QString::fromUtf8("GLWidgetClass"));
        GLWidgetClass->resize(600, 400);

        retranslateUi(GLWidgetClass);

        QMetaObject::connectSlotsByName(GLWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *GLWidgetClass)
    {
        GLWidgetClass->setWindowTitle(QCoreApplication::translate("GLWidgetClass", "GLWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GLWidgetClass: public Ui_GLWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLWIDGET_H
