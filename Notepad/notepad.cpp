#include "notepad.h"
#include "ui_notepad.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>
#include <iostream>
#include <QInputDialog>

using namespace std;

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->plainTextEdit);
    ui->menubar->setStyleSheet("background-color: bisque");
    ui->statusbar->setStyleSheet("background-color: bisque");
    ui->toolBar->setStyleSheet("background-color: lightblue");
    ui->menuSettings->setIcon(QIcon(":/res/images/settings.svg"));
    auto toolbar = ui->toolBar;
    removeToolBar(toolbar);
    addToolBar(Qt::LeftToolBarArea, toolbar);
    toolbar->show();


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
  QString path = file.fileName();
  QString fileTitle = path.section("/",-1,-1);

  ui->statusbar->showMessage(fileTitle);
  file.close();
}

void Notepad::on_actionSave_triggered()
{
    if(filePath==""){
        Notepad::on_actionSave_As_triggered();
        return;
    }
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
    QString path = file.fileName();
    QString fileTitle = path.section("/",-1,-1);

    ui->statusbar->showMessage(fileTitle);
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

void Notepad::on_plainTextEdit_textChanged()
{
    QString statusBarText = "";
    if(filePath==""){

        ui->plainTextEdit->toPlainText()==""?statusBarText= "Welcome  to Notepad":statusBarText="*";
        ui->statusbar->showMessage(statusBarText);
        return;
    }
    QFile file(filePath);
    if(!file.open(QFile::ReadOnly|QFile::Text)){
          return;
    }
    QTextStream in(&file);
    QString textInFile = in.readAll();
    QString textInEditor = ui->plainTextEdit->toPlainText();
    QString path = file.fileName();
    statusBarText = path.section("/",-1,-1);
    if (textInFile!=textInEditor){
        statusBarText+= "*";
    }
    ui->statusbar->showMessage(statusBarText);

}




void Notepad::on_actionChange_Font_Size_triggered()
{
    int currentFontSize = ui->plainTextEdit->fontInfo().pointSize();
    QString family = ui->plainTextEdit->fontInfo().family();
    int chosenFontSize = QInputDialog::getInt(this, "Chose font size", "Chose font Size", currentFontSize,0,100 );
    QFont newFont(family,chosenFontSize);
    ui->plainTextEdit->setFont(newFont);
}
