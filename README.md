# AKernelADay
## Overview
This repository is being put together to give a step by step OS development process. Each day we will be attempting to apply a new concept or advance on an existing concept till we get to a fully functioning OS. This OS will contain as many features as I can pack in. However, we will initially be focusing on the simple concepts first: System Call wrappers, I/O (such as Ethernet or USB), etc. This project will not include any of the Standard C Libraries (we will use some of their header files to save time and energy), this means we are flying solo here. The first few weeks to months will be spent researching how an OS and kernel interact. Then a simple implementation will be made (basic concepts only, get the basics down: Hello World, Basic Drawing, Networking, etc). Then the next stage is to get a more detailed implementation down (multiple processes running, drivers, etc). Finally we will lower priviledge down to userspace and will implement individual users and user programs.

# Journal Entries
## Day ∅: Initial Commit - Project Structure
Each day that passes will be documented as to maintain a sort of "engineers journal". Today will be spent organizing my ideas and aproaches on how I want to handle/go about the project. All of my research will be documented under a folder labeled "Research" and the files (Markdown, ".md") will be seperated by concept and/or day. All source files will be placed under the folder "Source" and will be seperated out into individual sub-project folders. Common header ".h" files will be placed in a master "Include" folder (and any subfolders). Now, C was chosen because of its simplistic design and nature and C++ will most likely be integrated later in the project. C++ was not choosen for the project initialy due to some of the addon behaviors. C requires that you only implement a simple \_start function (as seen at https://en.wikipedia.org/wiki/Crt0) where as C++ requires a slightly more complex implementation (which is handled mostly by stdlib and we aren't using that). For initial OS development (at least in the init program) it should be dedicated to C to reduce complexity and possible bugs.

# Schedule/Backlog
## Day 0: Initial Research - Who is the kernel and what do they do?
## Day 1: Research - Who takes over after the kernel and what do they do?
## Day 2: Research - Integrating C with Assembly.
## Day 3: Initial Coding - Implementing crt0, main and system calls.
## Day 4: Coding - Libraries and migrating system calls.
## Day 5: Coding - Example programs (display, networking, and filesystem).
## Day 6: Refactor - Summarise what we have learned and improve code.
