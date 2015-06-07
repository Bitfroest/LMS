#if ! defined(_MSC_VER)
#include <getopt.h>
#endif

#include <string>
#include <vector>

#include "lms/argumenthandler.h"
#include "lms/extra/os.h"

namespace lms {

bool runLevelByName(const std::string &str, RunLevel &runLevel) {
    if (str == "CONFIG" || str == "0") {
        runLevel = RunLevel::CONFIG;
        return true;
    } else if (str == "ENABLE" || str == "1") {
        runLevel = RunLevel::ENABLE;
        return true;
    } else if (str == "CYCLE" || str == "2") {
        runLevel = RunLevel::CYCLE;
        return true;
    }

    return false;
}

std::ostream& operator << (std::ostream &out, RunLevel runLevel) {
    switch(runLevel) {
    case RunLevel::CONFIG:
        out << "CONFIG";
        break;
    case RunLevel::ENABLE:
        out << "ENABLE";
        break;
    case RunLevel::CYCLE:
        out << "CYCLE";
        break;
    }
    return out;
}

ArgumentHandler::ArgumentHandler() : m_loadConfiguration(""),
    m_showHelp(false), m_runLevel(RunLevel::CYCLE),
    m_loggingMinLevel(logging::SMALLEST_LEVEL), m_quiet(false), m_user("") {

    m_user = lms::extra::username();
}

void ArgumentHandler::parseArguments(int argc, char* const*argv) {
#if ! defined(_MSC_VER)
    static const option LONG_OPTIONS[] = {
        {"help", no_argument, 0, 'h'},
        {"run-level", required_argument, 0, 'r'},
        {"logging-min-level", required_argument, 0, 1},
        {"logging-prefix", required_argument, 0, 2},
        {"user", required_argument, 0, 3},
        {"log-file", required_argument, 0, 4},
        {"quiet", no_argument, 0, 'q'}
    };

    opterr = 0;
    int c;
    while ((c = getopt_long(argc, argv, "hr:c:q", LONG_OPTIONS, NULL)) != -1) {
        switch (c) {
            case 'c':
                m_loadConfiguration = optarg;
                break;
            case 'h':  // --help
                m_showHelp = true;
                break;
            case 'r':  // --run-level
                if(! runLevelByName(optarg, m_runLevel)) {
                    std::cerr << "Invalid value for run level " << optarg << std::endl;
                }
                break;
            case 1:  // --logging-min-level
                m_loggingMinLevel = logging::levelFromName(optarg);
                break;
            case 2:  // --logging-prefix
                m_loggingPrefixes.push_back(optarg);
                break;  // Don't forget to break!
            case 3: // --user
                m_user = optarg;
                break;
            case 4: // --log-file
                m_logFile = optarg;
                break;
            case 'q': // --quiet
                m_quiet = true;
                break;
            default:
                std::cerr << "Invalid option" << std::endl;
                m_showHelp = true;
        }
    }
#endif
}

void ArgumentHandler::parseBoolArg(const std::string &argName, bool &arg) {
    if(std::string("true") == optarg) {
        arg = true;
    } else if(std::string("false") == optarg) {
        arg = false;
    } else {
        std::cerr << "Invalid value for " << argName << ": " << optarg << std::endl;
        m_showHelp = true;
    }
}

void ArgumentHandler::printHelp(std::ostream &out) const {
    out << "LMS - Lightweight Modular System\n"
        << "Usage: lms/lms [-h] [-c config]\n"
        << "  -h, --help          Show help\n"
        << "  -c config           Load XML configuration file\n"
        << "                       defaults to framework_conf.xml\n"
        << "  -r, --run-level     Execute until a certain run level\n"
        << "                       valid values: CONFIG, ENABLE, CYCLE\n"
        << "                       defaults to CYCLE\n"
        << "  --user              Set the username, used for config loading\n"
        << "                        defaults to $LOGNAME on linux\n"
        << "                        defaults to $USER on MacOSX\n"
        << "                        defaults to $USERNAME on Windows\n"
        << "  --logging-min-level Filter minimum logging level, e.g. ERROR\n"
        << "  --logging-prefix    Prefix of logging tags to filter\n"
        << "  --quiet             Do not log anything to stdout\n"
        << "  --log-file          Log to the given file\n"
        << std::endl;
}

std::string ArgumentHandler::argLoadConfiguration() const {
    return m_loadConfiguration;
}

bool ArgumentHandler::argHelp() const {
    return m_showHelp;
}

RunLevel ArgumentHandler::argRunLevel() const {
    return m_runLevel;
}

std::vector<std::string> ArgumentHandler::argLoggingPrefixes() const {
    return m_loggingPrefixes;
}

logging::LogLevel ArgumentHandler::argLoggingMinLevel() const {
    return m_loggingMinLevel;
}

std::string ArgumentHandler::argUser() const {
    return m_user;
}

std::string ArgumentHandler::argLogFile() const {
    return m_logFile;
}

bool ArgumentHandler::argQuiet() const {
    return m_quiet;
}

}  // namespace lms
