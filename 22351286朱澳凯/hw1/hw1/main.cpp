#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

double rtri = 60.0;
double rquad = 60.0;

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// �����Ļ����Ȼ���
	glMatrixMode(GL_MODELVIEW);//ģ����ͼ����4x4
	glLoadIdentity();							// ���õ�ǰ��ģ�͹۲����
	//glutSolidSphere(1.0, 400, 16);  //�L�uһ�����w
	/*��������glLoadIdentity()֮����ʵ���Ͻ���ǰ���Ƶ�����Ļ���ģ�X������������ң�Y������������ϣ�Z������������⡣OpenGL��Ļ���ĵ�����ֵ��X��Y���ϵ�0.0f�㡣�������������ֵ�Ǹ�ֵ����������ֵ��������Ļ��������ֵ��������Ļ�׶��Ǹ�ֵ��������Ļ��Ǹ�ֵ���Ƴ���Ļ������ֵ��
	 glTranslatef(x, y, z)���� X, Y �� Z ���ƶ�������ǰ��Ĵ�������Ĵ�������X������1.5����λ��Y�᲻��(0.0f)�����������Ļ6.0f����λ��ע����glTranslatef(x, y, z)�е����ƶ���ʱ���������������Ļ�����ƶ�����������뵱ǰ���ڵ���Ļλ�á�*/

	glPushMatrix();
	glTranslatef(-2.5f, 0.0f, -6.0f);						// ���� 1.5 ��λ����������Ļ 6.0
	//glRotatef(rtri, 0.0f, 1.0f, 0.0f);				// ��Y����ת������

	glBegin(GL_TRIANGLES);							// ����������
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0f, 1.0f, 0.0f);					// �϶���
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-0.5f, 0.0f, 0.0f);					// ����
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.5f, 0.0f, 0.0f);					// ����
	glEnd();								// �����λ��ƽ���
	glPopMatrix();

	//��������׶
	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(4.0f, -0.5f, -6.0f);
	glRotatef(rtri, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	//�L�u����c �����
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	//�҂���
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	//�Һ����
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);

	//������
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);

	glEnd();
	glPopMatrix();
	//���Ʋ��
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -8.0f);
	glutWireTeapot(2.0f);
	glPopMatrix();

	//�O�î�ǰʹ�õ��ɫ���ɫ
	glColor3f(1.0, 1.0, 1.0);
	glFlush();

	rtri += 0.3;
	rquad += 0.2;
}

void myReshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	//�������
	glMatrixMode(GL_PROJECTION);//ͶӰ����4x4
	glLoadIdentity();
	gluPerspective(60.0f, (GLdouble)w / (GLdouble)h, 1.0f, 800.0f);
}
/*��������glLoadIdentity()֮����ʵ���Ͻ���ǰ���Ƶ�����Ļ���ģ�X������������ң�Y������������ϣ�Z������������⡣OpenGL��Ļ���ĵ�����ֵ��X��Y���ϵ�0.0f�㡣�������������ֵ�Ǹ�ֵ����������ֵ��������Ļ��������ֵ��������Ļ�׶��Ǹ�ֵ��������Ļ��Ǹ�ֵ���Ƴ���Ļ������ֵ��
 glTranslatef(x, y, z)���� X, Y �� Z ���ƶ���ע����glTranslatef(x, y, z)�е����ƶ���ʱ���������������Ļ�����ƶ�����������뵱ǰ���ڵ���Ļλ�ã��Ӿ��壩��*/


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("��һ��OpenGL����");

	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}