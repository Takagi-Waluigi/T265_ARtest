#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "InstancedParticle.h"

#include <rs.hpp>
#include <rsutil.h>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofVec3f pos;
		ofVec3f rot;
		bool t265_Status;

		ofVideoGrabber webCam;

		ofEasyCam eCam;
		ofCamera cam;

		ofxPanel gui;
		ofParameter<float> cameraFov;
		bool visibleGUI = true;


		InstancedParticle particle;



private:
	static const int FISH_EYE_SENSOR_USE_INDEX = 1;

	rs2::pipeline pipe;
	rs2::config cfg;
	rs2::pipeline_profile pipe_profile;
	rs2::stream_profile fisheye_stream;
	rs2_intrinsics intrinsics;
	rs2_extrinsics extrinsics;
	rs2_pose device_pose_in_world;
};
