#include<stdio.h>
#include<GL/glut.h>

#define TIMER_ID 1
#define TIMER_INTERVAL 20

static void on_reshape(int width, int height);
static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int id);
static void drawTrack();
static void drawBall();

int animation_ongoing;
float animation_parameter;
float move = 2.04;
int acceleration = 1;

int main(int argc,char** argv){
    
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow(argv[0]);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    
    
    return 0;
}

static void on_display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2,3,animation_parameter-5,
                2,0,animation_parameter+1,
                0,1,0);

    
    drawTrack();
    drawBall();
    
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

static void on_keyboard(unsigned char key, int x, int y){
    switch(key){
        case 27:
            exit(0);
            break;
        case 'a':
        case 'A':
            if(move<3.04){
                move +=1;
                glutPostRedisplay();
                break;
            }else break;
        case 'd':
        case 'D':
            if(move>0.04){
                move -=1;
                glutPostRedisplay();
                break;
            }else break;
            
        case 'g':
        case 'G':
            if (!animation_ongoing) {
                animation_ongoing = 1;
                glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
            }
        break;
    }
}

static void on_timer(int id){
    if (TIMER_ID != id)
        return;
    /*Podesava se parametar kretanja i ubrzanja loptice*/
    animation_parameter += 0.0022*acceleration;
    acceleration+=1;
    glutPostRedisplay();

    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
}

void drawTrack()
{
    /*Iscrtava se staza*/
    glPushMatrix();
        glColor3f(0.3, 0.3, 0.3);
        glTranslatef(2.06,0.125,5);
        glScalef(5,0.25,100000);
        glutSolidCube(1);
    glPopMatrix();
    
    /*Iscrtavaju se linije koje dele stazu na 5 delova*/
    
    glPushMatrix();
        glColor3f(1,1,0);
        glTranslatef(0.54,0.2,5);
        glScalef(0.1,0.25,100000);
        glutSolidCube(1);
    glPopMatrix();
      
    glPushMatrix();
        glColor3f(1,1,0);
        glTranslatef(2.54,0.2,5);
        glScalef(0.1,0.25,100000);
        glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(1,1,0);
        glTranslatef(1.54,0.2,5);
        glScalef(0.1,0.25,100000);
        glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(1,1,0);
        glTranslatef(3.54,0.2,5);
        glScalef(0.1,0.25,100000);
        glutSolidCube(1);
    glPopMatrix();
}

void drawBall(){
    glPushMatrix();
        glColor3f(0,0,1);
        glTranslatef(move,0.5,animation_parameter);
        glutSolidSphere(0.25,100,100);
    glPopMatrix();
}