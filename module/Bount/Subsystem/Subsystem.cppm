module;

#include "Bount/Subsystem/Generic.hpp"

export module Bount.Subsystem;
export import Bount.Singleton;
export namespace Bount::Subsystem
{
template <typename T>
class Generic : public Singleton::Generic<T>
{
    Bool _startingUp, _started, _shuttingDown;

    Generic(const Generic&) = delete;
    Generic& operator=(const Generic&) = delete;

public:
    friend class Singleton::Generic<T>;

    Generic() noexcept;
    ~Generic() noexcept;
    
    /** @brief Starts up the Subsystem. */
    void startup();

    /** @return True if the Subsystem is in the process of starting. */
    Bool isStartingUp() const noexcept;
    /** @return True if the Subsystem has successfully started. */
    Bool hasStartedUp() const noexcept;

    /** @brief Shuts down the Subsystem. */
    void shutdown() noexcept;

    /** @return True if the Subsystem is in the process of shutting down. */
    Bool isShuttingDown() const noexcept;
    /** @return True if the Subsystem has successfully shutdown or never started. */
    Bool hasShutdown() const noexcept;

protected:
    virtual void onStartup() = 0;
    virtual void onShutdown() noexcept = 0;
};   
}

export namespace Bount::Subsystem
{
template <typename T>
Generic<T>::Generic() noexcept
    : _startingUp(false)
    , _started(false)
    , _shuttingDown(false)
{
}

template <typename T>
Generic<T>::~Generic() noexcept
{
    shutdown();
}

template <typename T>
void Generic<T>::startup()
{
    if (_startingUp || _started) return;

    _startingUp = true;
    try
    {
        onStartup();
    }
    catch (const std::exception& ex)
    {
        _startingUp = false;
        std::cerr << ex.what() << "\n";
        onShutdown();
        throw ex;
    }
    if (_startingUp) _started = true;
}

template <typename T>
Bool Generic<T>::isStartingUp() const noexcept
{
    return _startingUp;
}

template <typename T>
Bool Generic<T>::hasStartedUp() const noexcept
{
    return _started;
}

template <typename T>
void Generic<T>::shutdown() noexcept
{
    if (!(_startingUp || _started) || _shuttingDown) return;

    _shuttingDown = true;
    onShutdown();
    _shuttingDown = _startingUp = _started = false;
}

template <typename T>
Bool Generic<T>::isShuttingDown() const noexcept
{
    return _shuttingDown;
}

template <typename T>
Bool Generic<T>::hasShutdown() const noexcept
{
    return !_startingUp && !_started && !_shuttingDown;
}

template <typename T>
void Generic<T>::onStartup()
{
}

template <typename T>
void Generic<T>::onShutdown() noexcept
{    
}
}
