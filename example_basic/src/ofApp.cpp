#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gpxData.load("my-track.gpx");
    
    ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){
 
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 0, 0);
    
    // This is just a quick and dirty example. Sorry about that.
    
    for(vector<GPXTRK >::iterator it = gpxData.gpxTracks.begin(); it != gpxData.gpxTracks.end(); ++it) { // Tracks
        for(vector<GPXTRKSEG >::iterator jt = it->trkseg.begin(); jt != it->trkseg.end(); ++jt) {        //  - Track Segments
            for(vector<GPXWPT >::iterator kt = jt->trkpt.begin(); kt != jt->trkpt.end(); ++kt) {         //  - Track Segment Points
                ofCircle((kt->mercator.x*1000)-377000, (kt->mercator.y*1000)-225400, 1);
            }
        }
    }
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
