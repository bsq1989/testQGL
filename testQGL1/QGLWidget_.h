#pragma once

#include <QOpenGLWidget>
#include <QGLShaderProgram> 
#include <QGLBuffer>
#include <QOpenGLFunctions> 
#include <QOpenGLTexture>
#include <QTimer>
class QGLWidget_ : public QOpenGLWidget,protected QOpenGLFunctions
{
	Q_OBJECT

public:
	QGLWidget_(QWidget *parent);
	~QGLWidget_();
protected:
	virtual void initializeGL();
	virtual void paintGL();
	virtual void resizeGL(int w, int h);
private:
	QGLShaderProgram m_VertexShader;
	QGLShaderProgram m_FragmentShader;
	QGLBuffer m_VertexBuff;
	QGLBuffer m_IndexBuff;
	QOpenGLTexture* m_Texture1;
	QOpenGLTexture* m_Texture2;
	QImage m_TextureImg;
	QImage m_TextureImg1;
	void InitializeShader();
	void InitializeBuffer();
	void InitializeTexture();


// 	unsigned int m_texture;
// 	unsigned int m_texture1;
	const float m_mixValue;

	int m_ViewPortWidth;
	int m_ViewPortHeight;

	//timer for rotation
	QTimer m_timer;
	int m_RotateCnt;
	float m_angleStep;
private slots:
	void refresh();

};
