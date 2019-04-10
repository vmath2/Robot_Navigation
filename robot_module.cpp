# include<systemc.h>

SC_MODULE(robot_module){
	
	sc_in<bool> robot_enable_from_server;
	sc_in<bool> robot_started_from_server;
	sc_in<bool> robot_ended_from_server;
	sc_in<bool> check_delta_crossing_from_env;
	sc_in<bool> check_boundary_crossing_from_env;
	sc_in<bool> check_obstacle_from_env;
	
	
	sc_out<bool> relay_start_to_env;
	sc_out<bool> relay_stop_to_env;
	sc_out<bool> send_enable_to_server;
	sc_out<bool> check_delta_crossing_to_server;
	sc_out<bool> check_boundary_crossing_to_server;
	sc_out<bool> check_obstacle_to_server;

	void relay_to_server();
	void relay_to_env();


	SC_CTOR(robot_module){

	
	SC_THREAD(relay_to_server);

	sensitive<< check_delta_crossing_from_env;
	sensitive<< check_boundary_crossing_from_env;
	sensitive<< check_obstacle_from_env;
	
	}
	
};

void robot_module::relay_to_server(){
	while(true){
		wait();	

check_delta_crossing_to_server.write(check_delta_crossing_from_env);
check_boundary_crossing_to_server.write(check_boundary_crossing_from_env);
check_obstacle_to_server.write(check_obstacle_from_env);
send_enable_to_server.write(true);
wait(10, SC_MS);
send_enable_to_server.write(false);
}
cout<<"/**<-------------------------------------:: ROBOT MODULE LOG ::--------------------------------->**/"<<endl;
	cout<<"       Check Delta Crossing : "<<check_delta_crossing_to_server<<endl;
	cout<<"       Check Boundary Crossing : "<<check_boundary_crossing_to_server<<endl;
	cout<<"       Check Obstacle To Server : "<<check_obstacle_to_server<<endl;
	cout<<"       Enable Signal to Server : "<<send_enable_to_server<<endl;

	cout<<"/**<----------------------------------:: ROBOT MODULE LOG ::--------------------------------->**/"<<endl<<endl<<endl;
}

void robot_module::relay_to_env(){
	relay_start_to_env.write(relay_start_to_env);
	relay_stop_to_env.write(relay_stop_to_env);

	cout<<"/**<-------------------------------------:: ROBOT MODULE LOG ::--------------------------------->**/"<<endl;
	cout<<"       Relay Start To Environment: "<<relay_start_to_env<<endl;
	cout<<"       Relay Stop To Env : "<<relay_stop_to_env<<endl;
	cout<<"/**<----------------------------------:: ROBOT MODULE LOG ::--------------------------------->**/"<<endl<<endl<<endl;
}