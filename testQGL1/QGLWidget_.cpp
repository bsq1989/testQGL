#include "QGLWidget_.h"
#include <QDebug>

QGLWidget_::QGLWidget_(QWidget *parent)
	: QOpenGLWidget(parent)
	, m_IndexBuff(QGLBuffer(QGLBuffer::IndexBuffer))
	, m_mixValue(0.2)
	, m_ViewPortWidth(800)
	, m_ViewPortHeight(600)
	, m_RotateCnt(0)
	,m_angleStep(10.0)
{


}

QGLWidget_::~QGLWidget_()
{
	delete m_Texture1;
	delete m_Texture2;

}
void QGLWidget_::InitializeShader()
{
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aColor;\n"
		"out vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos, 1.0);\n"
		"   ourColor = aColor;\n"
		"}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(ourColor, 1.0f);\n"
		"}\n\0";
	QString shaderFile;
	shaderFile = "texture.vs";
	qDebug()<<m_VertexShader.addShaderFromSourceFile(QGLShader::Vertex, shaderFile);
	shaderFile = "texture.fs";
	qDebug() << m_VertexShader.addShaderFromSourceFile(QGLShader::Fragment, shaderFile);
	qDebug() << m_VertexShader.link();
}
void QGLWidget_::InitializeBuffer()
{
// 	float vertices[] = {
// 		0.5f, 0.5f, 0.0f, // top right
// 		0.5f, -0.5f, 0.0f, // bottom right
// 		-0.5f, -0.5f, 0.0f, // bottom left
// 		-0.5f, 0.5f, 0.0f // top left  
// 	};
	
// 	float vertices[] = {
// 		// positions          // colors           // texture coords
// 		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
// 		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
// 		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
// 		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
// 	};

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

// 	unsigned int indices[] = {
// 		0, 1, 3, // first triangle
// 		1, 2, 3  // second triangle
// 	};

	m_VertexBuff.create();
	m_VertexBuff.setUsagePattern(QGLBuffer::UsagePattern::StaticDraw);
	m_VertexBuff.bind();
 	m_VertexBuff.allocate(vertices, sizeof(vertices));
//   	m_IndexBuff.create();
//   	m_IndexBuff.setUsagePattern(QGLBuffer::UsagePattern::StaticDraw);
//  	m_IndexBuff.bind();
//   	m_IndexBuff.allocate(indices, sizeof(indices));
	//load texture

}
void QGLWidget_::InitializeTexture()
{
	/*
	//texture 1
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	QImage temp;
	qDebug() << temp.load("container.jpg", "JPG");
	m_TextureImg = temp.convertToFormat(QImage::Format_RGB888);
	qDebug() << m_TextureImg.depth();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
	m_TextureImg.width(), m_TextureImg.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_TextureImg.bits());
	glGenerateMipmap(GL_TEXTURE_2D);
	//texture 2
	glGenTextures(1, &m_texture1);
	glBindTexture(GL_TEXTURE_2D, m_texture1); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	qDebug() << temp.load("awesomeface.png", "PNG");
	m_TextureImg1 = temp.convertToFormat(QImage::Format_RGB888);
	m_TextureImg1 = m_TextureImg1.mirrored();
	qDebug() << m_TextureImg1.depth();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
	m_TextureImg1.width(), m_TextureImg1.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, m_TextureImg1.bits());
	glGenerateMipmap(GL_TEXTURE_2D);

	*/
	//	//QOpenGLTexturel

	QImage temp;
	temp.load("container.jpg", "JPG");
	m_TextureImg = temp.convertToFormat(QImage::Format_RGB888);
	m_Texture1 = new QOpenGLTexture(m_TextureImg.mirrored());
	m_Texture1->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::WrapMode::Repeat);
	m_Texture1->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::WrapMode::Repeat);
	m_Texture1->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	m_Texture1->setMagnificationFilter(QOpenGLTexture::Linear);

	temp.load("awesomeface.png", "PNG");
	m_TextureImg1 = temp.convertToFormat(QImage::Format_RGB888);

	m_Texture2 = new QOpenGLTexture(m_TextureImg1.mirrored());
	m_Texture2->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::WrapMode::Repeat);
	m_Texture2->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::WrapMode::Repeat);
	m_Texture2->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	m_Texture2->setMagnificationFilter(QOpenGLTexture::Linear);
}
void QGLWidget_::initializeGL()
{
	setGeometry(0, 0, m_ViewPortWidth, m_ViewPortHeight);
	initializeOpenGLFunctions();
	InitializeShader();
	InitializeBuffer();
	InitializeTexture();
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	connect(&m_timer, SIGNAL(timeout()), this, SLOT(refresh()));
	m_timer.start(1000);
}
void QGLWidget_::refresh()
{
 	m_RotateCnt++;
 	/*paintGL();*/
	update();
}
void QGLWidget_::paintGL()
{
	// bind Texture
	QVector3D cubePositions[] = {
		QVector3D(0.0f,  0.0f,  0.0f),
		QVector3D(2.0f,  5.0f, -15.0f),
		QVector3D(-1.5f, -2.2f, -2.5f),
		QVector3D(-3.8f, -2.0f, -12.3f),
		QVector3D(2.4f, -0.4f, -3.5f),
		QVector3D(-1.7f,  3.0f, -7.5f),
		QVector3D(1.3f, -2.0f, -2.5f),
		QVector3D(1.5f,  2.0f, -2.5f),
		QVector3D(1.5f,  0.2f, -1.5f),
		QVector3D(-1.3f,  1.0f, -1.5f)
	};

	// render
	// ------
	m_VertexShader.bind();
	//QOpenGLTexturel
	m_Texture1->bind();
	m_Texture2->bind(1);


	
	m_VertexShader.setUniformValue("texture1", 0);
	m_VertexShader.setUniformValue("texture2", 1);

	m_VertexShader.setUniformValue("mixValue", m_mixValue);

	//perform transformation
	QMatrix4x4 model;
	QMatrix4x4 view;
	QMatrix4x4 projection;

	//initialize to identity matrix
	model.setToIdentity();
	view.setToIdentity();
	projection.setToIdentity();

	//transform 
//	model.rotate(m_RotateCnt*m_angleStep, QVector3D(1.0, 0.0, 0.0));
//	view.translate(QVector3D(0.0, 0.0, -3.0));
	float radius = 10.0f;
	QVector4D temp;
	float camX = sin(m_RotateCnt*m_angleStep/180.0*3.1415926) * radius;
	float camZ = cos(m_RotateCnt*m_angleStep / 180.0*3.1415926) * radius;
	view.lookAt(QVector3D(camX, 0.0, camZ), QVector3D(0.0, 0.0, 0.0), QVector3D(0.0, 1.0, 0.0));

	projection.perspective(45, float(m_ViewPortWidth) / (float)m_ViewPortHeight, 0.1, 100);

	
	m_VertexShader.setUniformValue("view", view);
	m_VertexShader.setUniformValue("projection", projection);

	m_VertexShader.enableAttributeArray("aPos");
//	m_VertexShader.enableAttributeArray("aColor");
	m_VertexShader.enableAttributeArray("aTexCoord");

	m_VertexShader.setAttributeBuffer("aPos", GL_FLOAT, 0, 3, 5 * sizeof(float));
 //	m_VertexShader.setAttributeBuffer("aColor", GL_FLOAT, 3 * sizeof(float), 3, 8 * sizeof(float));
	m_VertexShader.setAttributeBuffer("aTexCoord", GL_FLOAT, 3 * sizeof(float), 2, 5 * sizeof(float));

	for (unsigned int i = 0; i < 10; i++)
	{
		model.setToIdentity();
		model.translate(cubePositions[i]);
//		model.rotate(m_RotateCnt*m_angleStep, QVector3D(1.0, 0.0, 0.0));
		float angle = 20.0f * i;
		model.rotate(angle, QVector3D(1.0f, 0.3f, 0.5f));
		m_VertexShader.setUniformValue("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

	}
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
 	m_VertexShader.disableAttributeArray("aPos");
//	m_VertexShader.disableAttributeArray("aColor");
	m_VertexShader.disableAttributeArray("aTexCoord");

}

void QGLWidget_::resizeGL(int w, int h)
{
	glViewport(0, 0, m_ViewPortWidth, m_ViewPortHeight);
}