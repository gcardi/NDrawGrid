//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <memory>

#include <Themes.hpp>

#include "NDrawGrid.h"

using std::unique_ptr;

using System::Types::TRect;
using System::Uitypes::TColor;

#pragma package(smart_init)

//---------------------------------------------------------------------------
#if defined( NDRAWGRID_USE_NAMESPACE )
namespace Vcl {
namespace Grids {
#endif
//---------------------------------------------------------------------------

__fastcall TNDrawGridInplaceEditList::TNDrawGridInplaceEditList(
                                                  Classes::TComponent* AOwner )
   : TInplaceEditList( AOwner ), mouseInControl_( false )
{
}
//---------------------------------------------------------------------------

void __fastcall TNDrawGridInplaceEditList::PaintWindow( HDC hDC )
{
    TRect R;
    int Flags;
    int W, X, Y;
    TThemedElementDetails Details;

    if ( EditStyle != esSimple ) {
        R = ButtonRect();
        Flags = 0;
        switch ( EditStyle ) {
           case esPickList:
               if ( StyleServices()->Enabled ) {
                   if ( !ActiveList )
                       Details = StyleServices()->GetElementDetails(
                                     tcDropDownButtonDisabled
                                 );
                   else if ( Pressed )
                       Details = StyleServices()->GetElementDetails(
                                     tcDropDownButtonPressed
                                  );
                   else if ( mouseInControl_ )
                       Details = StyleServices()->GetElementDetails(
                                     tcDropDownButtonHot
                                 );
                       else
                           Details = StyleServices()->GetElementDetails(
                                         tcDropDownButtonNormal
                                     );
                   StyleServices()->DrawElement( hDC, Details, R );
                }
                else {
                    if ( !ActiveList )
                        Flags = DFCS_INACTIVE;
					else if ( Pressed )
                        Flags = DFCS_FLAT | DFCS_PUSHED;
                    DrawFrameControl( hDC, &R, DFC_SCROLL, Flags | DFCS_SCROLLCOMBOBOX );
                }
                break;
           case esEllipsis:
               if ( StyleServices()->Enabled ) {
                   if ( Pressed )
                       Details = StyleServices()->GetElementDetails(
                                     tbPushButtonPressed
                                 );
                   else if ( mouseInControl_ )
                                   Details = StyleServices()->GetElementDetails(
                                                 tbPushButtonHot
                                             );
                     else
                       Details = StyleServices()->GetElementDetails(
                                     tbPushButtonNormal
                                 );
                   StyleServices()->DrawElement( hDC, Details, R );
               }
               else {
                   if ( Pressed )
                       Flags = BF_FLAT;
                         DrawEdge( hDC, &R, EDGE_RAISED, BF_RECT | BF_MIDDLE | Flags );
               }
                       X = R.Left + ( ( R.Right - R.Left ) / 2 ) - 1 + int( Pressed );
                       Y = R.Top + ( ( R.Bottom - R.Top ) / 2 ) - 1 + int( Pressed );
                       W = ButtonWidth / 8;
                       if ( !W )
                           ++W;
                       PatBlt( hDC, X, Y, W, W, BLACKNESS );
                       PatBlt( hDC, X - ( W * 2 ), Y, W, W, BLACKNESS );
                       PatBlt( hDC, X + ( W * 2 ), Y, W, W, BLACKNESS );
                       break;
           case esSimple:
               break;
        }
        ExcludeClipRect( hDC, R.Left, R.Top, R.Right, R.Bottom );
    }
    TCustomMaskEdit::PaintWindow( hDC );
}
//---------------------------------------------------------------------------

void __fastcall TNDrawGridInplaceEditList::DropDown( void )
{
    if ( TNDrawGrid* const NGrid = dynamic_cast<TNDrawGrid*>( Grid ) )
        Ctl3D = NGrid->Ctl3D;
    inherited::DropDown();
}
//---------------------------------------------------------------------------

void __fastcall TNDrawGridInplaceEditList::WndProc( Winapi::Messages::TMessage &Message )
{
    inherited::WndProc( Message );
    switch ( Message.Msg ) {
            case CM_MOUSEENTER:
                  //if ( StyleServices()->Enabled && !mouseInControl_ ) {
                  if ( !mouseInControl_ ) {
                        mouseInControl_ = true;
                        Invalidate();
                  }
                  break;
            case CM_MOUSELEAVE:
                  //if ( StyleServices()->Enabled && mouseInControl_ ) {
                  if ( mouseInControl_ ) {
                        mouseInControl_ = false;
                        Invalidate();
                  }
                  break;
    }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

__fastcall TCustomNDrawGrid::TCustomNDrawGrid(TComponent* Owner)
  : inherited(Owner)
  , onFixedCellGetText_( NULL )
  , onFixedCellCanClick_( NULL )
  , onColWidthsChanged_( NULL )
  , onFixedCellMouseUp_( NULL )
  , dropDownRowCount_( 8 )
  , onEditButtonClick_( NULL )
  , onGetEditStyle_( NULL )
  , onGetPickListItems_( NULL )
  , onNormalCellGetText_( NULL )
  , cellAutoHintEnabled_( false )
  , mouseDown_( false )
  , onOverlay_( NULL )
  , onGetTextFormat_( NULL )
  , gridCurrentHintCol_( -1 )
  , gridCurrentHintRow_( -1 )
  , onDrawCellBackground_( NULL )
  , onDrawCellHighlight_( NULL )
{
}
//---------------------------------------------------------------------------

void __fastcall TCustomNDrawGrid::MouseDown( TMouseButton Button,
                                             TShiftState Shift, int X, int Y )
{
    mouseDown_ = true;
    shiftOnMouseDown_ = Shift;
    inherited::MouseDown( Button, Shift, X, Y );
    if ( FHotTrackCell.Pressed ) {
        TGridCoord const GridCoord( MouseCoord( X,  Y ) );

        if ( ( Options.Contains( goFixedColClick ) && GridCoord.X < FixedRows ) ||
             ( Options.Contains( goFixedRowClick ) && GridCoord.Y < FixedCols ) )
        {
            if ( onFixedCellCanClick_ ) {
                bool CanClick = false;
                onFixedCellCanClick_( this, Button, Shift, GridCoord.X, GridCoord.Y, CanClick );
                if ( !CanClick ) {
                    return;
                }
            }
        }
        FHotTrackCell.Coord.X = -1;
        FHotTrackCell.Coord.Y = -1;
        FHotTrackCell.Pressed = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TCustomNDrawGrid::MouseMove( TShiftState Shift, int X, int Y )
{
    inherited::MouseMove( Shift, X, Y );
    if ( !mouseDown_ ) {
        ShowAutoHintIfNeeded( X, Y );
    }
}
//---------------------------------------------------------------------------

template<typename T>
class AssignOnDestruction {
public:
	explicit AssignOnDestruction( T& Ref, T const & Val ) : ref_( Ref ), val_( Val ) {}
	~AssignOnDestruction() /*throw()*/ { ref_ = val_; }
private:
	AssignOnDestruction( AssignOnDestruction const & );
	AssignOnDestruction& operator=( AssignOnDestruction const & );

	T& ref_;
	T val_;
};

void __fastcall TCustomNDrawGrid::MouseUp( TMouseButton Button, TShiftState Shift,
                                           int X, int Y )
{
    AssignOnDestruction<bool> const ClearFlagOnExit( mouseDown_, false );
    {
        RestoreOnMouseMovePropertyOnDestruction MouseMoveEventRestore( *this );
        OnMouseMove = 0;
        inherited::MouseUp( Button, Shift, X, Y );
    }
    TGridCoord const GridCoord( MouseCoord( X,  Y ) );
    if ( ( GridCoord.X >= 0 && GridCoord.X < FixedCols ) || ( GridCoord.Y >= 0 && GridCoord.Y < FixedRows ) ) {
        if ( onFixedCellMouseUp_ ) {
            onFixedCellMouseUp_( this, GridCoord.X, GridCoord.Y, Button, Shift, X, Y );
        }
    }
}
//---------------------------------------------------------------------------

UnicodeString TCustomNDrawGrid::GetCellText( int ACol, int ARow ) const
{
    UnicodeString Result;
    if ( ( ACol >= 0 && ACol < FixedCols ) || ( ARow >= 0 && ARow < FixedRows ) ) {
        if ( onFixedCellGetText_ ) {
            onFixedCellGetText_(
                const_cast<TCustomNDrawGrid*>( this ), ACol, ARow, Result
            );
        }
    }
    else if ( onNormalCellGetText_ ) {
        onNormalCellGetText_(
            const_cast<TCustomNDrawGrid*>( this ), ACol, ARow, Result
        );
    }
    return Result;
}
//---------------------------------------------------------------------------

void __fastcall TCustomNDrawGrid::DrawCell( int ACol, int ARow, const TRect &Rect,
                                            Grids::TGridDrawState AState )
{
    TRect ARect( Rect );

    if ( DefaultDrawing ) {
        String LText = GetCellText( ACol, ARow );
        if ( StyleServices()->Enabled ) {
            InflateRect( ARect, -8, -2 );
        }
        else {
            InflateRect( ARect, -2, -2 );
        }
        Canvas->TextRect( ARect, LText, GetCellTextFormat( ACol, ARow ) );
    }
    inherited::DrawCell( ACol, ARow, ARect, AState );
}
//---------------------------------------------------------------------------

void __fastcall TCustomNDrawGrid::DrawCellBackground(
                                            const System::Types::TRect &ARect,
                                            System::Uitypes::TColor AColor,
                                            TGridDrawState AState,
                                            int ACol, int ARow )
{
    if ( onDrawCellBackground_ ) {
        onDrawCellBackground_( this, ARect, AColor, AState, ACol, ARow );
    }
    else {
        DefaultDrawCellBackground( ARect, AColor, AState, ACol, ARow );
    }
}
//---------------------------------------------------------------------------

void __fastcall TCustomNDrawGrid::DrawCellHighlight(
                                             const System::Types::TRect &ARect,
                                             TGridDrawState AState,
                                             int ACol, int ARow )
{
    if ( onDrawCellHighlight_ ) {
        onDrawCellHighlight_( this, ARect, AState, ACol, ARow );
    }
    else {
        DefaultDrawCellHighlight( ARect, AState, ACol, ARow );
    }
}
//---------------------------------------------------------------------------

void __fastcall TCustomNDrawGrid::DefaultDrawCellBackground(
                                             const System::Types::TRect &ARect,
                                             System::Uitypes::TColor AColor,
                                             TGridDrawState AState,
                                             int ACol, int ARow )
{
    inherited::DrawCellBackground( ARect, AColor, AState, ACol, ARow );
}
//---------------------------------------------------------------------------

void __fastcall TCustomNDrawGrid::DefaultDrawCellHighlight(
                                            const System::Types::TRect &ARect,
                                            TGridDrawState AState,
                                            int ACol, int ARow )
{
    inherited::DrawCellHighlight( ARect, AState, ACol, ARow );
}
//---------------------------------------------------------------------------

bool __fastcall TCustomNDrawGrid::BeginColumnDrag( int &Origin, int &Destination,
                                                   TPoint const & MousePt )
{
    return
        inherited::BeginColumnDrag( Origin, Destination, MousePt ) &&
        shiftOnMouseDown_.Contains( ssShift );
}
//---------------------------------------------------------------------------

bool __fastcall TCustomNDrawGrid::EndColumnDrag( int &Origin, int &Destination,
                                                 TPoint const& MousePt )
{
    return inherited::EndColumnDrag( Origin, Destination, MousePt );
}
//---------------------------------------------------------------------------

void __fastcall TCustomNDrawGrid::KeyPress( TCHAR &Key )
{
    inherited::KeyPress( Key );
    ClearGridHintWindow();
}
//---------------------------------------------------------------------------

void __fastcall TCustomNDrawGrid::KeyDown( Word &Key, Classes::TShiftState Shift )
{
    inherited::KeyDown( Key, Shift );

    switch ( Key ) {
        case VK_SHIFT:
        case VK_CONTROL:
        case VK_MENU:
            break;
        default:
            ClearGridHintWindow();
            break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TCustomNDrawGrid::ColWidthsChanged( void )
{
    inherited::ColWidthsChanged();
    if ( onColWidthsChanged_ ) {
        onColWidthsChanged_( this );
    }
}
//---------------------------------------------------------------------------

TInplaceEdit* __fastcall TCustomNDrawGrid::CreateEditor( void )
{
    unique_ptr<TNDrawGridInplaceEditList> Editor(
        new TNDrawGridInplaceEditList( this )
    );
    Editor->DropDownRows = dropDownRowCount_;
    Editor->OnGetPickListitems = onGetPickListItems_;
    Editor->OnEditButtonClick = onEditButtonClick_;
    return Editor.release();
}
//---------------------------------------------------------------------------

TEditStyle __fastcall TCustomNDrawGrid::GetEditStyle( int ACol, int ARow )
{
    TEditStyle Result = esSimple;
    if ( onGetEditStyle_ ) {
        onGetEditStyle_( this, ACol, ARow, Result );
    }
    return Result;
}
//---------------------------------------------------------------------------

void __fastcall TCustomNDrawGrid::SetDropDownRowCount( int Value )
{
    dropDownRowCount_ = Value;
    if ( TInplaceEditList* const Editor = dynamic_cast<TInplaceEditList*>( InplaceEditor ) ) {
        Editor->DropDownRows = Value;
    }
}
//---------------------------------------------------------------------------

void __fastcall TCustomNDrawGrid::SetOnEditButtonClick( TNotifyEvent Value )
{
    onEditButtonClick_ = Value;
    if ( TInplaceEditList* const Editor = dynamic_cast<TInplaceEditList*>( InplaceEditor ) ) {
       Editor->OnEditButtonClick = Value;
    }
}
//---------------------------------------------------------------------------

void __fastcall TCustomNDrawGrid::SetOnGetPickListItems( TOnGetPickListItems Value )
{
    onGetPickListItems_ = Value;
    if ( TInplaceEditList* const Editor = dynamic_cast<TInplaceEditList*>( InplaceEditor ) ) {
       Editor->OnGetPickListitems = Value;
    }
}
//---------------------------------------------------------------------------

void __fastcall TCustomNDrawGrid::WndProc( Winapi::Messages::TMessage &Message )
{
    inherited::WndProc( Message );
    switch ( Message.Msg ) {
        case CM_MOUSELEAVE:
            ClearGridHintWindow();
            break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TCustomNDrawGrid::ClearGridHintWindow()
{
    if ( gridHintWindow_ ) {
        gridHintWindow_->Hide();
        gridHintWindow_.reset();
        gridCurrentHintCol_ = -1;
        gridCurrentHintRow_ = -1;
    }
}
//---------------------------------------------------------------------------

void TCustomNDrawGrid::RefreshAutoHint()
{
    const TPoint CursorPos = ScreenToClient( Mouse->CursorPos );
    const TGridCoord GridCoord( MouseCoord( CursorPos.x, CursorPos.y ) );
    if ( gridCurrentHintCol_ != GridCoord.X || gridCurrentHintRow_ != GridCoord.Y ) {
        ClearGridHintWindow();
    }
    ShowAutoHintIfNeeded( CursorPos.x, CursorPos.y );
}
//---------------------------------------------------------------------------

bool __fastcall TCustomNDrawGrid::SelectCell( int ACol, int ARow )
{
/*
    const TPoint CursorPos = ScreenToClient( Mouse->CursorPos );
    const TGridCoord GridCoord( MouseCoord( CursorPos.x, CursorPos.y ) );
    if ( gridCurrentHintCol_ != GridCoord.X || gridCurrentHintRow_ != GridCoord.Y ) {
        ClearGridHintWindow();
    }
    ShowAutoHintIfNeeded( CursorPos.x, CursorPos.y );
*/
    RefreshAutoHint();
    return inherited::SelectCell( ACol, ARow );
}
//---------------------------------------------------------------------------

void __fastcall TCustomNDrawGrid::TopLeftChanged( void )
{
/*
    const TPoint CursorPos = ScreenToClient( Mouse->CursorPos );
    const TGridCoord GridCoord( MouseCoord( CursorPos.x, CursorPos.y ) );
    if ( gridCurrentHintCol_ != GridCoord.X || gridCurrentHintRow_ != GridCoord.Y ) {
        ClearGridHintWindow();
    }
    ShowAutoHintIfNeeded( CursorPos.x, CursorPos.y );
*/
    RefreshAutoHint();
    inherited::TopLeftChanged();
}
//---------------------------------------------------------------------------

Vcl::Graphics::TTextFormat TCustomNDrawGrid::GetCellTextFormat( int ACol, int ARow ) const
{
    Vcl::Graphics::TTextFormat TextFmt =
       Vcl::Graphics::TTextFormat() << tfVerticalCenter << tfSingleLine << tfLeft;
    if ( onGetTextFormat_ ) {
        onGetTextFormat_(
            const_cast<TCustomNDrawGrid*>( this ), ACol, ARow, TextFmt
        );
    }
    TextFmt = TextFmt << tfSingleLine;
    return TextFmt;
}
//---------------------------------------------------------------------------

void __fastcall TCustomNDrawGrid::ShowAutoHintIfNeeded( int X, int Y )
{
    if ( cellAutoHintEnabled_ && MouseInClient && PtInRect( ClientRect, TPoint( X, Y ) ) ) {

        bool const HasFocus = FindControl( GetForegroundWindow() );

        TGridCoord const GridCoord( MouseCoord( X,  Y ) );
        if ( HasFocus && GridCoord.Y >= FixedRows && GridCoord.X >= FixedCols ) {
            if ( gridCurrentHintCol_ != GridCoord.X || gridCurrentHintRow_ != GridCoord.Y  ) {
                ClearGridHintWindow();
            }

            if ( onNormalCellGetText_ ) {
                UnicodeString DisplayText;
                onNormalCellGetText_( this, GridCoord.X, GridCoord.Y, DisplayText );
                Types::TRect CRect = CellRect( GridCoord.X, GridCoord.Y );

                const Vcl::Graphics::TTextFormat CellFmt = GetCellTextFormat( GridCoord.X, GridCoord.Y );
                const int TextWidth = Canvas->TextWidth( DisplayText ) + 4;

                if ( TextWidth > CRect.Width() - ( StyleServices()->Enabled ? 12 : 0 ) ) {
                    if ( !gridHintWindow_.get() ) {
                        gridHintWindow_.reset( new THintWindow( (TComponent*)0 ) );
                        gridHintWindow_->Color = Application->HintColor;
                        gridHintWindow_->Canvas->Font->Assign( Font );
                        TPoint const CellScreenPos =
                            ClientToScreen( Types::TPoint( CRect.Left, CRect.Top ) );
                        TRect HintRect =
                            gridHintWindow_->CalcHintRect( Screen->Width, DisplayText, 0 );

                        int XOfs;

                        if ( CellFmt.Contains( tfCenter ) ) {
                            XOfs =
                                (  ColWidths[GridCoord.X]
                                   - HintRect.Width()
                                   - ( StyleServices()->Enabled ?
                                        0 : ( ColWidths[GridCoord.X] & 1 ? 0 : 2 )
                                     )
                                ) / 2;
                        }
                        else if ( CellFmt.Contains( tfRight ) ) {
                            XOfs =
                              ( ColWidths[GridCoord.X] - HintRect.Width() )
                              + ( StyleServices()->Enabled ? -5 : 1 );
                        }
                        else {
                            XOfs = StyleServices()->Enabled ? 5 : -1;
                        }

                        Types::OffsetRect(
                            HintRect,
                            CellScreenPos.x + XOfs,
                            CellScreenPos.y
                              + ( CRect.Height() - HintRect.Height() ) / 2 - 2
                        );
                        gridHintWindow_->ActivateHint( HintRect, DisplayText );
                        gridCurrentHintCol_ = GridCoord.X;
                                    gridCurrentHintRow_ = GridCoord.Y;
                    }
                }
            }
        }
        else {
            ClearGridHintWindow();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TCustomNDrawGrid::Paint( void )
{
    inherited::Paint();
    if ( onOverlay_ ) {
        onOverlay_( this );
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

__fastcall TNDrawGrid::TNDrawGrid(TComponent* Owner)
    : TCustomNDrawGrid(Owner)
{
}
//---------------------------------------------------------------------------
#if defined( NDRAWGRID_USE_NAMESPACE )
} /* End of namespace Grids */
} /* End of namespace Vcl */
#endif
//---------------------------------------------------------------------------

