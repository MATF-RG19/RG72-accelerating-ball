#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>
#define TIMER_ID 1
#define TIMER_INTERVAL 20

static void on_reshape(int width, int height);
static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int id);
static void output(char* string);
static void output2(int score);
static void drawTrack();
static void drawBall();
static void drawWall();
static void drawCoin();
static void crash();
static void collectedCoin();
static void drawDCoin();
static void collectedDCoin();
static int i;
int score = 0;
int animation_ongoing;
float animation_parameter;
float move = 2.04;
int acceleration = 1;
int road = 200;
int randomNumber;
int wallArray[500];
int coinArray[500];
int coindArray[500];


int main(int argc,char** argv){
    
    GLfloat light_position[] = { 1, 3, 5, 0};
    
    GLfloat light_ambient[] = { 0, 0, 0, 1 };

    GLfloat light_diffuse[] = { 0.3, 0.3, 0.3, 1};

    GLfloat light_specular[] = { 0.3, 0.3, 0.3, 1 };

    GLfloat model_ambient[] = { 0.4, 0.4, 0.4, 1 };
    
    srand(time(0));
    for(i=0;i<500;i++){
        randomNumber = rand()%5;
        wallArray[i] = randomNumber;
    }

    for(i=0;i<100;i++){
        randomNumber = rand()%5;
        coinArray[i] = randomNumber;
    }

    for(i=0;i<100;i++){
        randomNumber = rand()%5;
        coindArray[i] = randomNumber;
    }

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
    drawWall();
    crash();
    drawCoin();
    collectedCoin();
    drawDCoin();
    collectedDCoin();
    if(animation_ongoing==0){
                char* string = {"Vas skor je:"};    
                output(string);
                output2(score);
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
            printf("Vas trenutni skor je: %d\n", score);
            break;
        case 'r':
        case 'R':
            animation_parameter = 0;
            animation_ongoing = 0;
            glutPostRedisplay();
            acceleration = 3;
            printf("Vas skor je: %d\n", score);
            score = 0;
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
    score+=1;
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
        glColor3f(0,1,1);
        
        glTranslatef(move,0.5,animation_parameter);
        glRotatef(animation_parameter*acceleration,1,0,0);
        glutSolidSphere(0.30,30,30);
    glPopMatrix();
   
}

void drawCoin(){
     for(i=0;i<100;i++){
            glPushMatrix();
                glColor3f(1,1,0);
                glTranslatef(coinArray[i]+0.06,0.7,5+50*i);
                glScalef(0.5,0.5,0.1);
                glRotatef(animation_parameter*10,0,1,0);
                glutSolidCube(1);
            glPopMatrix();
            
        }
}

void drawWall(){
        for(i=0;i<500;i++){
            glPushMatrix();
                glColor3f(0, 0, 1);
                glTranslatef(wallArray[i]+0.06,0.5,5+10*i);
                glScalef(1,1,1);
                glutSolidCube(1);
            glPopMatrix();
            
        }
}


void drawDCoin(){
     for(i=0;i<100;i++){
            glPushMatrix();
                glColor3f(1, 0, 0);
                glTranslatef(coindArray[i]+0.06,0.7,5+100*i);
                glScalef(0.5,0.5,0.1);
                glRotatef(animation_parameter*10,0,1,0);
                glutSolidCube(1);
            glPopMatrix();
            
        }
}


void crash(){
    for(i=0;i<500;i++){
        int xBall = floor(move-0.04+2);
        int xWall = floor(wallArray[i]+1);
        int zWall = floor(5+10*i);
        int zBall = floor(animation_parameter+1.2);
        if(zBall==zWall && xBall==xWall){
            animation_ongoing = 0;
            acceleration = 0;
            animation_parameter = 0;
            score = 0;
        }
    }
}

void collectedCoin(){
    for(i=0;i<100;i++){
        int a = 50;
        int xBall = floor(move-0.04+2);
        int xCoin = floor(coinArray[i]+1);
        int zCoin = floor(5+50*i);
        int zBall = floor(animation_parameter+1.2);
        if(zBall==zCoin && xBall==xCoin){
            printf("Skor je uvecan za: %d\n",a);
            score+=50;
        }
    }
}

void collectedDCoin(){
    for(i=0;i<100;i++){
        int a = 80;
        int xBall = floor(move-0.04+2);
        int xCoin = floor(coindArray[i]+1);
        int zCoin = floor(5+100*i);
        int zBall = floor(animation_parameter+1.2);
        if(zBall==zCoin && xBall==xCoin){
            
            
            if(acceleration>100){
                acceleration-=80;
                printf("Brzina je smanjena za: %d\n",a);
            }
        }
    }
}

void output(char *string)
{
  glColor3f(1,1,1);
  glRasterPos3f(1,3,animation_parameter);
  int len, i;
  len = (int)strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, string[i]);
  }
  
  
}

void output2(int score)
{
  glColor3f(1,1,1);
  glRasterPos3f(0.5,3,animation_parameter);
  glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, score);
  
  
  
}