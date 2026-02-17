### Description 🅿️🚘

Design a parking system for a parking lot. The parking lot has three kinds of parking spaces: big, medium, and small,
with a fixed number of slots for each size.

Implement the `ParkingSystem` class:

* `ParkingSystem(int big, int medium, int small)` Initializes object of the `ParkingSystem` class. The number of slots
  for each parking space are given as part of the constructor.
* `bool addCar(int carType)` Checks whether there is a parking space of carType for the car that wants to get into the
  parking lot. `carType` can be of three kinds: big, medium, or small, which are represented by 1, 2, and 3
  respectively. A car can only park in a parking space of its `carType`. If there is no space available, return false,
  else park the car in that size space and return true.

### Game Plan

> 🇵🇱 Trzymasz stan parkingu jako trzy liczniki: `m_big_slots`, `m_medium_slots`, `m_small_slots`, inicjalizowane w
> konstruktorze. Metoda `addCar(carType)` dla każdego typu auta sprawdza, czy są wolne miejsca danego rozmiaru, jeśli
> tak – dekrementuje odpowiedni licznik i zwraca `true`, w przeciwnym razie ostatecznie zwraca `false`. Każde wywołanie
> działa w czasie $O(1)$ i pamięci $O(1)$.
>

> 🇬🇧 You represent the parking lot with three counters: `m_big_slots`, `m_medium_slots`, and `m_small_slots`, all
> initialized in the constructor. The `addCar(carType)` method checks if there is at least one free slot for the requested
> car size; if so, it decrements the corresponding counter and returns `true`, otherwise it eventually returns `false`.
> Each call runs in $O(1)$ time and uses $O(1)$ extra space. 

## Build & Run (CLI)

```bash
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug
```

```bash
./cmake-build-debug/app --help
./cmake-build-debug/app --big 1 --medium 1 --small 1 --cars 1 2 3 3
```

To run unit tests, suit, run 
```
./test_launcher.sh
```