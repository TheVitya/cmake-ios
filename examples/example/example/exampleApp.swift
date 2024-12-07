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
            }
        }
    }

    init() {
        do {
            let basePath = try getBaseDirectory()

            basePath.withCString { cString in
                let config = AppCoreConfig( system_path: cString )
                AppCore.initialize(config)
            }
        } catch {
            fatalError("Failed to initialize AppCore: \(error)")
        }
    }

    static public func initialize() {
        let appCoreRef = AppCore.instance()

        let str = appCoreRef.string("TEST", "vitya test swiftbol" + String(Int.random(in: 0..<200)))
        appCoreRef.string("TEST")
        print("str: " + String(str))

        let float: Float = 123
        var _float = appCoreRef.set_float("float", float)
        _float = appCoreRef.get_float("float", float)
        print("float: " + String(_float))

        var bool = appCoreRef.set_bool("bool", true)
        bool = appCoreRef.get_bool("bool", true)
        print("bool: " + String(bool))

        var int32 = appCoreRef.set_int32_t("int32", -32)
        int32 = appCoreRef.get_int32_t("int32", -32)
        print("int32: " + String(int32))

        var int64 = appCoreRef.set_int64_t("int64", -64)
        int64 = appCoreRef.get_int64_t("int64", -64)
        print("int64: " + String(int64))

        var uint32 = appCoreRef.set_uint32_t("uint32", 32)
        uint32 = appCoreRef.get_uint32_t("uint32", 32)
        print("uint32: " + String(uint32))

        var uint64 = appCoreRef.set_uint64_t("uint64", 64)
        uint64 = appCoreRef.get_uint64_t("uint64", 64)
        print("uint64: " + String(uint64))

        var double = appCoreRef.set_double("double", 1.00)
        double = appCoreRef.get_double("double", 1.00)
        print("double: " + String(double))
    }
}
