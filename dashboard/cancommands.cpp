#include "cancommands.h"
#include <QDebug>
Cancommads::Cancommads(QObject *parent) :
    QObject(parent)
{
    m_ledstate = "0";
}

QString Cancommads::ledstate()
{
    return m_ledstate;
}

void Cancommads::setLedState(const QString &ledState)
{
    if(m_ledstate!=ledState)
    {
        m_ledstate=ledState;
        emit ledStateChanged();
        qDebug()<<"C++:state changed->"<<m_ledstate;
    }
}
