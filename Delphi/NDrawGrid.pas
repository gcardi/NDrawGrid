{---------------------------------------------------------------------------}
{                                                                           }
{  NDrawGrid - Enhanced TDrawGrid component                                 }
{                                                                           }
{  Delphi translation from the original C++ Builder component               }
{                                                                           }
{---------------------------------------------------------------------------}

unit NDrawGrid;

interface

uses
  System.SysUtils, System.Classes, System.Types, System.UITypes, System.Math,
  Winapi.Windows, Winapi.Messages,
  Vcl.Controls, Vcl.Grids, Vcl.Graphics, Vcl.Forms, Vcl.Themes;

type
  TNDrawGridGetCellTextEvent = procedure(Sender: TObject;
    ACol, ARow: Longint; var Result: string) of object;

  TNDrawGridOnCellClickQueryEvent = procedure(Sender: TObject;
    Button: TMouseButton; Shift: TShiftState; ACol, ARow: Longint;
    var Result: Boolean) of object;

  TNDrawGridOnCellMouseEvent = procedure(Sender: TObject;
    ACol, ARow: Longint; Button: TMouseButton; Shift: TShiftState;
    X, Y: Integer) of object;

  TNDrawGridOnGetEditStyleEvent = procedure(Sender: TObject;
    ACol, ARow: Longint; var Result: TEditStyle) of object;

  TNDrawGridOnGetTextFormatEvent = procedure(Sender: TObject;
    ACol, ARow: Longint; var Format: TTextFormat) of object;

  TNDrawGridOnDrawCellBackgroundEvent = procedure(Sender: TObject;
    const ARect: TRect; AColor: TColor; AState: TGridDrawState;
    ACol, ARow: Longint) of object;

  TNDrawGridOnDrawCellHighlightEvent = procedure(Sender: TObject;
    const ARect: TRect; AState: TGridDrawState;
    ACol, ARow: Longint) of object;

  TCustomNDrawGrid = class;

  TNDrawGridInplaceEditList = class(TInplaceEditList)
  private
    FMouseInControl: Boolean;
  protected
    procedure PaintWindow(DC: HDC); override;
    procedure DropDown; override;
    procedure WndProc(var Message: TMessage); override;
  public
    constructor Create(AOwner: TComponent); override;
  end;

  TCustomNDrawGrid = class(TCustomDrawGrid)
  private
    FShiftOnMouseDown: TShiftState;
    FOnFixedCellGetText: TNDrawGridGetCellTextEvent;
    FOnFixedCellCanClick: TNDrawGridOnCellClickQueryEvent;
    FOnColWidthsChanged: TNotifyEvent;
    FOnFixedCellMouseUp: TNDrawGridOnCellMouseEvent;
    FDropDownRowCount: Integer;
    FOnEditButtonClick: TNotifyEvent;
    FOnGetEditStyle: TNDrawGridOnGetEditStyleEvent;
    FOnGetTextFormat: TNDrawGridOnGetTextFormatEvent;
    FOnGetPickListItems: TOnGetPickListItems;
    FOnNormalCellGetText: TNDrawGridGetCellTextEvent;
    FGridHintWindow: THintWindow;
    FGridCurrentHintCol: Longint;
    FGridCurrentHintRow: Longint;
    FCellAutoHintEnabled: Boolean;
    FMouseDown: Boolean;
    FOnOverlay: TNotifyEvent;
    FOnDrawCellBackground: TNDrawGridOnDrawCellBackgroundEvent;
    FOnDrawCellHighlight: TNDrawGridOnDrawCellHighlightEvent;
    procedure SetDropDownRowCount(Value: Integer);
    procedure SetOnEditButtonClick(Value: TNotifyEvent);
    procedure SetOnGetPickListItems(Value: TOnGetPickListItems);
    procedure ClearGridHintWindow;
    procedure ShowAutoHintIfNeeded(X, Y: Integer);
    procedure RefreshAutoHint;
  protected
    function GetCellText(ACol, ARow: Longint): string;
    function GetCellTextFormat(ACol, ARow: Longint): TTextFormat;
    procedure MouseDown(Button: TMouseButton; Shift: TShiftState;
      X, Y: Integer); override;
    procedure MouseMove(Shift: TShiftState; X, Y: Integer); override;
    procedure MouseUp(Button: TMouseButton; Shift: TShiftState;
      X, Y: Integer); override;
    function BeginColumnDrag(var Origin, Destination: Integer;
      const MousePt: TPoint): Boolean; override;
    function EndColumnDrag(var Origin, Destination: Integer;
      const MousePt: TPoint): Boolean; override;
    procedure KeyPress(var Key: Char); override;
    procedure KeyDown(var Key: Word; Shift: TShiftState); override;
    procedure ColWidthsChanged; override;
    procedure DrawCell(ACol, ARow: Longint; ARect: TRect;
      AState: TGridDrawState); override;
    procedure DrawCellBackground(const ARect: TRect; AColor: TColor;
      AState: TGridDrawState; ACol, ARow: Longint); override;
    procedure DrawCellHighlight(const ARect: TRect;
      AState: TGridDrawState; ACol, ARow: Longint); override;
    function CreateEditor: TInplaceEdit; override;
    function GetEditStyle(ACol, ARow: Longint): TEditStyle; override;
    function SelectCell(ACol, ARow: Longint): Boolean; override;
    procedure TopLeftChanged; override;
    procedure Paint; override;
    procedure WndProc(var Message: TMessage); override;
    property OnEditButtonClick: TNotifyEvent
      read FOnEditButtonClick write SetOnEditButtonClick;
    property OnGetEditStyle: TNDrawGridOnGetEditStyleEvent
      read FOnGetEditStyle write FOnGetEditStyle;
    property OnGetTextFormat: TNDrawGridOnGetTextFormatEvent
      read FOnGetTextFormat write FOnGetTextFormat;
    property OnGetPickListItems: TOnGetPickListItems
      read FOnGetPickListItems write SetOnGetPickListItems;
    property DropdownRowCount: Integer
      read FDropDownRowCount write SetDropDownRowCount default 8;
    property OnColWidthsChanged: TNotifyEvent
      read FOnColWidthsChanged write FOnColWidthsChanged;
    property OnFixedCellGetText: TNDrawGridGetCellTextEvent
      read FOnFixedCellGetText write FOnFixedCellGetText;
    property OnNormalCellGetText: TNDrawGridGetCellTextEvent
      read FOnNormalCellGetText write FOnNormalCellGetText;
    property OnFixedCellCanClick: TNDrawGridOnCellClickQueryEvent
      read FOnFixedCellCanClick write FOnFixedCellCanClick;
    property OnFixedCellMouseUp: TNDrawGridOnCellMouseEvent
      read FOnFixedCellMouseUp write FOnFixedCellMouseUp;
    property CellAutoHintEnabled: Boolean
      read FCellAutoHintEnabled write FCellAutoHintEnabled;
    property OnOverlay: TNotifyEvent
      read FOnOverlay write FOnOverlay;
    property OnDrawCellBackground: TNDrawGridOnDrawCellBackgroundEvent
      read FOnDrawCellBackground write FOnDrawCellBackground;
    property OnDrawCellHighlight: TNDrawGridOnDrawCellHighlightEvent
      read FOnDrawCellHighlight write FOnDrawCellHighlight;
  public
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
    procedure DefaultDrawCellBackground(const ARect: TRect; AColor: TColor;
      AState: TGridDrawState; ACol, ARow: Longint);
    procedure DefaultDrawCellHighlight(const ARect: TRect;
      AState: TGridDrawState; ACol, ARow: Longint);
  end;

  TNDrawGrid = class(TCustomNDrawGrid)
  public
    constructor Create(AOwner: TComponent); override;
    function SelectCell(ACol, ARow: Longint): Boolean; override;
    function GetCellText(ACol, ARow: Longint): string;
    function GetCellTextFormat(ACol, ARow: Longint): TTextFormat;
    property InplaceEditor;
  published
    property Align;
    property Anchors;
    property BevelEdges;
    property BevelInner;
    property BevelKind;
    property BevelOuter;
    property BevelWidth;
    property BiDiMode;
    property BorderStyle;
    property CellAutoHintEnabled default False;
    property ColCount;
    property Color;
    property Constraints;
    property Ctl3D;
    property DefaultColAlignment;
    property DefaultColWidth;
    property DefaultDrawing;
    property DefaultRowHeight;
    property DoubleBuffered;
    property DragCursor;
    property DragKind;
    property DragMode;
    property DrawingStyle;
    property DropdownRowCount default 8;
    property Enabled;
    property FixedColor;
    property FixedCols;
    property FixedRows;
    property Font;
    property GradientEndColor;
    property GradientStartColor;
    property GridLineWidth;
    property OnClick;
    property OnColWidthsChanged;
    property OnColumnMoved;
    property OnContextPopup;
    property OnDblClick;
    property OnDragDrop;
    property OnDragOver;
    property OnDrawCell;
    property OnDrawCellBackground;
    property OnDrawCellHighlight;
    property OnEditButtonClick;
    property OnEndDock;
    property OnEndDrag;
    property OnEnter;
    property OnExit;
    property OnFixedCellCanClick;
    property OnFixedCellClick;
    property OnFixedCellGetText;
    property OnFixedCellMouseUp;
    property OnGesture;
    property OnGetEditMask;
    property OnGetEditStyle;
    property OnGetEditText;
    property OnGetPickListItems;
    property OnGetTextFormat;
    property OnKeyDown;
    property OnKeyPress;
    property OnKeyUp;
    property OnMouseActivate;
    property OnMouseDown;
    property OnMouseEnter;
    property OnMouseLeave;
    property OnMouseMove;
    property OnMouseUp;
    property OnMouseWheelDown;
    property OnMouseWheelUp;
    property OnNormalCellGetText;
    property OnOverlay;
    property OnResize;
    property OnRowMoved;
    property OnSelectCell;
    property OnSetEditText;
    property OnStartDock;
    property OnStartDrag;
    property OnTopLeftChanged;
    property Options;
    property ParentBiDiMode;
    property ParentColor;
    property ParentCtl3D;
    property ParentDoubleBuffered;
    property ParentFont;
    property ParentShowHint;
    property PopupMenu;
    property RowCount;
    property ScrollBars;
    property ShowHint;
    property StyleElements;
    property StyleName;
    property TabOrder;
    property Touch;
    property Visible;
    property VisibleColCount;
    property VisibleRowCount;
  end;

implementation

{ TNDrawGridInplaceEditList }

constructor TNDrawGridInplaceEditList.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FMouseInControl := False;
end;

procedure TNDrawGridInplaceEditList.PaintWindow(DC: HDC);
var
  R: TRect;
  Flags: Cardinal;
  W, X, Y: Integer;
  Details: TThemedElementDetails;
begin
  if EditStyle <> esSimple then
  begin
    R := ButtonRect;
    Flags := 0;
    case EditStyle of
      esPickList:
        begin
          if StyleServices.Enabled then
          begin
            if not Assigned(ActiveList) then
              Details := StyleServices.GetElementDetails(tcDropDownButtonDisabled)
            else if Pressed then
              Details := StyleServices.GetElementDetails(tcDropDownButtonPressed)
            else if FMouseInControl then
              Details := StyleServices.GetElementDetails(tcDropDownButtonHot)
            else
              Details := StyleServices.GetElementDetails(tcDropDownButtonNormal);
            StyleServices.DrawElement(DC, Details, R);
          end
          else
          begin
            if not Assigned(ActiveList) then
              Flags := DFCS_INACTIVE
            else if Pressed then
              Flags := DFCS_FLAT or DFCS_PUSHED;
            DrawFrameControl(DC, R, DFC_SCROLL, Flags or DFCS_SCROLLCOMBOBOX);
          end;
        end;
      esEllipsis:
        begin
          if StyleServices.Enabled then
          begin
            if Pressed then
              Details := StyleServices.GetElementDetails(tbPushButtonPressed)
            else if FMouseInControl then
              Details := StyleServices.GetElementDetails(tbPushButtonHot)
            else
              Details := StyleServices.GetElementDetails(tbPushButtonNormal);
            StyleServices.DrawElement(DC, Details, R);
          end
          else
          begin
            if Pressed then
              Flags := BF_FLAT;
            DrawEdge(DC, R, EDGE_RAISED, BF_RECT or BF_MIDDLE or Flags);
          end;
          X := R.Left + ((R.Right - R.Left) div 2) - 1 + Ord(Pressed);
          Y := R.Top + ((R.Bottom - R.Top) div 2) - 1 + Ord(Pressed);
          W := ButtonWidth div 8;
          if W = 0 then
            Inc(W);
          PatBlt(DC, X, Y, W, W, BLACKNESS);
          PatBlt(DC, X - (W * 2), Y, W, W, BLACKNESS);
          PatBlt(DC, X + (W * 2), Y, W, W, BLACKNESS);
        end;
    end;
    { Exclude the button area so the inherited PaintWindow (which may
      attempt to paint its own button) is effectively clipped to the
      text area only. }
    ExcludeClipRect(DC, R.Left, R.Top, R.Right, R.Bottom);
  end;
  inherited PaintWindow(DC);
end;

procedure TNDrawGridInplaceEditList.DropDown;
begin
  if Grid is TNDrawGrid then
    Ctl3D := TNDrawGrid(Grid).Ctl3D;
  inherited DropDown;
end;

procedure TNDrawGridInplaceEditList.WndProc(var Message: TMessage);
begin
  inherited WndProc(Message);
  case Message.Msg of
    CM_MOUSEENTER:
      if not FMouseInControl then
      begin
        FMouseInControl := True;
        Invalidate;
      end;
    CM_MOUSELEAVE:
      if FMouseInControl then
      begin
        FMouseInControl := False;
        Invalidate;
      end;
  end;
end;

{ TCustomNDrawGrid }

constructor TCustomNDrawGrid.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FOnFixedCellGetText := nil;
  FOnFixedCellCanClick := nil;
  FOnColWidthsChanged := nil;
  FOnFixedCellMouseUp := nil;
  FDropDownRowCount := 8;
  FOnEditButtonClick := nil;
  FOnGetEditStyle := nil;
  FOnGetTextFormat := nil;
  FOnGetPickListItems := nil;
  FOnNormalCellGetText := nil;
  FGridHintWindow := nil;
  FGridCurrentHintCol := -1;
  FGridCurrentHintRow := -1;
  FCellAutoHintEnabled := False;
  FMouseDown := False;
  FOnOverlay := nil;
  FOnDrawCellBackground := nil;
  FOnDrawCellHighlight := nil;
end;

destructor TCustomNDrawGrid.Destroy;
begin
  FreeAndNil(FGridHintWindow);
  inherited Destroy;
end;

procedure TCustomNDrawGrid.MouseDown(Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var
  GridCoord: TGridCoord;
  CanClick: Boolean;
begin
  FMouseDown := True;
  FShiftOnMouseDown := Shift;
  inherited MouseDown(Button, Shift, X, Y);
  { Note: The C++ version gates this on FHotTrackCell.Pressed, which is a
    private field of TCustomGrid inaccessible from Delphi. We check the
    fixed-cell coordinates directly instead — the functional effect is the
    same since hot-track presses only occur on fixed cells. }
  GridCoord := MouseCoord(X, Y);
  if ((goFixedColClick in Options) and (GridCoord.X < FixedCols)) or
     ((goFixedRowClick in Options) and (GridCoord.Y < FixedRows)) then
  begin
    if not (csDesigning in ComponentState) then
    begin
      if Assigned(FOnFixedCellCanClick) then
      begin
        CanClick := False;
        FOnFixedCellCanClick(Self, Button, Shift,
          GridCoord.X, GridCoord.Y, CanClick);
        if not CanClick then
          Exit;
      end;
    end;
  end;
end;

procedure TCustomNDrawGrid.MouseMove(Shift: TShiftState; X, Y: Integer);
begin
  inherited MouseMove(Shift, X, Y);
  if not FMouseDown then
    ShowAutoHintIfNeeded(X, Y);
end;

procedure TCustomNDrawGrid.MouseUp(Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var
  OldOnMouseMove: TMouseMoveEvent;
  GridCoord: TGridCoord;
begin
  try
    OldOnMouseMove := OnMouseMove;
    try
      OnMouseMove := nil;
      inherited MouseUp(Button, Shift, X, Y);
    finally
      OnMouseMove := OldOnMouseMove;
    end;
    GridCoord := MouseCoord(X, Y);
    if ((GridCoord.X >= 0) and (GridCoord.X < FixedCols)) or
       ((GridCoord.Y >= 0) and (GridCoord.Y < FixedRows)) then
    begin
      if not (csDesigning in ComponentState) and Assigned(FOnFixedCellMouseUp) then
        FOnFixedCellMouseUp(Self, GridCoord.X, GridCoord.Y, Button, Shift, X, Y);
    end;
  finally
    FMouseDown := False;
  end;
end;

function TCustomNDrawGrid.GetCellText(ACol, ARow: Longint): string;
begin
  Result := '';
  if not (csDesigning in ComponentState) then
  begin
    if ((ACol >= 0) and (ACol < FixedCols)) or
       ((ARow >= 0) and (ARow < FixedRows)) then
    begin
      if Assigned(FOnFixedCellGetText) then
        FOnFixedCellGetText(Self, ACol, ARow, Result);
    end
    else if Assigned(FOnNormalCellGetText) then
      FOnNormalCellGetText(Self, ACol, ARow, Result);
  end;
end;

function TCustomNDrawGrid.GetCellTextFormat(ACol, ARow: Longint): TTextFormat;
begin
  Result := [tfVerticalCenter, tfSingleLine, tfLeft];
  if not (csDesigning in ComponentState) and Assigned(FOnGetTextFormat) then
    FOnGetTextFormat(Self, ACol, ARow, Result);
  Include(Result, tfSingleLine);
end;

procedure TCustomNDrawGrid.DrawCell(ACol, ARow: Longint; ARect: TRect;
  AState: TGridDrawState);
var
  LText: string;
begin
  if DefaultDrawing then
  begin
    LText := GetCellText(ACol, ARow);
    if StyleServices.Enabled then
      InflateRect(ARect, -8, -2)
    else
      InflateRect(ARect, -2, -2);
    Canvas.TextRect(ARect, LText, GetCellTextFormat(ACol, ARow));
  end;
  inherited DrawCell(ACol, ARow, ARect, AState);
end;

procedure TCustomNDrawGrid.DrawCellBackground(const ARect: TRect;
  AColor: TColor; AState: TGridDrawState; ACol, ARow: Longint);
begin
  if not (csDesigning in ComponentState) and Assigned(FOnDrawCellBackground) then
    FOnDrawCellBackground(Self, ARect, AColor, AState, ACol, ARow)
  else
    DefaultDrawCellBackground(ARect, AColor, AState, ACol, ARow);
end;

procedure TCustomNDrawGrid.DrawCellHighlight(const ARect: TRect;
  AState: TGridDrawState; ACol, ARow: Longint);
begin
  if not (csDesigning in ComponentState) and Assigned(FOnDrawCellHighlight) then
    FOnDrawCellHighlight(Self, ARect, AState, ACol, ARow)
  else
    DefaultDrawCellHighlight(ARect, AState, ACol, ARow);
end;

procedure TCustomNDrawGrid.DefaultDrawCellBackground(const ARect: TRect;
  AColor: TColor; AState: TGridDrawState; ACol, ARow: Longint);
begin
  inherited DrawCellBackground(ARect, AColor, AState, ACol, ARow);
end;

procedure TCustomNDrawGrid.DefaultDrawCellHighlight(const ARect: TRect;
  AState: TGridDrawState; ACol, ARow: Longint);
begin
  inherited DrawCellHighlight(ARect, AState, ACol, ARow);
end;

function TCustomNDrawGrid.BeginColumnDrag(var Origin, Destination: Integer;
  const MousePt: TPoint): Boolean;
begin
  Result := inherited BeginColumnDrag(Origin, Destination, MousePt)
    and (ssShift in FShiftOnMouseDown);
end;

function TCustomNDrawGrid.EndColumnDrag(var Origin, Destination: Integer;
  const MousePt: TPoint): Boolean;
begin
  Result := inherited EndColumnDrag(Origin, Destination, MousePt);
end;

procedure TCustomNDrawGrid.KeyPress(var Key: Char);
begin
  inherited KeyPress(Key);
  ClearGridHintWindow;
end;

procedure TCustomNDrawGrid.KeyDown(var Key: Word; Shift: TShiftState);
begin
  inherited KeyDown(Key, Shift);
  case Key of
    VK_SHIFT, VK_CONTROL, VK_MENU: ; { do nothing }
  else
    ClearGridHintWindow;
  end;
end;

procedure TCustomNDrawGrid.ColWidthsChanged;
begin
  inherited ColWidthsChanged;
  if not (csDesigning in ComponentState) and Assigned(FOnColWidthsChanged) then
    FOnColWidthsChanged(Self);
end;

function TCustomNDrawGrid.CreateEditor: TInplaceEdit;
var
  Editor: TNDrawGridInplaceEditList;
begin
  Editor := TNDrawGridInplaceEditList.Create(Self);
  Editor.DropDownRows := FDropDownRowCount;
  Editor.OnGetPickListItems := FOnGetPickListItems;
  Editor.OnEditButtonClick := FOnEditButtonClick;
  Result := Editor;
end;

function TCustomNDrawGrid.GetEditStyle(ACol, ARow: Longint): TEditStyle;
begin
  Result := esSimple;
  if not (csDesigning in ComponentState) and Assigned(FOnGetEditStyle) then
    FOnGetEditStyle(Self, ACol, ARow, Result);
end;

procedure TCustomNDrawGrid.SetDropDownRowCount(Value: Integer);
var
  Editor: TInplaceEditList;
begin
  FDropDownRowCount := Value;
  if InplaceEditor is TInplaceEditList then
  begin
    Editor := TInplaceEditList(InplaceEditor);
    Editor.DropDownRows := Value;
  end;
end;

procedure TCustomNDrawGrid.SetOnEditButtonClick(Value: TNotifyEvent);
var
  Editor: TInplaceEditList;
begin
  FOnEditButtonClick := Value;
  if InplaceEditor is TInplaceEditList then
  begin
    Editor := TInplaceEditList(InplaceEditor);
    Editor.OnEditButtonClick := Value;
  end;
end;

procedure TCustomNDrawGrid.SetOnGetPickListItems(Value: TOnGetPickListItems);
var
  Editor: TInplaceEditList;
begin
  FOnGetPickListItems := Value;
  if InplaceEditor is TInplaceEditList then
  begin
    Editor := TInplaceEditList(InplaceEditor);
    Editor.OnGetPickListItems := Value;
  end;
end;

procedure TCustomNDrawGrid.WndProc(var Message: TMessage);
begin
  inherited WndProc(Message);
  case Message.Msg of
    CM_MOUSELEAVE:
      ClearGridHintWindow;
  end;
end;

procedure TCustomNDrawGrid.ClearGridHintWindow;
begin
  if Assigned(FGridHintWindow) then
  begin
    FGridHintWindow.Hide;
    FreeAndNil(FGridHintWindow);
    FGridCurrentHintCol := -1;
    FGridCurrentHintRow := -1;
  end;
end;

procedure TCustomNDrawGrid.RefreshAutoHint;
var
  CursorPos: TPoint;
  GridCoord: TGridCoord;
begin
  CursorPos := ScreenToClient(Mouse.CursorPos);
  GridCoord := MouseCoord(CursorPos.X, CursorPos.Y);
  if (FGridCurrentHintCol <> GridCoord.X) or
     (FGridCurrentHintRow <> GridCoord.Y) then
    ClearGridHintWindow;
  ShowAutoHintIfNeeded(CursorPos.X, CursorPos.Y);
end;

function TCustomNDrawGrid.SelectCell(ACol, ARow: Longint): Boolean;
begin
  RefreshAutoHint;
  Result := inherited SelectCell(ACol, ARow);
end;

procedure TCustomNDrawGrid.TopLeftChanged;
begin
  RefreshAutoHint;
  inherited TopLeftChanged;
end;

procedure TCustomNDrawGrid.ShowAutoHintIfNeeded(X, Y: Integer);
var
  HasFocus: Boolean;
  GridCoord: TGridCoord;
  DisplayText: string;
  CRect: TRect;
  CellFmt: TTextFormat;
  TextWidth: Integer;
  CellScreenPos: TPoint;
  HintRect: TRect;
  XOfs: Integer;
begin
  if FCellAutoHintEnabled and MouseInClient and
     PtInRect(ClientRect, Point(X, Y)) then
  begin
    HasFocus := FindControl(GetForegroundWindow()) <> nil;

    GridCoord := MouseCoord(X, Y);
    if HasFocus and (GridCoord.X >= FixedCols) and (GridCoord.X < ColCount)
                 and (GridCoord.Y >= FixedRows) and (GridCoord.Y < RowCount) then
    begin
      if (FGridCurrentHintCol <> GridCoord.X) or
         (FGridCurrentHintRow <> GridCoord.Y) then
        ClearGridHintWindow;

      if Assigned(FOnNormalCellGetText) then
      begin
        DisplayText := '';
        FOnNormalCellGetText(Self, GridCoord.X, GridCoord.Y, DisplayText);
        CRect := CellRect(GridCoord.X, GridCoord.Y);

        CellFmt := GetCellTextFormat(GridCoord.X, GridCoord.Y);
        TextWidth := Canvas.TextWidth(DisplayText) + 4;

        if TextWidth > CRect.Width - IfThen(StyleServices.Enabled, 12, 0) then
        begin
          if not Assigned(FGridHintWindow) then
          begin
            FGridHintWindow := THintWindow.Create(nil);
            FGridHintWindow.Color := Application.HintColor;
            FGridHintWindow.Canvas.Font.Assign(Font);
            CellScreenPos := ClientToScreen(Point(CRect.Left, CRect.Top));
            HintRect := FGridHintWindow.CalcHintRect(Screen.Width, DisplayText, nil);

            if tfCenter in CellFmt then
            begin
              XOfs := (ColWidths[GridCoord.X] - HintRect.Width
                - IfThen(StyleServices.Enabled, 0,
                    IfThen(Odd(ColWidths[GridCoord.X]), 0, 2))
                ) div 2;
            end
            else if tfRight in CellFmt then
            begin
              XOfs := (ColWidths[GridCoord.X] - HintRect.Width)
                + IfThen(StyleServices.Enabled, -5, 1);
            end
            else
            begin
              XOfs := IfThen(StyleServices.Enabled, 5, -1);
            end;

            OffsetRect(HintRect,
              CellScreenPos.X + XOfs,
              CellScreenPos.Y + (CRect.Height - HintRect.Height) div 2 - 2);
            FGridHintWindow.ActivateHint(HintRect, DisplayText);
            FGridCurrentHintCol := GridCoord.X;
            FGridCurrentHintRow := GridCoord.Y;
          end;
        end;
      end;
    end
    else
      ClearGridHintWindow;
  end;
end;

procedure TCustomNDrawGrid.Paint;
begin
  inherited Paint;
  if Assigned(FOnOverlay) then
    FOnOverlay(Self);
end;

{ TNDrawGrid }

constructor TNDrawGrid.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
end;

function TNDrawGrid.SelectCell(ACol, ARow: Longint): Boolean;
begin
  Result := inherited SelectCell(ACol, ARow);
end;

function TNDrawGrid.GetCellText(ACol, ARow: Longint): string;
begin
  Result := inherited GetCellText(ACol, ARow);
end;

function TNDrawGrid.GetCellTextFormat(ACol, ARow: Longint): TTextFormat;
begin
  Result := inherited GetCellTextFormat(ACol, ARow);
end;

end.
