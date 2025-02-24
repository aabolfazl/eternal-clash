package app.eternal.clash

import org.libsdl.app.SDLActivity

class MainActivity : SDLActivity() {

    companion object {
        init {
            System.loadLibrary("main");
        }
    }
}