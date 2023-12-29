#include "MyOpenGLWidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget*parent)
	: QOpenGLWidget(parent)
{

}

MyOpenGLWidget::~MyOpenGLWidget()
{}

void MyOpenGLWidget::initializeGL()
{
	initializeOpenGLFunctions();

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f, 
		0.0f, 0.5f, 0.0f
	};

	// ����һ��VAO
	glGenVertexArrays(1, &VAO);

	// ����VBO�����CPU��GPU�����ݴ���
	GLuint VBO;
	// ����һ��VBO
	glGenBuffers(1, &VBO);
	
	// VAO ��, ���и� GL_ARRAY_BUFFER �й�ϵ�Ĳ���״̬���������¼����
	glBindVertexArray(VAO);
	// VBO �� GPU�����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ���� ���� GPU������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// ���� VAO �� VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// ������ɫ��
	// ������ɫ��
	QOpenGLShader vertexShader(QOpenGLShader::Vertex);
	vertexShader.compileSourceFile("shader/triangle.vert");
	// Ƭ����ɫ��
	QOpenGLShader fragmentShader(QOpenGLShader::Fragment);
	fragmentShader.compileSourceFile("shader/triangle.frag");
	// ��ӵ���ɫ����������
	shaderProgram.addShader(&vertexShader);
	shaderProgram.addShader(&fragmentShader);
	shaderProgram.link();

	time.start();
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
}

void MyOpenGLWidget::paintGL()
{
	// �����ɫ�����Ʊ���
	glClearColor(qAbs(qSin((float)time.elapsed() / 1000)), 0.4, 0.6, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	shaderProgram.bind();
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	GLuint loc = shaderProgram.uniformLocation("outColor");
	shaderProgram.setUniformValue(loc, QVector4D(0.4, qAbs(qSin((float)time.elapsed() / 1000)), 0.3, 1));

	update();
}
