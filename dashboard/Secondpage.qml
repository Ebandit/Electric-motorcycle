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
import CPP.Mycomponents 1.0

Item {
    Cancommands{
        objectName: "canCommands"
        id:qmlEmp;
        ledstate: "0"
    }

    GridLayout {

        Item {
            width: 266
            height: 400

            ColumnLayout {

            }
        }

        ColumnLayout {
            spacing: 10

            Button{
                text: "Polizai"
                implicitWidth: 266
                implicitHeight: 60




                onClicked: {
                    qmlEmp.ledstate = 2
                }
            }


            Button{
                text: "Ritariloinen"
                implicitWidth: 266
                implicitHeight: 60


                onClicked: {
                    qmlEmp.ledstate = 4
                }
            }

            Button{
                text: "OFF"
                implicitWidth: 266
                implicitHeight: 60


                onClicked: {
                    qmlEmp.ledstate = 0
                }
            }
        }
    }
}

