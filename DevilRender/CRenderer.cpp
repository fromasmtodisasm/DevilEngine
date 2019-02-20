#include <windows.h>
#include <gl/gl.h>
#include <gl/GLU.h>
#include "CRenderer.h"
#include <IInput.h>

CRenderer::CRenderer()
{
	m_pModel = new Model("model.obj");
	ClearColor.r = ClearColor.g = ClearColor.b = 0.2;
}

CRenderer::~CRenderer()
{

}

void CRenderer::RenderModel()
{
	for (int i = 0; i < m_pModel->nfaces(); i++) {
		std::vector<int> face = m_pModel->face(i);
		//glColor3f(1.0f, 0.f, 0.f);

		glBegin(GL_TRIANGLES);
		for (int j = 0; j < 3; j++) {
			
			Vec3f v = m_pModel->vert(face[j]);
			Vec3f n = m_pModel->norm(face[j]);
			glNormal3f(n.x, n.y, n.z); glVertex3f(v.x, v.y, v.z);
			
			//int x0 = (v0.x+1.)*width/2.;
//            int y0 = (v0.y+1.)*height/2.;
//            int x1 = (v1.x+1.)*width/2.;
//            int y1 = (v1.y+1.)*height/2.;
//            line(x0, y0, x1, y1, image, white);
		}
		glEnd();
	}
	
}

void DrawPlane(float w, int step, float y)
{

	glBegin(GL_LINES);
	for (int i = 0; i <=step; i++)
	{
		glVertex3f(-w/2 + i*w/step, 0, -w/2);
		glVertex3f(-w/2 + i*w/step, 0, w/2);
		glVertex3f(-w/2, 0,  -w/2 + i*w/step);
		glVertex3f(w/2, 0,  -w/2 + i*w/step);
	}

	glEnd();
}

void DrawLine(float r, float g, float b)
{
		glBegin(GL_LINES);
			glColor3f(r,g,b);
			glVertex3f(0, -0.5, 0);
			glVertex3f(0, 0.5, 0);
		glEnd();
}

void DrawAxis()
{
	glPushMatrix();		
		glPushMatrix();
			glScalef(0,40,0);
			DrawLine(1,0,0);
		glPopMatrix();
		glPushMatrix();
			glRotatef(90, 0,0,1);
			glScalef(0,40,0);
			DrawLine(0,1,0);
		glPopMatrix();
		glPushMatrix();
			glRotatef(90, 1,0,0);
			glScalef(0,40,0);
			DrawLine(0,0,1);
		glPopMatrix();
	glPopMatrix();
}

void CRenderer::Update()
{
	GLUquadricObj *quadObj;
	static float theta = 0.0f;
	static float x_angle = 0.0f;
	static float y_angle = 0.0f;
	static float mouse_scale_x = 0.2,mouse_scale_y = 0.2;
	float center = -30;

	IInput *pInput = m_pSystem->GetIInput();
	
	if (pInput->GetIMouse()->MouseDown(1)){
		x_angle += (float)pInput->GetIMouse()->GetDeltaX();
		y_angle += (float)pInput->GetIMouse()->GetDeltaY();
	}

	//quadObj = gluNewQuadric(); // создаем новый объект 
							   // для создания сфер и цилиндров


	glClearColor(ClearColor.r, ClearColor.g, ClearColor.b, 0.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	
	// Устанавливаем камеру
	//gluLookAt(
	//	m_Camera->x_eye, m_Camera->y_eye, m_Camera->z_eye,
	//	m_Camera->cx, m_Camera->cy, m_Camera->cz,
	//	m_Camera->x_up, m_Camera->y_up, m_Camera->z_up

	//);
	gluLookAt(-5, 15, -10, 0, 0, center, 0, 1, 0);
	
	glPushMatrix();
	////////////////////////////////////////////////////////////
	glColor3f(1,1,1);
	//glTranslated(-2, 0, 0); // сдвигаемся влево
	glRotated(45, 1, 0, 0); // поворачиваем
	glColor3d(0, 1, 0);
	//gluQuadricDrawStyle(quadObj, GLU_FILL); // устанавливаем
							 // стиль: проволочный
	gluCylinder(quadObj, 0.5, 0.75, 1, 15, 15);
	glPopMatrix();
	
	/////////////////////////////////////////////////////////////

	glPushMatrix();
	//Установить центр вращения
	glTranslatef(0, 0, center);
	glRotatef(-x_angle*mouse_scale_x, 0,1,0);
	glRotatef(-y_angle*mouse_scale_y, 1,0,0);
	DrawAxis();
	
	glColor3f(1, 1, 0.34);

	glPushMatrix();
		glColor3f(1,0,0);
		glRotatef(90, 1,0,0);
		glTranslatef(0,center/4, 0);
		DrawPlane(20, 40, 0);

	glPopMatrix();
	glColor3f(0.8, 0.8, 0.8);
	DrawPlane(20, 40, 0);

	//Повернуть вокруг центра на угол theta
	glRotatef(theta, 0, 1, 0);
	glRotatef(theta / 2, 1, 0, 0);
	//glTranslatef(0, 4, 0);
	
	glTranslatef(0, 0, -4.0f);
	glRotatef(theta / 2, 0, 0, 1);
	
	//glRotatef(45, 1, 0, 0);
	
	//glTranslatef(0.1, 0.1, 0);

	//glPushMatrix();

	glColor3f(0.7,0.1,0.9);
	//gluQuadricDrawStyle(quadObj, GLU_FILL); // устанавливаем
							// стиль: сплошной
	glScalef(3, 3, 3);

	//gluSphere(quadObj, 1.0, 30, 30); // рисуем сферу
									 // радиусом 0.5
	RenderModel();
	glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(0, 0, -2.0f);
		RenderModel();
		glPopMatrix();

		glColor3f(1.0, 0.0, 1.0);
		glPushMatrix();
		glTranslatef(0, 0, 2.0f);
		RenderModel();
		glPopMatrix();

		glColor3f(1.0, 1.0, 0.0);
		glPushMatrix();
		glTranslatef(2.0, 0, 0.0f);
		RenderModel();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-2.0, 0.0, 0.0f);
		RenderModel();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, -2.0, 0.0f);
		RenderModel();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0, 2.0, 0.0f);
		RenderModel();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(2.0, -2.0, 0.0f);
		RenderModel();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(2.0, 2.0, 0.0f);
		RenderModel();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(2.0, -2.0, 2.0f);
		RenderModel();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(2.0, 2.0, 2.0f);
		RenderModel();
		glPopMatrix();
	glBegin(GL_LINES);
		glColor3d(1, 0, 0);
		glVertex3f(0, -3, 0);
		glVertex3f(0, 3, 0);
		glColor3f(0,1,0);
		glVertex3f(-3, 0, 0);
		glVertex3f(3, 0, 0);
		glColor3f(0,0,1);
		glVertex3f(0, 0, -3);
		glVertex3f(0, 0, 3);
	glEnd();

	glPopMatrix();

	//glPopMatrix();
	theta += 1.f;
}


void CRenderer::Init(ISystem *pSystem)
{
	DWORD w = 700, h = 700;

	m_pSystem = pSystem;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LINE_SMOOTH);
	glCullFace(GL_BACK);  
	glFrontFace(GL_CCW); 

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 20.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat whight_light[] = { 1.0, 1.0, 1.0, 1.5 };
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whight_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whight_light);

	//glEnable(GL_FOG);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//openglWindow->GetWindowSize(&w, &h);
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45, (GLfloat)w / (GLfloat)h, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

WIN_HWND CRenderer::Init(
	int x, int y, int width, int height,
	unsigned int cbpp, int zbpp, int sbits,
	bool fullscreen,
	WIN_HINSTANCE hinst, WIN_HWND Glhwnd, WIN_HDC Glhdc, WIN_HGLRC hGLrc,
	bool bReInit)
{
	return WIN_HWND();
}

bool CRenderer::SetCurrentContext(WIN_HWND hWnd)
{
	return false;
}

bool CRenderer::CreateContext(WIN_HWND hWnd, bool bAllowFSAA)
{
	return false;
}

bool CRenderer::DeleteContext(WIN_HWND hWnd)
{
	return false;
}

void CRenderer::SetCamera(CCamera * pCamera)
{
	m_Camera = pCamera;
}

CALL_API IRenderer* CreateRenderer()
{
	IRenderer *m_pIRenderer = new CRenderer();
	return m_pIRenderer;
}