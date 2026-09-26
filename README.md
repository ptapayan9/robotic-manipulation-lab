# Robotic Tabletop Arm Manipulation

A robotics project building toward a tabletop arm that can pick up and place objects. It starts with joint control in C++20, then progresses toward physics simulation, learned manipulation, and eventual deployment on a physical arm.

The intended end-to-end task is to observe an object on a table, move the arm to grasp it, verify the grasp, and place it at a destination. The project develops these capabilities incrementally, beginning with the feedback calculations behind a single joint.

## What it does today

The current program is a command-line numerical model of one rotating joint. It:

- Validates a target angle against permitted joint limits.
- Calculates position error as target minus current angle.
- Uses proportional feedback to turn that error into a requested angular velocity.
- Updates the angle in fixed modeled time steps.
- Stops when the angle is within tolerance or the update limit is reached.
- Prints modeled time, angle, commanded velocity, and the final position error.

This is an idealized calculation: the joint follows the requested velocity perfectly. Physics, rendering, grasping, and hardware control are not implemented yet.

## Build and run

Requires a C++20-compatible compiler, such as Clang or GCC. From the repository root:

```sh
mkdir -p build
c++ -std=c++20 -Wall -Wextra -pedantic src/main.cpp -o build/robot_lab
./build/robot_lab
```

The example settings are defined in `src/main.cpp`:

| Setting | Value |
| --- | --- |
| Initial angle | 0.2 rad |
| Target angle | 0.5 rad |
| Permitted target range | −1.0 to 1.0 rad |
| Proportional gain | 2.0 s⁻¹ |
| Time step | 0.1 s |
| Position tolerance | 0.01 rad |
| Maximum updates | 20 |

With these settings, the program reaches approximately **0.491556 rad after 16 updates**, leaving an error of approximately **0.00844425 rad**. Those updates represent 1.6 seconds of modeled motion; execution does not wait for real time to pass.

## Project direction

Future work will extend this foundation to bounded velocity commands, joint dynamics in MuJoCo, and a simulated arm performing pick-and-place tasks. Python-based learning workflows will support exploration of imitation learning and evaluation of manipulation policies. Physical hardware comes later, after the simulation and control foundations are established.

Immediate motion control and stopping will remain local to the robot. Workflow orchestration, experiment storage, and observability will be introduced as the project grows and needs them.
