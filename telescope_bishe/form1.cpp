#include "form1.h"
#include "ui_Telescope.h"
#include <QProcess>
#include <QString>
#include <QLineEdit>
#include "form1.moc"

class Form : public QWidget{

    Q_OBJECT

  public:
    explicit Form(QWidget *parent = nullptr){
        ui->setupUi(this);

        connect(ui->addball_button, &QPushButton::clicked,this,&Form::addball);
        connect(ui->deleteball_button, &QPushButton::clicked,this,&Form::deleteball);
        connect(ui->Star_database, &QPushButton::clicked,this,&Form::Star);
    }
    ~Form(){}

    private slots:
        void addball(){
            QString ballname = ui->addlineEdit_ballname->text();
            QString ball_RA = ui->addLineEdit_RA->text();
            QString ball_DEC = ui->addLineEdit_DEC->text();

            if(addballname.isEmpty() || addball_DEC.isEmpty() || addball_RA.isEmpty()){
                QMessageBox::warning(this, "输入不能为空","星球名称、RA、DEC不可为空");
                return;
            }
            QString ballinfo = ballname + ":" +ball_RA + "," + ball_DEC;
            ui->Star_database->addItem(ballinfo);


            ui->addlineEdit_ballname->clear();
            ui->addLineEdit_DEC->clear();
            ui->addLineEdit_RA->clear();
        }

    void deleteball(){
        QListWidgetItem *selectedItem = ui->Star_database->currentItem();
        if(selectedItem){
            delete selectedItem;
        }
    }

    void Star(){    //处理坐标显示
        QString ballinfo = item->text();
        QString parts = ballinfo.split(";");

        if(parts.size() == 2){
            QString coords = parts[1].split(",");
            if(coords.size() == 2){

                ui->SLineEdit_RA->setText(coords[0].trimmed());
                ui->SLineEdit_DEC->setText(coords[1].trimmed());
            }
        }
    }
    private:
        Ui::Form ui;
};

int main(int argc,char *argv[]){
    QApplication a(argc,argv);
    Form w;
    w.show();
    return a.exec();
}
