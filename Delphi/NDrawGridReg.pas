unit NDrawGridReg;

interface

procedure Register;

implementation

uses
  System.Classes, NDrawGrid;

procedure Register;
begin
  RegisterComponents('Anafestica', [TNDrawGrid]);
end;

end.
