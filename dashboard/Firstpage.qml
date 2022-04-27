import QtQuick 2.9
import QtQuick.Window 2.2
import com.dashboard.speedometer 1.0
import com.dashboard.batterygauge 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import Qt.labs.location 1.0
import QtQuick.Extras 1.4
import QtQuick.Shapes 1.14
import QtGraphicalEffects 1.0
import QtLocation 5.6
import QtPositioning 5.6

Item {
    ColumnLayout {

        spacing: 2
        Rectangle {
           width: 800; height: 140; color: "#ffffff"

            Row {
                spacing: 15
                anchors.verticalCenter: parent.verticalCenter

                        Column {
                            leftPadding: 10
                            spacing: 10

                            Item {
                                id: voltageItem
                                width: 50
                                height: 50

                                Image {
                                    width: 50
                                    height: 50
                                    id: voltage
                                    source: "qrc:/images/lightning-in-a-circle.png"
                                }


                                ColorOverlay {
                                    objectName: "VoltageColor"
                                    anchors.fill: voltage
                                    source: voltage
                                    color: "yellow"

                                }
                            }

                            Label {
                                objectName: "batteryVoltage"
                                id: buttontext
                                text: "0"
                                color: "black"
                                font.pixelSize: 30
                            }

                        }


                        Column {
                            spacing: 10
                            leftPadding: 10

                            Item {
                                id: ampereItem
                                width: 50
                                height: 50

                                Image {
                                    width: 50
                                    height: 50
                                    id: ampere
                                    source: "qrc:/images/ampere.png"
                                }


                                ColorOverlay {
                                    objectName: "ampereColor"
                                    anchors.fill: ampere
                                    source: ampere
                                    color: "blue"

                                }
                            }

                            Label {
                                objectName: "batteryAmperage"
                                leftPadding: 10
                                id: buttontext1
                                text: "0"
                                color: "black"
                                font.pixelSize: 30

                            }
                        }


                            Column {
                                spacing: 10
                                leftPadding: 10


                                Item {
                                    id: engineItem
                                    width: 50
                                    height: 50

                                    Image {
                                        width: 50
                                        height: 50
                                        id: engine
                                        source: "qrc:/images/engine.png"
                                    }


                                    ColorOverlay {
                                        objectName: "engineColor"
                                        anchors.fill: engine
                                        source: engine
                                        color: "red"

                                    }
                                }

                                Label {
                                    objectName: "engineTemp"
                                    leftPadding: 15
                                    id: buttontext11
                                    text: "22°"
                                    color: "black"
                                    font.pixelSize: 30

                                }
                            }


                            Column {
                                spacing: 10
                                leftPadding: 10


                                Item {
                                    id: batterytempItem
                                    width: 50
                                    height: 50

                                    Image {
                                        width: 50
                                        height: 50
                                        id: batteryTemp
                                        source: "qrc:/images/batterytemp.png"
                                    }


                                    ColorOverlay {
                                        objectName: "batteryTempColor"
                                        anchors.fill: batteryTemp
                                        source: batteryTemp
                                        color: "green"

                                    }
                                }

                                Label {
                                    objectName: "highestCellTemperature"
                                    leftPadding: 7
                                    id: buttontext111
                                    text: "0"
                                    color: "black"
                                    font.pixelSize: 30

                                }
                            }


                            Column {
                                spacing: 10
                                leftPadding: 5

                                Item {
                                    id: betteryItem
                                    width: 50
                                    height: 50

                                    Image {
                                        width: 50
                                        height: 50
                                        id: battery
                                        source: "qrc:/images/battery.png"
                                    }


                                    ColorOverlay {
                                        objectName: "batteryColor"
                                        anchors.fill: battery
                                        source: battery
                                        color: "green"

                                    }
                                }

                                Label {
                                    objectName: "lowestCellVoltage"
                                    id: buttontext1111
                                    text: "0"
                                    color: "black"
                                    leftPadding: 3
                                    font.pixelSize: 30
                                }
                            }

                            Column {
                                spacing: 10
                                leftPadding: 5

                                Item {
                                    id: battreyPowerItem
                                    width: 50
                                    height: 50

                                    Image {
                                        width: 50
                                        height: 50
                                        id: batteryPowerimg
                                        source: "qrc:/images/power.png"
                                    }


                                    ColorOverlay {
                                        objectName: "batteryPowerColor"
                                        anchors.fill: batteryPowerimg
                                        source: batteryPowerimg
                                        color: "green"

                                    }
                                }

                                Label {
                                    objectName: "batteryPower"
                                    id: batteryPowerText
                                    text: "0"
                                    color: "black"
                                    font.pixelSize: 30
                                }
                            }

                            Item {
                                id: spacer
                                height: 50

                            }

                            Column {
                                spacing: 10
                                leftPadding: 10


                                Item {
                                    id: wattagePerKmItem
                                    width: 50
                                    height: 50
                                }

                                Label {
                                    objectName: "wattagePerKm"
                                    id: wattagePerKmText
                                    text: "0"
                                    color: "black"
                                    font.pixelSize: 30
                                }
                            }
                        }
                    }


        RowLayout {
            Speedometer
            {
                objectName: "speedoMeter"
                x: 15
                y: 170
                width: speedometerSize
                height: speedometerSize
                startAngle: startAngle
                alignAngle: alignAngle
                lowestRange: lowestRange
                highestRange: highestRange
                speed: speed
                arcWidth: arcWidth
                outerColor: outerColor
                innerColor: innerColor
                speedColor: speedColor
                textColor: textColor
                backgroundColor: backgroundColor
            }

            ColumnLayout {
                RowLayout {
                    spacing: 50


                    Item {
                        id: spacers
                        width: 7
                        height: 2

                    }

                    Item {
                        id: leftArrowItem
                        width: 50
                        height: 50


                        Image {
                            id: leftArrow
                            source: "qrc:/images/right.png"
                            width: 50
                            height: 50
                            rotation: 180
                        }

                        ColorOverlay {
                            objectName: "leftColor"
                            anchors.fill: leftArrow
                            source: leftArrow
                            color: "#54854d"
                            rotation: 180

                        }
                    }

                    Item {
                        id: headlightItem
                        width: 50
                        height: 50


                        Image {
                            objectName: "headlightImage"
                            id: headlight
                            source: "qrc:/images/headlight.png"
                            width: 50
                            height: 50
                        }

                        ColorOverlay {
                            objectName: "headlightColor"
                            anchors.fill: headlight
                            source: headlight
                            color: "#2d302d"
                        }
                    }

                    Item {
                        id: rightArrowItem
                        width: 50
                        height: 50


                        Image {
                            id: rightArrow
                            source: "qrc:/images/right.png"
                            width: 50
                            height: 50
                            rotation: 0
                        }

                        ColorOverlay {
                            objectName: "rightColor"
                            anchors.fill: rightArrow
                            source: rightArrow
                            color: "#54854d"
                        }
                    }
                }


                Batterygauge
                {
                    objectName: "batteryGauge"
                    width: BatterygaugeSize
                    height: BatterygaugeSize
                    startAngle: startAngle
                    alignAngle: alignAngle
                    lowestRange: lowestRange
                    highestRange: highestRange
                    batteryLevel: batteryLevel
                    arcWidth: arcWidth
                    outerColor: outerColor
                    innerColor: innerColor
                    textColor: textColor
                    backgroundColor: backgroundColor
                }
            }
        }
    }
}
