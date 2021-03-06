//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 
 
#include "SFML/Graphics.hpp" 
#include "SFML/Graphics/Shader.hpp"
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#include "Terrain.h"
#include "Camera.h"
#include <SFML/Window/ContextSettings.hpp>

//0 = grass, 1 = snow, 2 = water
GLuint m_textures[3];

void LoadTextures()
{



	sf::Image waterImg;
	sf::Image snowImg;
	sf::Image grassImg;
	grassImg.loadFromFile("Textures/dirt_grass.png");
	snowImg.loadFromFile("Textures/snow.jpg");
	waterImg.loadFromFile("Textures/water.jpg");
	//terrainImg.loadFromFile("Textures/heightmap.png");



	sf::Texture* m_terrainTex;



	glEnable(GL_TEXTURE_2D);
	glGenTextures(3, m_textures);

	glBindTexture(GL_TEXTURE_2D, m_textures[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, grassImg.getSize().x, grassImg.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, grassImg.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, m_textures[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, snowImg.getSize().x, snowImg.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, snowImg.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, m_textures[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, waterImg.getSize().x, waterImg.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, waterImg.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


}



int main() 
{ 
    // Create the main window 
    
    int width=600,height=600;
	sf::ContextSettings settings;
	settings.depthBits = 24;
	sf::RenderWindow App(sf::VideoMode(width, height, 32), "SFML OpenGL", sf::Style::Default, sf::ContextSettings(32)); 
    // Create a clock for measuring time elapsed     
    sf::Clock Clock; 

	aiVector3D position(0, 10,-30);
	Camera camera;
    camera.Init(position); //create a camera

	LoadTextures();
	
      
    //prepare OpenGL surface for HSR 
    glClearDepth(1.f); 
    glClearColor(0.3f, 0.3f, 0.6f, 0.f); //background colour
    glEnable(GL_DEPTH_TEST); 
    glDepthMask(GL_TRUE); 
   
    //// Setup a perspective projection & Camera position 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
     
    //set up a 3D Perspective View volume
    gluPerspective(90.f, (float)width/height, 1.f, 300.0f);//fov, aspect, zNear, zFar 
 





	//load & bind the shader
	sf::Shader shader;
	//all the lighting & texture blending code should  be put in 'fragment.glsl'
	if (!shader.loadFromFile("vertex.glsl", "fragment.glsl")){
		exit(1);
	}
	sf::Shader::bind(&shader);


	//Create our Terrain
	Terrain terrain;
	terrain.Init();

    // Start game loop 
    while (App.isOpen()) 
    { 
        // Process events 
        sf::Event Event; 
        while (App.pollEvent(Event)) 
        { 
            // Close window : exit 
            if (Event.type == sf::Event::Closed) 
                App.close(); 
   
            // Escape key : exit 
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape)) 
                App.close(); 
             
			//update the camera
			camera.Update(Event);
 
            
    
        } 
           
        //Prepare for drawing 
        // Clear color and depth buffer 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
   
        // Apply some transformations 
        //initialise the worldview matrix
		glMatrixMode(GL_MODELVIEW); 
        glLoadIdentity(); 

		//get the viewing transform from the camera
		camera.ViewingTransform();


		//make the world spin
		//TODO:probably should remove this in final
		static float ang=0.0;
		//ang+=0.01f;
		glRotatef(ang*2,0,1,0);//spin about y-axis


		glBindTexture(GL_TEXTURE_2D, m_textures[2]);
		//draw the world
		terrain.Draw();

		   
        // Finally, display rendered frame on screen 
        App.display(); 
    } 
   
    return EXIT_SUCCESS; 
}
