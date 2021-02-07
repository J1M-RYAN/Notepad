#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; }
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

    void on_actionExit_triggered();

    void on_actionAbout_Notepad_triggered();

    void on_plainTextEdit_textChanged();

    void on_actionChange_Font_Size_triggered();

    void on_tabWidget_currentChanged(int index);

    void setValue(int value);



private:
    Ui::Notepad *ui;
    QString filePath;
signals:
    void textChanged(int newText);

};
#endif // NOTEPAD_H
