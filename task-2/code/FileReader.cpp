#include "FileReader.h"

list<pair<int, int>> FileReader::readCoords() const {
    reOpen();
    file->seekg(coordPos);
    list<pair<int, int>> res;
    while (!this->file->eof()) {
        int x, y;
        *this->file >> x;
        *this->file >> y;
        res.emplace_back(x, y);
    }
    reOpen();
    file->seekg(coordPos);
    return res;
}

pair<list<int>, list<int>> FileReader::getBirthSurviveRules() const {
    if (rulesPos != -1) {
        file->seekg(rulesPos);
    } else {
        throw runtime_error("file hasn't transition rules");
    }
    string line;
    getline(*this->file, line);
    rtrim(line);
    line = line.substr(3);
    if (!line.contains('B') || !line.contains("/S")) {
        throw runtime_error("format error");
    }
    list<int> liveRules;
    list<int> dieRules;
    string liveRulesStr = line.substr(1, line.find('/') - 1);
    string dieRulesStr = line.substr(line.find('/') + 2);
    for (const auto &item : liveRulesStr) {
        liveRules.push_back(item - '0');
    }
    for (const auto &item : dieRulesStr) {
        dieRules.push_back(item - '0');
    }
    return {liveRules, dieRules};
}

string FileReader::getUniverseName() const {
    if (namePos != -1) {
        file->seekg(namePos);
    } else {
        throw runtime_error("file hasn't universe name");
    }
    string line;
    getline(*file, line);
    rtrim(line);
    return line.substr(3);
}

void FileReader::setSeeks() {
    string line;
    auto oldSeek = file->tellg();
    getline(*this->file, line);
    rtrim(line);
    if (line.starts_with("#N ")) {
        namePos = oldSeek;
    } else if (line.starts_with("#R ")) {
        rulesPos = oldSeek;
        namePos = -1;
    } else {
        coordPos = oldSeek;
        rulesPos = -1;
        namePos = -1;
    }
    if (namePos != -1) {
        oldSeek = file->tellg();
        getline(*file, line);
        rtrim(line);
        if (line.starts_with("#R ")) {
            rulesPos = oldSeek;
            coordPos = file->tellg();
        } else {
            rulesPos = -1;
            coordPos = oldSeek;
        }
    }
    if (file->eof()) {
        reOpen();
    }
}
