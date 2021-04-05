# Cubic Spline Inerpolation

## Input file format

Any text file with `2N` integer or floating point values. It **must not** contain any other data.
If the number of points is less than 3 or if there are at least 2 points with the same X coordinate the program will show an error messagebox.

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
