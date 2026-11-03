# Philosophers

> A classic multithreading and concurrency project in C using threads and mutexes to solve the Dining Philosophers problem. 42 School Project.

## Overview

**Philosophers** is a project designed to teach the fundamentals of concurrent programming, process/thread synchronization, and race condition prevention. 

The goal is to simulate philosophers sitting around a table with a bowl of spaghetti in the middle. Philosophers alternate between **eating**, **thinking**, and **sleeping**. To eat, a philosopher must acquire two forks (represented by mutexes), one on their left and one on their right.

## Features

- **Multithreading**: Each philosopher is represented by an independent thread (`pthread_create`).
- **Mutex Synchronization**: Every fork is guarded by a mutex (`pthread_mutex_t`) to prevent data races and concurrent access.
- **Precision Timing**: Custom millisecond-accurate sleep function (`usleep` wrapper with `gettimeofday`).
- **Death Detection**: Real-time monitor thread to instantly log a philosopher's death if they starve.
- **Race Condition-Free**: Clean state management with dedicated mutexes for logging and status checking.

## ⚙️ Compilation & Installation

Compile the project using the provided `Makefile`:

```bash
git clone git@github.com:your-username/philosophers.git
cd philosophers/philo
make
```

The Makefile includes the standard 42 rules: `make`, `make clean`, `make fclean`, `make re`.

## 🚀 Usage

Execute the binary with the following arguments:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters

| Argument | Description |
| :--- | :--- |
| `number_of_philosophers` | The number of philosophers and forks on the table. |
| `time_to_die` (in ms) | Time limit in milliseconds a philosopher can go without eating before dying. |
| `time_to_eat` (in ms) | Time it takes for a philosopher to eat (holds two forks). |
| `time_to_sleep` (in ms) | Time a philosopher spends sleeping after eating. |
| `[number_of_times_each_philosopher_must_eat]` | *(Optional)* If all philosophers eat at least this many times, the simulation stops. |

### Examples

```bash
# Example 1: Philosopher should die
./philo 1 800 200 200

# Example 2: Normal simulation (no one dies)
./philo 5 800 200 200

# Example 3: Simulation stops after everyone eats 7 times
./philo 4 410 200 200 7
```

## Allowed Functions

- `memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`
- `pthread_create`, `pthread_detach`, `pthread_join`
- `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`