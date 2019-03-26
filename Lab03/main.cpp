//
// Created by Piotr Moszkowicz on 2019-03-26.
//
#include "main.h"
#include "frame.h"

IMPLEMENT_APP(HelloWorldApp)

// This is executed upon startup, like 'main()' in non-wxWidgets programs.
bool HelloWorldApp::OnInit()
{
    wxFrame *frame = new MyFrame1((wxFrame*) NULL);
    frame->Show(true);
    SetTopWindow(frame);
    return true;
}
