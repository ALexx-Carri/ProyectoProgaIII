cmake_minimum_required(VERSION 4.2)
project(new_proyect)

set(CMAKE_CXX_STANDARD 20)

add_executable(new_proyect main.cpp
        utils/DataCleaner.cpp
        utils/DataCleaner.h
        models/Movie.h
        utils/CSVReader.cpp
        utils/CSVReader.h
        utils/Tokenizar.cpp
        utils/Tokenizar.h
        structures/InvertedIndex.cpp
        structures/InvertedIndex.h
        structures/SuffixNode.cpp
        structures/SuffixNode.h
        structures/SuffixTrie.cpp
        structures/SuffixTrie.h
        systems/RankingSystem.cpp
        systems/RankingSystem.h
        systems/RecommendationSystem.cpp
        systems/RecommendationSystem.h
        systems/SearchEngine.cpp
        systems/SearchEngine.h
        models/Movie.cpp)
