#include "port.h"
#include "portSettings.h"
#include <string>

int main(int argc, char* argv[]) {

    // Set up the serial port
    PortSettings settings = getPortSettings(argc, argv);

    port_setup(settings.port, settings.baudRate, settings.byteSize, settings.stopBits, settings.parity);
    std::string stopMessage = std::to_string(settings.stopBits);
    // Check if the port was opened successfully
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "ERROR: Unable to open serial port.\n";
        return 1;
    }
    // Read data from the port in a loop
    while (true) {
        std::string data = read_data(hSerial);
        if (!data.empty()) {
            std::cout << "Received: " << data << "\n";
            if (data == stopMessage) {
                write_string(hSerial,"?0100 CR-LF");
            break;
        }
            // std::string response = "To działa!";
            // write_data(hSerial, response);  
        }
    }
    CloseHandle(hSerial);

    return 0;
}
// #include "window.h"
// #include "port.h"
// #include "portSettings.h"
// #include <wx/wx.h>
// #include <string>

// int global_argc;
// char** global_argv;

// class MyApp : public wxApp
// {
// public:
//     virtual bool OnInit() {
//         global_argc = wxApp::argc;
//         global_argv = wxApp::argv;

//         // Set up the serial port
//         PortSettings settings = getPortSettings(global_argc, global_argv);
//         port_setup(settings.port, settings.baudRate, settings.byteSize, settings.stopBits, settings.parity);

//         // Check if the port was opened successfully
//         if (hSerial == INVALID_HANDLE_VALUE) {
//             wxMessageBox("ERROR: Unable to open serial port.", "Error", wxOK | wxICON_ERROR);
//             return false;
//         }

//         MyFrame* frame = new MyFrame("My Frame", wxPoint(50, 50), wxSize(450, 340));
//         frame->Show(true);
//         return true;
//     }
// };

// wxIMPLEMENT_APP(MyApp);