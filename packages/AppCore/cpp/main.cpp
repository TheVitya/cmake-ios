#include "AppCore/AppCore.hpp"
#include <iostream>

// Example usage
int main() {
    AppCore app;

    if (app.initialize()) {
        std::cout << app.getAppName() << " version " << app.getVersion() << " is running." << std::endl;

        // Triggering events
        app.onEvent("UserLoggedIn");
        app.onEvent("SettingsChanged");

        // Shutdown the application
        app.shutdown();
    }

    return 0;
}
