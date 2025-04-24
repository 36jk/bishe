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
    connect(ui->GotoButton, &QPushButton::clicked, this, &Form::on_GotoButton_clicked);

    // 解析标准输出中的 LOG_INFO 信息
    connect(process, &QProcess::readyReadStandardOutput, this, [this]() {
        QString output = process->readAllStandardOutput();
        if (output.contains("listening on local domain", Qt::CaseInsensitive)) {
            ui->statu_Qlabel->setText("已连接");
        } else if (output.contains("LOG_INFO", Qt::CaseInsensitive)) {
            // 提取 LOG_INFO 的内容
            QString logInfo = output.mid(output.indexOf("LOG_INFO") + 9).trimmed();
            ui->statu_Qlabel->setText(logInfo); // 更新状态标签
        }
    });

    connect(process, &QProcess::readyReadStandardError, this, [this]() {
        QString errorOutput = process->readAllStandardError();
        if (!errorOutput.isEmpty()) {
            ui->statu_Qlabel->setText("连接失败");
        }
    });
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
        } else if (output.contains("LOG_INFO", Qt::CaseInsensitive)) {
            // 提取 LOG_INFO 的内容
            QString logInfo = output.mid(output.indexOf("LOG_INFO") + 9).trimmed();
            ui->statu_Qlabel->setText(logInfo); // 更新状态标签
        }
    });

    connect(process, &QProcess::readyReadStandardError, this, [this]() {
        QString errorOutput = process->readAllStandardError();
        if (!errorOutput.isEmpty()) {
            ui->statu_Qlabel->setText("连接失败");
        }
    });

    process->start(command, arguments);
}

void Form::on_HButton_Server_clicked_dis() {
    process->kill();
    ui->statu_Qlabel->setText("断开连接");
}

void Form::on_GotoButton_clicked() {
    // 获取用户输入的目标 RA 和 DEC
    double targetRA = ui->raInput->text().toDouble();
    double targetDEC = ui->decInput->text().toDouble();

    // 构造 GOTO 命令
    QString command = QString("GOTO %1 %2").arg(targetRA).arg(targetDEC);

    // 发送命令到驱动
    if (process->state() == QProcess::Running) {
        process->write(command.toUtf8() + "\n");
        ui->statu_Qlabel->setText("正在移动到目标位置...");
    } else {
        QMessageBox::warning(this, "错误", "驱动未启动，无法发送 GOTO 命令！");
    }
}