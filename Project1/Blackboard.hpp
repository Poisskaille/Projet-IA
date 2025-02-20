#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

using namespace std;
using namespace sf;

class Blackboard {
private:
    unordered_map<string, int> data;
public:
    void SetValue(const string& key, int value) {
        data[key] = value;
    }
    int GetValue(const string& key) {
        return data[key];
    }
};