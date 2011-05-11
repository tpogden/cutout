#ifndef ATOM_H
#define ATOM_H

#include <Eigen/Core>

#include "ogden.h"

using namespace std;
using namespace Eigen;

// Atom Id Iterator --------------------------------------------------

static int atom_id_iterator = 0;
int get_next_atom_id();

// Class: Atom -------------------------------------------------------

class Atom {

  private:
    
    int         id;
    string      element;
    Vector3f    pos;
    Vector3f    vel;

  public:

    // Constructors & Destructors ------------------------------------

    Atom(); 
    Atom(int, string, Vector3f);
    Atom(int, string);

    // Operators -----------------------------------------------------

    bool operator==(Atom const&) const; 
    bool operator!=(Atom const&) const;

    bool operator<(Atom const&) const;

    friend ostream& operator<< (ostream &, Atom &);
    
    // Active Functions ----------------------------------------------

    int init(int &, string &, Vector3f &);
    int init(int &, string &);

    int set_id(int &);
    int set_element(string &);
    int set_pos(Vector3f &);
    int set_vel(Vector3f &);
    int set_xyz(string &);

    int move(Vector3f &);

    // Passive Functions ---------------------------------------------

    int get_id() const;
    string get_element() const;
    Vector3f get_pos() const;
    Vector3f get_vel() const;

    string get_xyz() const;
    string get_info() const;

    Vector3f get_vector_to(Atom &) const;
    double get_distance_to(Atom &) const;

};

#endif
