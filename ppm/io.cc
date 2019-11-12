#include <fstream>

#include "ppm.h"

void PPM::load_from_file(const char *filename)
{
 std::ifstream in;
 in.open(filename, (std::ios::in | std::ios::binary));
 if (in.is_open())
 {
  load_from_stream(in);
  in.close();
 } else {
  std::cout << "Error loading file: " << *filename << "\n";
 }
}

void PPM::load_from_stream(std::istream& in)
{
 //Dump the old image and set the dimensions to 0 in case the loading fails
 set_image(0);
 set_dimensions(0, 0);
 
 //Skip "P6" header thing
 in.seekg(3, std::ios::cur);
 
 ushortint new_width=0, new_height=0;
 in >> new_width >> new_height;
 set_dimensions(new_width, new_height);
 
 //skip the last bit of header crap
 in >> new_width;
 in.seekg(1, std::ios::cur);
 
 //Now ready to read in the binary data
 allocate();
 in.read((char*) get_image(), (width*height*3));
}

void PPM::save_to_file(const char *filename)
{
 std::ofstream out;
 out.open(filename, (std::ios::out | std::ios::binary | std::ios::trunc));
 if(out.is_open())
 {
  save_to_stream(out);
  out.close();
 } else
  std::cout << "Error creating file: " << *filename << "\n";
}

void PPM::save_to_stream(std::ostream& out)
{
 //Dump the header
 out << "P6\n" << get_width() << "\n" << get_height() << "\n" << 255 << "\n";
 
 //Write out the binary data
 out.write((const char*) get_image(), (width*height*3));
}
