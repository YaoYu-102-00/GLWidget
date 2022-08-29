#include "GLWidget.h"
#include <qmath.h>

#define PI          3.14
#define ROT_DELTA   0.5f

void qgluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    const GLdouble ymax = zNear * tan(qDegreesToRadians(fovy) / 2.0);
    const GLdouble ymin = -ymax;
    const GLdouble xmin = ymin * aspect;
    const GLdouble xmax = ymax * aspect;
    glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
}

GLWidget::GLWidget(QWidget* parent)
    : QGLWidget(parent)
    , xRot(0.0f)
    , yRot(0.0f)
    , zRot(0.0f)

{    // ���û����˫�������Ȼ���
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    ui.setupUi(this);

}

GLWidget::~GLWidget()
{

}

void GLWidget::initializeGL()
{
    // ������Ӱƽ��
    glShadeModel(GL_SMOOTH);
    // ��ɫ����
    glClearColor(1.0, 1.0, 1.0, 1.0);
    // ������Ȼ���
    glClearDepth(1.0);
    // ������Ȳ���
    glEnable(GL_DEPTH_TEST);
    // ������Ȳ��Ե�����
    glDepthFunc(GL_LEQUAL);
    // ����ϵͳ��͸�ӽ�������
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    // ����2D����ӳ��
    glEnable(GL_TEXTURE_2D);
    // ��������
    loadGLTextures();
}

void GLWidget::paintGL()
{
    renderScene();
    update();
}

void GLWidget::resizeGL(int width, int height)
{
    // ��ֹ���ڴ�С��Ϊ0
    if (height == 0)
    {
        height = 1;
    }
    // ���õ�ǰ���ӿ�
    glViewport(0, 0, (GLint)width, (GLint)height);
    // ѡ��ͶӰ����
    glMatrixMode(GL_PROJECTION);
    // ����ͶӰ����
    glLoadIdentity();
    // �����ӿڵĴ�С
    qgluPerspective(45.0, (GLdouble)width / (GLdouble)height, 0.1, 100.0);
    // ѡ��ģ�͹۲����
    glMatrixMode(GL_MODELVIEW);
    // ����ͶӰ����
    glLoadIdentity();
}

// ����������
void GLWidget::drawCube()
{
    glBegin(GL_QUAD_STRIP);         //���͹�����
    glColor3f(1, 0, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3f(1, 1, 0);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0, 1, 0);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glColor3f(0, 1, 1);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glColor3f(1, 0, 0);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glColor3f(1, 1, 0);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glColor3f(0, 1, 0);
    glVertex3f(0.0f, 0.0f, -1.0f);
    glColor3f(0, 1, 1);
    glVertex3f(0.0f, 1.0f, -1.0f);
    glColor3f(1, 0, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3f(1, 1, 0);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();
    glBegin(GL_QUAD_STRIP);
    glColor3f(0, 0, 1);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3f(1, 0, 1);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glColor3f(0, 1, 0);
    glVertex3f(0.0f, 0.0f, -1.0f);
    glColor3f(1, 0, 0);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glColor3f(1, 1, 0);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(1, 0, 1);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glColor3f(0, 0, 1);
    glVertex3f(0.0f, 1.0f, -1.0f);
    glColor3f(1, 0, 0);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glEnd();
}

// ����Բ��
void GLWidget::drawCircle()
{
    glBegin(GL_TRIANGLE_FAN);           //����������������δ�
    glVertex3f(0.0f, 0.0f, 0.0f);
    int i = 0;
    for (i = 0; i <= 360; i += 15)
    {
        float p = i * 3.14 / 180;
        glColor3f(sin(p), cos(p), tan(p));
        glVertex3f(sin(p), cos(p), 0.0f);
    }
    glEnd();
}

// ����Բ����
void GLWidget::drawCylinder()
{
    // ���������κ��ı��εȻ���ͼԪ���Ƶ���ԲԲ��������ԭ�㣬 �뾶Ϊ r����Ϊ h�������� z �᷽���Բ����
    // �����ö���ı���,�����ö������������ʾ
    glBegin(GL_QUAD_STRIP);//��������ı��δ�
    int i = 0;
    for (i = 0; i <= 360; i += 15)
    {
        float p = i * 3.14 / 180;
        glVertex3f(sin(p), cos(p), 1.0f);
        glVertex3f(sin(p), cos(p), 0.0f);
    }
    glEnd();
    //bottom circle
    glColor3f(1, 0, 0);
    drawCircle();
    glTranslatef(0, 0, 1);
    //top circle
    glColor3f(0, 0, 1);
    drawCircle();
    glColor3f(0, 1, 0);
}

// ����Բ׶��
void GLWidget::drawCone()
{
    glBegin(GL_QUAD_STRIP);//��������ı��δ�
    int i = 0;
    for (i = 0; i <= 360; i += 15)
    {
        float p = i * 3.14 / 180;
        glColor3f(sin(p), cos(p), 1.0f);
        glVertex3f(0, 0, 1.0f);
        glVertex3f(sin(p), cos(p), 0.0f);
    }
    glEnd();
    //bottom circle
    glColor3f(0, 1, 1);
    drawCircle();
}

// �����������
void GLWidget::drawTetrahedron()
{
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-1, -1, 0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-1, 1, 0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(1, 1, 0);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(1, -1, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0, -1, 0.707);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-1, -1, 0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(1, -1, 0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(0, 0, 1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(1, 0, 0.707);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(1, -1, 0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(1, 1, 0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(0, 0, 1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 1, 0.707);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(1, 1, 0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(-1, 1, 0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(0, 0, 1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
    glNormal3f(-1, 0, 0.707);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(-1, 1, 0);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-1, -1, 0);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0, 0, 1.2);
    glEnd();
}

// ��������
// ��������Ϊ��x��y��z������İ뾶Ϊradius��M��N�ֱ��ʾ����ĺ����򱻷ֳɶ��ٷ�
void GLWidget::drawSphere(GLfloat xx, GLfloat yy, GLfloat zz,
    GLfloat radius, GLfloat M, GLfloat N)
{
    // ѡ��ʹ�õ�����
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    float step_z = PI / M;
    float step_xy = 2 * PI / N;
    float x[4], y[4], z[4];

    float angle_z = 0.0;
    float angle_xy = 0.0;
    int i = 0, j = 0;
    glBegin(GL_QUADS);
    for (i = 0; i < M; i++)
    {
        angle_z = i * step_z;

        for (j = 0; j < N; j++)
        {
            angle_xy = j * step_xy;

            x[0] = radius * sin(angle_z) * cos(angle_xy);
            y[0] = radius * sin(angle_z) * sin(angle_xy);
            z[0] = radius * cos(angle_z);

            x[1] = radius * sin(angle_z + step_z) * cos(angle_xy);
            y[1] = radius * sin(angle_z + step_z) * sin(angle_xy);
            z[1] = radius * cos(angle_z + step_z);

            x[2] = radius * sin(angle_z + step_z) * cos(angle_xy + step_xy);
            y[2] = radius * sin(angle_z + step_z) * sin(angle_xy + step_xy);
            z[2] = radius * cos(angle_z + step_z);

            x[3] = radius * sin(angle_z) * cos(angle_xy + step_xy);
            y[3] = radius * sin(angle_z) * sin(angle_xy + step_xy);
            z[3] = radius * cos(angle_z);
            for (int k = 0; k < 4; k++)
            {
                glColor3f(sin(angle_z), cos(angle_z), tan(angle_z));
                //glTexCoord2f(0.1f, 0.1f);
                glVertex3f(xx + x[k], yy + y[k], zz + z[k]);
            }
        }
    }
    glEnd();
}

// ����Բ��
// ��뾶Radius��С�뾶TubeRadius������Sides�� ����Rings
void GLWidget::DrawTorus(double Radius, double TubeRadius, int Sides, int Rings)
{
    double sideDelta = 2.0 * PI / Sides;
    double ringDelta = 2.0 * PI / Rings;
    double theta = 0;
    double cosTheta = 1.0;
    double sinTheta = 0.0;

    double phi, sinPhi, cosPhi;
    double dist;
    glColor3f(1, 0, 0);
    for (int i = 0; i < Rings; i++)
    {
        double theta1 = theta + ringDelta;
        double cosTheta1 = cos(theta1);
        double sinTheta1 = sin(theta1);

        glBegin(GL_QUAD_STRIP);
        phi = 0;
        for (int j = 0; j <= Sides; j++)
        {
            phi = phi + sideDelta;
            cosPhi = cos(phi);
            sinPhi = sin(phi);
            dist = Radius + (TubeRadius * cosPhi);

            glNormal3f(cosTheta * cosPhi, sinTheta * cosPhi, sinPhi);
            glColor3f(cosTheta, sinTheta, sinPhi);
            glVertex3f(cosTheta * dist, sinTheta * dist, TubeRadius * sinPhi);

            glNormal3f(cosTheta1 * cosPhi, sinTheta1 * cosPhi, sinPhi);
            glColor3f(cosTheta1, sinTheta1, sinPhi);
            glVertex3f(cosTheta1 * dist, sinTheta1 * dist, TubeRadius * sinPhi);
        }
        glEnd();
        theta = theta1;
        cosTheta = cosTheta1;
        sinTheta = sinTheta1;
    }
}

// ��������
void GLWidget::loadGLTextures()
{
    QImage tex1, buf1;
    QImage tex2, buf2;
    if (!buf1.load(":/data/qt-logo.jpg"))
    {
        // ������벻�ɹ����Զ�����һ��128*128��32λɫ����ɫͼƬ��
        qWarning("Could not read image file!");
        QImage dummy(128, 128, QImage::Format_RGB32);
        dummy.fill(Qt::green);
        buf1 = dummy;
    }

    if (!buf2.load(":/data/qt-wood.jpg"))
    {
        // ������벻�ɹ����Զ�����һ��128*128��32λɫ����ɫͼƬ��
        qWarning("Could not read image file!");
        QImage dummy(128, 128, QImage::Format_RGB32);
        dummy.fill(Qt::green);
        buf2 = dummy;
    }

    //***********************************************//
    // ����0��qt-logo
    //***********************************************//
    //ת������������
    tex1 = QGLWidget::convertToGLFormat(buf1);
    // ��������
    glGenTextures(1, &texture[0]);
    // ʹ������λͼ�������ɵĵ�������,����������texture[0]�󶨵�����Ŀ����
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    // WRAP�������������곬��[0,0]��[1,1]�ķ�Χ����ô�����أ�
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    // Filter��������������ӳ�䵽����λ��(127.34,255.14)����ô��?
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // ������
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    // �����������CPU����GPU��������Ϊ��ǰ����
    // �ڴ���һ����ʱ��������ã�����Ч�ʷǳ��͡�
    // ������ʱ���Բμ�����󶨡�
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tex1.width(), tex1.height(), 0,
        GL_RGBA, GL_UNSIGNED_BYTE, tex1.bits());

    //***********************************************//
    // ����0��qt-logo
    //***********************************************//
    tex2 = QGLWidget::convertToGLFormat(buf2);
    glGenTextures(1, &texture[1]);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tex2.width(), tex2.height(), 0,
        GL_RGBA, GL_UNSIGNED_BYTE, tex2.bits());
    // ʹ������
    // ���ȵ���glEnable( GL_TEXTURE_2D )��������2D����;
    // Ȼ�����ͼ�Σ�����Ϊÿ������ָ��ST����;
    // ������glDisable( GL_TEXTURE_2D ).
}

// ������Ⱦ
void GLWidget::renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
    renderBasicShape();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3, 0, 0);
    renderTextureCube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3, 0, 0);
    renderTextureCylinder();
    glPopMatrix();
}

// ��Ⱦ����ͼ��
void GLWidget::renderBasicShape()
{
    static float fRotAngle = 0.0f;
    fRotAngle += ROT_DELTA;
    if (fRotAngle > 360)
        fRotAngle = 0;

    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(-3, 3, -12);
    glRotatef(fRotAngle, 1, 1, 1);
    drawCylinder();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(0, 3, -12);
    glRotatef(fRotAngle, 1, 1, 1);
    drawTetrahedron();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(3, 3, -12);
    glRotatef(fRotAngle, 1, 1, 1);
    drawCircle();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(0, 0, -15);
    glRotatef(fRotAngle, 0, 1, 0);
    drawSphere();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 1, 1);
    glTranslatef(-3, -3, -12);
    glRotatef(fRotAngle, 1, 1, 1);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0, 1);
    glTranslatef(0, -3, -12);
    glRotatef(fRotAngle, 1, 1, 1);
    DrawTorus();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(3, -3, -12);
    glRotatef(fRotAngle, 1, 1, 1);
    drawCone();
    glPopMatrix();
}

// ��Ⱦ����
void GLWidget::renderTextureCube()
{
    // ����ӳ��
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.0f, 0.0f, -12.0f);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);
    // ʹ������λͼ�������ɵĵ�������,����������texture[0]�󶨵�����Ŀ����
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(1.0, -1.0, -1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0, -1.0, -1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glEnd();
    xRot += ROT_DELTA;
    if (xRot > 360) xRot = 0;
    yRot += ROT_DELTA;
    if (yRot > 360) yRot = 0;
    zRot += ROT_DELTA;
    if (zRot > 360) zRot = 0;
}

void GLWidget::renderTextureCylinder()
{
    // ����ӳ��
    glTranslatef(0.0f, 0.0f, -12.0f);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    //glRotatef(yRot, 0.0, 1.0, 0.0);
    //glRotatef(zRot, 0.0, 0.0, 1.0);
    // ѡ��ʹ�õ�����
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    // ���������κ��ı��εȻ���ͼԪ���Ƶ���ԲԲ��������ԭ�㣬 �뾶Ϊ r����Ϊ h�������� z �᷽���Բ����
    // �����ö���ı���,�����ö������������ʾ
    glBegin(GL_QUAD_STRIP);//��������ı��δ�
    int i = 0;
    for (i = 0; i <= 360; i += 15)
    {
        float p = i * 3.14 / 180;
        //p��Բ�������Ӧ�ģ� ����������ĺ�������Բ��ɨ���ĽǶ�һ��ı䣬���ܹ�������ͼ��ˢ����ȥ�ˣ�
        //������������Ϊͼ��ĸ߶Ⱥ�����߶ȵĶ�Ӧ��������ʵĲ����Ǹ���ʵ�ʲ��Եõ���
        glTexCoord2f(p / 10, 0.1f);
        glVertex3f(sin(p), cos(p), 1.0f);   //��� 1.0fָ�����Ǹ߶�h
        glTexCoord2f(p / 10, 0.0f);
        glVertex3f(sin(p), cos(p), 0.0f);
    }
    glEnd();
    //bottom circle
    glBegin(GL_TRIANGLE_FAN);           //����������������δ�
    glTexCoord2f(0.0f, 0.0f);           //������ͼ(0, 0)ӳ�䵽Բ��
    glVertex3f(0.0f, 0.0f, 0.0f);
    for (i = 0; i <= 360; i += 15)
    {
        float p = i * 3.14 / 180;
        glTexCoord2f(1.0f, 0.0f);       //������ͼ(1, 0)ӳ�䵽Բ��
        glVertex3f(sin(p), cos(p), 0.0f);
    }
    glEnd();
    glTranslatef(0, 0, 1);              //�趨�߶�Ϊ1�����ϵ���
    //top circle
    glBegin(GL_TRIANGLE_FAN);           //����������������δ�
    glTexCoord2f(0.0f, 0.0f);           //������ͼ(0, 0)ӳ�䵽Բ��
    glVertex3f(0.0f, 0.0f, 0.0f);
    for (i = 0; i <= 360; i += 15)
    {
        float p = i * 3.14 / 180;
        glTexCoord2f(1.0f, 0.0f);       //������ͼ(1, 0)ӳ�䵽Բ��
        glVertex3f(sin(p), cos(p), 0.0f);
    }
    glEnd();

    xRot += ROT_DELTA;
    if (xRot > 360) xRot = 0;
    yRot += ROT_DELTA;
    if (yRot > 360) yRot = 0;
    zRot += ROT_DELTA;
    if (zRot > 360) zRot = 0;
}
