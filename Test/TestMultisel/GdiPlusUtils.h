//---------------------------------------------------------------------------

#ifndef GdiPlusUtilsH
#define GdiPlusUtilsH

#include <Classes.hpp>
#include <SysUtils.hpp>

#include "VclGdiplus.h"

#include <boost/utility.hpp>

//---------------------------------------------------------------------------
namespace GdiplusUtils {
//---------------------------------------------------------------------------

class GdiPlusSessionManager : public boost::noncopyable {
public:
    GdiPlusSessionManager();
    ~GdiPlusSessionManager() /* throw() */;
private:
    Gdiplus::GdiplusStartupInput gdiplusStartupInput_;
    ULONG_PTR gdiplusToken_;
};

#define APPUTILS_MAKE_EXCEPTION_CLASS( name, base ) \
class name : public base \
{ \
    typedef base inherited; \
public: \
    __fastcall name(const System::UnicodeString Msg) : base(Msg) { } \
    __fastcall name(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_Size) : base(Msg, Args, Args_Size) { } \
    __fastcall name(int Ident)/* overload */ : base(Ident) { } \
    __fastcall name(int Ident, System::TVarRec const *Args, const int Args_Size)/* overload */ : base(Ident, Args, Args_Size) { } \
    __fastcall name(const System::UnicodeString Msg, int AHelpContext) : base(Msg, AHelpContext) { } \
    __fastcall name(const System::UnicodeString Msg, System::TVarRec const *Args, const int Args_Size, int AHelpContext) : base(Msg, Args, Args_Size, AHelpContext) { } \
    __fastcall name(int Ident, int AHelpContext)/* overload */ : base(Ident, AHelpContext) { } \
    __fastcall name(System::PResStringRec ResStringRec, System::TVarRec const *Args, const int Args_Size, int AHelpContext)/* overload */ : base(ResStringRec, Args, Args_Size, AHelpContext) { } \
    __fastcall virtual ~name(void) { } \
};

APPUTILS_MAKE_EXCEPTION_CLASS( EGdiplusExceptionBase, Sysutils::Exception );

class EGdiplusException : public EGdiplusExceptionBase {
public:
    typedef  EGdiplusExceptionBase  inherited;

    __fastcall EGdiplusException( String Msg );
    __fastcall EGdiplusException( Gdiplus::Status Code );
};

extern String GetGdiplusStatusStrings( Gdiplus::Status Code );
extern void GdiplusCheck( Gdiplus::Status Code );
extern Gdiplus::Image* LoadImage( String FileName );
extern Gdiplus::Color TColorToGdiplusColor( TColor Val );
extern Gdiplus::Color TColorToGdiplusColor( TColor Val, BYTE Alpha );
extern Gdiplus::StringAlignment AlignmentToGdiplusStringAlignment( TAlignment Val );
extern Gdiplus::StringAlignment VerticalAlignmentToGdiplusStringAlignment( TVerticalAlignment Val );
extern void DrawImage( ::Gdiplus::Graphics& g, Gdiplus::Image& Img,
                       Gdiplus::RectF const & DstRect, BYTE AlphaBlend,
                       bool Stretched = true, bool MantainAspectRatio = false );
extern Gdiplus::RectF VCLRectToGdiPlusRectF( TRect const & Rect );
extern void GetEncoderClsid( WCHAR const * Format, CLSID* Clsid );
//extern Gdiplus::Image* LoadImageFromStream( TStream* Stream, String MimeType );

//---------------------------------------------------------------------------
} // End of namespace GdiplusUtils
//---------------------------------------------------------------------------
#endif


