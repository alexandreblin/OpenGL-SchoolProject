#include "Object.h"

using namespace std;

Object::Object(std::string filename, Point pos, Vector axis) : m_position(pos), m_axis(axis) {
	ifstream file(filename.c_str());
	
	string line;
	while(getline(file, line)) {
		stringstream str(line);
		string type;
		
		str >> type;

		if (type == "Vertex") {
			double x, y, z;
			
			str >> x >> y >> z;
			
			m_vertices.push_back(Point(x, y, z));
		}
		else if (type == "Face") {
			Face f;
			while (!str.eof()) {
				int num;
			
				str >> num;
				
				f.push_back(num);
			}
			
			m_faces.push_back(f);
		}
	}
}