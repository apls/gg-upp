#include "gg.h"

#define IMAGECLASS Images
#define IMAGEFILE <gg/gg.iml>
#include <Draw/iml_source.h>

GameGate::GameGate()
{
	CtrlLayout(*this, "Window title");
}

GUI_APP_MAIN
{
	GameGate().Run();
}


MathTest::MathTest()
{
	level   = 10;
	time    = 15;
	count   = 10;
	option0.WhenPush = THISBACK1(Select, 0);
	option1.WhenPush = THISBACK1(Select, 1);
	option2.WhenPush = THISBACK1(Select, 2);
	option3.WhenPush = THISBACK1(Select, 3);
	option4.WhenPush = THISBACK1(Select, 4);
}

void MathTest::Begin()
{
	InitTopics();
	LoadTopics();
}

void MathTest::Select(int i)d
{
	if(i < 5 && i >= 0)
	{
		Topic& t = mts[current];
		if(t.opt[i] == t.c)
			Correct();
		else
			Wrong();
		SetTimeCallback(1000, THISBACK(LoadTopics));
	}
}

void MathTest::Correct()
{
	//PromptOK("Wrong Answer");
	formula.SetImage(Images::Correct());
}

void MathTest::Wrong()
{
	//PromptOK("Answered correctly");
	formula.SetImage(Images::Correct());
}


void MathTest::InitTopics()
{
	current = -1;
	mts.SetCount(count);
	
	for(int i = 0; i < count; i++)
	{
		int a = Random(level);
		int b = Random(level);
		int c = 0;
		int op = Random(2);
		switch(op)
		{
		case 0: // plus
			c = max(a, b);
			a = min(a, b);
			b = c - a;
			break;
		case 1: // minus
			c = max(a, b);
			b = min(a, b);
			a = c;
			c = a - b;
			break;
		}
		mts[i].a = a;
		mts[i].b = b;
		mts[i].c = c;
		mts[i].op = op;
		
		c -= Random(min(c, 5));
		for(a = 0; a < 5; a++, c++)
			mts[i].opt[a] = c;
	}
}

void MathTest::LoadTopics()
{
	current++;
	Topic& t = mts[current];
	
	String s;
	s << t.a << (t.op ? '-' : '+') << t.b << "=?";
	formula.SetText(s);
	
	option0.SetLabel(IntStr(t.opt[0]));
	option1.SetLabel(IntStr(t.opt[1]));
	option2.SetLabel(IntStr(t.opt[2]));
	option3.SetLabel(IntStr(t.opt[3]));
	option4.SetLabel(IntStr(t.opt[4]));
	
	progress.Set(current, count);
}
