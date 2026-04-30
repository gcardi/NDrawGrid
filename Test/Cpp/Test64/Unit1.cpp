//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "NDrawGrid"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::NDrawGrid1NormalCellGetText(TObject *Sender, int ACol, int ARow,
          UnicodeString &Result)
{
    Result = Format( _D( "%d, %d" ), ACol, ARow );
}
//---------------------------------------------------------------------------

