#pragma once

#include "node.h"
#include <string>

class Score : public Node
{
public:
    void increment();
    void reset();

private:
    void update();
    void set_text(std::string);

private:
    int score;
};
