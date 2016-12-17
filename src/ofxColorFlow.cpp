#include "ofxColorFlow.h"

//--------------------------------------------------------------
void ofxColorFlow::setup(){
    
    settings.setName("color_flow");
    settings.add(doShader.set("doShader", true));
    settings.add(drawMap.set("drawMap", false));
    settings.add(flowSpeed.set("flowSpeed", 164.0f, -.5f * 1024.0, .5f * 1024.0));
    settings.add(cycleTime.set("cycleTime", 10.0f, .0f, 100.0f));
    settings.add(drawSize.set("drawSize", .4f, .0f, 1920));
    settings.add(drawSmallSize.set("drawSmallSize", 128.f, .0f, 1024));
    settings.add(flowMap.settings);
    
    loadShaders();
    
    flowMap.setup();
}

//--------------------------------------------------------------
void ofxColorFlow::update() {
    flowMap.update();
}

//--------------------------------------------------------------
void ofxColorFlow::draw(ofImage *image) {
    
    ofClear(140);
    ofSetColor(255);
    ofEnableAlphaBlending();
    
    int type = 0;
    if (drawMap) type = 1;
    if (doShader == false) type = 2;
    
    flowMapFrag.begin();
    flowMapFrag.setUniform1i("type", type);
    flowMapFrag.setUniform1f("flowSpeed", flowSpeed);
    flowMapFrag.setUniform1f("cycleTime", cycleTime);
    flowMapFrag.setUniform1f("time", ofGetElapsedTimeMillis() / 100.0);
    flowMapFrag.setUniformTexture("water", image->getTexture(), 0);
    flowMapFrag.setUniform2f("imageSize", image->getWidth(), image->getHeight());
    flowMapFrag.setUniformTexture("flowMap", flowMap.fbo.getTexture(), 2);
    flowMapFrag.setUniform2f("mapSize", flowMap.fbo.getWidth(), flowMap.fbo.getHeight());
    image->draw(0, 0, ofGetWidth(), ofGetHeight());
    flowMapFrag.end();
}

void ofxColorFlow::loadShaders() {
    flowMapFrag.load("", "shaders/flow/FlowMap.frag");
    generateNormalMapShader.load("", "shaders/flow/GenerateNormalMap.frag");
    flowMapDirectionFrag.load("", "shaders/flow/FlowDirection.frag");
    flowMapTimeCycleFrag.load("", "shaders/flow/FlowMapTimeCycle.frag");
    flowMap.loadShaders();
    ofLogVerbose("[ofApp] reloaded");
}


//--------------------------------------------------------------
void ofxColorFlow::keyPressed(int key){
    
    if (key == '1') flowMap.mapPressure = -flowMap.mapPressure;
    if (key == 'c') flowMap.clearMap();
    if (key == ']' || key == '[' || key == 'p' || key == 'o') flowMap.updateMap();
    if (key == 'r') loadShaders();    
    if (key == '.') {
        ofImage image;
        flowMap.fbo.readToPixels(image.getPixels());
        image.update();
        image.save("map/created.png");
    }

}
