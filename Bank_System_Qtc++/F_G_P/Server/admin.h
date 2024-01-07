#ifndef ADMIN_H
#define ADMIN_H

#include <QObject>

class Admin : public QObject
{
    Q_OBJECT
public:
    explicit Admin(QObject *parent = nullptr);

signals:

};

#endif // ADMIN_H
