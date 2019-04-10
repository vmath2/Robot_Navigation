#include<systemc.h>

SC_MODULE(environment_module){
	
	sc_in<bool> clock;
	sc_in<bool> relay_start_from_robot;
	sc_in<bool> relay_stop_from_robot; 
	


	sc_out<bool> check_delta_crossing_to_robot;
	sc_out<bool> check_boundary_crossing_to_robot;
	sc_out<bool> check_obstacle_to_robot;


     float robot_X = 0;
     float robot_Y = 0;

     float obstacle_X =6;
     float obstacle_Y = 0;

     sc_uint<2> ROBOT_SPEED = 0b10;
     sc_uint<3> OBSTACLE_SPEED = 0b101;

     SC_CTOR(environment_module){

     	SC_THREAD(robotMovement);
     	sensitive<<clock.pos();

 	} 

	
	bool isObstaclePassed();
	void robotMovement();
	void checkDeltaCrossing();

 };
	
	bool environment_module:: isObstaclePassed(){

		return (obstacle_X -robot_X >3 || obstacle_X < robot_X);
	}

	void environment_module::robotMovement(){
		while(true){
			wait();
			obstacle_X = obstacle_X - OBSTACLE_SPEED*0.001;
			if(!relay_stop_from_robot.read()){ 
				if(isObstaclePassed()){
				 	robot_X = robot_X + ROBOT_SPEED*0.001;
				 	checkDeltaCrossing();
				 	check_obstacle_to_robot.write(false);
				} else{
				 	check_obstacle_to_robot.write(true);
				}
 			}
 			cout<<"/**<-------------------------------------:: ENVIRONMENT MODULE LOG ::--------------------------------->**/"<<endl;
		 	cout<<"       Robot Position : "<<robot_X<<endl;
			cout<<"       Obstacle Position : "<<obstacle_X<<endl;
			cout<<"       Check Obstacle: "<<check_obstacle_to_robot<<endl;
			cout<<"/**<----------------------------------:: ENVIRONMENT MODULE LOG ::--------------------------------->**/"<<endl<<endl<<endl;
		}
	}

	void environment_module:: checkDeltaCrossing(){

		if(!relay_stop_from_robot.read()){
			robot_X = robot_X -(int)robot_X;
			 if(robot_X >=0.5){
			 	check_delta_crossing_to_robot.write(true);
			 } else{
			 	check_delta_crossing_to_robot.write(false);
			 }
			 if(robot_X ==0){
			 	check_boundary_crossing_to_robot.write(true);
				check_delta_crossing_to_robot.write(false);
			} else{
				check_boundary_crossing_to_robot.write(false);
				check_delta_crossing_to_robot.write(false);
			}
		}

	}