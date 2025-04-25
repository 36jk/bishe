#ifndef FORM1_H
#define FORM1_H

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

private:
    Ui::Form *ui;
    QProcess *process;
};

#endif // FORM_H
