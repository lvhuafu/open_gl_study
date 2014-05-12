#include <math.h>
#include <GL/glut.h>
#include <Gl/GL.h>
#include <gl/GLU.h>
#include <stdio.h>
#define windowsWidth  500
#define windowsHeight 500
#define M_PI 3.1415926

int style = GL_QUAD_STRIP;
float x, y, z, phi,theta;

int preX, preY; //��¼�����һ��λ��        
bool leftState = false;
bool rightState = false;
bool downState = false;
bool flag = false;
bool flag1 = false;
bool flag2 = false;
float angleX = 0.0;//��x�����ϵ�λ�ƣ��Ƕȣ�
float angleY = 0.0;
float angleAdd = 20.0;
int number = 1;


void init(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//����ɫ��ɫ
	glShadeModel(GL_FLAT);//��ɫģʽ-�㶨��ɫ
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);//�Ӵ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0, 1.0, 0.1, 100.0);//��Ұ�ȣ������߱ȣ������棬Զ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		preX = x;
		preY = y;
		if (button == GLUT_LEFT_BUTTON)
			leftState = true;
		else if (button == GLUT_RIGHT_BUTTON)
			rightState = true;
		else if (button==GLUT_MIDDLE_BUTTON)
			downState = true;
	}
	else if (state == GLUT_UP)
	{
		if (button == GLUT_LEFT_BUTTON)
			leftState = false;
		else if (button == GLUT_RIGHT_BUTTON)
			rightState = false;
		else if (button == GLUT_MIDDLE_BUTTON)
			downState = false;
	}

}

void motion(int x, int y)
{
	if (leftState)
	{
		float xDis = x - preX;
		float yDis = y - preY;
		angleX += xDis;
		angleY += yDis;
		preX = x;
		preY = y;
		glutPostRedisplay();//��ǵ�ǰ���������»���
	}
	if (downState)
	{
		angleAdd-=1;
		if (angleAdd <= 5)
		{
			angleAdd = 5;
		}
		glutPostRedisplay();//��ǵ�ǰ���������»���
	}
}

void drawSpheroidal()
{
	//glTranslated(0.0f, 0.0f, -1.0f);

	for (int i = 0; i < number; i++)
	{

		if (flag2)
		{
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT, GL_LINE);
			glPolygonMode(GL_BACK, GL_LINE);
		}
		double c = M_PI / 180.0; //�Ƕ�ת�����ȣ�M_PI=3.14159��
		for (phi = -80; phi < 80.0; phi += angleAdd)
		{
			glBegin(style);
			for (theta = -180.0; theta <= 180.0; theta += angleAdd)
			{
				x = sin(c*theta)*cos(c*phi) + i*1.5;
				y = cos(c*theta)*cos(c*phi)+i*1.5;
				z = sin(c*phi);
				glVertex3d(x, y, z);

				if (flag)
				{
					x = sin(c*(theta + angleAdd))*cos(c*phi) + i*1.5;
					y = cos(c*(theta + angleAdd))*cos(c*phi) + i*1.5;
					z = sin(c*phi);
					glVertex3d(x, y, z);
				}
				if (flag1)
				{
					x = sin(c*(theta + angleAdd))*cos(c*(phi + angleAdd)) + i*1.5;
					y = cos(c*(theta + angleAdd))*cos(c*(phi + angleAdd)) + i*1.5;
					z = sin(c*(phi + angleAdd));
					glVertex3d(x, y, z);
				}
				x = sin(c*theta)*cos(c*(phi + angleAdd)) + i*1.5;
				y = cos(c*theta)*cos(c*(phi + angleAdd)) + i*1.5;
				z = sin(c*(phi + angleAdd));
				glVertex3d(x, y, z);
			}
			glEnd();
		}

		x = y = i*1.5;
		z = 1;
		glBegin(GL_TRIANGLE_FAN);
		glVertex3d(x, y, z);
		c = M_PI / 180.0;
		z = sin(c*80.0);
		for (theta = -180.0; theta <= 180.0; theta += angleAdd)
		{
			x = sin(c*theta)*cos(c*80.0) + i*1.5;
			y = cos(c*theta)*cos(c*80.0) + i*1.5;
			glVertex3d(x, y, z);
		}
		glEnd();

		x = y = i*1.5;
		z = -1;
		glBegin(GL_TRIANGLE_FAN);
		glVertex3d(x, y, z);
		z = -sin(c*80.0);
		for (theta = -180.0; theta <= 180.0; theta += angleAdd)
		{
			x = sin(c*theta)*cos(c*80.0) + i*1.5;
			y = cos(c*theta)*cos(c*80.0) +i*1.5;
			glVertex3d(x, y, z);
		}
		glEnd();
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glRotatef(angleX, 0.0, 1.0, 0.0);
	glRotatef(angleY, 1.0, 0.0, 0.0);

	drawSpheroidal();
	glColor3f(1.0, 0.0, 0.0);//red color

	glutSwapBuffers();//���Ƹ���ͼ��ʱ���仭������ʾ������˸
}

void submenu(int id)
{
	switch (id)
	{
	case 1:
		style = GL_QUADS;
		flag = true;
		flag1 = true;
		break;
	case 2:
		style = GL_QUAD_STRIP;
		flag = false;
		flag1 = false;
		break;
	case 3:
		style = GL_TRIANGLES;
		flag = true;
		flag1 = false;
		break;
	case 4:
		style = GL_TRIANGLE_STRIP;
		flag = false;
		flag1 = false;
		break;
	case 5:
		angleAdd = 20.0;
		flag2 = false;
		number = 1;
		break;
	case 6:
		flag2 = true;
		break;
	case 7:
		number++;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(windowsWidth, windowsHeight);
	glutCreateWindow("��");
	glutCreateMenu(submenu);//����һ���µĵ���ʽ�˵�
	glutAddMenuEntry("�ı���", 1);
	glutAddMenuEntry("�ı��δ�", 2);
	glutAddMenuEntry("������", 3);
	glutAddMenuEntry("�����δ�", 4);
	glutAddMenuEntry("���", 6);
	glutAddMenuEntry("����", 7);
	glutAddMenuEntry("reset", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);//�ѵ�ǰ���ڵ�һ����갴���뵱ǰ�˵��ı�ʶ����ϵ����
	glutDisplayFunc(&display);
	glutReshapeFunc(&reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	init();
	glutMainLoop();
	return 0;
}