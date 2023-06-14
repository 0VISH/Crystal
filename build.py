from sys import argv
from subprocess import run
import os

def runCmd(cmd):
    print("[CMD]", cmd)
    return run(cmd).returncode

isDbg = not("rls" in argv)
isWin = not("and" in argv)
shouldRun = "run" in argv
shouldBuildIMGUI = "imgui" in argv

folder = "bin/"

if(isWin): folder += "win/"
else: folder += "and/"

if(isDbg): folder += "dbg/"
else: folder += "rls/"

if not os.path.isdir(folder): os.makedirs(folder)

buildCmd = None

if(isWin):
    imguiPath = folder + "imgui.obj"
    if not os.path.isfile(imguiPath): shouldBuildIMGUI = True
    if(shouldBuildIMGUI):
        runCmd("cl /nologo /Z7 /I vendor/imgui/ src/Windows/imgui.cc -c /Fo:"+imguiPath)
    if(isDbg):
        buildCmd = "cl /nologo /Z7 /std:c++14 -c /I vendor/imgui/ src/Windows/entryPoint.cc /Fo" + folder + "crystal.obj"

if runCmd(buildCmd) != 0:
    quit()
if runCmd("link /NOLOGO /DEBUG /PDB:" + folder + "crystal.pdb " + folder + "crystal.obj " + folder + "imgui.obj /OUT:" + folder + "crystal.exe") != 0:
    quit()

if(shouldRun): runCmd(folder+"crystal.exe")

'''
rls- Release
dbg- debug
and- Android
win- Windows
'''
