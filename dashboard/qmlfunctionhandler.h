#ifndef QMLFUNCTIONHANDLER_H
#define QMLFUNCTIONHANDLER_H

#include <QObject>

class QmlFunctionHandler : public QObject
{
    Q_OBJECT
public:
    QmlFunctionHandler(QObject *parent = 0);
};

#endif // QMLFUNCTIONHANDLER_H
