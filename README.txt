Documentation Author: Niko Procopi 2019

This tutorial was designed for Visual Studio 2017 / 2019
If the solution does not compile, retarget the solution
to a different version of the Windows SDK. If you do not
have any version of the Windows SDK, it can be installed
from the Visual Studio Installer Tool

Welcome to the Materials Tutorial!
Prerequesites: Finish the intro tutorials

Inside our Materials.cpp, we handle binding and unbinding,
of shaders, matrices, textures, and uniforms. Each of these
topics have been covered in previous tutorials, except now it
has been moved, to make the code more organized.

Each object in the world will have its own material, and materials
can have different materials applied to them at any time. Every
tutorial in this section will use the Materials class
