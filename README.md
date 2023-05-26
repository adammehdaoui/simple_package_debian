# First Debian Package

## Description of the package : simple C code that finds the TOP 10 files (by size) in a directory

> Command to create the package (in the parent directory) :

```
sudo dpkg -c simple_package_debian
```

> Command to install the package :

```
sudo dpkg -i simple_package_debian.deb
```

> Once the package in installed, you can launch the command anywhere with  :

```
/largest_file <directory_name>
```
