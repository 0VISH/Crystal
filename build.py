from sys import argv
import os
import Omen

shouldRun = "run" in argv
shouldBuildIMGUI   = "imgui"   in argv
shouldBuildGLAD    = "glad"    in argv
shouldBuildVENDOR  = "vendor"  in argv
shouldBuildEditor  = "editor"  in argv
shouldBuildBox2d   = "box2d"   in argv
shouldBuildClean   = "clean"   in argv
dbg = not("rls" in argv)
plat = "win"
if "lin" in argv: plat = "lin"
renderingAPI = "gl"

Omen.setBuildDir(plat, dbg)
folder = Omen.getBuildDir()

if "package" in argv:
    if not os.path.isdir("package/bin/"): os.makedirs("package/bin/")
    extra = "/EHsc /I include/ /I game/"
    Omen.build("package/main.cc", plat, dbg, "package", extraSwitches=extra)
    quit()

if(shouldBuildClean):
    shouldBuildVENDOR = True
    shouldBuildEditor = True
if(shouldBuildVENDOR):
    shouldBuildIMGUI = True
    shouldBuildGLAD  = True
    shouldBuildBox2d = True

if(plat == "win"):
    Omen.build("src/Windows/entryPoint.cc", "crystal", "cl", extraSwitches="/I include/ /I vendor/imgui/ /I vendor/glad/include/ /I vendor/glm/ /I vendor/box2d/include/", intermediateOnly=True, defines=["RCONTEXT_GL"])
    imguiPath  = folder + "imgui.obj"
    gladPath   = folder + "glad.obj"
    enginePath = folder + "crystal.obj"
    editorPath = folder + "editor.obj"
    box2dPath  = folder + "box2d.obj"
    if not os.path.isfile(imguiPath): shouldBuildIMGUI = True
    if not os.path.isfile(gladPath): shouldBuildGLAD = True
    if not os.path.isfile(enginePath): shouldBuildEngine = True
    if not os.path.isfile(editorPath): shouldBuildEditor = True
    if not os.path.isfile(box2dPath): shouldBuildBox2d = True
    if(shouldBuildIMGUI):
        Omen.build("src/Windows/imgui.cc", "imgui", "cl", intermediateOnly=True, extraSwitches="/I include/ /I vendor/imgui/", defines=["RCONTEXT_GL"])
    if(shouldBuildGLAD):
        Omen.build("vendor/glad/src/glad.c", "glad", "cl", intermediateOnly=True, extraSwitches="/I vendor/glad/include/")
    if(shouldBuildEditor):
        Omen.build("editor/editor.cc", "editor", "cl", intermediateOnly=True, extraSwitches="/I vendor/imgui/ /I vendor/glm/ /I vendor/box2d/include/ /I include/", defines=["RCONTEXT_GL"])
        Omen.runCmd("link /NOLOGO /DEBUG /DLL /PDB:" + folder + "editor.pdb " + editorPath + " " + imguiPath + " /OUT:" + folder + "editor.dll")
    if(shouldBuildBox2d):
        Omen.build("src/box2dInclude.cc", "box2d", "cl", intermediateOnly=True, extraSwitches="/I vendor/box2d/include/ /I vendor/box2d/src/", defines=["RCONTEXT_GL"])
    Omen.runCmd("link /NOLOGO /DEBUG /PDB:" + folder + "crystal.pdb " + folder + "crystal.obj " + gladPath + " " + box2dPath + " /OUT:" + folder + "crystal.exe")
    Omen.runCmd(folder + "crystal.exe")
