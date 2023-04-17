#include <list>
#include <iostream>
#include <unordered_set>

// The numbers in a roulette which are colored red
static const std::unordered_set<int> reds{1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};

// The maximum bet allowed
static inline const int MAX_BET = 4000;

// A player which bets according to a list and keeps track of its earnings
class Player
{
  std::list<int> bets{1, 2, 3, 4};
  int earnings = 0;

  void reset_bets()
  {
    bets.clear();
    bets.push_back(1);
    bets.push_back(2);
    bets.push_back(3);
    bets.push_back(4);
  }

public:
  void lose()
  {
    int amount = bets.front() + bets.back();
    earnings -= amount;

    // Deletes the first and last element in list. If the list would become empty, reset to default value
    if (bets.size() <= 2)
      reset_bets();
    else
    {
      bets.pop_front();
      bets.pop_back();
    }
  }

  void win()
  {
    int amount = bets.front() + bets.back();
    earnings += amount;
    bets.push_back(amount);

    // If next bet would be invalid, reset list to default value
    if (bets.front() + bets.back() > MAX_BET)
      reset_bets();
  }

  int get_earnings()
  {
    return earnings;
  }
};

int main(int argc, char **argv)
{
  // We seed the RNG with the current time
  srand(time(NULL));

  // 0 bets red, 1 bets black, 2 bets high, 3 bets low, 4 bets even, 5 bets odd
  Player players[6];
  for (int i = 0; i < 10000; i++)
  {

    // The roulette comes up with a random number
    int number = rand() % 37;

    // If it's 0 everyone loses
    if (number == 0)
    {
      for (int j = 0; j < 6; j++)
        players[j].lose();
      continue; // We don't need to check evenness, color or high/low
    }

    // If it's red 0 wins and 1 loses, and viceversa
    if (reds.count(number))
    {
      players[0].win();
      players[1].lose();
    }
    else
    {
      players[1].win();
      players[0].lose();
    }

    // If it's high 2 wins and 3 loses, and viceversa
    if (number > 18)
    {
      players[2].win();
      players[3].lose();
    }
    else
    {
      players[3].win();
      players[2].lose();
    }

    // If it's even 4 wins and 5 loses, and viceversa
    if (number % 2 == 0)
    {
      players[4].win();
      players[5].lose();
    }
    else
    {
      players[5].win();
      players[4].lose();
    }
  }

  for (int i = 0; i < 6; i++)
    std::cout << "Player " << char('A' + i) << " total earnings: " << players[i].get_earnings() << std::endl;

  return 0;
}