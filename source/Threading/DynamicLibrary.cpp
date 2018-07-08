#if SQUAREPINE_WINDOWS
bool DynamicLibrary::open (const std::string& name)
{
    close();
    handle = LoadLibraryA (name.c_str());
    return handle != nullptr;
}

void DynamicLibrary::close()
{
    if (handle != nullptr)
    {
        FreeLibrary ((HMODULE) handle);
        handle = nullptr;
    }
}

void* DynamicLibrary::getFunction (const std::string& functionName) noexcept
{
    return handle != nullptr
        ? (void*) GetProcAddress ((HMODULE) handle, functionName.c_str()) //void* cast is required for MinGW
        : nullptr;
}
#else
    #error "TBD: DynamicLibrary"
#endif
