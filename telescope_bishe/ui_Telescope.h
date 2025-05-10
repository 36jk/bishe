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
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_ChiW_2;
    QPushButton *Button_RA;
    QLineEdit *SLineEdit_RA;
    QHBoxLayout *horizontalLayout_ChiJ_2;
    QPushButton *Button_DEC;
    QLineEdit *SLineEdit_DEC;
    QListWidget *Star_database;
    QPushButton *addball_button;
    QPushButton *deleteball_button;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QPushButton *addballname;
    QLineEdit *addlineEdit_ballname;
    QHBoxLayout *horizontalLayout_ChiW_3;
    QPushButton *addball_RA;
    QLineEdit *addLineEdit_RA;
    QHBoxLayout *horizontalLayout_ChiJ_3;
    QPushButton *addball_DEC;
    QLineEdit *addLineEdit_DEC;
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
        verticalLayoutWidget_4 = new QWidget(home);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(210, 30, 361, 81));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_ChiW_2 = new QHBoxLayout();
        horizontalLayout_ChiW_2->setObjectName(QString::fromUtf8("horizontalLayout_ChiW_2"));
        Button_RA = new QPushButton(verticalLayoutWidget_4);
        Button_RA->setObjectName(QString::fromUtf8("Button_RA"));

        horizontalLayout_ChiW_2->addWidget(Button_RA);

        SLineEdit_RA = new QLineEdit(verticalLayoutWidget_4);
        SLineEdit_RA->setObjectName(QString::fromUtf8("SLineEdit_RA"));

        horizontalLayout_ChiW_2->addWidget(SLineEdit_RA);


        verticalLayout_4->addLayout(horizontalLayout_ChiW_2);

        horizontalLayout_ChiJ_2 = new QHBoxLayout();
        horizontalLayout_ChiJ_2->setObjectName(QString::fromUtf8("horizontalLayout_ChiJ_2"));
        Button_DEC = new QPushButton(verticalLayoutWidget_4);
        Button_DEC->setObjectName(QString::fromUtf8("Button_DEC"));

        horizontalLayout_ChiJ_2->addWidget(Button_DEC);

        SLineEdit_DEC = new QLineEdit(verticalLayoutWidget_4);
        SLineEdit_DEC->setObjectName(QString::fromUtf8("SLineEdit_DEC"));

        horizontalLayout_ChiJ_2->addWidget(SLineEdit_DEC);


        verticalLayout_4->addLayout(horizontalLayout_ChiJ_2);

        Star_database = new QListWidget(home);
        new QListWidgetItem(Star_database);
        new QListWidgetItem(Star_database);
        new QListWidgetItem(Star_database);
        new QListWidgetItem(Star_database);
        new QListWidgetItem(Star_database);
        Star_database->setObjectName(QString::fromUtf8("Star_database"));
        Star_database->setGeometry(QRect(30, 130, 291, 301));
        addball_button = new QPushButton(home);
        addball_button->setObjectName(QString::fromUtf8("addball_button"));
        addball_button->setGeometry(QRect(360, 340, 121, 41));
        deleteball_button = new QPushButton(home);
        deleteball_button->setObjectName(QString::fromUtf8("deleteball_button"));
        deleteball_button->setGeometry(QRect(550, 340, 121, 41));
        verticalLayoutWidget_5 = new QWidget(home);
        verticalLayoutWidget_5->setObjectName(QString::fromUtf8("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(360, 200, 361, 116));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        addballname = new QPushButton(verticalLayoutWidget_5);
        addballname->setObjectName(QString::fromUtf8("addballname"));

        horizontalLayout->addWidget(addballname);

        addlineEdit_ballname = new QLineEdit(verticalLayoutWidget_5);
        addlineEdit_ballname->setObjectName(QString::fromUtf8("addlineEdit_ballname"));

        horizontalLayout->addWidget(addlineEdit_ballname);


        verticalLayout_5->addLayout(horizontalLayout);

        horizontalLayout_ChiW_3 = new QHBoxLayout();
        horizontalLayout_ChiW_3->setObjectName(QString::fromUtf8("horizontalLayout_ChiW_3"));
        addball_RA = new QPushButton(verticalLayoutWidget_5);
        addball_RA->setObjectName(QString::fromUtf8("addball_RA"));

        horizontalLayout_ChiW_3->addWidget(addball_RA);

        addLineEdit_RA = new QLineEdit(verticalLayoutWidget_5);
        addLineEdit_RA->setObjectName(QString::fromUtf8("addLineEdit_RA"));

        horizontalLayout_ChiW_3->addWidget(addLineEdit_RA);


        verticalLayout_5->addLayout(horizontalLayout_ChiW_3);

        horizontalLayout_ChiJ_3 = new QHBoxLayout();
        horizontalLayout_ChiJ_3->setObjectName(QString::fromUtf8("horizontalLayout_ChiJ_3"));
        addball_DEC = new QPushButton(verticalLayoutWidget_5);
        addball_DEC->setObjectName(QString::fromUtf8("addball_DEC"));

        horizontalLayout_ChiJ_3->addWidget(addball_DEC);

        addLineEdit_DEC = new QLineEdit(verticalLayoutWidget_5);
        addLineEdit_DEC->setObjectName(QString::fromUtf8("addLineEdit_DEC"));

        horizontalLayout_ChiJ_3->addWidget(addLineEdit_DEC);


        verticalLayout_5->addLayout(horizontalLayout_ChiJ_3);

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
        Button_RA->setText(QApplication::translate("Form", "\350\265\244\347\272\254", nullptr));
        SLineEdit_RA->setText(QString());
        Button_DEC->setText(QApplication::translate("Form", "\350\265\244\347\273\217", nullptr));
        SLineEdit_DEC->setText(QString());

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

        addball_button->setText(QApplication::translate("Form", "\346\267\273\345\212\240", nullptr));
        deleteball_button->setText(QApplication::translate("Form", "\345\210\240\351\231\244", nullptr));
        addballname->setText(QApplication::translate("Form", "\346\230\237\344\275\223\345\220\215\347\247\260", nullptr));
        addball_RA->setText(QApplication::translate("Form", "\350\265\244\347\272\254", nullptr));
        addLineEdit_RA->setText(QString());
        addball_DEC->setText(QApplication::translate("Form", "\350\265\244\347\273\217", nullptr));
        addLineEdit_DEC->setText(QString());
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
