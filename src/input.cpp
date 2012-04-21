#include "input.hpp"
#include "triger.h"

int callback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *dataPointer)
{
  Triger &triger = static_cast<Triger *>(dataPointer);
  register StkFloat *samples = static_cast<StkFloat *>(inputBuffer);
  triger->feedme(samples, nBufferFrames);
  return (0);
}

Input::Input(Triger& trgr) : triger(trgr)
{
  RtAudio::StreamParameters *parameters;
  RtAudioFormat format = ( sizeof(StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;

  parameters.deviceId = getDefaultInputDevice();
  parameters.nChannels = 2;
  Stk::setSampleRate(44100.0);

  try {
    dac.openStream( &parameters, &iparameters, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &callback, (void *)&triger);
  }
  catch ( RtError &error ) {
    error.printMessage();
    exit();
  }
}

void Input::run()
{
  try {
    dac.startStream();
  }
  catch ( RtError &error ) {
    error.printMessage();
    exit();
  }
}

void Input::close()
{
  try {
    dac.closeStream();
  }
  catch ( RtError &error ) {
    error.printMessage();
  }
}
