//---------------------------------------------------------------------------

#ifndef NDrawGridH
#define NDrawGridH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Grids.hpp>

#include <memory>

//---------------------------------------------------------------------------
#if defined( NDRAWGRID_USE_NAMESPACE )
namespace Vcl {
namespace Grids {
#endif
//---------------------------------------------------------------------------

class TNDrawGridInplaceEditList : public TInplaceEditList
{
private:
    typedef TInplaceEditList inherited;

    bool mouseInControl_;
protected:
    void __fastcall PaintWindow( HDC hDC );
    DYNAMIC void __fastcall DropDown( void );
    virtual void __fastcall WndProc( Winapi::Messages::TMessage &Message );
public:
    __fastcall TNDrawGridInplaceEditList( Classes::TComponent* AOwner );
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

typedef String __fastcall ( __closure *TNDrawGridGetCellTextEvent )(
    TObject* Sender, int ACol, int ARow
);

typedef bool __fastcall ( __closure *TNDrawGridOnCellClickQueryEvent )(
    TObject* Sender, TMouseButton Button, TShiftState Shift, int ACol, int ARow
);

typedef void __fastcall ( __closure *TNDrawGridOnCellMouseEvent )(
    TObject* Sender, int ACol, int ARow, TMouseButton Button,
    TShiftState Shift, int X, int Y
);

typedef TEditStyle __fastcall ( __closure *TNDrawGridOnGetEditStyleEvent )(
    TObject* Sender, int ACol, int ARow
);

typedef  void __fastcall ( __closure *TNDrawGridOnGetTextFormatEvent )(
    TObject* Sender, int ACol, int ARow, Vcl::Graphics::TTextFormat& Format
);

typedef  void __fastcall ( __closure *TNDrawGridOnDrawCellBackgroundEvent )(
    TObject* Sender, const System::Types::TRect &ARect,
    System::Uitypes::TColor AColor, TGridDrawState AState, int ACol, int ARow
);

typedef  void __fastcall ( __closure *TNDrawGridOnDrawCellHighlight )(
    TObject* Sender, const System::Types::TRect &ARect, TGridDrawState AState,
    int ACol, int ARow
);

class PACKAGE TCustomNDrawGrid : public TCustomDrawGrid
{
private:
    typedef  TCustomDrawGrid  inherited;

    TShiftState shiftOnMouseDown_;
    TNDrawGridGetCellTextEvent onFixedCellGetText_;
    TNDrawGridOnCellClickQueryEvent onFixedCellCanClick_;
    TNotifyEvent onColWidthsChanged_;
    TNDrawGridOnCellMouseEvent onFixedCellMouseUp_;
    int dropDownRowCount_;
    TNotifyEvent onEditButtonClick_;
    TNDrawGridOnGetEditStyleEvent onGetEditStyle_;
    TNDrawGridOnGetTextFormatEvent onGetTextFormat_;
    TOnGetPickListItems onGetPickListItems_;
    TNDrawGridGetCellTextEvent onNormalCellGetText_;
    std::unique_ptr<THintWindow> gridHintWindow_;
    int gridCurrentHintCol_;
    int gridCurrentHintRow_;
    bool cellAutoHintEnabled_;
    bool mouseDown_;
    TNotifyEvent onOverlay_;
    TNDrawGridOnDrawCellBackgroundEvent onDrawCellBackground_;
    TNDrawGridOnDrawCellHighlight onDrawCellHighlight_;

    void __fastcall SetDropDownRowCount( int Value );
    void __fastcall SetOnEditButtonClick( TNotifyEvent Value );
    void __fastcall SetOnGetPickListItems( TOnGetPickListItems Value );

    //void __fastcall SetCellAutoHintEnabled( bool Val );
    void __fastcall ClearGridHintWindow();
    void __fastcall ShowAutoHintIfNeeded( int X, int Y );

    class RestoreOnMouseMovePropertyOnDestruction {
    public:
        explicit RestoreOnMouseMovePropertyOnDestruction( TCustomNDrawGrid& Obj )
          : obj_( Obj ), oldOnMouseMove_( Obj.OnMouseMove ) {}
        ~RestoreOnMouseMovePropertyOnDestruction() throw() {
            obj_.OnMouseMove = oldOnMouseMove_;
        }
    private:
        TCustomNDrawGrid& obj_;
        TMouseMoveEvent oldOnMouseMove_;

        RestoreOnMouseMovePropertyOnDestruction(
            RestoreOnMouseMovePropertyOnDestruction const &
        );
        RestoreOnMouseMovePropertyOnDestruction& operator=(
            RestoreOnMouseMovePropertyOnDestruction const &
        );
    };

    friend class RestoreOnMouseMovePropertyOnDestruction;

    void RefreshAutoHint();

protected:
    String GetCellText( int ACol, int ARow ) const;
    Vcl::Graphics::TTextFormat GetCellTextFormat( int ACol, int ARow ) const;

    DYNAMIC void __fastcall MouseDown( TMouseButton Button, TShiftState Shift,
                                       int X, int Y );
    DYNAMIC void __fastcall MouseMove( TShiftState Shift, int X, int Y );
    DYNAMIC void __fastcall MouseUp( TMouseButton Button, TShiftState Shift,
                                     int X, int Y );
    DYNAMIC bool __fastcall BeginColumnDrag( int &Origin, int &Destination,
                                             TPoint const &MousePt );
    DYNAMIC bool __fastcall EndColumnDrag( int &Origin, int &Destination,
                                           TPoint const &MousePt );
    DYNAMIC void __fastcall KeyPress( TCHAR &Key );
    DYNAMIC void __fastcall KeyDown( Word &Key, Classes::TShiftState Shift );
    DYNAMIC void __fastcall ColWidthsChanged( void );
    virtual void __fastcall DrawCell( int ACol, int ARow, const TRect &ARect,
                                      Grids::TGridDrawState AState );
    virtual void __fastcall DrawCellBackground( const System::Types::TRect &ARect,
                                                System::Uitypes::TColor AColor,
                                                TGridDrawState AState,
                                                int ACol, int ARow );
    virtual void __fastcall DrawCellHighlight( const System::Types::TRect &ARect,
                                               TGridDrawState AState,
                                               int ACol, int ARow );
    virtual TInplaceEdit* __fastcall CreateEditor( void );
    DYNAMIC TEditStyle __fastcall GetEditStyle( int ACol, int ARow );
    virtual bool __fastcall SelectCell( int ACol, int ARow );
    DYNAMIC void __fastcall TopLeftChanged( void );
    virtual void __fastcall Paint( void );
    virtual void __fastcall WndProc( Winapi::Messages::TMessage &Message );
public:
    __fastcall TCustomNDrawGrid(TComponent* Owner);
    using inherited::InvalidateCell;
    using inherited::InvalidateCol;
    using inherited::InvalidateRow;
    void __fastcall DefaultDrawCellBackground( const System::Types::TRect &ARect,
                                               System::Uitypes::TColor AColor,
                                               TGridDrawState AState,
                                               int ACol, int ARow );
    void __fastcall DefaultDrawCellHighlight( const System::Types::TRect &ARect,
                                              TGridDrawState AState,
                                              int ACol, int ARow );
protected:
    __property TNotifyEvent OnEditButtonClick = {
        read = onEditButtonClick_, write = SetOnEditButtonClick
    };
    __property TNDrawGridOnGetEditStyleEvent OnGetEditStyle = {
        read = onGetEditStyle_, write = onGetEditStyle_
    };
	__property TNDrawGridOnGetTextFormatEvent OnGetTextFormat = {
        read = onGetTextFormat_, write = onGetTextFormat_
    };
    __property TOnGetPickListItems OnGetPickListItems = {
        read = onGetPickListItems_, write = SetOnGetPickListItems
    };
    __property int DropdownRowCount = {
        read = dropDownRowCount_, write = SetDropDownRowCount, default = 8
    };
    __property TNotifyEvent OnColWidthsChanged = {
        read = onColWidthsChanged_, write = onColWidthsChanged_
    };
    __property TNDrawGridGetCellTextEvent OnFixedCellGetText = {
        read = onFixedCellGetText_, write = onFixedCellGetText_
    };
    __property TNDrawGridGetCellTextEvent OnNormalCellGetText = {
        read = onNormalCellGetText_, write = onNormalCellGetText_
    };
    __property TNDrawGridOnCellClickQueryEvent OnFixedCellCanClick = {
        read = onFixedCellCanClick_, write = onFixedCellCanClick_
    };
    __property TNDrawGridOnCellMouseEvent OnFixedCellMouseUp = {
        read = onFixedCellMouseUp_, write = onFixedCellMouseUp_
    };
    __property bool CellAutoHintEnabled = {
        read = cellAutoHintEnabled_, write = cellAutoHintEnabled_,
        default = 0
    };
    __property TNotifyEvent OnOverlay = {
       read = onOverlay_, write = onOverlay_
    };

    __property TNDrawGridOnDrawCellBackgroundEvent OnDrawCellBackground = {
        read = onDrawCellBackground_, write = onDrawCellBackground_
    };
    __property TNDrawGridOnDrawCellHighlight OnDrawCellHighlight = {
        read = onDrawCellHighlight_, write = onDrawCellHighlight_
    };
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

class PACKAGE TNDrawGrid : public TCustomNDrawGrid
{
public:
    __fastcall TNDrawGrid(TComponent* Owner);
    using TCustomNDrawGrid::SelectCell;
    using TCustomNDrawGrid::GetCellText;
    using TCustomNDrawGrid::GetCellTextFormat;
	__property InplaceEditor;
    __property VisibleColCount ;
    __property VisibleRowCount ;
__published:
    __property Align  = {default=0};
    __property Anchors  = {default=3};
    __property BevelEdges  = {default=15};
    __property BevelInner  = {index=0, default=2};
    __property BevelKind  = {default=0};
    __property BevelOuter  = {index=1, default=1};
    __property BevelWidth  = {default=1};
    __property BiDiMode ;
    __property BorderStyle  = {default=1};
    __property ColCount  = {default=5};
    __property Color  = {default=-2147483643};
    __property Constraints ;
    __property Ctl3D ;
    __property DefaultColWidth  = {default=64};
    __property DefaultDrawing  = {default=1};
    __property DefaultRowHeight  = {default=24};
    __property DragCursor  = {default=-12};
    __property DragKind  = {default=0};
    __property DragMode  = {default=0};
    __property Enabled  = {default=1};
    __property FixedColor  = {default=-2147483633};
    __property FixedCols  = {default=1};
    __property FixedRows  = {default=1};
    __property Font ;
    __property GridLineWidth  = {default=1};
    __property OnClick ;
    __property OnColumnMoved ;
    __property OnContextPopup ;
    __property OnDblClick ;
    __property OnDragDrop ;
    __property OnDragOver ;
    __property OnEndDock ;
    __property OnEndDrag ;
    __property OnEnter ;
    __property OnExit ;
    __property OnGetEditMask ;
    __property OnGetEditText ;
    __property OnKeyDown ;
    __property OnKeyPress ;
    __property OnKeyUp ;
    __property OnMouseActivate ;
    __property OnMouseDown ;
    __property OnMouseEnter ;
    __property OnMouseLeave ;
    __property OnMouseMove ;
    __property OnMouseUp ;
	__property OnMouseWheelDown ;
	__property OnMouseWheelUp ;
    __property OnResize ;
    __property OnRowMoved ;
    __property OnSelectCell ;
    __property OnSetEditText ;
    __property OnStartDock ;
    __property OnStartDrag ;
    __property OnTopLeftChanged ;
    __property Options  = {default=31};
    __property ParentBiDiMode  = {default=1};
    __property ParentColor  = {default=0};
    __property ParentCtl3D  = {default=1};
    __property ParentFont  = {default=1};
    __property ParentShowHint  = {default=1};
    __property PopupMenu ;
    __property RowCount  = {default=5};
    __property ScrollBars  = {default=3};
    __property ShowHint ;
    __property OnEditButtonClick ;
    __property OnGetEditStyle ;
    __property OnGetPickListItems ;
    __property TabOrder  = {default=-1};
    __property Visible  = {default=1};
    __property DropdownRowCount  = { default = 8 };
    __property OnColWidthsChanged ;
    __property OnFixedCellGetText ;
    __property OnNormalCellGetText ;
    __property OnFixedCellClick ;
    __property OnFixedCellCanClick ;
    __property OnFixedCellMouseUp ;
    __property CellAutoHintEnabled = { default = 0 };
    __property OnOverlay;
	__property OnGetTextFormat;
    __property OnDrawCell;
    __property OnDrawCellBackground;
    __property OnDrawCellHighlight;
};

//---------------------------------------------------------------------------
#if defined( NDRAWGRID_USE_NAMESPACE )
} /* End of namespace Grids */
} /* End of namespace Vcl */
#endif
//---------------------------------------------------------------------------

#if defined( NDRAWGRID_USE_NAMESPACE ) && !defined( NO_IMPLICIT_NAMESPACE_USE )
using namespace Vcl::Grids;
#endif

#endif

