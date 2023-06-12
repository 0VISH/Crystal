from sys import argv
from subprocess import run
import os

isDbg = not("rls" in argv)
isWin = not("and" in argv)
shouldRun = "run" in argv

folder = "bin/"

if(isWin): folder += "win/"
else: folder += "and/"

if(isDbg): folder += "dbg/"
else: folder += "rls/"

if not os.path.isdir(folder): os.makedirs(folder)

buildCmd = None

if(isWin):
    if(isDbg):
        buildCmd = "cl /nologo /std:c++14 /Zi src/Windows/entryPoint.cc /Fo:" + folder + "crystal.obj /Fd:" + folder + "crystal.pdb /Fe:" + folder + "crystal.exe /I:src/window/GLFW/"

print("[CMD]", buildCmd)
if run(buildCmd).returncode != 0: shouldRun = False

if(shouldRun):
    cmd = folder+"crystal.exe"
    print("[CMD]", cmd)
    run(cmd)

'''
rls- Release
dbg- debug
and- Android
win- Windows
'''
