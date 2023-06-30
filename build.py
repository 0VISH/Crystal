from sys import argv
from subprocess import run
import os

def runCmd(cmd):
    print("[CMD]", cmd)
    if(run(cmd).returncode != 0): quit()

isDbg = not("rls" in argv)
plat = "win"
if("and" in argv): plat = "and"
shouldRun = "run" in argv
shouldBuildIMGUI  = "imgui" in argv
shouldBuildGLAD   = "glad" in argv
shouldBuildVENDOR = "vendor" in argv

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
    imguiPath = folder + "imgui.obj"
    gladPath  = folder + "glad.obj"
    if not os.path.isfile(imguiPath): shouldBuildIMGUI = True
    if not os.path.isfile(gladPath): shouldBuildGLAD = True
    if(shouldBuildIMGUI):
        runCmd("cl /nologo /Z7 /I vendor/imgui/ src/Windows/imgui.cc -c /Fo:"+imguiPath)
    if(shouldBuildGLAD):
        runCmd("cl /nologo /Z7 /I vendor/glad/include/ vendor/glad/src/glad.c -c /Fo:"+gladPath)
    if(isDbg):
        runCmd("cl /nologo /Z7 /std:c++14 -c /I vendor/glad/include/ /I vendor/glm/ /I vendor/imgui/ src/Windows/entryPoint.cc /Fo:" + folder + "crystal.obj")

runCmd("link /NOLOGO /DEBUG /PDB:" + folder + "crystal.pdb " + folder + "crystal.obj " + imguiPath + " " + gladPath + " /OUT:" + folder + "crystal.exe")

if(shouldRun): runCmd(folder+"crystal.exe")

'''
rls- Release
dbg- debug
and- Android
win- Windows
'''
