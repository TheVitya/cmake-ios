#include "{{.ModuleName}}/{{.ModuleName}}.hpp"
#include <iostream>

// Example usage
int main() {
    {{.ModuleName}} app;

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
