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
void readFromFile(const std::string fileName, std::vector<T> &list)
{
    std::ifstream read("../Oblig3/files/" + fileName +".txt");
    if(!read) {
        std::cerr << "Error reading from file! " << fileName << "\n";
        std::exit(1);
    }
    while(read) {

        T input;
        read >> input;
        list.push_back(input);
    }
    read.close();
}

int main()
{
    PlayerProfile player;
    std::vector<std::string> names;
    names.reserve(105);
    std::vector<int> rating;
    rating.reserve(105);

    std::cout << "Names vector size: " << names.size() << "\n";

    readFromFile("nameList",names);
    readFromFile("ratingList",rating);

    std::unordered_set<PlayerProfile> us;
    std::unordered_set<PlayerProfile>::iterator usit;
    std::pair<std::unordered_set<PlayerProfile>::iterator,bool> par;

    us.reserve(170);
    std::cout << "Load = " << us.load_factor() << "\n";
    for(auto i{0}; i < names.size(); i++){
        player.key = names.at(i);
        player.rating = rating.at(i); //Needs the same size as names vector. Else it causes a crash.
        par = us.insert(player);
    }


    std::cout << "Load = " << us.load_factor() << "\n";
    player.key = "Lyndia_Hedges";
    usit = us.find(player);
    player = *usit;
    std::cout << "Searching for Lydia_Hedges: "<< player.key << " - Rating: " << player.rating << "\n";
    player.key = "Alyson_Pollack";
    usit = us.find(player);
    player = *usit;
    std::cout << "Searching for Alyson_Pollack: "<< player.key << " - Rating: " << player.rating << "\n";
    std::cout << "Unordered_set size: " <<us.size() << "\n";
    std::cout << "Names vector size: " << names.size() << "\n";
    std::cout << "Load = " << us.load_factor() << "\n";

    return 0;
}
