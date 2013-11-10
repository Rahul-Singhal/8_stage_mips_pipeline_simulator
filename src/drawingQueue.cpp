#include "drawingQueue.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;


void DrawingQueue::render_bitmap_string(float x, float y, float z, void *font, const char *str){  
  const char *c;
  int str_len = strlen(str);
  int str_pel_width;
  for (unsigned int i = 0; i < str_len; i++)
  str_pel_width += glutBitmapWidth (GLUT_BITMAP_HELVETICA_12, str[i]);
  glRasterPos3f(x-(str_pel_width/2) , y,z);
  for (c=str; *c != '\0'; c++) 
    {
      glutBitmapCharacter(font, *c);
    }
}

int DrawingQueue::getMaxScrollableX(){
	return ((displayVector.size())*(instWidth+2)) + 50;
}

int DrawingQueue::getMaxScrollableY(){
	return (maxIdDrawn*(instHeight+20)) + 50;
}

void DrawingQueue::drawHeader(){
	int curSize = displayVector.size();
	glPushMatrix();
	glBegin(GL_QUADS);
		glColor3f(1,1,1);
		glVertex2f(-(instWidth+2)*curSize,instHeight*20);
        glVertex2f(-(instWidth+2)*curSize,-10);
        glVertex2f(+(instWidth+2)*curSize,-10);
        glVertex2f(+(instWidth+2)*curSize,instHeight*20);
	glEnd();
	glPopMatrix();

	char ch[10];
	for(int i= curSize-1; i>=0; i--){
		if(i != 0) sprintf(ch, "-%d", i);
		else sprintf(ch, "%d", i);
		glPushMatrix();
		glTranslatef((instWidth+2)*(curSize-i-1),0,0);
		glBegin(GL_LINE_STRIP);
			glColor3f(0,0,0);
			glVertex2f(-instWidth/2,instHeight/4);
	        glVertex2f(-instWidth/2,0);
	        glVertex2f(instWidth/2,0);
	        glVertex2f(instWidth/2,instHeight/4);
		glEnd();
		render_bitmap_string(0,10,0, GLUT_BITMAP_HELVETICA_12, ch);
		glPopMatrix();
	}
}

void DrawingQueue::drawSideBar(float scrollX){
	glPushMatrix();
	glBegin(GL_QUADS);
		glColor3f(1,1,1);
		glVertex2f(-500,500);
        glVertex2f(-500,-((maxIdDrawn*(instHeight+20)) + 50));
        glVertex2f(0, -((maxIdDrawn*(instHeight+20)) + 50));
        glVertex2f(0,500);
	glEnd();
	glPopMatrix();

	glPushMatrix();
		glLineWidth(3);
		glBegin(GL_LINES);
		glColor3f(0,0,0);
		glVertex2f(0,0);
		glVertex2f(0,-((maxIdDrawn*(instHeight+20)) + 50));
		glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-80,-instHeight,0);
	for(int i = 0 ; i<instStrings.size(); i++){
		glPushMatrix();
		glTranslatef(0,-((instHeight+20)*instStrings[i].first), 0);
		render_bitmap_string(0,-5,0, GLUT_BITMAP_HELVETICA_12, instStrings[i].second.c_str());
		glPopMatrix();
	}
	glPopMatrix();
}
 

DrawingQueue::DrawingQueue(){
	// ////cout<<"IT COMES HERE"<<endl;
	instHeight = 20;
	instWidth = 50;
	maxIdDrawn = 2;
	displayVector.clear();

	stageColorMap.clear();
	stageStringMap.clear();
	//stage 1
	stageColorMap[1] = new double[3];
	stageColorMap[1][0]= 0.372549;
	stageColorMap[1][1]= 0.619608;
	stageColorMap[1][2]= 0.627451;
	stageStringMap[1]="IF1";

	//stage2
	stageColorMap[2] = new double[3];
	stageColorMap[2][0]= 1;
	stageColorMap[2][1]= 0.498039;
	stageColorMap[2][2]= 0.313725;
	stageStringMap[2]="IF2";

	//stage3
	stageColorMap[3] = new double[3];
	stageColorMap[3][0]= 0.392157;
	stageColorMap[3][1]= 0.584314;
	stageColorMap[3][2]= 0.929412;
	stageStringMap[3]="ID";

	//stage4
	stageColorMap[4] = new double[3];
	stageColorMap[4][0]= 0.662745;
	stageColorMap[4][1]= 0.662745;
	stageColorMap[4][2]= 0.662745;
	stageStringMap[4]="EX";

	//stage5
	stageColorMap[5] = new double[3];
	stageColorMap[5][0]= 0.803922;
	stageColorMap[5][1]= 0.360784;
	stageColorMap[5][2]= 0.360784;
	stageStringMap[5]="MULT";

	//stage6
	stageColorMap[6] = new double[3];
	stageColorMap[6][0]= 0.737255;
	stageColorMap[6][1]= 0.560784;
	stageColorMap[6][2]= 0.560784;
	stageStringMap[6]="DIV";

	//stage7
	stageColorMap[7] = new double[3];
	stageColorMap[7][0]= 0.282353;
	stageColorMap[7][1]= 0.239216;
	stageColorMap[7][2]= 0.545098;
	stageStringMap[7]="MEM1";

	//stage8
	stageColorMap[8] = new double[3];
	stageColorMap[8][0]= 0;
	stageColorMap[8][1]= 0.74902;
	stageColorMap[8][2]= 1;
	stageStringMap[8]="MEM2";

	//stage9
	stageColorMap[9] = new double[3];
	stageColorMap[9][0]= 0.12549;
	stageColorMap[9][1]= 0.698039;
	stageColorMap[9][2]= 0.666667;
	stageStringMap[9]="MEM3";

	//stage10
	stageColorMap[10] = new double[3];
	stageColorMap[10][0]= 1;
	stageColorMap[10][1]= 0.647059;
	stageColorMap[10][2]= 0;
	stageStringMap[10]="WB";
}

void DrawingQueue::drawFinishedQueue(vector<Instruction> v){
	displayVector.push_back(v);
	//you need to call this function from your program and then call draw() which would essentially call glutPostRedisplay();
}

void DrawingQueue::draw(int scrollX, int scrollY){

	instStrings.clear();

	
	glPushMatrix();
	glTranslatef(instWidth/2 + 150, -((3*instHeight)/2 + 20), 0);
	for(int i =0 ; i<displayVector.size(); i++){
		glPushMatrix();
		for(int j = 0 ; j<displayVector[i].size(); j++){
			//draw the instruction corresponding to ith column and jth row in it
			drawInstruction(displayVector[i][j], i, j);
		}
		glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix();
		glTranslatef(instWidth/2 + 150, -(instHeight/2 + 20) - scrollY, 0);
		drawHeader();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(instWidth/2 + 110-scrollX, -(instHeight/2 + 20), 0);
		drawSideBar(scrollX);
	glPopMatrix();
}

void DrawingQueue::drawInstruction(Instruction inst, int i, int j){
	//draw the instruction corresponding to ith column and jth row in 
	string str = inst.getDisplayString();
	int prStage = inst.getPresentStage();
	////cout<<"YONESS"<<inst.getId()<<"YONESS"<<endl;
	if(prStage == 0) return;
	double * colors = stageColorMap[prStage];
	// if(inst.getPresentStage() == 1){
	// 	instStrings.push_back(pair<int, string> (inst.getId(), str));
	// }
	maxIdDrawn = maxIdDrawn > inst.getId()? maxIdDrawn:inst.getId();
	glPushMatrix();
	glTranslatef((instWidth+2)*i, -((instHeight+20)*inst.getId()), 0);
    glBegin(GL_QUADS);
        glColor3f(colors[0],colors[1],colors[2]);
        //glColor3f(0,0,1);
        glVertex2f(-instWidth/2,instHeight/2);
        glVertex2f(instWidth/2,instHeight/2);
        glVertex2f(instWidth/2,-instHeight/2);
        glVertex2f(-instWidth/2,-instHeight/2);
    glEnd();
    //text color
    glColor3f(1,1,1);
    if(!inst.getStalled() && !inst.getForwarded()) {
    	render_bitmap_string(0,-5,0, GLUT_BITMAP_HELVETICA_12, stageStringMap[prStage].c_str());
    }
    if(inst.getStalled()){

    	render_bitmap_string(0,-5,0, GLUT_BITMAP_HELVETICA_12, "STALL");
    	int lastQueueStartId = displayVector[i-1][0].getId();
    	if(displayVector[i-1][inst.getId() - lastQueueStartId].getStalled()){
    		//no need to draw any more arrows
    	}
    	else{
    		if(inst.getStallingInstructionId() != -1){
	    		//draw arrow
	    		int alpha = 0;
	    		int beta;
	    		//int lastQueueStartId = displayVector[i-alpha][0].getId();
	    		// stage 3 is ID
	    		bool myFlag = false;
	    		int stallInstId = inst.getStallingInstructionId();
	    		while(alpha++){
	    			int maxLeng = displayVector[i-alpha].size();
	    			for(beta = 0; beta < maxLeng; beta++){
	    				if(displayVector[i-alpha][beta].getId() == stallInstId){
	    					myFlag = true;
	    					break;
	    				}
	    				else if(displayVector[i-alpha][beta].getId() > stallInstId){
	    					myFlag = false;
	    					break;
	    				}
	    			}
	    			if(myFlag) break;
	    		}
	    		//draw arrow from rectangle alpha blocks back and inst.getId()-inst.getStallingInstructionId() up

	    		drawArrow(alpha, beta+1);
    		}

		}
	}
	if(inst.getForwarded()){
		//draw arrow to display forwarding

		int alpha = 1;
		int lastQueueStartId = displayVector[i-alpha][0].getId();
		// 
		// while(!(displayVector[i-alpha][inst.getForwardedFromInstructionId() - lastQueueStartId].getPresentStage() == inst.getForwardedFromInstructionStage())){
		// 	alpha++;
		// 	lastQueueStartId = displayVector[i-alpha][0].getId();
		// }

		// //draw arrow from rectangle alpha blocks back and inst.getId()-inst.getStallingInstructionId() up
		// drawArrow(alpha, inst.getId()-inst.getForwardedFromInstructionId());

	}
    glPopMatrix();
}

void DrawingQueue::drawArrow(int back ,int up){
	double x1 = 0;
	double x2 = -((instWidth+2)*back);
	double y1 = instHeight/2;
	double y2 = ((instHeight+20)*up)-instHeight/2;
	glPushMatrix();
		glLineWidth(3);
		glBegin(GL_LINES);
			glColor3f(0,0,0);
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
		glEnd();
	glPopMatrix();

	double dx = x2-x1;
	double dy = y2-y1;
	double leng = sqrt(dx*dx + dy*dy);
	dx = dx/leng;
	dy = dy/leng;

	double pX = x1 + dx*10;
	double pY = y1 + dy*10;

	glPushMatrix();
		glLineWidth(3);
		glBegin(GL_LINES);
			glColor3f(0,0,0);
			glVertex2f(x1,y1);
			glVertex2f(pX + 4*(-dy),pY + 4*(dx));
		glEnd();
	glPopMatrix();

	glPushMatrix();
		glLineWidth(3);
		glBegin(GL_LINES);
			glColor3f(0,0,0);
			glVertex2f(x1,y1);
			glVertex2f(pX - 4*(-dy),pY - 4*(dx));
		glEnd();
	glPopMatrix();


}