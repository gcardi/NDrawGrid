//---------------------------------------------------------------------------

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

static inline void ValidCtrCheck( TNDrawGrid * )
{
	new TNDrawGrid( NULL );
}
//---------------------------------------------------------------------------

namespace Ndrawgriddsgn
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = { __classid( TNDrawGrid ) };
		RegisterComponents( _T( "Anafestica" ), classes, 0 );
	}
}
//---------------------------------------------------------------------------

