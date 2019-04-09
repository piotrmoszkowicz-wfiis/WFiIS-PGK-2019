#include "GUIMyFrame1.h"

struct Point {
    float x, y, z;

    Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Color {
    int R, G, B;

    Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment {
    Point begin, end;
    Color color;

    Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end), color(_color) {}
};

std::vector<Segment> data;

GUIMyFrame1::GUIMyFrame1(wxWindow *parent)
        :
        MyFrame1(parent) {
    m_button_load_geometry->SetLabel(_("Wczytaj Geometri\u0119"));
    m_staticText25->SetLabel(_("Obr\u00F3t X:"));
    m_staticText27->SetLabel(_("Obr\u00F3t Y:"));
    m_staticText29->SetLabel(_("Obr\u00F3t Z:"));

    WxSB_TranslationX->SetRange(0, 200);
    WxSB_TranslationX->SetValue(100);
    WxSB_TranslationY->SetRange(0, 200);
    WxSB_TranslationY->SetValue(100);
    WxSB_TranslationZ->SetRange(0, 200);
    WxSB_TranslationZ->SetValue(100);

    WxSB_RotateX->SetRange(0, 360);
    WxSB_RotateX->SetValue(0);
    WxSB_RotateY->SetRange(0, 360);
    WxSB_RotateY->SetValue(0);
    WxSB_RotateZ->SetRange(0, 360);
    WxSB_RotateZ->SetValue(0);

    WxSB_ScaleX->SetRange(1, 200);
    WxSB_ScaleX->SetValue(100);
    WxSB_ScaleY->SetRange(1, 200);
    WxSB_ScaleY->SetValue(100);
    WxSB_ScaleZ->SetRange(1, 200);
    WxSB_ScaleZ->SetValue(100);
}

void GUIMyFrame1::WxPanel_Repaint(wxUpdateUIEvent &event) {
    Repaint();
}

void GUIMyFrame1::m_button_load_geometry_click(wxCommandEvent &event) {
    wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"),
                                  wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (WxOpenFileDialog.ShowModal() == wxID_OK) {
        double x1, y1, z1, x2, y2, z2;
        int r, g, b;

        std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
        if (in.is_open()) {
            data.clear();
            while (!in.eof()) {
                in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
                data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
            }
            in.close();
        }
    }
}

void GUIMyFrame1::Scrolls_Updated(wxScrollEvent &event) {
    WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationX->GetValue() - 100) / 50.0));
    WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationY->GetValue() - 100) / 50.0));
    WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationZ->GetValue() - 100) / 50.0));

    WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
    WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
    WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

    WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
    WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
    WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));


    Repaint();
}

inline Matrix4 GUIMyFrame1::getRotationX(const double angle) const {
    Matrix4 m;
    m.data[0][0] = 1;
    m.data[1][1] = m.data[2][2] = std::cos(angle);
    m.data[1][2] = -std::sin(angle);
    m.data[2][1] = std::sin(angle);
    return m;
}

inline Matrix4 GUIMyFrame1::getRotationY(const double angle) const {
    Matrix4 m;
    m.data[0][0] = m.data[2][2] = std::cos(angle);
    m.data[0][2] = -std::sin(angle);
    m.data[1][1] = 1;
    m.data[2][0] = std::sin(angle);
    return m;
}

inline Matrix4 GUIMyFrame1::getRotationZ(const double angle) const {
    Matrix4 m;
    m.data[0][0] = m.data[1][1] = std::cos(angle);
    m.data[0][1] = -std::sin(angle);
    m.data[1][0] = std::sin(angle);
    m.data[2][2] = 1;
    return m;
}

inline Matrix4 GUIMyFrame1::getScale(const double xScale, const double yScale, const double zScale) const {
    Matrix4 m;
    m.data[0][0] = xScale;
    m.data[1][1] = yScale;
    m.data[2][2] = zScale;
    return m;
}

inline Matrix4 GUIMyFrame1::getTranslation(const double xTranslation, const double yTranslation,
                                           const double zTranslation) const {
    Matrix4 m;
    m.data[0][0] = m.data[1][1] = m.data[2][2] = 1;
    m.data[0][3] = xTranslation;
    m.data[1][3] = -yTranslation;
    m.data[2][3] = zTranslation;
    return m;
}

void GUIMyFrame1::Repaint() {
    wxClientDC dc(WxPanel);
    wxBufferedDC dcBuff(&dc);

    int w, h;
    WxPanel->GetSize(&w, &h);

    dcBuff.SetBackground(*wxWHITE_BRUSH);
    dcBuff.Clear();

    const double scaleX = WxSB_ScaleX->GetValue() / 100.0;
    const double scaleY = WxSB_ScaleY->GetValue() / 100.0;
    const double scaleZ = WxSB_ScaleZ->GetValue() / 100.0;

    auto rotateX = static_cast<double>(WxSB_RotateX->GetValue()) / WxSB_RotateX->GetMax() * 2.0 * M_PI;
    auto rotateY = static_cast<double>(WxSB_RotateY->GetValue()) / WxSB_RotateY->GetMax() * 2.0 * M_PI;
    auto rotateZ = static_cast<double>(WxSB_RotateZ->GetValue()) / WxSB_RotateZ->GetMax() * 2.0 * M_PI;

    const double transX = (WxSB_TranslationX->GetValue() - 100.0) / 50.0;
    const double transY = (WxSB_TranslationY->GetValue() - 100.0) / 50.0;
    const double transZ = (WxSB_TranslationZ->GetValue() - 100.0) / 50.0;

    const Matrix4 scaleMatrix = getScale(scaleX, scaleY, scaleZ);
    const Matrix4 xRotationMatrix = getRotationX(rotateX);
    const Matrix4 yRotationMatrix = getRotationY(rotateY);
    const Matrix4 zRotationMatrix = getRotationZ(rotateZ);
    const Matrix4 rotationMatrix = xRotationMatrix * yRotationMatrix * zRotationMatrix;
    const Matrix4 translationMatrix = getTranslation(transX, transY, transZ);
    const Matrix4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;

    for (const auto& el : data) {
        Vector4 s, e;

        s.Set(el.begin.x, el.begin.y, el.begin.z);
        s = transformationMatrix * s;

        e.Set(el.end.x, el.end.y, el.end.z);
        e = transformationMatrix * e;

        dcBuff.SetPen(wxPen(wxColour(el.color.R, el.color.G, el.color.B)));

        dcBuff.DrawLine(
                (w / 2) + ((w / 2) * s.GetX() / std::abs(1.0 + (s.GetZ() / 2))),
                (h / 2) + ((h / 2) * s.GetY() / std::abs(1.0 + (s.GetZ() / 2))),
                (w / 2) + ((w / 2) * e.GetX() / std::abs(1.0 + (e.GetZ() / 2))),
                (h / 2) + ((h / 2) * e.GetY() / std::abs(1.0 + (e.GetZ() / 2)))
        );
    }
}