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
		return 1;
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
	Bowling_Frame** players = new Bowling_Frame*[number_of_players];
	
	// replaced (make frames) to make 10 frames for each player by using loops instead
	for (int player = 0; player < number_of_players; player++)
		{
			//save first frame in array
			players[player] = new Bowling_Frame(1);
			Bowling_Frame* previous = players[player];
			//make remaing frames then link together
			for (int frame = 2; frame <= 10; frame++)
				{
					Bowling_Frame* current = new Bowling_Frame(frame);
					//Link forward to next frame
					previous->next_frame(current);
					//link backwards to previous grame
					current->prev_frame(previous);
					previous = current;
				}
		}

	//replace(set frame scores) to simulate scores and allow enough callf for final-frame bonus	
	for (int roll = 0; roll < 22; roll++)
		{
			for (int player = 0; player < number_of_players; player++)
				{
					players[player]->update_scores();
				}
		}

	//print values replaced and updated to a loop to print frame scores and game total for each player
	for (int player = 0; player < number_of_players; player++)
		{
			cout << "\nPlayer " << player + 1 << endl;
			//start at players first frame, iterate through,and print each value
			Bowling_Frame* traverse = players[player];
			while(traverse != nullptr)
			{
				cout << "Frame " << traverse->frame_num() << ": " << endl
					<< " Score 1: " << traverse->score1() << endl
					<< " Score 2: " << traverse->score2() << endl;
				//show third roll only when final grame earns it
				if (traverse->frame_num() == 10 && (traverse->strike() || traverse->spare()))
				{
					cout << " Score 3: " << traverse->score3() << endl;
				}
					cout << " Frame total: " << traverse->frame_score() << endl;

		traverse = traverse->next_frame();
	}
			//calculator to get game total
		cout << "Total score: " << current_game_total(players[player]) << endl;
	}
	//cleanup and delete the frames allocated for players
	for (int player = 0; player < number_of_players; player++)
	{
		Bowling_Frame* current = players[player];
		while (current != nullptr)
		{
			//save next frame before deleting current one
			Bowling_Frame* next = current->next_frame();
			//disconnect neighbors because of starter desctructor and attempt to free next and previous pointers
			current->next_frame(nullptr);
			current->prev_frame(nullptr);
			delete current;
			current = next;
		}
	}
	//delete array of player pointers
	delete[] players;
	return 0;
}
