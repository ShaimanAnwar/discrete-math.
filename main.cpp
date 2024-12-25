#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_STUDENTS = 100;
const int MAX_FRIENDS = 10;

int main() {
    string students[MAX_STUDENTS];
    string friends[MAX_STUDENTS][MAX_FRIENDS];
    int studentCount = 0;

    ifstream infile("C:\\Users\\hp\\Documents\\dis\\friends_list.txt");

    if (!infile) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    string line;

    while (getline(infile, line)) {
        string student1, friendsList;
        size_t colonPos = line.find(":");

        student1 = line.substr(0, colonPos);
        friendsList = line.substr(colonPos + 1);

        bool studentExists = false;
        for (int i = 0; i < studentCount; i++) {
            if (students[i] == student1) {
                studentExists = true;
                break;
            }
        }

        if (!studentExists) {
            students[studentCount] = student1;
            studentCount++;
        }

        size_t startPos = 0;
        int friendIndex = 0;

        while (friendIndex < MAX_FRIENDS) {
            size_t commaPos = friendsList.find(",", startPos);
            if (commaPos == string::npos) {
                break;
            }

            string friendName = friendsList.substr(startPos, commaPos - startPos);
            startPos = commaPos + 1;

            size_t first = friendName.find_first_not_of(" ");
            size_t last = friendName.find_last_not_of(" ");
            friendName = friendName.substr(first, last - first + 1);

            friends[studentCount - 1][friendIndex] = friendName;
            friendIndex++;
        }
    }

    infile.close();

    cout << "List of Students and their Friends:" << endl;
    for (int i = 0; i < studentCount; i++) {
        cout << students[i] << ": ";
        for (int j = 0; j < MAX_FRIENDS && !friends[i][j].empty(); j++) {
            cout << friends[i][j] << ", ";
        }
        cout << endl;
    }

    cout << "\nCommon Friends Between Students:" << endl;

    for (int i = 0; i < studentCount; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            int commonFriendCount = 0;

            for (int x = 0; x < MAX_FRIENDS && !friends[i][x].empty(); x++) {
                for (int y = 0; y < MAX_FRIENDS && !friends[j][y].empty(); y++) {
                    if (friends[i][x] == friends[j][y]) {
                        commonFriendCount++;
                    }
                }
            }

            if (commonFriendCount > 0) {
                cout << students[i] << " and " << students[j]
                     << " have " << commonFriendCount << " common friends." << endl;
            }
        }
    }

    return 0;
}
