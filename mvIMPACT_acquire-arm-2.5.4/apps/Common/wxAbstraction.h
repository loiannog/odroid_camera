//-----------------------------------------------------------------------------
#ifndef wxAbstractionH
#define wxAbstractionH wxAbstractionH
//-----------------------------------------------------------------------------
#include <string>
#include <wx/config.h>
#include <wx/dynlib.h>
#include <wx/gdicmn.h>
#include <wx/log.h>
#include <wx/string.h>
#include <wx/window.h>

// helper class
struct ConvertedString : wxString
{
#if wxUSE_UNICODE
	ConvertedString( const char* s ) :
		wxString( s, wxConvUTF8 ) {};
	ConvertedString( const std::string& s ) :
		wxString( s.c_str(), wxConvUTF8 ) {};
	ConvertedString( const wxString& s ) :
# if wxCHECK_VERSION(2,9,0)
		wxString( s.mb_str(), wxConvUTF8 ) {};
# else
		wxString( s.c_str(), wxConvUTF8 ) {};
# endif
#else
	ConvertedString( const char* s ) :
		wxString( s ) {};
	ConvertedString( const std::string& s ) :
		wxString( s.c_str() ) {};
	ConvertedString( const wxString& s ) :
# if wxCHECK_VERSION(2,9,0)
		wxString( s.mb_str() ) {};
# else
		wxString( s.c_str() ) {};
# endif
#endif
};

#if ( wxMINOR_VERSION > 6 ) && ( wxMAJOR_VERSION < 3 ) && !WXWIN_COMPATIBILITY_2_6
#include <wx/filedlg.h>
enum {
    wxOPEN              = wxFD_OPEN,
    wxSAVE              = wxFD_SAVE,
    wxOVERWRITE_PROMPT  = wxFD_OVERWRITE_PROMPT,
    wxFILE_MUST_EXIST   = wxFD_FILE_MUST_EXIST,
    wxMULTIPLE          = wxFD_MULTIPLE,
    wxCHANGE_DIR        = wxFD_CHANGE_DIR
};
#endif

//=============================================================================
//================= Implementation FramePositionStorage =======================
//=============================================================================
//-----------------------------------------------------------------------------
class FramePositionStorage
//-----------------------------------------------------------------------------
{
	wxWindow* m_pWin;
public:
	FramePositionStorage( wxWindow* pWin ) : m_pWin(pWin) {}
	void Save( void ) const { Save( m_pWin ); }
	static void Save( wxWindow* pWin, const wxString& windowName = wxT("MainFrame") )
	{
		wxConfigBase* pConfig(wxConfigBase::Get());
		int Height, Width, XPos, YPos;
		pWin->GetSize( &Width, &Height );
		pWin->GetPosition( &XPos, &YPos );
		// when we e.g. try to write config stuff on a read-only file system the result can
		// be an annoying message box. Therefore we switch off logging during the storage operation.
		wxLogNull logSuspendScope;
		pConfig->Write( wxString::Format( wxT("/%s/h"), windowName.c_str() ), Height );
		pConfig->Write( wxString::Format( wxT("/%s/w"), windowName.c_str() ), Width );
		pConfig->Write( wxString::Format( wxT("/%s/x"), windowName.c_str() ), XPos );
		pConfig->Write( wxString::Format( wxT("/%s/y"), windowName.c_str() ), YPos );
		pConfig->Flush();
	}
	static wxRect Load( const wxRect& defaultDimensions, const wxString& windowName = wxT("MainFrame") )
	{
		wxConfigBase* pConfig(wxConfigBase::Get());
		wxRect rect;
		rect.height = pConfig->Read( wxString::Format( wxT("/%s/h"), windowName.c_str() ), defaultDimensions.height );
		rect.width = pConfig->Read( wxString::Format( wxT("/%s/w"), windowName.c_str() ), defaultDimensions.width );
		rect.x = pConfig->Read( wxString::Format( wxT("/%s/x"), windowName.c_str() ), defaultDimensions.x );
		rect.y = pConfig->Read( wxString::Format( wxT("/%s/y"), windowName.c_str() ), defaultDimensions.y );
		int displayWidth = 0;
		int displayHeight = 0;
		wxDisplaySize( &displayWidth, &displayHeight );
		if( ( rect.x >= displayWidth ) || ( rect.x < 0 ) )
		{
			rect.x = 0;
		}
		if( ( rect.y >= displayHeight ) || ( rect.y < 0 ) )
		{
			rect.y = 0;
		}
		return rect;
	}
};

#ifdef _WIN32
#	define DECLARE_GENTL_PRODUCER_LIB_NAMES \
		const wxString libName(wxT("mvGenTLProducer.cti")); \
		const wxString deprecatedLibName(wxT("mvTLIClientGigE.cti"));
#else
#	define DECLARE_GENTL_PRODUCER_LIB_NAMES \
	const wxString libName(wxT("libmvGenTLProducer.so")); \
	const wxString deprecatedLibName(wxT("libmvTLIClientGigE.so"));
#endif

//-----------------------------------------------------------------------------
inline wxString LoadGenTLProducer( wxDynamicLibrary& lib )
//-----------------------------------------------------------------------------
{
	DECLARE_GENTL_PRODUCER_LIB_NAMES

	wxString message;
	// when we e.g. trying to load a shared library that cannot be found the result can
	// be an annoying message box. Therefore we switch off logging during the load attempts.
	wxLogNull logSuspendScope;
	lib.Load( libName, wxDL_VERBATIM );
	if( !lib.IsLoaded() )
	{
		message = wxString::Format( wxT("Could not connect to '%s'. Will try to connect to the deprecated '%s' library instead.\n\n"), libName.c_str(), deprecatedLibName.c_str() );
		lib.Load( deprecatedLibName, wxDL_VERBATIM );
		if( !lib.IsLoaded() )
		{
			message.Append( wxString::Format( wxT("Connecting to '%s' however did fail as well. Check if your installation.\n\n"), deprecatedLibName.c_str() ) );
		}
	}
	return message;
}


#endif // wxAbstractionH
