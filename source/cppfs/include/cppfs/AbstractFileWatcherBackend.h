
#pragma once


#include <memory>

#include <cppfs/cppfs.h>


namespace cppfs
{


class FileHandle;
class FileWatcher;
class AbstractFileSystem;


/**
*  @brief
*    Interface for file watchers
*/
class CPPFS_API AbstractFileWatcherBackend
{
    friend class FileWatcher;


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] fileWatcher
    *    File watcher that owns the backend (must NOT be null!)
    */
    AbstractFileWatcherBackend(FileWatcher * fileWatcher);

    /**
    *  @brief
    *    Destructor
    */
    virtual ~AbstractFileWatcherBackend();

    /**
    *  @brief
    *    Get file system
    *
    *  @return
    *    File system (must NOT be null)
    */
    virtual AbstractFileSystem * fs() const = 0;

    /**
    *  @brief
    *    Watch file handle
    *
    *  @param[in] fh
    *    File handle
    *  @param[in] events
    *    Events that are watched (combination of FileEvent values)
    *  @param[in] recursive
    *    Watch file system recursively? (only relevant if fileHandle points to a directory)
    */
    virtual void add(FileHandle & fh, unsigned int events, RecursiveMode recursive) = 0;

    /**
    *  @brief
    *    Start watching files
    *
    *  @param[in] timeoutMilliSeconds
    *    timeout value in milliseconds, if less than zero, timeout is infinite
    * 
    *  @remarks
    *    This function shall watch the file system and block until one or more
    *    events have occured, or if the timeout has been exceeded (timeout >= 0).
    *    For each event, onFileEvent has to be called with the type of the event and
    *    a file handle to the file or directory. After all events have been
    *    processed, the function shall return.
    */
    virtual void watch(int timeoutMilliSeconds) = 0;


protected:
    /**
    *  @brief
    *    Called on each file event
    *
    *  @param[in] fh
    *    File handle
    *  @param[in] event
    *    Type of event that has occured
    */
    void onFileEvent(FileHandle & fh, FileEvent event);


protected:
    FileWatcher * m_fileWatcher; ///< File watcher that owns the backend (never null)
};


} // namespace cppfs
