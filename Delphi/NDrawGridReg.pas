unit NDrawGridReg;

interface

{$R NDrawGridDsgnPkg_resources.res}

procedure Register;

implementation

uses
  System.Classes, NDrawGrid;

procedure Register;
begin
  RegisterComponents('Anafestica', [TNDrawGrid]);
end;

end.
