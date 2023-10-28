#include <gtest/gtest.h>
#include "../commands/CommandFactory.h"
#include "../commands/CommandFabric.cpp"
#include "../commands/Command.h"
#include "../Life.h"
#include "../commands/TickCommand.h"

TEST(CommandFactory, Init) {
    CommandFactory factory;
    factory.add<TickCommand>("tick");
    Command *cmd = factory.get("tick");
}