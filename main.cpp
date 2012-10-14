#include "gg.h"

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
