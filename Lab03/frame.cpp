///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Mar 25 2019)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "frame.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size,
                   long style) : wxFrame(parent, id, title, pos, size, style) {
    this->SetSizeHints(wxSize(700, -1), wxDefaultSize);
    this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_APPWORKSPACE));

    m_textToDraw = wxT("tekst");

    m_drawBanana = false;

    m_pngHandler = new wxPNGHandler();

    wxImage::AddHandler(m_pngHandler);
    wxImage *bananImage = new wxImage(wxSize(50, 38));
    bananImage->LoadFile("assets/banan.png", wxBITMAP_TYPE_PNG);
    m_banana = new wxBitmap(*bananImage);

    m_saveDialog = new wxFileDialog(this, _("Choose file:"), _(""), _(""), _("JPG files (*.jpg)|*.jpg"), wxFD_SAVE);

    m_bananaPlace = 0;

    m_chosenFigure = 0;

    m_starColour = new wxColour(*wxBLACK);

    wxBoxSizer *bSizer3;
    bSizer3 = new wxBoxSizer(wxHORIZONTAL);

    bSizer3->SetMinSize(wxSize(700, -1));

    m_panel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxTAB_TRAVERSAL);
    m_panel1->SetBackgroundColour(wxColour(255, 255, 255));
    m_panel1->SetMinSize(wxSize(500, 410));

    bSizer3->Add( m_panel1, 500, wxEXPAND | wxALL, 5 );

    wxBoxSizer *bSizer1;
    bSizer1 = new wxBoxSizer(wxVERTICAL);

    bSizer1->SetMinSize(wxSize(180, -1));

    m_button7 = new wxButton(this, wxID_ANY, wxT("Zapis do pliku"), wxPoint(-1, -1), wxDefaultSize, 0);
    bSizer1->Add(m_button7, 0, wxALIGN_CENTER | wxALL, 5);

    m_checkBox1 = new wxCheckBox(this, wxID_ANY, wxT("banan"), wxDefaultPosition, wxDefaultSize, 0);
    m_checkBox1->SetForegroundColour(wxColour(0, 0, 0));
    bSizer1->Add(m_checkBox1, 0, wxALIGN_CENTER | wxALL, 5);

    m_scrollBar1 = new wxScrollBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL);
    m_scrollBar1->Disable();
    m_scrollBar1->SetMinSize(wxSize(170, -1));
    m_scrollBar1->SetRange(100);

    bSizer1->Add(m_scrollBar1, 0, wxALL, 5);

    m_gauge1 = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxSize(170, -1), wxGA_HORIZONTAL);
    m_gauge1->SetValue(0);
    m_gauge1->SetRange(100);
    m_gauge1->Disable();
    bSizer1->Add(m_gauge1, 0, wxALL, 5);

    m_button8 = new wxButton(this, wxID_ANY, wxT("Kolor gwiazdki"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer1->Add(m_button8, 0, wxALIGN_CENTER | wxALL, 5);

    m_textCtrl1 = new wxTextCtrl(this, wxID_ANY, wxT("tekst"), wxDefaultPosition, wxDefaultSize, 0);
    m_textCtrl1->SetBackgroundColour(wxColour(254, 255, 254));

    bSizer1->Add(m_textCtrl1, 0, wxALIGN_CENTER | wxALL, 5);

    wxArrayString m_choice1Choices;
    m_choice1Choices.Add(wxT("gwiazdka"));
    m_choice1Choices.Add(wxT("księżyc"));
    m_choice1Choices.Add(wxT("słonko"));
    m_choice1 = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1Choices, 0);
    m_choice1->SetSelection(0);
    bSizer1->Add(m_choice1, 0, wxALIGN_CENTER | wxALL, 5);

    bSizer3->Add(bSizer1, 1, wxFIXED_MINSIZE | wxALIGN_RIGHT | wxTOP, 5);


    this->SetSizer(bSizer3);
    this->Layout();

    this->Centre(wxBOTH);

    // Connect Events
    m_panel1->Connect(wxEVT_PAINT, wxPaintEventHandler(MyFrame1::m_panelOnPaint), NULL, this);
    m_panel1->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::m_panelOnUpdateUI), NULL, this);
    m_button7->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::m_button7OnButtonClick), NULL,
                       this);
    m_checkBox1->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MyFrame1::m_checkBox1OnCheckBox), NULL,
                         this);
    m_button8->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::m_button8OnButtonClick), NULL,
                       this);
    m_textCtrl1->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyFrame1::m_textCtrl1OnText), NULL, this);
    m_scrollBar1->Connect(wxEVT_SCROLL_TOP, wxScrollEventHandler(MyFrame1::m_scrollBar1OnScroll), NULL, this);
    m_scrollBar1->Connect(wxEVT_SCROLL_BOTTOM, wxScrollEventHandler(MyFrame1::m_scrollBar1OnScroll), NULL, this);
    m_scrollBar1->Connect(wxEVT_SCROLL_LINEUP, wxScrollEventHandler(MyFrame1::m_scrollBar1OnScroll), NULL, this);
    m_scrollBar1->Connect(wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler(MyFrame1::m_scrollBar1OnScroll), NULL, this);
    m_scrollBar1->Connect(wxEVT_SCROLL_PAGEUP, wxScrollEventHandler(MyFrame1::m_scrollBar1OnScroll), NULL, this);
    m_scrollBar1->Connect(wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler(MyFrame1::m_scrollBar1OnScroll), NULL, this);
    m_scrollBar1->Connect(wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler(MyFrame1::m_scrollBar1OnScroll), NULL, this);
    m_scrollBar1->Connect(wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler(MyFrame1::m_scrollBar1OnScroll), NULL, this);
    m_scrollBar1->Connect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(MyFrame1::m_scrollBar1OnScroll), NULL, this);
    m_choice1->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(MyFrame1::m_choice1OnChoice), NULL, this);
}

void MyFrame1::m_panelOnPaint(wxPaintEvent &event) {
    wxClientDC dcBuffer(m_panel1);
    m_panel1->Refresh();
    m_panel1->Update();
    m_render(dcBuffer);
}

void MyFrame1::m_panelOnUpdateUI(wxUpdateUIEvent &event) {
    wxClientDC dcBuffer(m_panel1);
    m_render(dcBuffer);
};


void MyFrame1::m_button7OnButtonClick(wxCommandEvent &event) {\
    wxClientDC dcClient(m_panel1);
    wxBufferedDC dcBuffer(&dcClient);
    PrepareDC(dcBuffer);
    wxInitAllImageHandlers();

    wxString fileName;

    if (m_saveDialog->ShowModal() == wxID_CANCEL) {
        return;
    }
    Refresh();
    fileName = m_saveDialog->GetPath();

    wxSize panelSize = m_panel1->GetVirtualSize();
    m_bitMapToSave = new wxBitmap(panelSize);

    wxMemoryDC memory;
    memory.SelectObject(*m_bitMapToSave);
    memory.Blit(0, 0, panelSize.GetX(), panelSize.GetY(), &dcBuffer, 0, 0, wxCOPY, true);

    wxImage result = m_bitMapToSave->ConvertToImage();
    result.SaveFile(fileName, wxBITMAP_TYPE_JPEG);
}

void MyFrame1::m_checkBox1OnCheckBox(wxCommandEvent &event) {
    m_drawBanana = event.IsChecked();
    m_scrollBar1->Enable(m_drawBanana);
}

void MyFrame1::m_scrollBar1OnScroll(wxScrollEvent &event) {
    m_bananaPlace = event.GetPosition();
    m_gauge1->SetValue(event.GetPosition());
    Refresh();
}

void MyFrame1::m_button8OnButtonClick(wxCommandEvent &event) {
    wxColourDialog colourDialog(this);
    if (colourDialog.ShowModal() == wxID_OK)
        *m_starColour = colourDialog.GetColourData().GetColour();
    Refresh();
}

void MyFrame1::m_textCtrl1OnText(wxCommandEvent &event) {
    m_textToDraw = event.GetString();
    wxClientDC dcClient(m_panel1);
    m_render(dcClient);
    Refresh();
}

void MyFrame1::m_choice1OnChoice(wxCommandEvent &event) {
    m_chosenFigure = static_cast<unsigned int>(event.GetSelection());
    Refresh();
}

void MyFrame1::m_render(wxClientDC &drawClient) {
    wxBufferedDC dcBuffer(&drawClient);
    PrepareDC(dcBuffer);

    dcBuffer.Clear();

    wxSize center = m_panel1->GetVirtualSize();
    int x{center.GetWidth() / 2};
    int y{center.GetHeight() / 2};
    dcBuffer.SetDeviceOrigin(0, 0);
    const int radius = 20;

    dcBuffer.SetPen(wxPen(wxColor(0, 0, 0), 2));
    dcBuffer.DrawLine(x, y + 30, x, y - 30);
    dcBuffer.DrawLine(x, y - 30, x + 60, y);
    dcBuffer.DrawLine(x, y + 30, x + 20, y + 120);
    dcBuffer.DrawLine(x, y + 30, x - 20, y + 120);

    dcBuffer.DrawCircle(x, y - 30 - radius, radius);
    dcBuffer.DrawCircle(x - 8, y - 30 - radius - 4, radius / 4);
    dcBuffer.DrawCircle(x + 8, y - 30 - radius - 4, radius / 4);


    m_coordsOfStar[0] = wxPoint(x - 100, y - 150);
    m_coordsOfStar[1] = wxPoint(x - 100 + 15, y - 150 + 50);
    m_coordsOfStar[2] = wxPoint(x - 100 - 25, y - 150 + 25);
    m_coordsOfStar[3] = wxPoint(x - 100 + 25, y - 150 + 25);
    m_coordsOfStar[4] = wxPoint(x - 100 - 15, y - 150 + 50);

    if (m_drawBanana) {
        if (m_banana)
            dcBuffer.DrawBitmap(*m_banana, x - 60 - 25, y - m_bananaPlace / 2 - 25);

        dcBuffer.DrawEllipticArc(x - 8, y - 30 - radius + 4, 15, 10, 0, -180);
        dcBuffer.DrawLine(x, y - 30, x - 60, y - m_bananaPlace / 2);

    } else {
        dcBuffer.DrawLine(x, y - 30, x - 60, y - m_bananaPlace / 2);
        dcBuffer.DrawEllipticArc(x - 8, y - 30 - radius + 4, 15, 10, 0, 180);
    }

    dcBuffer.SetPen(wxPen(*m_starColour));
    dcBuffer.SetBrush(wxBrush(*m_starColour));
    if (m_chosenFigure == 0)
        dcBuffer.DrawPolygon(5, m_coordsOfStar, wxWINDING_RULE);
    else if (m_chosenFigure == 1) {
        dcBuffer.SetPen(wxPen(*wxBLACK_PEN));
        dcBuffer.SetBrush(wxBrush(*wxGREY_BRUSH));
        dcBuffer.DrawCircle(wxPoint(x - 100, y - 150 + radius), radius);
        dcBuffer.SetPen(wxPen(*wxWHITE_PEN));
        dcBuffer.SetBrush(wxBrush(*wxWHITE_BRUSH));
        dcBuffer.DrawCircle(wxPoint(x - 100 - 15, y - 150 - 15 + radius), radius / 2);
    } else {
        dcBuffer.SetPen(wxPen(*wxBLACK_PEN));
        dcBuffer.SetBrush(wxBrush(*wxYELLOW_BRUSH));
        dcBuffer.DrawCircle(wxPoint(x - 100, y - 150 + radius), radius);
    }

    dcBuffer.SetPen(wxPen( wxColor(0,0,0), 3));
    dcBuffer.DrawText(m_textToDraw, x - 100, y + 120);
    dcBuffer.SetFont (wxFont(25, wxSWISS, wxITALIC, wxBOLD, false));
    dcBuffer.SetPen(wxPen( wxColor(0,0,0), 20 ,wxPENSTYLE_SOLID ) );
    dcBuffer.DrawRotatedText(m_textToDraw, x + 70, y + 120, 90);
}

MyFrame1::~MyFrame1() {
    // Disconnect Events
    m_panel1->Disconnect(wxEVT_PAINT, wxPaintEventHandler(MyFrame1::m_panelOnPaint), NULL, this);
    m_panel1->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame1::m_panelOnUpdateUI), NULL, this);
    m_button7->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::m_button7OnButtonClick), NULL,
                          this);
    m_checkBox1->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MyFrame1::m_checkBox1OnCheckBox),
                            NULL, this);
    m_button8->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame1::m_button8OnButtonClick), NULL,
                          this);
    m_textCtrl1->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MyFrame1::m_textCtrl1OnText), NULL, this);
    m_scrollBar1->Disconnect(wxEVT_SCROLL_TOP, wxScrollEventHandler(MyFrame1::m_scrollBar1OnScroll), NULL, this);
    m_scrollBar1->Disconnect(wxEVT_SCROLL_BOTTOM, wxScrollEventHandler(MyFrame1::m_scrollBar1OnScroll), NULL, this);
    m_scrollBar1->Disconnect(wxEVT_SCROLL_LINEUP, wxScrollEventHandler(MyFrame1::m_scrollBar1OnScroll), NULL, this);
    m_scrollBar1->Disconnect(wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler(MyFrame1::m_scrollBar1OnScroll), NULL, this);
    m_scrollBar1->Disconnect(wxEVT_SCROLL_PAGEUP, wxScrollEventHandler(MyFrame1::m_scrollBar1OnScroll), NULL, this);
    m_scrollBar1->Disconnect(wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler(MyFrame1::m_scrollBar1OnScroll), NULL, this);
    m_scrollBar1->Disconnect(wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler(MyFrame1::m_scrollBar1OnScroll), NULL, this);
    m_scrollBar1->Disconnect(wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler(MyFrame1::m_scrollBar1OnScroll), NULL,
                             this);
    m_scrollBar1->Disconnect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(MyFrame1::m_scrollBar1OnScroll), NULL, this);
    m_choice1->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(MyFrame1::m_choice1OnChoice), NULL,
                          this);

    delete m_starColour;
}
