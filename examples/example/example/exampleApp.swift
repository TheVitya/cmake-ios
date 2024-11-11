//
//  exampleApp.swift
//  example
//
//  Created by Viktor Nagy on 21.8.24..
//

import SwiftUI
import Test

@main
struct exampleApp: App {
    var body: some Scene {
        WindowGroup {
            ContentView().onAppear {
                var test = Test()
                test.test()
            }
        }
    }
}
