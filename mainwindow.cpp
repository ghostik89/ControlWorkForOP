#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "examplevalidator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->btn_save_student, SIGNAL(clicked()), this, SLOT(slt_save()));
    connect(ui->btn_save_first_student, SIGNAL(clicked()), this, SLOT(slt_save_first_student()));
    connect(ui->btn_save_second_student, SIGNAL(clicked()), this, SLOT(slt_save_second_student()));
    connect(ui->btn_first_student, SIGNAL(clicked()), this, SLOT(slt_show_first_student()));
    connect(ui->btn_second_student, SIGNAL(clicked()), this, SLOT(slt_show_second_student()));
    connect(ui->tab_one, SIGNAL(QTabWidget::currentChanged(int)), this, SLOT(slt_marks_tabs()));
    connect(ui->check_medal, SIGNAL(clicked(bool)),this, SLOT(slt_middle_marks(bool)));
    connect(ui->check_medal,SIGNAL(clicked(bool)), this, SLOT(slt_gold_medal_exam()));
    connect(ui->tab_marks, SIGNAL(QTabWidget::currentChanged(int)), this, SLOT(slt_check_unquie_exam()));

    ui->line_full_name->setValidator(&valid);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slt_save_first_student(){

}

void MainWindow::slt_medal_flag(bool){

}

void MainWindow::slt_show_first_student(){

}

void MainWindow::slt_save_second_student(){

}

void MainWindow::slt_show_second_student(){

}

void MainWindow::slt_marks_tabs(){
    bool medal = ui->check_medal->isChecked();
    bool best_first_exam = ui->spin_rus->value() >= 90 && ui->spin_math->value() >= 90 && ui->spin_phis->value() >= 90;
    if(medal && best_first_exam){
        ui->radio_rus_2->setEnabled(false);
        ui->radio_rus_3->setEnabled(false);
    }
}

void MainWindow::slt_middle_marks(bool gold_medal){
    if(gold_medal){
        ui->spin_middle_mark->setMinimum(4.6);
        ui->spin_middle_mark->setMaximum(5.0);
        ui->spin_middle_mark->setValue(4.6);
    }
    else{
        ui->spin_middle_mark->setMinimum(3.0);
        ui->spin_middle_mark->setMaximum(4.5);
        ui->spin_middle_mark->setValue(3.0);
    }
}

void MainWindow::slt_gold_medal_exam(bool gold_medal){
    bool best_first_exam = ui->spin_rus->value() >= 90 || ui->spin_math->value() >= 90 || ui->spin_phis->value() >= 90;
    if(gold_medal && best_first_exam){
        ui->tab_two->setEnabled(false);
        ui->tab_three->setEnabled(false);
    }
}

void MainWindow::slt_check_unquie_exam(){}
