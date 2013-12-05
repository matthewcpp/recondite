#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include "rAndroidDemoApp.hpp"

void android_onAppCmd(android_app* app, int32_t cmd) {
	rAndroidDemoApp* application = (rAndroidDemoApp*)app->userData;
	application->ProcessCommand(app, cmd);

}

int32_t android_onInputEvent(android_app* app, AInputEvent* event){
	rAndroidDemoApp* application = (rAndroidDemoApp*)app->userData;
	return application->OnInput(event);
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */

void android_main(struct android_app* state){
	rAndroidDemoApp application;

	app_dummy();

	state->userData = &application;
	state->onAppCmd = android_onAppCmd;
	state->onInputEvent = android_onInputEvent;

	__android_log_print(ANDROID_LOG_INFO, "recondite", "Hello World");

    while (1) {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;
        while ((ident=ALooper_pollAll(0, NULL, &events,  (void**)&source)) >= 0) {
			if (source != NULL) {
				source->process(state, source);
			}

			if (state->destroyRequested != 0) {
				//application.Uninit();
				return;
			}
        }

        application.Tick();
    }
}
