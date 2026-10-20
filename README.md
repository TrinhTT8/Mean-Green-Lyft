# Mean-Green-Lyft
This is an individual project for CSCE 1040.

The project serves as a booking system, similar to Uber, for customers and drivers at UNT.

## Building and running

```
make
./lyft
```

`make clean` removes the object files and the executable.

Data is saved to `passengers.dat`, `drivers.dat` and `rides.dat` when you exit. The file formats are unchanged, so data saved by the old version still loads.

## Refactor notes

The program keeps the same menus, prompts, features and save files. The code was reorganized to remove duplication, avoid unnecessary copying, and fix bugs that could crash the program or give wrong results.

### 1. Shared helpers (`utils.h` / `utils.cpp`, new)

The same snippets were copy-pasted dozens of times across the project. Each one is now a single function:

| Before (repeated in many places) | After |
|---|---|
| `for (int i = 0; i < s.length(); ++i) s[i] = tolower(s[i]);` (about 20 times) | `toLower(s)` / `equalsIgnoreCase(a, b)` |
| `cout << "..."; cin >> response; cin.ignore(); if (response == 'Y' \|\| response == 'y') ...` | `askYesNo("...")` |
| `cout << "..."; cin >> x; cin.ignore();` | `askInt("...")`, `askDouble("...")`, `askChar("...")`, `askLine("...")` |
| The 12-case vehicle type `switch` (3 copies) | `chooseVehicleType("...")` |
| `if (x == 1) cout << "Yes"; else cout << "No";` | `yesNo(x)` |
| "Search by 1 - Name / 2 - ID" prompt and matching loop (4 copies) | `askSearchKey("driver")` + `key.matches(...)` |

The input helpers also handle bad input. Before, typing a letter where a number was expected put `cin` into a failed state and the menu loop ran forever. Now the program says "Please enter a number" and asks again. If the input ends (for example Ctrl+D or a redirected file), `main` saves your data and exits instead of looping forever.

### 2. Driver class hierarchy (`tiereddriver.h` / `tiereddriver.cpp`, new)

`basic`, `economy`, `group` and `luxury` each had their own copy of the same members (`luggage`, `restrictions`, `type`), the same setters and getters, an almost identical `printDriver()`, and an identical `editDriver()`.

There is now a shared middle class:

```
Driver
└── TieredDriver        (luggage, restrictions, type, print and edit logic)
    ├── basic           (label "Basic",   price "$-$$")
    ├── economy         (label "Economy", price "$-$$")
    ├── group           (label "Group",   price "$$-$$$")
    └── luxury          (label "Luxury",  price "$$$-$$$$$", plus amenities)
```

Each driver type now only says what makes it different: its label and price range, and for `luxury`, the extra amenities field. All four classes still exist and still use virtual functions (polymorphism), but each one is about 10 lines instead of about 60.

Saving also uses polymorphism now. `Drivers::storeDri()` used a chain of four `dynamic_cast` checks to work out each driver's type. Now it calls the virtual `storeExtras()` once and each class writes its own data. Loading uses one `createDriver()` function instead of four nearly identical blocks.

`Drivers::addDri()` had four almost identical `case` blocks for the driver types. They are now one table of what differs (heading, price, capacity hint) plus one shared set of prompts.

### 3. Efficiency changes

- **Pass by `const&`.** Strings are passed to constructors and setters as `const string&`, and getters return `const string&`, so strings are no longer copied on every call. `Rides::editRide()` used to receive a full copy of the driver list (`vector<Driver*>` by value). It now takes a reference.
- **No re-lowercasing inside loops.** The old searches made a lowercase copy of *every* stored name on every comparison. `equalsIgnoreCase()` compares characters directly without making copies.
- **Constructor initializer lists** instead of assigning each member inside the constructor body.
- **Counts come from `vector::size()`.** `dricount` / `ridecount` with `inccount()` / `deccount()` were removed. They could drift out of sync with the list; for example, deleting a ride never decreased `ridecount`, so the next load read the wrong number of rides.
- **Deleting several rides happens in one pass** (`remove_if` + one `erase`) instead of erasing inside the loop.
- **`srand()` is called once** in `main()` instead of every time an ID is generated.
- **`const` methods** on everything that only reads data (print, find, store, getters).
- **Range-based `for` loops** (`for (Driver* d : driList)`) instead of manual iterators.
- **Shared search loops.** Every "find" menu option now uses one `printMatching(list, test)` function instead of its own copy of the loop.
- **Makefile rebuilt.** The old rules compiled other `.cpp` files inside unrelated targets (for example, `basic.o` also compiled `driver.cpp` and `drivers.cpp`), so files were compiled several times and the header dependencies were wrong. Now each `.o` is built from its own `.cpp`, depends on the headers it really includes, and builds with warnings on (`-Wall`).

### 4. Bugs fixed along the way

These were bugs in the original logic. They are fixed, so the program now does what the code and comments said it should:

| Where | Problem | Fix |
|---|---|---|
| `Ride::printRide` | `ctime()` reuses one buffer, so the pickup time was printed as the drop-off time (or as 1969 for rides that weren't finished) | Print each time right after converting it |
| `Rides::addRide` | Crashed when the ride was within 10 minutes (`driver` was always `nullptr`) | Mark the selected driver unavailable |
| `Rides::addRide` | With no matching drivers, it still asked you to pick one and created a ride with a garbage driver ID | Prints "No matching drivers found" and doesn't create the ride |
| `Rides::addRide` | Found up to 3 drivers but could only show 2 | Shows at most 2 available drivers, and only accepts a valid choice |
| `Rides::checkAvailability` | `convertTime()` swapped hour and minute, so a double booking was never detected | Compares the two pickup times directly |
| `Rides::editRide` | Party size and pets looked up the driver using the **ride** ID, and the pets option changed the **driver's** pet policy instead of the ride | Uses the ride's driver, and the pets option updates the ride |
| `Rides::editRide` | Looped forever if the ride was already in progress | Prints the message once and returns |
| `Rides::deleteRide` | Erasing inside the `for` loop skipped rides or went past the end; "can't delete an active ride" never showed; "no matching ride" printed even after deleting | Safe one-pass delete with the correct messages |
| `Rides::findRide` | Search by pets matched every ride when you answered Y (`\|\|` instead of `&&`); search by rating compared the **pets** field | Both search the right field |
| `Rides::printPassRides` | Always printed "Passenger has no rides yet" (the counter was never increased) | Only printed when there really are no rides |
| `Drivers::findDri` | Search by vehicle type, capacity or handicap printed only `basic` drivers (a leftover `typeid` check) | Prints all matching drivers |
| `Drivers::editDri` | `driverfound` and `searchid` were uninitialized, so it could edit the wrong driver or wrongly say "not found" | Initialized through `SearchKey` |
| `Drivers::addDri` | Picking an invalid driver type added an uninitialized pointer to the list (crash later) | Asks again until the choice is valid |
| `economy` / `group` / `luxury` `editDriver` | All said "You've signed up for Basic driver type." | Each shows its own type |
| `TieredDriver` (all driver types) | `type` was never set by the constructors (`getType()` returned `""`) | Set by each subclass |
| `Passengers::deletePass` | Removed the passenger without `delete` (memory leak) | Frees the memory |
| `Passengers::clearPass` | Freed the passengers but left dangling pointers in the list | Clears the list |
| `Passengers::findPass` | Search by payment never found "Paypal" passengers (stored with a capital P, compared in lowercase) | Case-insensitive compare |
| Vehicle type menus | An invalid choice set the vehicle type to an empty string | Asks again until the choice is valid |

Removed because nothing used them: `Rides::convertTime()` (it had the hour/minute bug above), `Drivers::printDriRides()` (declared but never written), and the `inccount()` / `deccount()` functions.
