#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "ui_Telescope.h"
#include <QProcess>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_HButton_Server_clicked();
    void on_HButton_Server_clicked_dis();
    void on_GotoButton_clicked();
    void on_SButton_RA_clicked(); 
    void on_SButton_DEC_clicked(); 

private:
    Ui::Form *ui;
    QProcess *process;
};

#endif // FORM_H
