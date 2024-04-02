#include "window.h"
#include "port.h"
#include "portSettings.h"
extern int global_argc;
extern char** global_argv;

void MyFrame::OnStartCommunication(wxCommandEvent& event)
{
    PortSettings settings = getPortSettings(global_argc, global_argv);
    wxMessageDialog dialog(this, "Would you like to enter the port name?", "Question", wxYES_NO);
    if (dialog.ShowModal() == wxID_YES) {
        wxTextEntryDialog textDialog(this, "Enter the port name:");
        if (textDialog.ShowModal() == wxID_OK) {
            wxString portName = textDialog.GetValue();
            port_setup(std::string(portName.mb_str()), settings.baudRate, settings.byteSize, settings.stopBits, settings.parity);
        }
    } else {
        port_setup(settings.port, settings.baudRate, settings.byteSize, settings.stopBits, settings.parity);
    }
}