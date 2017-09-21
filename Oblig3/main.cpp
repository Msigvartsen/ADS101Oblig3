#include <iostream>
#include <hash_map>
#include <unordered_set>
#include "playerprofile.cpp"


namespace std {
    template<>
    class hash<PlayerProfile>
    {
    public:
        size_t operator() (const PlayerProfile& profile) const
        {
            return profile.key % 11;
        }
        bool operator() (const PlayerProfile& profile1, const PlayerProfile& profile2)
        {
            return profile1.key == profile2.key;
        }
    };
}


int main()
{
    std::unordered_set<PlayerProfile> us;
    std::unordered_set<PlayerProfile>::iterator usit;
    std::pair<std::unordered_set<PlayerProfile>::iterator,bool> par;
    PlayerProfile magnus;
    magnus.key = 2115;
    magnus.nick = "Akson";
    magnus.email = "magnus_sigvartsen@hotmail.com";
    magnus.rating = 4310;
    us.reserve(10);
    us.insert(magnus);
    magnus.key = 11;


    par = us.insert(magnus);
    usit = us.find(magnus);
    magnus = *usit;
    std::cout << magnus.key << magnus.nick << magnus.email << magnus.rating ;
    //par = us.insert(magnus);

    return 0;
}
