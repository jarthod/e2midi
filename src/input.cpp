#include "input.hpp"
using namespace stk;

int callback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *dataPointer)
{
  Trigger *trigger = static_cast<Trigger *>(dataPointer);
  register StkFloat *samples = static_cast<StkFloat *>(inputBuffer);
  trigger->feedMe(samples, nBufferFrames);
  return (0);
}

Input::Input(Trigger& trgr) : trigger(trgr)
{
  unsigned int bufferFrames = RT_BUFFER_SIZE;
  RtAudio::StreamParameters parameters;
  RtAudioFormat format = ( sizeof(StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;

  parameters.deviceId = this->dac.getDefaultInputDevice();
  parameters.nChannels = 2;
  Stk::setSampleRate(44100.0);

  try {
    dac.openStream( &parameters, &parameters, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &callback, (void *)&trigger);
  }
  catch ( RtError &error ) {
    error.printMessage();
    exit(1);
  }
}

void Input::run()
{
  try {
    dac.startStream();
  }
  catch ( RtError &error ) {
    error.printMessage();
    exit(1);
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
