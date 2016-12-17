#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0,0,0);
    ofEnableAlphaBlending();
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetLogLevel("ofXml", OF_LOG_SILENT);
    
    colorFlow.setup();
    //colorFlow.settings.add(doSwitch.set("doSwitch", true));
    
    image.load("composition_vii.jpg");
}

//--------------------------------------------------------------
void ofApp::update(){
    colorFlow.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
    ofEnableAlphaBlending();
    
    colorFlow.draw(&image);
    
    int size = colorFlow.drawSmallSize;
    if (doDrawDebug) {
        colorFlow.flowMap.map.draw(0.0 * size, 0, size, size * 0.6);
        ofDrawBitmapStringHighlight("flow map", 0.0 * size, 20);
        
        image.draw(1.0 * size, 0, size, size * 0.6);
        ofDrawBitmapStringHighlight("image", 1.0 * size, 20);

        colorFlow.flowMap.fbo.draw(2.0 * size, 0, size, size * 0.6);
        ofDrawBitmapStringHighlight("fbo", 2.0 * size, 20);
    }

    
    ofSetColor(255);
    stringstream help;
    help << "[ColorFlow]:\n";
    help << "TAB: toggle debug\n";
    help << "SPACE: toggle edit\n";
    help << "m: toggle map view\n";
    help << "f: toggle fullscreeen\n";
    help << "c: clear map\n";
    help << "s: save created map as created.png\n";
    ofDrawBitmapString(help.str(), 10, ofGetHeight() - 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    colorFlow.keyPressed(key);
    if (key == OF_KEY_TAB) doDrawDebug = !doDrawDebug;
    if (key == 'm') colorFlow.drawMap = !colorFlow.drawMap;
    if (key == 'f') ofToggleFullscreen();
    if (key == ' ') colorFlow.flowMap.doDrawToMap = !colorFlow.flowMap.doDrawToMap;
}

void ofApp::exit() {}
