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
    width: 100; height: 100

    states: [
        State { name: "activated" },
        State { name: "deactivated" }
    ]

    Component.onCompleted: {
        console.log("Name of first state:", states[0].name)
        for (var i = 0; i < states.length; i++)
            console.log("state", i, states[i].name)
    }
}
