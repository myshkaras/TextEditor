/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actNew;
    QAction *actionOpen;
    QAction *actionSave_2;
    QAction *actionSave_as;
    QAction *actOpen;
    QAction *actSave;
    QAction *actSaveAs;
    QAction *actTextFont;
    QAction *actTextColor;
    QAction *actTextStyle;
    QAction *actTextBackgroundColor;
    QAction *actBackgroundColor;
    QAction *actionList;
    QAction *actionUTF_8;
    QAction *actionWin_1251;
    QAction *actionKOI_8R;
    QAction *actionUTF_16;
    QAction *actionChange_Coding;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *teLines;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuStyle;
    QMenu *menuEncoding;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(605, 407);
        actNew = new QAction(MainWindow);
        actNew->setObjectName(QStringLiteral("actNew"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave_2 = new QAction(MainWindow);
        actionSave_2->setObjectName(QStringLiteral("actionSave_2"));
        actionSave_as = new QAction(MainWindow);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        actOpen = new QAction(MainWindow);
        actOpen->setObjectName(QStringLiteral("actOpen"));
        actSave = new QAction(MainWindow);
        actSave->setObjectName(QStringLiteral("actSave"));
        actSaveAs = new QAction(MainWindow);
        actSaveAs->setObjectName(QStringLiteral("actSaveAs"));
        actTextFont = new QAction(MainWindow);
        actTextFont->setObjectName(QStringLiteral("actTextFont"));
        actTextColor = new QAction(MainWindow);
        actTextColor->setObjectName(QStringLiteral("actTextColor"));
        actTextStyle = new QAction(MainWindow);
        actTextStyle->setObjectName(QStringLiteral("actTextStyle"));
        actTextBackgroundColor = new QAction(MainWindow);
        actTextBackgroundColor->setObjectName(QStringLiteral("actTextBackgroundColor"));
        actBackgroundColor = new QAction(MainWindow);
        actBackgroundColor->setObjectName(QStringLiteral("actBackgroundColor"));
        actionList = new QAction(MainWindow);
        actionList->setObjectName(QStringLiteral("actionList"));
        actionUTF_8 = new QAction(MainWindow);
        actionUTF_8->setObjectName(QStringLiteral("actionUTF_8"));
        actionWin_1251 = new QAction(MainWindow);
        actionWin_1251->setObjectName(QStringLiteral("actionWin_1251"));
        actionKOI_8R = new QAction(MainWindow);
        actionKOI_8R->setObjectName(QStringLiteral("actionKOI_8R"));
        actionUTF_16 = new QAction(MainWindow);
        actionUTF_16->setObjectName(QStringLiteral("actionUTF_16"));
        actionChange_Coding = new QAction(MainWindow);
        actionChange_Coding->setObjectName(QStringLiteral("actionChange_Coding"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        teLines = new QTextEdit(centralWidget);
        teLines->setObjectName(QStringLiteral("teLines"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(teLines->sizePolicy().hasHeightForWidth());
        teLines->setSizePolicy(sizePolicy);
        teLines->setLayoutDirection(Qt::LeftToRight);
        teLines->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        verticalLayout->addWidget(teLines);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 605, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuStyle = new QMenu(menuBar);
        menuStyle->setObjectName(QStringLiteral("menuStyle"));
        menuEncoding = new QMenu(menuBar);
        menuEncoding->setObjectName(QStringLiteral("menuEncoding"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuStyle->menuAction());
        menuBar->addAction(menuEncoding->menuAction());
        menuFile->addAction(actNew);
        menuFile->addSeparator();
        menuFile->addAction(actOpen);
        menuFile->addSeparator();
        menuFile->addAction(actSave);
        menuFile->addSeparator();
        menuFile->addAction(actSaveAs);
        menuFile->addSeparator();
        menuStyle->addAction(actTextFont);
        menuStyle->addSeparator();
        menuStyle->addAction(actTextColor);
        menuStyle->addSeparator();
        menuStyle->addAction(actTextBackgroundColor);
        menuStyle->addSeparator();
        menuStyle->addAction(actBackgroundColor);
        menuEncoding->addSeparator();
        menuEncoding->addAction(actionUTF_8);
        menuEncoding->addSeparator();
        menuEncoding->addAction(actionWin_1251);
        menuEncoding->addSeparator();
        menuEncoding->addAction(actionKOI_8R);
        menuEncoding->addSeparator();
        menuEncoding->addAction(actionUTF_16);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actNew->setText(QApplication::translate("MainWindow", "New", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
        actionSave_2->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
        actionSave_as->setText(QApplication::translate("MainWindow", "Save as", Q_NULLPTR));
        actOpen->setText(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
        actSave->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
        actSaveAs->setText(QApplication::translate("MainWindow", "Save as", Q_NULLPTR));
        actTextFont->setText(QApplication::translate("MainWindow", "Text font", Q_NULLPTR));
        actTextColor->setText(QApplication::translate("MainWindow", "Text color", Q_NULLPTR));
        actTextStyle->setText(QApplication::translate("MainWindow", "Text style", Q_NULLPTR));
        actTextBackgroundColor->setText(QApplication::translate("MainWindow", "Text background color", Q_NULLPTR));
        actBackgroundColor->setText(QApplication::translate("MainWindow", "Background color", Q_NULLPTR));
        actionList->setText(QApplication::translate("MainWindow", "Codecs List", Q_NULLPTR));
        actionUTF_8->setText(QApplication::translate("MainWindow", "UTF-8", Q_NULLPTR));
        actionWin_1251->setText(QApplication::translate("MainWindow", "Win-1251", Q_NULLPTR));
        actionKOI_8R->setText(QApplication::translate("MainWindow", "KOI-8R", Q_NULLPTR));
        actionUTF_16->setText(QApplication::translate("MainWindow", "CP866", Q_NULLPTR));
        actionChange_Coding->setText(QApplication::translate("MainWindow", "Change", Q_NULLPTR));
        teLines->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuStyle->setTitle(QApplication::translate("MainWindow", "Style", Q_NULLPTR));
        menuEncoding->setTitle(QApplication::translate("MainWindow", "Encoding", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
