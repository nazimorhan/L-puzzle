#include "puzzle.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
class PuzzleApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnClick(wxCommandEvent& event);
    // void OnMotion(wxMouseEvent& event);

    wxDECLARE_EVENT_TABLE();
};

enum
{
    ID_Random = 1,
    ID_Search
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_BUTTON(ID_Search, MyFrame::OnClick)
// EVT_MOTION(MyFrame::OnMotion)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(PuzzleApp);

bool PuzzleApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "L-Puzzle Game Solver")
{
    //wxMenu *menuFile = new wxMenu;
    //menuFile->Append(ID_Random, "&Hello...\tCtrl-H",
    //                 "Help string shown in status bar for this menu item");
    //menuFile->AppendSeparator();
    //menuFile->Append(wxID_EXIT);
    //wxMenu *menuHelp = new wxMenu;
    //menuHelp->Append(wxID_ABOUT);
    //wxMenuBar *menuBar = new wxMenuBar;
    //menuBar->Append(menuFile, "&File");
    //menuBar->Append(menuHelp, "&Help");
    //SetMenuBar( menuBar );
    //CreateStatusBar();
    //SetStatusText("Welcome to wxWidgets!");
    
    // Add button to initiazlie search.
    auto button = new wxButton(this, ID_Search, "SEARCH");
    auto sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(button, 0, wxCENTER | wxALL, 100);
    SetSizerAndFit(sizer);

    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Random);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnClick, this, ID_Search);
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

void MyFrame::OnClick(wxCommandEvent& event) {
    int size = 3;
    int algo = 3;
    string inp[10] = {"3", "4", "6", "1", "0", "8", "7", "2", "5"};
    triggerSearch(size,algo, inp);
}

/*void MyFrame::OnMotion(wxMouseEvent& event)
{
    if (event.Dragging())
    {
        wxClientDC dc(this);
        wxPen pen(*wxRED, 1); // red pen of width 1
        dc.SetPen(pen);
        dc.DrawPoint(event.GetPosition());
        dc.SetPen(wxNullPen);
    }
}*/

/*int main(void){
    int size = 3;
    string inp[10] = {"3", "1", "2", "3", "4", "5", "6", "7", "8", "0"};
    search(size, inp);

    return 0;
}*/