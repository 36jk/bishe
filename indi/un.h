/********************************************************************************
** Form generated from reading UI file 'un.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UN_H
#define UN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QTabWidget *SButton_JingD;
    QWidget *home;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QDateTimeEdit *HEdit_DateTime;
    QPushButton *HButton_GetTimeData;
    QHBoxLayout *horizontalLayout_4;
    QTextEdit *HTime_textEdit;
    QComboBox *HTArea_comboBox;
    QPushButton *HButton_GetStarTime;
    QPushButton *HButton_Server;
    QWidget *control;
    QPushButton *CButton_North;
    QPushButton *CButton_West;
    QPushButton *CButton_East;
    QPushButton *CButton_Sorth;
    QPushButton *CButton_Stop;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *CButton_Ogz;
    QPushButton *CButton_Cgz;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *CButton_SetZero;
    QPushButton *CButton_Zero;
    QWidget *search;
    QToolBox *SelectBox;
    QWidget *page;
    QListWidget *Sun_Star_List;
    QWidget *page_2;
    QListWidget *Mark_Star;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_JingD;
    QPushButton *SButton_jingD;
    QLineEdit *SLineEdit_Jing_Du;
    QHBoxLayout *horizontalLayout_WeiD;
    QPushButton *SButton_WeiD;
    QLineEdit *SLineEdit_Wei_Du;
    QHBoxLayout *horizontalLayout_ChiW;
    QPushButton *SButton_ChiW;
    QLineEdit *SLineEdit_Chi_Wei;
    QHBoxLayout *horizontalLayout_ChiJ;
    QPushButton *SButton_ChiJ;
    QLineEdit *SLineEdit_Chi_Jing;
    QWidget *set;
    QWidget *record;
    QTextEdit *Record_TextEdit;
    QPushButton *Record_Select;
    QPushButton *Record_Enter;
    QLabel *Record_Label;
    QPushButton *Record_Share;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(627, 381);
        SButton_JingD = new QTabWidget(Form);
        SButton_JingD->setObjectName(QString::fromUtf8("SButton_JingD"));
        SButton_JingD->setGeometry(QRect(0, 0, 631, 381));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SButton_JingD->sizePolicy().hasHeightForWidth());
        SButton_JingD->setSizePolicy(sizePolicy);
        SButton_JingD->setTabPosition(QTabWidget::North);
        home = new QWidget();
        home->setObjectName(QString::fromUtf8("home"));
        verticalLayoutWidget_2 = new QWidget(home);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(20, 40, 581, 191));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        HEdit_DateTime = new QDateTimeEdit(verticalLayoutWidget_2);
        HEdit_DateTime->setObjectName(QString::fromUtf8("HEdit_DateTime"));

        horizontalLayout_3->addWidget(HEdit_DateTime);

        HButton_GetTimeData = new QPushButton(verticalLayoutWidget_2);
        HButton_GetTimeData->setObjectName(QString::fromUtf8("HButton_GetTimeData"));

        horizontalLayout_3->addWidget(HButton_GetTimeData);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        HTime_textEdit = new QTextEdit(verticalLayoutWidget_2);
        HTime_textEdit->setObjectName(QString::fromUtf8("HTime_textEdit"));

        horizontalLayout_4->addWidget(HTime_textEdit);

        HTArea_comboBox = new QComboBox(verticalLayoutWidget_2);
        HTArea_comboBox->addItem(QString());
        HTArea_comboBox->addItem(QString());
        HTArea_comboBox->setObjectName(QString::fromUtf8("HTArea_comboBox"));

        horizontalLayout_4->addWidget(HTArea_comboBox);

        HButton_GetStarTime = new QPushButton(verticalLayoutWidget_2);
        HButton_GetStarTime->setObjectName(QString::fromUtf8("HButton_GetStarTime"));

        horizontalLayout_4->addWidget(HButton_GetStarTime);

        horizontalLayout_4->setStretch(0, 12);
        horizontalLayout_4->setStretch(1, 2);
        horizontalLayout_4->setStretch(2, 2);

        verticalLayout->addLayout(horizontalLayout_4);

        verticalLayout->setStretch(1, 1);
        HButton_Server = new QPushButton(home);
        HButton_Server->setObjectName(QString::fromUtf8("HButton_Server"));
        HButton_Server->setGeometry(QRect(220, 260, 101, 31));
        SButton_JingD->addTab(home, QString());
        control = new QWidget();
        control->setObjectName(QString::fromUtf8("control"));
        CButton_North = new QPushButton(control);
        CButton_North->setObjectName(QString::fromUtf8("CButton_North"));
        CButton_North->setGeometry(QRect(390, 80, 61, 31));
        CButton_West = new QPushButton(control);
        CButton_West->setObjectName(QString::fromUtf8("CButton_West"));
        CButton_West->setGeometry(QRect(350, 110, 41, 41));
        CButton_East = new QPushButton(control);
        CButton_East->setObjectName(QString::fromUtf8("CButton_East"));
        CButton_East->setGeometry(QRect(450, 110, 41, 41));
        CButton_Sorth = new QPushButton(control);
        CButton_Sorth->setObjectName(QString::fromUtf8("CButton_Sorth"));
        CButton_Sorth->setGeometry(QRect(390, 150, 61, 31));
        CButton_Stop = new QPushButton(control);
        CButton_Stop->setObjectName(QString::fromUtf8("CButton_Stop"));
        CButton_Stop->setGeometry(QRect(390, 110, 61, 41));
        verticalLayoutWidget = new QWidget(control);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 80, 271, 141));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        CButton_Ogz = new QPushButton(verticalLayoutWidget);
        CButton_Ogz->setObjectName(QString::fromUtf8("CButton_Ogz"));

        horizontalLayout->addWidget(CButton_Ogz);

        CButton_Cgz = new QPushButton(verticalLayoutWidget);
        CButton_Cgz->setObjectName(QString::fromUtf8("CButton_Cgz"));

        horizontalLayout->addWidget(CButton_Cgz);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        CButton_SetZero = new QPushButton(verticalLayoutWidget);
        CButton_SetZero->setObjectName(QString::fromUtf8("CButton_SetZero"));

        horizontalLayout_2->addWidget(CButton_SetZero);

        CButton_Zero = new QPushButton(verticalLayoutWidget);
        CButton_Zero->setObjectName(QString::fromUtf8("CButton_Zero"));

        horizontalLayout_2->addWidget(CButton_Zero);


        verticalLayout_3->addLayout(horizontalLayout_2);

        SButton_JingD->addTab(control, QString());
        search = new QWidget();
        search->setObjectName(QString::fromUtf8("search"));
        SelectBox = new QToolBox(search);
        SelectBox->setObjectName(QString::fromUtf8("SelectBox"));
        SelectBox->setGeometry(QRect(350, 20, 241, 261));
        SelectBox->setFrameShape(QFrame::NoFrame);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(0, 0, 241, 209));
        Sun_Star_List = new QListWidget(page);
        new QListWidgetItem(Sun_Star_List);
        new QListWidgetItem(Sun_Star_List);
        new QListWidgetItem(Sun_Star_List);
        new QListWidgetItem(Sun_Star_List);
        Sun_Star_List->setObjectName(QString::fromUtf8("Sun_Star_List"));
        Sun_Star_List->setGeometry(QRect(0, 0, 241, 191));
        SelectBox->addItem(page, QString::fromUtf8("\345\244\252\351\230\263\347\263\273"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 100, 30));
        Mark_Star = new QListWidget(page_2);
        Mark_Star->setObjectName(QString::fromUtf8("Mark_Star"));
        Mark_Star->setGeometry(QRect(0, 0, 241, 191));
        SelectBox->addItem(page_2, QString::fromUtf8("\346\240\207\345\277\227\346\230\237\344\275\223"));
        verticalLayoutWidget_3 = new QWidget(search);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(10, 50, 321, 171));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_JingD = new QHBoxLayout();
        horizontalLayout_JingD->setObjectName(QString::fromUtf8("horizontalLayout_JingD"));
        SButton_jingD = new QPushButton(verticalLayoutWidget_3);
        SButton_jingD->setObjectName(QString::fromUtf8("SButton_jingD"));

        horizontalLayout_JingD->addWidget(SButton_jingD);

        SLineEdit_Jing_Du = new QLineEdit(verticalLayoutWidget_3);
        SLineEdit_Jing_Du->setObjectName(QString::fromUtf8("SLineEdit_Jing_Du"));

        horizontalLayout_JingD->addWidget(SLineEdit_Jing_Du);


        verticalLayout_2->addLayout(horizontalLayout_JingD);

        horizontalLayout_WeiD = new QHBoxLayout();
        horizontalLayout_WeiD->setObjectName(QString::fromUtf8("horizontalLayout_WeiD"));
        SButton_WeiD = new QPushButton(verticalLayoutWidget_3);
        SButton_WeiD->setObjectName(QString::fromUtf8("SButton_WeiD"));

        horizontalLayout_WeiD->addWidget(SButton_WeiD);

        SLineEdit_Wei_Du = new QLineEdit(verticalLayoutWidget_3);
        SLineEdit_Wei_Du->setObjectName(QString::fromUtf8("SLineEdit_Wei_Du"));

        horizontalLayout_WeiD->addWidget(SLineEdit_Wei_Du);


        verticalLayout_2->addLayout(horizontalLayout_WeiD);

        horizontalLayout_ChiW = new QHBoxLayout();
        horizontalLayout_ChiW->setObjectName(QString::fromUtf8("horizontalLayout_ChiW"));
        SButton_ChiW = new QPushButton(verticalLayoutWidget_3);
        SButton_ChiW->setObjectName(QString::fromUtf8("SButton_ChiW"));

        horizontalLayout_ChiW->addWidget(SButton_ChiW);

        SLineEdit_Chi_Wei = new QLineEdit(verticalLayoutWidget_3);
        SLineEdit_Chi_Wei->setObjectName(QString::fromUtf8("SLineEdit_Chi_Wei"));

        horizontalLayout_ChiW->addWidget(SLineEdit_Chi_Wei);


        verticalLayout_2->addLayout(horizontalLayout_ChiW);

        horizontalLayout_ChiJ = new QHBoxLayout();
        horizontalLayout_ChiJ->setObjectName(QString::fromUtf8("horizontalLayout_ChiJ"));
        SButton_ChiJ = new QPushButton(verticalLayoutWidget_3);
        SButton_ChiJ->setObjectName(QString::fromUtf8("SButton_ChiJ"));

        horizontalLayout_ChiJ->addWidget(SButton_ChiJ);

        SLineEdit_Chi_Jing = new QLineEdit(verticalLayoutWidget_3);
        SLineEdit_Chi_Jing->setObjectName(QString::fromUtf8("SLineEdit_Chi_Jing"));

        horizontalLayout_ChiJ->addWidget(SLineEdit_Chi_Jing);


        verticalLayout_2->addLayout(horizontalLayout_ChiJ);

        SButton_JingD->addTab(search, QString());
        set = new QWidget();
        set->setObjectName(QString::fromUtf8("set"));
        SButton_JingD->addTab(set, QString());
        record = new QWidget();
        record->setObjectName(QString::fromUtf8("record"));
        Record_TextEdit = new QTextEdit(record);
        Record_TextEdit->setObjectName(QString::fromUtf8("Record_TextEdit"));
        Record_TextEdit->setGeometry(QRect(10, 10, 601, 100));
        Record_Select = new QPushButton(record);
        Record_Select->setObjectName(QString::fromUtf8("Record_Select"));
        Record_Select->setGeometry(QRect(220, 120, 101, 61));
        Record_Enter = new QPushButton(record);
        Record_Enter->setObjectName(QString::fromUtf8("Record_Enter"));
        Record_Enter->setGeometry(QRect(330, 120, 101, 61));
        Record_Label = new QLabel(record);
        Record_Label->setObjectName(QString::fromUtf8("Record_Label"));
        Record_Label->setGeometry(QRect(10, 110, 181, 131));
        Record_Share = new QPushButton(record);
        Record_Share->setObjectName(QString::fromUtf8("Record_Share"));
        Record_Share->setGeometry(QRect(450, 120, 101, 61));
        SButton_JingD->addTab(record, QString());

        retranslateUi(Form);

        SButton_JingD->setCurrentIndex(0);
        SelectBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "\345\257\273\346\230\237\347\263\273\347\273\237", nullptr));
        HButton_GetTimeData->setText(QCoreApplication::translate("Form", "\350\216\267\345\217\226\347\263\273\347\273\237\346\227\266\351\227\264\345\222\214\346\227\245\346\234\237", nullptr));
        HTArea_comboBox->setItemText(0, QCoreApplication::translate("Form", "UTC +8", nullptr));
        HTArea_comboBox->setItemText(1, QCoreApplication::translate("Form", "UTC +0", nullptr));

        HButton_GetStarTime->setText(QCoreApplication::translate("Form", "\350\216\267\345\217\226\345\275\223\345\211\215\346\201\222\346\230\237\346\227\266", nullptr));
        HButton_Server->setText(QCoreApplication::translate("Form", "\350\277\236\346\216\245Indi\346\234\215\345\212\241\345\231\250", nullptr));
        SButton_JingD->setTabText(SButton_JingD->indexOf(home), QCoreApplication::translate("Form", "\344\270\273\351\241\265", nullptr));
        CButton_North->setText(QCoreApplication::translate("Form", "N", nullptr));
        CButton_North->setProperty("north", QVariant(QCoreApplication::translate("Form", "\345\214\227", nullptr)));
        CButton_West->setText(QCoreApplication::translate("Form", "W", nullptr));
        CButton_West->setProperty("west", QVariant(QCoreApplication::translate("Form", "\350\245\277", nullptr)));
        CButton_East->setText(QCoreApplication::translate("Form", "E", nullptr));
        CButton_East->setProperty("east", QVariant(QCoreApplication::translate("Form", "\344\270\234", nullptr)));
        CButton_Sorth->setText(QCoreApplication::translate("Form", "S", nullptr));
        CButton_Sorth->setProperty("sorth", QVariant(QCoreApplication::translate("Form", "\345\215\227", nullptr)));
        CButton_Stop->setText(QCoreApplication::translate("Form", "STOP", nullptr));
        CButton_Ogz->setText(QCoreApplication::translate("Form", "\346\211\223\345\274\200\350\267\237\350\270\252", nullptr));
        CButton_Cgz->setText(QCoreApplication::translate("Form", "\345\205\263\351\227\255\350\267\237\350\270\252", nullptr));
        CButton_SetZero->setText(QCoreApplication::translate("Form", "\350\256\276\347\275\256\345\275\222\351\233\266", nullptr));
        CButton_Zero->setText(QCoreApplication::translate("Form", "\345\275\222\351\233\266", nullptr));
        SButton_JingD->setTabText(SButton_JingD->indexOf(control), QCoreApplication::translate("Form", "\346\216\247\345\210\266", nullptr));

        const bool __sortingEnabled = Sun_Star_List->isSortingEnabled();
        Sun_Star_List->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = Sun_Star_List->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("Form", "\346\234\210\347\220\203", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = Sun_Star_List->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("Form", "\345\244\252\351\230\263", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = Sun_Star_List->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("Form", "\346\234\250\346\230\237", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = Sun_Star_List->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("Form", "\345\234\237\346\230\237", nullptr));
        Sun_Star_List->setSortingEnabled(__sortingEnabled);

        SelectBox->setItemText(SelectBox->indexOf(page), QCoreApplication::translate("Form", "\345\244\252\351\230\263\347\263\273", nullptr));
        SelectBox->setItemText(SelectBox->indexOf(page_2), QCoreApplication::translate("Form", "\346\240\207\345\277\227\346\230\237\344\275\223", nullptr));
        SButton_jingD->setText(QCoreApplication::translate("Form", "\347\273\217\345\272\246", nullptr));
        SLineEdit_Jing_Du->setText(QString());
        SButton_WeiD->setText(QCoreApplication::translate("Form", "\347\272\254\345\272\246", nullptr));
        SLineEdit_Wei_Du->setText(QString());
        SButton_ChiW->setText(QCoreApplication::translate("Form", "\350\265\244\347\272\254", nullptr));
        SLineEdit_Chi_Wei->setText(QString());
        SButton_ChiJ->setText(QCoreApplication::translate("Form", "\350\265\244\347\273\217", nullptr));
        SLineEdit_Chi_Jing->setText(QString());
        SButton_JingD->setTabText(SButton_JingD->indexOf(search), QCoreApplication::translate("Form", "\345\257\273\346\230\237", nullptr));
        SButton_JingD->setTabText(SButton_JingD->indexOf(set), QCoreApplication::translate("Form", "\350\256\276\347\275\256", nullptr));
        Record_Select->setText(QCoreApplication::translate("Form", "\351\200\211\346\213\251\345\233\276\347\211\207", nullptr));
        Record_Enter->setText(QCoreApplication::translate("Form", "\345\217\221\351\200\201", nullptr));
        Record_Label->setText(QCoreApplication::translate("Form", "\345\233\276\347\211\207\345\234\250\350\277\231\351\207\214\346\230\276\347\244\272", nullptr));
        Record_Share->setText(QCoreApplication::translate("Form", "\345\210\206\344\272\253", nullptr));
        SButton_JingD->setTabText(SButton_JingD->indexOf(record), QCoreApplication::translate("Form", "\344\272\213\344\273\266\350\256\260\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UN_H
