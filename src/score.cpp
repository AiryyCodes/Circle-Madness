#include "score.h"
#include "components/font_renderer.h"
#include <string>

void Score::increment()
{
    score++;
    update();
}

void Score::reset()
{
    score = 0;
    update();
}

void Score::update()
{
    std::string text = "Score: " + std::to_string(score);
    set_text(text);
}

void Score::set_text(std::string text)
{
    get_component<FontRenderer>()->set_text(text);
}
