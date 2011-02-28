#include <string>
#include <cmath>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

// Class: Atom -------------------------------------------------------

class atom {

  private:
    
    Vector3f pos;
    string element;

  public:

    atom();
    atom(Vector3f, string);

    // Sets ----------------------------------------------------------

    int set_pos(Vector3f, string);
    int set_pos_rand(double);

    int set_element(string);

    // Gets ----------------------------------------------------------

    Vector3f get_pos();

    string get_element();

    string get_xyz();

    Vector3f get_vector_to(atom *);
    double get_distance_to(atom *);

    // Actions -------------------------------------------------------  

    int move(Vector3f);

}; //*/

// Constructor. X atom stationary at origin
atom::atom() { pos << 0.0, 0.0, 0.0; element = "X"; }

// Constructor. Takes position vector and element string
atom::atom(Vector3f pos_i, string element_i) {

    set_pos(pos_i); set_element(element_i);

}

// Atom: Sets ---------------------------------------------------------

// Set atom position vector
int atom::set_pos(Vector3f pos_i) { pos = pos_i; return 0; }

// Set atom position randomly within 3D cube (0.0, size)
int atom::set_pos_rand(double size_i) {

    for (int d = 0; d < 3; d++)
        pos[d] = rand(size_i);

    return 0;

}

// Set atom element (e.g. H, Cl, Ne)
int atom::set_element(string element_i) {element = element_i; return 0; }

// Atom: Gets ---------------------------------------------------------

// Returns the atom position vector
Vector3f atom::get_pos() { return pos; }

// Returns the atom element
string atom::get_element() { return element; }

// Returns a line output string for an XYZ file
string atom::get_xyz() {

    stringstrream xyz_ss;
    xyz_ss << element << tb << pos.transpose();
    return xyz_ss.str();

}

// Atom: Actions ------------------------------------------------------

int atom::move(Vector3f displace_i) { pos = pos + displace_i; return 0; }

// End Class: Atom ----------------------------------------------------
