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

    connect(process, &QProcess::readyReadStandardOutput, this, [this]() {
        QString output = process->readAllStandardOutput();
        if (output.contains("listening on local domain", Qt::CaseInsensitive)) {
            ui->statu_Qlabel->setText("已连接");
        }
    });

    connect(process, &QProcess::readyReadStandardError, this, [this]() {
        QString errorOutput = process->readAllStandardError();
        if (!errorOutput.isEmpty()) {
            ui->statu_Qlabel->setText("连接失败");
            // QMessageBox::critical(this, "error", "Connect failed: " + errorOutput);
        }
    });

    process->start(command, arguments);
}

void Form::on_HButton_Server_clicked_dis() {
    process->kill();
    ui->statu_Qlabel->setText("断开连接");
}

void Form::on_GotoButton_clicked(){
    

}