#include "MainWidget.h"
#include <QTimer>

MainWidget::MainWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
	ui.setupUi(this);

	xRot = yRot = zRot = 0.0;
	xSpeed = ySpeed = 0.0;
	mySphere = gluNewQuadric();

	eyeX = 0;
	eyeY = 0;
	eyeZ = 150.0;

	//ҹ�ղ�������
	GLfloat  sky_ambient[] = { 0.0,0.0,0.0,1.0 };
	GLfloat  sky_diffuse[] = { 0.0,0.0,0.0,1.0 };
	GLfloat  sky_specular[] = { 0.0,0.0,0.0,1.0 };
	GLfloat  sky_shininess = 20.0;
	GLfloat  sky_radious = 290.0;
	sky = new Star(0, sky_radious, 0, 0, 0, 0, sky_ambient, sky_diffuse, sky_specular, sky_shininess);

	//̫����������
	GLfloat  sun_ambient[] = { 0.0,0.0,0.0,1.0 };
	GLfloat  sun_diffuse[] = { 0.0,0.0,0.0,1.0 };
	GLfloat  sun_specular[] = { 0.0,0.0,0.0,1.0 };
	GLfloat  sun_shininess = 20.0;
	GLfloat  sun_radious = 10.0;
	GLfloat sun_rotSpeed = (GLfloat)360 / 58 / 100;
	sun = new Star(1, sun_radious, 0, 0, 0, sun_rotSpeed, sun_ambient, sun_diffuse, sun_specular, sun_shininess);

	//ˮ��
	GLfloat  mercury_ambient[] = { 0.0,0.0,0.0,1.0 };
	GLfloat  mercury_diffuse[] = { 0.5,0.5,0.5,1.0 };
	GLfloat  mercury_specular[] = { 0.0,0.0,0.0,1.0 };
	GLfloat  mercury_shininess = 20.0;
	GLfloat  mercury_radious = 0.7;
	GLfloat mecury_revSpeed = (GLfloat)360 / 88;
	GLfloat mecury_rotSpeed = (GLfloat)360 / 58 / 100;
	mercury = new Star(2, mercury_radious, 15.2, 0, mecury_revSpeed, mecury_rotSpeed, mercury_ambient, mercury_diffuse, mercury_specular, mercury_shininess);

	//����
	GLfloat  venus_ambient[] = { 0.0,0.0,0.0,1.0 };
	GLfloat  venus_diffuse[] = { 0.8,0.8,0.8,1.0 };
	GLfloat  venus_specular[] = { 0.0,0.0,0.0,1.0 };
	GLfloat  venus_shininess = 20.0;
	GLfloat  venus_radious = 1.24;
	GLfloat venus_revSpeed = (GLfloat)360 / 224;
	GLfloat venus_rotSpeed = (GLfloat)360 / 243 / 100;
	venus = new Star(3, venus_radious, 19.2, 0, venus_revSpeed, venus_rotSpeed, venus_ambient, venus_diffuse, venus_specular, venus_shininess);

	//����
	GLfloat  earth_ambient[] = { 0.1,0.1,0.1,1.0 };
	GLfloat  earth_diffuse[] = { 0.4,0.4,0.8,1.0 };
	GLfloat  earth_specular[] = { 0.0,0.0,0.0,1.0 };
	GLfloat  earth_shininess = 20.0;
	GLfloat  earth_radious = 1.24;
	GLfloat earth_revSpeed = (GLfloat)360 / 365;
	GLfloat earth_rotSpeed = (GLfloat)360 / 1 / 100;
	earth = new Star(4, earth_radious, 26, 0, earth_revSpeed, earth_rotSpeed, earth_ambient, earth_diffuse, earth_specular, earth_shininess);

	//����
	GLfloat  mars_ambient[] = { 0.1,0.1,0.1,1.0 };
	GLfloat  mars_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat  mars_specular[] = { 0.0,0.0,0.0,1.0 };
	GLfloat  mars_shininess = 20.0;
	GLfloat  mars_radious = 1.0;
	GLfloat mars_revSpeed = (GLfloat)360 / 687;
	GLfloat mars_rotSpeed = (GLfloat)360 / 1 / 100;
	mars = new Star(5, mars_radious, 31, 0, mars_revSpeed, mars_rotSpeed, mars_ambient, mars_diffuse, mars_specular, mars_shininess);

	//ľ��
	GLfloat  jupiter_ambient[] = { 0.0, 0.0, 0.0,1.0 };
	GLfloat  jupiter_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat  jupiter_specular[] = { 0.0,0.0,0.0,1.0 };
	GLfloat  jupiter_shininess = 20.0;
	GLfloat  jupiter_radious = 4.0;
	GLfloat jupiter_revSpeed = (GLfloat)360 / 4329;
	GLfloat jupiter_rotSpeed = (GLfloat)360 / 0.3 / 100;
	jupiter = new Star(6, jupiter_radious, 43, 0, jupiter_revSpeed, jupiter_rotSpeed, jupiter_ambient, jupiter_diffuse, jupiter_specular, jupiter_shininess);

	//����
	GLfloat  saturn_ambient[] = { 0.0, 0.0, 0.0,1.0 };
	GLfloat  saturn_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat  saturn_specular[] = { 0.0,0.0,0.0,1.0 };
	GLfloat  saturn_shininess = 20.0;
	GLfloat  saturn_radious = 3.5;
	GLfloat saturn_revSpeed = (GLfloat)360 / 10768;
	GLfloat saturn_rotSpeed = (GLfloat)360 / 1.4 / 100;
	saturn = new Star(7, saturn_radious, 56.5, 0, saturn_revSpeed, saturn_rotSpeed, saturn_ambient, saturn_diffuse, saturn_specular, saturn_shininess);
}

MainWidget::~MainWidget()
{}

void MainWidget::loadGLTextures(QString filename, int id)
{
	qtexture[id].load(filename);
	qtexture[id] = qtexture[id].convertToFormat(QImage::Format_RGBA8888, Qt::AutoColor);
}

void MainWidget::drawStar(Star* s)
{
	glPushMatrix();
	//ָ������
	glTexImage2D(GL_TEXTURE_2D, 0, 3, qtexture[s->texId].width(), qtexture[s->texId].height(), 0,
		GL_RGBA, GL_UNSIGNED_BYTE, qtexture[s->texId].bits());
	//�������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//��ת
	glRotatef(s->revAngle, 0.0, 0.0, 1.0);
	glTranslatef(s->disX, s->disY, 0.0);
	//��ת
	glRotatef(s->rotAngle, 0.0, 0.0, 1.0);
	gluSphere(mySphere, s->radious, 32, 16);
	//���ò�������
	glMaterialfv(GL_BACK, GL_AMBIENT, s->ambient);
	glMaterialfv(GL_BACK, GL_DIFFUSE, s->diffuse);
	glMaterialfv(GL_BACK, GL_SPECULAR, s->specular);
	glMaterialf(GL_BACK, GL_SHININESS, s->shinniness);
	glPopMatrix();
}


void MainWidget::initializeGL()
{
	initializeOpenGLFunctions();

	//��������
	loadGLTextures(":/texture/Texture/sun.jpg", sun->texId);
	loadGLTextures(":/texture/Texture/mercury.jpg", mercury->texId);
	loadGLTextures(":/texture/Texture/venus.jpg", venus->texId);
	loadGLTextures(":/texture/Texture/earth.jpg", earth->texId);
	loadGLTextures(":/texture/Texture/mars.jpg", mars->texId);
	loadGLTextures(":/texture/Texture/saturn.jpg", saturn->texId);
	loadGLTextures(":/texture/Texture/jupiter.jpg", jupiter->texId);
	loadGLTextures(":/texture/Texture/sky.jpg", sky->texId);

	// ������Ӱƽ��
	glShadeModel(GL_SMOOTH);
	// ��ɫ����
	glClearColor(0.0, 0.0, 0.0, 0.0);

	GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //��Դ��λ������������ϵԲ�ģ����������ʽ
	GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //RGBAģʽ�Ļ����⣬Ϊ0
	GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //RGBAģʽ��������⣬ȫ�׹�
	GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //RGBAģʽ�µľ���� ��ȫ�׹�
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

	//�����ƹ�
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	// ������Ȼ���
	glClearDepth(1.0);
	// ������Ȳ���
	glEnable(GL_DEPTH_TEST);
	//��������
	glEnable(GL_TEXTURE_2D);
	// ������Ȳ��Ե�����
	glDepthFunc(GL_LEQUAL);
	// ����ϵͳ��͸�ӽ�������
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	// ʹ��ƽ������
	gluQuadricNormals(mySphere, GL_SMOOTH);
	// ʹ������
	gluQuadricTexture(mySphere, GL_TRUE);
}

void MainWidget::paintGL()
{

	// �����Ļ����Ȼ���
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, texture[sky->texId]);
	drawStar(sky);

	glBindTexture(GL_TEXTURE_2D, texture[sun->texId]);
	drawStar(sun);

	glBindTexture(GL_TEXTURE_2D, texture[mercury->texId]);
	drawStar(mercury);

	glBindTexture(GL_TEXTURE_2D, texture[venus->texId]);
	drawStar(venus);

	glBindTexture(GL_TEXTURE_2D, texture[earth->texId]);
	drawStar(earth);

	glBindTexture(GL_TEXTURE_2D, texture[mars->texId]);
	drawStar(mars);

	glBindTexture(GL_TEXTURE_2D, texture[jupiter->texId]);
	drawStar(jupiter);

	glBindTexture(GL_TEXTURE_2D, texture[saturn->texId]);
	drawStar(saturn);

	//��ת�ٶ�
	yRot += 0.4;
	sun->rotate();
	mercury->revolute();
	mercury->rotate();
	venus->revolute();
	venus->rotate();
	earth->revolute();
	earth->rotate();
	mars->revolute();
	mars->rotate();
	jupiter->revolute();
	jupiter->rotate();
	saturn->revolute();
	saturn->rotate();
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0);
	glFlush();

	update();
}

// ����OpenGL���ڴ�С
void MainWidget::resizeGL(int width, int height)
{
	// ��ֹ���ڴ�С��Ϊ0
	if (height == 0)height = 1;
	// ���õ�ǰ���ӿ�
	glViewport(0, 0, (GLint)width, (GLint)height);
	// ѡ��ͶӰ����
	glMatrixMode(GL_PROJECTION);
	// ����ͶӰ����
	glLoadIdentity();
	// �����ӿڵĴ�С
	gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 600.0);
	// ѡ��ģ�͹۲����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void MainWidget::eyeXup()
{
	eyeX += 1;
}

void MainWidget::eyeXdown()
{
	eyeX -= 1;
}

void MainWidget::eyeZup()
{
	eyeZ += 1;
}

void MainWidget::eyeZdown()
{
	eyeZ -= 1;
}