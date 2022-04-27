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

Window {
    id: window
    visible: true
    width: 800
    height: 400
    color: "#dff5f4"

    SwipeView {
        id: view
        currentIndex: 0
        anchors.fill: parent

        Firstpage {
            id: first
        }

        Secondpage {
            id: secondPage
        }
    }

}

