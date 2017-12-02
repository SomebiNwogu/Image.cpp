#include <string>
#include <iostream>
 #include <fstream>
using namespace std;
 
class Image
{
public:
    /**
    * Static method to create new Image objects.  Images are a 2D
    * array of pixels, where each pixel is comprised of an 8-bit
    * red, green, blue triple (i.e. 3 unsigned char values stored
    * per pixel).
    *
    * @params width, height - width and height of image in pixels
    *
    * @returns pointer to valid Image object if successful, else nullptr
    **/
    static Image* Create(unsigned int width, unsigned int height);
    
    //! Destructor
    ~Image();
   //! Copy Constructor
    Image(const Image&);
    //! Assignment operator overload
    Image& operator = (const Image&);
    
    //! Extracts the red value of the pixel at (x,y)
    unsigned char getRedPixel(unsigned int x, unsigned int y) const;    
    //! Extracts the green value of the pixel at (x,y)
    unsigned char getGreenPixel(unsigned int x, unsigned int y) const;
    //! Extracts the blue value of the pixel at (x,y)
    unsigned char getBluePixel(unsigned int x, unsigned int y) const;
    
    /**
    * Sets the RGB values for the pixel at (x,y).
    *
    * @params x, y - the x and y coordinates of the pixel
    *                @pre 0 <= x < pixelWidth, 0 <= y < pixelHeight
    * @params r, g, b - the red, green, and blue values respectively
    *                   for the pixel (x,y)
    * 
    * @modifies pixel data for pixel (x,y) to have new RGB values
   **/
   void setPixel(unsigned int x, unsigned int y,
                 unsigned char r, unsigned char g, unsigned char b);
    
    //! Returns width of image (in pixels)
    unsigned int getWidth() const;
    //! Returns height of image (in pixels)
    unsigned int getHeight() const;
    
    /**
    * Saves the image as a PPM file (see https://en.wikipedia.org/wiki/Netpbm_format#PPM_example)
    * based on the assumption that the 3 pixel values are stored horizontally.
    * Hence, the actual array storing values is 3x wider than its stated width, to account
    * for the 3 values (red, green, blue) stored per pixel.
    *
    * @params filename - name to save image as (should have .ppm extension)
    *
    * @returns true if no exceptions/errors encountered during save, else false
    **/
    bool saveImage(std::string filename); // This is provided for you
private:
     // Private constructor used by Create method
    Image(unsigned int w, unsigned int h, unsigned char* pxArray);
    
    // width and height of image in pixels
    unsigned int pixelWidth;
    unsigned int pixelHeight;
    
    // Pointer to array of unsigned char with
    // size 3 * pixelWidth * pixelHeight.
    // This is because each pixel is represented
   // by 3 colour values: red, green, and blue,
    // which are stored separately.
    // We are assuming we store the pixel colours
    // horizontally, so this pointer is to be
    // interpreted as a (3*pixelWidth) wide by
    // pixelHeight tall 2D array.
    unsigned char* pixelArray;
};

Image* Image::Create(unsigned int width, unsigned int height)
{
	unsigned char* x= new unsigned char[3*width*height];
	if(not x)
	{
	    return nullptr;
	}
	return new Image(width,height,x);
}
/*
* The saveImage method makes the assumption that the 3 colours for each pixel are stored
* horizontally next to each other.
*/


Image::Image(unsigned int w, unsigned int h, unsigned char* pxArray)
:pixelWidth(w),pixelHeight(h),pixelArray(pxArray)
 {


}
    
//! Destructor
Image::~Image()
{
	delete [] pixelArray;


}
//! Copy Constructor
Image::Image(const Image& orig)
{
	for(int i=0; i< (3*pixelWidth*pixelHeight);i++)
	{
		pixelArray[i]=orig.pixelArray[i];
	}
	this->pixelHeight=orig.pixelHeight;
	this->pixelWidth=orig.pixelWidth;
}
//! Assignment operator overload
Image& Image::operator = (const Image& other)
{
	delete [] pixelArray;
	this->pixelHeight=other.pixelHeight;
	this->pixelWidth=other.pixelWidth;
	
	this->pixelArray= new unsigned char[3*pixelWidth*pixelHeight];
	for(int i=0; i< (3*pixelWidth*pixelHeight);i++)
	{
		pixelArray[i]=other.pixelArray[i];
	}
	return *this;

}
unsigned char Image::getRedPixel(unsigned int x, unsigned int y) const
{
	return pixelArray[y*pixelWidth*3+x*3];

}  
    
unsigned char Image::getGreenPixel(unsigned int x, unsigned int y) const
{
	return pixelArray[y*pixelWidth*3+x*3+1];

}
   
unsigned char Image::getBluePixel(unsigned int x, unsigned int y) const
{
	return pixelArray[y*pixelWidth*3+x*3+2];
}
    
 void Image::setPixel(unsigned int x, unsigned int y,unsigned char r, unsigned char g, unsigned char b)
{

	pixelArray[y*pixelWidth*3+x*3]=r;
	pixelArray[y*pixelWidth*3+x*3+1]=g;
	pixelArray[y*pixelWidth*3+x*3+2]=b;
}
    
   
unsigned int Image::getWidth() const
{

	return pixelWidth;

}
    
unsigned int Image::getHeight() const
{

	return pixelHeight;

}
   
bool Image::saveImage(std::string filename)
{
    try
    {
        // Open a file for writing.
        std::ofstream myfile;
        myfile.open (filename);
        
        // Write header info
        myfile << "P6\n" << this->pixelWidth << " "
               << this->pixelHeight << "\n255\n";
        
        // Write stored pixel values as rows.
        for (int y = 0; y < this->pixelHeight; y++)
        {
            for (int x = 0; x < this->pixelWidth * 3; x += 3)
            {
                int idx = y * (3 * this->pixelWidth) + 3*x;
                myfile << this->pixelArray[idx] << " "
                       << this->pixelArray[idx+1] << " "
                       << this->pixelArray[idx+2] << " ";
            }
            myfile << "\n";
        }
  
        myfile.close();
    }
    catch (...)
    {
        // If a file-related exception occurs, just return false.
        return false;
    }
    return true;
}
int main()
{
    

    Image* sq100 = Image::Create(100, 100);
    if (sq100)
    {
    	cout << "Success!" << endl;
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                sq100->setPixel(i, j, 100, 200, 50);            
            }
        }
    }
    else
    {
        cout << "Error! Image::Create() method returned nullptr! Quitting with no more tests..." << endl;
    }

    // Test 0 verifies that image exists and pixel values set
    // properly as indicated above.

    // Tests 1 and 2: copy constructor and assignment operator
    // Verifies succesful create of these new images
    Image sq2(*sq100);
    Image* sq3 = Image::Create(50,50);
    if (sq3)
    {
        *sq3 = sq2; // overwrite 50x50
    }

    // Tests 3 and 4: Make changes to each of the images to
    // verify that they all own their own memory.

    // ...


    // Delete the heap-allocated images.
    // sq2 will be deleted when scope of main ends.
    delete sq100;
    delete sq3;

    return 0;
}


