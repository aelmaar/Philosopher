# Philosophers

## Overview
This project involves simulating the dining philosophers problem to learn about threads and synchronization. The objective is to precisely time a group of philosophers on when to pick up forks and eat spaghetti without succumbing to hunger.

## Project structure

The project is divided into two parts:
- **Mandatory part**
  - Implement the simulation using threads and mutexes, Philosophers must synchronize their actions to avoid conflicts over shared resources, such as forks.
- **Bonus part**
  - Implement the simulation using processes and semaphores, adding an additional layer of complexity to the synchronization problem.

## Usage

To run the `philosophers` program:
1. Clone the repository:
```bash
git clone https://github.com/aelmaar/Philosopher.git
```
2. Navigate to the project directory
3. Navigate to `philo` directory fot the mandatory part or `philo_bonus` for the bonus part
4. Build the **Philosophers** program using `make`
5. Run the program with the desired parameters:
```
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat](OPTIONAL)
```
## Example:
![](https://github.com/aelmaar/GIFS/blob/master/philosophers.gif)
