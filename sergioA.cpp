//Author: Sergio Alvarado
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include </usr/include/AL/alut.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "log.h"
#include "ppm.h"
#include "main.h"
extern "C"{
	#include "fonts.h"
}


ALuint alSource;
ALuint alBuffer;

void createSound() {
		 //Get started right here.
 alutInit(0, NULL);
 if (alGetError() != AL_NO_ERROR) {
 printf("ERROR: alutInit()\n");
 }
 //Clear error state.
 alGetError();
 // Setup the listener.
 // Forward and up vectors are used.
 float vec[6] = {0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f};
 alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
 alListenerfv(AL_ORIENTATION, vec);
 alListenerf(AL_GAIN, 1.0f);
	
	// // Buffer holds the sound information.
 //ALuint alBuffer;
 alBuffer = alutCreateBufferFromFile("./cha-ching.wav");
	
	// // Source refers to the sound.
	// // ALuint alSource;
	// // Generate a source, and store it in a buffer.
 alGenSources(1, &alSource);
 alSourcei(alSource, AL_BUFFER, alBuffer);
	// // Set volume and pitch to normal, no looping of sound.
 alSourcef(alSource, AL_GAIN, 1.0f);
 alSourcef(alSource, AL_PITCH, 1.0f);
 alSourcei(alSource, AL_LOOPING, AL_FALSE);
 if (alGetError() != AL_NO_ERROR) {
 	printf("ERROR: setting source\n");
 }
for (int i=0; i<1; i++){
	 alSourcePlay(alSource);
 	 usleep(900000);
 }
}

 void cleanupSound() {
	// // First delete the source.
 alDeleteSources(1, &alSource);
	// // Delete the buffer.
 alDeleteBuffers(1, &alBuffer);
	// // Close out OpenAL itself.
	// // Get active context.
 ALCcontext *Context = alcGetCurrentContext();
	// // Get device for active context.
 ALCdevice *Device = alcGetContextsDevice(Context);
	// // Disable context.
 alcMakeContextCurrent(NULL);
	// // Release context(s).
 alcDestroyContext(Context);
	// // Close device.
 alcCloseDevice(Device);

 }
 
void startMenu() {
  
   Rect r;
  
  	//start the opengl stuff
	//set the viewing area on screen
	glViewport(0, 0, xres, yres);
	//clear color buffer
	//glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	//init matrices
	glMatrixMode (GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	//this sets to 2D mode (no perspective)
	glOrtho(0, xres, 0, yres, -1, 1);
	//
	//screen background
	glColor3f(0.5f, 0.5f, 0.5f);
	/*glBindTexture(GL_TEXTURE_2D, startTexture);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(0,      0);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(0,      yres);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, yres);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	*/
	r.left   = xres/2;
	r.bot    = yres-100;
	r.center = 1;
	ggprint16(&r, 16, 0x00ffffff, "Heist Game");
	
	r.left   = xres/2;
	r.bot    = yres-300;
	r.center = 1;
	ggprint16(&r, 16, 0x00ffffff, "Press SPACE to start!");
}
