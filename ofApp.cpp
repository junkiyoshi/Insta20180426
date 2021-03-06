#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(39);
	ofSetWindowTitle("Insta");

	ofSetLineWidth(2);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);
	ofRotateZ(35);

	float noise_x_param = ofRandom(1000);
	float noise_y_param = ofRandom(1000);
	float noise_threshold_high = 0.65;
	float noise_threshold_low = 0.35;
	for (int z = -300; z <= 300; z += 10) {

		ofPushMatrix();
		
		float noise_x_value = ofNoise(noise_x_param + z * 0.005 - ofGetFrameNum() * 0.05);
		float noise_y_value = ofNoise(noise_y_param + z * 0.005 - ofGetFrameNum() * 0.05);

		if (noise_x_value > noise_threshold_high) {

			ofTranslate(ofMap(noise_x_value, noise_threshold_high, 1.0, 0, 500), 0);
		}
		else if (noise_x_value < noise_threshold_low) {

			ofTranslate(ofMap(noise_x_value, 0.0, noise_threshold_low, -500, 0), 0);
		}

		if (noise_y_value > noise_threshold_high) {

			ofTranslate(0, ofMap(noise_y_value, noise_threshold_high, 1.0, 0, 500));
		}
		else if (noise_y_value < noise_threshold_low) {

			ofTranslate(0, ofMap(noise_y_value, 0.0, noise_threshold_low, -500, 0));
		}

		this->draw_hexagon(ofPoint(), 300, z);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::draw_hexagon(ofPoint center, float radius, float z) {

	for (int deg = 0; deg < 360; deg += 60) {

		ofPoint start = ofPoint(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), z);
		ofPoint end = ofPoint(radius * cos((deg + 60) * DEG_TO_RAD), radius * sin((deg + 60) * DEG_TO_RAD), z);
		ofPoint distance = end - start;
		float len = distance.length();
		distance.normalize();

		for (int l = 0; l < len; l++) {

			ofPoint p1 = start + l * distance;
			ofPoint p2 = start + (l + 1) * distance;

			ofSetColor(239, ofMap(p1.y, -radius, radius, 255, 25));
			ofDrawLine(p1, p2);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}