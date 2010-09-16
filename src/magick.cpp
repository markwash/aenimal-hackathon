#include <string> 
#include <iostream> 
#include <Magick++.h>

using namespace std; 
using namespace Magick;

int main(int /*argc*/,char **argv) 
{ 
  try { 
    InitializeMagick(*argv);

    // Create base image (white image of 300 by 200 pixels) 
    Image image( Geometry(300,200), Color("white") );

    // Set draw options 
    image.strokeColor("red"); // Outline color 
    image.fillColor("green"); // Fill color 
    image.strokeWidth(10);

    // Draw a circle 
    //image.draw( DrawableCircle(100,100, 50,100) );

    // Draw a rectangle 
    image.draw( DrawableRectangle(100,50, 200,150) );

    // Display the result 
    image.display( ); 
    image.write("magick.png");
  } 
  catch( exception &error_ ) 
    { 
      cout << "Caught exception: " << error_.what() << endl; 
      return 1; 
    }

  return 0; 
}
