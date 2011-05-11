Cutout v0.1
Tommy Ogden <t@ogden.eu>

Cutout takes a cartesian format (XYZ) molecular file and cuts out the 
molecules in a given range of a given position, returning a new XYZ file.

#Switches

-i      Input file name. Default: cutout_in.xyz
-o      Output file name. Default: cutout_out.xyz
-r      Cutout radius. Default: 5.0
-b      Bond cutoff, i.e. the maximum distance between two atoms
        that will be considered as a bond. Default: 1.5
-x      A preliminary external cutout, before molecules are formed, to 
        speed up the procedure. This value is a radius _outside_ the main cu        tout, so the first cutout radius will be (-r + -x). 
        Default 0.0 (i.e. no preliminary cutout) 

#Examples

cutout -i my_input.xyz -o my_output.xyz -r 4.0 -b 1.2 -x 3.0
cutout -r 3.0 -x 2.0
