object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 559
  ClientWidth = 742
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    742
    559)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 22
    Top = 11
    Width = 71
    Height = 13
    Alignment = taRightJustify
    Caption = 'Selected style:'
  end
  object ComboBox1: TComboBox
    Left = 104
    Top = 8
    Width = 145
    Height = 21
    Style = csDropDownList
    TabOrder = 2
    OnChange = ComboBox1Change
  end
  object Button1: TButton
    Left = 280
    Top = 6
    Width = 137
    Height = 25
    Caption = 'Clear Selelction'
    TabOrder = 1
    OnClick = Button1Click
  end
  object NDrawGrid2: TNDrawGrid
    Left = 8
    Top = 37
    Width = 726
    Height = 514
    Anchors = [akLeft, akTop, akRight, akBottom]
    ColCount = 20
    Color = clWindow
    DefaultDrawing = False
    DefaultRowHeight = 20
    FixedColor = clBtnFace
    FixedCols = 0
    OnGetEditText = NDrawGrid2GetEditText
    OnKeyPress = NDrawGrid2KeyPress
    OnMouseUp = NDrawGrid2MouseUp
    OnSelectCell = NDrawGrid2SelectCell
    OnSetEditText = NDrawGrid2SetEditText
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goEditing, goRowSelect, goThumbTracking, goFixedColClick]
    RowCount = 100
    OnGetEditStyle = NDrawGrid2GetEditStyle
    OnGetPickListItems = NDrawGrid2GetPickListItems
    TabOrder = 0
    OnFixedCellGetText = NDrawGrid2FixedCellGetText
    OnNormalCellGetText = NDrawGrid2NormalCellGetText
    CellAutoHintEnabled = True
    OnDrawCell = NDrawGrid2DrawCell
  end
end
