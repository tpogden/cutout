#ifndef ENSEMBLE_H
#define ENSEMBLE_H

#include <fstream>

#include "molecule.h"

using namespace std;

// Class: Emsemble ---------------------------------------------------

class Ensemble {

  private:

    vector<Molecule> molecules;

  public:

    // Constructors & Destructors ------------------------------------

    Ensemble();
    Ensemble(string &);

    // Operators -----------------------------------------------------
    
    friend ostream& operator<< (ostream &, Ensemble const&);
    
    // Active Functions ----------------------------------------------

    int init(string &);
    int init_from_file(string &);

    int move(Vector3f &);

    int add(Molecule &);
    int add(string &);
    int add_from_file(string &);

    int remove(Molecule &);

    int merge(vector<Molecule>::iterator, vector<Molecule>::iterator);
    int merge(Molecule &, Molecule &);

    int merge_bonded(Molecule &, double);
    int merge_bonded(double);

    int write_to_file(string &);

    // Passive Functions ---------------------------------------------

    Molecule * get_molecule(int);
    int get_num_molecules() const;
    int get_num_atoms() const;

    vector<Molecule>::const_iterator find_molecule(Molecule const&) const; 
    bool contains(Molecule&) const;

    string get_xyz() const;
    string get_info() const; 

    Ensemble get_cutout(Atom &, double);

};

#endif
