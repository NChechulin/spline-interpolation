# Cubic Spline Inerpolation

## Task

Implement [cubic spline interpolation](https://en.wikipedia.org/wiki/Spline_interpolation#Algorithm_to_find_the_interpolating_cubic_spline) and draw a graph for a given set of 2-dimensional points

## Input file format

Any text file with `2N` integer or floating point values. It **must not** contain any other data.
If the number of points is less than 3 or if there are at least 2 points with the same X coordinate the program will show an error messagebox.

Example:
```
-87.6083  32.7009
66.8744   42.2585
75.6633   44.6086
-55.5066  28.8486
46.2896   -12.5529
-51.2362  21.5556
78.5095   6.7208
95.6425   29.2169
-71.4888  -7.3083
-84.2601  9.0064
```

## Screenshots

Plot constructed using the sample file (`points.txt`)
On the left there's result of some [online tool](https://tools.timodenk.com/cubic-spline-interpolation) and the output of my program is on the right.

![](https://i.imgur.com/sSLk9dh.png)

## Project structure

```
|-- LICENSE                         
|-- README.md                       
|-- points.txt                      - Sample file with points
`-- src                             - Directory with source code
    |-- interpolation.cpp           - Logic for reading data and interpolating
    |-- interpolation.h             
    |-- main.cpp                    
    |-- mainwindow.cpp              - View logic
    |-- mainwindow.h                
    |-- mainwindow.ui               - Form
    |-- polynomial.cpp              - Class Polynomial
    |-- polynomial.h                
    |-- qcustomplot.cpp             - Library for plotting
    |-- qcustomplot.h               - Library for plotting
    `-- spline-interpolation.pro    - Qt project file
```
