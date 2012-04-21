#include "input.hpp"
using namespace stk;

int t = 0;

int callback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *dataPointer)
{
  Trigger *trigger = static_cast<Trigger *>(dataPointer);
  StkFloat *samples = static_cast<StkFloat *>(inputBuffer);
  trigger->feedMe(samples, nBufferFrames);
  return (0);
}

Input::Input(Trigger& trgr) : trigger(trgr)
{
  unsigned int bufferFrames = RT_BUFFER_SIZE;
  RtAudio::StreamParameters parameters;
  //RtAudio::StreamParameters iparameters;
  RtAudioFormat format = ( sizeof(StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;

  std::cout << "Device listing:" << std::endl;
  int device = this->dac.getDefaultInputDevice();
  unsigned nDevices = dac.getDeviceCount();
  for(unsigned i = 0; i < nDevices; i++) {
    RtAudio::DeviceInfo info = dac.getDeviceInfo(i);
    std::cout << "[" << i << "] " << (device == i ? "* " : "  ") << info.name << std::endl;
  }

  parameters.deviceId = device;
  parameters.nChannels = 2;
  //iparameters.deviceId = device;
  //iparameters.nChannels = 2;
  Stk::setSampleRate(44100.0);

  try {
    dac.openStream( NULL, &parameters, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &callback, (void *)&trigger);
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
