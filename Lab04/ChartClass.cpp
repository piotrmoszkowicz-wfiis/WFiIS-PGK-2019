#define _USE_MATH_DEFINES
#include <wx/dc.h>
#include <iostream>
#include <memory>
#include <cmath>

#include "ChartClass.h"
#include "vecmat.h"

ChartClass::ChartClass(std::shared_ptr<ConfigClass> c) {
    cfg = std::move(c);
    x_step = 200;
}

void ChartClass::Set_Range() {
    double xmin = 9999.9, xmax = -9999.9, ymin = 9999.9, ymax = -9999.9;
    double x, y, step;
    int i;

    xmin = cfg->Get_x_start();
    xmax = cfg->Get_x_stop();

    step = (cfg->Get_x_stop() - cfg->Get_x_start()) / (double) x_step;
    x = cfg->Get_x_start();

    for (i = 0; i <= x_step; i++) {
        y = GetFunctionValue(x);
        if (y > ymax) ymax = y;
        if (y < ymin) ymin = y;
        x = x + step;
    }

    y_min = ymin;
    y_max = ymax;
    x_min = xmin;
    x_max = xmax;
}


double ChartClass::GetFunctionValue(double x) {
    if (cfg->Get_F_type() == 1) return x * x;
    if (cfg->Get_F_type() == 2) return 0.5 * exp(4 * x - 3 * x * x);
    return x + sin(x * 4.0);
}

double ChartClass::Get_Y_min() {
    Set_Range();
    return y_min;
}

double ChartClass::Get_Y_max() {
    Set_Range();
    return y_max;
}

inline Matrix ChartClass::getRotationMatrix(int w, int h) {
    Matrix rotationMatrix;

    const auto cosValue = std::cos(cfg->Get_Alpha() * M_PI / -180.0);
    const auto sinValue = std::sin(cfg->Get_Alpha() * M_PI / -180.0);

    rotationMatrix.data[0][0] = rotationMatrix.data[1][1] = cosValue;
    rotationMatrix.data[0][1] = sinValue;
    rotationMatrix.data[1][0] = -sinValue;

    if (cfg->RotateScreenCenter()) {
        rotationMatrix.data[0][2] = (w / 2.0) * (1 - cosValue) + (h / 2.0) * (-sinValue);
        rotationMatrix.data[1][2] = (w / 2.0) * sinValue + (h / 2.0) * (1 - cosValue);
    } else {
        Matrix scaleMatrix = getScaleMatrix(w, h);
        rotationMatrix.data[0][2] = scaleMatrix.data[0][2] * (1 - cosValue) + scaleMatrix.data[1][2] * (-sinValue);
        rotationMatrix.data[1][2] = scaleMatrix.data[0][2] * sinValue + scaleMatrix.data[1][2] * (1 - cosValue);
    }

    return rotationMatrix;
}

inline Matrix ChartClass::getScaleMatrix(int w, int h) {
    Matrix scaleMatrix;

    scaleMatrix.data[0][0] = (w - 20.0) / (cfg->Get_x1() - cfg->Get_x0());
    scaleMatrix.data[1][1] = (h - 20.0) / (cfg->Get_y1() - cfg->Get_y0());
    scaleMatrix.data[0][2] = 10.0 - scaleMatrix.data[0][0] * cfg->Get_x0();
    scaleMatrix.data[1][2] = 10.0 - scaleMatrix.data[1][1] * cfg->Get_y0();

    return scaleMatrix;
}

inline Matrix ChartClass::getTranslationMatrix() {
    Matrix translationMatrix;

    translationMatrix.data[0][0] = translationMatrix.data[1][1] = 1;
    translationMatrix.data[0][2] = cfg->Get_dX();
    translationMatrix.data[1][2] = -cfg->Get_dY();

    return translationMatrix;
}

inline void ChartClass::drawRotatedText(wxDC *dc, Matrix transformMatrix, wxString text, double x, double y, int h) {
    Vector rotationVector;
    rotationVector.Set(x, y);
    rotationVector = transformMatrix * rotationVector;
    dc->DrawRotatedText(text, static_cast<int>(rotationVector.GetX()), static_cast<int>(h - rotationVector.GetY()),
                        -cfg->Get_Alpha());
}

void ChartClass::line2d(wxDC *dc, Matrix t, double x1, double y1, double x2, double y2, int w, int h) {
	Vector startPoint, endPoint;

	startPoint.Set(x1, y1);
	endPoint.Set(x2, y2);

	startPoint = t * startPoint;
	endPoint = t * endPoint;

	dc->DrawLine(static_cast<int>(startPoint.GetX()), static_cast<int>(h - startPoint.GetY()),
		static_cast<int>(endPoint.GetX()), static_cast<int>(h - endPoint.GetY()));
}

void ChartClass::drawChartAxis(wxDC *dc, Matrix transformMatrix, int w, int h) {
    line2d(dc, transformMatrix, x_min, 0, x_max, 0, w, h); // X axis

    double deltaX = 1.0 + static_cast<int>((cfg->Get_x1() - cfg->Get_x0()) / 10);

	double diff = (cfg->Get_x1() - cfg->Get_x0()) / 4;

    for (double x = x_min + diff; x < x_max; x += (deltaX / 2)) {
		if (x == 0 || x >= 2.0) {
			continue;
		}
        line2d(dc, transformMatrix, x, -0.05, x, 0.05, w, h);
        drawRotatedText(dc, transformMatrix, wxString::Format(wxT("%.2f"), x), x - 0.001, -0.1, h);
    }

    line2d(dc, transformMatrix, cfg->Get_x_stop(), 0, cfg->Get_x_stop() - 0.05, 0.05, w, h);
    line2d(dc, transformMatrix, cfg->Get_x_stop(), 0, cfg->Get_x_stop() - 0.05, -0.05, w, h); //arrow x
	
	line2d(dc, transformMatrix, 0, y_min, 0, y_max, w, h);
	double deltaY = 1.0 + static_cast<int>((cfg->Get_y1() - cfg->Get_y0()) / 20);

    for (double y = y_min; y < y_max; y += (deltaY)) {
		if (y == 0 || y >= 2.0) {
			continue;
		}
        line2d(dc, transformMatrix, -0.05, y, 0.05, y, w, h);
        drawRotatedText(dc, transformMatrix, wxString::Format(wxT("%.2f"), y), 0.1, y - 0.001, h);
    }

    line2d(dc, transformMatrix, 0, y_max, 0.05, y_max - 0.05, w, h);
    line2d(dc, transformMatrix, 0, y_max, -0.05, y_max - 0.05, w, h); //arrow y
}

void ChartClass::Draw(wxDC *dc, int w, int h) {
	Set_Range();
    dc->SetBackground(wxBrush(*wxWHITE));
    dc->Clear();
    dc->SetPen(*wxRED_PEN);
    dc->DrawRectangle(10, 10, w - 20, h - 20);
	dc->SetClippingRegion(wxRect(10, 10, w - 20, h - 20));
    dc->SetFont(*wxSMALL_FONT);
    dc->SetPen(*wxBLUE_PEN);

    Matrix transformationMatrix = cfg->RotateScreenCenter() ? getRotationMatrix(w, h) * getTranslationMatrix() *
                                                              getScaleMatrix(w, h) : getTranslationMatrix() *
                                                                                     getRotationMatrix(w, h) *
                                                                                     getScaleMatrix(w, h);

    drawChartAxis(dc, transformationMatrix, w, h);

    dc->SetPen(*wxGREEN_PEN);
    const double deltaX = (cfg->Get_x1() - cfg->Get_x0()) / x_step;
    for (double x = cfg->Get_x_start(); x < cfg->Get_x_stop(); x += deltaX) {
        line2d(dc, transformationMatrix, x, GetFunctionValue(x), x + deltaX, GetFunctionValue(x + deltaX), w, h);
    }
}