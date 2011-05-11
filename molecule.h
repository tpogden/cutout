#ifndef MOLECULE_H
#define MOLECULE_H

#include <vector>
#include <algorithm>

#include "atom.h" // Include here or in the .cpp?

using namespace std;

// Class: Molecule ---------------------------------------------------

class Molecule {

  private:

    vector<Atom>    atoms;

  public:

    // Constructors & Destructors ------------------------------------

    Molecule();
    Molecule(string &);

    // Operators -----------------------------------------------------

    bool operator==(Molecule const&) const; 
    bool operator!=(Molecule const&) const;
    
    friend ostream& operator<< (ostream &, Molecule const&);
    
    // Active Functions ----------------------------------------------

    int init(string &);

    int sort_atoms();
    int move(Vector3f &);

    int add(Atom &);
    int remove(Atom &);

    // Passive Functions ---------------------------------------------

    Atom * get_atom(int);
    int get_num_atoms() const;
   
    vector<Atom>::const_iterator find_atom(Atom const&) const; 
    bool contains(Atom&) const;

    Molecule get_union(Molecule&) const;

    double get_distance_to(Atom&) /*const*/;
    double get_distance_to(Molecule&); 

    string get_xyz() const;
    string get_info() const;

};

#endif
