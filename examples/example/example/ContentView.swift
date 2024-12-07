//
//  ContentView.swift
//  example
//
//  Created by Viktor Nagy on 21.8.24..
//

import SwiftUI
import AppCoreFramework

struct ContentView: View {
    @State private var data: String
    
    init() {
        let appCoreRef = AppCore.instance()
        data = String(appCoreRef.string("TEST"))
    }

    var body: some View {
        VStack {
            Image(systemName: "globe")
                .imageScale(.large)
                .foregroundStyle(.tint)
            Text("Hello, world!")
            
            Button(data) {
                exampleApp.initialize()
                let appCoreRef = AppCore.instance()
                let str = String(appCoreRef.string("TEST"))
                
                data = str
            }
        }
        .padding()
    }
}

#Preview {
    ContentView()
}
