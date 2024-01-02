#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <GL/GLU.h>

#include "star.h"
#include "ui_MainWidget.h"

class MainWidget : public QOpenGLWidget, QOpenGLFunctions_3_3_Core
{
	Q_OBJECT

public:
	MainWidget(QWidget *parent = nullptr);
	~MainWidget();

    void eyeXup();
    void eyeXdown();
    void eyeZup();
    void eyeZdown();
protected:
    //������Ⱦ����
    void initializeGL();
    //���ƴ���
    void paintGL();
    //��Ӧ���ڵĴ�С�仯
    void resizeGL(int width, int height);
    //��������
    void loadGLTextures(QString filename, int id);
    //��������
    void drawStar(Star* s);

    GLfloat xRot, yRot, zRot;
    //����洢����
    GLuint texture[13];
    QImage qtexture[13];
    //��������X���Y������ת���ٶ�
    GLfloat xSpeed, ySpeed;

    GLUquadricObj* mySphere;

    Star* sky;
    Star* sun;
    Star* mercury;
    Star* venus;
    Star* earth;
    Star* mars;
    Star* jupiter;
    Star* saturn;
public:
    GLfloat eyeX;
    GLfloat eyeY;
    GLfloat eyeZ;

	Ui::MainWidgetClass ui;
};
