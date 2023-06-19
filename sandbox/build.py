from sys import argv
from subprocess import run
import os

isDbg = not("rls" in argv)
isWin = not("and" in argv)

folder = "sandbox/bin/"
if not os.path.isdir(folder): os.makedirs(folder)

def runCmd(cmd):
    print("[CMD]", cmd)
    if(run(cmd).returncode != 0): quit()

runCmd("cl /nologo /Z7 /std:c++14 /I src/ sandbox/sandbox.cc -c /Fo:"+folder+"sandbox.obj")
runCmd("link /NOLOGO /DEBUG /PDB:" + folder + "sandbox.pdb " + folder + "sandbox.obj /DLL /OUT:" + folder + "sandbox.dll")
