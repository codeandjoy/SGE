#include <fstream>
#include <iostream>
#include <jsoncpp/json/json.h>

#include "readTiledMapData.h"

Json::Value readTiledMapData(std::string mapDataFileLocation){
    std::ifstream mapFile(mapDataFileLocation);
    if(!mapFile.is_open()){
        printf("Can not open file: %s", mapDataFileLocation.c_str());
        exit(1);
    }

    Json::Reader reader;
    Json::Value mapData;

    if(!reader.parse(mapFile, mapData)){
        printf("Can not parse file: %s", mapDataFileLocation.c_str());
        exit(1);
    }

    // Prepare data
    Json::Value cleanMapData;
    cleanMapData["width"] = mapData["width"];
    cleanMapData["height"] = mapData["height"];
    cleanMapData["tilewidth"] = mapData["tilewidth"];
    cleanMapData["tileheight"] = mapData["tileheight"];
    cleanMapData["layers"] = mapData["layers"];
    // 

    return cleanMapData;
}