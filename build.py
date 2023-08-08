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
shouldBuildEditor = "editor" in argv
shouldBuildBox2d  = "box2d"  in argv

plat = None
for i in argv:
    if i.startswith("plat:"):
        plat = i[len("plat:"):]
if(plat == None):
    plat = "win"

if(shouldBuildVENDOR):
    shouldBuildIMGUI = True
    shouldBuildGLAD  = True
    shouldBuildBox2d = True

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
    box2dPath  = folder + "box2d.obj"
    if not os.path.isfile(imguiPath):   shouldBuildIMGUI  = True
    if not os.path.isfile(gladPath):    shouldBuildGLAD   = True
    if not os.path.isfile(enginePath):  shouldBuildEngine = True
    if not os.path.isfile(editorPath):  shouldBuildEditor = True
    if not os.path.isfile(box2dPath):   shouldBuildBox2d  = True
    if(shouldBuildIMGUI):
        runCmd(buildUsual + "/I include/ /I vendor/imgui/ src/Windows/imgui.cc /Fo:"+imguiPath)
    if(shouldBuildGLAD):
        runCmd(buildUsual + "/I vendor/glad/include/ vendor/glad/src/glad.c /Fo:"+gladPath)
    if(shouldBuildEditor):
        runCmd(buildUsual + "/I vendor/imgui/ /I vendor/glm/ /I vendor/box2d/include/ /I include/ editor/editor.cc /Fo:" + editorPath)
        runCmd("link /NOLOGO /DEBUG /DLL /PDB:" + folder + "editor.pdb " + editorPath + " " + imguiPath + " /OUT:" + folder + "editor.dll")
    if(shouldBuildBox2d):
        runCmd(buildUsual + "/I vendor/box2d/include/ /I vendor/box2d/src/ src/box2d.cc /Fo:" + box2dPath)
    runCmd(buildUsual + "/I include/ /I vendor/imgui/ /I vendor/glad/include/ /I vendor/glm/ /I vendor/box2d/include/ src/Windows/entryPoint.cc /Fo:"+enginePath)

runCmd("link /NOLOGO /DEBUG /PDB:" + folder + "crystal.pdb " + folder + "crystal.obj " + gladPath + " " + box2dPath + " /OUT:" + folder + "crystal.exe")

if(shouldRun): runCmd(folder+"crystal.exe")

'''
rls- Release
dbg- debug
and- Android
win- Windows
'''
