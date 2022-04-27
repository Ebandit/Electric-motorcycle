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

Page {
    width: 840
    height: 400

    ColumnLayout {
        spacing: 2

        Rectangle {
           width: 840; height: 140; color: "#1a1b1c"

            Row {
                spacing: 15
                anchors.verticalCenter: parent.verticalCenter

                        Column {
                            leftPadding: 30
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
                                leftPadding: 10
                                id: buttontext
                                text: "Test"
                            }

                        }


                        Column {
                            spacing: 10
                            leftPadding: 30

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
                                    objectName: "VoltageColor"
                                    anchors.fill: ampere
                                    source: ampere
                                    color: "blue"

                                }
                            }

                            Label {
                                leftPadding: 10
                                id: buttontext1
                                text: "Test"
                            }
                        }


                            Column {
                                spacing: 10
                                leftPadding: 30


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
                                        color: "blue"

                                    }
                                }

                                Label {
                                    leftPadding: 10
                                    id: buttontext11
                                    text: "Test"
                                }
                            }


                            Column {
                                spacing: 10
                                leftPadding: 30


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
                                        color: "blue"

                                    }
                                }

                                Label {
                                    leftPadding: 10
                                    id: buttontext111
                                    text: "Test"
                                }
                            }


                            Column {
                                spacing: 10
                                leftPadding: 20

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
                                        color: "blue"

                                    }
                                }

                                Label {
                                    leftPadding: 10
                                    id: buttontext1111
                                    text: "Test"
                                }
                            }

                            Item {
                                id: spacer
                                width: 80
                                height: 50

                            }

                            Column {
                                spacing: 6


                            Item {
                                id: clock
                                width: 50
                                height: 20

                                property int hours
                                property int minutes
                                property bool internationalTime: false //Unset for local time

                                function timeChanged() {
                                    var date = new Date;
                                    hours = internationalTime ? date.getUTCHours() + Math.floor(clock.shift) : date.getHours()
                                    minutes = internationalTime ? date.getUTCMinutes() + ((clock.shift % 1) * 60) : date.getMinutes()
                                }

                                Timer {
                                    interval: 100; running: true; repeat: true;
                                    onTriggered: clock.timeChanged()
                                }


                                Text {
                                    leftPadding: 5
                                    bottomPadding: 20
                                    id: clockText
                                    text: `${clock.hours}:${clock.minutes}`
                                    font.pointSize: 16
                                    font.bold: true
                                    color: "blue"
                                }
                            }

                            Item {
                                id: compassItem
                                width: 50
                                height: 50


                                Image {
                                    width: 50
                                    height: 50
                                    id: compass
                                    source: "qrc:/images/north.png"
                                }
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
