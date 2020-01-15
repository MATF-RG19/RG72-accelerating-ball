#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>
#include "image.h"
#define TIMER_ID 1
#define TIMER_INTERVAL 20
#define FILENAME0 "sun.bmp"
#define FILENAME1 "pleiades-sevensisters.bmp"
#define FILENAME2 "meteor.bmp"

static void on_reshape(int width, int height);
static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int id);
static void output();
static void output2();
static void drawTrack();
static void drawBall();
static void drawWall();
static void drawCoin();
static void crash();
static void collectedCoin();
static void drawDCoin();
static void collectedDCoin();
static void initialize(void);
static int i;
int score = 0;
int highScore = 0;
int animation_ongoing;
float animation_parameter;
float move = 2.04;
int acceleration = 1;
int road = 200;
int randomNumber;
int wallArray[500];
int coinArray[500];
int coindArray[500];
static GLuint names[7];


int main(int argc,char** argv){
    
    GLfloat light_position[] = { 1, 3, 5, 0};
    
    GLfloat light_ambient[] = { 0, 0, 0, 1 };

    GLfloat light_diffuse[] = { 0.3, 0.3, 0.3, 1};

    GLfloat light_specular[] = { 0.3, 0.3, 0.3, 1 };

    GLfloat model_ambient[] = { 0.4, 0.4, 0.4, 1 };
    
    srand(time(0));
    /*Generisanje random brojeva za postavljanje prepreka, novcica za skor i novcica za usporavanje*/
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
    
    initialize();

    glutMainLoop();
    
    
    return 0;
}

static void on_display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /*Postavljanje kamere*/
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2,3,animation_parameter-5,
                2,0,animation_parameter+1,
                0,1,0);
    /*Iscrtavanje objekata u igri*/
    drawTrack();    
    drawBall();
    drawWall();
    crash();
    drawCoin();
    collectedCoin();
    drawDCoin();
    collectedDCoin();
    /*Ispis skora i high skora*/
    output();
    output2();
    
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
            /*Pauza*/
        case 's':
        case 'S':
            if(animation_ongoing){
                animation_ongoing = 0;
            }
            printf("Vas trenutni skor je: %d\n", score);
            break;
            /*Restart*/
        case 'r':
        case 'R':
            animation_parameter = 0;
            animation_ongoing = 0;
            glutPostRedisplay();
            acceleration = 3;
            printf("Vas skor je: %d\n", score);
            score = 0;
            break;
            /*Skretanje u levo*/
        case 'a':
        case 'A':
            if(move<3.04){
                move +=1;
                glutPostRedisplay();
                break;
            }else break;
            /*Skretanje u desno*/
        case 'd':
        case 'D':
            if(move>0.04){
                move -=1;
                glutPostRedisplay();
                break;
            }else break;
            /*Pokretanje igre*/
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
    acceleration+=2;
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
        glColor3f(0,0,0);
        glTranslatef(0.54,0.2,5);
        glScalef(0.1,0.25,road);
        glutSolidCube(1);
    glPopMatrix();
      
    glPushMatrix();
        glColor3f(0,0,0);
        glTranslatef(2.54,0.2,5);
        glScalef(0.1,0.25,road);
        glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(0,0,0);
        glTranslatef(1.54,0.2,5);
        glScalef(0.1,0.25,road);
        glutSolidCube(1);
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(0,0,0);
        glTranslatef(3.54,0.2,5);
        glScalef(0.1,0.25,road);
        glutSolidCube(1);
    glPopMatrix();

}
/*Iscrtavanje loptice koja izgleda kao Sunce*/
static void drawBall(){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, names[0]);
        glEnable(GL_TEXTURE_2D);
        GLUquadric* sphere = gluNewQuadric();
        gluQuadricTexture(sphere, GL_TRUE);
        glTranslatef(move,0.5,animation_parameter);
        glRotatef(animation_parameter*acceleration,1,0,0);
        gluSphere(sphere, (GLdouble) 0.30, (GLint) 100, (GLint) 100);        

       // glutSolidSphere(0.30,30,30);
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
   
}
/*Iscrtavanje novcica za skor koji izgleda kao meteor(nema razloga zasto tako izgleda :'D)*/
void drawCoin(){
     for(i=0;i<100;i++){
            glPushMatrix();
                glBindTexture(GL_TEXTURE_2D, names[2]);
                glEnable(GL_TEXTURE_2D);
       
                GLUquadric* disk1 = gluNewQuadric();

                gluQuadricTexture(disk1, GL_TRUE);
                glTranslatef(coinArray[i]+0.06,0.7,5+50*i);
                glScalef(0.5,0.5,0.1);
                glRotatef(180,0,1,0);
                
                
                gluDisk(disk1, 0.1 , 0.8, 30, 30);        
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);
   
            glPopMatrix();
            
        }
}
/*Iscrtavanje prepreka koje pokusavamo da izbegnemo*/
void drawWall(){
        for(i=0;i<500;i++){
            glPushMatrix();
                glColor3f(1, 0.2, 0.2);
                glTranslatef(wallArray[i]+0.06,0.5,5+10*i);
                glScalef(1,1,1);
                glutSolidCube(1);
            glPopMatrix();
            
        }
}

/*Iscrtavanje novcica za usporavanje loptice koji izgleda kao galaksija(takodje nema razloga zasto tako izgleda:'D)*/
void drawDCoin(){
     for(i=0;i<100;i++){
            glPushMatrix();
         
                glBindTexture(GL_TEXTURE_2D, names[1]);
                glEnable(GL_TEXTURE_2D);
       
                GLUquadric* disk = gluNewQuadric();
  
                gluQuadricTexture(disk, GL_TRUE);
                glTranslatef(coindArray[i]+0.06,0.7,5+70*i);
                glScalef(0.5,0.5,0.1);
                glRotatef(180,0,1,0);
        
                gluDisk(disk, 0.1 , 0.8, 30, 30);        
                glBindTexture(GL_TEXTURE_2D, 0);
                glDisable(GL_TEXTURE_2D);
   
            glPopMatrix();
            
        }
}

/*Detekcija sudara loptice sa preprekom*/
void crash(){
    for(i=0;i<500;i++){
        int xBall = floor(move-0.04+2);
        int xWall = floor(wallArray[i]+1);
        int zWall = floor(5+10*i);
        int zBall = floor(animation_parameter+1.2);
        if(zBall==zWall && xBall==xWall){
            printf("Vas skor je %d\n",score);
            if(score>highScore){
                highScore=score;
            }
            animation_ongoing = 0;
            acceleration = 0;
            animation_parameter = 0;
            score = 0;
        }
    }
}
/*Detekcija skupljanja novcica koji dodaje na skor*/
void collectedCoin(){
    for(i=0;i<100;i++){
        int xBall = floor(move-0.04+2);
        int xCoin = floor(coinArray[i]+1);
        int zCoin = floor(5+50*i);
        int zBall = floor(animation_parameter+1.2);
        if(zBall==zCoin && xBall==xCoin){
            score+=50;
        }
    }
}
/*Detekcija skupljanja novcica koji usporava lopticu*/
void collectedDCoin(){
    for(i=0;i<100;i++){
        int xBall = floor(move-0.04+2);
        int xCoin = floor(coindArray[i]+1);
        int zCoin = floor(5+70*i);
        int zBall = floor(animation_parameter+1.2);
        if(zBall==zCoin && xBall==xCoin){
            
            
            if(acceleration>160){
                acceleration-=160;
            }
        }
    }
}
/*Ispis trenutnog skora*/
void output()
{
  glRasterPos3f(1,3,animation_parameter);
    char scoreText[30] = "Vas skor je: ";
    char scoreValue[30];
    sprintf(scoreValue," %d ",score);
    strcat(scoreText,scoreValue);

    int len = (int)strlen(scoreText);

    for(int i = 0; i < len ; i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,scoreText[i]);
    }
  
}
/*Ispis high skora*/
void output2(){
    glRasterPos3f(1,2.7,animation_parameter);
    char highScoreText[30] = "High score je: ";
    char highScoreValue[30];
    sprintf(highScoreValue," %d ",highScore);
    strcat(highScoreText,highScoreValue);

    int len = (int)strlen(highScoreText);

    for(int i = 0; i < len ; i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,highScoreText[i]);
    }

}



/* Inicijalizacija parametara za postavljanje tekstura. */
static void initialize(void)
{
    /* Deklaracija teskture učitane iz fajla. */
    Image * image;

    /* Uključuju se teksture. */
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    /* Inicijalizuje se promenljiva image koji ce sadrzati teksture ucitane iz fajlova. */
    image = image_init(0, 0);

    /* Kreira se prva tekstura. */
    /* Generisu se identifikatori tekstura. */
    glGenTextures(7, names);

    image_read(image, FILENAME0);

    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);


    image_read(image, FILENAME1);

    glBindTexture(GL_TEXTURE_2D, names[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    
    image_read(image, FILENAME2);

    glBindTexture(GL_TEXTURE_2D, names[2]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    
    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Unistava se objekat za citanje tekstura iz fajla. */
    image_done(image);
}
/*Kod za teksture je preuzet sa vezbi, Cas 7.
  Ispis skora kao i high skora je preuzet sa neta i malo modifikovan tako da bude prilagodjen igri.*/