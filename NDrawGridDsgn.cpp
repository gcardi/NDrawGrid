//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop

#include "NDrawGrid.h"
#include "NDrawGridDsgn.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
//---------------------------------------------------------------------------

namespace Ndrawgriddsgn
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = { __classid( TNDrawGrid ) };
		RegisterComponents( L"Anafestica", classes, 0 );
	}
}
//---------------------------------------------------------------------------


