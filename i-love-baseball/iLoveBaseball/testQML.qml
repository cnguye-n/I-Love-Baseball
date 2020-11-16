import QtQuick 2.0
import QtLocation 5.3
import QtPositioning 5.0

Item {

    id: window

    Plugin
    {
        id: mapPlugin
        name: "osm"
    }

    Map
    {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(38.500000, -97.000000)
        zoomLevel: 4.7

        Component.onCompleted:
        {

        }
    }

    function addLine(code, color)
    {
        var path;

        // PROC - COORDINATES OF EACH STADIUM
        //        25 "UNIQUE" ones because 5 are "same destination"

        // angels stadium is same destination as dodgers
        let angel = {latitude: 33.800186, longitude: -117.88274}
        // at&t park is same destination as o.co coliseum
        let att = {latitude: 37.778027, longitude: -122.390625}
        let busch = {latitude: 38.62262, longitude: -90.19282}
        // camden is same destination as national park
        let camden = {latitude: 39.284023, longitude: -76.62022}
        let chase = {latitude: 33.445377, longitude: -112.06762}
        // citi field is same destination as yankee stadium
        let citi = {latitude: 40.757088, longitude: -73.84582}
        let citizens = {latitude: 39.905018, longitude: -75.16677}
        let comerica = {latitude: 42.337856, longitude: -83.04946}
        let coors = {latitude: 39.75532, longitude: -104.99324}
        let fenway = {latitude: 42.345894, longitude: -71.09816}
        // globe park AKA rangers park
        let globe = {latitude: 32.74736, longitude: -97.08417}
        let great = {latitude: 39.097614, longitude: -84.50745}
        let kauffman = {latitude: 39.05079, longitude: -94.48145}
        let marlins = {latitude: 25.77813, longitude: -80.21954}
        let miller = {latitude: 43.02852, longitude: -87.971886}
        let maid = {latitude: 29.757746, longitude: -95.35616}
        let petco = {latitude: 32.707565, longitude: -117.15706}
        let pnc = {latitude: 40.446964, longitude: -80.00571}
        let progressive = {latitude: 41.494724, longitude: -81.685326}
        let rogers = {latitude: 43.6418, longitude: -79.3891}
        let safeco = {latitude: 47.5914, longitude: -122.3325}
        let target = {latitude: 44.9818, longitude: -93.2775}
        let tropicana = {latitude: 27.7682, longitude: -82.6534}
        let turner = {latitude: 33.7354, longitude: -84.3895}
        // wrigley field is same destination as us cellular stadium
        let wrigley = {latitude: 41.9484, longitude: -87.6553}

        // PROCESSING - set paths based on different codes passed in
        // TOTAL 47 EDGES
        switch (code)
        {
            case "safeco_ATT":
                path = [safeco, att]
                break;
            case "safeco_rogers":
                path = [safeco, rogers]
                break;
            case "safeco_target":
                path = [safeco, target]
                break;
            case "ATT_angel":
                path = [att, angel]
                break;
            case "ATT_chase":
                path = [att, chase]
                break;
            case "angel_petco":
                path = [angel, petco]
                break;
            case "angel_target":
                path = [angel, target]
                break;
            case "petco_chase":
                path = [petco, chase]
                break;
            case "petco_coors":
                path = [petco, coors]
                break;
            case "chase_coors":
                path = [chase, coors]
                break;
            // -- 10
            case "chase_globe":
                path = [chase, globe]
                break;
            case "chase_maid":
                path = [chase, maid]
                break;
            case "coors_globe":
                path = [coors, globe]
                break;
            case "coors_kauffman":
                path = [coors, kauffman]
                break;
            case "target_miller":
                path = [target, miller]
                break;
            case "target_busch":
                path = [target, busch]
                break;
            case "kauffman_globe":
                path = [kauffman, globe]
                break;
            case "kauffman_wrigley":
                path = [kauffman, wrigley]
                break;
            case "globe_turner":
                path = [globe, turner]
                break;
            case "globe_maid":
                path = [globe, maid]
                break;
            // -- 20
            case "miller_rogers":
                path = [miller, rogers]
                break;
            case "miller_wrigley":
                path = [miller, wrigley]
                break;
            case "wrigley_comerica":
                path = [wrigley, comerica]
                break;
            case "wrigley_great":
                path = [wrigley, great]
                break;
            case "busch_great":
                path = [busch, great]
                break;
            case "busch_maid":
                path = [busch, maid]
                break;
            case "rogers_fenway":
                path = [rogers, fenway]
                break;
            case "rogers_pnc":
                path = [rogers, pnc]
                break;
            case "rogers_comerica":
                path = [rogers, comerica]
                break;
            case "comerica_progress":
                path = [comerica, progressive]
                break;
            // -- 30
            case "progress_pnc":
                path = [progressive, pnc]
                break;
            case "progress_great":
                path = [progressive, great]
                break;
            case "great_turner":
                path = [great, turner]
                break;
            case "great_tropicana":
                path = [great, tropicana]
                break;
            case "great_pnc":
                path = [great, pnc]
                break;
            case "pnc_citi":
                path = [pnc, citi]
                break;
            case "pnc_camden":
                path = [pnc, camden]
                break;
            case "turner_camden":
                path = [turner, camden]
                break;
            case "turner_marlins":
                path = [turner, marlins]
                break;
            case "fenway_citi":
                path = [fenway, citi]
                break;
            // -- 40
            case "fenway_marlins":
                path = [fenway, marlins]
                break;
            case "citi_citizens":
                path = [citi, citizens]
                break;
            case "citizens_camden":
                path = [citizens, camden]
                break;
            case "camden_marlins":
                path = [camden, marlins]
                break;
            case "tropicana_marlins":
                path = [tropicana, marlins]
                break;
            case "maid_tropicana":
                path = [maid, tropicana]
                break;
            case "maid_marlins":
                path = [maid, marlins]
                break;
            // -- TOTAL 48 EDGES
            case "kauff_busch":
                path = [kauffman, busch]
                break;

        }

        // set line item
        var component = Qt.createComponent("qrc:///qml/line.qml")
        var item = component.createObject(window, { path: path,
        lineColor: color})
        map.addMapItem(item)
    }

    // FUNCTION TO ADD MARKER
    function addMarker(name, latitude, longitude)
    {
        var component = Qt.createComponent("qrc:///qml/marker.qml")
        var item = component.createObject(window, { coordinate:
        QtPositioning.coordinate(latitude, longitude), labelText: name })
        map.addMapItem(item)
    }

    // FUNCTION TO CLEAR ALL MAP ITEMS
    function clearAll()
    {
        map.clearMapItems();
    }
}
