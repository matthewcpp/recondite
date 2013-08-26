/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

//BEGIN_INCLUDE(all)
#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include "rAndroidContentManager.hpp"
#include "rAndroidInputManager.hpp"

#include "rOpenGLGraphicsDevice.hpp"
#include "rViewport.hpp"
#include "rMatrix4.hpp"
#include "rAndroidLog.hpp"
#include "rCamera.hpp"
#include "rLog.hpp"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define RLOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "recondite", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

/**
 * Our saved state data.
 */
struct saved_state {
    float angle;
    int32_t x;
    int32_t y;
};

/**
 * Shared state for our app.
 */
struct engine {
    struct android_app* app;

    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    ASensorEventQueue* sensorEventQueue;

    int animating;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int32_t width;
    int32_t height;
    struct saved_state state;

    rOpenGLGraphicsDevice* graphicsDevice;
    rAndroidContentManager* contentManager;
    rAndroidInputManager* inputManager;
    rViewport viewport;
    rTargetCamera* camera;
    rAndroidLog* log;
    int frame;
};

void createColoredShader(rContentManager* contentManager, const char* name, const char* value){
    rMaterialData materialData;
    materialData.SetShader("default_colored", "");
    materialData.SetParameter( rMATERIAL_PARAMETER_COLOR , "fragColor", value);

    contentManager->LoadMaterial(materialData, name);
}

static void createGeometry(struct engine* engine){

	float verts[] = { -0.5f,  0.5f, 0.0f,  // Position 0
            -0.5f, -0.5f, 0.0f,  // Position 1
             0.5f, -0.5f, 0.0f,  // Position 2
             0.5f,  0.5f, 0.0f,  // Position 3
          };

	float tex_verts[] = { 	-0.5f,  0.5f, 0.0f,  // Position 0
	                         0.0f,  0.0f,        // TexCoord 0
	                         -0.5f, -0.5f, 0.0f,  // Position 1
	                         0.0f,  1.0f,        // TexCoord 1
	                         0.5f, -0.5f, 0.0f,  // Position 2
	                         1.0f,  1.0f,        // TexCoord 2
	                         0.5f,  0.5f, 0.0f,  // Position 3
	                         1.0f,  0.0f         // TexCoord 3
	                      };

	/*
	float verts[] = { 50.0f,  100.0f, 0.0f,  // Position 0
            50.0f, 50.0f, 0.0f,  // Position 1
             100.0f, 50.0f, 0.0f,  // Position 2
             100.0f,  100.0f, 0.0f,  // Position 3
          };


	float tex_verts[] = { 	200.0f,  400.0f, 0.0f,  // Position 0
	                         0.0f,  0.0f,        // TexCoord 0
	                        200.0f, 200.0f, 0.0f,  // Position 1
	                         0.0f,  1.0f,        // TexCoord 1
	                         400.0f, 200.0f, 0.0f,  // Position 2
	                         1.0f,  1.0f,        // TexCoord 2
	                         400.0f,  400.0f, 0.0f,  // Position 3
	                         1.0f,  0.0f         // TexCoord 3
	                      };

*/
	unsigned short elements[] = { 0, 1, 2, 0, 2, 3 };

	rGeometryData data;
	data.SetVertexData(verts, 4, false, false);
	data.CreateElementBuffer("rect",elements, 6);
	engine->contentManager->LoadGeometry(data, "rect");

	data.SetVertexData(tex_verts, 4, true, false);
	engine->contentManager->LoadGeometry(data, "texture_rect");

	float triangle1VerticesData []= {
		            -0.5f, -0.25f, 0.0f,
		            0.5f, -0.25f, 0.0f,
		            0.0f, 0.559016994f, 0.0f,
		            };

	unsigned short triangleElements[] ={1,2,3};


	rGeometryData triangleData;
	triangleData.SetVertexData(triangle1VerticesData, 3, false, false);
	triangleData.CreateElementBuffer("triangle", triangleElements, 3);
	engine->contentManager->LoadGeometry(triangleData, "triangle");


	   unsigned char pixels[] = {
	      128,   92,   61, // brown
	        191, 27,   224, // purple
	        0,   0, 255, // Blue
	      255, 255,   0	// Yellow
	   };


   rTexture2DData texture;
   texture.SetImageData(2,2,3,pixels);
   rTexture2D* t = engine->contentManager->LoadTexture(texture, "texture");

   rMaterialData materialData;
   materialData.SetShader("default_textured", "");
   materialData.SetParameter( rMATERIAL_PARAMETER_TEXTURE2D , "s_texture", "texture");

   engine->contentManager->LoadMaterial(materialData, "test_tex");
}


/**
 * Initialize an EGL context for the current display.
 */
static int engine_init_display(struct engine* engine, struct android_app* state) {
    // initialize OpenGL ES and EGL

    /*
     * Here specify the attributes of the desired configuration.
     * Below, we select an EGLConfig with at least 8 bits per color
     * component compatible with on-screen windows
     */
    const EGLint attribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };
    EGLint w, h, dummy, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, 0, 0);

    /* Here, the application chooses the configuration it desires. In this
     * sample, we have a very simplified selection process, where we pick
     * the first EGLConfig that matches our criteria */
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);

    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

    ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);

    surface = eglCreateWindowSurface(display, config, engine->app->window, NULL);

    EGLint contextAttrs[] = {
         EGL_CONTEXT_CLIENT_VERSION, 2,
         EGL_NONE
    };

    context = eglCreateContext(display, config, NULL, contextAttrs);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        LOGW("Unable to eglMakeCurrent");
        return -1;
    }

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    engine->display = display;
    engine->context = context;
    engine->surface = surface;
    engine->width = w;
    engine->height = h;
    engine->state.angle = 0;

    engine->log = new rAndroidLog();
    rLog::SetLogTarget(engine->log);

    rLog::Info("display size: %d x %d", engine->width, engine->height);

    engine->camera = new rTargetCamera("camera", rVector3(0,0,50));
    engine->camera->SetTarget(rVector3(0,0,-5));

    engine->viewport.SetCamera(engine->camera);
    engine->viewport.SetClipping(1.0, 100.0f);
    engine->viewport.SetSize(w,h);
    engine->viewport.SetViewportType(rVIEWPORT_PERSP);
    //engine->viewport.SetViewportType(rVIEWPORT_2D);

    AAssetManager* assetManager = state->activity->assetManager;
    engine->graphicsDevice = new rOpenGLGraphicsDevice();
    engine->inputManager = new rAndroidInputManager();

    engine->graphicsDevice->SetClearColor(0,0,0,0);

    engine->contentManager = new rAndroidContentManager(assetManager, engine->graphicsDevice);
    engine->contentManager->InitDefaultAssets();
    rLog::Info("contentManager->InitDefaultAssets");

    engine->frame = 0;

    createColoredShader(engine->contentManager, "red_shaded", "255 0 0 255");
    createColoredShader(engine->contentManager, "green_shaded", "0 255 0 255");


    createGeometry(engine);

    return 0;
}

/**
 * Just the current frame in the display.
 */

static void drawShaded(struct engine* engine){
	rMatrix4 matrix;
	matrix.SetTranslate(1.0f, 0.0f, 0.0f);
	matrix.SetUniformScale(2);
	rGeometry* geometry = engine->contentManager->GetGeometryAsset("rect");
	rMaterial* material = (engine-> frame % 120 < 60) ?
		engine->contentManager->GetMaterialAsset("red_shaded") :
		engine->contentManager->GetMaterialAsset("green_shaded");

	engine->graphicsDevice->RenderGeometry(geometry, matrix, "rect", material);

}

static void drawTextured(struct engine* engine){
	rMatrix4 matrix;
	matrix.SetTranslate(-1.0f, 0.0f, 0.0f);
	rGeometry* geometry = engine->contentManager->GetGeometryAsset("texture_rect");
	rMaterial* material = engine->contentManager->GetMaterialAsset("test_tex");
	engine->graphicsDevice->RenderGeometry(geometry, matrix, "rect", material);
}

static void engine_draw_frame(struct engine* engine) {

	engine->frame++;
    if (engine->display == NULL) {
        // No display.
        return;
    }

    engine->graphicsDevice->Clear();
    engine->graphicsDevice->SetActiveViewport(&engine->viewport);

    drawTextured(engine);
    drawShaded(engine);


    eglSwapBuffers(engine->display, engine->surface);
}

/**
 * Tear down the EGL context currently associated with the display.
 */
static void engine_term_display(struct engine* engine) {
	delete engine->contentManager;

    if (engine->display != EGL_NO_DISPLAY) {
        eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (engine->context != EGL_NO_CONTEXT) {
            eglDestroyContext(engine->display, engine->context);
        }
        if (engine->surface != EGL_NO_SURFACE) {
            eglDestroySurface(engine->display, engine->surface);
        }
        eglTerminate(engine->display);
    }
    engine->animating = 0;
    engine->display = EGL_NO_DISPLAY;
    engine->context = EGL_NO_CONTEXT;
    engine->surface = EGL_NO_SURFACE;
}

/**
 * Process the next input event.
 */
static int32_t engine_handle_input(struct android_app* app, AInputEvent* event) {
    struct engine* engine = (struct engine*)app->userData;

    engine->inputManager->ProcessInputEvent(event);

    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {
    	engine->animating = 1;

        engine->state.x = AMotionEvent_getX(event, 0);
        engine->state.y = AMotionEvent_getY(event, 0);
        return 1;
    }
    return 0;
}

/**
 * Process the next main command.
 */
static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
    struct engine* engine = (struct engine*)app->userData;
    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            // The system has asked us to save our current state.  Do so.
            engine->app->savedState = malloc(sizeof(struct saved_state));
            *((struct saved_state*)engine->app->savedState) = engine->state;
            engine->app->savedStateSize = sizeof(struct saved_state);
            break;
        case APP_CMD_INIT_WINDOW:
            // The window is being shown, get it ready.
            if (engine->app->window != NULL) {
                engine_init_display(engine, app);
                engine_draw_frame(engine);
            }
            break;
        case APP_CMD_TERM_WINDOW:
            // The window is being hidden or closed, clean it up.
            engine_term_display(engine);
            break;
        case APP_CMD_GAINED_FOCUS:
            // When our app gains focus, we start monitoring the accelerometer.
            if (engine->accelerometerSensor != NULL) {
                ASensorEventQueue_enableSensor(engine->sensorEventQueue,
                        engine->accelerometerSensor);
                // We'd like to get 60 events per second (in us).
                ASensorEventQueue_setEventRate(engine->sensorEventQueue,
                        engine->accelerometerSensor, (1000L/60)*1000);
            }
            break;
        case APP_CMD_LOST_FOCUS:
            // When our app loses focus, we stop monitoring the accelerometer.
            // This is to avoid consuming battery while not being used.
            if (engine->accelerometerSensor != NULL) {
                ASensorEventQueue_disableSensor(engine->sensorEventQueue,
                        engine->accelerometerSensor);
            }
            // Also stop animating.
            engine->animating = 0;
            engine_draw_frame(engine);
            break;
    }
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* state) {
    struct engine engine;

    // Make sure glue isn't stripped.
    app_dummy();

    memset(&engine, 0, sizeof(engine));
    state->userData = &engine;
    state->onAppCmd = engine_handle_cmd;
    state->onInputEvent = engine_handle_input;
    engine.app = state;

    // Prepare to monitor accelerometer
    engine.sensorManager = ASensorManager_getInstance();
    engine.accelerometerSensor = ASensorManager_getDefaultSensor(engine.sensorManager,
            ASENSOR_TYPE_ACCELEROMETER);
    engine.sensorEventQueue = ASensorManager_createEventQueue(engine.sensorManager,
            state->looper, LOOPER_ID_USER, NULL, NULL);

    if (state->savedState != NULL) {
        // We are starting with a previous saved state; restore from it.
        engine.state = *(struct saved_state*)state->savedState;
    }

    // loop waiting for stuff to do.

    while (1) {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
        while ((ident=ALooper_pollAll(engine.animating ? 0 : -1, NULL, &events,
                (void**)&source)) >= 0) {

            // Process this event.
            if (source != NULL) {
                source->process(state, source);
            }

            // If a sensor has data, process it now.
            if (ident == LOOPER_ID_USER) {
                if (engine.accelerometerSensor != NULL) {
                    ASensorEvent event;
                    while (ASensorEventQueue_getEvents(engine.sensorEventQueue,
                            &event, 1) > 0) {
                        ;/*LOGI("accelerometer: x=%f y=%f z=%f",
                                event.acceleration.x, event.acceleration.y,
                                event.acceleration.z);*/
                    }
                }
            }

            // Check if we are exiting.
            if (state->destroyRequested != 0) {
                engine_term_display(&engine);
                return;
            }
        }

        if (engine.animating) {
            // Done with events; draw next animation frame.
            engine.state.angle += .01f;
            if (engine.state.angle > 1) {
                engine.state.angle = 0;
            }

            // Drawing is throttled to the screen update rate, so there
            // is no need to do timing here.
            engine_draw_frame(&engine);
        }
    }
}
//END_INCLUDE(all)
