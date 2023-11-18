#include <gtest/gtest.h>
#include "../CommandArgumentService.h"
#include "../CommandArgumentService.cpp"

TEST(CmdArgumentService, constructor) {
    char *args[] = {"filepath", "-i", "10", "-f", "file"};
    CommandArgumentService arg(5, args);
    EXPECT_EQ(arg.getArgument("-i"), "10");
    EXPECT_EQ(arg.getArgument("-f"), "file");
}

TEST(CmdArgumentService, error) {
    char *args[] = {"filepath", "-t", "10", "-f", "file"};
    EXPECT_ANY_THROW(CommandArgumentService arg(5, args));
}

TEST(CmdArgumentService, parse) {
    string cmd = "tick 100";
    vector<string> res = {"tick", "100"};
    EXPECT_EQ(res, CommandArgumentService::parseCommand(cmd));
}