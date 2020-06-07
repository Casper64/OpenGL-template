# OpenGL-template

## Usage
1. Clone this repository and install the submodules
```
git clone https://github.com/Casper64/OpenGL-template.git
cd OpenGL-template
git submodule update --init --recursive
```
2. Add Imgui fork and switch to docking branch
```
git submodule add https://github.com/Casper64/imgui.git imguiWindow/vendor/imgui
cd imguiWindow/vendor/imgui
git checkout docking
```
3. Download premake5 and put it in {root}/vendor/bin/premake/premake5.exe
4. Click on GenerateProjects.bat and the Visual Studio 2019 solution will be generated
