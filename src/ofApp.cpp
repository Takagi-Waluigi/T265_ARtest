#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(0);
    //T265 setup 
    {
        HRESULT hr = true;

        if (SUCCEEDED(hr))
        {
            //cfg.enable_all_streams();
            cfg.enable_stream(RS2_STREAM_POSE, RS2_FORMAT_6DOF);
            cfg.enable_stream(RS2_STREAM_FISHEYE, 1);
            cfg.enable_stream(RS2_STREAM_FISHEYE, 2);
            pipe_profile = pipe.start(cfg);

            if (pipe_profile != NULL)
            {
                t265_Status = true;
                cout << "succeeded to open device" << endl;
                hr = true;
            }
            else
            {
                cout << "failed to open device" << endl;
            }
        }

        if (SUCCEEDED(hr))
        {
            cout << "setup device" << endl;
            fisheye_stream = pipe_profile.get_stream(RS2_STREAM_FISHEYE, FISH_EYE_SENSOR_USE_INDEX);
            intrinsics = fisheye_stream.as<rs2::video_stream_profile>().get_intrinsics();
            extrinsics = fisheye_stream.get_extrinsics_to(pipe_profile.get_stream(RS2_STREAM_POSE));
        }
    }

    //WebCamera
    {
        webCam.listDevices();
        webCam.setDeviceID(1);
        webCam.initGrabber(1280, 720);
       
    }

    //Mesh Instancing
    particle.setup();

    //GUI
    {
        gui.setup();
        
        cameraFov.set("Fov", 45, 0, 180);

        gui.add(cameraFov);
        gui.add(particle.lightPosition);
        gui.add(particle.lightColor);
        gui.add(particle.ambientColor);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    //Update Data from T265
    {
        if (t265_Status)
        {

            auto frames = pipe.wait_for_frames();
            rs2::video_frame fisheye_frame = frames.get_fisheye_frame(FISH_EYE_SENSOR_USE_INDEX);
            rs2::pose_frame pose_frame = frames.get_pose_frame();
            device_pose_in_world = pose_frame.get_pose_data();


            pos.x = device_pose_in_world.translation.x * 10000;
            pos.y = device_pose_in_world.translation.y * 10000;
            pos.z = device_pose_in_world.translation.z * 10000;


            ofQuaternion q = ofQuaternion(device_pose_in_world.rotation.x,
                device_pose_in_world.rotation.y,
                device_pose_in_world.rotation.z,
                device_pose_in_world.rotation.w);


            rot.x = q.getEuler().x;
            rot.y = q.getEuler().y;
            rot.z = q.getEuler().z;

        }
    }

    {
        webCam.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //WebCam
    {
        ofSetColor(255);
        webCam.draw(0, 0);
    }

    ofEnableDepthTest();
    
    ofPushMatrix();
    //CameraBegin
    {
        cam.setFov(cameraFov);
        cam.setGlobalPosition(pos);
        cam.lookAt(glm::vec3(pos.x, pos.y, pos.z - 10));
        cam.rotateDeg(rot.y, glm::vec3(0, 1, 0));
        cam.tilt(rot.x);
        cam.roll(rot.z);
        cam.begin();
    }
    particle.draw();
    /*
    //Draw Grid
    {
        ofPushMatrix();
        ofRotateX(90);
        ofNoFill();
        ofSetColor(255);
        int gridNum = 50;
        int gridSize = 50;
        for (int x = 0; x < gridNum; x++)
        {
            for (int y = 0; y < gridNum; y++)
            {
                ofDrawRectangle((x - gridNum / 2) * gridSize, (y - gridNum / 2) * gridSize, gridSize, gridSize);
            }
        }

        ofFill();
        ofPopMatrix();
    }
    */

    {
        cam.end();
    }
    ofDisableDepthTest();
    ofPopMatrix();

    if (visibleGUI)
    {
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') visibleGUI = !visibleGUI;
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
