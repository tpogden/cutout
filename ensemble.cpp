#include "ensemble.h"

// Constructors & Destructors ----------------------------------------

Ensemble::Ensemble() {}

Ensemble::Ensemble(string & xyz_filename_i) { 
    
    init_from_file(xyz_filename_i);

}

// Operators ---------------------------------------------------------

ostream& operator<< (ostream &stream_o, Ensemble const& ens_i) {

    stream_o << ens_i.get_xyz();
    return stream_o;

}

// Active Functions --------------------------------------------------

int Ensemble::init(string & xyz_i) {

    stringstream xyz_ss(xyz_i);
    string mol_str;
    
    while (getline(xyz_ss,mol_str))
        add(mol_str);

    return 0;

}

int Ensemble::init_from_file(string & xyz_filename_i) {

    add_from_file(xyz_filename_i);

    return 0;

}

int Ensemble::move(Vector3f &displace_i) { 
   
    vector<Molecule>::iterator iter; 
    for (iter=molecules.begin(); iter != molecules.end(); ++iter)
        iter->move(displace_i);
    return 0;

} 

int Ensemble::add(Molecule &mol_i) {

    if (!contains(mol_i)) {

        molecules.push_back(mol_i);
        return 0;

    }

    else return 1;

}

int Ensemble::add(string & xyz_string_i) {

    Molecule xyz_mol(xyz_string_i);
    add(xyz_mol);

    return 0;

}

int Ensemble::add_from_file(string & xyz_filename_i) {

    fstream xyz_file;
    xyz_file.open(xyz_filename_i.c_str(), fstream::in);

    if (xyz_file.is_open()) {

        cout << xyz_filename_i << " opened." << lb;

        string atom_count;

        getline(xyz_file, atom_count);
        cout << atom_count << " atoms to add." << lb;

        getline(xyz_file, atom_count); // Get the next line.

        string xyz_line;

        while (getline(xyz_file,xyz_line))
            add(xyz_line);
        
        xyz_file.close(); 
        cout << xyz_filename_i << " closed." << lb;

        return 0;

    }

    else {

        cout << "Unable to open " << xyz_filename_i << lb;

        return 1;

    }

}

int Ensemble::remove(Molecule &mol_i) {

    if (contains(mol_i)) {

        // Technique from 'Three Guidelines for Effective Iterator Usage'
        // http://pinboard.in/u:tommyogden/b:c05c363e0c0c
        
        vector<Molecule>::iterator iter(molecules.begin());

        advance(iter, 
            distance<vector<Molecule>::const_iterator>(iter, 
                find_molecule(mol_i))); 

        molecules.erase(iter);

        return 0;

    }

    else return 1;

}
/*//
int Ensemble::merge(vector<Molecule>::iterator iter_1_i,
                    vector<Molecule>::iterator iter_2_i) {
    
    vector<Molecule>::iterator iter_1 = iter_1_i, iter_2 = iter_2_i; 

    Molecule merged_mol = iter_1->get_union(*iter_2);

    molecules.erase(iter_1);
    molecules.erase(iter_2);

    add(merged_mol);

    return 0;

} // */

int Ensemble::merge(Molecule & mol_1_i, Molecule & mol_2_i) {

    Molecule mol_1(mol_1_i), mol_2(mol_2_i);

    Molecule merged_mol = mol_1.get_union(mol_2);    

    remove(mol_1);

    remove(mol_2);

    add(merged_mol);

    return 0;

}

int Ensemble::merge_bonded(Molecule & mol_i, double max_bond_i) {

    vector<Molecule>::iterator iter;
    
    Molecule merged_molecule;
   
    vector<Molecule> molecules_to_delete;
    
    merged_molecule = mol_i; 

    for (iter = molecules.begin(); iter != molecules.end(); ++iter) {

        if (mol_i.get_distance_to(*iter) <= max_bond_i) {

            // Merge the molecules
            merged_molecule = merged_molecule.get_union(*iter);
           
            // We're going to delete these later 
            molecules_to_delete.push_back(*iter);
            
        } 

    }

    for (iter = molecules_to_delete.begin(); 
            iter != molecules_to_delete.end(); ++iter)
        remove(*iter);

    // Don't need this 'if' now we're setting merged_molecule = mol_i first.
    if (merged_molecule.get_num_atoms() > 0)
        add(merged_molecule);

    return 0;

} 

int Ensemble::merge_bonded(double max_bond_i) {

    merge_bonded(molecules[0], max_bond_i);  

    // First merge is now at the back, so get that to check.

    Molecule first_merge = molecules.back();
 
    while (molecules[0] != first_merge) 
        merge_bonded(molecules[0], max_bond_i);  
    
    return 0;

}

int Ensemble::write_to_file(string & xyz_filename_i) {

   ofstream xyz_file;
   xyz_file.open(xyz_filename_i.c_str());

    xyz_file << *this;

   xyz_file.close(); 

}

// Passive Functions -------------------------------------------------

Molecule * Ensemble::get_molecule(int index_i) { 
    
    return &molecules[index_i];

}

int Ensemble::get_num_molecules() const { return molecules.size(); }

int Ensemble::get_num_atoms() const {

    int num_atoms = 0;
    vector<Molecule>::const_iterator iter;

    for (iter = molecules.begin(); iter != molecules.end(); ++iter)
        num_atoms += iter->get_num_atoms();

    return num_atoms;

}

vector<Molecule>::const_iterator Ensemble::find_molecule(Molecule const&
    mol_i) const {

    return find(molecules.begin(), molecules.end(), mol_i);     

}

bool Ensemble::contains(Molecule& mol_i) const {
   
    return (find_molecule(mol_i) != molecules.end()); 

}

string Ensemble::get_xyz() const {

    vector<Molecule>::const_iterator iter;

    stringstream xyz_ss;
    xyz_ss << get_num_atoms() << endl << endl;
    for (iter=molecules.begin(); iter != molecules.end(); ++iter)
        xyz_ss << iter->get_xyz();

    return xyz_ss.str();

}

string Ensemble::get_info() const {

    vector<Molecule>::const_iterator iter;
    
    stringstream info_ss;
    info_ss << "Molecules: " << get_num_molecules() << endl;
    info_ss << "Atoms: " << get_num_atoms() << endl << endl;
    for (iter=molecules.begin(); iter != molecules.end(); ++iter)
        info_ss << iter->get_info() << endl;
    return info_ss.str();

}

Ensemble Ensemble::get_cutout(Atom & atom_i, double radius_i) {

    Ensemble cutout_ensemble;

    vector<Molecule>::iterator iter;

    cout << "Cutout from atom " << endl << atom_i << lb;

    for (iter=molecules.begin(); iter != molecules.end(); ++iter) {

        if (iter->get_distance_to(atom_i) < radius_i)
            cutout_ensemble.add(*iter);
    }

    return cutout_ensemble;

}

// End ---------------------------------------------------------------
