#Cutout   
###v0.1  
By Tommy Ogden <t@ogden.eu>

Cutout takes a cartesian format (XYZ) molecular file and cuts out the 
molecules in a given range of a given position, returning a new XYZ file.

##Switches

* -i    Input file name. Default: cutout_in.xyz
* -o    Output file name. Default: cutout_out.xyz
* -r    Cutout radius. Default: 5.0
* -b    Bond cutoff, i.e. the maximum distance between two atoms
        that will be considered as a bond. Default: 1.5
* -x    A preliminary external cutout, before molecules are formed, to 
        speed up the procedure. This value is a radius _outside_ the main 
        cutout, so the first cutout radius will be (-r + -x). 
        Default 0.0 (i.e. no preliminary cutout) 

##Examples

cutout -i my_input.xyz -o my_output.xyz -r 4.0 -b 1.2 -x 3.0

cutout -r 3.0 -x 2.0

##MIT License

Copyright (C) 2011 by Thomas P. Ogden

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
