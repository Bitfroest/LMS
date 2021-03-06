#ifndef LMS_FRAMEWORK_H
#define LMS_FRAMEWORK_H

#include <lms/datamanager.h>
#include <lms/signalhandler.h>
#include <lms/argumenthandler.h>
#include <lms/executionmanager.h>
#include <lms/logger.h>
#include "lms/clock.h"
#include "pugixml.hpp"
#include "lms/extra/file_monitor.h"
#include "lms/deprecated.h"

/**
 *TODO: Framework config that contains max threads for executionManager etc.
 */
namespace lms {

/**
 * @brief Main entry point into the lightweight module system.
 *
 * Create an object of this class and you will start the framwork.
 */
class Framework : public SignalHandler::Listener {
public:
    /**
     * @brief executionPath absolute path to running framework (folder that contains core and external)
     */
    DEPRECATED static std::string programDirectory();

    /**
     * @brief Framework::externalDirectory absolute path to the external directory
     *
     * This attribute is deprecated.
     */

    static std::string externalDirectory;
    /**
     * @brief Framework::configsDirectory absolute path to the configs directory
     *
     * This attribute is deprecated.
     */
    static std::string configsDirectory;

    /**
     * @brief Instantiate the framework, initiate datamanager and
     * execution manager and start the main loop.
     *
     * @param arguments parsed command line arguments
     */
    Framework(const ArgumentHandler& arguments);

    /**
     * @brief Destroy execution manager.
     */
    ~Framework();

    ExecutionManager& executionManager();
    Clock & clock();
private:
    logging::Logger logger;

    ArgumentHandler argumentHandler;
    ExecutionManager m_executionManager;

    Clock m_clock;

    /**
     * @brief running just for main-while-loop if it's set to false, the programm will terminate
     */
    bool running;

    extra::FileMonitor configMonitor;
    bool configMonitorEnabled;

    /**
     * @brief signal called by the system (Segfaults etc)
     * @param s
     */
    void signal(int s);
};

}  // namespace lms

#endif /* LMS_FRAMEWORK_H */
