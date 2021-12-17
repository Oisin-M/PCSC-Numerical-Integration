# Project 5 - Numerical Integration

*https://gitlab.epfl.ch/majoor/project-5-numerical-integration*

*Note: this documentation expects a linux distribution e.g. [Ubuntu](https://ubuntu.com/)*

### Compiling the Program for the First Time
The following steps should be undertaken to run our code
- clone the repository with 
```
git clone git@gitlab.epfl.ch:majoor/project-5-numerical-integration.git
```
- move to the cloned directory
```
cd project-5-numerical-integration/
```
- fetch the submodules (Eigen and Googletest) using 
```
git submodule update --init
```
- build the executable using CMAKE 
```
mkdir build
cd build
cmake ..
make
```
- run the executable 
```
./integration
```

This code will produce the following output:
```
Successfully opened file ../readfile.txt

---Input Data---

D: 2
m: 2
boundsX: 
1 2
6 7
boundsY: 
  5   6
  8 9.5
noSteps: 
10 11
 3 10
coefficients: 
  (1,1) (15,-5) (-2,11) (1,3.6)
 (5,-6)  (10,1)   (0,0)   (0,0)

---Integration Methods---

MidpointFormula:
[ 199.819 + 388.072i,
125 + -3.75i ]

TrapezoidalRule:
[ 199.863 + 388.231i,
125 + -3.75i ]

SimpsonsRule:
[ 199.833 + 388.125i,
125 + -3.75i ]

```

### Configuring the Program
To run the program with different integrals and different domains of integration, the input file `readfile.txt` can be configured. An example of the format required is shown below:

![image showing file structure](../README_Images/file_structure.PNG)

The first line details the length of inputs the program should expect. The lines (a), (b), (c) and (d) are then read as follows:
- *(a)* first domain is between x=1 and x=2, y=5 and y=6 and the integration method undergoes 10 steps in the x direction and 11 steps in the y direction
- *(b)* first domain is between x=6 and x=7, y=8 and y=9.5 and the integration method undergoes 3 steps in the x direction and 10 steps in the y direction
- *(c)* first function output reads 1+1i + (15-5i)x + (-2+11i)y + (1+3.6i)x^2
- *(d)* second function output reads 5-6i + (19+1i)x + (0+0i)y + (0+0i)x^2

*Note: to configure a 1D integration task, it suffices to set all coefficients of y^n terms to 0, and to set the y-bounds to differ by 1.*

### Typical Program Usage
A typical execution would be to edit the configuration file `readfile.txt` to indicate a new integration problem, and then to simply rerun the program
with `./integration` and view the results of the methods.

### Program Features
- Reads arbitrary input from file
- Implementation of 3 integration methods in 2D and 1D
- Error handling
- Individual testing of all features
- Documentation of all code
- Extensible code due to polymorphic approach

### Tests
To execute tests, it suffices to run
```
./Tests
```
from the `build/` directory.

Two types of test are run using googletest :
- Tests of the text file reader
- Tests of the integration methods

For the reader, we execute a few death tests to ensure that the first inputs are asserted to be positive.

For the integration, we run tests on polynomials of 4 values of l (l is defined above).
- For l=1, we integrate a constant function and expect an exact solution for all 3 methods.
- For l=3, we expect an exact solution for midpoint and Simpson but an approximate solution for trapezoidal.
- For l=6, we expect an exact solution for Simpson but an approximate solution for midpoint and trapezoidal.
- For l=9, we expect an approximate solution for all 3 methods.