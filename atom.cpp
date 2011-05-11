#include <iostream>
#include <string>
#include <sstream>

#include "atom.h"

int get_next_atom_id() { return atom_id_iterator++; }

// Constructors & Destructors ----------------------------------------

Atom::Atom() { 
    
    int id_int = 0;
    string xyz_str = "X 0.0 0.0 0.0";
    init(id_int, xyz_str);

}

Atom::Atom(int id_i, string element_i, Vector3f pos_i) { 
    
    init(id_i, element_i, pos_i);

}

Atom::Atom(int id_i, string atom_str_i) { init(id_i, atom_str_i); }

// Operators ---------------------------------------------------------

bool Atom::operator==(Atom const& atom_i) const {
    
    return (get_id() == atom_i.get_id());

} 

bool Atom::operator!=(Atom const& atom_i) const { 
    
    return !(*this == atom_i);

}

bool Atom::operator<(Atom const& atom_i) const {

    return (get_id() < atom_i.get_id());

}

ostream& operator<< (ostream &stream_o, Atom &atom_i) {

    stream_o << atom_i.get_xyz();
    return stream_o;

}

// Active Functions --------------------------------------------------

int Atom::init(int &id_i, string &element_i, Vector3f &pos_i) { 

    set_id(id_i);
    set_element(element_i);
    vel << 0.0, 0.0, 0.0; 
    
    return 0;

}

int Atom::init(int &id_i, string &atom_str_i) {

    set_id(id_i);  
    set_xyz(atom_str_i);
    vel << 0.0, 0.0, 0.0;

    return 0;

}

int Atom::set_id(int &id_i) { id = id_i; return 0; }

int Atom::set_element(string &element_i) { element = element_i; return 0; }

int Atom::set_pos(Vector3f &pos_i) { pos = pos_i; return 0; }

int Atom::set_vel(Vector3f &vel_i) { vel = vel_i; return 0; }

int Atom::set_xyz(string &xyz_i) { // Sets element, pos from xyz string.

    stringstream xyz_ss(xyz_i);        

    string element_str;
    xyz_ss >> element_str;
    set_element(element_str);

    Vector3f atom_pos; atom_pos << 0.0, 0.0, 0.0;
    for (int d = 0; d < 3; d++)
        xyz_ss >> atom_pos(d);
    set_pos(atom_pos);

    return 0;

}

int Atom::move(Vector3f &displace_i) { pos = pos + displace_i; return 0; }

// Passive Functions -------------------------------------------------

int Atom::get_id() const { return id; }

string Atom::get_element() const { return element; }

Vector3f Atom::get_pos() const { return pos; }

Vector3f Atom::get_vel() const { return vel; }

string Atom::get_xyz() const { // 2011-04-11 17:57 added const

    stringstream xyz_ss;
    xyz_ss << get_element() << tb << get_pos().transpose();
    return xyz_ss.str(); 

}

string Atom::get_info() const {

    stringstream info_ss;
    info_ss << get_id() << tb << get_xyz();
    return info_ss.str();

}

Vector3f Atom::get_vector_to(Atom &atom_i) const {

    return atom_i.get_pos() - get_pos();

}

double Atom::get_distance_to(Atom &atom_i) const {

    return get_vector_to(atom_i).norm();

}

// End ---------------------------------------------------------------
