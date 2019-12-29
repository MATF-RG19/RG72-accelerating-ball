#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<time.h>
#include<string.h>
#define TIMER_ID 1
#define TIMER_INTERVAL 20

static void on_reshape(int width, int height);
static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int id);
static void drawTrack();
static void drawBall();
static void drawWall();
static int i;
int animation_ongoing;
float animation_parameter;
float move = 2.04;
int acceleration = 1;
int road = 200;
int randomNumber;

int main(int argc,char** argv){
    
     GLfloat light_position[] = { 1, 3, 10, 0};
    
    GLfloat light_ambient[] = { 0, 0, 0, 1 };

    GLfloat light_diffuse[] = { 0.3, 0.3, 0.3, 1};

    GLfloat light_specular[] = { 1, 1, 1, 1 };

    GLfloat model_ambient[] = { 0.4, 0.4, 0.4, 1 };

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow(argv[0]);
    srand(time(0));
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
    

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
    for(i=0;i<20;i++){
        randomNumber = rand()%5;
        drawWall(randomNumber,i);
    }
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
        case 's':
        case 'S':
            if(animation_ongoing){
                animation_ongoing = 0;
            }
            break;
        case 'r':
        case 'R':
            animation_parameter = 0;
            glutPostRedisplay();
            acceleration = 1;
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
    road+=150;
    glutPostRedisplay();

    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
}

static void drawTrack()
{
    /*Iscrtava se staza*/
    glPushMatrix();
        glColor3f(0.3, 0.3, 0.3);
        glTranslatef(2.06,0.125,5);
        glScalef(5,0.25,road);
        glutSolidCube(1);
    glPopMatrix();
    
    /*Iscrtavaju se linije koje dele stazu na 5 delova*/
    
    glPushMatrix();
        glColor3f(1,1,0);
        glTranslatef(0.54,0.2,5);
        glScalef(0.1,0.25,road);
        glutSolidCube(1);
    glPopMatrix();
      
    glPushMatrix();
        glColor3f(1,1,0);
        glTranslatef(2.54,0.2,5);
        glScalef(0.1,0.25,road);
        glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(1,1,0);
        glTranslatef(1.54,0.2,5);
        glScalef(0.1,0.25,road);
        glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(1,1,0);
        glTranslatef(3.54,0.2,5);
        glScalef(0.1,0.25,road);
        glutSolidCube(1);
    glPopMatrix();

}

static void drawBall(){
    glPushMatrix();
        //glColor3f(0,0,1);
        
        glTranslatef(move,0.5,animation_parameter);
        glRotatef(animation_parameter*acceleration,1,0,0);
        glutSolidSphere(0.30,100,100);
    glPopMatrix();
}

void drawWall(int randomNumber, int i){
        
            glPushMatrix();
                glColor3f(0, 0, 1);
               
                glTranslatef(randomNumber+0.06,1,5+10*i);
                glScalef(1,1,1);
                glutSolidCube(1);
            glPopMatrix();

}
