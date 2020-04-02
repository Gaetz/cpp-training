#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::cin;
using std::string;

int main(int argc, char *argv[])
{
    const int GOLD_PIECES = 900;
    int adventurers, killed, survivors;
    string leader;

    cout << "-=> LOST FORTUNE <=-" << endl;
    cout << "Please enter information for your personalized adventure.\n"; 
    cout << "Enter a number: ";
    cin >> adventurers;
    cout << "Enter a number, smaller than the first: ";
    cin >> killed;

    survivors = adventurers - killed;

    cout << "Enter your name, without space: ";
    cin >> leader;

    // Story
    cout << "\nA brave group of " << adventurers << " adventurers set out on a quest ";
    cout << "in search of the lost treasure of the Ancient Dwarves. ";
    cout << "The group was led by the legendary rogue, " << leader << ".\n";

    cout << "\nAlong the way, a band of marauding ogres ambushed the party. ";
    cout << "All fought bravely under the command of " << leader;
    cout << ", and the ogres were defeated, but at a cost. ";
    cout << "Of the adventurers, " << killed << " were vanquished, ";
    cout << "leaving just " << survivors << " in the group.\n";

    cout << "\nThe party was about to give up all hope. ";
    cout << "But while laying the deceased to rest, ";
    cout << "they stumbled upon the buried fortune. ";
    cout << "So the adventurers split " << GOLD_PIECES << " gold pieces. ";
    cout << leader << " held on the extra " << GOLD_PIECES % survivors;
    cout << " pieces to keep things fair, of course.\n";

    // End of program
    char end;
    cout << "\nEnter a char to end >> ";
    cin >> end;

    return 0;
}