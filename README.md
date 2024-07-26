# Smart Printer System Simulation
The project aimed to simulate a smart printer system. Jobs were prioritized and served based on arrival time and priority using a queue. Statistics included printer usage, completion time, average/max waiting time, and popular job types.

## Overview

This project simulates a smart printer system that manages and processes print jobs using a queue. The simulation accepts command-line arguments to configure the number of jobs, number of printers, maximum arrival time, and maximum service time. It generates random print jobs, processes them, and then reports various statistics related to the print jobs and printer usage.

## Features

- **Random Job Generation**: Jobs are randomly generated with attributes such as arrival time, service time, job request type, job request info, and job type.
- **Priority-Based Job Processing**: Jobs are processed based on their arrival time and priority.
- **Statistics Reporting**: The simulation reports statistics such as the number of jobs processed by each printer, average waiting time, maximum waiting time, and the most popular job request type.

## Getting Started

### Prerequisites

- A C compiler (e.g., `gcc`)

### Compilation

To compile the program, run:

```sh
gcc -o smart_printer main.c queue.c
```

### Running the Program

To run the program, use the following command:

```sh
./smart_printer <number_of_jobs> <number_of_printers> <max_arrival_time> <max_service_time>
```

For example:

```sh
./smart_printer 10 3 20 5
```

This command runs the simulation with 10 jobs, 3 printers, a maximum arrival time of 20 units, and a maximum service time of 5 units.

## Code Structure

### Main Function

The `main` function initializes the simulation, generates jobs, processes them, and finally reports statistics.

### Helper Functions

1. **`parseInput`**: Parses command-line arguments and stores them in an array.
2. **`initialiseSimulator`**: Initializes the queue and printer availability array.
3. **`isemptyqueue`**: Checks if the queue is empty.
4. **`MakeEmptyQueue`**: Initializes the queue with a dummy node.
5. **`createJobList`**: Generates a linked list of jobs with random attributes and sorts them by arrival time.
6. **`Generate_Random_Value`**: Generates random values for job attributes (type, request info, request type).
7. **`newJob`**: Adds a new job to the queue.
8. **`serveJob`**: Dequeues a job from the queue based on the current time and job priority.
9. **`assign_priority`**: Assigns priority to a job based on its type.
10. **`reportStatistics`**: Reports the simulation statistics after all jobs are processed.

### Data Structures

- **Queue**: Used to manage the print jobs waiting to be processed.
- **Node**: Represents a print job with attributes such as arrival time, service time, job request type, job request info, job type, and priority.

## Detailed Description

### Main Function

- **Random Seed Initialization**: Ensures different random values are generated each time the program runs.
- **Command-Line Argument Parsing**: Stores command-line arguments in the `information` array.
- **Variable Initialization**: Initializes various arrays and variables to keep track of job types, printer availability, job statistics, etc.
- **Queue Initialization and Job Generation**: Initializes a queue (`Job`) and generates a linked list of jobs, which are then sorted by arrival time.
- **Job Processing**: The main while-loop processes jobs, assigning them to available printers and calculating waiting times.
- **Statistics Reporting**: Reports various statistics once all jobs are processed.

### Helper Functions

Each helper function performs a specific task such as parsing input, initializing data structures, generating random job attributes, adding jobs to the queue, serving jobs based on priority, and reporting statistics.

### Data Structures

- **Queue**: Manages the print jobs waiting to be processed.
- **Node**: Represents a print job with various attributes.

## Example Output

An example output of the program might look like this:

```plaintext
***************Smart Printer Statistics*****************
The number of printers: 3
The number of jobs: 10
The number of jobs for each job type:
    Short: 5
    Medium: 1
    Long: 4
The number of jobs for each printer:
    Printer 1: 5
    Printer 2: 3
    Printer 3: 2
Completion time: 25
Average time spent in the queue: 1.6
Maximum waiting time: 5
Popular job request type: Assignment
Popular job request info: Same
************************************************************
```

## Conclusion

This project demonstrates a simulation of a smart printer system using C programming. It covers job generation, queue management, priority-based job processing, and reporting of relevant statistics. The simulation can be customized by changing the command-line arguments for different configurations.
