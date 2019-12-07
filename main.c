#include<stdio.h>
#include<GL/glut.h>

static void on_reshape(int width, int height);
static void on_display(void);
static void drawTrack();

int main(int argc,char** argv){
    
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow(argv[0]);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glClearColor(1,1,1,0);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    
    
    return 0;
}

static void on_display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2,3,-5,
                2,0,2,
                0,10,0);

    glBegin(GL_LINES);
        glColor3f(1,1,0);
        glVertex3f(0,0,0);
        glVertex3f(10,0,0);
        glVertex3f(0,0,0);
        glVertex3f(-10,0,0);
        
        glColor3f(1,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,10,0);
        glVertex3f(0,0,0);
        glVertex3f(0,-10,0);

        glColor3f(1,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,0,10);
        glVertex3f(0,0,0);
        glVertex3f(0,0,-10);
    glEnd();
    
    drawTrack();
    
    glutSwapBuffers();
}

static void on_reshape(int width, int height)
{
    /* Postavlja se viewport. */
    glViewport(0, 0, width, height);

    /* Postavljaju se parametri projekcije. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 1500);
}

void drawTrack()
{
    /*Iscrtava se staza*/
    glPushMatrix();
        glColor3f(0.3, 0.3, 0.3);
        glTranslatef(2.5,0.125,5);
        glScalef(5,0.25,10);
        glutSolidCube(1);
    glPopMatrix();
    
    /*Iscrtavaju se linije koje dele stazu na 5 delova*/
    
    glPushMatrix();
        glColor3f(1,1,0);
        glTranslatef(1,0.2,5);
        glScalef(0.1,0.25,10);
        glutSolidCube(1);
    glPopMatrix();
      
    glPushMatrix();
        glColor3f(1,1,0);
        glTranslatef(3,0.2,5);
        glScalef(0.1,0.25,10);
        glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(1,1,0);
        glTranslatef(2,0.2,5);
        glScalef(0.1,0.25,10);
        glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(1,1,0);
        glTranslatef(4,0.2,5);
        glScalef(0.1,0.25,10);
        glutSolidCube(1);
    glPopMatrix();
}