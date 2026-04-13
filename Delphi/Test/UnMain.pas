unit UnMain;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.Grids, NDrawGrid;

type
  TForm1 = class(TForm)
    procedure FormCreate(Sender: TObject);
  private
    FGrid: TNDrawGrid;
    procedure GridNormalCellGetText(Sender: TObject; ACol, ARow: Integer;
      var Result: string);
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.FormCreate(Sender: TObject);
begin
  FGrid := TNDrawGrid.Create(Self);
  FGrid.Parent := Self;
  FGrid.Left := 48;
  FGrid.Top := 48;
  FGrid.Width := 320;
  FGrid.Height := 120;
  FGrid.CellAutoHintEnabled := True;
  FGrid.OnNormalCellGetText := GridNormalCellGetText;
end;

procedure TForm1.GridNormalCellGetText(Sender: TObject; ACol, ARow: Integer;
  var Result: string);
begin
  Result := Format('%d, %d', [ACol, ARow]);
end;

end.
