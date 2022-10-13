# Task for company
## How to use

- launch server in bash or cmd with `-ip` `-port`, use w/s or down/up for navigation ( all information in FManager )
- you can open logs or check online list for usability
- launch client, and if you don't have error,then client connected to server
- make all operation with task
- designed in such a way as to show all the states and their errors

## Dependencies
All elements support cross-rming
```git
                  [task1](main)
                  /           \
                /               \
              /                   \
          [server]               [client]
            |                      / \
[FServerManager].git             /    \
  (TaskSession)                /       \
               \             /       [QML / Qt Libs(6.2+)]
                \          /
                  [FServer2.0.git](main)
                     |           |
                     |           |
                   [ASIO]   [googletest]
```

## Installation

Two ways:
- With `build` to your platform
  - `git clone` repository
  - `git submodule update --force --remote --init --recursive`
  - `cmake` and `build` files then run build
  - don't forget add qt dlls, to client excecutable for launch not in qt creator
- Or dowload executables ( client / server )
  - Linux(x64)
  - Windows(x64)

## Screenshots

## Feed

bystrov.official.one@gmail.com
