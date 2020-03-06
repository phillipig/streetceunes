#include <math.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

//Como compilar: g++ main.cpp -o main -lopenal -lalut -fpermissive
//OpenAL: sudo apt-get install libopenal0a libopenal-dev
//ALUT: sudo apt-get install libalut0 libalut-dev

// Maximum data buffers we will need.
#define NUM_BUFFERS 9

// Maximum emissions we will need.
#define NUM_SOURCES 9

// These index the buffers and sources.
#define APLAUSOS 0
#define CHUTE 1
#define FUNDO 2
#define PULO 3
#define SECO 4
#define SOCO 5
#define CORTE 6
#define LANCA 7
#define LUTEM 8

// Buffers hold sound data.
ALuint Buffers[NUM_BUFFERS];

// Sources are points of emitting sound.
ALuint Sources[NUM_SOURCES];

// Position of the source sounds.
ALfloat SourcesPos[NUM_SOURCES][3];

// Velocity of the source sounds.
ALfloat SourcesVel[NUM_SOURCES][3];

// Position of the listener.
ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

// Velocity of the listener.
ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

// Orientation of the listener. (first 3 elements are "at", second 3 are "up")
ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };

/*
 * ALboolean LoadALData()
 *
 *	This function will load our sample data from the disk using the alut
 *	utility and send the data into OpenAL as a buffer. A source is then
 *	also created to play that buffer.
 */
ALboolean LoadALData(){
	// Variables to load into.
	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop;

	// Load wav data into buffers.
	alGenBuffers(NUM_BUFFERS, Buffers);

	if(alGetError() != AL_NO_ERROR)	return AL_FALSE;

	alutLoadWAVFile("audio/aplausos.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[APLAUSOS], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	alutLoadWAVFile("audio/chute.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[CHUTE], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	alutLoadWAVFile("audio/fundo.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[FUNDO], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);
	
	alutLoadWAVFile("audio/pulo.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[PULO], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	alutLoadWAVFile("audio/seco.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[SECO], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	alutLoadWAVFile("audio/soco.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[SOCO], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);
	
	alutLoadWAVFile("audio/corte.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[CORTE], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	alutLoadWAVFile("audio/lanca.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[LANCA], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);
	
	alutLoadWAVFile("audio/lutem.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffers[LUTEM], format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);
	
	// Bind buffers into audio sources.
	alGenSources(NUM_SOURCES, Sources);

	if(alGetError() != AL_NO_ERROR) return AL_FALSE;

	alSourcei (Sources[APLAUSOS], AL_BUFFER,   Buffers[APLAUSOS]   );
	alSourcef (Sources[APLAUSOS], AL_PITCH,    1.0f              );
	alSourcef (Sources[APLAUSOS], AL_GAIN,     1.0f              );
	alSourcefv(Sources[APLAUSOS], AL_POSITION, SourcesPos[APLAUSOS]);
	alSourcefv(Sources[APLAUSOS], AL_VELOCITY, SourcesVel[APLAUSOS]);
	alSourcei (Sources[APLAUSOS], AL_LOOPING,  AL_FALSE            );

	alSourcei (Sources[CHUTE], AL_BUFFER,   Buffers[CHUTE]   );
	alSourcef (Sources[CHUTE], AL_PITCH,    1.0f            );
	alSourcef (Sources[CHUTE], AL_GAIN,     1.0f            );
	alSourcefv(Sources[CHUTE], AL_POSITION, SourcesPos[CHUTE]);
	alSourcefv(Sources[CHUTE], AL_VELOCITY, SourcesVel[CHUTE]);
	alSourcei (Sources[CHUTE], AL_LOOPING,  AL_FALSE        );

	alSourcei (Sources[FUNDO], AL_BUFFER,   Buffers[FUNDO]   );
	alSourcef (Sources[FUNDO], AL_PITCH,    1.0f            );
	alSourcef (Sources[FUNDO], AL_GAIN,     1.0f            );
	alSourcefv(Sources[FUNDO], AL_POSITION, SourcesPos[FUNDO]);
	alSourcefv(Sources[FUNDO], AL_VELOCITY, SourcesVel[FUNDO]);
	alSourcei (Sources[FUNDO], AL_LOOPING,  AL_TRUE       );
	
	alSourcei (Sources[PULO], AL_BUFFER,   Buffers[PULO]   );
	alSourcef (Sources[PULO], AL_PITCH,    1.0f              );
	alSourcef (Sources[PULO], AL_GAIN,     1.0f              );
	alSourcefv(Sources[PULO], AL_POSITION, SourcesPos[PULO]);
	alSourcefv(Sources[PULO], AL_VELOCITY, SourcesVel[PULO]);
	alSourcei (Sources[PULO], AL_LOOPING,  AL_FALSE           );

	alSourcei (Sources[SECO], AL_BUFFER,   Buffers[SECO]   );
	alSourcef (Sources[SECO], AL_PITCH,    1.0f            );
	alSourcef (Sources[SECO], AL_GAIN,     1.0f            );
	alSourcefv(Sources[SECO], AL_POSITION, SourcesPos[SECO]);
	alSourcefv(Sources[SECO], AL_VELOCITY, SourcesVel[SECO]);
	alSourcei (Sources[SECO], AL_LOOPING,  AL_FALSE        );

	alSourcei (Sources[SOCO], AL_BUFFER,   Buffers[SOCO]   );
	alSourcef (Sources[SOCO], AL_PITCH,    1.0f            );
	alSourcef (Sources[SOCO], AL_GAIN,     1.0f            );
	alSourcefv(Sources[SOCO], AL_POSITION, SourcesPos[SOCO]);
	alSourcefv(Sources[SOCO], AL_VELOCITY, SourcesVel[SOCO]);
	alSourcei (Sources[SOCO], AL_LOOPING,  AL_FALSE        );

	alSourcei (Sources[CORTE], AL_BUFFER,   Buffers[CORTE]   );
	alSourcef (Sources[CORTE], AL_PITCH,    1.0f            );
	alSourcef (Sources[CORTE], AL_GAIN,     1.0f            );
	alSourcefv(Sources[CORTE], AL_POSITION, SourcesPos[CORTE]);
	alSourcefv(Sources[CORTE], AL_VELOCITY, SourcesVel[CORTE]);
	alSourcei (Sources[CORTE], AL_LOOPING,  AL_FALSE        );

	alSourcei (Sources[LANCA], AL_BUFFER,   Buffers[LANCA]   );
	alSourcef (Sources[LANCA], AL_PITCH,    1.0f            );
	alSourcef (Sources[LANCA], AL_GAIN,     1.0f            );
	alSourcefv(Sources[LANCA], AL_POSITION, SourcesPos[LANCA]);
	alSourcefv(Sources[LANCA], AL_VELOCITY, SourcesVel[LANCA]);
	alSourcei (Sources[LANCA], AL_LOOPING,  AL_FALSE        );
	
	alSourcei (Sources[LUTEM], AL_BUFFER,   Buffers[LUTEM]   );
	alSourcef (Sources[LUTEM], AL_PITCH,    1.0f            );
	alSourcef (Sources[LUTEM], AL_GAIN,     1.0f            );
	alSourcefv(Sources[LUTEM], AL_POSITION, SourcesPos[LUTEM]);
	alSourcefv(Sources[LUTEM], AL_VELOCITY, SourcesVel[LUTEM]);
	alSourcei (Sources[LUTEM], AL_LOOPING,  AL_FALSE        );
	
	// Do another error check and return.
	if(alGetError() != AL_NO_ERROR) return AL_FALSE;

	return AL_TRUE;
}

/*
 * void SetListenerValues()
 *
 *	We already defined certain values for the listener, but we need
 *	to tell OpenAL to use that data. This function does just that.
 */
void SetListenerValues(){
	alListenerfv(AL_POSITION,    ListenerPos);
	alListenerfv(AL_VELOCITY,    ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
}

/*
 * void KillALData()
 *
 *	We have allocated memory for our buffers and sources which needs
 *	to be returned to the system. This function frees that memory.
 */
void KillALData(){
	alDeleteBuffers(NUM_BUFFERS, Buffers);
	alDeleteSources(NUM_SOURCES, Sources);
	alutExit();
}
