/*
* Created by Gustavo Viegas (2016/09)
*/

#ifndef DEFINITIONS_HXX
#define DEFINITIONS_HXX

#include <string>

enum class ObjectType { Tile = 0, Player, Enemy, Trap, Door, Key };

//enum class Condition { None = 0, Jumping, Dead };

// todo: remove this ns ffs
namespace GameInput {
static std::string Left = "Left";
static std::string Right = "Right";
static std::string Jump = "Jump";
};

#endif