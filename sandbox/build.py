from sys import argv
from subprocess import run
import os
import time

def getTime():
    t = time.localtime()
    return time.strftime("%H_%M_%S", t)

def runCmd(cmd):
    print("[CMD]", cmd)
    if(run(cmd).returncode != 0): quit()

dir = "sandbox/bin/"
if not os.path.isdir(dir): os.makedirs(dir)

runCmd("cl /nologo /Z7 /std:c++14 -c /I include/ /I vendor/glm/ /I vendor/box2d/include/ /DWIN=true sandbox/src/sandbox.cc /Fo:"+dir+"game.obj")
runCmd("link /NOLOGO /DLL /DEBUG /PDB:"+dir+"game"+getTime()+".pdb "+dir+"game.obj /OUT:"+dir+"gamewin.dll")
