#ifndef CANCOMMANDS_H
#define CANCOMMANDS_H

#include <QObject>

class Cancommads : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString ledstate READ ledstate WRITE setLedState NOTIFY ledStateChanged)


public:
    explicit Cancommads(QObject *parent = 0);
    QString ledstate();
    void setLedState(const QString &ledState);
signals:
    void ledStateChanged();
public slots:

private:
    QString m_ledstate;

};
#endif // CANCOMMANDS_H
