<p align="center">
  <img src="https://github.com/Ego8316/Ego8316/blob/main/42-badges/philosophers.png" height="150" alt="42 Philosophers Badge"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/42-Project-blue" height="32"/>
  <img src="https://img.shields.io/github/languages/code-size/Ego8316/Philosophers?color=5BCFFF" height="32"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Linux-0a97f5?style=for-the-badge&logo=linux&logoColor=white" height="32"/>
  <img src="https://img.shields.io/badge/WSL-0a97f5?style=for-the-badge&logo=linux&logoColor=white" height="32"/>
</p>

# Philosophers

### 🎓 42 School – Final Grade: **125/100**

Classical Dining Philosophers simulation. Mandatory part uses threads and mutexes; bonus uses processes and POSIX semaphores to orchestrate forks and printing while avoiding starvation, deadlocks, and race conditions.

---

## 📦 Features
- Deterministic startup barrier so all philosophers begin together.
- Death detection watchdog (threads) and a meal-completion watchdog (bonus).
- Colored/emoji status logs with timestamps since simulation start.
- Precise sleeping helpers to minimize scheduler drift.
- Safe teardown: joins or kills children, frees memory, and cleans semaphores.

---

## 🛠️ Building
```bash
make          # build mandatory ./philo
make bonus    # build bonus ./philo_bonus
make clean    # remove object files
make fclean   # remove objects + binaries
make re       # rebuild from scratch
```
Requirements: `gcc`, `make`, POSIX threads, and POSIX semaphores (Linux/WSL recommended).

---

## 🚀 Usage
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_required]
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_required]
```
- `number_of_philosophers` (int > 0, capped by `MAX_PHILO`)
- `time_to_die` / `time_to_eat` / `time_to_sleep` in ms (int > 0)
- `meals_required` optional (int > 0): stop once every philosopher has eaten this many times
- The bonus binary spawns one process per philosopher and manages named semaphores; the mandatory binary uses threads and mutexes.

---

## 📄 License
MIT — see `LICENSE`.
