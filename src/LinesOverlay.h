//
//  LinesOverlay.h
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 14/03/2013.
//
//

#ifndef fullSpectrumAnalyser_LinesOverlay_h
#define fullSpectrumAnalyser_LinesOverlay_h

#include "StageObjectOverlay.h"

class LinesOverlay : public StageObjectOverlay
{
public:
    static const std::string NAME;
    virtual void update(ofxCvColorImage* input);
    virtual void draw();
    virtual void setup(float width, float height);
    virtual std::string getName();
    
    virtual int getGeometry();
    LinesOverlay();
    
};

#endif
