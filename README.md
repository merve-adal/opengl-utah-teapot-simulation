# OpenGL Utah Teapot Interactive Simulation

This repository contains the complete implementation for **Utah Teapot**, developed as part of the **Computer Graphics** course at Aydın Adnan Menderes University. The project demonstrates core computer graphics concepts including 3D geometric transformations, camera and matrix management, multi-window synchronization, and advanced lighting models using **C++** and the **OpenGL/GLUT** libraries.

<img width="1009" height="534" alt="Ekran görüntüsü 2026-09-13 170354" src="https://github.com/user-attachments/assets/2498c74b-fa98-440b-a9cf-c2b759bd3d91" />

---

## Project Overview & Features

The application renders the classic **Utah Teapot** across two simultaneous, interactive windows, incorporating advanced visual enhancements for realism:

*   **Window 1 (Free Rotation):** 
    *   Renders the teapot in a **Perspective View**.
    *   Allows users to freely rotate the 3D model around its axis in real-time by dragging the mouse (left, right, or middle click).
*   **Window 2 (Fixed Angles & Pop-Up Menu):** 
    *   Features a context-aware **right-click pop-up menu** to switch viewing angles dynamically.
    *   Supports **Top, Bottom, Left, and Right** orthographic/perspective camera alignments.
    *   Applies distinct color coding per view (Top: Green, Bottom: Yellow, Left: Blue, Right: Turquoise) for easy identification.
*   **Advanced Realism (Bonus Features):**
    *   Utilizes solid geometry (`glutSolidTeapot`) instead of wireframes.
    *   Implements a custom lighting model (`GL_LIGHT0`) with ambient, diffuse, and specular components.
    *   Configures surface material properties (`glMaterialfv`) to simulate a sharp, porcelain-like shine (`GL_SHININESS = 100`).
    *   Enables depth testing (`GL_DEPTH_TEST`) to ensure correct surface occlusion and eliminate rendering artifacts.

---

## Code Structure & Architecture

The source code (`main.cpp`) is organized into modular functions handling distinct graphics pipelines:

*   `initLighting()`: Sets up depth testing, configures light source parameters (position, ambient, diffuse, specular), and defines surface material shine for porcelain reflections.
*   `reshape(int w, int h)`: Manages viewport scaling and maintains correct 3D aspect ratios using `gluPerspective`.
*   `display1()` & `display2()`: Independent rendering loops for both windows, handling matrix transformations (`glRotatef`) and camera positioning (`gluLookAt`).
*   `mouse1()` & `motion1()`: Interactive mouse listeners for Window 1 that calculate drag offsets to update rotation angles dynamically.
*   `menu(int value)`: Controls the view-switching logic for Window 2's right-click menu and triggers screen refreshes (`glutPostRedisplay`).
*   `main()`: Initializes GLUT, creates multi-window contexts using explicit IDs (`window1`, `window2`), links callback functions, and starts the event loop (`glutMainLoop`).

---

## Prerequisites & Dependencies

To compile and run this project locally, ensure you have the following installed:

*   **C++ Compiler** (GCC, Clang, or MSVC)
*   **OpenGL** libraries
*   **GLUT / FreeGLUT** development libraries

---

## How to Compile and Run

1. Clone the repository:
   ```bash
   git clone [https://github.com/merve-adal/opengl-utah-teapot-simulation.git](https://github.com/merve-adal/opengl-utah-teapot-simulation.git)
   cd opengl-utah-teapot-simulation
