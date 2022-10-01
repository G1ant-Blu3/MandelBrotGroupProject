/*******************************
 * Programmers: Carl Brown     *
 *              Ben Paepke     *
 * Assignment:  Mandelbrot Set * 
 *              Group Project  *
 * Class:       CISP 400       *
 *******************************/

#include "ComplexPlane.h"
#include <thread>

using namespace std;

void calculateIteration(float desktopWidth, float desktopHeight, VertexArray& background, RenderWindow& window, ComplexPlane& complexPlane, int index, int num)
{
	//Make double for loop for all pixels
	for(int j = index; j < num; j++)
	{
		for(int i = 0; i < static_cast<int>(desktopHeight); i++)
		{
			background[j + i * static_cast<int>(desktopWidth)].position = {(float)j, (float)i};
			Vector2i points(j, i);
			Vector2f coord = window.mapPixelToCoords(points, complexPlane.getView());

			//Call countIterations and store return value
			size_t count = complexPlane.countIterations(coord);

			//Declare 3 local variables r, g, b
			Uint8 r, g, b;

			//Pass count and 3 color variables to iterationsToRGB
			complexPlane.iterationsToRGB(count, r, g, b);

			//Set color variable in VertexArray
			background[j + i * static_cast<int>(desktopWidth)].color = {r, g, b};
		}
	}
}


int main()
{
	//Get video resolution
	VideoMode vm(1920, 1080);
	VideoMode desktop = vm.getDesktopMode();
	float desktopWidth = desktop.width;
	float desktopHeight = desktop.height;
	
	//Calculate aspect ratio
	float aspectRatio = desktopHeight / desktopWidth;
	
	//Construct window
	RenderWindow window(vm, "Mandlebrot Set", Style::Default);

	//Construct ComplexPlane object
	ComplexPlane complexPlane(aspectRatio);

	//Construct Font object
	Font font;
	font.loadFromFile("OpenSans-Regular.ttf");

	//Construct Text object and set font to text
	Text text;
	text.setFont(font);

	//Construct a VertexArray
	VertexArray background;
	//Set primitive type to Points
	background.setPrimitiveType(Points);	
    //Resize the screen to height * width
	background.resize(desktopHeight * desktopWidth);

	//Create an enum class state variable
	enum State { CALCULATING, DISPLAYING };
	//Initialize to CALCULATING
	State state = CALCULATING;

    /*************
	* Begin loop *
    **************/
	while (window.isOpen())
	{
        /*************************
		 * Handle player's input *
         *************************/ 

		//Create queue events
		Event event;
		while (window.pollEvent(event))
		{
			//Event for closing window
			if(event.type == Event::Closed)	{ window.close(); }
			
			//Event if mouse button is pressed
			if (event.type == Event::MouseButtonPressed)
			{
				//Find the coordinates of the mouse click
				Vector2i points = Mouse::getPosition(window);
				Vector2f coord = window.mapPixelToCoords(points, complexPlane.getView());

				//ZoomOut and SetCenter if right mouse button is clicked
				if (event.mouseButton.button == Mouse::Right)
				{
					complexPlane.zoomOut();
					complexPlane.setCenter(coord);
				}

				//ZoomIn and SetCenter if left mouse button is clicked
				else if (event.mouseButton.button == Mouse::Left)
				{
					complexPlane.zoomIn();
					complexPlane.setCenter(coord);
				}

				//Set state to CALCULATING
				state = CALCULATING;
			}

			//Event when mouse moves
			if (event.type == Event::MouseMoved)
			{
				//Get coordinates of mouse location
				Vector2i points = Mouse::getPosition(window);
				Vector2f coord = window.mapPixelToCoords(points, complexPlane.getView());

				//Store mouse location
				complexPlane.setMouseLocation(coord);
			}

			//Event when escape key is pressed
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{ window.close(); }
		}

        /***************
		* Update scene *
        ****************/
		if (state == CALCULATING)
		{
			//Multithreading
			const int NUM_OF_THREADS = 16;
			
			//Calculates the number of pixels for each thread to access
			int step = static_cast<int>(desktopWidth) / NUM_OF_THREADS;
			thread t[NUM_OF_THREADS];

			for(int i = 0; i < NUM_OF_THREADS; i++)
			{
				t[i] = thread(calculateIteration, desktopWidth, desktopHeight, ref(background), ref(window), ref(complexPlane), step * i, step * (i + 1));
			}			
			for(int i = 0; i < NUM_OF_THREADS; i++)
			{
				t[i].join();
			}
			
			//Set state to DISPLAYING
			state = DISPLAYING;
		}

        /**************
		 * Draw scene *
         **************/ 

		//Call loadText
		complexPlane.loadText(text);

		//Clear window
		window.clear();

		//Draw VertexArray
		window.draw(background);

		//Draw text
		window.draw(text);

		//Display window
		window.display();
	}
}