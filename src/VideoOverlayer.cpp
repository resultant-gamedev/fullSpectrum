//
//  VideoOverlayer.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 10/04/2013.
//
//

#include "VideoOverlayer.h"


VideoOverlayer::VideoOverlayer()
{
    streamWidth = 640 ;
    streamHeight = 360;
    

    //videoIn.allocateCamera(streamWidth, streamHeight);
    lensImage.allocate(streamWidth, streamHeight);
    ofSetFrameRate(60);
    
    choreography.setOverlayLibrary(&overlayLibrary);
    choreography.setSensorLibrary(&sensorLibrary);
    
}
void VideoOverlayer::setVideoInput(VideoSource* newVideoIn)
{
    videoIn = newVideoIn;
    streamWidth = videoIn->getWidth();
    streamHeight = videoIn->getHeight();
}
void VideoOverlayer::setChoreography(const std::string path)
{
    
    std::vector<std::string> startEffects = choreography.loadCueSheet(path);
    std::vector<std::string>::const_iterator startEffect = startEffects.begin();
    for(;startEffect<startEffects.end(); ++startEffect)
        choreography.activateEffect(*startEffect, streamWidth, streamHeight);
}

void VideoOverlayer::update()
{
    if (!videoIn) return;
    
    videoIn->update();
    if (videoIn->isFrameNew())
    {
        if (videoIn->getPixels()) lensImage.setFromPixels(videoIn->getPixels(), streamWidth, streamHeight);
        sensorLibrary.onEnterFrame(&lensImage);
        overlayLibrary.update(&lensImage);
    }
}

std::vector<Effect*> VideoOverlayer::getActiveEffects()
{
    return choreography.getActiveEffects();
}

void VideoOverlayer::draw()
{
    
    float oldWidth = ofGetWidth(), oldHeight = ofGetHeight();
    ofViewport(ofRectangle(0,0, streamWidth, streamHeight));
    /*if (fullScreen)
    {
        ofScale(ofGetScreenWidth()/streamWidth, ofGetScreenHeight()/streamHeight );
    }
    else
    {
        ofScale(1, 1);
    }*/
    setOrthoScale();
	lensImage.draw(0,0);
    unsetOrthoScale();
    
    std::vector<Overlay*> activeOverlays = overlayLibrary.getActiveOverlays();
    for(int i = 0; i < activeOverlays.size(); ++i)
    {
        if (activeOverlays[i]->getGeometry()==Overlay::ORTHO)
        {
            
            setOrthoScale();
            activeOverlays[i]->draw();
            unsetOrthoScale();
        }
        else
        {
            activeOverlays[i]->draw();
        }
    }
    //unsetOrthoScale();
    ofViewport(ofRectangle(0,0,oldWidth, oldHeight));
}

void VideoOverlayer::setOrthoScale()
 {
 glDisable(GL_DEPTH_TEST);
 float scalex = ofGetWidth()/streamWidth;
 float scaley = ofGetHeight()/streamHeight;
 ofPushMatrix();
 ofScale(scalex, scaley);
 }
 
 void VideoOverlayer::unsetOrthoScale()
 {
 ofPopMatrix();
 glEnable(GL_DEPTH_TEST);
 }

std::vector<Overlay*> VideoOverlayer::getActiveOverlays()
{
    return overlayLibrary.getActiveOverlays();
}

std::vector<Sensor*> VideoOverlayer::getActiveSensors()
{
    return sensorLibrary.getActiveSensors();
}

Overlay* VideoOverlayer::getNamedOverlay(const std::string& name)
{
    return overlayLibrary[name];
}

Sensor* VideoOverlayer::getNamedSensor(const std::string& name)
{
    return sensorLibrary[name];
}


void VideoOverlayer::addEffect(const std::string& effectName)
{
    choreography.activateEffect(effectName, streamWidth, streamHeight);
}

void VideoOverlayer::removeEffect(const std::string& effectName)
{
    choreography.removeEffect(effectName);
}

std::vector<std::string> VideoOverlayer::getAllEffectNames()
{
    return choreography.getAllEffectNames();
}

