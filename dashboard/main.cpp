#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include "speedometer.h"
#include "batterygauge.h"
#include <unistd.h>
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>
#include <iostream>
#include <canframeid.h>
#include <QTimer>
#include <QRandomGenerator>
#include <QDebug>
#include <QQmlProperty>
#include <qmlfunctionhandler.h>
#include <cancommands.h>


using namespace std;

// Global.
QCanBusDevice *device;
QObject *object;
QObject *speedoMeter;
QObject *engineTemp;
QObject *motorTemp;
QObject *batteryVoltage;
QObject *wattagePerKmObject;
QObject *batteryAmperage;
QObject *highestCellTemperature;
QObject *lowestCellVoltage;
QObject *rightColor;
QObject *leftColor;
QObject *headlightColor;
QObject *headlightImage;
QObject *batteryPower;

int speed;

Speedometer *ptrSpeedometer;
Batterygauge *ptrBatteryGauge;
Cancommads *ptrCanCommands;

void setSpeedometerColor(int speed)
{
    if(speed < 60) {
        ptrSpeedometer->setProperty("speedColor", QColor(255,0,0));
    } else {
        ptrSpeedometer->setProperty("speedColor", QColor(128,255,0));
    }
}

void handleFirstControllerInfo(const QCanBusFrame &frame)
{
    const QByteArray payload = frame.payload();
    const int highRpm = payload[0];
    const int lowRpm = payload[1];
    const int motorTempemperature = payload[2];
    const int controllerTemperature = payload[3];
    const int capHigh = payload[4];
    const int capLow = payload[5];

    int current = (short)(((capHigh) & 0xFF) << 8 | (capLow) & 0xFF);
    int motorRpm = (short)(((highRpm) & 0xFF) << 8 | (lowRpm) & 0xFF);

   // qDebug() << QString("RPM: %1").arg((motorRpm));


    speed = (motorRpm / 4) * 2 * 60 / 1000;

    engineTemp->setProperty("text", QString("%1°")
                            .arg(motorTempemperature));

    ptrSpeedometer->setProperty("speed", speed);
}


void sendCanCommands()
{

    QString ledString = ptrCanCommands->ledstate();
    int ledState = ledString.toInt();

    QCanBusFrame frame;
    frame.setFrameId(0x651);
    QByteArray payload;
    payload[0]=ledState;
    payload[1]=0x00;
    payload[2]=0x00;
    payload[3]=0x00;
    payload[4]=0x00;
    payload[5]=0x00;
    payload[6]=0x00;
    payload[7]=0x00;

    frame.setPayload(payload);

    //device->waitForFramesWritten(10);
    device->writeFrame(frame);
}

void handleFirstBmsInfo(const QCanBusFrame &frame)
{
    const QByteArray payload = frame.payload();
    const int lowestCellVoltageHighByte = payload[0];
    const int lowestCellVoltageLowByte = payload[1];
    const int ampHoursHighByte = payload[6];
    const int ampHoursLowByte = payload[7];
    const int packAmperageHighByte = payload[4];
    const int packAmperageLowByte = payload[5];


    int lowestVoltage = lowestCellVoltageHighByte * 256 + lowestCellVoltageLowByte;
    int ampHours = ampHoursHighByte * 256 + ampHoursLowByte;


    ptrBatteryGauge->setProperty("batteryLevel", double(ampHours)/10);
    lowestCellVoltage->setProperty("text", QString("%1V")
                            .arg(QString::number(double(lowestVoltage)/1000, 'f', 2)));
}

void handleSecondBmsInfo(const QCanBusFrame &frame)
{
    const QByteArray payload = frame.payload();
    const int highestCellTemp = payload[1];


   highestCellTemperature->setProperty("text", QString("%1°")
                           .arg(highestCellTemp));
}

void handleThirdBmsInfo(const QCanBusFrame &frame)
{
    double timePerKm = 0;

    const QByteArray payload = frame.payload();

    const int packAmperageHighByte = payload[0];
    const int packAmperageLowByte = payload[1];
    const int packVoltageHighByte = payload[5];
    const int packVoltageLowByte = payload[6];


    int packVoltage = packVoltageHighByte * 256 + packVoltageLowByte;
    int packAmperage = ((((packAmperageHighByte*256)+packAmperageLowByte)-32767.0)) * -1;


    batteryVoltage->setProperty("text", QString("%1V")
                            .arg(QString::number(double(packVoltage)/100, 'f', 1)));

    batteryAmperage->setProperty("text", QString("%1A")
                            .arg(QString::number(double(packAmperage / 10.0), 'f', 1)));

    batteryPower->setProperty("text", QString("%1KW")
                            .arg(QString::number(double((packAmperage / 10.0) * (packVoltage / 100) / 1000), 'f', 1)));


    double power = double((packAmperage / 10.0) * (packVoltage / 100) / 1000);



     qDebug() << QString("P: %1").arg(power);
    // qDebug() << QString("A: %1").arg(double((packAmperage / 10.0)));



    if(speed > 0) {
        timePerKm = static_cast<float>(1) / static_cast<float>(speed);
        float wattagePerKm = timePerKm * (packAmperage / 10.0) * (packVoltage / 100);

        wattagePerKmObject->setProperty("text", QString("%1 Wh/km")
                                .arg(QString::number(double(wattagePerKm), 'f', 1)));
    } else {
        wattagePerKmObject->setProperty("text", "0 Wh/km");
    }
}

void handleArduinoInfo(const QCanBusFrame &frame)
{
    const QByteArray payload = frame.payload();

    const int headlightState = payload[0];
    const int blinkerState = payload[1];

    if (blinkerState == 1) {
        rightColor->setProperty("color", QColor(128,255,0));
        leftColor->setProperty("color", QColor(84, 133, 77));


    } else if(blinkerState == 2) {
        leftColor->setProperty("color", QColor(128, 255, 0));
        rightColor->setProperty("color", QColor(84, 133, 77));

    } else {
        rightColor->setProperty("color", QColor(84, 133, 77));
        leftColor->setProperty("color", QColor(84, 133, 77));
    }

    if (headlightState == 1) {
        headlightColor->setProperty("color", QColor(128, 255, 0));
        headlightImage->setProperty("source", "qrc:/images/headlight.png");

    } else if (headlightState == 2) {
        headlightColor->setProperty("color", QColor(66, 135, 245));
        headlightImage->setProperty("source", "qrc:/images/highbeam.png");

    } else {
        headlightColor->setProperty("color", QColor(45, 48, 45));
        headlightImage->setProperty("source", "qrc:/images/headlight.png");
    }
}


void checkFrames()
{
    while(device->framesAvailable() > 0)
    {
       QCanBusFrame frame = device->readFrame();
        if(frame.isValid())
        {
            switch(frame.frameId())
            {
                case FIRST_CONTROLLER_INFO:
                    handleFirstControllerInfo(frame);
                    break;

                case SECOND_CONTROLLER_INFO:
                   // handleSecondControllerInfo(frame);
                    break;

                case FIRST_BMS_INFO:
                    handleFirstBmsInfo(frame);
                    break;

                case SECOND_BMS_INFO:
                    handleSecondBmsInfo(frame);
                    break;

                case THIRD_BMS_INFO:
                    handleThirdBmsInfo(frame);
                    break;

                case ARDUINO_INFO:
                    handleArduinoInfo(frame);
                    break;

                default:
                    break;
            }
        }
    }
}

QCanBusDevice::Filter setCanFilter(const unsigned short &id)
{
    QCanBusDevice::Filter filter;

    filter.frameId = id;
    filter.frameIdMask = 0x7FFu; // Compare against all 11-bits of frame id.
    filter.format = QCanBusDevice::Filter::MatchBaseFormat;
    filter.type = QCanBusFrame::DataFrame;

    return filter;
}


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Speedometer>("com.dashboard.speedometer",1,0,"Speedometer");
    qmlRegisterType<Batterygauge>("com.dashboard.batterygauge",1,0,"Batterygauge");
        qmlRegisterType<Cancommads>("CPP.Mycomponents",1,0,"Cancommands");

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *object = engine.rootObjects()[0];


    engineTemp = object->findChild<QObject*>("engineTemp");


    batteryVoltage = object->findChild<QObject*>("batteryVoltage");
    batteryAmperage = object->findChild<QObject*>("batteryAmperage");
    highestCellTemperature = object->findChild<QObject*>("highestCellTemperature");
    lowestCellVoltage = object->findChild<QObject*>("lowestCellVoltage");
    wattagePerKmObject = object->findChild<QObject*>("wattagePerKm");
    rightColor = object->findChild<QObject*>("rightColor");
    leftColor = object->findChild<QObject*>("leftColor");
    headlightColor = object->findChild<QObject*>("headlightColor");
    headlightImage = object->findChild<QObject*>("headlightImage");
    batteryPower = object->findChild<QObject*>("batteryPower");


    QObject *speedometer = object->findChild<QObject*>("speedoMeter");
    QObject *batterygauge = object->findChild<QObject*>("batteryGauge");
    QObject *canCommands = object->findChild<QObject*>("canCommands");


    ptrBatteryGauge = qobject_cast<Batterygauge*>(batterygauge);
    ptrSpeedometer = qobject_cast<Speedometer*>(speedometer);
    ptrCanCommands = qobject_cast<Cancommads*>(canCommands);


    ptrSpeedometer->setProperty("speed", 0);
    setSpeedometerColor(120);


    if (engine.rootObjects().isEmpty())
        return -1;


    /************************************** CAN Bus functionality ***************************************/

    if(QCanBus::instance()->plugins().contains("socketcan"))
        {

            // Create CAN bus device and connect to can0 via SocketCAN plugin.
            device = QCanBus::instance()->createDevice("socketcan", "can0");
            device->connectDevice();

            // Apply filters to CAN Bus device.
            QList<QCanBusDevice::Filter> filterList;

            filterList.append(setCanFilter(VEHICLE_SPEED));
            filterList.append(setCanFilter(FIRST_CONTROLLER_INFO));
            filterList.append(setCanFilter(SECOND_CONTROLLER_INFO));
            filterList.append(setCanFilter(FIRST_BMS_INFO));
            filterList.append(setCanFilter(SECOND_BMS_INFO));
            filterList.append(setCanFilter(THIRD_BMS_INFO));
            filterList.append(setCanFilter(ARDUINO_INFO));

            bool fdKey = true;

            device->setConfigurationParameter(QCanBusDevice::RawFilterKey, QVariant::fromValue(filterList));
            device->setConfigurationParameter(QCanBusDevice::CanFdKey, fdKey);
            QTimer *canTimer = new QTimer;

            canTimer->start(100);

            QObject::connect(canTimer, &QTimer::timeout, sendCanCommands);

            // Connect framesRecieved signal to slot function for reading frames.
            QObject::connect(device, &QCanBusDevice::framesReceived, checkFrames);


    }
    return app.exec();
}
