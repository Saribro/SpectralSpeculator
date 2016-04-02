#include "SSApp.h"
#include "SSWindow.h"
#include "Spectrum.h"

#include "wx/textctrl.h"
#include "wx/choice.h"

IMPLEMENT_APP(SpectralSpeculatorApp)

IMPLEMENT_CLASS(SpectralSpeculatorApp, wxApp)

SpectralSpeculatorApp::SpectralSpeculatorApp()
{
    Init();
}

void SpectralSpeculatorApp::Init()  // TODO
{
    // bind events (generated by SSWindow)
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &SpectralSpeculatorApp::OnButtonToRadianceClick,    this, ID_BUTTON_TORADIANCE);
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &SpectralSpeculatorApp::OnButtonToTemperatureClick, this, ID_BUTTON_TOTEMPERATURE);

    Bind(wxEVT_TEXT_ENTER, &SpectralSpeculatorApp::OnButtonToRadianceClick,    this, ID_TEMPERATURE);
    Bind(wxEVT_TEXT_ENTER, &SpectralSpeculatorApp::OnButtonToTemperatureClick, this, ID_RADIANCE);

    // Adjust language
    // TODO: Figure out this mess :/.
    // TODO: Use identifiers instead of strings (ex: "T_WINDOW_TITLE"), even 'English' should be a translation.
}

bool SpectralSpeculatorApp::OnInit()
{
    auto window = new SSWindow(nullptr);
    SetTopWindow(window);
    window->Show(true);

    return true;
}

void SpectralSpeculatorApp::ToRadiance()
{
    auto topwindow = GetTopWindow();

    auto lStartString = dynamic_cast<wxTextCtrl *>(topwindow->FindWindowById(ID_L_START))->GetValue();
    auto lEndString   = dynamic_cast<wxTextCtrl *>(topwindow->FindWindowById(ID_L_END))->GetValue();

    double lStart = 0.0f;
    double lEnd   = 0.0f;

    auto tempString = dynamic_cast<wxTextCtrl *>(topwindow->FindWindowById(ID_TEMPERATURE))->GetValue();

    double temperature = 0.0f;
    double radiance    = 0.0f;

    if(!lStartString.empty() && !lEndString.empty() && !tempString.empty()) {
        lStart = std::stod(lStartString.wc_str()) / 1000000;
        lEnd   = std::stod(lEndString.wc_str()) / 1000000;

        temperature = std::stod(tempString.wc_str());

        if(dynamic_cast<wxChoice *>(topwindow->FindWindowById(ID_TEMPERATURE_UNIT))->GetSelection()) {
            temperature += 273.15f;
        }

        radiance = Spectrum::TemperatureToRadiance(temperature, lStart, lEnd);

        dynamic_cast<wxTextCtrl *>(topwindow->FindWindowById(ID_RADIANCE))->SetValue(std::to_wstring(radiance));
    }
}

void SpectralSpeculatorApp::ToTemperature()
{
    auto topwindow = GetTopWindow();

    auto lStartString = dynamic_cast<wxTextCtrl *>(topwindow->FindWindowById(ID_L_START))->GetValue();
    auto lEndString   = dynamic_cast<wxTextCtrl *>(topwindow->FindWindowById(ID_L_END))->GetValue();

    double lStart = 0.0f;
    double lEnd   = 0.0f;

    auto radString = dynamic_cast<wxTextCtrl *>(topwindow->FindWindowById(ID_RADIANCE))->GetValue();

    double temperature = 0.0f;
    double radiance    = 0.0f;

    if(!lStartString.empty() && !lEndString.empty() && !radString.empty()) {
        lStart = std::stod(lStartString.wc_str()) / 1000000;
        lEnd   = std::stod(lEndString.wc_str()) / 1000000;

        radiance = std::stod(radString.wc_str());

        temperature = Spectrum::RadianceToTemperature(radiance, lStart, lEnd);

        if(dynamic_cast<wxChoice *>(topwindow->FindWindowById(ID_TEMPERATURE_UNIT))->GetSelection()) {
            temperature -= 273.15f;
        }

        dynamic_cast<wxTextCtrl *>(topwindow->FindWindowById(ID_TEMPERATURE))->SetValue(std::to_wstring(temperature));
    }
}