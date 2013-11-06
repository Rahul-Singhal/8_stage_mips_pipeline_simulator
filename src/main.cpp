#include <GL/glut.h>
#include <stdlib.h>
#include "Instruction.h"
#include <iostream>
#include "drawingQueue.h"
#include "Program.h"
using namespace std;
 
float scrollX = 0;
float scrollY = 0;
Program p("shit");
int win_height, win_width;

DrawingQueue dq;

/* GLUT callback Handlers */
static void resize(int width, int height)
{
    if  ( height == 0 ) height = 1;

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  win_width = width;
  win_height = height;

  glOrtho( 0.0, (GLdouble)width, 0.0, (GLdouble)height, -1., 1. );
  glViewport( 0, 0, width, height );
  glutPostRedisplay();
}
 
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
        glTranslatef(scrollX, scrollY, 0);
        glPushMatrix();
        glTranslatef(0,win_height,0);
        dq.draw(scrollX, scrollY);
        glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}
 

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
        case 's':
            dq.drawFinishedQueue(p.execute());
            break;
    }
    glutPostRedisplay();
}
 
static void idle(void)
{
    glutPostRedisplay();
}

void init(){
    p.init();
    /*vector <Instruction > v;
    Instruction inst1(1,1,false,1, 20, false, 10, 20, "add $t1, $t2, $t3", 0);
    Instruction inst2(4,2,false,1, 20, false, 10, 20, "hey there2", 0);
    Instruction inst3(4,3,false,1, 20, false, 10, 20, "hey there3", 0);
    Instruction inst4(4,4,false,1, 20, false, 10, 20, "hey there4", 0);
    Instruction inst5(4,5,false,1, 20, false, 10, 20, "hey there5", 0);
    Instruction inst6(4,6,false,1, 20, false, 10, 20, "hey there6", 0);
    Instruction inst7(4,7,false,1, 20, false, 10, 20, "hey there7", 0);
    Instruction inst8(4,8,false,1, 20, false, 10, 20, "hey there8", 0);

    Instruction inst11(1,1,false,1, 20, false, 10, 20, "add $t4, $t1, $t3", 1);
    Instruction inst21(4,2,false,1, 20, false, 10, 20, "hey there2", 1);

    Instruction inst311(4,3,true,0, 20, false, 10, 20, "hey there2", 1);
    Instruction inst312(4,3,true,0, 20, false, 10, 20, "hey there2", 1);
    Instruction inst313(4,3,true,0, 20, false, 10, 20, "hey there2", 1);
    Instruction inst314(4,3,true,0, 20, false, 10, 20, "hey there2", 1);

    Instruction inst31(4,3,false,1, 20, false, 10, 20, "hey there3", 1);
    Instruction inst41(4,4,false,1, 20, false, 10, 20, "hey there4", 1);
    Instruction inst51(4,5,false,1, 20, false, 10, 20, "hey there5", 1);
    Instruction inst61(4,6,false,1, 20, false, 10, 20, "hey there6", 1);
    Instruction inst71(4,7,false,1, 20, false, 10, 20, "hey there7", 1);
    Instruction inst81(4,8,false,1, 20, false, 10, 20, "hey there8", 1);

    //instruction to check vertical scrollability

    Instruction insta1(4,8,false,1, 20, false, 10, 20, "hey there8", 2);
    Instruction insta2(4,8,false,1, 20, false, 10, 20, "hey there8", 3);
    Instruction insta3(4,8,false,1, 20, false, 10, 20, "hey there8", 4);
    Instruction insta4(4,8,false,1, 20, false, 10, 20, "hey there8", 5);
    Instruction insta5(4,8,false,1, 20, false, 10, 20, "hey there8", 6);
    Instruction insta6(4,8,false,1, 20, false, 10, 20, "hey there8", 7);
    Instruction insta7(4,8,false,1, 20, false, 10, 20, "hey there8", 8);
    Instruction insta8(4,8,false,1, 20, false, 10, 20, "hey there8", 9);
    Instruction insta9(4,8,false,1, 20, false, 10, 20, "hey there8", 10);
    Instruction insta10(4,8,false,1, 20, false, 10, 20, "hey there8", 11);
    Instruction insta11(4,8,false,1, 20, false, 10, 20, "hey there8", 12);
    Instruction insta12(4,8,false,1, 20, false, 10, 20, "hey there8", 13);
    Instruction insta13(4,8,false,1, 20, false, 10, 20, "hey there8", 14);
    Instruction insta14(4,8,false,1, 20, false, 10, 20, "hey there8", 15);
    Instruction insta15(4,8,false,1, 20, false, 10, 20, "hey there8", 16);
    Instruction insta16(4,8,false,1, 20, false, 10, 20, "hey there8", 17);

    v.push_back(inst1);
    dq.drawFinishedQueue(v);

    v.clear();
    v.push_back(inst2);
    v.push_back(inst11);
    dq.drawFinishedQueue(v);

    v.clear();
    v.push_back(inst3);
    v.push_back(inst21);
    dq.drawFinishedQueue(v);

    v.clear();
    v.push_back(inst4);
    v.push_back(inst311);
    dq.drawFinishedQueue(v);

    v.clear();
    v.push_back(inst5);
    v.push_back(inst312);
    dq.drawFinishedQueue(v);

    v.clear();
    v.push_back(inst6);
    v.push_back(inst313);
    dq.drawFinishedQueue(v);  

    v.clear();
    v.push_back(inst7);
    v.push_back(inst314);
    dq.drawFinishedQueue(v);  

    v.clear();
    v.push_back(inst8);
    v.push_back(inst31);
    dq.drawFinishedQueue(v);

    v.clear();
    v.push_back(inst41);
    dq.drawFinishedQueue(v);

    v.clear();
    v.push_back(inst51);
    dq.drawFinishedQueue(v);

    v.clear();
    v.push_back(inst61);
    dq.drawFinishedQueue(v);

    v.clear();
    v.push_back(inst71);
    dq.drawFinishedQueue(v);

    v.clear();
    v.push_back(inst81);
    dq.drawFinishedQueue(v);

    v.clear();
    v.push_back(insta1);
    v.push_back(insta2);
    v.push_back(insta3);
    v.push_back(insta4);
    v.push_back(insta5);
    v.push_back(insta6);
    v.push_back(insta7);
    v.push_back(insta8);
    v.push_back(insta9);
    v.push_back(insta10);
    v.push_back(insta11);
    v.push_back(insta12);
    v.push_back(insta13);
    v.push_back(insta14);
    v.push_back(insta15);
    v.push_back(insta16);
    dq.drawFinishedQueue(v);*/
}
 
void specialKey(int key, int x, int y){
    float shift = 6;
    switch(key){
        case GLUT_KEY_LEFT:
            if(scrollX < 0) scrollX += shift;
            else return;
            break;
        case GLUT_KEY_RIGHT:
            if(scrollX > -(dq.getMaxScrollableX() - win_width))scrollX -= shift;
            break;
        case GLUT_KEY_UP:
            if(scrollY > 0) scrollY -= shift;
            else return;
            break;
        case GLUT_KEY_DOWN:
            if(scrollY < (dq.getMaxScrollableY()-win_height))scrollY += shift;
            else return;
            break;
    }
    glutPostRedisplay();
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
 
    glutCreateWindow("8 Stage Pipeline Simulator");
 
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(specialKey);

    glClearColor(1,1,1,0);
    init();
    // dq = DrawingQueue();
    glutMainLoop();
 
    return EXIT_SUCCESS;
}