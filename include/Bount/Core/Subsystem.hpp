/**
 * @file Subsystem.hpp
 * @brief Standard sublibrary for managing and creating subsystems.
 * @author Brandon Foster (Paradox Gene)
 */

#ifndef BOUNT_CORE_SUBSYSTEM_HPP
#define BOUNT_CORE_SUBSYSTEM_HPP

#include "Bount/Core/DesignPatterns.hpp"

namespace Bount
{
/** @brief
 * Abstract class for creating concrete subsystems.
 * All subsystems must inherit from this class to operate properly within the Bount Framework.
 * A Bount subsystem is also a singleton.
 */
template <typename T>
class SubsystemBase : DesignPattern::SingletonBase<T>
{
    Bool _startingUp, _started, _shuttingDown;

public:
    SubsystemBase()
        : _startingUp(false), _started(false), _shuttingDown(false)
    {
    }

    /** @brief Starts up the Subsystem. */
    void startup()
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
            throw ex;
        }
        if (_startingUp) _started = true;
    }
    /** @return True if the Subsystem is in the process of starting. */
    Bool isStartingUp() const noexcept
    {
        return _startingUp;
    }
    /** @return True if the Subsystem has successfully started. */
    Bool hasStartedUp() const noexcept
    {
        return _started;
    }

    /** @brief Shuts down the Subsystem. */
    void shutdown() noexcept
    {
        if (!(_startingUp || _started) || _shuttingDown) return;

        _shuttingDown = true;
        onShutdown();
        _shuttingDown = _startingUp = _started = false;
    }
    /** @return True if the Subsystem is in the process of shutting down. */
    Bool isShuttingDown() const noexcept
    {
        return _shuttingDown;
    }
    /** @return True if the Subsystem has successfully shutdown or never started. */
    Bool hasShutdown() const noexcept
    {
        return !_startingUp && !_started && !_shuttingDown;
    }

protected:
    virtual void onStartup() = 0;
    virtual void onShutdown() = 0;

};

/** @brief Final behavior extension for a subsystem.*/
template <typename T>
using Subsystem = DesignPattern::Singleton<T>;
}
#endif