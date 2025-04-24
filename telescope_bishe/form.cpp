#include "form.h"
#include "ui_Telescope.h"
#include <QProcess>
#include <QMessageBox>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form),
    process(new QProcess(this))
{
    ui->setupUi(this);
    connect(ui->HButton_Server, &QPushButton::clicked, this, &Form::on_HButton_Server_clicked); 
    connect(ui->HButton_Server_dis, &QPushButton::clicked, this, &Form::on_HButton_Server_clicked_dis); 
}

Form::~Form()
{
    delete ui;
    delete process;
}

void Form::on_HButton_Server_clicked() {
    QString command = "indiserver";
    QStringList arguments;
    arguments << "-v" << "./indi_mycustomdriver";

    process->start(command, arguments);
    process->waitForFinished();

    QString output = process->readAllStandardOutput();
    QString errorOutput = process->readAllStandardError();

    if (output.contains("listening on local domain", Qt::CaseInsensitive)) {
        ui->statu_Qlabel->setText("已连接");
    } else {
        ui->statu_Qlabel->setText("连接失败");
        // QMessageBox::critical(this, "error", "Connect failed: " + errorOutput);
    }
}
void Form::on_HButton_Server_clicked_dis() {
    process->kill();
    ui->statu_Qlabel->setText("断开连接");
}

void Form::on_GotoButton_clicked(){
    

}