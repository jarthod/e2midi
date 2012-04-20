#!/usr/bin/env ruby

require 'rubygems'
require 'alsa'

ALSA::PCM::Capture.open do |capture|
  capture.read do |buffer, frame_count|
    $stdout.write "%s\n" % buffer.get_uint16(0).inspect
  end               
end