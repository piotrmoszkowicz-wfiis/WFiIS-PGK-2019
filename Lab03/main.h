#include <wx/wx.h>

class HelloWorldApp : public wxApp
{
public:
    virtual bool OnInit();
};

DECLARE_APP(HelloWorldApp)