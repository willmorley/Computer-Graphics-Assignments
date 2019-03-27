# Computer-Graphics-Assignments
This is a repository to store and show my work for a 4th year UofT computer graphics course.

Each assignment's individual README outline's some background on the material followed by the assignment tasks and contraints.

Note: all assignments are implemented in C++

## Assignment 1: Raster Images
RGB/A image manipulations including rotations, shifts, mosaicing, hue/saturation conversions, and superimposing images. 

## Assignment 2: Ray Caster
Created a basic ray caster using the Eigen linear algebra library. Shot rays into a scene to pseudo-render a multitude of shapes including spheres, planes, triangles, and the Stanford Bunny.

## Assignment 3: Ray Tracer
Extended assignment 2 to create a basic ray tracing rendering engine. Works by shooting rays through a screen and simulating it's effects as it interacts with the objects and light sources in the scene. This is the prefered method of rendering animations and is used by firms like Pixar.

## Assignment 4: Bounding Volume Hierarchies
Implemented multiple techniques to improve algorithmic performance of a ray tracer. This involved encapsulating the object in a tree of bounding boxes allowing for fast tree search algorithms to test for intersection as opposed to brute force methods. Implemented both object partitioning structures and space partitioning structures which also allowed for fast object intersection tests.

## Assignment 5: Meshes
Worked with mesh data structures to represent and manipulate complex objects in 3D space. Created texture maps of a Rubik's Cube and a globe and mapped them to a cube and sphere respectively. Included implementation of Blinn-Phong shading model. Finally implemented Catmull-Clark subdivision to increase the resolution of a mesh (yellow rubber duck).

## Assignment 6: GLSL Shader Pipeline
Wrote all shaders and suplementary functions needed to implement multiple animated models of the moon circling the earth. Each implementation increased the complexity of the final rendering and included implementations of upscaling the surface resolution, Blinn-Phong shading, and Perlin noise generators.

## Assignment 7: Kinematics
(Will add as soon as submission period closes)

## Final Image Competition: TBD
Open ended competition to make the best computer generated image/scene in the class. For bonus marks. Note: Optional project to do if I have time.
