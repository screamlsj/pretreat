#ifndef SYSFILE_H
#define SYSFILE_H

#include <QObject>

class sysfile : public QObject
{
    Q_OBJECT
public:
    explicit sysfile(QObject *parent = nullptr);
    QString load_sysparam(char* arg,...);
    void save_sysparam(char* arg,...);
    void create_sysfile(QString filename);

signals:

public slots:
};

#endif // SYSFILE_H
