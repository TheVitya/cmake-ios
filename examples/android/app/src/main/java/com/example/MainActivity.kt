package com.example

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.example.ui.theme.ExampleTheme
import org.AppCore.AppCoreJava

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            ExampleTheme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    val path = getFilesDir().getAbsolutePath();
                    val appCoreRef = AppCoreJava()
                    appCoreRef.initialize(path)

                    val floatValue: Float = 123f
                    var _float = appCoreRef.setFloat("float", floatValue)
                    _float = appCoreRef.getFloat("float", floatValue)
                    println("float: $_float")

                    var bool = appCoreRef.setBool("bool", true)
                    bool = appCoreRef.getBool("bool", true)
                    println("bool: $bool")

                    var int32 = appCoreRef.setInt32("int32", -32)
                    int32 = appCoreRef.getInt32("int32", -32)
                    println("int32: $int32")

                    var int64 = appCoreRef.setInt64("int64", -64L)
                    int64 = appCoreRef.getInt64("int64", -64L)
                    println("int64: $int64")

                    var uint32 = appCoreRef.setUInt32("uint32", 32)
                    uint32 = appCoreRef.getUInt32("uint32", 32)
                    println("uint32: $uint32")

                    var uint64 = appCoreRef.setUInt64("uint64", 64L)
                    uint64 = appCoreRef.getUInt64("uint64", 64L)
                    println("uint64: $uint64")

                    var doubleValue = 1.00
                    var _double = appCoreRef.setDouble("double", doubleValue)
                    _double = appCoreRef.getDouble("double", doubleValue)
                    println("double: $_double")

                    Greeting(
                        name = "Android",
                        modifier = Modifier.padding(innerPadding)
                    )
                }
            }
        }
    }
}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    Text(
        text = "Hello $name!",
        modifier = modifier
    )
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    ExampleTheme {
        Greeting("Android")
    }
}