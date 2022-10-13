# Task for company
## How to use

- launch server in bash or cmd with `-ip 127.0.0.1` `-port 2001`, use w/s or down/up for navigation (all information in [FManager.git](https://github.com/ArtemBystrovOfficial/FManager))
- you can open logs or check online list for usability
- launch client, and if you don't have error,then client connected to server
- make all operation with task
- designed in such a way as to show all the states and their errors

## Dependencies
All elements support cross-ming
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
  - `cmake` and `build` server and client
  - server build in any enviroment, client you can build in qt creator (Qt 6.4.0) or by cmake
  - don't forget add qt dlls (Win) , to client excecutable for launch not in qt creator
- Or dowload executables ( client / server )
  - [Linux(x64)](https://drive.google.com/drive/folders/1SCg0zZtYdAG-fSqRu0q5NHu_OcZUkzB1?usp=sharing)
  - [Windows(x64)](https://drive.google.com/drive/folders/1TueNXhj2bQn7kUi3OQeKhPqCSbACTsAE?usp=sharing)

## Screenshots
![out](https://user-images.githubusercontent.com/92841151/195632019-9baebc7e-2f88-46a9-9d5f-9fe0317944b5.png)

## Feed

bystrov.official.one@gmail.com
