#pragma comment(lib,"assimp.lib")
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "GL/glu.h" 



class Camera{
    static aiVector3D zero,yaxis,zaxis;
	float angleLR, angleUD;
public:
    aiVector3D position;
    aiVector3D forward;
    aiVector3D up;
 
    float forwardSpeed;
    float roationSpeed;
     
    Camera():forwardSpeed(0.5f),roationSpeed(0.05f){}
 
    void Init(aiVector3D& p=zero, aiVector3D& f=zaxis, aiVector3D& u=yaxis){
        position=p;
        forward=f;
		up = u;
		angleLR = 0;
		angleUD = 0;
         
    }
 
	void Update(sf::Event e){//respond to keyboard events
		if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::D)){
                MoveLeftRight(+1);
            }

			if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::A)){
                MoveLeftRight(-1);
            }
 
            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::W)){
                MoveForwardBack(1);
            }
            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::S)){
                MoveForwardBack(-1);
            }

			if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Q)){
                MoveUpDown(1);
            }
            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::E)){
                MoveUpDown(-1);
            }
 
            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Right)){
                TurnRightLeft(1);
            }
            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Left)){
                TurnRightLeft(-1);
            }
            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Up)){
               TurnUpDown(1);
            }
            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Down)){
                TurnUpDown(-1);
 
            }
	
	}
    void MoveLeftRight(int dir){ //Dir=+1=>Right, dir=-1=> Left
		if (dir == 1)
			position -= (up ^ forward) * forwardSpeed;
		else
			position += (up ^ forward) * forwardSpeed;
    }

	void MoveUpDown(int dir){ //Dir=+1=>Right, dir=-1=> Left
            //TODO
    }
 
    void MoveForwardBack(int dir){ //Dir=+1=>Forward, dir=-1=> Back
 
        position+=(forward*(forwardSpeed*dir));
    }
 
    void TurnRightLeft(int dir){ //Dir=+1=>Right, dir=-1=> Left
        
		if (dir == -1)
			angleLR += roationSpeed;

		else if (dir  == 1)
			angleLR -= roationSpeed;

		forward.x = sinf(angleLR) * cosf(angleUD);
		forward.z = cosf(angleLR);
		
    }
         
    void TurnUpDown(int dir){ //Dir=+1=>Up, dir=-1=> Down

		if (dir == -1 && angleUD > -1.25)
			angleUD -= roationSpeed;

		else if (dir == 1 && angleUD < 1.25)
			angleUD += roationSpeed;

		forward.y = sinf(angleUD) * cosf(angleLR);
		forward.z = cosf(angleUD) * cosf(angleLR);
    }
 
    void ViewingTransform(){
        gluLookAt(	position.x,position.y,position.z,// camera position
					position.x + forward.x,position.y + forward.y,position.z + forward.z, //look at this point //TODO: BUG here!! what is it ??
					0,1,0); //camera up
    }
 
};

//create some default vectors
aiVector3D Camera::zero(0.0f);
aiVector3D Camera::yaxis(0.0f,1.0f,0.0f);
aiVector3D Camera::zaxis(0.0f,0.0f,1.0f);