#ifndef SQUAREPINE_WINDOW_H
#define SQUAREPINE_WINDOW_H

/**
*/
class Window
{
public:
    /** A combination of these flags is passed to the ComponentPeer constructor. */
    enum StyleFlags
    {
        windowAppearsOnTaskbar      = (1 << 0),    /**< Indicates that the window should have a corresponding
                                                        entry on the taskbar (ignored on MacOSX) */
        windowIsTemporary           = (1 << 1),    /**< Indicates that the window is a temporary popup, like a menu,
                                                        tooltip, etc. */
        windowIgnoresMouseClicks    = (1 << 2),    /**< Indicates that the window should let mouse clicks pass
                                                        through it (may not be possible on some platforms). */
        windowHasTitleBar           = (1 << 3),    /**< Indicates that the window should have a normal OS-specific
                                                        title bar and frame. if not specified, the window will be
                                                        borderless. */
        windowIsResizable           = (1 << 4),    /**< Indicates that the window should have a resizable border. */
        windowHasMinimiseButton     = (1 << 5),    /**< Indicates that if the window has a title bar, it should have a
                                                        minimise button on it. */
        windowHasMaximiseButton     = (1 << 6),    /**< Indicates that if the window has a title bar, it should have a
                                                        maximise button on it. */
        windowHasCloseButton        = (1 << 7),    /**< Indicates that if the window has a title bar, it should have a
                                                        close button on it. */
        windowHasDropShadow         = (1 << 8),    /**< Indicates that the window should have a drop-shadow (this may
                                                        not be possible on all platforms). */
        windowRepaintedExplictly    = (1 << 9),    /**< Not intended for public use - this tells a window not to
                                                        do its own repainting, but only to repaint when the
                                                        performAnyPendingRepaintsNow() method is called. */
        windowIgnoresKeyPresses     = (1 << 10),   /**< Tells the window not to catch any keypresses. This can
                                                        be used for things like plugin windows, to stop them interfering
                                                        with the host's shortcut keys */
        windowIsSemiTransparent     = (1 << 31)    /**< Not intended for public use - makes a window transparent. */
    };

    Window (const std::string& title = "");

    ~Window();

    //==============================================================================
    void setTitle (const std::string& title);

    //==============================================================================
    void update();

    void draw();

    //==============================================================================
    void* getNativeHandle() const;

private:
    //==============================================================================
    class Pimpl;
    Pimpl* pimpl;
};

#endif //SQUAREPINE_WINDOW_H
