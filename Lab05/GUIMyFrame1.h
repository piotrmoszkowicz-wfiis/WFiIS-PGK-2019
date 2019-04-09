#pragma once

#include "GUI.h"
#include "vecmat.h"

#include <cmath>
#include <fstream>
#include <vector>

#include <wx/filedlg.h>
#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/colourdata.h>
#include <wx/colordlg.h>

/** Implementing MyFrame1 */
class GUIMyFrame1 : public MyFrame1 {
public:
    /** Constructor */
    GUIMyFrame1(wxWindow *parent);

    //// end generated class members
    void Repaint();
protected:
    // Handlers for MyFrame1 events.
    void WxPanel_Repaint(wxUpdateUIEvent &event);
    void m_button_load_geometry_click(wxCommandEvent &event);
    void Scrolls_Updated(wxScrollEvent &event);
private:
    Matrix4 getRotationX(const double angle) const;
    Matrix4 getRotationY(const double angle) const;
    Matrix4 getRotationZ(const double angle) const;
    Matrix4 getScale(const double xScale, const double yScale, const double zScale) const;
    Matrix4 getTranslation(const double xTranslation, const double yTranslation, const double zTranslation) const;
};

