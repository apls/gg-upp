#ifndef _gg_gg_h
#define _gg_gg_h

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define LAYOUTFILE <gg/gg.lay>
#include <CtrlCore/lay.h>

#define IMAGEFILE <gg/gg.iml>
#include <Draw/iml_header.h>

class GameGate : public WithGameGateLayout<TopWindow> {
public:
	typedef GameGate CLASSNAME;
	GameGate();
};

#endif
