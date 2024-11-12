#include "{{.ModuleName}}/{{.ModuleName}}.hpp"
#include <iostream>

// Constructor
{{.ModuleName}}::{{.ModuleName}}() : appName("MyApp"), version("1.0"), isRunning(false) {
    std::cout << "{{.ModuleName}} initialized." << std::endl;
}

// Destructor
{{.ModuleName}}::~{{.ModuleName}}() {
    std::cout << "{{.ModuleName}} shutting down." << std::endl;
}

// Initialization method
bool {{.ModuleName}}::initialize() {
    std::cout << "Initializing application..." << std::endl;
    isRunning = true;
    return isRunning;
}

// Shutdown method
void {{.ModuleName}}::shutdown() {
    std::cout << "Shutting down application..." << std::endl;
    isRunning = false;
}

// Event handling
void {{.ModuleName}}::onEvent(const std::string& event) {
    events.push_back(event);
    std::cout << "Event triggered: " << event << std::endl;
}

// Getter methods
const std::string& {{.ModuleName}}::getAppName() const {
    return appName;
}

const std::string& {{.ModuleName}}::getVersion() const {
    return version;
}

bool {{.ModuleName}}::isAppRunning() const {
    return isRunning;
}
