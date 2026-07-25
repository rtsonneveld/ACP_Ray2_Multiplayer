# Building the project

https://learn.microsoft.com/en-us/vcpkg/get_started/get-started-vs?pivots=shell-powershell
1. Download and install cmake (https://cmake.org/)

2. Make sure vcpkg is installed using the Visual Studio Installer

3. Open the project folder in Visual Studio and in the terminal run `vcpkg install --triplet x86-windows`

4. Right click the project in the Solution Explorer and switch to CMake Targets View.

5. Clone and build ACP_Ray2 (https://github.com/raytools/ACP_Ray2) and set the environment variable "acplib" to the \bin\ folder of the ACP_Ray2 project.

6. Set the environment variable "rayman2" to the Mods folder inside your Rayman 2 installation, e.g. "C:\Games\Rayman 2\Mods" (create if it doesn't exist).

7. You can now build the project.