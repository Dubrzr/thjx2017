User manual for the EPITA thjx2017 project. This manual describes how to
generate the user environment, build the tools to do it and compile your
champions to play the NOSE and MUR game.

# Installation

## Dépendances
This project depends on the ``stechec2`` project, therefore you will need to
clone, configure, build and install it.

Warning: ``stechec2`` only works/runs/builds on linux

### Debian/Ubuntu

Install the dependencies:

    apt-get install gcc python3 libzmq3-dev libzmqpp-dev libgflags-dev \
                    libgtest-dev ruby python3-yaml

Install the language dependencies (take only what you need/want):

    apt-get install libphp5-embed php5-dev php5  # PHP
    apt-get install python3-dev  # Python
    apt-get install ocaml  # Ocaml
    apt-get install mono-devel  # C#
    apt-get install openjdk-8-jdk  # Java
    apt-get install haskell-platform  # Haskell

### Archlinux

Install the dependencies:

    pacman --needed -S gcc zeromq gtest ruby python-yaml gflags

Install the language dependencies (take only what you need/want):

    pacman -S --needed php php-embed  # PHP
    pacman -S --needed ocaml  # Ocaml
    pacman -S --needed mono  # C#
    pacman -S --needed jdk8-openjdk  # Java
    pacman -S --needed haskell-platform  # Haskell

## Stechec2 + THJX2017

The installation procedure follows a simple common patter with one exception
you will have to clone ``thjx2017`` before building/configuring ``stechec2``.

    git clone https://bitbucket.org/prologin/stechec2
    git clone https://github.com/Dubrzr/thjx2017.git stechec2/games/thjx2017

    ./waf.py configure --with-games=thjx2017 --prefix=/usr
    ./waf.py build
    sudo ./waf.py install

# Generate your projet

We are now going to use the tools we just installed to generate your environment
to generate your project:

    stechec2-generator player thjx2017 path/to/your/project

You can now choose any language you would like to code in and type
your code in the corresponding folder. You can remove the folders you
won't be coding in.

# Run a local match

If you wish to test your AI you will need to create a ``config.yml`` which will
describe the game setup.
Here is a simple example:

    rules: /usr/lib/libthjx2017.so
    verbose: 3
    clients:
      - ./champion.so
      - ./champion.so
    names:
      - Player 1
      - Player 2

Once this file has been created and filled with the correct informations to run the
math you only need to call the following commands:

    make
    stechec2-run ./config.yml

Important: ``make`` only needs to be called once in python
Important: ``stechec2-run`` has many options which you can lookup with
           ``stechec2-run -h`` (such as ``stechec2-run -d`` which lanches
           a GDB client)

# Send us your code

You will be able (in the near future) to test your code on our website.
To send us your code as a tarball, run the following command:

    make tar
