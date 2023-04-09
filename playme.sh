#!/bin/sh

source $(root-config --bindir)/thisroot.sh

cd calcum

make clean && make -j4 cum
./Cum.sh

cd ../plot
make clean && make first && ./first 2 && ./first 4 && ./first 0
root -b -q second_cumulants.cpp
root -b -q third.C


# Get the operating system
os_name=$(uname)

if [ "$os_name" = "Linux" ]; then
  # Check for the existence of lsb_release command
  if command -v lsb_release >/dev/null 2>&1; then
    distro=$(lsb_release -is)
    if [ "$distro" = "Ubuntu" ]; then
      # Ubuntu specific command
      gnome-open output/pics/
    else
      # Other Linux distribution specific command
      xdg-open output/pics/
    fi
  else
    # If lsb_release is not available, use a generic Linux command
    xdg-open output/pics/
  fi
elif [ "$os_name" = "Darwin" ]; then
  # macOS specific command
  open output/pics/
else
  echo "Unsupported OS: $os_name"
fi


cd ../
