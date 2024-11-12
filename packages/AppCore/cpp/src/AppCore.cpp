#include "AppCore/AppCore.hpp"
#include <iostream>

// Constructor
AppCore::AppCore() : appName("MyApp"), version("1.0"), isRunning(false) {
    std::cout << "AppCore initialized." << std::endl;
}

// Destructor
AppCore::~AppCore() {
    std::cout << "AppCore shutting down." << std::endl;
}

// Initialization method
bool AppCore::initialize() {
    std::cout << "Initializing application..." << std::endl;
    isRunning = true;
    return isRunning;
}

// Shutdown method
void AppCore::shutdown() {
    std::cout << "Shutting down application..." << std::endl;
    isRunning = false;
}

// Event handling
void AppCore::onEvent(const std::string& event) {
    events.push_back(event);
    std::cout << "Event triggered: " << event << std::endl;
}

// Getter methods
const std::string& AppCore::getAppName() const {
    return appName;
}

const std::string& AppCore::getVersion() const {
    return version;
}

bool AppCore::isAppRunning() const {
    return isRunning;
}
