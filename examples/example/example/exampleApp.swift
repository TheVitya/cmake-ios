//
//  exampleApp.swift
//  example
//
//  Created by Viktor Nagy on 21.8.24..
//

import SwiftUI
import AppCore
import AppCoreFramework

func getBaseDirectory() throws -> String {
    #if os(tvOS)
    let paths = NSSearchPathForDirectoriesInDomains(.cachesDirectory, .userDomainMask, true)
    #else
    let paths = NSSearchPathForDirectoriesInDomains(.documentDirectory, .userDomainMask, true)
    #endif
    
    if let documentPath = paths.first, !documentPath.isEmpty {
        let basePath = (documentPath as NSString).appendingPathComponent("realm")
        return documentPath
    } else {
        throw NSError(domain: "BasePathNotFound", code: 1, userInfo: [
            NSLocalizedDescriptionKey: "Cannot find base-path to store MMKV files!"
        ])
    }
}

@main
struct exampleApp: App {
    var body: some Scene {
        WindowGroup {
            ContentView().onAppear {
                do {
                    var basePath = try getBaseDirectory()
                    
                    
                    basePath.withCString { cString in
                        var app = AppCore(cString)
                        app.initialize()
                    }

                } catch {
                    
                }
//                var basePath = try getBaseDirectory()
//                var app = AppCore()
//                app.initialize()
//                var swift = AppCoreSwift()
//                swift.test()
            }
        }
    }
}
