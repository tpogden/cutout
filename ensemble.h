#include <string>
#include <sstream>
#include <cmath>
#include <Eigen/Core>

#include "tommy.h"
#include "atom.h"
#include "molecule.h"

using namespace std;
using namespace Eigen;

// Class: Ensemble ---------------------------------------------------

class ensemble {

  private:

    int num_atoms;
    atom * atoms;

    int num_molecules;
    molecule * molecules;

  public:

    ensemble();
    // ensemble(string filename_i);

    ~ensemble();

    // Sets ----------------------------------------------------------
    

    // Gets ----------------------------------------------------------

    int get_num_atoms();
    atom * get_atom(int);

    int get_num_molecules();
    molecule * get_molecule(int);

    string get_xyz();

    bool contains_atom(atom *);

    // Actions -------------------------------------------------------

    int add_atom(atom);

}; //*/

ensemble::ensemble() {

    num_atoms = 0;
    num_molecules = 0;

}

ensemble::~ensemble() {

//    if(atoms)
//        delete atoms;
//    if(molecules)
//        delete molecules;

}

// Ensemble: Gets ----------------------------------------------------

// Returns the number of atoms in the ensemble
int ensemble::get_num_atoms() { return num_atoms; }

// Returns a pointer to the atom at a given index
atom * ensemble::get_atom(int atom_index_i) { return &atoms[atom_index_i]; }

// Returns the number of molecules in the ensemble
int ensemble::get_num_molecules() { return num_molecules; }

// Returns a pointer to the molecule at a given index
molecule * ensemble::get_molecule(int mol_index_i) { return &molecules[mol_index_i]; }

// Returns an xyz string for the atoms in this ensemble
string ensemble::get_xyz() {

    stringstream xyz_ss;

    xyz_ss << num_atoms << lb;

    for (int n = 0; n < num_atoms; n++)
        xyz_ss << atoms[n].get_xyz() << endl;
    return xyz_ss.str();

}

bool ensemble::contains_atom(atom * atom_i) {

    bool contains_atom = false;

    for (int n = 0; n < num_atoms; n++)
        if (atom_i == &atoms[n])
            contains_atom = true;

    return contains_atom;

}

// Ensemble: Actions -------------------------------------------------

int ensemble::add_atom(atom atom_i) {

    cout << "Create a new array of atoms with size +1 of num atoms" << endl;

    // Create a new array of atoms with size +1 of num atoms
    atom * new_atoms; new_atoms = new atom[num_atoms + 1];

    cout << "Fill new array with existing atoms" << endl;

    // Fill the new array with the existing atoms, leaving the last
    // array cell empty
    for (int n = 0; n < num_atoms; n++)
        new_atoms[n] = atoms[n];


    // Fill in the last array cell with the new atom
    new_atoms[num_atoms] = atom_i;
 
    // Delete the existing atoms array and create a new blank one 1 bigger
//    if (num_atoms > 0) delete atoms;

    num_atoms++;

    atoms = new atom[num_atoms];

    // Fill the new blank atoms with new_atoms    
    for (int n = 0; n < num_atoms; n++)
        atoms[n] = new_atoms[n];

//    if (new_atoms) delete new_atoms;

}

// End Class: Ensemble -----------------------------------------------
