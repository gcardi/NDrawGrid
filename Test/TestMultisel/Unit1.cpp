//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

#include "VclGdiplus.h"

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
    NDrawGrid2->ColWidths[2] = 120;

    selected_.insert( 5 );

    TStringDynArray StyleNames = TStyleManager::StyleNames;
    for ( int Idx = 0 ; Idx < StyleNames.Length ; ++Idx )
        ComboBox1->Items->Append( StyleNames[Idx] );
    ComboBox1->ItemIndex =
        ComboBox1->Items->IndexOf( TStyleManager::ActiveStyle->Name );

    int const RowCount = NDrawGrid2->RowCount - NDrawGrid2->FixedRows;
    int const ColCount = NDrawGrid2->ColCount - NDrawGrid2->FixedCols;
    gridData_.reserve( RowCount );
    RowCont ANewRow( ColCount );
    for ( int Row = 0 ; Row < RowCount ; ++Row ) {
        gridData_.push_back( ANewRow );
        for ( int Col = 0 ; Col < ColCount ; ++Col ) {
            gridData_[Row][Col] =
                String::Format( _T( "%d,%d" ), ARRAYOFCONST( ( Col, Row ) ) );
        }
    }

}
//---------------------------------------------------------------------------



bool TForm1::IsRowHighlighted( int Row ) const
{
    return selected_.find( Row ) != selected_.end();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
    String const NewStyleName = ComboBox1->Text;

    if ( !SameText( TStyleManager::ActiveStyle->Name, NewStyleName ) ) {
        ::OutputDebugString(
            String::Format(
                _T( "Switching style from \'%s\' to \'%s\'" ),
                ARRAYOFCONST( (
                    TStyleManager::ActiveStyle->Name,
                    NewStyleName
                ) )
            ).c_str()
        );
        TStyleManager::TrySetStyle( NewStyleName, true );
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
    selected_.clear();
    NDrawGrid2->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NDrawGrid2DrawCell(TObject *Sender, int ACol, int ARow, const TRect &Rect,
          TGridDrawState State)
{
    int const SelIdx = ARow - NDrawGrid2->FixedRows;

    if ( !State.Contains( gdFixed ) && IsRowHighlighted( ARow ) )
        NDrawGrid2->DefaultDrawCellHighlight( Rect, State, ACol, ARow );
    else
        NDrawGrid2->DefaultDrawCellBackground(Rect, NDrawGrid2->Color, State, ACol, ARow );

    if ( ARow == NDrawGrid2->Row ) {
        Gdiplus::Graphics g( NDrawGrid2->Canvas->Handle );
        Gdiplus::RectF Re = GdiplusUtils::VCLRectToGdiPlusRectF( Rect );
        Gdiplus::Color bc( /*Alpha*/ 0x80, /* Red */ 0x00, /* Green */ 0xFF, /* Blue */ 0xFF );
        Gdiplus::SolidBrush b( bc );
        g.FillRectangle( &b, Re );
    }

    TRect Rct( Rect );
    String Txt = NDrawGrid2->GetCellText( ACol, ARow );

    if ( StyleServices()->Enabled )
        InflateRect( Rct, -8, -2 );
    else {
        InflateRect( Rct, -2, -2 );
        NDrawGrid2->Canvas->Font->Color = NDrawGrid2->Font->Color;
    }

    NDrawGrid2->Canvas->Brush->Style = bsClear;
    NDrawGrid2->Canvas->TextRect(
        Rct, Txt, NDrawGrid2->GetCellTextFormat( ACol, ARow )
    );

}
//---------------------------------------------------------------------------

UnicodeString __fastcall TForm1::NDrawGrid2FixedCellGetText(TObject *Sender, int ACol,
          int ARow)
{
    switch ( ACol ) {
        case 2:
            return _T( "Drop down list" );
        default:
            return String::Format( _T( "-%03d-,-%03d-" ), ARRAYOFCONST( ( ACol, ARow ) ) );
    }
}
//---------------------------------------------------------------------------

TEditStyle __fastcall TForm1::NDrawGrid2GetEditStyle(TObject *Sender, int ACol, int ARow)
          
{
    if ( ACol == 2 )
        return esPickList;
    return esSimple;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NDrawGrid2GetEditText(TObject *Sender, int ACol, int ARow,
          UnicodeString &Value)
{
    Value = gridData_[ARow - NDrawGrid2->FixedRows][ACol - NDrawGrid2->FixedCols];
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NDrawGrid2GetPickListItems(int ACol, int ARow, TStrings *Items)

{
    Items->Append( _T( "Porceddu" ) );
    Items->Append( _T( "Cuccureddu" ) );
    Items->Append( _T( "Ahiò!" ) );
    Items->Append( _T( "Zac!" ) );
    Items->Append( _T( "Mirto" ) );
    Items->Append( _T( "Morto" ) );
    Items->Append( _T( "Eiàh!" ) );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NDrawGrid2KeyPress(TObject *Sender, System::WideChar &Key)
{
    if ( NDrawGrid2->Col == 2 )
        Key = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NDrawGrid2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
    int ACol;
    int ARow;

    NDrawGrid2->MouseToCell( X, Y, ACol, ARow );

    if ( ACol >= NDrawGrid2->FixedCols ) {

        if ( Shift.Contains( ssCtrl ) ) {
            if ( selected_.find( ARow ) != selected_.end() )
                selected_.erase( ARow );
            else
                selected_.insert( ARow );
            NDrawGrid2->InvalidateRow( ARow );
        }
    }

}
//---------------------------------------------------------------------------

UnicodeString __fastcall TForm1::NDrawGrid2NormalCellGetText(TObject *Sender, int ACol,
          int ARow)
{
    return gridData_[ARow - NDrawGrid2->FixedRows][ACol - NDrawGrid2->FixedCols];
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NDrawGrid2SelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect)
{
    if ( NDrawGrid2->ComponentState.Contains( csLoading ) )
        return;
    NDrawGrid2->InvalidateRow( NDrawGrid2->Row );
    NDrawGrid2->InvalidateRow( ARow );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NDrawGrid2SetEditText(TObject *Sender, int ACol, int ARow,
          const UnicodeString Value)
{
    gridData_[ARow - NDrawGrid2->FixedRows][ACol - NDrawGrid2->FixedCols] =
        Trim( Value );
}
//---------------------------------------------------------------------------

