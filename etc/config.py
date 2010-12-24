#!/usr/bin/pyhton
#-*- coding: UTF-8 -*-

import NoTouchScreenMod

print("Config from python script...")

# Getting the config object
config=NoTouchScreenMod.NoTouchScreenConfig()

# Configuration of keyboard shorcuts
config.addActionOnEvent("OnRightTranslation","Ctrl+Alt+Left")
config.addActionOnEvent("OnLeftTranslation","Ctrl+Alt+Right")

print("Done")