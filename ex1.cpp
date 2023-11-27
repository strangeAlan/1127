#include<GL/glut.h>
GLfloat vertices[8][3] = {
	{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},{1.0,1.0,-1.0},{-1.0,1.0,-1.0},
	{-1.0,-1.0,1.0},{1.0,-1.0,1.0},{1.0,1.0,1.0},{-1.0,1.0,1.0}
};
GLfloat colors[8][3] = {
	{0.0,0.0,0.0},{1.0,0.0,0.0},{1.0,1.0,0.0},{0.0,1.0,0.0},
	{0.0,0.0,1.0},{1.0,0.0,1.0},{1.0,1.0,1.0},{0.0,1.0,1.0}
};
GLfloat trangle[4][3] = {
	{2.0,2.0,2.0},{3.0,2.0,2.0},{2.5,2.7,2.0},{2.5,2.3,3.0}
};
GLfloat colors2[4][3] = {
	{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,1.0,0.0}
};
void polygon(int a, int b, int c, int d)
{
	glColor3f(1.0, 1.0, 1.0);
	//glBegin(GL_LINE_LOOP);
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
void polygon2(int a, int b,  int c,int color)
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glColor3fv(colors2[color]);
	glVertex3fv(trangle[a]);
	//glColor3fv(colors2[b]);
	glVertex3fv(trangle[b]);
	//glColor3fv(colors2[c]);
	glVertex3fv(trangle[c]);
	glEnd();
}
void polygon3(int a, int b, int c, int d)
{
	glColor3f(1.0, 1.0, 1.0);
	//glBegin(GL_LINE_LOOP);
	glBegin(GL_POLYGON);
	glColor3fv(colors[d]);
	glVertex3f(vertices[a][0]+3 , vertices[a][1] + 3, vertices[a][2]);
	glColor3fv(colors[a]);
	glVertex3f(vertices[b][0] + 3, vertices[b][1] + 3, vertices[b][2]);
	glColor3fv(colors[c]);
	glVertex3f(vertices[c][0] + 3, vertices[c][1] + 3, vertices[c][2]);
	glColor3fv(colors[b]);
	glVertex3f(vertices[d][0] + 3, vertices[d][1] + 3, vertices[d][2]);
	glEnd();
}
void drawcube(void)
{
	polygon(1, 0, 3, 2);
	polygon(3, 7, 6, 2);
	polygon(7, 3, 0, 4);
	polygon(2, 6, 5, 1);
	polygon(4, 5, 6, 7);
	polygon(5, 4, 0, 1);

}
void drawanothercube(void) {
	polygon3(1, 0, 3, 2);
	polygon3(3, 7, 6, 2);
	polygon3(7, 3, 0, 4);
	polygon3(2, 6, 5, 1);
	polygon3(4, 5, 6, 7);
	polygon3(5, 4, 0, 1);
}
void drawtrangle(void) {
	polygon2(0, 1, 2,0);
	polygon2(0, 2, 3,1);
	polygon2(0, 1, 3,2);
	polygon2(1, 2, 3,3);
}
/*float mynear = 3.0;
float myfar = 7.0;
float viewform_z = -5.0;*/
void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	//glTranslatef(0.0, 0.0, viewform_z);
	gluLookAt(1, -3, -1, 2, 2, 2, 0, 1, 0);
	drawcube();
	drawtrangle();
	drawanothercube();
	glutSwapBuffers();
	glutPostRedisplay();
}
void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);//x,y起始位置，width，height，宽度和高度
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		glOrtho(-5.0, 5.0, -5.0 * (GLfloat)h / w, 5.0 * (GLfloat)h / w,-10.0,10.0);
	}
	else
	{
		glOrtho(-5.0 * (GLfloat)w / h, 5.0 * (GLfloat)w / h, -5.0, 5.0,-10.0,10.0);
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
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); // 设置背景颜色
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-5.0, 5.0, -5.0, 5.0, -10.0, 10.0);
	// Set projection parameters.投影模式
	//gluOrtho2D(-200.0, 200.0, -200.0, 200.0);//给画圆算法，有四个完整象限
	//gluOrtho2D(0.0, 200.0, 0.0, 150.0);//常见渲染范围
}
void lineSegment(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

	glColor3f(1.0, 0.4, 0.2); // Set line segment color to green.
	glBegin(GL_LINES);
	glVertex2i(180, 15); // Specify line-segment geometry.
	glVertex2i(10, 145);
	glVertex2i(160, 25);
	glVertex2i(10, 125);
	glVertex2i(10, 10);
	glVertex2i(100, 100);
	glEnd();
	/*glBegin(GL_POINT);
	glVertex2i(50, 100);
	glVertex2i(75, 150);
	glVertex2i(100, 200);
	glEnd();*/

	glFlush(); // Process all OpenGL routines as quickly as possible.
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv); // Initialize GLUT.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB|GLUT_DEPTH); // Set display mode.
	glutInitWindowPosition(50, 100); // Set top-left displaywindow position.
	glutInitWindowSize(1000, 1000); // Set displaywindow width and height.
	
	glutCreateWindow("Experiment 1"); // Create display window

	init(); // Execute initialization procedure
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display); // Send graphics to display window.
	glutMainLoop(); // Display everything and wait.
}