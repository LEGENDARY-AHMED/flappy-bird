#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

// includes for random libirary
#include <iostream>
#include <iomanip>
#include <random>

//includes for background
#include <cmath>
using namespace std;

/*some instruction
pipe spaces 40 for two pipes
bird space 15
bottom 5

*/





//variables

//pipes variables
//pipes positions
float pipePos[3]={45,15,0};
float pipePos2[3]={75,15,0};
float pipePos3[3]={105,15,0};

//pipes variables positions
float pipe1X=pipePos[0]; /*from 45 to -46.7995*/
float pipe2X=pipePos2[0];/*from 75 to -47.399*/
float pipe3X=pipePos3[0];/*from 105 to -48.0495*/

//pipes current height
float pipe1Height=15;
float pipe2Height=15;
float pipe3Height=15;

//moving pipes
float speed = 0.0; // Initial speed
float acceleration = 0.001; // Slower acceleration rate
float damping = 0.98; // Greater damping factor for slower speed reduction

float current_height;
float spaceForBird=20;
float SpaceForPipes=40;




//bird variables
float birdBody_Y=70.0;/*30 is good position to start but 70 to drop from top*/
bool lose=false;//if lose or no
float down=.1; // the bird is gores down with abstract .1 from bird height
float birdVelocity = 0.0f;
float gravity = -0.001f;



// start gameOver screen and score variable
bool buttom_moved=false;
float buttom_fast=.1;
float start_moving_variable=0; //start buttom moving variable
float end_moving_variable=0; //end buttom moving variable
float gameName_moving_variable=0;//game name and bird in start screen buttom moving variable
float moveGameOver=0; //gameOver screen moving down



//start game variable
bool Start=false;

//score variable
int counter=0;
//to just add 1 to counter without it the counter work more than once in each pipe
bool pipe1=false;
bool pipe2=false;
bool pipe3=false;




//////////////////////////////////////////////////CODE HERE ///////////////////////////////////////////////////////




/*background "mohamed"*/

void drawCircle(float radius, float x, float y, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(x, y); // Center of the circle

    for (int i = 0; i <= num_segments; ++i) {
        float theta = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(num_segments);
        float dx = radius * cos(theta);
        float dy = radius * sin(theta);
        glVertex2f(x + dx, y + dy);
    }

    glEnd();
}


void bottom(void)
{
    glPushMatrix();

    glColor3f(0.58, 0.54, 0.36); // bottom
    glBegin(GL_QUADS);
        glVertex2f(-30.0, 0.0);
        glVertex2f(30.0, 0.0);
        glVertex2f(30.0, 4.0);
        glVertex2f(-30.0, 4.0);
    glEnd();


    glColor3f(0.33, 0.49, 0.11); // bottom Green
    glBegin(GL_QUADS);
        glVertex2f(-30.0, 4.0);
        glVertex2f(30.0, 4.0);
        glVertex2f(30.0, 5.0);
        glVertex2f(-30.0, 5.0);
    glEnd();

    for (float i = -30.0, j = -25.0; j <= 30; j += 7, i += 7) {
        glColor3f(0.45, 0.61, 0.29);
        glBegin(GL_POLYGON);
        glVertex2f(i, 4.0);
        glVertex2f(j, 4.0);
        glVertex2f(i + 7, 5.0);
        glVertex2f(j + 7, 5.0);
        glEnd();
     }

    glPopMatrix();
}


void background(void)
{
    glPushMatrix();

    glColor3f(0.41, 0.61, 0.42); // Green Grass
    glBegin(GL_QUADS);
        glVertex2f(-30.0, 5.0);
        glVertex2f(30.0, 5.0);
        glVertex2f(30.0, 9.0);
        glVertex2f(-30.0, 9.0);
    glEnd();

    glColor3f(1, 1, 1); // Sky
    glBegin(GL_QUADS);
        glVertex2f(-30.0, 9.0);
        glVertex2f(30.0, 9.0);
        glVertex2f(30.0, 15.0);
        glVertex2f(-30.0, 15.0);
    glEnd();

    glColor3f(1, 1, 1);
    drawCircle(3 , -30.0, 15 , 1000); //Clouds
    drawCircle(4 , -25.0, 16 , 1000);
    drawCircle(6 , -19.0, 15 , 1000);
    drawCircle(3 , -15.0, 15 , 1000);
    drawCircle(5 , -10.0, 14 , 1000);
    drawCircle(5 , -5.0, 15 , 1000);
    drawCircle(5, -1.0, 16 , 1000);
    drawCircle(5 , 8.0, 15 , 1000);
    drawCircle(5 , 14.0, 15 , 1000);
    drawCircle(3 , 20.0, 15 , 1000);
    drawCircle(5, 22, 16 , 1000);
    drawCircle(5 , 28, 15 , 1000);
    glPopMatrix();


}



/*draw pipes "khaled"*/

// draw a top pipe and bottom pipe
void drawPipe(float width, float heightLong,float heightShort) {

//bottom pipe
glPushMatrix();
    // tube view
    glRotatef(80,4,0,0); // rotate



    //Define the quadratic object
    GLUquadricObj *quadric = gluNewQuadric();

{// long tube

    glColor3f(0.0, 109.0/255, 82.0/255); //set the color

        // Draw the pipe body
  gluCylinder(quadric, width, width, heightLong, 16, 100);


  // Draw two disks to cap the ends of the pipe
  gluDisk(quadric, 0.0, width, 16, 16);

  gluDisk(quadric, -width, 0.0, 16, 16);
}


{ // short tube


    glColor3f(0.0/255,170.0/255,127.0/255);  //set the color body

        // Draw the pipe body
  gluCylinder(quadric, width+2, width+2, heightShort, 16, 100);


    // Draw two disks to cap the ends of the pipe

    glColor3f(82.0/255, 82.0/255, 82.0/255);  //face up and down color

    gluDisk(quadric, 0.0, width+2, 16, 16);

    gluDisk(quadric, -width+2, 0.0, 16, 16);

}

glPopMatrix();


    //top pipe
    glPushMatrix();
    glTranslatef(0,spaceForBird,0);
    glRotatef(260,4,0,0);


    //Define the quadratic object
    GLUquadricObj *quadric2 = gluNewQuadric();

    {// long tube

    glColor3f(0.0, 109.0/255, 82.0/255); //set the color

        // Draw the pipe body
  gluCylinder(quadric2, width, width, SpaceForPipes-heightLong, 16, 100);


  // Draw two disks to cap the ends of the pipe
  gluDisk(quadric2, 0.0, width, 16, 16);

  gluDisk(quadric2, -width, 0.0, 16, 16);
}


{ // short tube


    glColor3f(0.0/255,170.0/255,127.0/255);  //set the color body

        // Draw the pipe body
  gluCylinder(quadric2, width+2, width+2, heightShort, 16, 100);


    // Draw two disks to cap the ends of the pipe

    glColor3f(82.0/255, 82.0/255, 82.0/255);  //face up and down color

    gluDisk(quadric2, 0.0, width+2, 16, 16);

    gluDisk(quadric2, -width+2, 0.0, 16, 16);

}
 // delete object to free memory
    glPopMatrix();

    gluDeleteQuadric(quadric2);
    gluDeleteQuadric(quadric);

}



// random function  get random number
float random_float(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    int res=dis(gen);
    return float(res);
}



// function to create continuous pipes
void createMovingPipes(float initPosition[3], float width, float heightShort , float &current_pipe_pos , float &currentHeightUsedWithBird) {
    // Check if the heightLong for this pipe has been generated
    if (initPosition[1] == 0.0) {
        // Generate a new random height for the long tube
        initPosition[1] = random_float(10, 25);
        current_height = initPosition[1];  // to know the current height
        currentHeightUsedWithBird=current_height;
    }


    glPushMatrix(); // Save the current matrix state

    // Translate to the specified initial position +5 for the buttom
    glTranslatef(initPosition[0], initPosition[1]+5, initPosition[2]);

    // Draw the pipe at the current position
    drawPipe(width, initPosition[1], heightShort);

    glPopMatrix(); // Restore the previous matrix state

    // Update speed with acceleration
    speed += acceleration;
    current_pipe_pos-=speed;

    // Apply damping to slow down the pipes
    speed *= damping;

    // Move to the next position for the next pipe with the current speed
    initPosition[0] -= speed; // Adjust the movement speed

    // If the pipe has moved off the screen, reset its position to the right
    if (initPosition[0] < -45.0) {
        initPosition[0] = 45.0;
        speed = 0.0; // Reset speed when reaching the right side
        current_pipe_pos=initPosition[0]; // start again from initial position on x-axis
        initPosition[1] = 0.0; // Reset the heightLong for the next pipe
    }

}





/*draw bird "khaled moursi"*/

void drawBird(float &birdStartHeight) {

     glPushMatrix();//move hole bird

    // Body
    glColor3f(1.0f, 0.9f, 0.0f);  // yellow color
    glPushMatrix();
    glTranslatef(-20.0f, birdBody_Y, 0.0f);
    glutSolidSphere(2, 20, 20);  // Body
    glPopMatrix();

    // Head
    glColor3f(1.0f, 1.0f, 0.0f);  // Yellow color
    glPushMatrix();
    glTranslatef(-18.0f, birdBody_Y+2, 0.0f);
    glutSolidSphere(1, 20, 20);  // Head
    glPopMatrix();

    // Beak (Triangle)
    glColor3f(1.0f, 0.5f, 0.0f);  // Orange color
    glPushMatrix();
    glTranslatef(-17.5f, birdBody_Y+1, 0.0f);
    glRotatef(-15.0f, 0.0f, 0.0f, 1.0f);
    glScalef(.4,.4,1);

    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(4.0f, 2.0f);
    glVertex2f(0.0f, 4.0f);
    glEnd();

    glPopMatrix();

    // Eye
    glColor3f(0.0f, 0.0f, 0.0f);  // Black color
    glPushMatrix();
    glTranslatef(-18.0f,birdBody_Y+2, 0.0f);
    glutSolidSphere(.2, 10, 10);  // Eye
    glPopMatrix();

    glPopMatrix();

    // if bird is not on the ground
    if (birdStartHeight > 8){
         // Apply gravity to the bird's velocity
        birdVelocity += gravity;
        // Update the bird's position based on velocity
        birdStartHeight += birdVelocity;
    }else{
    //if bird is on the ground it lose
    lose=true;

    }

}


/*game logic*/
bool lose_game(float &pipeRandomeHeight , float &pipeNumberX){

   if ((pipeNumberX >= -26  && pipeNumberX <= -14) && ((pipeRandomeHeight+7 >= birdBody_Y) || (pipeRandomeHeight+2+spaceForBird <= birdBody_Y) ) ){
     lose=true;
   }
}




/*start and end screen and score function "3zoz"*/
void Output(int x,int y, void *font, char *string){
    glRasterPos2f(x,y);
    while(*string){
        glutBitmapCharacter(font ,*string);
        string++;
    }
}


//Bottom
void Bottoms(){
        //start buttom
        glPushMatrix();

        glTranslatef(start_moving_variable,0,0);
            glColor3f(142.0/255,195.0/255,244.0/255);
        glBegin(GL_POLYGON);
        glVertex2f(-26,16);
        glVertex2f(-26,19);
        glVertex2f(-9,19);
        glVertex2f(-9,16);
        glEnd();

            glColor3f(0.0,1.0,0.0);
        glBegin(GL_POLYGON);
        glVertex2f(-25,15);
        glVertex2f(-25,20);
        glVertex2f(-10,20);
        glVertex2f(-10,15);
        glEnd();

        //text "start"
        glColor3f(0.0, 0.0, 0.0);
        Output(-22.5,17,GLUT_BITMAP_TIMES_ROMAN_24,"START");
           glPopMatrix();

           //exit buttom
         glPushMatrix();
         glTranslatef(end_moving_variable,0,0);
            glColor3f(142.0/255,195.0/255,244.0/255);
        glBegin(GL_POLYGON);
        glVertex2f(26,16);
        glVertex2f(26,19);
        glVertex2f(9,19);
        glVertex2f(9,16);
        glEnd();
            glColor3f(0.0,1.0,0.0);
        glBegin(GL_POLYGON);
        glVertex2f(25,15);
        glVertex2f(25,20);
        glVertex2f(10,20);
        glVertex2f(10,15);
        glEnd();

        //text "end"
        glColor3f(0.0, 0.0, 0.0);
        Output(14,17,GLUT_BITMAP_TIMES_ROMAN_24,"EXIT");
           glPopMatrix();


}




//Start Screen
void Start_Screen(){

        /*bird start*/
 glPushMatrix();//move hole bird
  glTranslatef(0,gameName_moving_variable,0);
     glTranslatef(18,20,0);

    // Body
    glColor3f(1.0f, 0.8f, 0.0f);  // Red color
    glPushMatrix();
    glTranslatef(-20.0f, 20.0f, 0.0f);
    glutSolidSphere(2, 20, 20);  // Body
    glPopMatrix();

    // Head
    glColor3f(1.0f, 1.0f, 0.0f);  // Yellow color
    glPushMatrix();
    glTranslatef(-18.0f, 22.0f, 0.0f);
    glutSolidSphere(1, 20, 20);  // Head
    glPopMatrix();

    // Beak (Triangle)
    glColor3f(1.0f, 0.5f, 0.0f);  // Orange color
    glPushMatrix();
    glTranslatef(-17.5f, 21.0f, 0.0f);
    glRotatef(-15.0f, 0.0f, 0.0f, 1.0f);
    glScalef(.4,.4,1);

    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(4.0f, 2.0f);
    glVertex2f(0.0f, 4.0f);
    glEnd();

    glPopMatrix();

    // Eye
    glColor3f(0.0f, 0.0f, 0.0f);  // Black color
    glPushMatrix();
    glTranslatef(-18.0f, 22.0f, 0.0f);
    glutSolidSphere(.2, 10, 10);  // Eye
    glPopMatrix();

    glPopMatrix();
        /*bird end*/
        Bottoms();
        glPushMatrix();
        glTranslatef(0,gameName_moving_variable,0);
        glColor3f(1.0, 1.0, 1.0);
        Output(-11,50,GLUT_BITMAP_TIMES_ROMAN_24,"FLUPPY BEARD");
        glPopMatrix();


        // after press start the buttoms will moved of screen
        if(Start){

                if(start_moving_variable >= -30 )
                    start_moving_variable-=buttom_fast;
                if(end_moving_variable <= 30 )
                    end_moving_variable+=buttom_fast;
                if(gameName_moving_variable <= 31 )
                    gameName_moving_variable+=buttom_fast;


                    if(start_moving_variable >= -21 && end_moving_variable <= 21 && gameName_moving_variable <= 22 )
                        buttom_moved=true;
        }


    }




// game over screen
void Game_Over(){
        glPushMatrix();
        glTranslatef(0,moveGameOver,0);
            if(moveGameOver>=-60)
                moveGameOver-=buttom_fast;
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_POLYGON);
        glVertex2f(-30,60);
        glVertex2f(-30,120);
        glVertex2f(30,120);
        glVertex2f(30,60);
        glEnd();
           glPopMatrix();


     glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0,moveGameOver,0);
    Output(-10,90,GLUT_BITMAP_TIMES_ROMAN_24,"GAME OVER");
     glPopMatrix();

     //score in game over screen
    glPushMatrix();
    glTranslatef(0,moveGameOver,0);
    glRasterPos2f(-6, 85); //position
     string displayed="Score : " + to_string(counter);
    for (int i = 0; displayed[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, displayed[i]);

     glPopMatrix();
     }



//score
void Score() {
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2f(-25, 55);
    string displayed = to_string(counter);
    for (int i = 0; displayed[i]; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, displayed[i]);

            //three variable for each pipe if pipe moved add 1 to the counter "pipe1==false" to just add 1 to counter
        if(pipe1X+5 <=-20){
                if(pipe1==false){
                        counter++;
                        pipe1=true;
                        pipe3=false;
                }

        }
        if(pipe2X+5 <=-20){
                if(pipe2==false){
                        counter++;
                        pipe2=true;
                }

        }
        if(pipe3X+5 <=-20){
                if(pipe3==false){
                        counter++;
                        pipe3=true;
                        pipe1=false;
                        pipe2=false;

                }

        }


    glPopMatrix();
}


#endif // GAME_H_INCLUDED
