# Time-Sharing Simulation

## A simple simulation of a time-sharing system with a round-robin scheduler

## Building

This project is cross-platform and can be built for Windows, macOS, and Linux
using CMake.

### Visual Studio (Windows)

1. Make sure Visual Studio is up to date and make sure you have the **Desktop Development with C++**
and **C++ CMake Tools for Windows** modules installed.

2. Find the **Startup Item** dropdown and choose `Simulation.exe`

3. Click the run button (or press **F5**) to build and execute the project.

_**NOTE:** you can also build the project through the_ **CMake Targets View** _in the solution explorer or from the menu by navigating to_ `Build > Build All`_._

### Command Line (macOS/Linux)

1. Clone the repository

    ```sh
    git clone https://github.com/Ryan-M-Smith/TimeSharingSimulation.git
    ```

2. Run the CMake build

    ```sh
    # For a production build, use `Production`
    cmake -S . -DCMAKE_BUILD_TYPE=Debug
    ```

3. Build the project

    ```sh
    make
    ```

4. Execute

    ```sh
    ./Simulation
    ```

## Cleaning

### Basic clean

```sh
make clean
```

### Full clean (removes all build files/diectories and audit logs)

```sh
make clean-all
```
