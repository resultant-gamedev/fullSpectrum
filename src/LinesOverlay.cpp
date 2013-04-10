//
//  LinesOverlay.cpp
//  fullSpectrumAnalyser
//
//  Created by Alex Shaw on 14/03/2013.
//
//

#include "LinesOverlay.h"
#include "PoseSensor.h"

const ofColor colorList[] = {
    ofColor(255,0,0),
    ofColor(255,255,0),
    ofColor(0,255,0),
    ofColor(0,255,255),
    ofColor(0,0,255),
    ofColor(255,0,255)};
void renderCube(float size);
const std::string LinesOverlay::NAME = "lines overlay";
void LinesOverlay::update(ofxCvColorImage* input)
{
    StageObjectOverlay::update(input);
}
void LinesOverlay::draw()
{
    PoseSensor * sensor = dynamic_cast<PoseSensor *>(sensors[0]);
    
    float storeProjection[16], storeModelView[16];
    glGetFloatv(GL_PROJECTION_MATRIX, storeProjection);
    glGetFloatv(GL_MODELVIEW_MATRIX, storeModelView);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( sensor->projectionMatrix );
	glMatrixMode(GL_MODELVIEW);
    
	//Draw the object with the estimated pose
	glLoadIdentity();
	glScalef( 1.0f, 1.0f, -1.0f);
	glMultMatrixf( sensor->posePOSIT );
	//glEnable( GL_LIGHTING );
	//glEnable( GL_LIGHT0 );
    
    StageObjectOverlay::draw();    
	/*for (int i = 0; i < sensor->modelPoints.size(); ++i)
    {
        ofSetColor(colorList[i]);
        CvPoint3D32f& pt = sensor->modelPoints[i];
        glPushMatrix();
        glTranslatef(pt.x,pt.y,pt.z);
        ofBox(2);
        renderCube(2);
        glPopMatrix();
    }*/
    
	//renderCube( 10 );
	//glDisable( GL_LIGHTING );
    //glDisable( GL_LIGHT0 );
    //glLoadIdentity();
    
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(storeProjection);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_DEPTH_TEST);
    glLoadMatrixf(storeModelView);
    
    
    
    /*
     ofSetColor(0,255,0);
     for (int i = 0; i < sensor->points.size(); ++i)
    {
        ofSetColor(colorList[i]);
        ofCircle(sensor->points[i], 2);
    }*/
    
    //ofRect(0,0,100,100);
    
    //sensor->lines.draw(0,0);

    ofSetColor(255,255,255);
}
void LinesOverlay::setup(float width, float height)
{
    StageObjectOverlay::setup(width,height);
}
std::string LinesOverlay::getName() {}
LinesOverlay::LinesOverlay() {}


int LinesOverlay::getGeometry() {return ORTHO;}

void renderCube(float size)
{
	glBegin(GL_QUADS);
    // Front Face
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glVertex3f( 0.0f,  0.0f,  0.0f);
    glVertex3f( size,  0.0f,  0.0f);
    glVertex3f( size,  size,  0.0f);
    glVertex3f( 0.0f,  size,  0.0f);
    // Back Face
    glNormal3f( 0.0f, 0.0f,-1.0f);
    glVertex3f( 0.0f,  0.0f, size);
    glVertex3f( 0.0f,  size, size);
    glVertex3f( size,  size, size);
    glVertex3f( size,  0.0f, size);
    // Top Face
    glNormal3f( 0.0f, 1.0f, 0.0f);
    glVertex3f( 0.0f,  size,  0.0f);
    glVertex3f( size,  size,  0.0f);
    glVertex3f( size,  size, size);
    glVertex3f( 0.0f,  size, size);
    // Bottom Face
    glNormal3f( 0.0f,-1.0f, 0.0f);
    glVertex3f( 0.0f,  0.0f,  0.0f);
    glVertex3f( 0.0f,  0.0f, size);
    glVertex3f( size,  0.0f, size);
    glVertex3f( size,  0.0f,  0.0f);
    // Right face
    glNormal3f( 1.0f, 0.0f, 0.0f);
    glVertex3f( size,  0.0f, 0.0f);
    glVertex3f( size,  0.0f, size);
    glVertex3f( size,  size, size);
    glVertex3f( size,  size, 0.0f);
    // Left Face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f( 0.0f,  0.0f, 0.0f);
    glVertex3f( 0.0f,  size, 0.0f);
    glVertex3f( 0.0f,  size, size);
    glVertex3f( 0.0f,  0.0f, size);
    glEnd();
}