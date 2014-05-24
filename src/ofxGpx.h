#pragma once

#include "ofMain.h"

// GPX metadataType
typedef struct GPXMetadataType {
    string name;
    string desc;
    // author
    // copyright
    // link
    string time;
    string keywords;
    ofPoint bounds [2];
} GPXMETADATA;

// GPX wptType
typedef struct GPXWptType {
    ofPoint lonlat; // Lon, Lat, Ele
    string time;
    // magvar
    // geoidheight
    string name;
    string cmt;
    string desc;
    string src;
    // link
    // sym
    string type;
    // fix
    // sat
    // hdop
    // vdop
    // pdop
    // ageofdgpsdata
    // dgpsid
    
    ofPoint mercator;
} GPXWPT;

// GPX rteType
typedef struct GPXRteType {
    string name;
    string cmt;
    string desc;
    string src;
    // link
    int number = 0;
    string type;
    vector<GPXWPT > rtept;
} GPXRTE;

// GPX trksegType
typedef struct GPXTrksegType {
    vector<GPXWPT > trkpt;
} GPXTRKSEG;

// GPX trkType
typedef struct GPXTrkType {
    string name;
    string cmt;
    string desc;
    string src;
    // link
    int number = 0;
    string type;
    vector<GPXTRKSEG > trkseg;
} GPXTRK;


class ofxGpx {
    public:
        ofxGpx();
        bool load(string _path);
    
        GPXMETADATA gpxMetadata;
        vector<GPXWPT> gpxWaypoints;
        vector<GPXRTE> gpxRoutes;
        vector<GPXTRK> gpxTracks;
    private:
        ofPoint convertToMercator(ofPoint);
        void calculateBounds(ofPoint);
        ofXml XML;
};
