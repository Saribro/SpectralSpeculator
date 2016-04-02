#include "SSWindow.h"

#include "wx/bitmap.h"
#include "wx/sizer.h"
#include "wx/gbsizer.h"
#include "wx/stattext.h"
#include "wx/statbox.h"
#include "wx/textctrl.h"
#include "wx/button.h"
#include "wx/choice.h"
#include "wx/valnum.h"
#include "wx/panel.h"

IMPLEMENT_CLASS(SSWindow, wxFrame)

SSWindow::SSWindow()
{
    Init();
}

SSWindow::SSWindow(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
    Init();
    Create(parent, id, caption, pos, size, style);
}

bool SSWindow::Create(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
    wxFrame::Create(parent, id, caption, pos, size, style);

    CreateControls();
    Fit();
    Centre();

    return true;
}

void SSWindow::CreateControls()
{
    auto panelSizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(panelSizer);

    auto panel = new wxPanel(this, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    panelSizer->Add(panel, 0, wxGROW, 5);

    auto mainSizer = new wxGridBagSizer(0, 0);
    panel->SetSizer(mainSizer);

    auto lambdaSizer = new wxStaticBoxSizer(new wxStaticBox(panel, wxID_STATIC, _("Wavelength")), wxHORIZONTAL);
    mainSizer->Add(lambdaSizer, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_LEFT | wxGROW | wxALL, 5);

    auto lambdaGridSizer = new wxFlexGridSizer(0, 2, 0, 0);
    lambdaSizer->Add(lambdaGridSizer, 0, wxALIGN_CENTER_VERTICAL, 5);

    lambdaGridSizer->Add(new wxStaticText(panel, wxID_STATIC, _("Start:"), wxDefaultPosition, wxDefaultSize, 0),
                         0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 5);

    lambdaGridSizer->Add(new wxTextCtrl(panel, ID_L_START, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxFloatingPointValidator<double>(1)),
                         0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 5);

    lambdaGridSizer->Add(new wxStaticText(panel, wxID_STATIC, _("End:"), wxDefaultPosition, wxDefaultSize, 0),
                         0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 5);

    lambdaGridSizer->Add(new wxTextCtrl(panel, ID_L_END, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxFloatingPointValidator<double>(1)),
                         0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 5);

    auto actionSizer = new wxStaticBoxSizer(new wxStaticBox(panel, wxID_ANY, _("Action")), wxVERTICAL);
    mainSizer->Add(actionSizer, wxGBPosition(0, 1), wxGBSpan(1, 1), wxALIGN_CENTER_HORIZONTAL | wxGROW | wxALL, 5);

    actionSizer->Add(new wxButton(panel, ID_BUTTON_TORADIANCE, _("To Radiance"), wxDefaultPosition, wxDefaultSize, 0),
                     0, wxGROW | wxALL, 5);

    actionSizer->Add(new wxButton(panel, ID_BUTTON_TOTEMPERATURE, _("To Temperature"), wxDefaultPosition, wxDefaultSize, 0),
                     0, wxGROW | wxALL, 5);

    auto valueSizer = new wxStaticBoxSizer(new wxStaticBox(panel, wxID_ANY, _("Values")), wxHORIZONTAL);
    mainSizer->Add(valueSizer, wxGBPosition(1, 0), wxGBSpan(1, 2), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 5);

    auto valueGridSizer = new wxFlexGridSizer(0, 3, 0, 0);
    valueSizer->Add(valueGridSizer, 0, wxALIGN_CENTER_VERTICAL, 5);

    valueGridSizer->Add(new wxStaticText(panel, wxID_STATIC, _("Temperature:"), wxDefaultPosition, wxDefaultSize, 0),
                        0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 5);

    valueGridSizer->Add(new wxTextCtrl(panel, ID_TEMPERATURE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxFloatingPointValidator<double>(2)),
                        0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxArrayString unitStrings;
    unitStrings.Add(_("K (Kelvin)"));
    unitStrings.Add(_("°C (Celcius)"));
    auto choice = new wxChoice(panel, ID_TEMPERATURE_UNIT, wxDefaultPosition, wxDefaultSize, unitStrings, 0);
    choice->SetSelection(1);    // default to Celsius
    valueGridSizer->Add(choice, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 5);

    valueGridSizer->Add(new wxStaticText(panel, wxID_STATIC, _("Radiance:"), wxDefaultPosition, wxDefaultSize, 0),
                        0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 5);

    valueGridSizer->Add(new wxTextCtrl(panel, ID_RADIANCE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER, wxFloatingPointValidator<double>()),
                        0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL | wxALL, 5);
}

wxBitmap SSWindow::GetBitmapResource(const wxString & name)
{
    wxUnusedVar(name);
    return wxNullBitmap;
}

wxIcon SSWindow::GetIconResource(const wxString & name)
{
    wxUnusedVar(name);
    return wxNullIcon;
}
