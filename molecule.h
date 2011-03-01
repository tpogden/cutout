#include <string>
#include <cmath>
#include <iostream> // Check if I can remove this after testing?
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

// Class: Molecule ---------------------------------------------------

class molecule {

  private:
    
    int num_atoms;
    atom ** atoms; // An array of pointers to atoms    

  public:

    molecule();
    molecule(atom *, int, atom *, double);

    // Sets ----------------------------------------------------------

    

    // Gets ----------------------------------------------------------

    int get_num_atoms();
    atom * get_atom(int);

    double get_distance_to_atom(atom *);

    string get_xyz();

    bool contains_atom(atom *);

    // Actions -------------------------------------------------------

    int add_atom(atom *);

    int add_bonded_atoms(atom * base_atom_i, int num_atoms_i,
        atom * atoms_i, double bond_cutoff_i);

}; //*/

// Constructor. Molecule of 0 atoms
molecule::molecule() { num_atoms = 0; atoms = new atom * [num_atoms]; }

// Constructor. Construct molecule from base atom and ensemble, adding 
// atoms recursively within a bond cutoff
molecule::molecule(atom * base_atom_i, int num_atoms_i, atom * atoms_i,
    double bond_cutoff_i) {

    add_bonded_atoms(base_atom_i, num_atoms_i, atoms_i, bond_cutoff_i);

} 

// Molecule: Sets ----------------------------------------------------


// Molecule: Gets ----------------------------------------------------

// Returns the number of atoms
int molecule::get_num_atoms() { return num_atoms; }

// Returns a pointer to the atoms at index
atom * molecule::get_atom(int index_i) { return atoms[index_i]; }

// Returns the shortest distance from the molecule to an atom
double molecule::get_distance_to_atom(atom * atom_i) {

    // Set the shortest distance to be the longest possible double
    double shortest_distance = numeric_limits<double>::max();

    // Loop through the atoms, if it's shorter use this distance
    for (int n = 0; n < num_atoms; n++)
        if (atom_i->get_distance_to(atoms[n]) < shortest_distance)
            shortest_distance = atom_i->get_distance_to(atoms[n]);

    return shortest_distance;

}

string molecule::get_xyz() {

    stringstream xyz_ss;

    for (int n = 0; n < num_atoms; n++)
        xyz_ss << atoms[n]->get_xyz() << endl;
    return xyz_ss.str();

}

bool molecule::contains_atom(atom * atom_i) {

    bool contains_atom = false;

    for (int n = 0; n < num_atoms; n++)
        if (atom_i == atoms[n])
            contains_atom = true;

    return contains_atom;

}

// Molecule: Actions -------------------------------------------------

int molecule::add_atom(atom * atom_i) {

    // Create a new array of atom pointers with size +1 of num atoms
    atom ** new_atoms; new_atoms = new atom * [num_atoms + 1];

    // Fill the new array with the existing atom pointers, leaving the last
    // array cell empty
    for (int n = 0; n < num_atoms; n++)
        new_atoms[n] = atoms[n];

    // Fill in the last array cell with the new atom pointer
    new_atoms[num_atoms] = atom_i;

    num_atoms++;

    // Delete the existing atoms array and create a new blank one 1 bigger
    delete atoms;
    atoms = new atom * [num_atoms];

    // Fill the new blank atoms with new_atoms    
    for (int n = 0; n < num_atoms; n++)
        atoms[n] = new_atoms[n];

    delete new_atoms;

}

int molecule::add_bonded_atoms(atom * base_atom_i, int num_atoms_i,
    atom * atoms_i, double bond_cutoff_i) {

    // Code to add bonded atoms here!

    return 0;

}

// End Class: Molecule -----------------------------------------------
