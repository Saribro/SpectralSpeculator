#pragma once

#include "wx/frame.h"

#define ID_SSWINDOW             10000

#define ID_L_START              10001
#define ID_L_END                10002

#define ID_BUTTON_TORADIANCE    10006
#define ID_BUTTON_TOTEMPERATURE 10007

#define ID_TEMPERATURE          10003
#define ID_TEMPERATURE_UNIT     10004
#define ID_RADIANCE             10005

#define SYMBOL_SSWINDOW_STYLE       wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)
#define SYMBOL_SSWINDOW_TITLE       _("Spectral Speculator")
#define SYMBOL_SSWINDOW_IDNAME      ID_SSWINDOW
#define SYMBOL_SSWINDOW_SIZE        wxSize(310, 200)
#define SYMBOL_SSWINDOW_POSITION    wxDefaultPosition

class SSWindow : public wxFrame
{
    DECLARE_CLASS(SSWindow)

public:
    SSWindow();
    SSWindow(wxWindow* parent, wxWindowID id = SYMBOL_SSWINDOW_IDNAME, const wxString& caption = SYMBOL_SSWINDOW_TITLE, const wxPoint& pos = SYMBOL_SSWINDOW_POSITION, const wxSize& size = SYMBOL_SSWINDOW_SIZE, long style = SYMBOL_SSWINDOW_STYLE);

    bool Create(wxWindow* parent, wxWindowID id = SYMBOL_SSWINDOW_IDNAME, const wxString& caption = SYMBOL_SSWINDOW_TITLE, const wxPoint& pos = SYMBOL_SSWINDOW_POSITION, const wxSize& size = SYMBOL_SSWINDOW_SIZE, long style = SYMBOL_SSWINDOW_STYLE);

    ~SSWindow() {}

    void Init() {}
    void CreateControls();

    wxBitmap GetBitmapResource(const wxString& name);
    wxIcon   GetIconResource(const wxString& name);

    static bool ShowToolTips() { return true; }
};
