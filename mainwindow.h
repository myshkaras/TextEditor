#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QComboBox;
class QFontComboBox;
class QTextEdit;
class QTextCharFormat;
class QMenu;
QT_END_NAMESPACE


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

//    QComboBox *comboStyle;
//    QFontComboBox *comboFont;
//    QComboBox *comboSize;

    QToolBar *tb;
    QString fileName;

    void ChangeSelectionFormat(const QTextCharFormat &format);
    void FontChanged(const QFont &f);
    void TextColorChanged(const QColor &c);
    void TextBackgroundColorChanged(const QColor &c);
    void BackgroundColorChanged(const QColor &c);

private slots:
    void SetCurrentFileName(const QString &fileName);
    bool SaveNeeded();
    bool Load(const QString &f);
    void Open();
    bool Save();
    bool SaveAs();
    void New();
    void SetTextFont();
    void SetTextColor();
    void SetTextBackgroundColor();
    void SetBackgroundColor();
};

#endif // MAINWINDOW_H
