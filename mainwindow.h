#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "readsavefile.h"

QT_BEGIN_NAMESPACE
class QAction;
class QComboBox;
class QFontComboBox;
class QTextEdit;
class QTextCharFormat;
class QMenu;
class QActionGroup;
class QTextCodec;
QT_END_NAMESPACE


namespace Ui {

class MainWindow;

}

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* _ui;
    QActionGroup* _encodingGroup;

    FileOperator _edFile;

    void changeSelectionFormat(const QTextCharFormat& format);
    void textColorChanged(const QColor& c);
    void textBackgroundColorChanged(const QColor& c);
    void backgroundColorChanged(const QColor& c);

private slots:
    void setCurrentFileName(const QString& fileName);
    bool saveNeeded();
    bool load(const QString& f);
    void open();
    bool save();
    bool saveAs();
    void New();

    void setTextFont();
    void setTextColor();
    void setTextBackgroundColor();
    void setBackgroundColor();
    void setActionUTF_8();
    void setActioncp866();
    void setActionWin_1251();
    void setActionKOI_8R();
};

#endif // MAINWINDOW_H
