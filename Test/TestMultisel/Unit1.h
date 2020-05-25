//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <NDrawGrid.h>
#include <Vcl.Grids.hpp>
#include <Vcl.ImgList.hpp>

#include <unordered_set>
#include <vector>

#include "GdiPlusUtils.h"

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TComboBox *ComboBox1;
    TLabel *Label1;
    TButton *Button1;
    TNDrawGrid *NDrawGrid2;
    void __fastcall ComboBox1Change(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall NDrawGrid2DrawCell(TObject *Sender, int ACol, int ARow, const TRect &Rect,
          TGridDrawState State);
    UnicodeString __fastcall NDrawGrid2FixedCellGetText(TObject *Sender, int ACol,
          int ARow);
    TEditStyle __fastcall NDrawGrid2GetEditStyle(TObject *Sender, int ACol, int ARow);
    void __fastcall NDrawGrid2GetEditText(TObject *Sender, int ACol, int ARow, UnicodeString &Value);
    void __fastcall NDrawGrid2GetPickListItems(int ACol, int ARow, TStrings *Items);
    void __fastcall NDrawGrid2KeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall NDrawGrid2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
    UnicodeString __fastcall NDrawGrid2NormalCellGetText(TObject *Sender, int ACol,
          int ARow);
    void __fastcall NDrawGrid2SelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect);
    void __fastcall NDrawGrid2SetEditText(TObject *Sender, int ACol, int ARow, const UnicodeString Value);







private:	// User declarations
    typedef  std::tr1::unordered_set<int>  SelectedCont;
    typedef  std::vector<String>  RowCont;
    typedef  std::vector<RowCont> GridCont;

    SelectedCont selected_;
    GridCont gridData_;
    GdiplusUtils::GdiPlusSessionManager gdiMngr_;

    bool IsRowHighlighted( int ARow ) const;
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
