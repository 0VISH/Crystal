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
shouldBuildEditor = "editor" in argv

gameMain = None
plat = None
for i in argv:
    if i.startswith("main:"):
        gameMain = i[len("main:"):]
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
    buildUsual = "cl /nologo /Z7 /std:c++14 -c "
    imguiPath  = folder + "imgui.obj"
    gladPath   = folder + "glad.obj"
    enginePath = folder + "crystal.obj"
    editorPath = folder + "editor.obj"
    if not os.path.isfile(imguiPath):   shouldBuildIMGUI  = True
    if not os.path.isfile(gladPath):    shouldBuildGLAD   = True
    if not os.path.isfile(enginePath):  shouldBuildEngine = True
    if not os.path.isfile(editorPath):  shouldBuildEditor = True
    if(shouldBuildIMGUI):
        runCmd(buildUsual + "/I include/ /I vendor/imgui/ src/Windows/imgui.cc /Fo:"+imguiPath)
    if(shouldBuildGLAD):
        runCmd(buildUsual + "/I vendor/glad/include/ vendor/glad/src/glad.c /Fo:"+gladPath)
    if(shouldBuildEngine):
        runCmd(buildUsual + "/I include/ /I vendor/imgui/ /I vendor/glad/include/ /I vendor/glm/ src/Windows/entryPoint.cc /Fo:"+enginePath)
    if(shouldBuildEditor):
        runCmd(buildUsual + "/I vendor/imgui/ /I vendor/glm/ /I include/ editor/editor.cc /Fo:" + editorPath)
    runCmd(buildUsual + "/I include/ /I vendor/imgui/ /I vendor/glm/ " + gameMain + " /Fo:" + folder + "game.obj")

runCmd("link /NOLOGO /DEBUG /PDB:" + folder + "crystal.pdb " + folder + "game.obj " + folder + "crystal.obj " + imguiPath + " " + gladPath + " " + editorPath + " /OUT:" + folder + "crystal.exe")

if(shouldRun): runCmd(folder+"crystal.exe")

'''
rls- Release
dbg- debug
and- Android
win- Windows
'''
