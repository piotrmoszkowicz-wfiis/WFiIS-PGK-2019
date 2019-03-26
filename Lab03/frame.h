///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Mar 25 2019)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <iostream>

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/scrolbar.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/frame.h>
#include <wx/filedlg.h>
#include <wx/log.h>
#include <wx/wfstream.h>
#include <wx/dcbuffer.h>
#include <wx/colordlg.h>
#include <wx/event.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame {
private:

protected:
    wxPanel *m_panel1;
    wxButton *m_button7;
    wxCheckBox *m_checkBox1;
    wxScrollBar *m_scrollBar1;
    wxGauge* m_gauge1;
    wxButton *m_button8;
    wxTextCtrl *m_textCtrl1;
    wxChoice *m_choice1;
    wxFileDialog *m_saveDialog;
    wxPoint m_coordsOfStar[5];
    wxColor *m_starColour;
    wxString m_textToDraw;
    bool m_drawBanana;
    wxBitmap * m_banana;
    wxBitmap * m_bitMapToSave;
    int m_bananaPlace;
    unsigned int m_chosenFigure;

    wxPNGHandler *m_pngHandler;

    // Virtual event handlers, overide them in your derived class
    void m_panelOnPaint( wxPaintEvent& event );

    void m_panelOnUpdateUI( wxUpdateUIEvent& event );

    void m_button7OnButtonClick(wxCommandEvent &event);

    void m_checkBox1OnCheckBox(wxCommandEvent &event);

    void m_scrollBar1OnScroll( wxScrollEvent& event );

    void m_button8OnButtonClick(wxCommandEvent &event);

    void m_textCtrl1OnText(wxCommandEvent &event);

    void m_choice1OnChoice(wxCommandEvent &event);

    void m_render(wxClientDC &drawClient);


public:

    MyFrame1(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &title = wxT("GFK Lab 03"),
             const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxSize(700, 450),
             long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

    ~MyFrame1();

};

