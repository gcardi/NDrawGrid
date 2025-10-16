//---------------------------------------------------------------------------

#ifndef NDrawGridH
#define NDrawGridH
//---------------------------------------------------------------------------
#pragma option push
#if defined(__BORLANDC__) && !defined(__clang__)
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member
#endif
#pragma pack(push,8)
//---------------------------------------------------------------------------

#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Grids.hpp>

#include <memory>

//---------------------------------------------------------------------------
namespace Vcl {
namespace Grids {
//---------------------------------------------------------------------------

class PACKAGE TNDrawGridInplaceEditList : public TInplaceEditList
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

typedef void __fastcall ( __closure *TNDrawGridGetCellTextEvent )(
    TObject* Sender, int ACol, int ARow, UnicodeString& Result
);

typedef void __fastcall ( __closure *TNDrawGridOnCellClickQueryEvent )(
	System::TObject* Sender, System::Uitypes::TMouseButton Button,
	System::Classes::TShiftState Shift,
	System::LongInt ACol, System::LongInt ARow,
	bool& Result
);

typedef void __fastcall ( __closure *TNDrawGridOnCellMouseEvent )(
	System::TObject* Sender, System::LongInt ACol, System::LongInt ARow,
	System::Uitypes::TMouseButton Button,
	System::Classes::TShiftState Shift, int X, int Y
);

typedef void __fastcall ( __closure *TNDrawGridOnGetEditStyleEvent )(
	System::TObject* Sender, System::LongInt ACol, System::LongInt ARow,
	TEditStyle& Result
);

typedef  void __fastcall ( __closure *TNDrawGridOnGetTextFormatEvent )(
	System::TObject* Sender, System::LongInt ACol, System::LongInt ARow,
	Vcl::Graphics::TTextFormat& Format
);

typedef  void __fastcall ( __closure *TNDrawGridOnDrawCellBackgroundEvent )(
    TObject* Sender, const System::Types::TRect &ARect,
    System::Uitypes::TColor AColor, TGridDrawState AState, int ACol, int ARow
);

typedef  void __fastcall ( __closure *TNDrawGridOnDrawCellHighlight )(
    System::TObject* Sender, const System::Types::TRect &ARect,
    Grids::TGridDrawState AState, System::LongInt ACol, System::LongInt ARow
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
    System::LongInt gridCurrentHintCol_;
    System::LongInt gridCurrentHintRow_;
    bool cellAutoHintEnabled_;
    bool mouseDown_;
    System::Classes::TNotifyEvent onOverlay_;
    TNDrawGridOnDrawCellBackgroundEvent onDrawCellBackground_;
    TNDrawGridOnDrawCellHighlight onDrawCellHighlight_;

    void __fastcall SetDropDownRowCount( int Value );
    void __fastcall SetOnEditButtonClick( TNotifyEvent Value );
    void __fastcall SetOnGetPickListItems( TOnGetPickListItems Value );

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
        Vcl::Controls::TMouseMoveEvent oldOnMouseMove_;

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
    UnicodeString GetCellText( System::LongInt ACol, System::LongInt ARow ) const;
    Vcl::Graphics::TTextFormat GetCellTextFormat( System::LongInt ACol, System::LongInt ARow ) const;

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
    virtual void __fastcall DrawCell( System::LongInt ACol, System::LongInt ARow,
                                      const System::Types::TRect &ARect,
                                      Grids::TGridDrawState AState );
    virtual void __fastcall DrawCellBackground( const System::Types::TRect &ARect,
                                                System::Uitypes::TColor AColor,
                                                TGridDrawState AState,
                                                System::LongInt ACol,
                                                System::LongInt ARow );
    virtual void __fastcall DrawCellHighlight( const System::Types::TRect &ARect,
                                               TGridDrawState AState,
                                               System::LongInt ACol,
                                               System::LongInt ARow );
    virtual TInplaceEdit* __fastcall CreateEditor( void );
    DYNAMIC TEditStyle __fastcall GetEditStyle( System::LongInt ACol,
                                                System::LongInt ARow );
    virtual bool __fastcall SelectCell( System::LongInt ACol, System::LongInt ARow );
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
                                               System::LongInt ACol, System::LongInt ARow );
    void __fastcall DefaultDrawCellHighlight( const System::Types::TRect &ARect,
                                              TGridDrawState AState,
                                              System::LongInt ACol, System::LongInt ARow );
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
        read = cellAutoHintEnabled_, write = cellAutoHintEnabled_
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
__published:
    __property Align = {default=0};
    __property Anchors = {default=3};
    __property BevelEdges = {default=15};
    __property BevelInner = {index=0, default=2};
    __property BevelKind = {default=0};
    __property BevelOuter = {index=1, default=1};
    __property BevelWidth = {default=1};
    __property BiDiMode;
    __property BorderStyle = {default=1};
    __property CellAutoHintEnabled = {default = 0};
    __property ColCount = {default=5};
    __property Color = {default=-16777211};
    __property Constraints;
    __property Ctl3D;
    __property DefaultColAlignment = {default=0};
    __property DefaultColWidth = {default=64};
    __property DefaultDrawing = {default=1};
    __property DefaultRowHeight = {default=24};
    __property DoubleBuffered;
    __property DragCursor = {default=-12};
    __property DragKind = {default=0};
    __property DragMode = {default=0};
    __property DrawingStyle = {default=1};
    __property DropdownRowCount = { default = 8 };
    __property Enabled = {default=1};
    __property FixedColor = {default=-16777201};
    __property FixedCols = {default=1};
    __property FixedRows = {default=1};
    __property Font;
    __property GradientEndColor;
    __property GradientStartColor = {default=16777215};
    __property GridLineWidth = {default=1};
    __property OnClick;
    __property OnColWidthsChanged;
    __property OnColumnMoved;
    __property OnContextPopup;
    __property OnDblClick;
    __property OnDragDrop;
    __property OnDragOver;
    __property OnDrawCell;
    __property OnDrawCellBackground;
    __property OnDrawCellHighlight;
    __property OnEditButtonClick;
    __property OnEndDock;
    __property OnEndDrag;
    __property OnEnter;
    __property OnExit;
    __property OnFixedCellCanClick;
    __property OnFixedCellClick;
    __property OnFixedCellGetText;
    __property OnFixedCellMouseUp;
    __property OnGesture;
    __property OnGetEditMask;
    __property OnGetEditStyle;
    __property OnGetEditText;
    __property OnGetPickListItems;
    __property OnGetTextFormat;
    __property OnKeyDown;
    __property OnKeyPress;
    __property OnKeyUp;
    __property OnMouseActivate;
    __property OnMouseDown;
    __property OnMouseEnter;
    __property OnMouseLeave;
    __property OnMouseMove;
    __property OnMouseUp;
    __property OnMouseWheelDown;
    __property OnMouseWheelUp;
    __property OnNormalCellGetText;
    __property OnOverlay;
    __property OnResize;
    __property OnRowMoved;
    __property OnSelectCell;
    __property OnSetEditText;
    __property OnStartDock;
    __property OnStartDrag;
    __property OnTopLeftChanged;
    __property Options = {default=524319};
    __property ParentBiDiMode = {default=1};
    __property ParentColor = {default=0};
    __property ParentCtl3D = {default=1};
    __property ParentDoubleBuffered = {default=1};
    __property ParentFont = {default=1};
    __property ParentShowHint = {default=1};
    __property PopupMenu;
    __property RowCount = {default=5};
    __property ScrollBars = {default=3};
    __property ShowHint;
    __property StyleElements = {default=7};
    __property StyleName = {default=0};
    __property TabOrder = {default=-1};
    __property Touch;
    __property Visible = {default=1};
    __property VisibleColCount;
    __property VisibleRowCount;
};

//---------------------------------------------------------------------------
} /* End of namespace Grids */
} /* End of namespace Vcl */
//---------------------------------------------------------------------------

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCL_GRIDS)
using namespace Vcl::Grids;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCL)
using namespace Vcl;
#endif

#pragma pack(pop)
#pragma option pop

#endif

