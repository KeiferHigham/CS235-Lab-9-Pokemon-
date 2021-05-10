#include <iostream>
#include <fstream>
#include <sstream>
#include "Set.h"
#include "HashMap.h"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 3) {
        cerr << "please provide the name of the input and output files" << endl;
        return 1;
    }
    cout << "Input file " << argv[1] << endl;
    ifstream in(argv[1]);
    if(!in) {
        cout << "unable to open " << argv[1] << " for input" << endl;
        return 2;
    }
    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out) {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }

    Set<string> addSet;

     string command;

     HashMap<string,string> pokemon;
     HashMap<string,string> moves;
     HashMap<string,Set<string>> effective;
     HashMap<string,Set<string>> ineffective;

    for(string userInput; getline(in, userInput);) {
        stringstream iss(userInput);
        iss >> command;
        if(userInput == "") {
            continue;
        }
        if (command == "Set:") {
            if(userInput == "") {
                continue;
            }
            out << userInput << endl;
            string userWord;
            while (iss >> userWord) {
                addSet.insert(userWord);
            }
            out << "[" << addSet.toString() << "]" << endl << endl;
            addSet.clear();
        }

        if(command == "Pokemon:") {
            if(userInput == "") {
                continue;
            }

            out << userInput << endl;
           string key;
           string value;
           iss >> key;
           iss >> value;
           if(key != "" && value != "") {

               pokemon[key] = value;
           }
        }
        if(command == "Move:") {
            if(userInput == "") {
                continue;
            }
            out << userInput << endl;
           string key;
           string value;
           iss >> key;
           iss >> value;
           moves[key] = value;
        }
        if(command == "Pokemon") {
            if(userInput == "") {
                continue;
            }
            out << endl << "Pokemon: ";
           out << pokemon.toString();
        }
        if(command == "Moves") {
            if(userInput == "") {
                continue;
            }
            out << endl << "Moves: ";
            out << moves.toString();
        }
        if(command == "Effective:") {
          if(userInput == "") {
              continue;
          }
          out << userInput << endl;
            string key;
         string value;
          iss >> key;
          while(iss >> value) {
           effective[key].insert(value);
          }
        }
        if(command == "Ineffective:") {
            if(userInput == "") {
                continue;
            }
            out << userInput << endl;
            string key;
            string value;
            iss >> key;
            while(iss >> value) {
                ineffective[key].insert(value);
            }
        }
        if(command == "Effectivities") {
            if(userInput == "") {
                continue;
            }
            out << endl << "Effectivities: ";
            out << effective.toString();
        }
        if(command == "Ineffectivities") {
            out << endl << "Ineffectivities: ";
            out << ineffective.toString();
            out << endl;
        }
        if(command == "Battle:") {
            out << userInput << endl;
            string firstPokemon;
            string secondPokemon;
            string firstMove;
            string secondMove;
            iss >> firstPokemon;
            iss >> firstMove;
            iss >> secondPokemon;
            iss >> secondMove;
            out << firstPokemon << "(" << firstMove << ")" << " vs " << secondPokemon << " (" << secondMove << ")" << endl;
            out << firstPokemon << " is a " << pokemon[firstPokemon] << " type Pokemon." << endl;
            out << secondPokemon << " is a " << pokemon[secondPokemon] << " type Pokemon." << endl;
            out << firstMove << " is a " << moves[firstMove] << " type move." << endl;
            out << secondMove << " is a " << moves[secondMove] << " type move." << endl;
            out << firstMove << " is super effective against " << "[" << effective[moves[firstMove]].toString() << "]" << " type Pokemon." << endl;
            out << firstMove << " is ineffective against " << "[" << ineffective[moves[firstMove]].toString() << "]" << " type Pokemon." << endl;
            out << firstPokemon << "'s " << firstMove << " is ";
            if(effective[moves[firstMove]].count(pokemon[secondPokemon]) == 1) {
                out << "super effective against " << secondPokemon << endl;
            }
            else if(ineffective[moves[firstMove]].count(pokemon[secondPokemon]) == 1) {
                out << "ineffective against " << secondPokemon << endl;
            }
            else {
                out << "effective against " << secondPokemon << endl;
            }
            out << secondMove << " is super effective against " << "[" << effective[moves[secondMove]].toString() << "]" << " type Pokemon." << endl;
            out << secondMove << " is ineffective against " << "[" << ineffective[moves[secondMove]].toString() << "]" << " type Pokemon." << endl;
           out << secondPokemon << "'s " << secondMove << " is ";
            if(effective[moves[secondMove]].count(pokemon[firstPokemon]) == 1) {
                out << "super effective against " << firstPokemon << endl;
            }
            else if(ineffective[moves[secondMove]].count(pokemon[firstPokemon]) == 1) {
                out << "ineffective against " << firstPokemon << endl;
            }
            else {
                out << "effective against " << firstPokemon << endl;
            }
            int damageAtoB = effective[moves[firstMove]].count(pokemon[secondPokemon]) -
                     ineffective[moves[firstMove]].count(pokemon[secondPokemon]);
            int damageBtoA = effective[moves[secondMove]].count(pokemon[firstPokemon]) -
                    ineffective[moves[secondMove]].count(pokemon[firstPokemon]);
            int damage1To2 = int(damageAtoB);
            int damage2To1 = int(damageBtoA);

            if((damage1To2 - damage2To1) == 0) {
                out << "The battle between " << firstPokemon << " and " << secondPokemon << " is a tie." << endl << endl;
            }
            if((damage1To2 - damage2To1) > 0) {
                out << "In the battle between " << firstPokemon << " and " << secondPokemon << ", ";
                out << firstPokemon << " wins!" << endl << endl;
            }
            if(damage1To2 - damage2To1 < 0) {
                out << "In the battle between " << firstPokemon << " and " << secondPokemon << ", ";
                out << secondPokemon << " wins!" << endl << endl;
            }

        }
    }















    return 0;
    }











