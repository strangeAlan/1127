/*��꽻����ͼ�ν���*/
#include<GL/glut.h>
#include<cmath>
#include<stdio.h>
enum TransMode {
	Translate,
	Rotate,
	Scale
};
TransMode transModeSelected = Translate;
float angle = 0.0, axis[3];
GLfloat vertices[8][3] = {
	{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},{1.0,1.0,-1.0},{-1.0,1.0,-1.0},
	{-1.0,-1.0,1.0},{1.0,-1.0,1.0},{1.0,1.0,1.0},{-1.0,1.0,1.0}
};
GLfloat colors[8][3] = {
	{0.0,0.0,0.0},{1.0,0.0,0.0},{1.0,1.0,0.0},{0.0,1.0,0.0},
	{0.0,0.0,1.0},{1.0,0.0,1.0},{1.0,1.0,1.0},{0.0,1.0,1.0}
};
GLfloat objectXform[4][4] = {
{1.0, 0.0, 0.0, 0.0},
{0.0, 1.0, 0.0, 0.0},
{0.0, 0.0, 1.0, 0.0},
{0.0, 0.0, 0.0, 1.0}
};
bool drawLines = false;
float time = 0.0;
float deltaTime = 0.01;
int judge = 0;
int lastX, lastY;
int winWidth = 1000, winHeight = 1000;
GLfloat scale_factor =1.0f;
struct menuEntryStruct {
	const char* label;
	char key;
};
static menuEntryStruct mainMenu[] = {
	 "Reset", '0',
	 "Rotate", 'r',
	 "Translate", 't',
	 "Scale", 's',
	 "lines/polygons", '1',
	 "quit", 27, //ESC ����ASCII: 27��
	 };


int mainMenuEntries = sizeof(mainMenu) / sizeof(menuEntryStruct);
void userEventAction(int key);
void mouseButton(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void startMotion(int x, int y)
{
	lastX = x;
	lastY = y;
}
void stopMotion(int x, int y)
{
	angle = 0.0f;
	memset(axis, 0, sizeof(axis));
	printf("objectXform:\n");
	for (int i = 0; i < 4; i++)
	{
	printf("\t");
	for (int j = 0; j < 4; j++)
	{
	printf("%.2f\t", objectXform[i][j]);
	}
	printf("\n");
	}

}
void mouseButton(int button, int state, int x, int y) {
	/*switch (button) {
	case GLUT_LEFT_BUTTON :
		// �����������¼�
		break;
	default:
		return;
	}*/
	switch (button)
	{
		/*if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		if (transModeSelected == Scale) {
			/*if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
				// ����м����£��Ŵ�������
				scale_factor += 0.1f;
			}*/
	case GLUT_MIDDLE_BUTTON:
			if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP&&transModeSelected==Scale) {
				// ����м��ͷţ���С������
				//if (scale_factor > 1)scale_factor = 0.9f;
				//else scale_factor -= 0.1f;
				// ȷ���������Ӳ�С��0
				//if (scale_factor < 0.1f)
				//	scale_factor = 0.1f;
				scale_factor = 0.9f;
			}
			break;
			/*else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				// ���������£���С������
				scale_factor -= 0.1f;
			}*/
	case GLUT_LEFT_BUTTON:
			if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && transModeSelected == Scale) {
				// �������ͷţ��Ŵ�������
				//if (scale_factor < 1)scale_factor = 1.1f;
				//else scale_factor += 0.1f;
				// ȷ���������Ӳ�С��0
				scale_factor = 1.1f;
			}
			break;
	default:
		break;
		}
	
	switch (state) {
	case GLUT_DOWN:
		startMotion(x, y); // ��ʼ��꽻��
		break;
	case GLUT_UP:
		stopMotion(x, y); // ֹͣ��꽻��
		break;
	}
	glutPostRedisplay();
}
void mouseMotion(int x, int y) {
	float dx = x - lastX;
	float dy = y - lastY;
	if (!dx && !dy) return;

	if (transModeSelected == Translate) {
		axis[0] = dx * (10.0f / winWidth);
		axis[1] = -dy * (10.0f / winHeight);
		axis[2] = 0;
	}
	else if (transModeSelected == Rotate) {
		angle = 3.0;
		axis[0] = dy * (360.0f / winHeight);
		axis[1] = dx * (360.0f / winWidth);
		axis[2] = 0;
	}
	else if (transModeSelected == Scale) {
		axis[0] = dx * (4.0f / winWidth);
		axis[1] = -dy * (4.0f / winHeight);
		axis[2] = 0;
		
	}

	lastX = x;
	lastY = y;
	glutPostRedisplay();
}
void userEventAction(int key) {
	switch (key) {
	case '0':
		angle = 0.0f;
		memset(axis, 0, sizeof(axis));
		memset(objectXform, 0, sizeof(objectXform)); // ���ñ任����
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (i == j) {
					objectXform[i][j] = 1.0f;
				}
			}
		}
		break;
	case 'r': // ��ת
		transModeSelected = Rotate;
		break;
	case 't': // ƽ��
		transModeSelected = Translate;
		break;
	case 's': // ����
		transModeSelected = Scale;
		break;
	case '1': // �߿�ͼ/�����
		drawLines = !drawLines;
		break;
	case '+':
		if (transModeSelected == Scale)
		{
			//if (scale_factor < 1)scale_factor = 1.1f;
			//else scale_factor += 0.1f;

			scale_factor = 1.1f;
		}
		break;
		// ���� "-" ������С������
	case '-':
		if (transModeSelected == Scale) 
		{
			//if (scale_factor > 1)scale_factor = 0.9f;
			//else scale_factor -= 0.1f;
			// ȷ���������Ӳ�С��0
			//if (scale_factor < 0.1f)
			//	scale_factor = 0.1f;
			scale_factor = 0.9f;
		}
		break;
	case 27: // ESC ����ASCII: 27���˳�
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay(); // �ػ�
}
void selectMain(int choice) // ���->key ӳ��
{
	userEventAction(mainMenu[choice].key); // ����ͨ�ö������ͺ���
}
void keyboard(unsigned char key, int x, int y)
{
	userEventAction(key);
}
void polygon(int a, int b, int c, int d,int face)
{
	glColor3f(1.0, 1.0, 1.0);
	//glBegin(GL_LINE_LOOP);
	if (drawLines)
	{
		glBegin(GL_LINE_LOOP);
		glColor3fv(colors[a]);
		glVertex3fv(vertices[a]);
		glColor3fv(colors[b]);
		glVertex3fv(vertices[b]);
		glColor3fv(colors[c]);
		glVertex3fv(vertices[c]);
		glColor3fv(colors[d]);
		glVertex3fv(vertices[d]);
		glEnd();
	}
	else {
		glBegin(GL_POLYGON);
		glColor3fv(colors[a]);
		glVertex3fv(vertices[a]);
		glColor3fv(colors[b]);
		glVertex3fv(vertices[b]);
		glColor3fv(colors[c]);
		glVertex3fv(vertices[c]);
		glColor3fv(colors[d]);
		glVertex3fv(vertices[d]);
		glEnd();
	}
}
void colorcube(void)
{
	polygon(1, 0, 3, 2,0);
	polygon(3, 7, 6, 2,1);
	polygon(7, 3, 0, 4,2);
	polygon(2, 6, 5, 1,3);
	polygon(4, 5, 6, 7,4);
	polygon(5, 4, 0, 1,5);

}
void init(void)
{
	glLineWidth(3.0);
	glEnable(GL_DEPTH_TEST);

	glutCreateMenu(selectMain); // ʹ�� selectMain ��Ϊ�˵����ú���
	for (int i = 0; i < mainMenuEntries; i++) {
		glutAddMenuEntry(mainMenu[i].label, i);
	}
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* view transform */
	glLoadIdentity();
	//glTranslatef(0.0, 0.0, viewxform_z);
	gluLookAt(0.0, 0.0, 1.0,  // ���λ��
		0.0, 0.0, 0.0,  // �۲�Ŀ��λ�ã�������������ĵ�
		0.0, 1.0, 0.0); // ������Ϸ�������
	///////////////////////////////////////////////////////////////////////
	// ƽ��
	if (transModeSelected == Translate)
	{
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(axis[0], axis[1], axis[2]);
		glMultMatrixf((GLfloat*)objectXform);
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)objectXform);
		glPopMatrix();
	}
	else if(transModeSelected == Rotate)
	{
		glPushMatrix();
		glLoadIdentity();
		glRotatef(axis[0], 1.0, 0.0, 0.0); // ��X����ת
		glRotatef(axis[1], 0.0, 1.0, 0.0); // ��Y����ת
		glRotatef(axis[2], 0.0, 0.0, 1.0); // ��Z����ת
		glMultMatrixf((GLfloat*)objectXform);
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)objectXform);
		glPopMatrix();
	}
	else if (transModeSelected == Scale)
	{
		glPushMatrix();
		glLoadIdentity();
		glScalef(scale_factor, scale_factor, scale_factor);
		glMultMatrixf((GLfloat*)objectXform);
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)objectXform);
		glPopMatrix();
	}
	glPushMatrix();
	glMultMatrixf((GLfloat*)objectXform);
	colorcube();
	glPopMatrix();

	//glLoadIdentity();

	glFlush();
	glutSwapBuffers();

	//glutPostRedisplay();
}
void myReshape(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);//x,y��ʼλ�ã�width��height����Ⱥ͸߶�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		glOrtho(-5.0, 5.0, -5.0 * (GLfloat)h / w, 5.0 * (GLfloat)h / w, -10.0, 10.0);
	}
	else
	{
		glOrtho(-5.0 * (GLfloat)w / h, 5.0 * (GLfloat)w / h, -5.0, 5.0, -10.0, 10.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0, 5.0, -5.0, 5.0,-10.0,10.0);
	//glFrustum(-2.5, 2.5, -2.5, 2.5, mynear, myfar);
	glMatrixMode(GL_MODELVIEW);*/
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv); // Initialize GLUT.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Set display mode.
	glutInitWindowPosition(50, 100); // Set top-left displaywindow position.
	glutInitWindowSize(1000, 1000); // Set displaywindow width and height.

	
	glutCreateWindow("An Example OpenGL Program"); // Create display window
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);//ע����ꡢ����glutMouseFunc(mouseButton);
	//glutMotionFunc(mouseMotion);
	
	init(); // Execute initialization procedure
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display); // Send graphics to display window.
	glutMainLoop(); // Display everything and wait.
}