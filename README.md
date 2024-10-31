# Raytracing Demo
The goal of this program is to demonstrate a single-core implementation of a path tracer.

Quick Disclaimer: I am not claiming that this is the only way (or the most efficient way) to run a Raytracer, far from it. The goal of this is to be able to learn and show others the fundamentals of raytracing.

Additionally, this was an in-course academic assignment, and therefore had compatibility constraints set by the professor. The entry point, minimum features and styles were all chosen for me, and many of the paths were hard-coded to be used in computer labs at the university.
** Please take a look and edit the `CMakeLists.txt` file before compiling to ensure it works on your specific hardware and file system. **

## Compilation
1. Clone the repository using:
```
git clone https://github.com/brandon-tol/RayTracer/
```
2. Create the build folder and generate build files using CMake
*NOTE: This project requires GLFW, GLEW, and GLM. Seeing a this program was intended as a part of a school project, the paths are hard-coded to work on the computers there. Change the `CMakeLists.txt` file in the root of the repo if you want to compile this on a personal machine*
```
mkdir build
cd build
cmake .. 
```
3. Compile it using the method of your choice.
For the sake of this project, the build was generated in Visual Studio 2022 and Visual Studio 2019 on Windows, as well as with the g++ compiler on Linux.
NOTE: It is highly recommended to build in Release mode, regardless of the compiler chosen.

## Run
* First, you will need to have a specification file.
  * Use the examples provided in /Assets/ to learn some of the capabilities. It is all done in JSON.
* Locate the built executable and run it with one command line argument as such:
```
<path to executable>/RayTracer.exe <path to specification file>
```
* Once it parses, the program will begin generating the image, with the text `Running student solution`. Please be patient as this process can take some time, and depends on hardware.
* The program is finished once it outputs the amount of time it took, (e.g. 'It took 200 second(s)').
* The output file can be found in the same directory the command was run from. It will have the same name as the chosen specification file, with the file extension `.ppm`. Note that not all image viewers can view .ppm files. I recommend using [GIMP](https://gimp.org), but there are many other free solutions.
