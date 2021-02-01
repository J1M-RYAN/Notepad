#include "notepad.h"
#include "ui_notepad.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>
Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->plainTextEdit);
}

Notepad::~Notepad()
{
    delete ui;
}


void Notepad::on_actionNew_triggered()
{
    filePath="";
    ui->plainTextEdit->setPlainText("");
}

void Notepad::on_actionOpen_triggered()
{
  QString fileName=  QFileDialog::getOpenFileName(this, "Choose File",QDir::homePath());
  QFile file(fileName);
  if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this, "File Not Open", "Your file has not been opened");
        return;
  }
  QTextStream in(&file);
  QString text = in.readAll();
  ui->plainTextEdit->setPlainText(text);
  file.close();
}

void Notepad::on_actionSave_triggered()
{

    QFile file(filePath);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
          QMessageBox::warning(this, "File Not Open", "Your file has not been opened");
          return;
    }
    QTextStream out(&file);
    QString text = ui->plainTextEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void Notepad::on_actionSave_As_triggered()
{
    QString fileName=  QFileDialog::getSaveFileName(this, "Save File",QDir::homePath());
    QFile file(fileName);
    filePath=fileName;
    if(!file.open(QFile::WriteOnly|QFile::Text)){
          QMessageBox::warning(this, "File Not Open", "Your file has not been opened");
          return;
    }
    QTextStream out(&file);
    QString text = ui->plainTextEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void Notepad::on_actionCut_triggered()
{
    ui->plainTextEdit->cut();
}

void Notepad::on_actionCopy_triggered()
{
    ui->plainTextEdit->copy();
}

void Notepad::on_actionPaste_triggered()
{
    ui->plainTextEdit->paste();
}

void Notepad::on_actionRedo_triggered()
{
    ui->plainTextEdit->redo();
}

void Notepad::on_actionUndo_triggered()
{
    ui->plainTextEdit->undo();
}

void Notepad::on_actionExit_triggered()
{
    QApplication::quit();
}

void Notepad::on_actionAbout_Notepad_triggered()
{
    QMessageBox::about(this, "About Notepad", "This is a simple notepad app made in the Qt C++ framework");
}
