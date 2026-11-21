#include <iostream>
#include "bowling_frame.h"
#include <random>
#include <cstdlib> // make player-count argument to integer

using namespace std;

std::random_device dev_main;
std::mt19937 rng_main(dev_main());

int current_game_total(Bowling_Frame * first_frame)
{
	Bowling_Frame * temp = first_frame;
	int game_total = 0;
	int temp_total = 0;
	while(temp)
	{
		game_total += temp->frame_score();
		temp = temp->next_frame();
	}
	return game_total;	
}

int main(int argc, char* argv[]) //argc # of items in command include prgram name, argv array containing items text
{
	//require one command-line argument for # players
	if (argc != 2)
	{
		cout << "Usage: " << argv[0] << " <number of players>" << endl;
		retun 1;
	}
	//atoi converts text to integer (ASCII to Integer)
	int number_of_players = atoi(argv[1]);

	//ensure at least one player
	if (number_of_players <= 0)
	{
		cout << "The number of players must be greater than zero." << endl;
		return 1;
	}
	//store first frame of each players list
	Bowling_Frame** players = new Bowling_Frame*[numbe_of_players];
	
	//make frames
	Bowling_Frame * f1 = new Bowling_Frame(1);
	Bowling_Frame * f2 = new Bowling_Frame(2);
	Bowling_Frame * f3 = new Bowling_Frame(3);

	//link frames together
	f1->next_frame(f2);

	f2->next_frame(f3);
	f2->prev_frame(f1);

	f3->prev_frame(f2);	

	//set frame scores	
	f1->update_scores();
	f1->update_scores();
	cout << "Frame 1 Total: " << current_game_total(f1) << endl;

	f1->update_scores();
	f1->update_scores();
	cout << "Frame 1 and 2 Total: " << current_game_total(f1) << endl;


	f1->update_scores();
	f1->update_scores();
	cout << "Frame 1,2,and 3 Total: " << current_game_total(f1) << endl;

	//print values
	cout << "Frame " << f1->frame_num() << ": " << endl
		 << " Score 1: " << f1->score1() << endl
		 << " Score 2: " << f1->score2() << endl;

	cout << "Frame " << f2->frame_num() << ": " << endl
	     << " Score 1: " << f2->score1() << endl
		 << " Score 2: " << f2->score2() << endl;

	cout << "Frame " << f3->frame_num() << ": " << endl
	     << " Score 1: " << f3->score1() << endl
		 << " Score 2: " << f3->score2() << endl;

	//iterate through linked list and print values
	Bowling_Frame * traverse = f1;
	
	while(traverse)
	{
		cout << "Frame " << traverse->frame_num() << ": " << endl
		 	 << " Score 1: " << traverse->score1() << endl
		 	 << " Score 2: " << traverse->score2() << endl;

		traverse = traverse->next_frame();
	}

}
