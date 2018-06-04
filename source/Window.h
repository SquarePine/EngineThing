#ifndef SQUAREPINE_WINDOW_H
#define SQUAREPINE_WINDOW_H

class Window
{
public:
    Window();
    ~Window();

private:
    //==============================================================================
    class Pimpl;
    Pimpl* pimpl;
};

#endif //SQUAREPINE_WINDOW_H
