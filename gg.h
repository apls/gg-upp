#ifndef _gg_gg_h
#define _gg_gg_h

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define LAYOUTFILE <gg/gg.lay>
#include <CtrlCore/lay.h>

#define IMAGECLASS Images
#define IMAGEFILE <gg/gg.iml>
#include <Draw/iml_header.h>

class GameGate : public WithGameGateLayout<TopWindow> 
{
public:
	typedef GameGate CLASSNAME;
	GameGate();
};


class MathTest : public WithMathTestLayout<TopWindow> 
{
public:
	typedef MathTest CLASSNAME;
	
	MathTest();
	void Begin();
	void InitTopics();
	void LoadTopics();
	
	void Select(int i);
	void Correct();
	void Wrong();
	
protected:
	struct Topic {
		int op;
		int a, b, c;
		int opt[5];
	};
	Array<Topic> mts;
	int level;
	int time;
	int count;
	int current;

};

#endif
