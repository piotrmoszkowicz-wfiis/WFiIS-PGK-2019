#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1(wxWindow *parent)
        :
        MyFrame1(parent) {
    m_staticText1->SetLabel(_(L"Jasno\u015B\u0107"));
    m_b_threshold->SetLabel(_(L"Pr\u00F3g 128"));
    this->SetBackgroundColour(wxColor(192, 192, 192));
    m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
    m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
}

void GUIMyFrame1::m_scrolledWindow_update(wxUpdateUIEvent &event) {
    Repaint();
}

void GUIMyFrame1::m_b_grayscale_click(wxCommandEvent &event) {
    Img_Cpy = Img_Org.Copy().ConvertToGreyscale();
}

void GUIMyFrame1::m_b_blur_click(wxCommandEvent &event) {
    Img_Cpy = Img_Org.Copy().Blur(7);
}

void GUIMyFrame1::m_b_mirror_click(wxCommandEvent &event) {
    Img_Cpy = Img_Org.Copy().Mirror();
}

void GUIMyFrame1::m_b_replace_click(wxCommandEvent &event) {
    Img_Cpy = Img_Org.Copy();
    Img_Cpy.Replace(254, 0, 0, 0, 0, 255);
}

void GUIMyFrame1::m_b_rescale_click(wxCommandEvent &event) {
    Img_Cpy = Img_Org.Copy().Rescale(320, 240);
}

void GUIMyFrame1::m_b_rotate_click(wxCommandEvent &event) {
    Img_Cpy = Img_Org.Copy().Rotate((30.0 * M_PI) / 180.0, wxPoint(Img_Org.GetWidth() / 2, Img_Org.GetHeight() / 2));
}

void GUIMyFrame1::m_b_rotate_hue_click(wxCommandEvent &event) {
    Img_Cpy = Img_Org.Copy();
    Img_Cpy.RotateHue(0.5);
}

void GUIMyFrame1::m_b_mask_click(wxCommandEvent &event) {
    Img_Cpy = Img_Org.Copy();
    Img_Cpy.SetMaskFromImage(Img_Mask, 0, 0, 0);
}

void GUIMyFrame1::m_s_brightness_scroll(wxScrollEvent &event) {
    Brightness(m_s_brightness->GetValue() - 100);
    Repaint();
}

void GUIMyFrame1::m_s_contrast_scroll(wxScrollEvent &event) {
    Contrast(m_s_contrast->GetValue() - 100);
    Repaint();
}

void GUIMyFrame1::m_b_prewitt_click(wxCommandEvent &event) {
    Img_Cpy = Img_Org.Copy();
    auto newPixels = Img_Cpy.GetData();
    auto oldPixels = new unsigned char[Img_Cpy.GetHeight() * Img_Cpy.GetWidth() * 3];

    for (unsigned int i = 0; i < Img_Cpy.GetHeight() * Img_Cpy.GetWidth() * 3; i++) {
        oldPixels[i] = newPixels[i];
    }

    for (unsigned int i = 1; i < Img_Cpy.GetHeight() - 1; ++i) {
        for (unsigned int j = 1; j < Img_Cpy.GetWidth() - 1; ++j) {
            for (unsigned int k = 0; k < 3; ++k) {
                int val = 0;
                val += oldPixels[k + i * Img_Cpy.GetWidth() * 3 + (j + 1) * 3];
                val -= oldPixels[k + i * Img_Cpy.GetWidth() * 3 + (j - 1) * 3];
                val += oldPixels[k + (i + 1) * Img_Cpy.GetWidth() * 3 + (j + 1) * 3];
                val -= oldPixels[k + (i + 1) * Img_Cpy.GetWidth() * 3 + (j - 1) * 3];
                val += oldPixels[k + (i - 1) * Img_Cpy.GetWidth() * 3 + (j + 1) * 3];
                val -= oldPixels[k + (i - 1) * Img_Cpy.GetWidth() * 3 + (j - 1) * 3];
                newPixels[k + i * Img_Cpy.GetWidth() * 3 + j * 3] = static_cast<unsigned char>(std::fabs(val) / 3.0);
            }
        }
    }

    delete[] oldPixels;
}

void GUIMyFrame1::m_b_threshold_click(wxCommandEvent &event) {
    Img_Cpy = Img_Org.Copy();
    auto pixels = Img_Cpy.GetData();
    for (unsigned int i = 0; i < Img_Cpy.GetWidth() * Img_Cpy.GetHeight() * 3; ++i) {
        pixels[i] = pixels[i] < 128 ? 0 : 255;
    }
}


void GUIMyFrame1::Contrast(int value) {
    Img_Cpy = Img_Org.Copy();
    auto pixels = Img_Cpy.GetData();

    const double contrast = (value + 100.0) / (101.0 - value);

    for (unsigned int i = 0; i < Img_Cpy.GetWidth() * Img_Cpy.GetHeight() * 3; ++i) {
        int v = static_cast<int>(((pixels[i] - 255.0) / 2.0) * contrast + (255.0/2.0));
        if (v > 255) {
            v = 255;
        } else if (v < 0) {
            v = 0;
        }
        pixels[i] = v;
    }
}

void GUIMyFrame1::Repaint() {
    wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
    wxClientDC dc(m_scrolledWindow);   // Pobieramy kontekst okna
    m_scrolledWindow->DoPrepareDC(dc); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
    dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
}

void GUIMyFrame1::Brightness(int value) {
    Img_Cpy = Img_Org.Copy();
    auto pixels = Img_Cpy.GetData();

    for (unsigned int i = 0; i < Img_Cpy.GetWidth() * Img_Cpy.GetHeight() * 3; ++i) {
        int v = pixels[i] + value;
        if (v > 255) {
            v = 255;
        } else if (v < 0) {
            v = 0;
        }
        pixels[i] = v;
    }
}