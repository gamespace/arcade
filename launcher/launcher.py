#!/usr/bin/python

import json
import os
import time
from subprocess import call, Popen


homedir = os.path.expanduser('~')
running = None

def kill_running():
  global running
  if running:
    print 'killing process'
    running.kill()
    running = None

def find_usb_sticks():
  return dict((f, None) for f in os.listdir('/media'))

def run_stick(stick):
  global running
  kill_running()
  print 'loading config'
  config_json = open('/media/' + stick + '/arcade.json')
  config = json.load(config_json)
  if config['arcade_version'] != '1':
    print 'Config not supported'
    return
  copy = config['copy']
  exec_ = config['exec']
  print 'copying ' + copy
  targetdir = homedir + '/tmp/' + f + '/'
  call(['mkdir', targetdir])
  call(['cp', '-r', '/media/' + f + '/' + copy, targetdir])
  targetexec = targetdir + exec_
  call(['chmod', '+x', targetexec])
  print 'running ' + targetexec
  running = Popen(targetexec)

def clean_stick(f):
  kill_running()
  print 'cleaning ' + f
  call(['rm', '-r', homedir+'/tmp/'+f])

sticks = find_usb_sticks()

while True:
  time.sleep(2)
  new_sticks = find_usb_sticks()
  added = [f for f in new_sticks if not f in sticks]
  removed = [f for f in sticks if not f in new_sticks]
  for f in added:
    run_stick(f)
  for f in removed:
    clean_stick(f)
  sticks = new_sticks


