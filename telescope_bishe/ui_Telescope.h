/********************************************************************************
** Form generated from reading UI file 'Telescope.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TELESCOPE_H
#define UI_TELESCOPE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QTabWidget *SButton_JingD;
    QWidget *home;
    QPushButton *HButton_Server;
    QPushButton *HButton_Server_dis;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_ChiW_2;
    QPushButton *SButton_RA;
    QLineEdit *SLineEdit_RA;
    QHBoxLayout *horizontalLayout_ChiJ_2;
    QPushButton *SButton_DEC;
    QLineEdit *SLineEdit_DEC;
    QLabel *statu_Qlabel;
    QPushButton *GotoButton;
    QLabel *statu_RA_label;
    QLabel *statu_DEC_label;
    QListWidget *Star_database;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *record;
    QTextEdit *Record_TextEdit;
    QPushButton *Record_SelectPic;
    QPushButton *Record_Send;
    QLabel *Record_PicLabel;
    QPushButton *Record_Share;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(774, 534);
        SButton_JingD = new QTabWidget(Form);
        SButton_JingD->setObjectName(QString::fromUtf8("SButton_JingD"));
        SButton_JingD->setGeometry(QRect(0, 0, 1261, 671));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SButton_JingD->sizePolicy().hasHeightForWidth());
        SButton_JingD->setSizePolicy(sizePolicy);
        SButton_JingD->setTabPosition(QTabWidget::North);
        home = new QWidget();
        home->setObjectName(QString::fromUtf8("home"));
        HButton_Server = new QPushButton(home);
        HButton_Server->setObjectName(QString::fromUtf8("HButton_Server"));
        HButton_Server->setGeometry(QRect(190, 300, 221, 61));
        HButton_Server_dis = new QPushButton(home);
        HButton_Server_dis->setObjectName(QString::fromUtf8("HButton_Server_dis"));
        HButton_Server_dis->setGeometry(QRect(480, 300, 221, 61));
        verticalLayoutWidget_4 = new QWidget(home);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(290, 70, 361, 81));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_ChiW_2 = new QHBoxLayout();
        horizontalLayout_ChiW_2->setObjectName(QString::fromUtf8("horizontalLayout_ChiW_2"));
        SButton_RA = new QPushButton(verticalLayoutWidget_4);
        SButton_RA->setObjectName(QString::fromUtf8("SButton_RA"));

        horizontalLayout_ChiW_2->addWidget(SButton_RA);

        SLineEdit_RA = new QLineEdit(verticalLayoutWidget_4);
        SLineEdit_RA->setObjectName(QString::fromUtf8("SLineEdit_RA"));

        horizontalLayout_ChiW_2->addWidget(SLineEdit_RA);


        verticalLayout_4->addLayout(horizontalLayout_ChiW_2);

        horizontalLayout_ChiJ_2 = new QHBoxLayout();
        horizontalLayout_ChiJ_2->setObjectName(QString::fromUtf8("horizontalLayout_ChiJ_2"));
        SButton_DEC = new QPushButton(verticalLayoutWidget_4);
        SButton_DEC->setObjectName(QString::fromUtf8("SButton_DEC"));

        horizontalLayout_ChiJ_2->addWidget(SButton_DEC);

        SLineEdit_DEC = new QLineEdit(verticalLayoutWidget_4);
        SLineEdit_DEC->setObjectName(QString::fromUtf8("SLineEdit_DEC"));

        horizontalLayout_ChiJ_2->addWidget(SLineEdit_DEC);


        verticalLayout_4->addLayout(horizontalLayout_ChiJ_2);

        statu_Qlabel = new QLabel(home);
        statu_Qlabel->setObjectName(QString::fromUtf8("statu_Qlabel"));
        statu_Qlabel->setGeometry(QRect(420, 250, 51, 31));
        GotoButton = new QPushButton(home);
        GotoButton->setObjectName(QString::fromUtf8("GotoButton"));
        GotoButton->setGeometry(QRect(390, 190, 131, 41));
        statu_RA_label = new QLabel(home);
        statu_RA_label->setObjectName(QString::fromUtf8("statu_RA_label"));
        statu_RA_label->setGeometry(QRect(660, 70, 51, 31));
        statu_DEC_label = new QLabel(home);
        statu_DEC_label->setObjectName(QString::fromUtf8("statu_DEC_label"));
        statu_DEC_label->setGeometry(QRect(660, 120, 61, 31));
        Star_database = new QListWidget(home);
        new QListWidgetItem(Star_database);
        new QListWidgetItem(Star_database);
        new QListWidgetItem(Star_database);
        new QListWidgetItem(Star_database);
        new QListWidgetItem(Star_database);
        Star_database->setObjectName(QString::fromUtf8("Star_database"));
        Star_database->setGeometry(QRect(10, 10, 241, 261));
        scrollArea = new QScrollArea(home);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(60, 390, 641, 81));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 639, 79));
        scrollArea->setWidget(scrollAreaWidgetContents);
        SButton_JingD->addTab(home, QString());
        record = new QWidget();
        record->setObjectName(QString::fromUtf8("record"));
        Record_TextEdit = new QTextEdit(record);
        Record_TextEdit->setObjectName(QString::fromUtf8("Record_TextEdit"));
        Record_TextEdit->setGeometry(QRect(20, 20, 751, 131));
        Record_SelectPic = new QPushButton(record);
        Record_SelectPic->setObjectName(QString::fromUtf8("Record_SelectPic"));
        Record_SelectPic->setGeometry(QRect(280, 240, 111, 61));
        Record_Send = new QPushButton(record);
        Record_Send->setObjectName(QString::fromUtf8("Record_Send"));
        Record_Send->setGeometry(QRect(640, 240, 111, 61));
        Record_PicLabel = new QLabel(record);
        Record_PicLabel->setObjectName(QString::fromUtf8("Record_PicLabel"));
        Record_PicLabel->setGeometry(QRect(20, 200, 151, 111));
        Record_Share = new QPushButton(record);
        Record_Share->setObjectName(QString::fromUtf8("Record_Share"));
        Record_Share->setGeometry(QRect(470, 240, 111, 61));
        SButton_JingD->addTab(record, QString());

        retranslateUi(Form);

        SButton_JingD->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "\345\257\273\346\230\237\347\263\273\347\273\237", nullptr));
        HButton_Server->setText(QApplication::translate("Form", "\350\277\236\346\216\245Indi\346\234\215\345\212\241\345\231\250", nullptr));
        HButton_Server_dis->setText(QApplication::translate("Form", "\346\226\255\345\274\200Indi\346\234\215\345\212\241\345\231\250", nullptr));
        SButton_RA->setText(QApplication::translate("Form", "\350\256\276\347\275\256\350\265\244\347\272\254", nullptr));
        SLineEdit_RA->setText(QString());
        SButton_DEC->setText(QApplication::translate("Form", "\350\256\276\347\275\256\350\265\244\347\273\217", nullptr));
        SLineEdit_DEC->setText(QString());
        statu_Qlabel->setText(QApplication::translate("Form", "\346\234\252\350\277\236\346\216\245", nullptr));
        GotoButton->setText(QApplication::translate("Form", "GOTO", nullptr));
        statu_RA_label->setText(QApplication::translate("Form", "\346\234\252\350\256\276\347\275\256", nullptr));
        statu_DEC_label->setText(QApplication::translate("Form", "\346\234\252\350\256\276\347\275\256", nullptr));

        const bool __sortingEnabled = Star_database->isSortingEnabled();
        Star_database->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = Star_database->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("Form", "\346\234\210\347\220\203", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = Star_database->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("Form", "\345\234\237\346\230\237", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = Star_database->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("Form", "\346\234\250\346\230\237", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = Star_database->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("Form", "\347\201\253\346\230\237", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = Star_database->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("Form", "\345\214\227\346\236\201\346\230\237", nullptr));
        Star_database->setSortingEnabled(__sortingEnabled);

        SButton_JingD->setTabText(SButton_JingD->indexOf(home), QApplication::translate("Form", "\344\270\273\351\241\265", nullptr));
        Record_SelectPic->setText(QApplication::translate("Form", "\351\200\211\346\213\251\345\233\276\347\211\207", nullptr));
        Record_Send->setText(QApplication::translate("Form", "\344\277\235\345\255\230", nullptr));
        Record_PicLabel->setText(QApplication::translate("Form", "\345\233\276\347\211\207\345\234\250\350\277\231\351\207\214\346\230\276\347\244\272", nullptr));
        Record_Share->setText(QApplication::translate("Form", "\345\210\206\344\272\253", nullptr));
        SButton_JingD->setTabText(SButton_JingD->indexOf(record), QApplication::translate("Form", "\344\272\213\344\273\266\350\256\260\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TELESCOPE_H
