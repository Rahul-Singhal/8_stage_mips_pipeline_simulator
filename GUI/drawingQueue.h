#ifndef DRAWINGQUEUE_H
#define DRAWINGQUEUE_H
#include <vector>
#include <string>
#include "Instruction.h"
#include <GL/glut.h>
#include <map>
#include <utility>
using namespace std;

class DrawingQueue{
private:
	float instHeight;
	float instWidth;
	int maxIdDrawn;
	vector< pair<int,string> > instStrings;
	map <int, double *> stageColorMap;
	map <int, string> stageStringMap;
	vector<vector <Instruction> > displayVector;
	void drawArrow(int back ,int up);
	void drawInstruction(Instruction inst, int i, int j);
	void render_bitmap_string(float x, float y, float z, void *font, const char *string);
	void drawHeader();
	void drawSideBar(float scrollX);

public:
	DrawingQueue();
	void drawFinishedQueue(vector<Instruction> v);
	void draw(int scrollX, int scrollY);
	int getMaxScrollableX();
	int getMaxScrollableY();
};

#endif