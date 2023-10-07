#include <vector>
#include <clocale>
#include "FileReader.h"
#include "FileWriter.h"
#include "Parser.h"
#include "Statistics.h"
using namespace std;

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "RUS");
    if (argc != 3) {
        return 0;
    }
    string nameFrom = string(argv[1]);
    string nameTo = string(argv[2]);
    size_t totalAmount = 0;
    Statistics stat;
    FileReader reader(nameFrom);
    reader.open();
    while (reader.hasNext()) {
        string line = reader.next();
        auto words = Parser::split(line);
        totalAmount += words.size();
        for (const auto& word : words) {
            stat.add(word);
        }
    }
    reader.close();
    auto sorted = stat.getSortedData();
    FileWriter writer(nameTo);
    writer.open();
    for (auto &item : sorted) {
        long double frequency = (long double) item.second / totalAmount;
        vector<string> data;
        data.emplace_back(item.first);
        data.emplace_back(to_string(frequency));
        writer.writeLine(data);
    }
    writer.close();
}