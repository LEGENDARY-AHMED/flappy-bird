
#include <GL/gl.h>
#include <GL/glut.h>
#include "headers/game.h"



void init()
{

	glClearColor(142.0/255,195.0/255,244.0/255, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-30.0, 30.0, 0.0, 60.0, -30.0, 30.0);

}


/* game pieces
bird
background
pipes
start page
end page
function to write on screen
*/


// callback all function here
void render(){

    /* game logic
    if lose ==false then the background will be drown only
        if start ==true and button_moved of screen then start drop the bird and start moving the pipes
        else if lose ==true stop the screen and start drop game over screen with score
    */
    if(lose == false ){
    glClear(GL_COLOR_BUFFER_BIT);

        bottom();
        background();

        // if you press start the pipes will start move and bird drop
        if (!Start==false &&  buttom_moved==true){
        createMovingPipes(pipePos, 4,  4,pipe1X, pipe1Height);
        createMovingPipes(pipePos2, 4,  4,pipe2X,pipe2Height);
        createMovingPipes(pipePos3, 4,  4,pipe3X,pipe3Height);

        drawBird(birdBody_Y);
        lose_game(pipe1Height,pipe1X);
        lose_game(pipe2Height,pipe2X);
        lose_game(pipe3Height,pipe3X);

        }

        Start_Screen();

        Score();





    }else{
        Game_Over();
    }


 glutSwapBuffers();
}

//every time press space the Velocity of bird will be 0.1
void keyboard(unsigned char key, int x, int   y)
{
	if (key == ' ' ){
	    birdVelocity = 0.1f;
        glutPostRedisplay();
	}
}


//press on start or end
void mouse(int btn, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		if (btn == GLUT_LEFT_BUTTON){

			 if ((x >= 44 && x <= 168) && (y >= 332 && y <= 373))
                {
                Start = true;
            }

        if((x >= 332 && x <= 456) && (y >= 332 && y <= 373))
            {
                exit(0);

            }

		}
	}
}



int main(int argc, char **argv)
{
    srand(static_cast<unsigned>(time(0))); //used to make random funciton work
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Flappy bird");
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
	glutDisplayFunc(render);
	glutIdleFunc(render);
	init();
	glutMainLoop();
	return(0);
}
