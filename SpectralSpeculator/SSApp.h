#pragma once

#include "wx/app.h"

class SpectralSpeculatorApp : public wxApp
{
    DECLARE_CLASS(SpectralSpeculatorApp)

public:
    SpectralSpeculatorApp();

    void Init();

    virtual bool OnInit();
    virtual int OnExit() { return wxApp::OnExit(); }

private:
    void OnButtonToRadianceClick(wxCommandEvent &)    { ToRadiance(); }
    void OnButtonToTemperatureClick(wxCommandEvent &) { ToTemperature(); }

    void ToRadiance();
    void ToTemperature();
};

DECLARE_APP(SpectralSpeculatorApp)
