#ifndef READSAVEFILE_H
#define READSAVEFILE_H

#include <QString>
#include <QFile>
#include <QTextDocumentFragment>

class FileOperator
{
public:
    FileOperator();

    bool saveFile(const QTextDocument* fragment);
    QString loadFileTo(const QString& fName);
    bool exists(const QString& fName);
    QString getFileName();
    void setFileName(const QString& fName);
    bool setCodec(const QString& codecName);

    ~FileOperator();

private:
    QString _fileName;
    QFile _file;

public:
    QTextCodec* codec;
};

#endif // READSAVEFILE_H
