#ifndef LMS_TYPE_MODULE_CONFIG_H
#define LMS_TYPE_MODULE_CONFIG_H

#include <unordered_map>
#include <sstream>

namespace lms { namespace type {

/**
 * @brief ModuleConfig is a property map
 * where modules can load their configuration from.
 *
 * @author Hans Kirchner
 */
class ModuleConfig {
public:
    /* Default contructors and assignment operators */
    ModuleConfig() = default;
    ModuleConfig(const ModuleConfig &) = default;
    ModuleConfig(ModuleConfig &&) = default;
    ModuleConfig& operator= (const ModuleConfig &) = default;
    ModuleConfig& operator= (ModuleConfig &&) = default;

    /**
     * @brief Load a config file from the given path.
     *
     * The format is KEY = VALUE.
     * Empty lines are ignored.
     * Comment lines start with '#'.
     *
     * @param path file path to the config file
     * @return false if the file could not be opened, true otherwise
     */
    bool loadFromFile(const std::string &path);

    /**
     * @brief Return the value by the given config key.
     *
     * If the key is not found the default constructor
     * of T is invoked the that object is returned.
     *
     * If you want to check if a key is in the config file
     * use hasKey()
     *
     * @param key the key to look for
     * @return value of type T
     */
    template<typename T>
    T get(const std::string &key) const {
        T result;
        const auto it = properties.find(key);

        if(it == properties.end()) {
            return result;
        } else {
            std::istringstream stream(it->second);
            stream >> result;
            return result;
        }
    }

    /**
     * @brief Check if the given key is available.
     * @param key the key to look for
     * @return true, if the key is found
     */
    bool hasKey(const std::string &key) const {
        return properties.count(key) == 1;
    }

private:
    std::unordered_map<std::string, std::string> properties;
};

} // namespace type
} // namespace lms

#endif /* LMS_TYPE_MODULE_CONFIG_H */