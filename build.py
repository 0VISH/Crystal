from sys import argv
from subprocess import run
import os

def runCmd(cmd):
    print("[CMD]", cmd)
    if(run(cmd).returncode != 0): quit()

isDbg = not("rls" in argv)
shouldRun = "run" in argv
shouldBuildIMGUI  = "imgui"  in argv
shouldBuildGLAD   = "glad"   in argv
shouldBuildVENDOR = "vendor" in argv
shouldBuildEngine = "engine" in argv

gameMain = None
plat = None
for i in argv:
    if i.startswith("main:"):
        gameMain = i[len("path:"):]
    if i.startswith("plat:"):
        plat = i[len("plat:"):]

if(gameMain == None):
    print("path for game's main file required")
    quit()
if(plat == None):
    plat = "win"

if(shouldBuildVENDOR):
    shouldBuildIMGUI = True
    shouldBuildGLAD  = True

folder = "bin/"

folder += plat + "/"

if(isDbg): folder += "dbg/"
else: folder += "rls/"

if not os.path.isdir(folder): os.makedirs(folder)

buildCmd = None

if(plat == "win"):
    imguiPath  = folder + "imgui.obj"
    gladPath   = folder + "glad.obj"
    enginePath = folder + "crystal.obj"
    if not os.path.isfile(imguiPath): shouldBuildIMGUI = True
    if not os.path.isfile(gladPath):  shouldBuildGLAD = True
    if not os.path.isfile(enginePath):  shouldBuildEngine = True
    if(shouldBuildIMGUI):
        runCmd("cl /nologo /Z7 /I vendor/imgui/ src/Windows/imgui.cc -c /Fo:"+imguiPath)
    if(shouldBuildGLAD):
        runCmd("cl /nologo /Z7 /I vendor/glad/include/ vendor/glad/src/glad.c -c /Fo:"+gladPath)
    if(shouldBuildEngine):
        runCmd("cl /nologo /Z7 /std:c++14 -c /I include/ /I vendor/glad/include/ /I vendor/glm/ /I vendor/imgui/ src/Windows/entryPoint.cc /Fo:"+enginePath)
    runCmd("cl /nologo /Z7 /std:c++14 -c /I include /I vendor/glm/ " + gameMain + " /Fo:" + folder + "game.obj")

runCmd("link /NOLOGO /DEBUG /PDB:" + folder + "crystal.pdb " + folder + "game.obj " + folder + "crystal.obj " + imguiPath + " " + gladPath + " /OUT:" + folder + "crystal.exe")

if(shouldRun): runCmd(folder+"crystal.exe")

'''
rls- Release
dbg- debug
and- Android
win- Windows
'''
