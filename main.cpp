#include "gg.h"

#define IMAGECLASS Images
#define IMAGEFILE <gg/gg.iml>
#include <Draw/iml_source.h>


GUI_APP_MAIN
{
	GameGate().Run();
}

////////////////////////////////////////////////////////////////////////////////////////////////
GameGate::GameGate()
{
	CtrlLayout(*this, "Window title");
	
	//mt.Transparent(false);
	//Add(mt);
	//mt.SizePos();
	//mt.Hide();
	skip.Disable();
	conf.Disable();
	skip << THISBACK(Skip);
	conf << THISBACK(Conf);
	pwd << THISBACK(Pwd);
	start << THISBACK(Start);
}

void GameGate::Serialize(Stream& s)
{
	int version = 0;
	s / version;
	s / password;
	SerializePlacement(s);
	//sclist.Serialize(s);
}

void GameGate::Start()
{
	MathTest mt;
	//mt.Open();
	mt.Title("Math test");
	int i = mt.Execute();//.RunAppModal();
	//mt.Show();
}

void GameGate::Conf()
{
}

void GameGate::Skip()
{
	Close();
}

void GameGate::Pwd()
{
	bool b = password == pwd;
	skip.Enable(b);
	conf.Enable(b);
}

////////////////////////////////////////////////////////////////////////////////////////////////
MathTest::MathTest()
{
	CtrlLayout(*this, "Math test");
	
	level   = 10;
	time    = 15;
	count   = 10;
	option0.WhenPush = THISBACK1(Select, 0);
	option1.WhenPush = THISBACK1(Select, 1);
	option2.WhenPush = THISBACK1(Select, 2);
	option3.WhenPush = THISBACK1(Select, 3);
	option4.WhenPush = THISBACK1(Select, 4);
	restart << THISBACK(Start);
	progress.Set(0, count);
}

void MathTest::Start()
{
//	KillTimeCallback(TID_LOADTOPICS);
	InitTopics();
	LoadTopics();
}

void MathTest::Select(int i)
{
	if(i < 5 && i >= 0)
	{
		Topic& t = mts[current];
		if(t.opt[i] == t.c)
			Correct();
		else
			Wrong();
		//SetTimeCallback(1000, THISBACK(LoadTopics));//, TID_LOADTOPICS);
		LoadTopics();
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
	formula.SetImage(Images::Wrong());
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
		//case 1: // minus
		default:
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
	//KillTimeCallback();
	current++;
	if(current == count)
	{
		//Break(IDOK);
		return;
	}
	
	Topic& t = mts[current];
	
	String s;
	s << t.a << (t.op ? '-' : '+') << t.b << "=";
	formula.SetText(s);
	formula.SetImage(Images::Question()); // ?
	
	option0.SetLabel(IntStr(t.opt[0]));
	option1.SetLabel(IntStr(t.opt[1]));
	option2.SetLabel(IntStr(t.opt[2]));
	option3.SetLabel(IntStr(t.opt[3]));
	option4.SetLabel(IntStr(t.opt[4]));
	
	progress.Set(current + 1, count);
}
