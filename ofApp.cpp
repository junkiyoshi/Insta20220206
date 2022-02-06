#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofSetLineWidth(3);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->line.clear();

	float R = 250;
	float r = R * 0.25;
	float v_step = 5;

	for (float v = 0; v < 360; v += v_step) {

		float u_start = ofMap(ofNoise(glm::vec3(cos(v * DEG_TO_RAD) * 0.85, sin(v * DEG_TO_RAD) * 0.85, ofGetFrameNum() * 0.01)), 0, 1, -360,360);
		ofColor face_color;
		float hue = ofMap(v, 0, 360, 0, 255);
		face_color.setHsb(hue, 130, 255);

		vector<glm::vec3> vertices;
		for (float u = u_start; u < u_start + 360; u += 90) {

			vertices.push_back(glm::vec3(this->make_point(R, r, u, v)));
		}

		this->face.addVertices(vertices);
		this->line.addVertices(vertices);

		this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 2); this->face.addIndex(this->face.getNumVertices() - 3);
		this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 3); this->face.addIndex(this->face.getNumVertices() - 4);

		this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
		this->line.addIndex(this->line.getNumVertices() - 2); this->line.addIndex(this->line.getNumVertices() - 3);
		this->line.addIndex(this->line.getNumVertices() - 3); this->line.addIndex(this->line.getNumVertices() - 4);
		this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 4);

		for (int i = 0; i < vertices.size(); i++) {

			this->face.addColor(face_color);
			this->line.addColor(ofColor(255));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofRotateY(ofGetFrameNum() * 1.333333333333333333);

	this->line.drawWireframe();
	this->face.draw();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}