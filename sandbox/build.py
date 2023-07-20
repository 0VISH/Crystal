from sys import argv
from subprocess import run
import os

def runCmd(cmd):
    print("[CMD]", cmd)
    if(run(cmd).returncode != 0): quit()

dir = "sandbox/bin/"
if not os.path.isdir(dir): os.makedirs(dir)

runCmd("cl /nologo /Z7 /std:c++14 -c /I include/ /I vendor/glm/ sandbox/src/sandbox.cc /Fo:"+dir+"game.obj")
runCmd("link /NOLOGO /DLL /DEBUG /PDB:"+dir+"game.pdb "+dir+"game.obj /OUT:"+dir+"game.dll")
