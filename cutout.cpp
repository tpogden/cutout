#include <iostream>
#include "ensemble.h"

using namespace std;

int main(int argc, char* argv[]) {

    string xyz_file_in = "cutout_in.xyz";
    string xyz_file_out = "cutout_out.xyz";
    
    double cutout_radius = 5.0;
    double exo_cutout_radius = 0.0; // A first cutout of atoms before merge
    double max_bond = 1.5; 
/*
    cout << "argc = " << argc << endl; 
    for(int i = 0; i < argc; i++) 
        cout << "argv[" << i << "] = " << argv[i] << endl; 
    cout << endl;
*/
    // Iterate over argv[] to get the parameters stored inside.
    for (int i = 1; i < argc; i++) { 
            
            // Check that we haven't finished parsing already
            if (i + 1 != argc) { 
                if (string(argv[i]) == "-i") { // In File 
                    xyz_file_in = argv[i+1]; 
                }
                else if (string(argv[i]) == "-o") { // Out File 
                    xyz_file_out = argv[i+1];
                }
                else if (string(argv[i]) == "-r") { // Cutout Radius
                    cutout_radius = atof(argv[i+1]);  
                }
                else if (string(argv[i]) == "-x") { // Exo Cutout Radius
                    exo_cutout_radius = atof(argv[i+1]);  
                }
                else if (string(argv[i]) == "-b") { // Bond Length
                    max_bond = atof(argv[i+1]);
                }
            }

    }

//    tic();

    cout << "Start Cutout" << lb;

    Ensemble ens_0(xyz_file_in);

    cout << "Cutting out molecules within exo radius of "; 
    cout << cutout_radius + exo_cutout_radius << "Å from the first atom.";
    cout << lb;

    if (exo_cutout_radius != 0.0)
        ens_0 = ens_0.get_cutout(*ens_0.get_molecule(0)->get_atom(0),
                                cutout_radius + exo_cutout_radius);

    cout << "Merging bonded molecules with maximum bond length of "; 
    cout << max_bond << "Å" << lb;
        
    ens_0.merge_bonded(max_bond);

    cout << "Cutting out molecules within radius of "; 
    cout << cutout_radius<< "Å from the first atom." << lb;

    Ensemble ens_1;
    ens_1 = ens_0.get_cutout(*ens_0.get_molecule(0)->get_atom(0),
                                cutout_radius);

    Vector3f fix_origin = ens_0.get_molecule(0)->get_atom(0)->get_pos()*-1;

    ens_1.move(fix_origin);

    cout << ens_1.get_info();

    cout << "Writing to "; 
    cout << xyz_file_out << lb;

    cout << ens_1.get_num_atoms() << " atoms in " << ens_1.get_num_molecules() << " molecules written." << lb;

    ens_1.write_to_file(xyz_file_out);

//    toc();

    return 0;

}
