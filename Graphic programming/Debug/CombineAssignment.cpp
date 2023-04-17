
#include <Windows.h>
#include <gl/GL.h>
#include <Math.h>
#include <gl/GLU.h>
#define WINDOW_TITLE "Robot"

//SKYBOX
GLuint skyboxArr[6];

//TEXTURE
//Step 1: Variable declaration
BITMAP BMP;				//bitmap structure
HBITMAP hBMP = NULL;	//bitmap handle
GLuint textureArr[5];  //texture array
bool onTexture = true;


//LIGHTING
//lighting
float lx, ly, lz = 0;
float amb[] = { 1, 1, 1 };		//white ambient
float dif[] = { 1, 1, 1 };		//white diffuse
float posA[] = { lx, ly, lz };		//above	(0,	1, 0)
float posD[] = { lx, ly, lz };		//right
float lSpeed = 10;
boolean lightType = false;
float difM[] = { 1.0, 0.0, 0.0 };		//red
float ambM[] = { 0.38, 0.38, 0.38 }; //dark grey
bool isLightOn = false;					//is light on?
boolean drill = false;





//STRAIGHT AWAY COPY THE DECLARATION ---------------------------------------------------------------------
float tx = 0.0, tz = 0.0, tSpeed = 1.0;
boolean isOrtho = true;
float oNear = -100.0, oFar = 100.0;
float pNear = 101, pFar = 301.0;
float ptx = 0.0, pty = 0.0, ptSpeed = 0.1;
float pry = 0.0, prSpeed = 1.0;
float rs1 = 3.0;
//ZF
float rxLeg = 1;
float rxBotFoot, rxFoot = 0.0;
float rxLeftLeg, rxRightLeg, rxLeftBotFoot, rxRightBotFoot, rxLeftFoot, rxRightFoot = 0.0;
float speed = 2;
int qNo = 1;
float z = 0;
boolean reach = true;
float zoom = 0;
float rrobot = 0;
float aSpeed = 2;
float dSpeed = 2;

float x = 0, y = 0; //origin of circle  (x,y) (0,0)
float radius = 2; //radius of circle 
float angle = 0; //angle of circle 
float PI = 3.1429; //PI 
float x2 = 0, y2 = 0; //point on the circle (x2,y2) 
float noOfTri = 36;  //no of triangles


//WJ
float rSpeed = 0;
float turn = -50;		//whole robot rotation
float rLwArm = 0;	//lower arm rotation angle
float rUpArm = 0;	//upper arm rotation angle
float rWrist = 0;	//wrist rotation angle
float rLwArmLeft = 0;	//left lower arm rotation angle
float rUpArmLeft = 0;	//left upper arm rotation angle
float rWristLeft = 0;	//left wrist rotation angle
float rPalmLeft = 0;	//whole Left Palm rotation angle
float rPalm = 0;	//whole Palm rotation angle
float rUpPalm = 0;	//upper Palm rotation angle
float rLwPalm = 0;	//lower Palm rotation angle
float rLwPalmLeft = 0;  //lower left Palm rotation angle
float rThumb = 0;	//thumb rotation angle
float rThumbLeft = 0;	//left thumb rotation angle
float rFingers = 0;	//all fingers rotation 
float rFinger1 = 0;	//finger1 rotation 
float rFingerRoot = 0;	//finger root  rotation angle
float rFingerMiddle = 0;	//finger middle  rotation angle
float rFingerTip = 0;	//finger tip rotation angle
float rFingerRootLeft = 0;	//left finger root  rotation angle
float rFingerMiddleLeft = 0;	//left finger middle  rotation angle
float rFingerTipLeft = 0;	//left finger tip rotation angle
float rFinger2 = 0;	//finger2 rotation angle
float rFinger3 = 0;	//finger3 rotation angle
float rFinger4 = 0;	//finger4 rotation angle
bool moveFinger = false;
bool moveArm = false;
boolean reach2 = false;
boolean reach3 = false;
bool walking = false;
bool jumping = false;
bool moveLeg = false;
bool onLaser = false;
float rLaser = 0;
bool moveLaser = false;
//YX
float rc = 0;
float rotateCone = 0;
float cSpeed = 0.0;
float xh = 0;
float yh = 0.5;
float hSpeed = 1.0;
float rh = 0.0;
float x3, y3, z3 = 0;


boolean activateW = false;
boolean activateS = false;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{ //interactive 
	switch (msg)
	{
	case WM_DESTROY: //press the X button (close window) 
		PostQuitMessage(0); //close window 
		break;

	case WM_KEYDOWN: //press the key 
		if (wParam == VK_ESCAPE) // vk=virtual key esc key 
			PostQuitMessage(0); //close window 
		if (wParam == VK_TAB) { //zoom in
			if (isOrtho) {
				if (zoom < 90) {
					zoom += speed;
				}
			}
			else {
				if (zoom <= 55) {
					zoom += speed;
				}
			}
		}
		if (wParam == VK_CAPITAL) { //zoom out
			if (isOrtho) {
				if (zoom >= -90) {
					zoom -= speed;
				}
			}
			else {
				if (zoom >= -120) {
					zoom -= speed;
				}
			}

		}
		else if (wParam == '0') { //walking 
			walking = !walking;
			rLwArm = 0;
			rLwArmLeft = 0;
		}
		else if (wParam == VK_F5) { //laser
			onLaser = !onLaser;
		}
		else if (wParam == VK_F3) {   //move laser
			if (!moveLaser) {
				if (rLaser < 45 && rLaser >= -45) {
					rLaser += 5;
				}
				else
					moveLaser = true;
			}
			else {
				if (rLaser >= -44 && rLaser <= 46) {
					rLaser -= 5;
				}
				else
					moveLaser = false;
			}
		}
		else if (wParam == VK_F4) {    //turn on turn off texture
			onTexture = !onTexture;
			if (!onTexture) {
				//Step 5: Remove texture info
				glDisable(GL_TEXTURE_2D);
			}
		}
		else if (wParam == 'R') {
			if (rxLeftBotFoot < 90 && rxLeftBotFoot >= -46) {
				rxLeftBotFoot += speed;
			}
		}
		else if (wParam == 'F') {
			if (rxLeftBotFoot <= 90 && rxLeftBotFoot > -44.4) {
				rxLeftBotFoot -= speed;
			}
		}
		else if (wParam == 'T') {
			if (rxRightBotFoot < 90 && rxRightBotFoot >= -46) {
				rxRightBotFoot += speed;
			}
		}
		else if (wParam == 'G') {
			if (rxRightBotFoot <= 90 && rxRightBotFoot > -44.4) {
				rxRightBotFoot -= speed;
			}
		}
		else if (wParam == 'Y') {
			if (rxLeftFoot < 44 && rxLeftFoot >= 0) { //(rxLeftFoot < 89 && rxLeftFoot >= -45)
				rxLeftFoot += speed;
			}
		}
		else if (wParam == 'H') {
			if (rxLeftFoot <= 45 && rxLeftFoot > 0.1) { //(rxLeftFoot <= 90 && rxLeftFoot > -44.4)
				rxLeftFoot -= speed;
			}
		}
		else if (wParam == 'Q') {
			if (rxRightFoot < 44 && rxRightFoot >= 0) {
				rxRightFoot += speed;
			}
		}
		else if (wParam == 'E') {
			if (rxRightFoot <= 45 && rxRightFoot > 0.1) {
				rxRightFoot -= speed;
			}
		}
		else if (wParam == '1') {//
			isOrtho = true;
			z = 0;
			ptx = 0.0;
			pty = 0.0;
			zoom = 0;
		}
		else if (wParam == '2') {// 
			zoom = 0;
			isOrtho = false;
			ptx = 0.0;
			pty = 0.0;
			z = pNear + rs1; //+3.0(radius) to avoid the camera in side the obj
		}
		else if (wParam == VK_LEFT) {// camera move to left
			if (isOrtho) {
				if (ptx > -0.28 || ptx == 0) {
					ptx -= ptSpeed;
				}
			}
			else {

				if (ptx > -0.5 || ptx == 0) {
					ptx -= ptSpeed;
				}
			}


		}
		else if (wParam == VK_RIGHT) {// camera move to right
			if (isOrtho) {
				if (ptx < 0.28 || ptx == 0) {
					ptx += ptSpeed;
				}
			}
			else {

				if (ptx < 0.5 || ptx == 0) {
					ptx += ptSpeed;
				}
			}
		}
		else if (wParam == VK_UP) {// camera move to up
			if (isOrtho) {
				if (pty < 0.1 || pty == 0) {
					pty += ptSpeed;
				}
			}
			else {

				if (pty < 0.3 || pty == 0) {
					pty += ptSpeed;
				}
			}
		}
		else if (wParam == VK_DOWN) {// camera move to down 
			if (isOrtho) {
				if (pty > -0.1 || pty == 0) {
					pty -= ptSpeed;
				}
			}
			else {

				if (pty > -0.3 || pty == 0) {
					pty -= ptSpeed;
				}
			}
		}
		else if (wParam == '4') {// rotate the camara along y axis 
			pry += prSpeed;
		}
		else if (wParam == '3') {// rotate the camera along t axis
			pry -= prSpeed;
		}
		//------------------------------------------------------------------------------------------------------------------------------------
		//WJ
		else if (wParam == VK_F1) {					//move lower arm forward and backward (continuous)
			if (!moveArm) {
				if (rLwArm < 75 && rLwArmLeft > -75) {
					rSpeed = 2;
					rLwArm += rSpeed;
					rLwArmLeft -= rSpeed;
				}
				else {
					rLwArm = rLwArm;
					moveArm = true;
				}
			}
			else {
				if (rLwArm >= -74 || rLwArm >= 74) {
					rSpeed = 2;
					rLwArm -= rSpeed;
					rLwArmLeft += rSpeed;
				}
				else {
					rLwArm = rLwArm;
					moveArm = false;
				}
			}
		}
		else if (wParam == 'Z') {					//move lower arm backward
			if (rLwArm <= 0) {
				rSpeed = 1;
				rLwArm += rSpeed;
				rLwArmLeft += rSpeed;
			}
			else {
				rLwArm = rLwArm;
				rLwArmLeft = rLwArmLeft;
			}
		}
		else if (wParam == 'X') {					//move lower arm forward
			if (rLwArm >= -120 || rLwArm >= 120) {
				rSpeed = 1;
				rLwArm -= rSpeed;
				rLwArmLeft -= rSpeed;
				if (rWrist > -40) {
					rSpeed = 1;
					rWrist -= rSpeed;
					rWristLeft -= rSpeed;
				}
				else {
					rWrist = rWrist;
					rWristLeft = rWristLeft;
				}
			}
			else {
				rLwArm = rLwArm;
				rLwArmLeft = rLwArmLeft;
				rWrist = rWrist;
			}
			if (rUpArm >= 0 || rUpArm >= 15) {
				rSpeed = 1;
				rUpArm -= rSpeed;
			}
			else {
				rUpArm = rUpArm;
			}
		}
		else if (wParam == 'C') {				//move wrist and palm forward
			if (rWrist < 8) {
				rSpeed = 1;
				rWrist += rSpeed;
				rWristLeft += rSpeed;
			}
			else {
				rWrist = rWrist;
				rWristLeft = rWristLeft;
			}
		}
		else if (wParam == 'V') {				//move wrist and palm backward
			if (rWrist >= -5 || rWrist >= 9) {
				rSpeed = 1;
				rWrist -= rSpeed;
				rWristLeft -= rSpeed;
			}
			else {
				rWrist = rWrist;
				rWristLeft = rWristLeft;
			}
		}
		else if (wParam == 'N') {			//palm rotate front
			if (rPalm < 90) {
				rSpeed = 1;
				rPalm += rSpeed;
				rPalmLeft += rSpeed;
			}
			else {
				rPalm = rPalm;
				rPalmLeft = rPalmLeft;
			}
		}
		else if (wParam == 'B') {						//palm rotate back
			if (rPalm >= 0 || rPalm >= 89) {
				rSpeed = 1;
				rPalm -= rSpeed;
				rPalmLeft -= rSpeed;
			}
			else {
				rPalm = rPalm;
				rPalmLeft = rPalmLeft;
			}
		}
		else if (wParam == 'M') {			//all finger move
			if (!moveFinger) {
				if (rFingerTip > -45) {
					rSpeed = 1;
					rFingerTip -= rSpeed;
					rFingerMiddle -= rSpeed;
					rFingerTipLeft += rSpeed;
					rFingerMiddleLeft += rSpeed;
					rLwPalm += rSpeed;
					rLwPalmLeft -= rSpeed;
					rFingers -= rSpeed;
					rThumb -= rSpeed;
					rThumbLeft += rSpeed;
					/*rFinger2 += rSpeed;
					rFinger3 += rSpeed;
					rFinger4 += rSpeed;*/
					if (rFingerRoot > -20) {
						rFingerRoot -= rSpeed;
						rFingerRootLeft += rSpeed;
					}
				}
				else {
					rFingerTip = rFingerTip;
					rFingerMiddle = rFingerMiddle;
					rFingerRoot = rFingerRoot;
					rLwPalm = rLwPalm;
					rLwPalmLeft = rLwPalmLeft;
					rFingers = rFingers;
					rThumb = rThumb;
					rThumbLeft = rThumbLeft;
					rFingerTipLeft = rFingerTipLeft;
					rFingerMiddleLeft = rFingerMiddleLeft;
					rFingerRootLeft = rFingerRootLeft;
					moveFinger = true;
					/*rFinger2 = rFinger2;
					rFinger3 = rFinger3;
					rFinger4 = rFinger4;*/
				}
			}
			else {
				if (rFingerTip <= 0) {
					rSpeed = 1;
					rFingerTip += rSpeed;
					rFingerMiddle += rSpeed;
					rFingerTipLeft -= rSpeed;
					rFingerMiddleLeft -= rSpeed;
					rLwPalm -= rSpeed;
					rFingers += rSpeed;
					rThumb += rSpeed;
					rThumbLeft -= rSpeed;
					rLwPalmLeft += rSpeed;
					/*rFinger2 += rSpeed;
					rFinger3 += rSpeed;
					rFinger4 += rSpeed;*/
					if (rFingerRoot <= 0) {
						rFingerRoot += rSpeed;
						rFingerRootLeft -= rSpeed;
					}
				}
				else {
					rFingerTip = rFingerTip;
					rFingerMiddle = rFingerMiddle;
					rFingerRoot = rFingerRoot;
					rLwPalm = rLwPalm;
					rLwPalmLeft = rLwPalmLeft;
					rFingers = rFingers;
					rThumb = rThumb;
					rThumbLeft = rThumbLeft;
					moveFinger = false;
					rFingerTipLeft = rFingerTipLeft;
					rFingerMiddleLeft = rFingerMiddleLeft;
					rFingerRootLeft = rFingerRootLeft;
					/*rFinger2 = rFinger2;
					rFinger3 = rFinger3;
					rFinger4 = rFinger4;*/
				}
			}
		}
		/////////////////////////////////???????????????????????????????????????????????????????????
		/*else if (wParam == 'M') {
			moveArm = true;
		}*/
		/////////////////////////////////???????????????????????????????????????????????????????????
		else if (wParam == VK_SPACE) {	//reset
			rSpeed = 2;
			turn = -50;
			rLwArm = 0;
			rUpArm = 0;
			rWrist = 0;
			rLwArmLeft = 0;
			rUpArmLeft = 0;
			rWristLeft = 0;
			rPalmLeft = 0;
			rPalm = 0;
			rFinger1 = 0;
			rFinger2 = 0;
			rFinger3 = 0;
			rFinger4 = 0;
			rFingerTip = 0;
			rFingerMiddle = 0;
			rFingerRoot = 0;
			rFingers = 0;
			rThumb = 0;
			rThumbLeft = 0;
			rLwPalm = 0;
			rLwPalmLeft = 0;
			rFingerTipLeft = 0;
			rFingerMiddleLeft = 0;
			rFingerRootLeft = 0;
			activateW = false;
			activateS = false;
			rxLeg = 1;
			rxBotFoot = 0.0;
			rxFoot = 0.0;
			rxLeftLeg = 0.0;
			rxRightLeg = 0.0;
			rxLeftBotFoot = 0.0;
			rxRightBotFoot = 0.0;
			rxLeftFoot = 0.0;
			rxRightFoot = 0.0;
			speed = 1;
			qNo = 1;
			rrobot = 0;
			dSpeed = 2;
			aSpeed = 2;
			cSpeed = 0; 
			drill = false;
			if (!isOrtho) {
				z = pNear + rs1;
			}
			else {
				z = 0;
			}
			reach = true;
			zoom = 0;
			ptx = 0;
			pty = 0;
			xh = 0;
			yh = 0;
			rh = 0;
			pry = 0;
			walking = false;
			rLaser = 0;
			onLaser = false;
		}
		//------------------------------------------------------------------------------------------------------------------------------------
		//YX
		else if (wParam == 'U') {//left rotate robot 
			rrobot += speed;
		}
		else if (wParam == 'O') { //right rotate robot 
			rrobot -= speed;
		}
		else if (wParam == VK_F6) { //SPIN CORN
		drill = !drill; 
		if (drill) {
			cSpeed = 20;
			}
		else {
			cSpeed = 0;
		}
			
		}
		else if (wParam == 'S') { //move head down
			if (rh <= 45 && rh > -30) {
				rh -= hSpeed;
			}
		}

		else if (wParam == 'W') { //move head up
			if (rh < 44 && rh >= -30.1) {
				rh += hSpeed;
			}

		}
		else if (wParam == 'A') { //move head left
			xh -= 1.0;
		}
		else if (wParam == 'D') { //move head right 
			xh += 1.0;
		}
		//else if (wParam == VK_DELETE) {  //reset
		//	xh = 0;
		//	yh = 0;
		//	rh = 0;
		//}


		else if (wParam == '6') {  //attack
			activateW = !activateW;
			if (activateW == false) {
				aSpeed = 0;
			}
			activateS = false;
			rLwArm = 0;
			rLwPalm = 0;
			rLwPalmLeft = 0;
			//rSpeed = 1;
			rFingerTip = -90;
			rFingerMiddle = -90;
			rFingerTipLeft = 90;
			rFingerMiddleLeft = 90;
			/*rLwPalm += rSpeed;
			rLwPalmLeft -= rSpeed;*/
			rFingers = -90;
			rThumb = -90;
			rThumbLeft = 90;
			/*rFinger2 += rSpeed;
			rFinger3 += rSpeed;
			rFinger4 += rSpeed;*/
			//if (rFingerRoot > -20) {
			rFingerRoot = -20;
			rFingerRootLeft = -20;
			//}
		}
		else if (wParam == '5') {  //deffense

			activateW = false;
			activateS = !activateS;
			if (activateS == false) {
				dSpeed = 0;
			}
			rLwArmLeft = 0;
			rLwPalm = 0;
			rLwPalmLeft = 0;
			//rSpeed = 1;
			rFingerTip = -90;
			rFingerMiddle = -90;
			rFingerTipLeft = 90;
			rFingerMiddleLeft = 90;
			/*rLwPalm += rSpeed;
			rLwPalmLeft -= rSpeed;*/
			rFingers = -90;
			rThumb = -90;
			rThumbLeft = 90;
			/*rFinger2 += rSpeed;
			rFinger3 += rSpeed;
			rFinger4 += rSpeed;*/
			//if (rFingerRoot > -20) {
			rFingerRoot = -20;
			rFingerRootLeft = -20;
			//}
		}
		//lighting
		else if (wParam == VK_DELETE) { //switch on the light
			lightType = !lightType;
		}
		else if (wParam == '7') {
			isLightOn = !isLightOn;		//swtich on ambient and diffuse
			lightType = false;
		}
		else if (wParam == '9') {
			lz -= lSpeed;
			posA[2] = lz;
		}
		else if (wParam == '8') {
			lz += lSpeed;
			posA[2] = lz;
		}
		else if (wParam == 'J') {
			lx -= lSpeed;
			posA[0] = lx;
		}
		else if (wParam == 'L') {
			lx += lSpeed;
			posA[0] = lx;
		}
		else if (wParam == 'I') {
			ly += lSpeed;
			posA[1] = ly;
		}
		else if (wParam == 'K') {
			ly -= lSpeed;
			posA[1] = ly;
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}


//--------------------------------------------------------------------
//TEXTURE
GLuint loadTexture(LPCSTR filename) {

	//Take fromStep 1
	GLuint texture = 0;  //texture name

	//Step 3: Initialize texture info
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	//Step 4: Assign texture to pulygon

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Take from Step 5
	DeleteObject(hBMP);

	return texture;
}
//new
//lighting
void lighting() {
	if (isLightOn) {
		//glRotatef(ay, 0, 1, 0);
		glEnable(GL_LIGHTING);		//Enable the lighthing for the whole scene
		glDisable(GL_LIGHT0);
	}
	else if (lightType) {
		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT0, GL_POSITION, posA);
		glEnable(GL_LIGHT0);
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambM);
	}
	else {
		glDisable(GL_LIGHTING);		//Disable the lighthing
	}
}

void initSkybox() {
	skyboxArr[0] = loadTexture("skytop.bmp");
	skyboxArr[1] = loadTexture("skybottom.bmp");
	skyboxArr[2] = loadTexture("skyfront.bmp");
	skyboxArr[3] = loadTexture("skyback.bmp");
	skyboxArr[4] = loadTexture("skyleft.bmp");
	skyboxArr[5] = loadTexture("skyright.bmp");
}

void killSkybox() {
	glDeleteTextures(6, &skyboxArr[0]);
}

void drawSkybox(float sz) {

	if (onTexture && !isLightOn) {
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);

		//camera frame

	
		glMatrixMode(GL_PROJECTION); // refer to the projection matrix 
		glLoadIdentity(); //reset the projection matrix 
		if(!isOrtho) {
			glTranslatef(ptx, pty, 0.0); //move the camera to left right and up down
		}
		//glRotatef(pry, 0.0, 1.0, 0.0); //rotate the camera to view different angle
		if (isOrtho) {
			glOrtho(-100.0, 100.0, -100.0, 100.0, oNear, oFar); //change the viewing x-axis = -10 to +10

		}
		else {
			//viewing frustum try to use smaller than ortho eg: 100/2 = glFrustum(50 -50, 50, -50, 5-,.....)
			gluPerspective(60, 1.0, -3, 5);
			glFrustum(-50.0, 50.0, -50.0, 50.0, pNear, pFar); //-10 - 10 = 20 21 - 1 = 20 same
		}


		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		if (!isOrtho) {
			glTranslatef(0, 0, zoom);
			glRotatef(pry, 0.0, 1.0, 0.0); //rotate the camera to view different angle
			glTranslatef(0, 0, -zoom);
			glTranslatef(0, 0, zoom);
		}
		lighting();
		glColor3f(1, 1, 1);


		glBindTexture(GL_TEXTURE_2D, skyboxArr[3]);
		glBegin(GL_QUADS);
		// Face 1 (back face)
		glTexCoord2f(0.0, 0.0);   //skybox text 1
		glVertex3f(sz / 2, sz / 2, sz / 2);
		glTexCoord2f(1.0, 0.0); //skybox text 2
		glVertex3f(-sz / 2, sz / 2, sz / 2);
		glTexCoord2f(1.0, 1.0);  //skybox text 3
		glVertex3f(-sz / 2, -sz / 2, sz / 2);
		glTexCoord2f(0.0, 1.0);  //skybox text 4
		glVertex3f(sz / 2, -sz / 2, sz / 2);
		glEnd();


		glBindTexture(GL_TEXTURE_2D, skyboxArr[4]);
		// Face 2 (left face)
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);   //skybox text 1
		glVertex3f(-sz / 2, sz / 2, sz / 2);
		glTexCoord2f(1.0, 0.0); //skybox text 2
		glVertex3f(-sz / 2, sz / 2, -sz / 2);
		glTexCoord2f(1.0, 1.0);  //skybox text 3
		glVertex3f(-sz / 2, -sz / 2, -sz / 2);
		glTexCoord2f(0.0, 1.0);  //skybox text 4
		glVertex3f(-sz / 2, -sz / 2, sz / 2);
		glEnd();


		glBindTexture(GL_TEXTURE_2D, skyboxArr[2]);
		//face 3 (front face)
		glBegin(GL_QUADS);
		glTexCoord2f(1.0, 0.0);   //skybox text 1
		glVertex3f(sz / 2, sz / 2, -sz / 2);
		glTexCoord2f(0.0, 0.0); //skybox text 2
		glVertex3f(-sz / 2, sz / 2, -sz / 2);
		glTexCoord2f(0.0, 1.0);  //skybox text 3
		glVertex3f(-sz / 2, -sz / 2, -sz / 2);
		glTexCoord2f(1.0, 1.0);  //skybox text 4
		glVertex3f(sz / 2, -sz / 2, -sz / 2);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, skyboxArr[5]);
		//face 4 (right face) 
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);   //skybox text 1
		glVertex3f(sz / 2, sz / 2, -sz / 2);
		glTexCoord2f(1.0, 0.0); //skybox text 2
		glVertex3f(sz / 2, sz / 2, sz / 2);
		glTexCoord2f(1.0, 1.0);  //skybox text 3
		glVertex3f(sz / 2, -sz / 2, sz / 2);
		glTexCoord2f(0.0, 1.0);  //skybox text 4
		glVertex3f(sz / 2, -sz / 2, -sz / 2);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, skyboxArr[1]);
		//face 5 (top face)
		glBegin(GL_QUADS);
		glTexCoord2f(1.0, 0.0);   //skybox text 1
		glVertex3f(sz / 2, sz / 2, sz / 2);
		glTexCoord2f(0.0, 0.0); //skybox text 2
		glVertex3f(-sz / 2, sz / 2, sz / 2);
		glTexCoord2f(0.0, 1.0);  //skybox text 3
		glVertex3f(-sz / 2, sz / 2, -sz / 2);
		glTexCoord2f(1.0, 1.0);  //skybox text 4
		glVertex3f(sz / 2, sz / 2, -sz / 2);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, skyboxArr[0]);
		//face 6 (bottom face)
		glBegin(GL_QUADS);
		glTexCoord2f(1.0, 1.0);   //skybox text 1
		glVertex3f(sz / 2, -sz / 2, sz / 2);
		glTexCoord2f(0.0, 1.0); //skybox text 2
		glVertex3f(-sz / 2, -sz / 2, sz / 2);
		glTexCoord2f(0.0, 0.0);  //skybox text 3
		glVertex3f(-sz / 2, -sz / 2, -sz / 2);
		glTexCoord2f(1.0, 0.0);  //skybox text 4
		glVertex3f(sz / 2, -sz / 2, -sz / 2);
		glEnd();
		glPopMatrix();


		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);
	}

}
//new
void drawCube(float sz) {
	glBegin(GL_QUADS);
	// Face 1 (bottom face)
	//glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(sz, 0.0f, sz);
	glVertex3f(sz, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	// Face 2 (left face)
	//glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(0.0f, sz, sz);
	glVertex3f(0.0f, 0.0f, sz);
	//face 3 (front face)
	//glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0f, 0.0f, sz);
	glVertex3f(0.0f, sz, sz);
	glVertex3f(sz, sz, sz);
	glVertex3f(sz, 0.0f, sz);
	//face 4 (right face) 
	//glColor3f(1.0, 1.0, 0.0);
	glVertex3f(sz, 0.0f, sz);
	glVertex3f(sz, sz, sz);
	glVertex3f(sz, sz, 0.0f);
	glVertex3f(sz, 0.0f, 0.0f);
	//face 5 (back face)
	//glColor3f(1.0, 0.0, 1.0);
	glVertex3f(sz, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(sz, sz, 0.0f);
	//face 6 (top face)
	//glColor3f(0.0, 1.0, 1.0);
	glVertex3f(sz, sz, 0.0f);
	glVertex3f(0.0f, sz, 0.0f);
	glVertex3f(0.0f, sz, sz);
	glVertex3f(sz, sz, sz);
	glEnd();
}   //new
void drawPyramid(float size) {
	glLineWidth(5.0);
	glBegin(GL_QUADS);
	//Face 1 (bottom quad)
	glColor3f(1, 0.75, 0.9);
	glVertex3f(0, 0, size);
	glVertex3f(size, 0, size);
	glVertex3f(size, 0, 0);
	glVertex3f(0, 0, 0);
	glEnd();
	//Face 2 (tri)
	glBegin(GL_TRIANGLES);
	glColor3f(0.55, 0.75, 0.9);
	glVertex3f(0, 0, 0);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(0, 0, size);
	//Face 3 (tri)
	glVertex3f(0, 0, size);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(size, 0, size);
	//Face 4 (tri)
	glVertex3f(size, 0, size);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(size, 0, 0);
	//Face 5 (tri)
	glVertex3f(size, 0, 0);
	glVertex3f(size / 2, size, size / 2);
	glVertex3f(0, 0, 0);
	glEnd();
}

//new
void drawCuboid(float l, float size, float r, float n, float f) { //from wj method l=-10 r=15
	glBegin(GL_QUADS);
	//Face 1 (bottom)
	//glColor3f(0.55, 0.75, 0.9);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(l, 0, n);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(r, 0, n);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(r, 0, f);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(l, 0, f);
	glEnd();

	//Face 2 (left)
	glBegin(GL_QUADS);
	//glColor3f(1, 0.45, 0.45);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(l, 0, f);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(l, size, f);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(l, size, n);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(l, 0, n);
	//glEnd();

	//Face 3  (front)
	glBegin(GL_QUADS);
	//glColor3f(0.7843, 0.749, 0.9059);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(l, 0, n);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(l, size, n);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(r, size, n);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(r, 0, n);
	glEnd();

	//Face 4 (right)
	glBegin(GL_QUADS);
	//glColor3f(0.651, 0.8235, 0.8235);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(r, 0, n);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(r, size, n);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(r, size, f);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(r, 0, f);
	glEnd();

	//Face 5 (back)
	glBegin(GL_QUADS);
	//glColor3f(1, 0.8627, 0.7255);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(r, 0, f);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(l, 0, f);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(l, size, f);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(r, size, f);
	glEnd();

	//Face 6 (top)
	glBegin(GL_QUADS);
	//glColor3f(0.8, 1, 0.8);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(r, size, f);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(l, size, f);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(l, size, n);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(r, size, n);
	glEnd();
}
//new
void drawSphere(float r) {
	GLUquadricObj* sphere = NULL;  //create quadric object pointer
	sphere = gluNewQuadric(); //create the quadric obj 
	gluQuadricDrawStyle(sphere, GLU_FILL); //set the draw style
	if (onTexture) {
		gluQuadricTexture(sphere, true);
	}
	gluSphere(sphere, r, 30, 30);  // draw sphere 10 = slice = stack the higher slice and stack the smoother of the sphere 
	gluDeleteQuadric(sphere);
}
//new
void drawCylinder(float tr, float br, float h) {
	GLUquadricObj* cylinder = NULL;  //create quadric object pointer
	cylinder = gluNewQuadric(); //create the quadric obj 
	gluQuadricDrawStyle(cylinder, GL_QUADS); //set the draw style
	if (onTexture) {
		gluQuadricTexture(cylinder, true);
	}
	gluCylinder(cylinder, tr, br, h, 30, 30);  // 0.8 = height 0.2 = topradius & baseradius
	gluDeleteQuadric(cylinder);
}
void drawCone(float r, float h) {
	GLUquadricObj* cylinder = NULL;  //create quadric object pointer
	cylinder = gluNewQuadric(); //create the quadric obj 
	gluQuadricDrawStyle(cylinder, GLU_LINE); //set the draw style
	gluCylinder(cylinder, 0.0, r, h, 30, 30);  // 0.8 = height 0.2 = topradius & baseradius
	gluDeleteQuadric(cylinder);
}
void drawDisk(float inr, float outr) {
	GLUquadricObj* disk = NULL;  //create quadric object pointer
	disk = gluNewQuadric(); //create the quadric obj 
	gluQuadricDrawStyle(disk, GLU_LINE); //set the draw style
	gluDisk(disk, inr, outr, 30, 5);  //5 loop and 30 slices 
	gluDeleteQuadric(disk);
}
void drawSphereWithoutGLU(float radius)
{
	const float PI = 3.141592f;
	GLfloat x, y, z, sliceA, stackA;
	int sliceNo = 30, stackNo = 30;
	for (sliceA = 0.0; sliceA < 2 * PI; sliceA += PI / sliceNo)
	{
		glBegin(GL_LINE_STRIP);
		for (stackA = 0.0; stackA < 2 * PI; stackA += PI / stackNo)
		{
			x = radius * cos(stackA) * sin(sliceA);
			y = radius * sin(stackA) * sin(sliceA);
			z = radius * cos(sliceA);
			glVertex3f(x, y, z);
			x = radius * cos(stackA) * sin(sliceA + PI / stackNo);
			y = radius * sin(stackA) * sin(sliceA + PI / sliceNo);
			z = radius * cos(sliceA + PI / sliceNo);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
}
void projection() {
	//camera frame
	glMatrixMode(GL_PROJECTION); // refer to the projection matrix 
	glLoadIdentity(); //reset the projection matrix 
	glTranslatef(ptx, pty, 0.0); //move the camera to left right and up down
	glRotatef(pry, 0.0, 1.0, 0.0); //rotate the camera to view different angle
	if (isOrtho) {
		glOrtho(-100.0, 100.0, -100.0, 100.0, oNear, oFar); //change the viewing x-axis = -10 to +10

	}
	else {
		//viewing frustum try to use smaller than ortho eg: 100/2 = glFrustum(50 -50, 50, -50, 5-,.....)
		gluPerspective(60, 1.0, -3, 5);
		glFrustum(-50.0, 50.0, -50.0, 50.0, pNear, pFar); //-10 - 10 = 20 21 - 1 = 20 same
	}
}
void drawWireframeCuboid(float l, float size, float r) {

	glBegin(GL_LINE_LOOP);
	//Face 1 (bottom)
	glColor3f(0.55, 0.75, 0.9);
	glVertex3f(l, 0, size);
	glVertex3f(r, 0, size);
	glVertex3f(r, 0, 0);
	glVertex3f(l, 0, 0);
	glEnd();

	//Face 2 (left)
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0.45, 0.45);
	glVertex3f(l, 0, 0);
	glVertex3f(l, size, 0);
	glVertex3f(l, size, size);
	glVertex3f(l, 0, size);
	glEnd();

	//Face 3  (front)
	glBegin(GL_LINE_LOOP);
	glColor3f(0.7843, 0.749, 0.9059);
	glVertex3f(l, 0, size);
	glVertex3f(l, size, size);
	glVertex3f(r, size, size);
	glVertex3f(r, 0, size);
	glEnd();

	//Face 4 (right)
	glBegin(GL_LINE_LOOP);
	glColor3f(0.651, 0.8235, 0.8235);
	glVertex3f(r, 0, size);
	glVertex3f(r, size, size);
	glVertex3f(r, size, 0);
	glVertex3f(r, 0, 0);
	glEnd();

	//Face 5 (back)
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0.8627, 0.7255);
	glVertex3f(r, 0, 0);
	glVertex3f(l, 0, 0);
	glVertex3f(l, size, 0);
	glVertex3f(r, size, 0);
	glEnd();

	//Face 6 (top)
	glBegin(GL_LINE_LOOP);
	glColor3f(0.8, 1, 0.8);
	glVertex3f(r, size, 0);
	glVertex3f(l, size, 0);
	glVertex3f(l, size, size);
	glVertex3f(r, size, size);
	glEnd();
}
//ZF
//new
void upperRightLeg() {
	glColor3f(1, 1, 1);
	//right big leg 
	glPushMatrix();
	glTranslatef(5, -3, -3.2);
	glRotatef(2, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	if (!onTexture) {
		glColor3f(0.5, 0.5, 0.5); //grey
	}
	if (onTexture) {
		textureArr[1] = loadTexture("shield2.bmp");
	}
	drawCylinder(4, 5, 28);
	glDeleteTextures(1, &textureArr[1]);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(5, -3, -3.2);
	if (!onTexture) {
		glColor3f(0.35, 0.65, 0.95); //greyish blue
	}
	if (onTexture) {
		textureArr[1] = loadTexture("shield2.bmp");
	}
	drawSphere(3.5);
	glDeleteTextures(1, &textureArr[1]);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();


	//right cover 
	glPushMatrix();
	glTranslatef(-1.5, -31, 0);
	if (onTexture) {
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	drawCuboid(14, 20, 3, 2, 0);
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
//new
void upperLeftLeg() {

	glColor3f(1, 1, 1);
	//left big leg
	glPushMatrix();
	glTranslatef(-5, -3, -3.2);
	glRotatef(-2, 0, 0, 1);
	glRotatef(90, 1, 0, 0);
	if (!onTexture) {
		glColor3f(0.5, 0.5, 0.5); //grey
	}
	if (onTexture) {
		textureArr[1] = loadTexture("shield2.bmp");
	}
	drawCylinder(4, 5, 28);
	glDeleteTextures(1, &textureArr[1]);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5, -3, -3.2);
	if (!onTexture) {
		glColor3f(0.35, 0.65, 0.95); //greyish blue
	}
	if (onTexture) {
		textureArr[1] = loadTexture("shield2.bmp");
	}
	drawSphere(3.5);
	glDeleteTextures(1, &textureArr[1]);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//left cover 
	glPushMatrix();
	glTranslatef(1.5, -31, 0);
	if (!onTexture) {
		glColor3f(0.35, 0.65, 0.95); //greyish blue
	}
	if (onTexture) {
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	drawCuboid(-14, 20, -3, 2, 0);
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
//new
void body() {
	//perut 
	//front face
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);
	if (onTexture) {
		glColor3f(1, 1, 1);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	else {
		glColor3f(0.5, 0.5, 0.5); //grey
	}
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(0, 19, -1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-14, 22, -1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(0, 7, -1);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(14, 22, -1);
	glEnd();

	//right face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(14, 22, -1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(0, 7, -1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(0, 7, -9.9);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(14, 22, -9.9);
	glEnd();

	//top right face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(14, 22, -9.9);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(14, 22, -1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(0, 19, -1);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(0, 19, -9.9);
	glEnd();

	//top left face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(0, 19, -9.9);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(0, 19, -1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-14, 22, -1);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(-14, 22, -9.9);
	glEnd();

	//left face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-14, 22, -9.9);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-14, 22, -1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(0, 7, -1);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(0, 7, -9.9);
	glEnd();

	//back face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(0, 7, -9.9);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(14, 22, -9.9);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(0, 19, -9.9);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(-14, 22, -9.9);
	glEnd();
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);

	if (onTexture) {
		glColor3f(1, 1, 1);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	else{
		glColor3f(0.5, 0.5, 0.5); //grey
	}
	//left chest 
	//front face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-14, 45, -1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-14, 22, -1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(0, 19, -1);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(0, 30, -1);
	glEnd();

	//right face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(0, 30, -1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(0, 19, -1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(0, 19, -9.9);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(0, 30, -9.9);
	glEnd();

	//top  face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(0, 30, -9.9);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(0, 30, -1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-14, 45, -1);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(-14, 45, -9.9);
	glEnd();

	//left face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-14, 45, -9.9);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-14, 45, -1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-14, 22, -1);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(-14, 22, -9.9);
	glEnd();

	//bottom face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-14, 22, -9.9);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-14, 22, -1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(0, 19, -1);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(0, 19, -9.9);
	glEnd();

	//back face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(0, 19, -9.9);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-14, 22, -9.9);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-14, 45, -9.9);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(0, 30, -9.9);
	glEnd();

	//right chest 
	//front face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(14, 45, -1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(14, 22, -1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(0, 19, -1);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(0, 30, -1);
	glEnd();

	//right face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(0, 30, -1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(0, 19, -1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(0, 19, -9.9);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(0, 30, -9.9);
	glEnd();

	//top  face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(0, 30, -9.9);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(0, 30, -1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(14, 45, -1);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(14, 45, -9.9);
	glEnd();

	//left face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(14, 45, -9.9);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(14, 45, -1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(14, 22, -1);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(14, 22, -9.9);
	glEnd();

	//bottom face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(14, 22, -9.9);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(14, 22, -1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(0, 19, -1);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(0, 19, -9.9);
	glEnd();

	//back face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(0, 19, -9.9);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(14, 22, -9.9);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(14, 45, -9.9);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(0, 30, -9.9);
	glEnd();
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);

	//left suo gu
	glColor3f(0.35, 0.45, 0.95); //purple grey blue

	//front face
	glBegin(GL_POLYGON);
	glVertex3f(-14, 45, -1);
	glVertex3f(-6, 45, -1);
	glVertex3f(0, 30, -1);
	glEnd();

	//right face
	glBegin(GL_POLYGON);
	glVertex3f(0, 30, -1);
	glVertex3f(0, 30, -9.9);
	glVertex3f(-6, 45, -9.9);
	glVertex3f(-6, 45, -1);
	glEnd();

	//top  face
	glBegin(GL_POLYGON);
	glVertex3f(-6, 45, -1);
	glVertex3f(-6, 45, -9.9);
	glVertex3f(-14, 45, -9.9);
	glVertex3f(-14, 45, -1);
	glEnd();

	//left face
	glBegin(GL_POLYGON);
	glVertex3f(-14, 45, -1);
	glVertex3f(0, 30, -1);
	glVertex3f(0, 30, -9.9);
	glVertex3f(-14, 45, -9.9);
	glEnd();

	//back face
	glBegin(GL_POLYGON);
	glVertex3f(-14, 45, -9.9);
	glVertex3f(-6, 45, -9.9);
	glVertex3f(0, 30, -9.9);
	glEnd();

	glPushMatrix();
	glTranslatef(-9.7, 43, -5.5);
	glColor3f(0.35, 0.45, 0.95); //purple grey blue
	drawSphere(4.5);
	glPopMatrix();

	//right suo gu
	glColor3f(0.35, 0.45, 0.95); //purple grey blue
	//front face
	glBegin(GL_POLYGON);
	glVertex3f(14, 45, -1);
	glVertex3f(6, 45, -1);
	glVertex3f(0, 30, -1);
	glEnd();

	//right face
	glBegin(GL_POLYGON);
	glVertex3f(0, 30, -1);
	glVertex3f(0, 30, -9.9);
	glVertex3f(6, 45, -9.9);
	glVertex3f(6, 45, -1);
	glEnd();

	//top  face
	glBegin(GL_POLYGON);
	glVertex3f(6, 45, -1);
	glVertex3f(6, 45, -9.9);
	glVertex3f(14, 45, -9.9);
	glVertex3f(14, 45, -1);
	glEnd();

	//left face
	glBegin(GL_POLYGON);
	glVertex3f(14, 45, -1);
	glVertex3f(0, 30, -1);
	glVertex3f(0, 30, -9.9);
	glVertex3f(14, 45, -9.9);
	glEnd();

	//back face
	glBegin(GL_POLYGON);
	glVertex3f(14, 45, -9.9);
	glVertex3f(6, 45, -9.9);
	glVertex3f(0, 30, -9.9);
	glEnd();
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(9.7, 43, -5.5);
	glColor3f(0.35, 0.45, 0.95); //purple grey blue
	drawSphere(4.5);
	glPopMatrix();

	//middle point
	glColor3f(0.27, 0.41, 0.60);  //dark grey blue
	if (onTexture) {
		glColor3f(0, 0, 0.63); //dark blue
	}
	glBegin(GL_POLYGON);
	glVertex3f(-2, 40, -0.9);
	glVertex3f(5, 34, -0.9);
	glVertex3f(2, 28, -0.9);
	glVertex3f(-5, 34, -0.9);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(-5, 34, -0.9);
	glVertex3f(-2, 28, -0.9);
	glVertex3f(2, 28, -0.9);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(-2, 40, -0.9);
	glVertex3f(2, 40, -0.9);
	glVertex3f(5, 34, -0.9);
	glEnd();

	//center sphere
	glPushMatrix();
	glTranslatef(0, 34, 0);
	if (onLaser) {
		glPushMatrix();
		glRotatef(rLaser, 1, 0, 0);
		glLineWidth(3);
		glBegin(GL_LINES);
		if (onTexture) {
			glColor3f(0, 1, 1); //white
			textureArr[2] = loadTexture("rainbow mirror.bmp");
		}
		else {
			glColor3f(1, 0, 0);
		}
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 300);
		glEnd();
		glDeleteTextures(1, &textureArr[2]);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	glColor3f(1, 0.73, 0.74); //pink
	if (onTexture) {
		glColor3f(1, 1, 1); //white
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	drawSphere(3.3);
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
	//obj 1
	glColor3f(0.27, 0.41, 0.60);  //dark grey blue
	if (onTexture) {
		glColor3f(0, 0, 0.63); //dark blue
	}
	//glScalef(2, 2, 2);
	glBegin(GL_POLYGON);
	glVertex2f(-6, 25);
	glVertex2f(-8, 12);
	glVertex2f(-6, 10);
	glVertex2f(-5, 13);
	glVertex2f(-3, 20);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(6, 25);
	glVertex2f(8, 12);
	glVertex2f(6, 10);
	glVertex2f(5, 13);
	glVertex2f(3, 20);
	glEnd();

	//obj2 
	glPushMatrix();
	glTranslatef(3.8, 1, 0);
	glRotatef(90, 0.0, 0.0, 1.0);
	drawCuboid(-10, 8, 15, 2, -10);

	glPopMatrix();

	//vshape

	glBegin(GL_TRIANGLES);
	glColor3f(1, 0.62, 0.44);  //peach orange
	glVertex3f(3, 13, 2.1); //2.1 = near = 2 
	glVertex3f(-1, 10, 2.1);
	glVertex3f(0, 9, 2.1);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(-3, 13, 2.1);
	glVertex3f(1, 10, 2.1);
	glVertex3f(0, 9, 2.1);
	glEnd();

	//triangle 
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0.62, 0.44);  //peach orange
	glVertex3f(-3, 4, 2.1);
	glVertex3f(0, 7, 2.1);
	glVertex3f(3, 4, 2.1);
	glEnd();

	//small quad
	glBegin(GL_QUADS);
	glVertex3f(-2, -1, 2.1);
	glVertex3f(2, -1, 2.1);
	glVertex3f(2, -2, 2.1);
	glVertex3f(-2, -2, 2.1);
	glEnd();

	//big quad with 2 dots 
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0); 
	glVertex3f(-3, -2, 2.1);
	glVertex3f(3, -2, 2.1);
	glVertex3f(3, -4, 2.1);
	glVertex3f(-3, -4, 2.1);
	glEnd();
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(1, 1, 0); 
	glVertex3f(-2, -3, 2.2); //8.2 = size z axis + 0.1 infront of the big quad
	glEnd();
	glBegin(GL_POINTS);
	glVertex3f(2, -3, 2.2); //8.2 = size z axis + 0.1 infront of the big quad
	glEnd();

	//line 
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3f(1, 1, 0);
	glVertex3f(0, -4, 2.1); //8.1 = size z axis 
	glVertex3f(0, -9, 2.1); //8.1 = size z axis 
	glEnd();


}
//new
void middleRightLeg() {
	//right leg 
	glPushMatrix();
	glTranslatef(7, -31, -3);
	glRotatef(90, 1, 0, 0);
	if (!onTexture) {
		glColor3f(0.27, 0.41, 0.60);  //dark grey blue
	}
	if (onTexture) {
		glColor3f(0.75, 0.91, 0.95);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	drawCylinder(6, 7, 9); //top r, bot r, h
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(7, -40, -3);
	glRotatef(90, 1, 0, 0);
	if (!onTexture) {
		glColor3f(0.27, 0.41, 0.60);  //dark grey blue
	}
	if (onTexture) {
		glColor3f(0.75, 0.91, 0.95);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	drawCylinder(7, 6, 9); //top r, bot r, h
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.75, 0.75, 0.75); //light grey
	drawSphere(5);
	glPopMatrix();
}
//new
void middleLeftLeg() {
	//left leg 
	glPushMatrix();
	glTranslatef(-7, -31, -3);
	glRotatef(90, 1, 0, 0);
	if (!onTexture) {
		glColor3f(0.27, 0.41, 0.60);  //dark grey blue
	}
	if (onTexture) {
		glColor3f(0.75, 0.91, 0.95);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	drawCylinder(6, 7, 9); //top r, bot r, h
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7, -40, -3);
	glRotatef(90, 1, 0, 0);
	if (!onTexture) {
		glColor3f(0.27, 0.41, 0.60);  //dark grey blue
	}
	if (onTexture) {
		glColor3f(0.75, 0.91, 0.95);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	drawCylinder(7, 6, 9); //top r, bot r, h
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);
	glColor3f(0.75, 0.75, 0.75); //light grey
	drawSphere(5);
	glPopMatrix();


}
//new
void bottomRightLeg() {
	//right joint
	glPushMatrix();
	glTranslatef(7, -51, -3);
	if (!onTexture) {
		glColor3f(0.75, 0.75, 0.75); //light grey
	}
	if (onTexture) {
		glColor3f(1, 1, 1);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	drawSphere(3);
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glColor3f(1, 1, 1);

	//right small leg 
	glPushMatrix();
	glTranslatef(7, -53, -3);
	glRotatef(90, 1, 0, 0);
	if (!onTexture) {
		glColor3f(0.35, 0.65, 0.95); //greyish blue
	}
	if (onTexture) {
		glColor3f(0.75, 0.91, 0.95);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	drawCylinder(6, 5, 13); //top r, bot r, h
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
//new
void bottomLeftLeg() {

	//left joint
	glPushMatrix();
	glTranslatef(-7, -51, -3);
	if (!onTexture) {
		glColor3f(0.75, 0.75, 0.75); //light grey
	}
	if (onTexture) {
		glColor3f(1, 1, 1);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	drawSphere(3);
	glPopMatrix();
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);

	glColor3f(1, 1, 1);
	//left small leg 
	glPushMatrix();
	glTranslatef(-7, -53, -3);
	glRotatef(90, 1, 0, 0);
	if (!onTexture) {
		glColor3f(0.35, 0.65, 0.95); //greyish blue
	}
	if (onTexture) {
		glColor3f(0.75, 0.91, 0.95);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	drawCylinder(6, 5, 13); //top r, bot r, h
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();



}
//new
void leftFoot() {


	//bottom left joint 
	glPushMatrix();
	glTranslatef(-8.5, -70, -4.5);
	glColor3f(0.35, 0.65, 0.95); //greyish blue
	drawCube(4);
	glPopMatrix();

	glColor3f(1, 1, 1);

	/////////////////////////////////////////////////////////////////////
	////left foot
	glPushMatrix();
	glTranslatef(-4.5, 0, -1.5);
	glRotatef(90, 0, 0, 1);
	glColor3f(0.5, 0.5, 0.5); //grey
	drawCuboid(-70, 4, -90, 1, -3);
	glPopMatrix();
	
	//jiao huai 
	if (!onTexture) {
		glColor3f(0.27, 0.41, 0.60);  //dark grey blue
	}
	if (onTexture) {
		glColor3f(1, 1, 1);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	glBegin(GL_QUADS);
	// Face 1 (bottom face)
	//glColor3f(0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-3, -90, 0);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-11, -90, 0);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-11, -90, 5);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(-3, -90, 5);
	glEnd();
	// Face 2 (left face)
	glBegin(GL_QUADS);
	//glColor3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-3, -90, 5);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-3, -90, 0);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-3, -70, 0);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(-3, -85, 5);
	glEnd();
	//face 3 (front face)
	glBegin(GL_QUADS);
	//glColor3f(0.0, 1.0, 0);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-3, -85, 5);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-3, -90, 5);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-11, -90, 5);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(-11, -85, 5);
	glEnd();
	//face 4 (right face) 
	glBegin(GL_QUADS);
	//glColor3f(0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-11, -85, 5);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-11, -90, 5);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-11, -90, 0);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(-11, -70, 0);
	glEnd();
	//face 5 (back face)
	glBegin(GL_QUADS);
	//glColor3f(0, 0.0, 1.0);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-11, -70, 0);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-11, -90, 0);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-3, -90, 0);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(-3, -70, 0);
	glEnd();
	//face 6 (top face)
	glBegin(GL_QUADS);
	//glColor3f(0.0, 1.0, 0);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-3, -70, 0);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-11, -70, 0);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-11, -85, 5);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(-3, -85, 5);
	glEnd();
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);

	//foot flat
	glBegin(GL_QUADS);
	// Face 1 (bottom face)
	glColor3f(0.5, 0.5, 0.5); //grey
	glVertex3f(-11, -90, 5);
	glVertex3f(-9, -90, 10);
	glVertex3f(-5, -90, 10);
	glVertex3f(-3, -90, 5);
	glEnd();
	// Face 2 (left face)
	glBegin(GL_QUADS);
	//glColor3f(0.0, 0, 1.0);
	glVertex3f(-3, -90, 5);
	glVertex3f(-3, -85, 5);
	glVertex3f(-5, -85, 8);
	glVertex3f(-5, -90, 10);
	glEnd();
	//face 3 (front face)
	glBegin(GL_QUADS);
	//glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-5, -90, 10);
	glVertex3f(-5, -85, 8);
	glVertex3f(-9, -85, 8);
	glVertex3f(-9, -90, 10);
	glEnd();
	//face 4 (right face) 
	glBegin(GL_QUADS);
	//glColor3f(0, 0, 1.0);
	glVertex3f(-9, -90, 10);
	glVertex3f(-9, -85, 8);
	glVertex3f(-11, -85, 5);
	glVertex3f(-11, -90, 5);
	glEnd();
	//face 5 (back face)
	glBegin(GL_QUADS);
	glColor3f(0, 0.0, 1.0);
	glVertex3f(-11, -85, 5);
	glVertex3f(-11, -90, 5);
	glVertex3f(-3, -90, 5);
	glVertex3f(-3, -85, 5);
	glEnd();
	//face 6 (top face)
	glBegin(GL_QUADS);
	//glColor3f(0.0, 0, 1.0);
	glVertex3f(-3, -85, 5);
	glVertex3f(-11, -85, 5);
	glVertex3f(-9, -85, 8);
	glVertex3f(-5, -85, 8);
	glEnd();

	glPushMatrix();
	glTranslatef(-10, -90, 8.0);
	//jiao zhi 1
	glBegin(GL_POLYGON);
	// Face 1 (bottom face)
	glColor3f(1.0, 1.0, 0.0);

	glVertex3f(-1, 4, 0);
	glVertex3f(1, 4, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(-1, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1, 0, 0);
	glVertex3f(0, 0, 4);
	glVertex3f(-1, 4, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1, 4, 0);
	glVertex3f(0, 0, 4);
	glVertex3f(1, 4, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1, 4, 0);
	glVertex3f(0, 0, 4); //go up
	glVertex3f(1, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 4);
	glVertex3f(-1, 0, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7.5, -90, 8.0);
	//jiao zhi 2
	glBegin(GL_POLYGON);
	// Face 1 (bottom face)
	glColor3f(1.0, 1.0, 0.0);

	glVertex3f(-1, 4, 0);
	glVertex3f(1, 4, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(-1, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1, 0, 0);
	glVertex3f(0, 0, 4);
	glVertex3f(-1, 4, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1, 4, 0);
	glVertex3f(0, 0, 4);
	glVertex3f(1, 4, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1, 4, 0);
	glVertex3f(0, 0, 4); //go up
	glVertex3f(1, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 4);
	glVertex3f(-1, 0, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, -90, 8.0);
	//jiao zhi 3
	glBegin(GL_POLYGON);
	// Face 1 (bottom face)
	glColor3f(1.0, 1.0, 0.0);

	glVertex3f(-1, 4, 0);
	glVertex3f(1, 4, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(-1, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1, 0, 0);
	glVertex3f(0, 0, 4);
	glVertex3f(-1, 4, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1, 4, 0);
	glVertex3f(0, 0, 4);
	glVertex3f(1, 4, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1, 4, 0);
	glVertex3f(0, 0, 4); //go up
	glVertex3f(1, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 4);
	glVertex3f(-1, 0, 0);
	glEnd();
	glPopMatrix();


	/////////////////////////////////////////
}
//new
void rightFoot() {
	//bottom right joint 
	glPushMatrix();
	glTranslatef(5.5, -70, -4.5);
	glColor3f(0.35, 0.65, 0.95); //greyish blue
	drawCube(4);
	glPopMatrix();
	/////////////////////////////////////////////////////////////////////
	//right foot
	glPushMatrix();
	glTranslatef(9.5, 0, -1.5);
	glRotatef(90, 0, 0, 1);
	glColor3f(0.5, 0.5, 0.5); //grey
	drawCuboid(-70, 4, -90, 1, -3);
	glPopMatrix();

	glColor3f(1, 1, 1);
	//jiao huai 
	if (!onTexture) {
		glColor3f(0.27, 0.41, 0.60);  //dark grey blue
	}
	if (onTexture) {
		glColor3f(1, 1, 1);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	glBegin(GL_QUADS);
	// Face 1 (bottom face)
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(3, -90, 0);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(11, -90, 0);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(11, -90, 5);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(3, -90, 5);
	glEnd();
	// Face 2 (left face)
	glBegin(GL_QUADS);
	//glColor3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(3, -90, 5);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(3, -90, 0);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(3, -70, 0);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(3, -85, 5);
	glEnd();
	//face 3 (front face)
	glBegin(GL_QUADS);
	//glColor3f(0.0, 1.0, 0);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(3, -85, 5);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(3, -90, 5);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(11, -90, 5);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(11, -85, 5);
	glEnd();
	//face 4 (right face) 
	glBegin(GL_QUADS);
	//glColor3f(0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(11, -85, 5);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(11, -90, 5);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(11, -90, 0);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(11, -70, 0);
	glEnd();
	//face 5 (back face)
	glBegin(GL_QUADS);
	//glColor3f(0, 0.0, 1.0);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(11, -70, 0);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(11, -90, 0);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(3, -90, 0);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(3, -70, 0);
	glEnd();
	//face 6 (top face)
	glBegin(GL_QUADS);
	//glColor3f(0.0, 1.0, 0);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(3, -70, 0);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(11, -70, 0);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(11, -85, 5);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(3, -85, 5);
	glEnd();
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);


	//foot flat
	glBegin(GL_QUADS);
	// Face 1 (bottom face)
	glColor3f(0.5, 0.5, 0.5); //grey
	glVertex3f(11, -90, 5);
	glVertex3f(9, -90, 10);
	glVertex3f(5, -90, 10);
	glVertex3f(3, -90, 5);
	glEnd();
	// Face 2 (left face)
	glBegin(GL_QUADS);
	glVertex3f(3, -90, 5);
	glVertex3f(3, -85, 5);
	glVertex3f(5, -85, 8);
	glVertex3f(5, -90, 10);
	glEnd();
	//face 3 (front face)
	glBegin(GL_QUADS);
	glVertex3f(5, -90, 10);
	glVertex3f(5, -85, 8);
	glVertex3f(9, -85, 8);
	glVertex3f(9, -90, 10);
	glEnd();
	//face 4 (right face) 
	glBegin(GL_QUADS);
	glVertex3f(9, -90, 10);
	glVertex3f(9, -85, 8);
	glVertex3f(11, -85, 5);
	glVertex3f(11, -90, 5);
	glEnd();
	//face 5 (back face)
	glBegin(GL_QUADS);
	glVertex3f(11, -85, 5);
	glVertex3f(11, -90, 5);
	glVertex3f(3, -90, 5);
	glVertex3f(3, -85, 5);
	glEnd();
	//face 6 (top face)
	glBegin(GL_QUADS);
	glVertex3f(3, -85, 5);
	glVertex3f(11, -85, 5);
	glVertex3f(9, -85, 8);
	glVertex3f(5, -85, 8);
	glEnd();

	glPushMatrix();
	glTranslatef(10, -90, 8.0);
	//jiao zhi 1
	glBegin(GL_POLYGON);
	// Face 1 (bottom face)
	glColor3f(1.0, 1.0, 0.0);

	glVertex3f(-1, 4, 0);
	glVertex3f(1, 4, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(-1, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1, 0, 0);
	glVertex3f(0, 0, 4);
	glVertex3f(-1, 4, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1, 4, 0);
	glVertex3f(0, 0, 4);
	glVertex3f(1, 4, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1, 4, 0);
	glVertex3f(0, 0, 4); //go up
	glVertex3f(1, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 4);
	glVertex3f(-1, 0, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7.5, -90, 8.0);
	//jiao zhi 2
	glBegin(GL_POLYGON);
	// Face 1 (bottom face)
	glColor3f(1.0, 1.0, 0.0);

	glVertex3f(-1, 4, 0);
	glVertex3f(1, 4, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(-1, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1, 0, 0);
	glVertex3f(0, 0, 4);
	glVertex3f(-1, 4, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1, 4, 0);
	glVertex3f(0, 0, 4);
	glVertex3f(1, 4, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1, 4, 0);
	glVertex3f(0, 0, 4); //go up
	glVertex3f(1, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 4);
	glVertex3f(-1, 0, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, -90, 8.0);
	//jiao zhi 3
	glBegin(GL_POLYGON);
	// Face 1 (bottom face)
	glColor3f(1.0, 10, 0.0);

	glVertex3f(-1, 4, 0);
	glVertex3f(1, 4, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(-1, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1, 0, 0);
	glVertex3f(0, 0, 4);
	glVertex3f(-1, 4, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1, 4, 0);
	glVertex3f(0, 0, 4);
	glVertex3f(1, 4, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1, 4, 0);
	glVertex3f(0, 0, 4); //go up
	glVertex3f(1, 0, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 4);
	glVertex3f(-1, 0, 0);
	glEnd();
	glPopMatrix();
	///////////////////////////////////////////
}

//new
void weapon() {
	/*glBegin(GL_LINES);
	glVertex2f(0, 100);
	glVertex2f(0, -100);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(100, 0);
	glVertex2f(-100, 0);
	glEnd();*/

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glColor3f(0, 0, 0.63); //dark blue
	drawCylinder(1, 1, 40);
	glPopMatrix();


	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 0); //yellow 
	glVertex3f(-0.5, -10, 0);
	glVertex3f(-0.5, -16, 0);
	glVertex3f(-2, -13, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 0); //yellow 
	glVertex3f(0.5, -10, 0);
	glVertex3f(0.5, -16, 0);
	glVertex3f(2, -13, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 0); //yellow 
	glVertex3f(-0.5, -20, 0);
	glVertex3f(-0.5, -25, 0);
	glVertex3f(-3, -22.5, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 0); //yellow 
	glVertex3f(0.5, -20, 0);
	glVertex3f(0.5, -25, 0);
	glVertex3f(3, -22.5, 0);
	glEnd();

	glPushMatrix();
	glTranslatef(0.2, 4, 0);
	glScalef(1.1, 1.2, 1.2);
	//front face
	if (onTexture) {
		glColor3f(1, 1, 1);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	else {
		glColor3f(0.75, 0.75, 0.75); //light grey
	}
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-10, -31, 0);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-10, -35, 0);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-1, -35, 1);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(-1, -31, 1);
	glEnd();

	//top face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-1, -31, 1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-10, -31, 0);
	glTexCoord2f(0.5, 0.0);  //tri text 3
	glVertex3f(-1, -35, -1);
	glEnd();

	//back  face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-1, -35, -1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-10, -31, 0);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-10, -35, 0);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(-1, -35, -1);
	glEnd();

	//bottom face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-1, -35, -1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-10, -35, 0);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-1, -35, 1);
	glEnd();

	//right face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-1, -35, 1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-1, -35, -1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-1, -31, -1);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(-1, -31, 1);
	glEnd();

	//front face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-10, -31, 0);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-7, -31, 1);
	glTexCoord2f(0.5, 0.0);  //tri text 3
	glVertex3f(-7, -27, 1);
	glEnd();

	//top face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-7, -27, 1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-10, -31, 0);
	glTexCoord2f(0.5, 0.0);  //tri text 3
	glVertex3f(-7, -27, -1);
	glEnd();

	//back  face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-7, -27, -1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-10, -31, 0);
	glTexCoord2f(0.5, 0.0);  //tri text 3
	glVertex3f(-7, -31, -1);
	glEnd();

	//bottom face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-7, -31, -1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-10, -31, 0);
	glTexCoord2f(0.5, 0.0);  //tri text 3
	glVertex3f(-7, -31, 1);
	glEnd();

	//right face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-7, -31, 1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-7, -27, 1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-7, -27, -1);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(-7, -31, -1);
	glEnd();

	//front face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-10, -35, 0);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-7, -39, 1);
	glTexCoord2f(0.5, 0.0);  //tri text 3
	glVertex3f(-7, -35, 1);
	glEnd();

	//top face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-7, -35, 1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-10, -35, 0);
	glTexCoord2f(0.5, 0.0);  //tri text 3
	glVertex3f(-7, -35, -1);
	glEnd();

	//back  face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-7, -35, -1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-10, -35, 0);
	glTexCoord2f(0.5, 0.0);  //tri text 3
	glVertex3f(-7, -39, -1);
	glEnd();

	//bottom face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-7, -39, -1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-10, -35, 0);
	glTexCoord2f(0.5, 0.0);  //tri text 3
	glVertex3f(-7, -39, 1);
	glEnd();

	//right face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-7, -39, 1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-7, -35, 1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-7, -35, -1);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(-7, -39, -1);
	glEnd();
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);


	glPushMatrix();
	glTranslatef(-10, -33, 0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 0.63); //dark blue
	glVertex2f(x, y); //origin of circle 
	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / noOfTri) {
		x2 = x + radius * cos(angle);
		y2 = y + radius * sin(angle);
		glVertex2f(x2, y2);
	}

	glEnd();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	//glTranslatef(10, 4, 0);
	glTranslatef(19, -13, 0);
	glTranslatef(-10, -31, 0);
	glRotatef(180, 0, 0, 1);
	glTranslatef(10, 31, 0);
	glScalef(1.1, 1.2, 1.2);
	//front face
	if (onTexture) {
		glColor3f(1, 1, 1);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	else {
		glColor3f(0.75, 0.75, 0.75); //light grey
	}
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-10, -31, 0);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-10, -35, 0);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-1, -35, 1);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(-1, -31, 1);
	glEnd();

	//top face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-1, -31, 1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-10, -31, 0);
	glTexCoord2f(0.5, 0.0);  //tri text 3
	glVertex3f(-1, -35, -1);
	glEnd();

	//back  face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-1, -35, -1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-10, -31, 0);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-10, -35, 0);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(-1, -35, -1);
	glEnd();

	//bottom face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-1, -35, -1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-10, -35, 0);
	glTexCoord2f(0.5, 0.0);  //tri text 3
	glVertex3f(-1, -35, 1);
	glEnd();

	//right face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-1, -35, 1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-1, -35, -1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-1, -31, -1);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(-1, -31, 1);
	glEnd();

	//front face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-10, -31, 0);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-7, -31, 1);
	glTexCoord2f(0.5, 0.0);  //tri text 3
	glVertex3f(-7, -27, 1);
	glEnd();

	//top face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-7, -27, 1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-10, -31, 0);
	glTexCoord2f(0.5, 0.0);  //tri text 3
	glVertex3f(-7, -27, -1);
	glEnd();

	//back  face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-7, -27, -1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-10, -31, 0);
	glTexCoord2f(0.5, 0.0);  //tri text 3
	glVertex3f(-7, -31, -1);
	glEnd();

	//bottom face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-7, -31, -1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-10, -31, 0);
	glTexCoord2f(0.5, 0.0);  //tri text 3
	glVertex3f(-7, -31, 1);
	glEnd();

	//right face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-7, -31, 1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-7, -27, 1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-7, -27, -1);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(-7, -31, -1);
	glEnd();

	//front face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-10, -35, 0);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-7, -39, 1);
	glTexCoord2f(0.5, 0.0);  //tri text 3
	glVertex3f(-7, -35, 1);
	glEnd();

	//top face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-7, -35, 1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-10, -35, 0);
	glTexCoord2f(0.5, 0.0);  //tri text 3
	glVertex3f(-7, -35, -1);
	glEnd();

	//back  face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-7, -35, -1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-10, -35, 0);
	glTexCoord2f(0.5, 0.0);  //tri text 3
	glVertex3f(-7, -39, -1);
	glEnd();

	//bottom face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-7, -39, -1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-10, -35, 0);
	glTexCoord2f(0.5, 0.0);  //tri text 3
	glVertex3f(-7, -39, 1);
	glEnd();

	//right face
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(-7, -39, 1);
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(-7, -35, 1);
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(-7, -35, -1);
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(-7, -39, -1);
	glEnd();
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(-10, -33, 0);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 0.63); //dark blue
	glVertex2f(x, y); //origin of circle 
	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / noOfTri) {
		x2 = x + radius * cos(angle);
		y2 = y + radius * sin(angle);
		glVertex2f(x2, y2);
	}

	glEnd();
	glPopMatrix();
	glPopMatrix();
}

//WJ----------------------------------------------------------------------------------------------------------------------------------------------------------
void drawUpperShoulder(float l, float size, float r, float n, float f) {

	glBegin(GL_QUADS);
	//Face 1 (bottom)
	glColor3f(0.55, 0.75, 0.9);
	glVertex3f(l, 0, n);
	glVertex3f(r, 0, n);
	glVertex3f(r, 0, f);
	glVertex3f(l, 0, f);
	glEnd();

	//Face 2 (left)
	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	//glColor3f(1, 0.45, 0.45);
	glVertex3f(l, 0, f);
	glVertex3f(l, size, f);
	glVertex3f(l, size, n);
	glVertex3f(l, 0, n);
	glEnd();

	//Face 3  (front)
	glBegin(GL_QUADS);
	//glColor3f(0.7843, 0.749, 0.9059); 
	glColor3f(1, 0, 0);  //red
	glVertex3f(l, 0, n);
	glVertex3f(l, size, n);
	glVertex3f(r, size, n);
	glVertex3f(r, 0, n);
	glEnd();

	//Face 4 (right)
	glBegin(GL_QUADS);
	glColor3f(0.651, 0.8235, 0.8235);
	glVertex3f(r, 0, n);
	glVertex3f(r, size, n);
	glVertex3f(r, size, f);
	glVertex3f(r, 0, f);
	glEnd();

	//Face 5 (back)
	glBegin(GL_QUADS);
	glColor3f(1, 1, 0); //yellow
	//glColor3f(1, 0.8627, 0.7255);
	glVertex3f(r, 0, f);
	glVertex3f(l, 0, f);
	glVertex3f(l, size, f);
	glVertex3f(r, size, f);
	glEnd();

	//Face 6 (top)
	glBegin(GL_QUADS);
	glColor3f(0.8, 1, 0.8);
	glVertex3f(r, size, f);
	glVertex3f(l, size, f);
	glVertex3f(l, size, n);
	glVertex3f(r, size, n);
	glEnd();
}
void drawFinger(float l, float size, float r, float n, float f) {

	glBegin(GL_QUADS);
	//Face 1 (bottom)
	glVertex3f(l, 0, n);
	glVertex3f(r, 0, n);
	glVertex3f(r, 0, f);
	glVertex3f(l, 0, f);
	glEnd();

	//Face 2 (left)
	glBegin(GL_QUADS);
	//glColor3f(1, 0.45, 0.45);
	glVertex3f(l, 0, f);
	glVertex3f(l, size, f);
	glVertex3f(l, size, n);
	glVertex3f(l, 0, n);
	glEnd();

	//Face 3  (front)
	glBegin(GL_QUADS);
	//glColor3f(0.7843, 0.749, 0.9059); 
	glVertex3f(l, 0, n);
	glVertex3f(l, size, n);
	glVertex3f(r, size, n);
	glVertex3f(r, 0, n);
	glEnd();

	//Face 4 (right)
	glBegin(GL_QUADS);
	glVertex3f(r, 0, n);
	glVertex3f(r, size, n);
	glVertex3f(r, size, f);
	glVertex3f(r, 0, f);
	glEnd();

	//Face 5 (back)
	glBegin(GL_QUADS);

	//glColor3f(1, 0.8627, 0.7255);
	glVertex3f(r, 0, f);
	glVertex3f(l, 0, f);
	glVertex3f(l, size, f);
	glVertex3f(r, size, f);
	glEnd();

	//Face 6 (top)
	glBegin(GL_QUADS);
	glVertex3f(r, size, f);
	glVertex3f(l, size, f);
	glVertex3f(l, size, n);
	glVertex3f(r, size, n);
	glEnd();
}

//new
void shoulder() {
	glPushMatrix();
	glRotatef(10, 0, 0, 1);
	glRotatef(20, 1, 0, 0);
	glRotatef(50, 0, 1, 0);
	glTranslatef(0, 25, -5);
	if (!onTexture) {
		glColor3f(0.27, 0.41, 0.60);  //dark grey blue
	}
	drawCuboid(20, 5, 50, 0, 15);
	glPopMatrix();
}
//new
void upperArm() {
	glColor3f(1, 1, 1);
	if (!onTexture) {
		glColor3f(0.35, 0.65, 0.95); //greyish blue
	}
	//upper arm (cuboid)
	glPushMatrix();
	glRotatef(50, 0, 1, 0);
	glRotatef(15, 0, 0, 1);
	drawCuboid(20, 30, 40, 0, 10);

	//upper arm (inner cylinder)
	glPushMatrix();
	//glRotatef(30, 0, 0, 1);
	glTranslatef(30, 30, 5);
	glRotatef(90, 1, 0, 0);
	glColor3f(1, 0.73, 0.74); //pink
	drawCylinder(4, 4, 40);//upper arm (inner cylinder)
	glPopMatrix();
	glPopMatrix();
}
//new
void armJoint() {
	//joint(sphere)
	glPushMatrix();
	glTranslatef(30, -12, 5);
	glRotatef(90, 1, 0, 0);
	if (!onTexture) {
		glColor3f(0.75, 0.75, 0.75);
	}
	if (onTexture) {
		glColor3f(1, 1, 1);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	drawSphere(8);
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//joint(pattern side)
	glPushMatrix();
	glTranslatef(30, -12, 5);
	glColor3f(0.45, 0.45, 0.45);
	drawCylinder(8.2, 8.2, 2);
	glPopMatrix();
}
//new
void lowerArm() {
	//lower arm (cylinder)
	glPushMatrix();
	glTranslatef(30, -12, 5);
	glRotatef(90, 1, 0, 0);
	if (!onTexture) {
		glColor3f(0.5, 0.5, 0.5); //grey
	}
	if (onTexture) {
		glColor3f(1, 1, 1);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	drawCylinder(4, 4, 43);//lower arm (inner cylinder)
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//cylinder pattern outside
	glPushMatrix();
	glTranslatef(30, -12, 5);
	glRotatef(90, 1, 0, 0);
	glColor3f(0.35, 0.65, 0.85); //greyish blue
	drawCylinder(4.1, 4.1, 23);//lower arm (inner cylinder)
	glPopMatrix();

	//cuboid floating on arm
	glPushMatrix();
	glTranslatef(0, -45, 0);
	if (!onTexture) {
		glColor3f(1, 0.73, 0.74); //pink
	}
	if (onTexture) {
		glColor3f(0.25, 0.25, 1);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	drawCuboid(30, 20, 32, 0, 2);
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, -45, 7);
	if (!onTexture) {
		glColor3f(1, 0.73, 0.74); //pink
	}
	if (onTexture) {
		glColor3f(0.25, 0.25, 1);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	drawCuboid(30, 20, 32, 0, 3);
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
void wrist() {
	//wrist(cylinder plate)
	glPushMatrix();
	glTranslatef(30, -53, 5);
	glRotatef(90, 1, 0, 0);
	glColor3f(0.35, 0.65, 0.95); //greyish blue
	drawCylinder(6, 6, 4);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(30, -57, 5);
	glRotatef(90, 1, 0, 0);
	glColor3f(0.35, 0.65, 0.95); //greyish blue
	drawDisk(0, 6);
	glPopMatrix();
}
void upperPalm() {
	glPushMatrix();
	glColor3f(0.35, 0.45, 0.95); //purple grey blue
	drawFinger(30, 5, 40, 0, 2); //upper palam
	glPopMatrix();
}
void lowerPalm() {
	glPushMatrix();
	glTranslatef(0, -5, 0);
	glColor3f(0.35, 0.45, 0.95); //purple grey blue
	drawFinger(30, 5, 40, 0, 2);//lower palm
	glPopMatrix();
}
void thumb() {


	//glTranslatef(-30, 53, -5);
	//thumb
	glPushMatrix();
	glColor3f(0.45, 0.45, 0.45);
	glTranslatef(-1, -2, 0);
	drawFinger(30, 2, 31, 0, 2); //thumb root joint
	glPopMatrix();


	//thumb root
	glPushMatrix();
	glRotatef(75, 0, 0, 1);
	glTranslatef(-29, -29.5, 0);

	//thumb root
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 35, 0, 2);
	glPopMatrix();

	//move thumb tip
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(-1, 0, 0);
	glRotatef(rThumb, 0, 1, 0);
	glTranslatef(1, 0, 0);
	glTranslatef(-32, 40, 0);

	//thumb joint1
	glPushMatrix();
	glTranslatef(-1, 0, 0);
	glColor3f(1, 1, 0); //yellow
	drawFinger(30, 1.5, 31, 0, 2);
	glPopMatrix();
	//thumb tip
	glPushMatrix();
	glTranslatef(-5, 0, 0);
	glColor3f(0.45, 0.45, 0.45);
	drawFinger(30, 1.5, 34, 0, 2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(25, 0.75, 1);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawSphere(0.85);
	glPopMatrix();
	glPopMatrix();//end of move thumb tip

	glPopMatrix();//end of thumb



}
void thumbLeft() {


	//glTranslatef(-30, 53, -5);
	//thumb
	glPushMatrix();
	glColor3f(0.45, 0.45, 0.45);
	glTranslatef(-1, -2, 0);
	drawFinger(30, 2, 31, 0, 2); //thumb root joint
	glPopMatrix();


	//thumb root
	glPushMatrix();
	glRotatef(75, 0, 0, 1);
	glTranslatef(-29, -29.5, 0);

	//thumb root
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 35, 0, 2);
	glPopMatrix();

	//move thumb tip
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(-1, 0, 0);
	glRotatef(rThumbLeft, 0, 1, 0);
	glTranslatef(1, 0, 0);
	glTranslatef(-32, 40, 0);

	//thumb joint1
	glPushMatrix();
	glTranslatef(-1, 0, 0);
	glColor3f(1, 1, 0); //yellow
	drawFinger(30, 1.5, 31, 0, 2);
	glPopMatrix();
	//thumb tip
	glPushMatrix();
	glTranslatef(-5, 0, 0);
	glColor3f(0.45, 0.45, 0.45);
	drawFinger(30, 1.5, 34, 0, 2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(25, 0.75, 1);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawSphere(0.85);
	glPopMatrix();
	glPopMatrix();//end of move thumb tip

	glPopMatrix();//end of thumb



}
void finger1() {

	//move finger root
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glRotatef(rFingerRoot, 0, 1, 0);
	glTranslatef(-32, 40, 0);
	//finger(1)root
	glPushMatrix();
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 35, 0, 2);
	glPopMatrix();


	//move finger middle
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(-1, 0, 0);
	glRotatef(rFingerMiddle, 0, 1, 0);
	glTranslatef(1, 0, 0);
	glTranslatef(-32, 40, 0);
	//finger(1)joint1
	glPushMatrix();
	glTranslatef(-1, 0, 0);
	glColor3f(1, 1, 0);  //yellow
	drawFinger(30, 1.5, 31, 0, 2);
	glPopMatrix();


	//finger(1)middle
	glPushMatrix();
	glTranslatef(-5, 0, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 34, 0, 2);
	glPopMatrix();


	//move finger tip
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(-6, 0, 0);
	glRotatef(rFingerTip, 0, 1, 0);
	glTranslatef(6, 0, 0);
	glTranslatef(-32, 40, 0);
	//finger(1)joint2
	glPushMatrix();
	glTranslatef(-6, 0, 0);
	glColor3f(1, 1, 0);  //yellow
	drawFinger(30, 1.5, 31, 0, 2);
	glPopMatrix();


	//finger(1)tip
	glPushMatrix();
	glTranslatef(-9, 0, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 33, 0, 2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(21, 0.75, 1);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawSphere(0.85);
	glPopMatrix();

	glPopMatrix();//end move finger tip
	glPopMatrix(); //end of Move finger middle
	glPopMatrix(); //end of move finger root
}
void finger2() {
	//move finger root
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(0, -2.5, 0);
	glRotatef(rFingerRoot, 0, 1, 0);
	glTranslatef(0, 2.5, 0);
	glTranslatef(-32, 40, 0);
	//finger(2)root
	glPushMatrix();
	glTranslatef(0, -2.5, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 35, 0, 2);
	glPopMatrix();

	//move finger middle
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(-1, -2.5, 0);
	glRotatef(rFingerMiddle, 0, 1, 0);
	glTranslatef(1, 2.5, 0);
	glTranslatef(-32, 40, 0);

	//finger(2)joint1
	glPushMatrix();
	glTranslatef(-1, -2.5, 0);
	glColor3f(1, 1, 0);  //yellow
	drawFinger(30, 1.5, 31, 0, 2);
	glPopMatrix();
	//finger(2)middle
	glPushMatrix();
	glTranslatef(-5, -2.5, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 34, 0, 2);
	glPopMatrix();

	//move finger tip
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(-6, -2.5, 0);
	glRotatef(rFingerTip, 0, 1, 0);
	glTranslatef(6, 2.5, 0);
	glTranslatef(-32, 40, 0);

	//finger(2)joint2
	glPushMatrix();
	glTranslatef(-6, -2.5, 0);
	glColor3f(1, 1, 0);  //yellow
	drawFinger(30, 1.5, 31, 0, 2);
	glPopMatrix();
	//finger(2)tip
	glPushMatrix();
	glTranslatef(-9, -2.5, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 33, 0, 2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(21, -1.7, 1);
	drawSphere(0.85);
	glPopMatrix();

	glPopMatrix();//end move finger tip
	glPopMatrix(); //end of Move finger middle
	glPopMatrix(); //end of move finger root
}
void finger3() {
	//move finger root
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(0, -5, 0);
	glRotatef(rFingerRoot, 0, 1, 0);
	glTranslatef(0, 5, 0);
	glTranslatef(-32, 40, 0);
	//finger(3)root
	glPushMatrix();
	glTranslatef(0, -5, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 35, 0, 2);
	glPopMatrix();

	//move finger middle
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(-1, -5, 0);
	glRotatef(rFingerMiddle, 0, 1, 0);
	glTranslatef(1, 5, 0);
	glTranslatef(-32, 40, 0);
	//finger(3)joint1
	glPushMatrix();
	glTranslatef(-1, -5, 0);
	glColor3f(1, 1, 0);  //yellow
	drawFinger(30, 1.5, 31, 0, 2);
	glPopMatrix();
	//finger(3)middle
	glPushMatrix();
	glTranslatef(-5, -5, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 34, 0, 2);
	glPopMatrix();

	//move finger tip
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(-6, -5, 0);
	glRotatef(rFingerTip, 0, 1, 0);
	glTranslatef(6, 5, 0);
	glTranslatef(-32, 40, 0);
	//finger(3)joint2
	glPushMatrix();
	glTranslatef(-6, -5, 0);
	glColor3f(1, 1, 0);  //yellow
	drawFinger(30, 1.5, 31, 0, 2);
	glPopMatrix();
	//finger(3)tip
	glPushMatrix();
	glTranslatef(-9, -5, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 33, 0, 2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(21, -4.2, 1);
	drawSphere(0.85);
	glPopMatrix();

	glPopMatrix();//end move finger tip
	glPopMatrix(); //end of Move finger middle
	glPopMatrix(); //end of move finger root
}
void finger4() {

	//move finger root
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(0, -7.5, 0);
	glRotatef(rFingerRoot, 0, 1, 0);
	glTranslatef(0, 7.5, 0);
	glTranslatef(-32, 40, 0);

	//finger(4)root
	glPushMatrix();
	glTranslatef(0, -7.5, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 35, 0, 2);
	glPopMatrix();


	//move finger middle
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(-1, -7.5, 0);
	glRotatef(rFingerMiddle, 0, 1, 0);
	glTranslatef(1, 7.5, 0);
	glTranslatef(-32, 40, 0);
	//finger(4)joint1
	glPushMatrix();
	glTranslatef(-1, -7.5, 0);
	glColor3f(1, 1, 0);  //yellow
	drawFinger(30, 1.5, 31, 0, 2);
	glPopMatrix();
	//finger(4)middle
	glPushMatrix();
	glTranslatef(-5, -7.5, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 34, 0, 2);
	glPopMatrix();

	//move finger tip
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(-6, -7.5, 0);
	glRotatef(rFingerTip, 0, 1, 0);
	glTranslatef(6, 7.5, 0);
	glTranslatef(-32, 40, 0);
	//finger(4)joint2
	glPushMatrix();
	glTranslatef(-6, -7.5, 0);
	glColor3f(1, 1, 0);  //yellow
	drawFinger(30, 1.5, 31, 0, 2);
	glPopMatrix();
	//finger(4)tip
	glPushMatrix();
	glTranslatef(-9, -7.5, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 33, 0, 2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(21, -6.7, 1);
	drawSphere(0.9);
	glPopMatrix();

	glPopMatrix();//end move finger tip
	glPopMatrix(); //end of Move finger middle
	glPopMatrix(); //end of move finger root
}
void finger1Left() {

	//move finger root
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glRotatef(rFingerRootLeft, 0, 1, 0);
	glTranslatef(-32, 40, 0);
	//finger(1)root
	glPushMatrix();
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 35, 0, 2);
	glPopMatrix();


	//move finger middle
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(-1, 0, 0);
	glRotatef(rFingerMiddleLeft, 0, 1, 0);
	glTranslatef(1, 0, 0);
	glTranslatef(-32, 40, 0);
	//finger(1)joint1
	glPushMatrix();
	glTranslatef(-1, 0, 0);
	glColor3f(1, 1, 0);  //yellow
	drawFinger(30, 1.5, 31, 0, 2);
	glPopMatrix();


	//finger(1)middle
	glPushMatrix();
	glTranslatef(-5, 0, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 34, 0, 2);
	glPopMatrix();


	//move finger tip
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(-6, 0, 0);
	glRotatef(rFingerTipLeft, 0, 1, 0);
	glTranslatef(6, 0, 0);
	glTranslatef(-32, 40, 0);
	//finger(1)joint2
	glPushMatrix();
	glTranslatef(-6, 0, 0);
	glColor3f(1, 1, 0);  //yellow
	drawFinger(30, 1.5, 31, 0, 2);
	glPopMatrix();


	//finger(1)tip
	glPushMatrix();
	glTranslatef(-9, 0, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 33, 0, 2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(21, 0.75, 1);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawSphere(0.85);
	glPopMatrix();

	glPopMatrix();//end move finger tip
	glPopMatrix(); //end of Move finger middle
	glPopMatrix(); //end of move finger root
}
void finger2Left() {
	//move finger root
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(0, -2.5, 0);
	glRotatef(rFingerRootLeft, 0, 1, 0);
	glTranslatef(0, 2.5, 0);
	glTranslatef(-32, 40, 0);
	//finger(2)root
	glPushMatrix();
	glTranslatef(0, -2.5, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 35, 0, 2);
	glPopMatrix();

	//move finger middle
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(-1, -2.5, 0);
	glRotatef(rFingerMiddleLeft, 0, 1, 0);
	glTranslatef(1, 2.5, 0);
	glTranslatef(-32, 40, 0);

	//finger(2)joint1
	glPushMatrix();
	glTranslatef(-1, -2.5, 0);
	glColor3f(1, 1, 0);  //yellow
	drawFinger(30, 1.5, 31, 0, 2);
	glPopMatrix();
	//finger(2)middle
	glPushMatrix();
	glTranslatef(-5, -2.5, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 34, 0, 2);
	glPopMatrix();

	//move finger tip
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(-6, -2.5, 0);
	glRotatef(rFingerTipLeft, 0, 1, 0);
	glTranslatef(6, 2.5, 0);
	glTranslatef(-32, 40, 0);

	//finger(2)joint2
	glPushMatrix();
	glTranslatef(-6, -2.5, 0);
	glColor3f(1, 1, 0);  //yellow
	drawFinger(30, 1.5, 31, 0, 2);
	glPopMatrix();
	//finger(2)tip
	glPushMatrix();
	glTranslatef(-9, -2.5, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 33, 0, 2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(21, -1.7, 1);
	drawSphere(0.85);
	glPopMatrix();

	glPopMatrix();//end move finger tip
	glPopMatrix(); //end of Move finger middle
	glPopMatrix(); //end of move finger root
}
void finger3Left() {
	//move finger root
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(0, -5, 0);
	glRotatef(rFingerRootLeft, 0, 1, 0);
	glTranslatef(0, 5, 0);
	glTranslatef(-32, 40, 0);
	//finger(3)root
	glPushMatrix();
	glTranslatef(0, -5, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 35, 0, 2);
	glPopMatrix();

	//move finger middle
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(-1, -5, 0);
	glRotatef(rFingerMiddleLeft, 0, 1, 0);
	glTranslatef(1, 5, 0);
	glTranslatef(-32, 40, 0);
	//finger(3)joint1
	glPushMatrix();
	glTranslatef(-1, -5, 0);
	glColor3f(1, 1, 0);  //yellow
	drawFinger(30, 1.5, 31, 0, 2);
	glPopMatrix();
	//finger(3)middle
	glPushMatrix();
	glTranslatef(-5, -5, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 34, 0, 2);
	glPopMatrix();

	//move finger tip
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(-6, -5, 0);
	glRotatef(rFingerTipLeft, 0, 1, 0);
	glTranslatef(6, 5, 0);
	glTranslatef(-32, 40, 0);
	//finger(3)joint2
	glPushMatrix();
	glTranslatef(-6, -5, 0);
	glColor3f(1, 1, 0);  //yellow
	drawFinger(30, 1.5, 31, 0, 2);
	glPopMatrix();
	//finger(3)tip
	glPushMatrix();
	glTranslatef(-9, -5, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 33, 0, 2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(21, -4.2, 1);
	drawSphere(0.85);
	glPopMatrix();

	glPopMatrix();//end move finger tip
	glPopMatrix(); //end of Move finger middle
	glPopMatrix(); //end of move finger root
}
void finger4Left() {

	//move finger root
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(0, -7.5, 0);
	glRotatef(rFingerRootLeft, 0, 1, 0);
	glTranslatef(0, 7.5, 0);
	glTranslatef(-32, 40, 0);

	//finger(4)root
	glPushMatrix();
	glTranslatef(0, -7.5, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 35, 0, 2);
	glPopMatrix();


	//move finger middle
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(-1, -7.5, 0);
	glRotatef(rFingerMiddleLeft, 0, 1, 0);
	glTranslatef(1, 7.5, 0);
	glTranslatef(-32, 40, 0);
	//finger(4)joint1
	glPushMatrix();
	glTranslatef(-1, -7.5, 0);
	glColor3f(1, 1, 0);  //yellow
	drawFinger(30, 1.5, 31, 0, 2);
	glPopMatrix();
	//finger(4)middle
	glPushMatrix();
	glTranslatef(-5, -7.5, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 34, 0, 2);
	glPopMatrix();

	//move finger tip
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glTranslatef(-6, -7.5, 0);
	glRotatef(rFingerTipLeft, 0, 1, 0);
	glTranslatef(6, 7.5, 0);
	glTranslatef(-32, 40, 0);
	//finger(4)joint2
	glPushMatrix();
	glTranslatef(-6, -7.5, 0);
	glColor3f(1, 1, 0);  //yellow
	drawFinger(30, 1.5, 31, 0, 2);
	glPopMatrix();
	//finger(4)tip
	glPushMatrix();
	glTranslatef(-9, -7.5, 0);
	glColor3f(0.45, 0.45, 0.45); //grey
	drawFinger(30, 1.5, 33, 0, 2);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(21, -6.7, 1);
	drawSphere(0.9);
	glPopMatrix();

	glPopMatrix();//end move finger tip
	glPopMatrix(); //end of Move finger middle
	glPopMatrix(); //end of move finger root
}
void drawPalm() {

	glPushMatrix();
	glTranslatef(30, -53, 5);
	glRotatef(rLwPalm, 1, 0, 0);
	glTranslatef(-30, 53, -5);

	//palm
	glPushMatrix();
	glTranslatef(-3, -62, 3);

	//move whole palm + fingers
	upperPalm();

	//move whole fingers and lower palm
	lowerPalm();

	thumb();   //thumb

	//fingers
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glRotatef(90, 0, 0, 1);

	//glPushMatrix();
	//glRotatef(rFinger1, 1, 1, 0);
	//finger 1
	finger1();
	//glPopMatrix();

	//finger 2
	finger2();

	//finger 3
	finger3();

	//finger 4
	finger4();
	glPopMatrix(); //end of fingers
//glPopMatrix();//end of move whole fingers and lower palm
	glPopMatrix(); //end of palm
	glPopMatrix(); //end of move whole palm + fingers
}
void drawleftPalm() {

	glPushMatrix();
	glTranslatef(30, -53, 5);
	glRotatef(rLwPalmLeft, 1, 0, 0);
	glTranslatef(-30, 53, -5);

	//palm
	glPushMatrix();
	glTranslatef(-3, -62, 3);

	//move whole palm + fingers
	upperPalm();

	//move whole fingers and lower palm
	lowerPalm();

	thumbLeft();   //thumb

	//fingers
	glPushMatrix();
	glTranslatef(32, -40, 0);
	glRotatef(90, 0, 0, 1);

	//glPushMatrix();
	//glRotatef(rFinger1, 1, 1, 0);
	//finger 1
	finger1Left();
	//glPopMatrix();

	//finger 2
	finger2Left();

	//finger 3
	finger3Left();

	//finger 4
	finger4Left();
	glPopMatrix(); //end of fingers
//glPopMatrix();//end of move whole fingers and lower palm
	glPopMatrix(); //end of palm
	glPopMatrix(); //end of move whole palm + fingers
}
void palm() {
	//palm(rotate angle)
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(-25, -1, -35);
	glPushMatrix();
	glScalef(0.9, 0.9, 0.9);
	glRotatef(-180, 0, 1, 0);
	glTranslatef(-65, -5, -9);
	drawPalm();
	glPopMatrix();//end ori palm
	glPopMatrix(); //end of palm (rotate angle)
}
void leftPalm() {
	//left palm(rotate angle)
	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	glTranslatef(-25, -1, -35);
	glPushMatrix();
	glScalef(0.9, 0.9, 0.9);
	glRotatef(-180, 0, 1, 0);
	glTranslatef(-65, -5, -9);
	drawleftPalm();
	glPopMatrix();//end ori palm
	glPopMatrix(); //end of palm (rotate angle)
}
void drawCross() {

	glBegin(GL_QUADS);
	glVertex2f(18, -10);
	glVertex2f(23, -10);
	glVertex2f(23, -35);
	glVertex2f(18, -35);

	glVertex2f(13, -15);
	glVertex2f(28, -15);
	glVertex2f(28, -20);
	glVertex2f(13, -20);

	glEnd();
}

//new
void drawShield(float x1, float x2, float x3, float sz, float n, float f) {
	
	glBegin(GL_QUADS);
	//front
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(0, 0, n);  //n = 0
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(x1, sz, n);  //x1 = 10   sz = 10
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(x2, sz, n);	//x2 = 30  sz = 10
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(x3, 0, n);	//x3 = 40

	//right
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(x3, 0, n);	//x3 = 40
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(x3, 0, f);  //f = 5
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(x2, sz, f);	//x2 = 30  sz = 10, f = 5
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(x2, sz, n);  //sz = 10

	//top
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(x2, sz, n);  //sz = 10
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(x2, sz, f);	//x2 = 30  sz = 10, f = 5
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(x1, sz, f);  //f = 5
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(x1, sz, n);  //x1 = 10   sz = 10, n = 0

	//left
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(x1, sz, n);  //x1 = 10   sz = 10, n = 0
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(x1, sz, f);  //x1 = 10   sz = 10, f = 5
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(0, 0, f);  //f = 5
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(0, 0, n);  //n = 0

	//bottom
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(0, 0, n);  //n = 0
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(0, 0, f);  //f = 5
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(x3, 0, f);  //x3 = 40  f = 5
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(x3, 0, n);	//x3 = 40


	//back
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(x3, 0, f);  //x3 = 40  f = 5
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(0, 0, f);  //f = 5
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(x1, sz, f);  //x1 = 10   sz = 10, f = 5
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(x2, sz, f);	//x2 = 30  sz = 10, f = 5

	glEnd();

}
//new
void drawShieldTriangle(float x1, float x2, float x3, float sz, float n, float f) {


	glBegin(GL_TRIANGLES);
	//front
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(x2, 0, n);	//x2 = 20  n = 0
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(x1, sz, n);  //x1 = 10 n = 0
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(x3, sz, n);  //x3 = 30   sz = 10
	glEnd();

	glBegin(GL_TRIANGLES);
	//back
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(x2, 0, f);  //x2 = 20   f = 5
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(x1, sz, f);  //x1 = 10 f = 5
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(x3, sz, f);  //x3 = 30   sz = 10  f = 5

	glEnd();

	glBegin(GL_QUADS);

	//right
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(x3, sz, n);	//x3 = 30, sz = 10
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(x3, sz, f);  //f = 5
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(x2, 0, f);  //x2 = 20  f = 5
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(x2, 0, n);	//x2 = 20  n = 0

	//left
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(x2, 0, n);	//x2 = 20  n = 0
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(x2, 0, f);  //x2 = 20  f = 5
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(x1, sz, f);  //x1 = 10   sz = 10, f = 5
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(x1, sz, n);  //x1 = 10   sz = 10, n = 0


	//top
	glTexCoord2f(0.0, 1.0);   //text 1
	glVertex3f(x1, sz, n);  //sz = 10
	glTexCoord2f(1.0, 1.0); //text 2
	glVertex3f(x1, sz, f);	//x2 = 30  sz = 10, f = 5
	glTexCoord2f(1.0, 0.0);  //text 3
	glVertex3f(x3, sz, f);  //f = 5
	glTexCoord2f(0.0, 0.0);  //text 4
	glVertex3f(x3, sz, n);  //x3 = 10   sz = 10, n = 0


	glEnd();
}
//new
void shield() {

	glColor3f(1, 1, 1);
	if (!onTexture) {
		glColor3f(0.75, 0.75, 0.75); //light grey
	}
	if (onTexture) {
		textureArr[0] = loadTexture("metal frame.bmp");
	}
	glPushMatrix();
	drawShield(10, 30, 40, 10, 0, 5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 1, 0, 0);
	drawShield(10, 30, 40, 50, 0, -5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -60, 0);
	drawShieldTriangle(10, 20, 30, 10, 0, 5);
	glPopMatrix();
	glDeleteTextures(1, &textureArr[0]);
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(0, 0, -1);
	if (!onTexture) {
		glColor3f(1, 1, 0);
	}
	else {
		glColor3f(0.75, 0.06, 0.09);//dark red
	}
	drawCross();
	glPopMatrix();
}
//new
void robotRightHand() {
	//whole upper arm
	//glPushMatrix();
	//glTranslatef(30, 30, 5);
	//glTranslatef(0, 25, -5);
	//glRotatef(rUpArm, 1, 0, 0);
	//glTranslatef(0, -25, 5);

	//upper arm (shoulder)
	if (onTexture) {
		glColor3f(0.75, 0.91, 0.95);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	shoulder();
	glDeleteTextures(1, &textureArr[2]);

	//upper Arm
	if (onTexture) {
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	upperArm();
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);

	//whole lower arm
	glPushMatrix();
	glRotatef(50, 0, 1, 0);
	glRotatef(15, 0, 0, 1);

	//move whole lower arm (1)  (elbow + wrist + palm)
	glPushMatrix();
	glTranslatef(30, -12, 5);
	glRotatef(rLwArm, 1, 0, 0);
	glTranslatef(-30, 12, -5);

	//elbow or joint
	armJoint();

	//lower arm
	lowerArm();


	////move whole wrist  (wrist + palm)
	//glPushMatrix();
	//glTranslatef(30, -53, 5);
	//glRotatef(rWrist, 1, 0, 0);
	//glTranslatef(-30, 53, -5);

	//move whole palm
	glPushMatrix();
	glTranslatef(30, -53, 5);
	glRotatef(rWrist, 1, 0, 0);
	glRotatef(rPalm, 0, 1, 0);
	glTranslatef(-30, 53, -5);

	//wrist
	wrist();


	//palm	
	palm();
	//shield -------------------------------------------------------------------
	if (activateS) {

		dSpeed = 2;
		glPushMatrix();
		glTranslatef(-10, 10, -2);							//glTranslatef(0, -60, -23);
		glTranslatef(30, -45, 5);
		//	
													//glPushMatrix();
													//glTranslatef(-0.5, -10, 0);=
		glRotatef(180, 0, 0, 1);
		glTranslatef(-30, 45, -5);


		//	glTranslatef(30, -60, 0);
																	//glPushMatrix();
																	//glTranslatef(-0.5, -10, 0);=
		//	glRotatef(90, 0, 1, 0);
		//	glTranslatef(-30, 60, 0);
																//glRotatef(-70, 1, 0, 0);
																	//glTranslatef(0.5, 10, 0);
		shield();
		glPopMatrix();

		if (!reach3) {

			if (rLwArm >= -170 || rLwArm >= 120) {
				//rSpeed = 1;
				rLwArm -= dSpeed;
				//rLwArmLeft -= rSpeed;
				//if (rWrist > -40) {
				//	rSpeed = 1;
				//	//rWrist -= rSpeed;
				//	rWristLeft -= rSpeed;
				//}
				//else {
				//	//rWrist = rWrist;
				//	rWristLeft = rWristLeft;
				//	//reach = true;
				//}
			}
			else {
				reach3 = true;
			}
		}
		else {
			if (rLwArm <= -171 || rLwArm <= 0) {
				rLwArm += dSpeed;
				//rLwArmLeft += rSpeed;
				/*if (rWrist < 40) {
					rWristLeft += rSpeed;
				}*/
				/*rLwArm = rLwArm;
				rLwArmLeft = rLwArmLeft;
				rWrist = rWrist;*/
			}
			else {
				reach3 = false;
			}


		}
	}
	if (activateS == false && dSpeed == 0) {
		glPushMatrix();
		glTranslatef(-10, 10, -2);							//glTranslatef(0, -60, -23);
		glTranslatef(30, -45, 5);
		//	
													//glPushMatrix();
													//glTranslatef(-0.5, -10, 0);=
		glRotatef(180, 0, 0, 1);
		glTranslatef(-30, 45, -5);


		//	glTranslatef(30, -60, 0);
																	//glPushMatrix();
																	//glTranslatef(-0.5, -10, 0);=
		//	glRotatef(90, 0, 1, 0);
		//	glTranslatef(-30, 60, 0);
																//glRotatef(-70, 1, 0, 0);
																	//glTranslatef(0.5, 10, 0);
		shield();
		glPopMatrix();
	}
	//glPopMatrix();
	//shield -------------------------------------------------------------------

	glPopMatrix();//end of move whole palm

	//glPopMatrix(); //end of move whole wrist + palm

	glPopMatrix(); //end of move whole lower arm (1)

	glPopMatrix(); //end of whole lower arm


}
//new
void robotLeftHand()
{
	//whole left robot hand
	glPushMatrix();
	glTranslatef(0, 0, 10);
	glRotatef(-180, 0, 1, 0);
	glTranslatef(0, 0, -5);

	if (onTexture) {
		glColor3f(0.75, 0.91, 0.95);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	shoulder();
	glDeleteTextures(1, &textureArr[2]);

	//upper Arm
	if (onTexture) {
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	upperArm();
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);

	//whole lower arm
	glPushMatrix();
	glRotatef(50, 0, 1, 0);
	glRotatef(15, 0, 0, 1);

	//move whole lower arm (1)  (elbow + wrist + palm)
	glPushMatrix();
	glTranslatef(30, -12, 5);
	//glRotatef(rLwArm, 1, 0, 0);
	glRotatef(-rLwArmLeft, 1, 0, 0);
	glTranslatef(-30, 12, -5);

	//elbow or joint
	armJoint();

	//lower arm
	lowerArm();


	////move whole wrist  (wrist + palm)
	//glPushMatrix();
	//glTranslatef(30, -53, 5);
	//glRotatef(rWrist, 1, 0, 0);
	//glTranslatef(-30, 53, -5);

	//move whole palm
	glPushMatrix();
	glTranslatef(30, -53, 5);
	glRotatef(-rWristLeft, 1, 0, 0);
	glRotatef(-rPalmLeft - 180, 0, 1, 0);
	glTranslatef(-30, 53, -5);

	//wrist
	wrist();


	leftPalm();

	//waepon -------------------------------------------------------------------
	if (activateW) {

		aSpeed = 2;
		glPushMatrix();
		//glTranslatef(0, -60, -23);
		glTranslatef(3, -40, 60);
		glTranslatef(30, -60, 0);
		//glPushMatrix();
		//glTranslatef(-0.5, -10, 0);=
		glRotatef(-90, 1, 0, 0);
		glTranslatef(-30, 60, 0);


		glTranslatef(30, -60, 0);
		//glPushMatrix();
		//glTranslatef(-0.5, -10, 0);=
		glRotatef(90, 0, 1, 0);
		glTranslatef(-30, 60, 0);
		//glRotatef(-70, 1, 0, 0);
		//glTranslatef(0.5, 10, 0);
		weapon();
		glPopMatrix();

		if (!reach2) {

			if (rLwArmLeft >= -100 || rLwArmLeft >= 100) {
				//rSpeed = 1;
				//rLwArm -= rSpeed;
				rLwArmLeft -= aSpeed;
				//if (rWrist > -40) {
				//	rSpeed = 1;
				//	//rWrist -= rSpeed;
				//	rWristLeft -= rSpeed;
				//}
				//else {
				//	//rWrist = rWrist;
				//	rWristLeft = rWristLeft;
				//	//reach = true;
				//}
			}
			else {
				reach2 = true;
			}
		}
		else {
			if (rLwArmLeft <= -101 || rLwArmLeft <= 0) {
				//rLwArm += rSpeed;
				rLwArmLeft += aSpeed;
				/*if (rWrist < 40) {
					rWristLeft += rSpeed;
				}*/
				/*rLwArm = rLwArm;
				rLwArmLeft = rLwArmLeft;
				rWrist = rWrist;*/
			}
			else {
				reach2 = false;
			}


		}
	}
	if (activateW == false && aSpeed == 0) {
		glPushMatrix();
		//glTranslatef(0, -60, -23);
		glTranslatef(3, -40, 60);
		glTranslatef(30, -60, 0);
		//glPushMatrix();
		//glTranslatef(-0.5, -10, 0);=
		glRotatef(-90, 1, 0, 0);
		glTranslatef(-30, 60, 0);


		glTranslatef(30, -60, 0);
		//glPushMatrix();
		//glTranslatef(-0.5, -10, 0);=
		glRotatef(90, 0, 1, 0);
		glTranslatef(-30, 60, 0);
		//glRotatef(-70, 1, 0, 0);
		//glTranslatef(0.5, 10, 0);
		weapon();
		glPopMatrix();
	}
	//glPopMatrix();
	//weapon -------------------------------------------------------------------

	glPopMatrix();//end of move whole palm

	//glPopMatrix(); //end of move whole wrist + palm

	glPopMatrix(); //end of move whole lower arm (1)

	glPopMatrix(); //end of whole lower arm

	glPopMatrix();  //end of whole left robot hand
}
//END WJ------------------------------------------------------------------------------------------------------------------------

//YX---------------------------------------------------------------------------------------------------------
void drawHead(float r, float sl, float st) {
	GLUquadricObj* sphere = NULL;			//create quadric obj pointer
	sphere = gluNewQuadric();				//create the quadric obj
	gluQuadricDrawStyle(sphere, GLU_FILL);	//GLU_SILHOUETTE, GLU_POINT, GLU_FILL //set  the draw style 
	gluSphere(sphere, r, sl, st);			//draw sphere
	gluDeleteQuadric(sphere);				//delete the quafric obj
}
//new
void drawHeadCone(float r, float h) {
	GLUquadricObj* cylinder = NULL;					//create quadric
	cylinder = gluNewQuadric();						//create the quadric
	gluQuadricDrawStyle(cylinder, GLU_FILL);		//set the draw style
	if (onTexture) {
		gluQuadricTexture(cylinder, true);
	}
	gluCylinder(cylinder, 0.0, r, h, 30, 5);		//draw the cone
	gluDeleteQuadric(cylinder);						//delete the quadric
}
void largeEye() {			//semisphere //Large left eye
	const float PI = 3.141592f;
	GLfloat x3, y3, z3, sliceA, stackA;
	GLfloat r2 = 0.055;
	int sliceNo = 30, stackNo = 30;
	for (sliceA = 0.0; sliceA < 2 * PI; sliceA += PI / sliceNo)
	{
		glBegin(GL_POLYGON);
		for (stackA = 0.0; stackA < PI; stackA += PI / stackNo)
		{
			x3 = r2 * cos(stackA) * sin(sliceA);
			y3 = r2 * sin(stackA) * sin(sliceA);
			z3 = r2 * cos(sliceA);
			glVertex3f(x3, y3, z3);
			x3 = r2 * cos(stackA) * sin(sliceA + PI / stackNo);
			y3 = r2 * sin(stackA) * sin(sliceA + PI / sliceNo);
			z3 = r2 * cos(sliceA + PI / sliceNo);
			glVertex3f(x3, y3, z3);
		}
		glEnd();
	}
}
void Eye() {
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0, 0.0, 0.0);		//black color

	float x = 0, y = 0;				//origin of circle (x,y) (0,0)
	float radius = 0.018;				//radius of circle
	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / noOfTri)
	{
		x2 = x + radius * cos(angle);
		y2 = y + radius * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
}
void smallEye() {					//smallest white right eye
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0, 1.0, 1.0);		//white 

	float x = 0, y = 0;				//origin of circle (x,y) (0,0)
	float radius = 0.007;				//radius of circle
	for (angle = 0; angle <= 2 * PI; angle += (2 * PI) / noOfTri)
	{
		x2 = x + radius * cos(angle);
		y2 = y + radius * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
}

//new
void nose() {
	glBegin(GL_TRIANGLES);
	//glColor3f(0.9, 0.0, 0.0);		//Red
	glVertex2f(-0.017, 0.60);
	glVertex2f(0.017, 0.60);
	glVertex2f(0, 0.57);
	glEnd();
}
//new
void mouth() {						//semicircle
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 0.73, 0.74); //pink

	float x = 0, y = 0;				//origin of circle (x,y) (0,0)
	//float r = 0.025;				//radius of circle
	float r = 0.025;				//radius of circle
	for (angle = PI; angle <= 2 * PI; angle += (2 * PI) / noOfTri)
	{
		x2 = x + r * cos(angle);
		y2 = y + r * sin(angle);
		glVertex2f(x2, y2);
	}
	glEnd();
}
//new
void noseLine() {
	glBegin(GL_LINES);
	//glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0.0, 0.57);
	glVertex2f(0.0, 0.54);
	glEnd();
}
//new
void rightEar() {
	//front face
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.06, 0.65, 0.01);
	glVertex3f(0.12, 0.65, 0.01);
	glVertex3f(0.09, 0.72, 0.01);
	glEnd();

	//right face
	glBegin(GL_POLYGON);
	glColor3f(0.96, 0.21, 0.42);  //dark pink
	glVertex3f(0.12, 0.65, 0.01);
	glVertex3f(0.12, 0.65, -0.01);
	glVertex3f(0.09, 0.72, -0.01);
	glVertex3f(0.09, 0.72, 0.01);
	glEnd();


	//bottom face
	glBegin(GL_POLYGON);
	glColor3f(0.96, 0.21, 0.42);  //dark pink
	glVertex3f(0.06, 0.65, -0.01);
	glVertex3f(0.06, 0.65, 0.01);
	glVertex3f(0.12, 0.65, 0.01);
	glVertex3f(0.12, 0.65, -0.01);
	glEnd();

	//left  face
	glBegin(GL_POLYGON);
	glColor3f(0.96, 0.21, 0.42);  //dark pink
	glVertex3f(0.09, 0.72, 0.01);
	glVertex3f(0.09, 0.72, -0.01);
	glVertex3f(0.06, 0.65, -0.01);
	glVertex3f(0.06, 0.65, 0.01);
	glEnd();

	//back face
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.06, 0.65, -0.01);
	glVertex3f(0.12, 0.65, -0.01);
	glVertex3f(0.09, 0.72, -0.01);
	glEnd();
}
//new
void leftEar() {
	//front face
	glBegin(GL_POLYGON);
	glColor3f(1, 0.62, 0.44);  //peach orange
	glVertex3f(-0.06, 0.65, 0.01);
	glVertex3f(-0.12, 0.65, 0.01);
	glVertex3f(-0.09, 0.72, 0.01);
	glEnd();

	//right face
	glBegin(GL_POLYGON);
	glColor3f(0.96, 0.21, 0.42);  //dark pink
	glVertex3f(-0.12, 0.65, 0.01);
	glVertex3f(-0.12, 0.65, -0.01);
	glVertex3f(-0.09, 0.72, -0.01);
	glVertex3f(-0.09, 0.72, 0.01);
	glEnd();


	//bottom face
	glBegin(GL_POLYGON);
	glColor3f(0.96, 0.21, 0.42);  //dark pink
	glVertex3f(-0.06, 0.65, -0.01);
	glVertex3f(-0.06, 0.65, 0.01);
	glVertex3f(-0.12, 0.65, 0.01);
	glVertex3f(-0.12, 0.65, -0.01);
	glEnd();

	//left  face
	glBegin(GL_POLYGON);
	glColor3f(0.96, 0.21, 0.42);  //dark pink
	glVertex3f(-0.09, 0.72, 0.01);
	glVertex3f(-0.09, 0.72, -0.01);
	glVertex3f(-0.06, 0.65, -0.01);
	glVertex3f(-0.06, 0.65, 0.01);
	glEnd();

	//back face
	glBegin(GL_POLYGON);
	glColor3f(1, 0.62, 0.44);  //peach orange
	glVertex3f(-0.06, 0.65, -0.01);
	glVertex3f(-0.12, 0.65, -0.01);
	glVertex3f(-0.09, 0.72, -0.01);
	glEnd();
}

//NEW ------------------------------------------------------------------------------------------------------------------------------------------
void drawConeLine(float r, float h) {
	GLUquadricObj* cylinder = NULL;  //create quadric object pointer
	cylinder = gluNewQuadric(); //create the quadric obj 
	gluQuadricDrawStyle(cylinder, GLU_LINE); //set the draw style
	gluCylinder(cylinder, 0.0, r, h, 10, 30);  // 0.8 = height 0.2 = topradius & baseradius
	gluDeleteQuadric(cylinder);
}
//ENDYX---------------------------------------------------------------------------------------------------------

void robotView() {
	//else if (wParam == VK_UP) {
		//	if (rxLeg <= 30 && rxLeg > -29) {									//rxLeftBotFoot <= 90 && rxLeftBotFoot > -44.4
		//		rxLeg -= speed;
		//	}
		//}
		//else if (wParam == VK_DOWN) {
		//if (rxLeg < 29 && rxLeg >= -30) { //rxLeftBotFoot < 89 && rxLeftBotFoot >= -45
		//	rxLeg += speed;
		//}
		//}
	//if (qNo == 2) {
		//1
		
	//new jumping
	if (jumping) {

	}

	//new walking
	if (walking) {
		activateW = false;
		activateS = false;
		if (!isOrtho) {
			if (!reach) {
				if (zoom <= 55) {
					zoom += 1;
				}
				else
					reach = true;
			}
			else {
				if (zoom >= -95) {
					zoom -= 1;
				}
				else
					reach = false;
			}
		}
		if (!moveArm) {
			if (rLwArm < 30 && rLwArmLeft > -31) {
				rSpeed = 2;
				rLwArm += rSpeed;
				rLwArmLeft -= rSpeed;
			}
			else {
				rLwArm = rLwArm;
				moveArm = true;
			}
		}
		else {
			if (rLwArm >= 29|| rLwArmLeft <= 31) {
				rSpeed = 2;
				rLwArm -= rSpeed;
				rLwArmLeft += rSpeed;
			}
			else {
				rLwArm = rLwArm;
				moveArm = false;
			}
		}
		if (!moveLeg) {
			if (rxLeg < 30 && rxLeg >= -31) {
				speed = 2;
				rxLeg += speed;
			}
			else {
				rxLeg = rxLeg;
				moveLeg = true;
			}
		}
		else {
			if (rxLeg <= 31 && rxLeg > -30) {
				speed = 2;
				rxLeg -= speed;
			}
			else {
				rxLeg = rxLeg;
				moveLeg = false;
			}
		}
	} //end walking





	//}///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	glPushMatrix();
	glTranslatef(0, 0, z);				//walking


	glPushMatrix();

	//glRotatef(90, 0, 1, 0);				//rotate 90 degree on y
	
	body();
	

	glPushMatrix();						//moving down up on leg
	glTranslatef(5, -3, -3.2);
	glRotatef(-rxLeg, 1, 0, 0);
	glTranslatef(-5, 3, 3.2);
	upperLeftLeg();
	middleLeftLeg();

	glPushMatrix();						//moving down up on left bottom leg and foot
	glTranslatef(-7, -51, -3);
	glRotatef(-rxLeftBotFoot, 1, 0, 0);
	glTranslatef(7, 51, 3); //
	bottomLeftLeg();

	//-8.5, -70, -4.5
	glPushMatrix();						//moving down up on bottom foot
	glTranslatef(-8.5, -70, -4.5);
	glRotatef(-rxLeftFoot, 1, 0, 0);
	glTranslatef(8.5, 70, 4.5);
	leftFoot();

	glPopMatrix();						//moving down up on bottom foot
	glPopMatrix();						//moving down up on bottom leg and foot
	glPopMatrix();						//moving down up on leg


	//right
	glPushMatrix();						//moving down up on leg
	glTranslatef(5, -3, -3.2);
	glRotatef(rxLeg, 1, 0, 0);
	glTranslatef(-5, 3, 3.2);
	upperRightLeg();
	middleRightLeg();
	glPushMatrix();						//moving down up on bottom leg and foot
	glTranslatef(-7, -51, -3);
	glRotatef(-rxRightBotFoot, 1, 0, 0);
	glTranslatef(7, 51, 3);
	bottomRightLeg();
	glPushMatrix();						//moving down up on bottom foot
	glTranslatef(-8.5, -70, -4.5);
	glRotatef(-rxRightFoot, 1, 0, 0);
	glTranslatef(8.5, 70, 4.5);
	rightFoot();
	glPopMatrix();						//moving down up on bottom foot
	glPopMatrix();						//moving down up on bottom leg and foot
	glPopMatrix();						//moving down up on leg
	glPopMatrix();						//rotate 90 degree on y
	


	//WJ -----------------------------------------------------------------------------------------------------------------------
	//whole robot
	glPushMatrix();				//ADDED BY ZF 
	glTranslatef(6.5, 10, -10);  // ADDDED BY ZF
	glPushMatrix();
	glRotatef(turn, 0, 1, 0);


	//left hand
	glPushMatrix();
	glPushMatrix();//ADDED BY ZF 
	glTranslatef(-3, 0, 0);  // ADDDED BY ZF
	robotLeftHand();
	glPopMatrix();//ADDED BY ZF 
	glPopMatrix();

	//right hand
	glPushMatrix();
	robotRightHand();
	glPopMatrix();

	glPopMatrix(); //end whole robot
	glPopMatrix(); //END TRANSLATION ADDED BY ZF 


	//YX------------------------------------------------------------------------
	glPushMatrix();
	glTranslatef(0, -5.3, 0);
	
	glPushMatrix();//ADDED BY ZF
	glTranslatef(0, 10, -5);
	glScalef(100, 100, 100);
	glRotatef(180, 0, 1, 0);

	glPushMatrix();
	glTranslatef(0, -0.055, 0);
	glLineWidth(1.0);

	glPushMatrix();//MOVE UP DOWN HEAD 
	glTranslatef(0, 0.49, 0);
	glRotatef(rh, 1, 0, 0);
	glTranslatef(0, -0.49, 0);

	glPushMatrix();//MOVE UP LEFT RIGHT
	glTranslatef(0, 0.49, 0);
	glRotatef(xh, 0, 1, 0);
	glTranslatef(0, -0.49, 0);

	glPushMatrix();	//2		 		//Head corn
		//glTranslatef(0.0, 0.89, 0.0);
	glTranslatef(0.0, 0.89, 0.0);
	//glTranslatef(0.0, 0.0, -0.1);
	glRotatef(90, 1.0, 0.0, 0.0);
	if (onTexture) {
		glColor3f(1, 1, 1);
		textureArr[2] = loadTexture("rainbow mirror.bmp");
	}
	else {
		glColor3f(1.0, 1.0, 0.0);
	}
	glPushMatrix();			//rotate corn 
	//glTranslatef(0.0, 0.89, 0.0);
	glRotatef(rotateCone, 0.0, 0.0, 1.0);
	rotateCone += cSpeed;
	//glTranslatef(0.0, -0.89, 0.0);
	drawHeadCone(0.03, 0.2);
	glDeleteTextures(1, &textureArr[2]);
	glDisable(GL_TEXTURE_2D);
	if (!onTexture) {
		glColor3f(0.75, 0.75, 0.75); //light grey
	}
	drawConeLine(0.03, 0.2);
	glPopMatrix();			//end rotate corn
	glPopMatrix(); //2

	

	//new
	glPushMatrix();	//3				//Head
	glRotatef(rc, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.60, 0.0);
	glColor3f(0.65, 0.75, 1.0);  //change to light blue color
	drawHead(0.11, 30, 30);
	glPopMatrix(); //3

	glPushMatrix();			//4			//left large eye
	glTranslatef(-0.04, 0.63, -0.06);
	glRotatef(90, 1.0, 1.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	largeEye();
	glPopMatrix();//4

	glPushMatrix();		//5				//right large eye
	glTranslatef(0.04, 0.63, -0.06);
	glRotatef(90, 1.0, 1.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	largeEye();
	glPopMatrix();//5

	glPushMatrix();			//6			//right middle eye
	glTranslatef(0.053, 0.63, -0.115);
	glColor3f(1.0, 0.0, 0.0);
	Eye();
	glPopMatrix();//6

	glPushMatrix();			//7			//left middle eye
	glTranslatef(-0.053, 0.63, -0.115);
	glColor3f(1.0, 0.0, 0.0);
	Eye();
	glPopMatrix();//7

	glPushMatrix();			//8			//left small eye
	glTranslatef(-0.050, 0.63, -0.116);
	glColor3f(0.0, 1.0, 1.0);
	smallEye();
	glPopMatrix();//8

	glPushMatrix();			//9			//right small eye
	glTranslatef(0.050, 0.63, -0.116);
	glColor3f(0.0, 1.0, 1.0);
	smallEye();
	glPopMatrix();//9


	//new
	glPushMatrix();				//10		//nose
	glTranslatef(0.0, 0.0, -0.11);
	glColor3f(1, 0.73, 0.74); //pink
	nose();
	glPopMatrix();//10

	//new
	glPushMatrix();			//11			//nose line
	glTranslatef(0.0, 0.0, -0.105);
	glColor3f(1.0, 1.0, 0.0);
	glLineWidth(1.3);
	noseLine();
	glPopMatrix();//11

	//new
	glPushMatrix();			//12			//mouth
	glTranslatef(0.0, 0.55, -0.09);
	glColor3f(1, 0.73, 0.74); //pink
	mouth();
	glPopMatrix();//12

	//new
	glPushMatrix();			//13			//left ear
	//-0.06, 0.65, 0.01
	//glVertex3f(-0.06, 0.65, 0.01);
	glTranslatef(-0.06, 0.65, 0.01);
	glRotatef(45, 0.0, 0.0, 1.0);
	glTranslatef(0.06, -0.65, -0.01);
	leftEar();
	glPopMatrix();//13

	//new
	glPushMatrix();			//14			//right ear
	//glVertex3f(0.06, 0.65, 0.01);
	glTranslatef(0.06, 0.65, 0.01);
	glRotatef(-45, 0.0, 0.0, 1.0);
	glTranslatef(-0.06, -0.65, -0.01);


	rightEar();
	glPopMatrix();//14

	glPushMatrix();			//15				//left bottom horn
	glTranslatef(-0.055, 0.70, 0.0);
	glRotatef(-90, 1.0, 1.0, 1.0);
	glColor3f(0.0, 1.0, 1.0);
	drawCylinder(0.007, 0.007, 0.04);
	glPopMatrix();//15
	//drawDisk(0.1, 0.5);

	glPushMatrix();			//16				//left upper left horn
	glTranslatef(-0.067, 0.74, 0.0);
	glRotatef(-45, 1.0, 1.0, 1.0);
	glColor3f(0.0, 1.0, 1.0);
	drawCylinder(0.007, 0.007, 0.06);
	glPopMatrix();//16
	//drawDisk(0.1, 0.5);

	glPushMatrix();				//17			//left upper right horn
	glTranslatef(-0.067, 0.74, 0.0);
	glRotatef(190, 1.0, 1.0, 1.0);
	glColor3f(0.0, 1.0, 1.0);
	drawCylinder(0.007, 0.007, 0.05);
	glPopMatrix();//17

	glPushMatrix();				//18			//right bottom horn
	glTranslatef(0.067, 0.69, 0.0);
	glRotatef(220, 1.0, 1.0, 1.0);
	glColor3f(0.0, 1.0, 1.0);
	drawCylinder(0.007, 0.007, 0.04);
	glPopMatrix();//18
	//drawDisk(0.1, 0.5);

	glPushMatrix();					//19		//right upper left horn
	glTranslatef(0.067, 0.73, 0.0);
	glRotatef(-45, 1.0, 1.0, 1.0);
	glColor3f(0.0, 1.0, 1.0);
	drawCylinder(0.007, 0.007, 0.06);
	glPopMatrix();//19
	//drawDisk(0.1, 0.5);

	glPushMatrix();//20
	glTranslatef(0.075, 0.73, 0.0);			//right upper right horn
	glRotatef(190, 1.0, 1.0, 1.0);
	glColor3f(0.0, 1.0, 1.0);
	drawCylinder(0.007, 0.007, 0.05);
	glPopMatrix();//20
	glPopMatrix(); //END MOVE UP DOWN HEAD 
	glPopMatrix(); //END MOVE LEFT RIGHT HEAD 


	//new
	glPushMatrix();				//21			//neck
	glTranslatef(0.0, 0.45, 0.0);
	glRotatef(-120, 1.0, 1.0, 1.0);
	if (!onTexture) {
		glColor3f(0.0, 1.0, 1.0);
	}
	else {
		glColor3f(1, 0.73, 0.74); //pink
	}
	drawCylinder(0.06, 0.03, 0.04);
	glPopMatrix();//21
	glPopMatrix();

	//new
	glPushMatrix();//22
	//glLoadIdentity();
	glTranslatef(0.0, 0.40, 0.0);			//body neck
	glRotatef(-90, -90, 1.0, 1.0);
	if (!onTexture) {
		glColor3f(0.0, 1.0, 1.0);
	}
	else {
		glColor3f(1, 0.73, 0.74); //pink
	}
	drawCylinder(0.06, 0.0, 0.3);
	glPopMatrix();//22

	glPopMatrix();//ADDED BY ZF 
	glPopMatrix();
	//END YX------------------------------------------------------------------------
	glPopMatrix();						//walking

	glDisable(GL_TEXTURE_2D);
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); //depth test turn on
	
	initSkybox();
	glShadeModel(GL_SMOOTH);
	
	glPushMatrix();
		drawSkybox(200);
	glPopMatrix();
	killSkybox();

	projection();



	//glRotatef(0.1, 0, 1, 0);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, ambM);	//red color amb mat
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, difM);	//blue color amb mat
	//glMaterialfv(GL_FRONT, GL_SPECULAR, specM);
	//glMaterialfv(GL_FRONT, GL_SHININESS, shinM);


	glMatrixMode(GL_MODELVIEW); //refer to the model view matrix. 
								//it will translate the object instead of translate the view. 
								//glprojection translate the viewing 
	//glLoadIdentity();			//reset model view matrix (world frame)
	//glTranslatef(tx, 0.0, tz);
	//drawSphere(rs1, 30, 30);  //if radius no same with the tspeed it will change the size when moving back
	//glRotatef(-0.01, 0, 1, 0);
	//glRotatef(90, 0, 1, 0);
	lighting();
	glPushMatrix();
	glTranslatef(0, 0, zoom);
	glPushMatrix();//rotate robot
	glRotatef(rrobot, 0, 1, 0);
	robotView();
	glPopMatrix();//rotate robot
	glPopMatrix();

	glDisable(GL_DEPTH_TEST);
	
	//delete skybox texture 

	//Step 5: Remove texture info
	glDeleteTextures(6, &textureArr[0]);
	glDisable(GL_TEXTURE_2D);
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{ //main function 
	WNDCLASSEX wc; //wc = window class
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		800, 10, 500, 500,
		NULL, NULL, wc.hInstance, NULL); //CW_USEDEFAULT

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));



	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------