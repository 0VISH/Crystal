from sys import argv
import os
import Omen

shouldRun = "run" in argv
shouldBuildIMGUI   = "imgui"   in argv
shouldBuildGLAD    = "glad"    in argv
shouldBuildVENDOR  = "vendor"  in argv
shouldBuildEditor  = "editor"  in argv
shouldBuildBox2d   = "box2d"   in argv
shouldBuildGuizmo  = "guizmo"  in argv
shouldBuildClean   = "clean"   in argv
dbg = not("rls" in argv)
plat = "win"
if "lin" in argv: plat = "lin"
renderingAPI = "gl"
renderingAPI = renderingAPI.upper()

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
    shouldBuildIMGUI  = True
    shouldBuildGLAD   = True
    shouldBuildBox2d  = True
    shouldBuildGuizmo = True

if(plat == "win"):
    Omen.build("src/Windows/entryPoint.cc", "crystal", "cl", extraSwitches="/I include/ /I vendor/imgui/ /I vendor/glad/include/ /I vendor/glm/ /I vendor/box2d/include/", intermediateOnly=True, defines=[renderingAPI])
    imguiPath  = folder + "imgui.obj"
    gladPath   = folder + "glad.obj"
    enginePath = folder + "crystal.obj"
    editorPath = folder + "editor.obj"
    box2dPath  = folder + "box2d.obj"
    guizmoPath = folder + "guizmo.obj"
    if not os.path.isfile(imguiPath): shouldBuildIMGUI = True
    if not os.path.isfile(gladPath): shouldBuildGLAD = True
    if not os.path.isfile(enginePath): shouldBuildEngine = True
    if not os.path.isfile(editorPath): shouldBuildEditor = True
    if not os.path.isfile(box2dPath): shouldBuildBox2d = True
    if(shouldBuildIMGUI):
        Omen.build("src/Windows/imguiFiles.cc", "imgui", "cl", intermediateOnly=True, extraSwitches="/I include/ /I vendor/imgui/", defines=[renderingAPI])
    if(shouldBuildGLAD):
        Omen.build("vendor/glad/src/glad.c", "glad", "cl", intermediateOnly=True, includes=["vendor/glad/include/"])
    if(shouldBuildBox2d):
        Omen.build("src/box2dFiles.cc", "box2d", "cl", intermediateOnly=True, includes=["vendor/box2d/include/", "vendor/box2d/src/"])
    if(shouldBuildGuizmo):
        Omen.build("vendor/imguizmo/ImGuizmo.cpp", "guizmo", "cl", intermediateOnly=True, includes=["vendor/imguizmo/", "vendor/imgui/"])
    if(shouldBuildEditor):
        Omen.build("editor/editor.cc", "editor", "cl", intermediateOnly=True, defines=[renderingAPI], includes=["vendor/imgui/", "vendor/glm/", "vendor/box2d/include/", "vendor/glad/include/", "vendor/imguizmo/", "include/"])
        Omen.runCmd("link /NOLOGO /DEBUG /DLL /PDB:" + folder + "editor.pdb " + editorPath + " " + imguiPath + " " + guizmoPath + " " + box2dPath + " /OUT:" + folder + "editor.dll")
    Omen.runCmd("link /NOLOGO /DEBUG /PDB:" + folder + "crystal.pdb " + folder + "crystal.obj " + gladPath + " " + box2dPath + " /OUT:" + folder + "crystal.exe")
    Omen.runCmd(folder + "crystal.exe")
