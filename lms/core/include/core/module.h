#ifndef SHARED_SHARED_BASE_H
#define SHARED_SHARED_BASE_H
/**
 *TODO rename it to module.h
 */

//#include <core/shared_interface.h>
#include <string>
#include <vector>
#include <core/loader.h>

namespace lms{

class DataManager;
class Module {
public:
    Module() { }
    virtual ~Module() { }
	
    std::string getName() const;
    /**
     * called by the framework itself at module-creation
    */
    bool initializeBase(DataManager* d,Loader::module_entry& loaderEntry);

    /**
     * TODO
     * @brief initialize
     * @param d
     * @return
     */
    virtual bool initialize() = 0;
	virtual bool deinitialize() = 0;
	virtual bool cycle() = 0;

    //TODO: reset method
    // The following implementation is fully backwards compatible:
    // Modules can override reset if they can implement it
    virtual void reset() {}
    // If a module overrides reset() then isResettable() should be overriden to return true
    virtual bool isResettable() { return false; }

protected:
    DataManager* datamanager() { return dm; }
private:
    Loader::module_entry loaderEntry;
	DataManager* dm;
};
}

#endif