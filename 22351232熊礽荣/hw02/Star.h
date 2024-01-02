#pragma once
#include <QOpenGLWidget>

class Star
{
public:
    Star();
    Star(int tex, GLfloat r, GLfloat x, GLfloat y, GLfloat revS, GLfloat rotS, GLfloat a[], GLfloat d[], GLfloat p[], GLfloat s);
    ~Star();
    //��ת
    void revolute();
    //��ת
    void rotate();
    //����뾶
    float radious;
    //����λ��
    GLfloat disX;
    GLfloat disY;
    //����id
    int texId;
    //���������
    GLfloat* ambient;
    //������
    GLfloat* diffuse;
    //���淴��
    GLfloat* specular;
    //���淴��ǿ��
    GLfloat shinniness;
    //��ת�ٶ�
    GLfloat revSpeed;
    //��ת�ٶ�
    GLfloat rotSpeed;
    //��ת�Ƕ�
    float revAngle;
    //��ת�Ƕ�
    float rotAngle;
};

