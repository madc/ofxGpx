#include "ofMain.h"
#include "ofxGpx.h"

ofxGpx::ofxGpx() {
};

bool ofxGpx::load(string _path) {
    if(XML.load(_path)){
        ofLog(OF_LOG_NOTICE, "Loaded " + _path);
        
        // metadataType
        if(XML.exists("metadata")) {
            XML.setTo("metadata[0]");
            
            if(XML.exists("name")) {
                gpxMetadata.name = XML.getValue<string>("name");
            }
            
            if(XML.exists("desc")) {
                gpxMetadata.desc = XML.getValue<string>("desc");
            }
            
            if(XML.exists("autor")) {
                //PersonType
            }
            
            if(XML.exists("copyright")) {
                //CopyrightType
            }
            
            if(XML.exists("link")) {
                //LinkType
            }
            
            if(XML.exists("time")) {
                gpxMetadata.time = XML.getValue<string>("//time");
            }
            
            if(XML.exists("keywords")) {
                gpxMetadata.keywords = XML.getValue<string>("keywords");
            }
            
            if(XML.exists("bounds")) {
                XML.setTo("bounds[0]");
                
                gpxMetadata.bounds_lonlat[0] = ofPoint(ofToFloat(XML.getAttribute("minlon")), ofToFloat(XML.getAttribute("minlat")));
                gpxMetadata.bounds_lonlat[1] = ofPoint(ofToFloat(XML.getAttribute("maxlon")), ofToFloat(XML.getAttribute("maxlat")));
                
                XML.setToParent();
            } else {
                gpxMetadata.bounds_lonlat[0] = ofPoint(180, 90);
                gpxMetadata.bounds_lonlat[1] = ofPoint(-180, -90);
            }
            
            XML.setToParent();
        }
        
        // wptType
        for(int i=0; XML.exists("wpt["+ofToString(i)+"]"); i++) {
            XML.setTo("wpt["+ofToString(i)+"]");
            
            GPXWPT point;
            
            double lat = ofToDouble(XML.getAttribute("lat"));
            double lon = ofToDouble(XML.getAttribute("lon"));
            double ele = XML.getValue<double>("ele");
            
            point.coor_lonlat = ofPoint(lon, lat, ele);
            point.coor_mercator = convertToMercator(point.coor_lonlat);
            
            if(XML.exists("time")) {
                point.time = XML.getValue<string>("time");
            }
            
            if(XML.exists("name")) {
                point.name = XML.getValue<string>("name");
            }
            
            if(XML.exists("cmt")) {
                point.cmt = XML.getValue<string>("cmt");
            }
            
            if(XML.exists("desc")) {
                point.desc = XML.getValue<string>("desc");
            }
            
            if(XML.exists("src")) {
                point.src = XML.getValue<string>("src");
            }
            
            if(XML.exists("link")) {
                //LinkType
            }
            
            calculateBounds(point.coor_lonlat);
            
            gpxWaypoints.push_back(point);
            XML.setToParent();
        }
        
        // rteType
        for(int i=0; XML.exists("rte["+ofToString(i)+"]"); i++) {
            XML.setTo("rte["+ofToString(i)+"]");
            
            if(XML.getName() != "rte") {
                break;
            }
            
            GPXRTE route;
            
            if(XML.exists("name")) {
                route.name = XML.getValue<string>("name");
            }
            
            if(XML.exists("cmt")) {
                route.cmt = XML.getValue<string>("cmt");
            }
            
            if(XML.exists("desc")) {
                route.desc = XML.getValue<string>("desc");
            }
            
            if(XML.exists("src")) {
                route.src = XML.getValue<string>("src");
            }
            
            if(XML.exists("link")) {
                //LinkType
            }
            
            if(XML.exists("number")) {
                route.number = XML.getValue<int>("number");
            }
            
            if(XML.exists("type")) {
                route.type = XML.getValue<string>("type");
            }
            
            if(XML.exists("rtept")) {
                XML.setTo("rtept[0]");

                do {
                    GPXWPT point;
                    
                    double lat = ofToDouble(XML.getAttribute("lat"));
                    double lon = ofToDouble(XML.getAttribute("lon"));
                    double ele = XML.getValue<double>("ele");
                    
                    point.coor_lonlat = ofPoint(lon, lat, ele);
                    point.coor_mercator = convertToMercator(point.coor_lonlat);
                    
                    if(XML.exists("time")) {
                        point.time = XML.getValue<string>("time");
                    }
                    
                    if(XML.exists("name")) {
                        point.name = XML.getValue<string>("name");
                    }
                    
                    if(XML.exists("cmt")) {
                        point.cmt = XML.getValue<string>("cmt");
                    }
                    
                    if(XML.exists("desc")) {
                        point.desc = XML.getValue<string>("desc");
                    }
                    
                    if(XML.exists("src")) {
                        point.src = XML.getValue<string>("src");
                    }
                    
                    if(XML.exists("link")) {
                        //LinkType
                    }
                    
                    calculateBounds(point.coor_lonlat);
                    
                    route.rtept.push_back(point);
                }
                while(XML.setToSibling());
                
                XML.setToParent();
            }
            
            gpxRoutes.push_back(route);
            XML.setToParent();
        }
        
        // trkType
        for(int i=0; XML.exists("trk["+ofToString(i)+"]"); i++) {
            XML.setTo("trk["+ofToString(i)+"]");
            
            GPXTRK track;

            if(XML.exists("name")) {
                track.name = XML.getValue<string>("name");
            }
            
            if(XML.exists("cmt")) {
                track.cmt = XML.getValue<string>("cmt");
            }
            
            if(XML.exists("desc")) {
                track.desc = XML.getValue<string>("//desc");
            }
            
            if(XML.exists("src")) {
                track.src = XML.getValue<string>("//src");
            }
            
            if(XML.exists("link")) {
                //LinkType
            }
            
            if(XML.exists("number")) {
                track.number = XML.getValue<int>("number");
            }
            
            if(XML.exists("type")) {
                track.type = XML.getValue<string>("type");
            }
            
            vector<GPXTRKSEG> tracksegments;
            for(int j=0; XML.exists("trkseg["+ofToString(j)+"]"); j++) {
                XML.setTo("trkseg["+ofToString(j)+"]trkpt[0]");

                GPXTRKSEG tracksegment;

                do {
                    GPXWPT point;
                    
                    double lat = ofToDouble(XML.getAttribute("lat"));
                    double lon = ofToDouble(XML.getAttribute("lon"));
                    double ele = XML.getValue<double>("ele");
                    
                    point.coor_lonlat = ofPoint(lon, lat, ele);
                    point.coor_mercator = convertToMercator(point.coor_lonlat);
                    
                    if(XML.exists("time")) {
                        point.time = XML.getValue<string>("time");
                    }
                    
                    if(XML.exists("name")) {
                        point.name = XML.getValue<string>("name");
                    }
                    
                    if(XML.exists("cmt")) {
                        point.cmt = XML.getValue<string>("cmt");
                    }
                    
                    if(XML.exists("desc")) {
                        point.desc = XML.getValue<string>("desc");
                    }
                    
                    if(XML.exists("src")) {
                        point.src = XML.getValue<string>("src");
                    }
                    
                    if(XML.exists("link")) {
                        //LinkType
                    }
                    
                    calculateBounds(point.coor_lonlat);
                    
                    tracksegment.trkpt.push_back(point);
                }
                while(XML.setToSibling());
                
                tracksegments.push_back(tracksegment);
                
                XML.setToParent();
                XML.setToParent();
            }
            
            XML.setToParent();
            
            track.trkseg = tracksegments;
            gpxTracks.push_back(track);
        }
        
        gpxMetadata.bounds_mercator[0] = convertToMercator(gpxMetadata.bounds_lonlat[0]);
        gpxMetadata.bounds_mercator[1] = convertToMercator(gpxMetadata.bounds_lonlat[1]);
        
        return true;
    } else {
        // not found or parsing error
        ofLog(OF_LOG_ERROR, "Could not load " + _path);
        
        return false;
    }
};


void ofxGpx::calculateBounds(ofPoint _lonlat) {
    if(_lonlat.x < gpxMetadata.bounds_lonlat[0].x) {
        gpxMetadata.bounds_lonlat[0].x = _lonlat.x;
    }
    
    if(_lonlat.y < gpxMetadata.bounds_lonlat[0].y) {
        gpxMetadata.bounds_lonlat[0].y = _lonlat.y;
    }
    
    if(_lonlat.x > gpxMetadata.bounds_lonlat[1].x) {
        gpxMetadata.bounds_lonlat[1].x = _lonlat.x;
    }

    if(_lonlat.y > gpxMetadata.bounds_lonlat[1].y) {
        gpxMetadata.bounds_lonlat[1].y = _lonlat.y;
    }
}

// -----------------------------------------------------------------------------------

// LonLat to Mercator conversion
ofPoint ofxGpx::convertToMercator(ofPoint _coordinates) {
    ofPoint point;

    point.x = _coordinates.x/180;
    point.y = log(tan(PI/4 + ofDegToRad(_coordinates.y)/2))/PI;
    
    point.z = _coordinates.z;
    
    return point;
};

// ------------------------------------------------------------------------------------