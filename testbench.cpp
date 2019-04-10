#include<systemc.h>
#include<robot_module.cpp>
#include<server_module.cpp> 
#include<environment_module.cpp> 

SC_MODULE(test_bench) {

	//environment module variables
	sc_signal<bool> clock, relay_start_from_robot, relay_stop_from_robot, check_delta_crossing_to_robot, check_boundary_crossing_to_robot, check_obstacle_to_robot;

	//robot module variables
	sc_signal<bool> robot_enable_from_server, robot_started_from_server, robot_ended_from_server, check_delta_crossing_from_env, check_boundary_crossing_from_env, check_obstacle_from_env, relay_start_to_env, relay_stop_to_env, send_enable_to_server, check_delta_crossing_to_server, check_boundary_crossing_to_server, check_obstacle_to_server; 

	//server module variables
	sc_signal<bool> check_delta_crossing_from_robot, check_boundary_crossing_from_robot, check_obstacle_from_robot, server_enable_from_robot, start_to_robot, stop_to_robot, enable_to_robot;

	
	environment_module*env;
	robot_module*robot;
	server_module*server;

	void clock_signal();

	SC_CTOR(test_bench){

		env = new environment_module("Enivronment Module");
		robot = new robot_module("Robot Module");
		server = new server_module("Server Module");


		 //signals from server to robot

                           server->enable_to_robot(enable_to_robot);

                           robot->robot_enable_from_server(enable_to_robot);

                           server->start_to_robot(start_to_robot);

                           robot->robot_started_from_server(start_to_robot);

                           server->stop_to_robot(stop_to_robot);

                           robot->robot_ended_from_server(stop_to_robot);
// signals from robot to server

						robot->send_enable_to_server(send_enable_to_server);

                           server->server_enable_from_robot(send_enable_to_server);

                           robot->check_delta_crossing_to_server(check_delta_crossing_to_server);

                           server->check_delta_crossing_from_robot(check_delta_crossing_to_server);

                           robot->check_boundary_crossing_to_server(check_boundary_crossing_to_server);

                           server->check_boundary_crossing_from_robot(check_boundary_crossing_to_server);

                           robot->check_obstacle_to_server(check_obstacle_to_server);

                           server->check_obstacle_from_robot(check_obstacle_to_server);

 

                           //signals from environment to robot

                           env->clock(clock);

                           env->check_delta_crossing_to_robot(check_delta_crossing_to_robot);

                           robot->check_delta_crossing_from_env(check_delta_crossing_to_robot);

                           env->check_boundary_crossing_to_robot(check_boundary_crossing_to_robot);

                           robot->check_boundary_crossing_from_env(check_boundary_crossing_to_robot);

                           env->check_obstacle_to_robot(check_obstacle_to_robot);

                           robot->check_obstacle_from_env(check_obstacle_to_robot);

 

                           //signals from robot to environment

                           robot->relay_start_to_env(relay_start_to_env);

                           env->relay_start_from_robot(relay_start_to_env);

                           robot->relay_stop_to_env(relay_stop_to_env);

                           env->relay_stop_from_robot(relay_stop_to_env);

		SC_THREAD(clock_signal);
		
	}
};

void test_bench::clock_signal() {
	while (true){
	    wait(0.5 , SC_MS);
		clock = false;
		wait(0.5 , SC_MS);
		clock = true;
	}
}

int sc_main(int argc , char* argv[]) {

	cout<<"@ "<<sc_time_stamp()<<"----------Start---------"<<endl<<endl<<endl;
	test_bench test_bench("Robot Navigation");

	cout<<"@ "<<sc_time_stamp()<<"----------Start Simulation---------"<<endl<<endl<<endl;
	sc_start(50000 , SC_MS);
	cout<<"@ "<<sc_time_stamp()<<"----------End Simulation---------"<<endl<<endl<<endl;
	return 0;
}