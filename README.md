WeatherExplorer
===============

A spreadsheet style viewer for EnergyPlus weather files

## Description

This is very much a work in progress. It is regularly broken
and not working, so use at your own risk. 

The program gives a simple spreadsheet view of an EnergyPlus
EPW weather file. Empty cells indicate that values that are
not available.

## Building the Program

At present, build files are  provided for Qt Creator and 
CMake. The Creator file will go away soon. Otherwise, you'll
need:

* Qt - I build with Qt5, but it might still work with 4.

* boost - I build with version 1.55, but earlier versions might work.

