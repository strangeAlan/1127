#include<GL/glut.h>
#include<cmath>
#include<stdio.h>
int choice = 0;
int currentIter = 0;
const int maxTotalIter = 1000;
const int refreshInterval = 200; // 每隔100毫秒刷新一次
GLint Iter;
GLsizei winWidth = 500, winHeight = 500;
GLfloat xComplexMin = -2.00, xComplexMax = 0.50;
GLfloat yComplexMin = -1.25, yComplexMax = 1.25;

GLfloat complexWidth = xComplexMax - xComplexMin;
GLfloat complexHeight = yComplexMax - yComplexMin;
GLint newX = 0, newY = 0;
class complexNum {
public:
	GLfloat x, y;
};

struct color { GLfloat r, g, b; };

void zoom();
void mouseButton(int button, int state, int x, int y);
void unProject(GLdouble winx, GLdouble winy, GLdouble winz,
	GLdouble* objx, GLdouble* objy, GLdouble* objz);

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}
void plotPoint(complexNum z)
{
	glBegin(GL_POINTS);
	glVertex2f(z.x, z.y);
	glEnd();
}
complexNum complexSquare(complexNum z)
{
	complexNum zSquare;
	zSquare.x = z.x * z.x - z.y * z.y;
	zSquare.y = 2 * z.x * z.y;
	return zSquare;
}
GLint mandelSqTransf(complexNum z0, GLint maxIter)
{
	complexNum z = z0;
	GLint count = 0;

	while ((z.x * z.x + z.y * z.y < 4.0) && (count < maxIter))
	{
		z = complexSquare(z);
		z.x += z0.x;
		z.y += z0.y;
		count++;
	}
	return count;
}
void timerFcn(int value) {
	if (currentIter < Iter) {
		currentIter += 1; // 每次增加一个迭代次数

		glutPostRedisplay(); // 标记窗口需要重新绘制
		glutTimerFunc(refreshInterval, timerFcn, 0); // 设置下一次定时器回调
	}
}
void mandelbrot(GLint nx, GLint ny, GLint maxIter)
{
	complexNum z, zIncr;
	color ptColor;
	GLint iterCount;

	zIncr.x = complexWidth / GLfloat(nx);
	zIncr.y = complexHeight / GLfloat(ny);

	for(z.x=xComplexMin;z.x<xComplexMax;z.x+=zIncr.x)
		for (z.y = yComplexMin; z.y < yComplexMax; z.y += zIncr.y)
		{
			iterCount = mandelSqTransf(z, maxIter);
			if (iterCount >= maxIter)
			{
				ptColor.r = ptColor.g = ptColor.b = 0.0;
			}
			/*else if (iterCount >(maxIter / 8))
			{
				ptColor.r = 1.0;
				ptColor.g = 0.5;
				ptColor.b = 0.0;
			}
			else if(iterCount > (maxIter / 10))
			{
				ptColor.r = 1.0;
				ptColor.g = ptColor.b = 0.0;
			}
			else if (iterCount > (maxIter / 20))
			{
				ptColor.b = 0.5;
				ptColor.g = ptColor.r = 0.0;
			}
			else if (iterCount > (maxIter / 40))
			{
				ptColor.g = ptColor.r = 1.0;
				ptColor.b = 0.0;
			}
			else if (iterCount > (maxIter / 100))
			{
				ptColor.r = ptColor.b = 0.0;
				ptColor.g = 0.3;
			}
			else
			{
				ptColor.r = 0.0;
				ptColor.g = ptColor.b = 1.0;
			}*/
			else
			{
				GLfloat value = (GLfloat)iterCount / maxIter;
				
				ptColor.r = (GLfloat)(sin(value * 2 + 0.1) / 2 + 0.5);
				ptColor.g = (GLfloat)(sin(value * 3 + 0.3) / 2 + 0.5);
				ptColor.b = (GLfloat)(sin(value * 5 + 0.5) / 2 + 0.5);
			}
			glColor3f(ptColor.r, ptColor.g, ptColor.b);
			plotPoint(z);
		}
}
void displayFcn(void)
{
	GLint nx = winWidth , ny = winHeight, maxIter = Iter;
	glClear(GL_COLOR_BUFFER_BIT);
	switch (choice)
	{
	case 1:///多个视口
	{	
	int numColumns = 3;
	int numRows = 3;
	int viewportWidth = winWidth / numColumns;
	int viewportHeight = winHeight / numRows;
	int cnt = 0;
	for (int row = 0; row < numRows; ++row) {
		for (int column = 0; column < numColumns; ++column) {
			glViewport(column * viewportWidth, (numRows - row - 1) * viewportHeight, viewportWidth, viewportHeight);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			// 设置适当的投影矩阵和视口参数
			gluOrtho2D(xComplexMin, xComplexMax, yComplexMin, yComplexMax);
			glMatrixMode(GL_MODELVIEW);
			cnt++;
			mandelbrot(nx, ny, Iter/9*cnt);
			// 绘制当前位置的图形
		}
	}
	break;
	}

	case 2://动态显示
	{
		glViewport(0, 0, winWidth, winHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(xComplexMin, xComplexMax, yComplexMin, yComplexMax);
		glMatrixMode(GL_MODELVIEW);
		mandelbrot(nx , ny , currentIter);
		break;
	}
	case 3://直接显示
	{
		glViewport(0, 0, winWidth, winHeight);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(xComplexMin, xComplexMax, yComplexMin, yComplexMax);
		glMatrixMode(GL_MODELVIEW);
		mandelbrot(nx , ny , maxIter);
		break;
	}
	default:
		break;
	}
	glFlush();


	//printf("Zoom:%.2f\n", (2.5 / complexHeight));
}
void winReshapeFcn(GLint newWidth, GLint newHeight)
{	
	//winWidth = newWidth;
	//winHeight = newHeight;
	glViewport(0,0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//gluOrtho2D(xComplexMin, xComplexMax, yComplexMin, yComplexMax);
	if (newWidth <= newHeight)
	{
		gluOrtho2D(xComplexMin, xComplexMax, yComplexMin * (GLfloat)newHeight / newWidth, yComplexMax * (GLfloat)newHeight / newWidth);
	}
	else
	{
		gluOrtho2D(xComplexMin * (GLfloat)newWidth / newHeight, xComplexMax * (GLfloat)newWidth / newHeight, yComplexMin, yComplexMax);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glutPostRedisplay();
}
void mouseButton(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		break;
	case GLUT_RIGHT_BUTTON:
		// 重置
		xComplexMin = -2.00; xComplexMax = 0.50;
		yComplexMin = -1.25; yComplexMax = 1.25;
		complexWidth = xComplexMax - xComplexMin;
		complexHeight = yComplexMax - yComplexMin;
		glutPostRedisplay();
		return;
	default:
		return;
	}
	switch (state) {
	case GLUT_DOWN:
		newX = x;
		newY = y;
		glutIdleFunc(zoom);
		break;
	case GLUT_UP:
		newX = 0;
		newY = 0;
		glutIdleFunc(NULL);
		break;
	}
}
void mouseMotion(int x, int y)
{
	newX = x;
	newY = y;
}
void unProject(GLdouble winx, GLdouble winy, GLdouble winz,
	GLdouble* objx, GLdouble* objy, GLdouble* objz) 
{
	// 从窗口到世界坐标系
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	gluUnProject(winx, winy, winz, modelview, projection, viewport, objx, objy, objz);
}
void zoom() 
{
	// 向下缩放
	// 从窗口到世界坐标系
	GLdouble winx = (GLdouble)newX;
	GLdouble winy = (GLdouble)winHeight - (GLdouble)newY;
	GLdouble winz = 0;
	GLdouble objx = 0;
	GLdouble objy = 0;
	GLdouble objz = 0;
	unProject(winx, winy, winz, &objx, &objy, &objz);
	xComplexMin += (objx - xComplexMin) / 5;
	xComplexMax += (objx - xComplexMax) / 5;
	yComplexMin += (objy - yComplexMin) / 5;
	yComplexMax += (objy - yComplexMax) / 5;
	complexWidth = xComplexMax - xComplexMin;
	complexHeight = yComplexMax - yComplexMin;
	glutPostRedisplay();
}
void choose()
{
	printf("请输入Mandelbort Set迭代的最大迭代次数");
	scanf_s("%d", &Iter);
	printf("你有以下选择：\n");
	printf("1.展示多个视口多次迭代的结果\n");
	printf("2.展示动态分形过程\n");
	printf("3.直接显示最终结果\n");
	printf("请输入你的选择：");
	char c;
	scanf_s("%c");
	scanf_s("%d", &choice);
}
void main(int argc, char** argv)
{
	
	choose();
	glutInit(&argc, argv); // Initialize GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB ); // Set display mode.
	glutInitWindowPosition(50, 50); // Set top-left displaywindow position.
	glutInitWindowSize(winWidth, winHeight); // Set displaywindow width and height.

	glutCreateWindow("Mandelbort Set"); // Create display window
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	init(); // Execute initialization procedure
	
	glutDisplayFunc(displayFcn); // Send graphics to display window.
	glutTimerFunc(refreshInterval, timerFcn, 0);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop(); // Display everything and wait.
}