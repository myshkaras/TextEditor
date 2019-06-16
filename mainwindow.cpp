#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "readsavefile.h"

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

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    //connect this action to the slot
    connect(_ui->actOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(_ui->actSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(_ui->actSaveAs, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(_ui->actNew, SIGNAL(triggered()), this, SLOT(New()));
    connect(_ui->actTextFont, SIGNAL(triggered()), this, SLOT(setTextFont()));
    connect(_ui->actTextColor, SIGNAL(triggered()), this, SLOT(setTextColor()));
    connect(_ui->actTextBackgroundColor, SIGNAL(triggered()), this, SLOT(setTextBackgroundColor()));
    connect(_ui->actBackgroundColor, SIGNAL(triggered()), this, SLOT(setBackgroundColor()));
    connect(_ui->actionUTF_8, SIGNAL(triggered()), this, SLOT(setActionUTF_8()));
    connect(_ui->actionUTF_16, SIGNAL(triggered()), this, SLOT(setActioncp866()));
    connect(_ui->actionWin_1251, SIGNAL(triggered()), this, SLOT(setActionWin_1251()));
    connect(_ui->actionKOI_8R, SIGNAL(triggered()), this, SLOT(setActionKOI_8R()));

    _ui->actionUTF_8->setCheckable(true);
    _ui->actionUTF_16->setCheckable(true);
    _ui->actionWin_1251->setCheckable(true);
    _ui->actionKOI_8R->setCheckable(true);

    _encodingGroup = new QActionGroup(this);
    _encodingGroup->addAction(_ui->actionUTF_8);
    _encodingGroup->addAction(_ui->actionUTF_16);
    _encodingGroup->addAction(_ui->actionWin_1251);
    _encodingGroup->addAction(_ui->actionKOI_8R);
    _ui->actionUTF_8->setChecked(true);

    _edFile.setCodec("UTF-8");

    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    _ui->actTextColor->setIcon(pix);

    QPixmap bgpix(16, 16);
    bgpix.fill(Qt::white);
    _ui->actBackgroundColor->setIcon(bgpix);

    _ui->teLines->setWordWrapMode(QTextOption::NoWrap);

}

MainWindow::~MainWindow()
{
    if (_encodingGroup!=nullptr)
    {
        delete _encodingGroup;
    }
    if (_ui!=nullptr)
    {
        delete _ui;
    }
}

void MainWindow::setCurrentFileName(const QString &fileName)
{
    _ui->teLines->document()->setModified(false);

    QString shownName;
    if (fileName.isEmpty())
    {
        shownName = "untitled.txt";    
        _edFile.setFileName(shownName);
    }else
    {
        shownName = QFileInfo(fileName).fileName();
        _edFile.setFileName(fileName);
    }

    setWindowTitle(tr("%1[*] - %2").arg(shownName, QCoreApplication::applicationName()));
    setWindowModified(false);
}

bool MainWindow::load(const QString &f)
{
    if (_edFile.exists(f))
    {
        setCurrentFileName(f);
        _ui->teLines->setPlainText(_edFile.loadFileTo(f));

        return true;
    }else
    {
        return false;
    }
}

void MainWindow::open()
{
    QFileDialog fileDialog(this, tr("Open File..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setNameFilter(tr("CPP(*.cpp *.h);;Text files (*.txt);;Python files (*.py)"));

    if (fileDialog.exec() != QDialog::Accepted)
    {
        return;
    }

    const QString fn = fileDialog.selectedFiles().first();

    if (load(fn))
    {
        statusBar()->showMessage(tr("File Opened \"%1\"").arg(QDir::toNativeSeparators(fn)));
    }else
    {
        statusBar()->showMessage(tr("Could Not Open File\"%1\"").arg(QDir::toNativeSeparators(fn)));
    }
}

bool MainWindow::save()
{
    if (_edFile.getFileName().isEmpty())
    {
        return saveAs();
    }

    if (_edFile.getFileName().startsWith(QStringLiteral(":/")))
    {
        return saveAs();
    }

    bool success = _edFile.saveFile(_ui->teLines->document());

    if (success)
    {
        _ui->teLines->document()->setModified(false);
        statusBar()->showMessage(tr("File Saved \"%1\"").arg(QDir::toNativeSeparators(_edFile.getFileName())));
    } else
    {
        statusBar()->showMessage(tr("Could Not Save The File \"%1\"")
                                 .arg(QDir::toNativeSeparators(_edFile.getFileName())));
    }

    return success;
}

bool MainWindow::saveAs()
{
    QFileDialog fileDialog(this, tr("Save as..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setNameFilter(tr("CPP(*.cpp *.h);;Text files (*.txt);;Python files (*.py)"));
    fileDialog.setDefaultSuffix("txt");
    if (fileDialog.exec() != QDialog::Accepted)
    {
        return false;
    }
    const QString fn = fileDialog.selectedFiles().first();
    setCurrentFileName(fn);

    return save();
}


bool MainWindow::saveNeeded()
{
    if (!_ui->teLines->document()->isModified())
    {
        return true;
    }

    const QMessageBox::StandardButton resBtn =
        QMessageBox::warning(this, QCoreApplication::applicationName(),tr("The document was changed.\n"
                        "Do you want to save it?"),QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    if (resBtn == QMessageBox::Save)
    {
        return save();
    }else
    {
        if (resBtn == QMessageBox::Cancel)
        {
            return false;
        }
    }

    return true;
}

void MainWindow::New()
{
    if (saveNeeded())
    {
        _ui->teLines->clear();
        setCurrentFileName(QString());
    }

    statusBar()->showMessage(tr("New File Created"),2000);
}

void MainWindow::setTextFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Courier 10 Pitch Regular", 10), this);
    QTextCharFormat fmt;
    fmt.setFont(font);
    changeSelectionFormat(fmt);
    statusBar()->showMessage(font.family(),2000);
}

void MainWindow::changeSelectionFormat(const QTextCharFormat &format)
{
    QTextCursor cursor = _ui->teLines->textCursor();

    if (!cursor.hasSelection())
    {
        cursor.select(QTextCursor::WordUnderCursor);
    }

    cursor.mergeCharFormat(format);
    _ui->teLines->mergeCurrentCharFormat(format);
}

void MainWindow::textColorChanged(const QColor &c)
{
    QPixmap pix(16, 16);
    pix.fill(c);
    _ui->actTextColor->setIcon(pix);
}

void MainWindow::setTextColor()
{
    QColor col = QColorDialog::getColor(_ui->teLines->textColor(), this);
    if (!col.isValid())
    {
        return;
    }

    QTextCharFormat fmt;
    fmt.setForeground(col);
    changeSelectionFormat(fmt);
    textColorChanged(col);

    statusBar()->showMessage(tr("Text Color changed"),2000);
}

void MainWindow::textBackgroundColorChanged(const QColor &c)
{
    QPixmap pix(16, 16);
    pix.fill(c);
    _ui->actTextBackgroundColor->setIcon(pix);
}

void MainWindow::setTextBackgroundColor(){

    QColor col = QColorDialog::getColor(_ui->teLines->textColor(), this);
    if (!col.isValid())
    {
        return;
    }

    QTextCharFormat fmt;
    fmt.setBackground(col);
    changeSelectionFormat(fmt);
    textBackgroundColorChanged(col);

    statusBar()->showMessage(tr("Text Background Color changed"),2000);
}

void MainWindow::backgroundColorChanged(const QColor &c)
{
    QPixmap pix(16, 16);
    pix.fill(c);
    _ui->actBackgroundColor->setIcon(pix);
}

void MainWindow::setBackgroundColor()
{
    QColor col = QColorDialog::getColor(_ui->teLines->textColor(), this);
    if (!col.isValid())
    {
        return;
    }

    QPalette p = _ui->teLines->palette();
    p.setColor(QPalette::Base, col);
    _ui->teLines->setPalette(p);
    backgroundColorChanged(col);

    statusBar()->showMessage(tr("Background Color changed"),2000);
}

void MainWindow::setActionUTF_8()
{
    _edFile.setCodec("UTF-8");
}

void MainWindow::setActioncp866()
{
    _edFile.setCodec("cp866");
}

void MainWindow::setActionWin_1251()
{
    _edFile.setCodec("windows-1251");
}

void MainWindow::setActionKOI_8R()
{
    _edFile.setCodec("KOI8-R");
}


