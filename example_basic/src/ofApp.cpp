#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetColor(255, 0, 0);

    gpxData.load("my-track.gpx");
    offset = 10;
    
    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
}

//--------------------------------------------------------------
void ofApp::update(){
    float scaleFactorX = (gpxData.gpxMetadata.bounds_mercator[1].x - gpxData.gpxMetadata.bounds_mercator[0].x) / (ofGetWindowWidth() - 2 * offset);
    float scaleFactorY = (gpxData.gpxMetadata.bounds_mercator[1].y - gpxData.gpxMetadata.bounds_mercator[0].y) / (ofGetWindowHeight() - 2 * offset);
    
    float scaleFactor;

    if(scaleFactorX > scaleFactorY) {
        scaleFactor = scaleFactorX;
    } else {
        scaleFactor = scaleFactorY;
    }
    
    mesh.clear();
    
    // This is just a quick and dirty example. Sorry about that.
    for(vector<GPXTRK >::iterator it = gpxData.gpxTracks.begin(); it != gpxData.gpxTracks.end(); ++it) { // Tracks
        for(vector<GPXTRKSEG >::iterator jt = it->trkseg.begin(); jt != it->trkseg.end(); ++jt) {        //  - Track Segments
            for(vector<GPXWPT >::iterator kt = jt->trkpt.begin(); kt != jt->trkpt.end(); ++kt) {         //  - Track Segment Points
                float x = (kt->coor_mercator.x - gpxData.gpxMetadata.bounds_mercator[0].x) / scaleFactor;
                float y = (kt->coor_mercator.y - gpxData.gpxMetadata.bounds_mercator[0].y) / scaleFactor;
                
                mesh.addVertex(ofPoint(x + offset, ofGetWindowHeight() - offset - y));
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    mesh.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
