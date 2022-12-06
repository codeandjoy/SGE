#include <fstream>
#include <jsoncpp/json/json.h>
using namespace std;

#include "readTiledMapData.h"

Json::Value readTiledMapData(string mapDataFileLocation){
    Json::Value mapData;

    ifstream mapFile(mapDataFileLocation, ifstream::binary);
    mapFile >> mapData;

    // Prepare data
    Json::Value cleanMapData;
    cleanMapData["width"] = mapData["width"];
    cleanMapData["height"] = mapData["height"];
    cleanMapData["tilewidth"] = mapData["tilewidth"];
    cleanMapData["tileheight"] = mapData["tileheight"];
    cleanMapData["layers"] = mapData["layers"];
    // 
    // printf("%s", cleanMapData.toStyledString().c_str());

    return cleanMapData;
}