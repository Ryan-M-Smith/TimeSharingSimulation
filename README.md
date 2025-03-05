# Time-Sharing Simulation

## A simple simulation of a time-sharing system with a round-robin scheduler

## Building

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
