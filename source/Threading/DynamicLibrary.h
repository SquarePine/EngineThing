#ifndef DYNAMIC_LIBRARY_H
#define DYNAMIC_LIBRARY_H

class DynamicLibrary
{
public:
    /** Creates an unopened DynamicLibrary object.
        Call open() to actually open one.
    */
    DynamicLibrary() noexcept : handle (nullptr) {}

    /**
    */
    DynamicLibrary (const std::string& name) : handle (nullptr) { open (name); }

#if 0
    /** Move constructor */
    DynamicLibrary (DynamicLibrary&& other) noexcept :
        handle (nullptr)
    {
        std::swap (handle, other.handle);
    }
#endif

    /** Destructor.

        If a library is currently open, it will be closed when this object is destroyed.
    */
    ~DynamicLibrary() { close(); }

    /** Opens a DLL.

        The name and the method by which it gets found is of course platform-specific, and
        may or may not include a path, depending on the OS.

        If a library is already open when this method is called, it will first close the library
        before attempting to load the new one.

        @returns true if the library was successfully found and opened.
    */
    bool open (const std::string& name);

    /** Releases the currently-open DLL, or has no effect if none was open. */
    void close();

    /** Tries to find a named function in the currently-open DLL, and returns a pointer to it.
        If no library is open, or if the function isn't found, this will return a null pointer.
    */
    void* getFunction (const std::string& functionName) noexcept;

    /** Returns the platform-specific native library handle.
        You'll need to cast this to whatever is appropriate for the OS that's in use.
    */
    void* getNativeHandle() const noexcept { return handle; }

private:
    void* handle;
};

#endif //DYNAMIC_LIBRARY_H
