//
//  exampleApp.swift
//  example
//
//  Created by Viktor Nagy on 21.8.24..
//

import SwiftUI
import AppCore
import AppCoreFramework

@main
struct exampleApp: App {
    var body: some Scene {
        WindowGroup {
            ContentView().onAppear {
                var app = AppCore()
                app.initialize()
                var swift = AppCoreSwift()
                swift.test()
            }
        }
    }
}
