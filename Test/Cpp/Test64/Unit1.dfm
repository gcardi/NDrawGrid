object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 441
  ClientWidth = 624
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object NDrawGrid1: TNDrawGrid
    Left = 48
    Top = 48
    Width = 320
    Height = 120
    CellAutoHintEnabled = True
    OnNormalCellGetText = NDrawGrid1NormalCellGetText
    TabOrder = 0
  end
end
