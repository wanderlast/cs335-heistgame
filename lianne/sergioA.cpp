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
  
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(0, yres);
	glVertex2i(xres, yres);
	glVertex2i(xres, 0);
	glEnd();

  
  
}