#include "molecule.h"

// Constructors & Destructors ----------------------------------------

Molecule::Molecule() {

}

Molecule::Molecule(string & xyz_i) { 
    
    init(xyz_i);

}

// Operators ---------------------------------------------------------
   
bool Molecule::operator==(Molecule const& mol_i) const {
    
    int num_contained = 0;

    vector<Atom>::const_iterator iter;
    for (iter = atoms.begin(); iter != atoms.end(); ++iter) {
        Atom my_atom = *iter;
        num_contained += mol_i.contains(my_atom); 
    }

    return (num_contained == get_num_atoms()) &&
        (mol_i.get_num_atoms() == get_num_atoms());

} 
    
bool Molecule::operator!=(Molecule const& mol_i) const { 
    
    return !(*this == mol_i);

}

ostream& operator<< (ostream &stream_o, Molecule const& mol_i) {

    stream_o << mol_i.get_xyz();
    return stream_o;

}

// Active Functions --------------------------------------------------

int Molecule::init(string & xyz_i) { 

    stringstream xyz_ss(xyz_i);
    string atom_str;
    
    while (getline(xyz_ss,atom_str)) {

        Atom xyz_atom(get_next_atom_id(), atom_str);
        add(xyz_atom);

    }

    return 0;

}

int Molecule::sort_atoms() {

    sort(atoms.begin(),atoms.end());

    return 0;

} 

int Molecule::move(Vector3f &displace_i) { 
   
    vector<Atom>::iterator iter; 
    for (iter=atoms.begin(); iter != atoms.end(); ++iter)
        iter->move(displace_i);
    return 0; 

}

int Molecule::add(Atom &atom_i) {

    if (!contains(atom_i)) {

        atoms.push_back(atom_i);
        return 0;

    }

    else return 1;

}

int Molecule::remove(Atom &atom_i) {

    if (contains(atom_i)) {

        // Technique from 'Three Guidelines for Effective Iterator Usage'
        // http://pinboard.in/u:tommyogden/b:c05c363e0c0c
        
        vector<Atom>::iterator iter(atoms.begin());
        
        advance(iter, 
                distance<vector<Atom>::const_iterator>(iter, 
                                                       find_atom(atom_i))); 
        
        atoms.erase(iter);

        return 0;

    }

    else return 1;

}

// Passive Functions -------------------------------------------------

Atom * Molecule::get_atom(int index_i) { return &atoms[index_i]; }

int Molecule::get_num_atoms() const { return atoms.size(); }

vector<Atom>::const_iterator Molecule::find_atom(Atom const& atom_i) const {

    return find(atoms.begin(), atoms.end(), atom_i);     

}

bool Molecule::contains(Atom& atom_i) const {
   
    return (find_atom(atom_i) != atoms.end()); 

}

Molecule Molecule::get_union(Molecule& mol_i) const {

    Molecule union_mol(*this);
    vector<Atom>::iterator iter;
    for (iter = mol_i.atoms.begin(); iter != mol_i.atoms.end(); ++iter)
        if (!union_mol.contains(*iter))
            union_mol.atoms.push_back(*iter);

    union_mol.sort_atoms();
    return union_mol;

}

double Molecule::get_distance_to(Atom& atom_i) /*const*/ {

    double shortest_distance = numeric_limits<double>::max();
    vector<Atom>::/*const_*/iterator iter;

    for (iter = atoms.begin(); iter != atoms.end(); ++iter)
        if (atom_i.get_distance_to(*iter) < shortest_distance)
            shortest_distance = atom_i.get_distance_to(*iter);
        
    return shortest_distance;
}

double Molecule::get_distance_to(Molecule& mol_i) {

    double shortest_distance = numeric_limits<double>::max();
    vector<Atom>::iterator iter;
    
    for (iter = atoms.begin(); iter != atoms.end(); ++iter)
        if (mol_i.get_distance_to(*iter) < shortest_distance)
            shortest_distance = mol_i.get_distance_to(*iter);
        
    return shortest_distance;

}

string Molecule::get_xyz() const {

    vector<Atom>::const_iterator iter;

    stringstream xyz_ss;
    for (iter=atoms.begin(); iter != atoms.end(); ++iter)
        xyz_ss << iter->get_xyz() << endl;

    return xyz_ss.str();

}

string Molecule::get_info() const {

    vector<Atom>::const_iterator iter;
    
    stringstream info_ss;
    info_ss << "Size: " << get_num_atoms() << endl;
    for (iter=atoms.begin(); iter != atoms.end(); ++iter)
        info_ss << iter->get_info() << endl;
    return info_ss.str();

}

// End ---------------------------------------------------------------
