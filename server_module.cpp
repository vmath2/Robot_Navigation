#include <systemc.h>

 

//template <class data_size>

SC_MODULE(server_module) {

 

             sc_in<bool> check_delta_crossing_from_robot;

             sc_in<bool> check_boundary_crossing_from_robot;

             sc_in<bool> check_obstacle_from_robot;

             sc_in<bool> server_enable_from_robot;

 

             sc_out<bool> start_to_robot;

             sc_out<bool> stop_to_robot;

             sc_out<bool> enable_to_robot;

 

             //sc_uint<1> robot_index[5];

             //sc_uint<4> current_location[5];

             //sc_uint<4> next_location[5];

 
             
             std::vector<sc_uint<13> > robots;
             sc_uint<3> const robot_end_Position = 0b110;

             void signal_to_robot();
             void signal_to_obstacle();

           
 	
             SC_CTOR(server_module){

              SC_METHOD(signal_to_robot);

              sensitive<<server_enable_from_robot.pos();

              SC_METHOD(signal_to_obstacle);
              sensitive<<check_obstacle_from_robot.pos();

              	 for(int i=0; i<1; i++){
              	robots.push_back(0b0000010000000);
              }

             
             }

};

 

void server_module::signal_to_robot(){
	
	robots[0].range(12,12) = 0b1;
	sc_uint<1> robot_status= robots[0].range(12,12);
bool start_Robot = true;

if(check_boundary_crossing_from_robot.read()){
	

sc_uint<6> next_grid = robots[0].range(11,6);
sc_uint<6> current_grid = robots[0].range(5,0);

if(next_grid == robot_end_Position){
	bool start_Robot=false;
	enable_to_robot.write(true);
	stop_to_robot.write(true);
	
	 robot_status = 0b0;

} 
current_grid = robots[0].range(11,6);
next_grid= next_grid + 0b000001;

cout<<"/**<-------------------------------------:: SERVER LOG ::--------------------------------->**/"<<endl;
	cout<<"       Robot Status : "<<current_grid<<endl;
	cout<<"       Current Grid : "<<robots[0].range(5,0)<<endl;
	cout<<"       Next Grid : "<<robots[0].range(11,6)<<endl;
	cout<<"/**<----------------------------------:: SERVER LOG ::--------------------------------->**/"<<endl<<endl<<endl;

}

stop_to_robot.write(start_Robot);


 }

 void server_module::signal_to_obstacle(){
 	if(check_obstacle_from_robot.read()){
 		robots[0].range(12,12)= 0b0;
 	}
 }