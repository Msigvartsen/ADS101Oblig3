#include <iostream>
#include <hash_map>
#include <unordered_set>
#include "playerprofile.cpp"
#include <fstream>
#include <sstream>

namespace std {
    template<>
    class hash<PlayerProfile>
    {
    public:
        size_t operator() (const PlayerProfile& profile) const
        {
            unsigned int hashVal{0};
            for(auto ch : profile.key) {
                hashVal = 37 * hashVal + ch;
            }
            return hashVal % 170;
        }
        bool operator() (const PlayerProfile& profile1, const PlayerProfile& profile2)
        {
            return profile1.key == profile2.key;
        }
    };
}


template<typename T>
void testReader(const std::string fileName, std::vector<T> &list)
{
    std::ifstream read("../Oblig3/files/" + fileName +".txt");
    if(!read) {
        std::cerr << "Error reading from file! " << fileName << "\n";
        std::exit(1);
    }
    std::string fileLine;
    std::string data;
    while(std::getline(read,fileLine)) {
        std::istringstream ss(fileLine);
        while(std::getline(ss, data,',')) {
            list.push_back(data);
        }
    }
    read.close();
}

int main()
{
    PlayerProfile player;
    std::vector<std::string> playerList;
    playerList.reserve(210);
    //Read player info from file. Add to vector.
    testReader("playerList",playerList);

    std::unordered_set<PlayerProfile> us;
    std::unordered_set<PlayerProfile>::iterator usit;
    std::pair<std::unordered_set<PlayerProfile>::iterator,bool> par;

    std::cout << "--------- UNORDERED_MULTISET -------------\n\n";
    us.reserve(170);
    std::cout << "Load = " << us.load_factor() << "\n";

    //Loop through vector containing player data. Key is all Odd numbers, rating is all even numbers.
    for(unsigned int i{0}; i < playerList.size(); i++) {

        if(i%2 == 0) {
            player.key = playerList.at(i);
        } else {
            player.rating = playerList.at(i);
            par = us.insert(player);
        }
    }
    //Player array contains info with name and rating. Divide by two to get number of keys.
    std::cout << "Inserting list in unordered set...\n";
    std::cout << "Load = " << us.load_factor() << "\n\n";
    std::cout << "Player Array Size() = " << playerList.size()/2 << "\n";
    std::cout << "Unordered_set size:" << us.size() << "\n";
    std::cout << "Number of duplicates: " << (playerList.size()/2)-us.size() << "\n";
    player.key = "Lyndia_Hedges";
    usit = us.find(player);
    player = *usit;
    std::cout << "\nSearching for Lyndia Hedges:\n"<< player.key << "\nRating: " << player.rating << "\n\n";
    player.key = "Alyson_Pollack";
    usit = us.find(player);
    player = *usit;
    std::cout << "\nSearching for Alyson_Pollack:\n"<< player.key << "\nRating: " << player.rating << "\n\n";


    //------------------ unordered_multiset ---------------------
    PlayerProfile playerProfile;
    std::unordered_multiset<PlayerProfile> multiset;
    std::unordered_multiset<PlayerProfile>::iterator msit;
    std::pair<std::unordered_multiset<PlayerProfile>::iterator,bool> mspair;
    std::cout << "--------- UNORDERED_MULTISET -------------\n\n";
    multiset.reserve(170);
    std::cout << "Load = " << multiset.load_factor() << "\n";
    for(unsigned int i{0}; i < playerList.size(); i++) {
        if(i%2 == 0) {
            playerProfile.key = playerList.at(i);
        } else {
            playerProfile.rating = playerList.at(i);
            multiset.insert(playerProfile);
        }
    }
    std::cout << "Inserting list in unordered multiset...\n";
    std::cout << "Load = " << multiset.load_factor() << "\n\n";
    std::cout << "Player array size: " << playerList.size()/2 << "\n";
    std::cout << "Multiset size: " << multiset.size() << "\nContains duplicates\n\n";
    playerProfile.key = "Micah_Lorenzo";
    msit = multiset.find(playerProfile);
    playerProfile = *msit;
    std::cout << "\nSearching for Micah Lorenzo:\n"<< playerProfile.key << "\nRating: " << playerProfile.rating << "\n\n";
    playerProfile.key = "Erna_Song";
    msit = multiset.find(playerProfile);
    playerProfile = *msit;
    std::cout << "\nSearching for Erna Song:\n"<< playerProfile.key << "\nRating: " << playerProfile.rating << "\n\n";
    return 0;
}
