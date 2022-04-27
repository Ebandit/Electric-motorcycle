#ifndef BATTERYVOLTAGES_H
#define BATTERYVOLTAGES_H

#include <QObject>

class Batteryvoltages : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList voltages READ voltages WRITE setVoltages NOTIFY voltagesChanged)

public:
    explicit Batteryvoltages(QObject *parent = 0);};

    QString voltages();
    void setVoltages(const QString &voltages);

signals:
void ledStateChanged();
public slots:

private:
QString m_ledstate;

};
#endif // CANCOMMANDS_H

