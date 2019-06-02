#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QColorDialog>
#include <QComboBox>
#include <QFontComboBox>
#include <QFontDialog>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontDatabase>
#include <QMenu>
#include <QMenuBar>
#include <QTextCodec>
#include <QTextEdit>
#include <QStatusBar>
#include <QToolBar>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QTextList>
#include <QtDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QMimeData>
#include <QListIterator>
#include <QActionGroup>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif
#include <QPrinter>
#if QT_CONFIG(printpreviewdialog)
#include <QPrintPreviewDialog>
#endif
#endif
#endif

const QString rsrcPath = ":/images";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){

    ui->setupUi(this);

    //connect this action to the slot open()
    connect(ui->actOpen, SIGNAL(triggered()), this, SLOT(Open()));
    connect(ui->actSave, SIGNAL(triggered()), this, SLOT(Save()));
    connect(ui->actSaveAs, SIGNAL(triggered()), this, SLOT(SaveAs()));
    connect(ui->actNew, SIGNAL(triggered()), this, SLOT(New()));
    connect(ui->actTextFont, SIGNAL(triggered()), this, SLOT(SetTextFont()));
    connect(ui->actTextColor, SIGNAL(triggered()), this, SLOT(SetTextColor()));
    connect(ui->actTextBackgroundColor, SIGNAL(triggered()), this, SLOT(SetTextBackgroundColor()));
    connect(ui->actBackgroundColor, SIGNAL(triggered()), this, SLOT(SetBackgroundColor()));
    connect(ui->actionList, SIGNAL(triggered()), this, SLOT(ListAvailableCodecs()));
    connect(ui->actionUTF_8, SIGNAL(triggered()), this, SLOT(SetActionUTF_8()));
    connect(ui->actionUTF_16, SIGNAL(triggered()), this, SLOT(SetActionUTF_16()));
    connect(ui->actionWin_1251, SIGNAL(triggered()), this, SLOT(SetActionWin_1251()));
    connect(ui->actionKOI_8R, SIGNAL(triggered()), this, SLOT(SetActionKOI_8R()));

    ui->actionUTF_8->setCheckable(true);
    ui->actionUTF_16->setCheckable(true);
    ui->actionWin_1251->setCheckable(true);
    ui->actionKOI_8R->setCheckable(true);

    EncodingGroup = new QActionGroup(this);
    EncodingGroup->addAction(ui->actionUTF_8);
    EncodingGroup->addAction(ui->actionUTF_16);
    EncodingGroup->addAction(ui->actionWin_1251);
    EncodingGroup->addAction(ui->actionKOI_8R);
    ui->actionUTF_8->setChecked(true);

    codec = QTextCodec::codecForName("UTF-8");

    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    ui->actTextColor->setIcon(pix);

    QPixmap bgpix(16, 16);
    bgpix.fill(Qt::white);
    ui->actBackgroundColor->setIcon(bgpix);

    ui->teLines->setWordWrapMode(QTextOption::NoWrap);

}

MainWindow::~MainWindow(){

    delete ui;

}

void MainWindow::SetCurrentFileName(const QString &fileName){

    this->fileName = fileName;
    ui->teLines->document()->setModified(false);

    QString shownName;
    if (fileName.isEmpty())
        shownName = "untitled.txt";
    else
        shownName = QFileInfo(fileName).fileName();

    setWindowTitle(tr("%1[*] - %2").arg(shownName, QCoreApplication::applicationName()));
    setWindowModified(false);

}

bool MainWindow::Load(const QString &f){

    if (!QFile::exists(f)){

        return false;

    }

    QFile file(f);

    if (!file.open(QFile::ReadOnly)){

        return false;

    }

    QTextStream stream (&file);
     stream.setCodec(codec);

     QString str =  stream.readAll();

     ui->teLines->setPlainText(str);

    SetCurrentFileName(f);

    return true;

}

void MainWindow::Open(){

    QFileDialog fileDialog(this, tr("Open File..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setNameFilter(tr("CPP(*.cpp *.h);;Text files (*.txt);;Python files (*.py)"));

    if (fileDialog.exec() != QDialog::Accepted){

        return;

    }
    const QString fn = fileDialog.selectedFiles().first();
    if (Load(fn)){

        statusBar()->showMessage(tr("File Opened \"%1\"").arg(QDir::toNativeSeparators(fn)));

    }else{

        statusBar()->showMessage(tr("Could Not Open File\"%1\"").arg(QDir::toNativeSeparators(fn)));

    }
}

bool MainWindow::Save(){

    if (fileName.isEmpty())
    {

        return SaveAs();

    }
    if (fileName.startsWith(QStringLiteral(":/")))
    {

        return SaveAs();

    }

    QTextDocumentWriter writer(fileName);
    writer.setCodec(codec);
    bool success = writer.write(ui->teLines->document());
    if (success) {

        ui->teLines->document()->setModified(false);
        statusBar()->showMessage(tr("File Saved \"%1\"").arg(QDir::toNativeSeparators(fileName)));

    } else {

        statusBar()->showMessage(tr("Could Not Save The File \"%1\"")
                                 .arg(QDir::toNativeSeparators(fileName)));

    }

    return success;

}

bool MainWindow::SaveAs(){

    QFileDialog fileDialog(this, tr("Save as..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setNameFilter(tr("CPP(*.cpp *.h);;Text files (*.txt);;Python files (*.py)"));
    fileDialog.setDefaultSuffix("txt");
    if (fileDialog.exec() != QDialog::Accepted)
        return false;
    const QString fn = fileDialog.selectedFiles().first();
    SetCurrentFileName(fn);

    return Save();

}


bool MainWindow::SaveNeeded(){

    if (!ui->teLines->document()->isModified()){

        return true;

    }

    const QMessageBox::StandardButton resBtn =
        QMessageBox::warning(this, QCoreApplication::applicationName(),
                             tr("The document was changed.\n"
                                "Do you want to save it?"),
                             QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if (resBtn == QMessageBox::Save)
    {

        return Save();

    }else
        if (resBtn == QMessageBox::Cancel){

            return false;
        }

    return true;

}



void MainWindow::New(){

    if (SaveNeeded()){

        ui->teLines->clear();
        SetCurrentFileName(QString());

    }

    statusBar()->showMessage(tr("New File Created"),2000);

}

void MainWindow::SetTextFont(){

    bool ok;
    QFont font = QFontDialog::getFont(
                    &ok, QFont("Courier 10 Pitch Regular", 10), this);

    QTextCharFormat fmt;
    fmt.setFont(font);
    ChangeSelectionFormat(fmt);

    statusBar()->showMessage(font.family(),2000);

}

void MainWindow::ChangeSelectionFormat(const QTextCharFormat &format){

    QTextCursor cursor = ui->teLines->textCursor();

    if (!cursor.hasSelection()){

        cursor.select(QTextCursor::WordUnderCursor);

    }
    cursor.mergeCharFormat(format);
    ui->teLines->mergeCurrentCharFormat(format);

}

void MainWindow::TextColorChanged(const QColor &c){

    QPixmap pix(16, 16);
    pix.fill(c);
    ui->actTextColor->setIcon(pix);

}

void MainWindow::SetTextColor(){

    QColor col = QColorDialog::getColor(ui->teLines->textColor(), this);
    if (!col.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setForeground(col);
    ChangeSelectionFormat(fmt);
    TextColorChanged(col);

    statusBar()->showMessage(tr("Text Color changed"),2000);

}

void MainWindow::TextBackgroundColorChanged(const QColor &c)
{
    QPixmap pix(16, 16);
    pix.fill(c);
    ui->actTextBackgroundColor->setIcon(pix);
}

void MainWindow::SetTextBackgroundColor(){

    QColor col = QColorDialog::getColor(ui->teLines->textColor(), this);
    if (!col.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setBackground(col);
    ChangeSelectionFormat(fmt);
    TextBackgroundColorChanged(col);

    statusBar()->showMessage(tr("Text Background Color changed"),2000);

}

void MainWindow::BackgroundColorChanged(const QColor &c){

    QPixmap pix(16, 16);
    pix.fill(c);
    ui->actBackgroundColor->setIcon(pix);

}

void MainWindow::SetBackgroundColor(){

    QColor col = QColorDialog::getColor(ui->teLines->textColor(), this);
    if (!col.isValid()){

        return;

    }

    QPalette p = ui->teLines->palette();
    p.setColor(QPalette::Base, col);
    ui->teLines->setPalette(p);
    BackgroundColorChanged(col);

    statusBar()->showMessage(tr("Background Color changed"),2000);

}

void MainWindow::ListAvailableCodecs(){

    QList<QByteArray>  QL=QTextCodec::availableCodecs();
    QListIterator<QByteArray> i(QL);
    while (i.hasNext())
    ui->teLines->append(i.next());

}

void MainWindow::SetActionUTF_8(){

    codec = QTextCodec::codecForName("UTF-8");

}

void MainWindow::SetActionUTF_16(){

    codec = QTextCodec::codecForName("UTF-16");

}

void MainWindow::SetActionWin_1251(){

    codec = QTextCodec::codecForName("windows-1251");

}

void MainWindow::SetActionKOI_8R(){

    codec = QTextCodec::codecForName("KOI8-R");

}


