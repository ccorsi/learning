/**
 * @file wildcard_pattern_matching_two.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is solution to the problem https://www.techiedelight.com/?problem=WildcardPatternMatchingII
 * @version 0.1
 * @date 2025-02-04
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "wildcard_pattern_matching_two.h"
#include <vector>

namespace valhalla {

namespace dynamic_programming {

namespace wildcard_pattern_matching_two {

/*

Given a word and a pattern containing wildcard characters '*' and '?', check if the
pattern matches with the complete string or not. Here, '?' can match to any single
character in the string and '*' can match to any number of characters including zero
characters.

Input: word = "xyxzzxy", pattern = "x***y"
Output: true

Input: word = "xyxzzxy", pattern = "x***x"
Output: false

Input: word = "xyxzzxy", pattern = "x***x?"
Output: true

Input: word = "xyxzzxy", pattern = "*"
Output: true

*/

// This enumeration is used to determine what type of information we are going to be using
// when comparing the current section of the word with the next concrete string extracted
// from the passed pattern.
enum Type {
    NONE, ANY, OPTIONAL
};

/*
    NOTE: I could of just use a std::pair<std::size_t,std::size_t> instance but then it is
    possible that I can incorrectly set the positions when using th first and second fields.
*/
struct state {
    std::size_t ppos, wpos;
    state() : ppos(0), wpos(0) {}
    state(std::size_t cppos, std::size_t cwpos) : ppos(cppos), wpos(cwpos) {}
};

bool attempt_four(std::string word, std::string pattern) {
    if (word.empty() && pattern.empty() == false && pattern.find_first_not_of("*") != pattern.npos) {
        return false;
    }

    if(word == pattern || pattern.find_first_not_of("*") == pattern.npos) {
        return true;
    }

    // holds the current state of the pattern check against the word
    std::vector<state> states;

    // add a single state to the states to get started
    states.push_back(state());

    const std::size_t wend = word.size(), pend = pattern.size();

    // while we have states we continue to check for confirmation of pattern/word combination
    while ( ! states.empty() ) {
        // Get the next state
        state current = states.front();
        // Remove the next state from the vector
        states.pop_back();

        // set the positions for the pattern and word
        std::size_t ppos = current.ppos, wpos = current.wpos;
        char option = ' ';

        // find the next pattern to check
        while (ppos < pend && (pattern[ppos] == '*' || pattern[ppos] == '?')) {
            if (pattern[ppos] == '*') {
                option = '*';
            } else {
                wpos++;
            }
            ppos++;
        } // while (ppos < pend && (pattern[ppos] == '*' || pattern[ppos] == '?'))

        if (wpos > wend) {
            // this word/pattern is not valid
            continue;
        } else if (wpos == wend && ppos == pend) {
            return true;
        }

        std::string concrete;

        // find the next concrete characters
        while (ppos < pend && pattern[ppos] != '*' && pattern[ppos] != '?') {
            concrete += pattern[ppos++];
        } // while (ppos < pend && pattern[ppos] != '*' && pattern[ppos] != '?')

        // make initial checks
        if (concrete.empty()) {
            if (option == '*') {
                return true;
            }
            // this is not a valid option
            continue;
        } else if (option == ' ') {
            std::size_t idx = 0;
            while (idx < concrete.size() && concrete[idx] == word[wpos + idx]) {
                idx++;
            } // while (idx < concrete.size() && concrete[idx] == word[wpos + idx])

            if (idx != concrete.size()) {
                // pattern doesn't match word
                continue;
            } // if (idx != concrete.size())

            // push current state onto the queue and continue
            states.push_back(state(ppos,wpos + concrete.size()));
            continue;
        } // if (concrete.empty())

        std::size_t next = wpos;

        // find the first character of the pattern
        while (next < wend) {
            if (word[next] == concrete[0]) {
                if (concrete.size() + next > wend) {
                    // this is not a valid pattern check. break out of the while loop
                    break;
                } // if (concrete.size() + next > wend)

                // determine if the concrete is found in word at position next
                std::size_t idx = 1;
                while (idx < concrete.size() && concrete[idx] == word[next + idx]) {
                    idx++;
                } // while (idx < concrete.size() && concrete[idx] == word[next + idx])

                if (idx == concrete.size()) {
                    // this is valid pattern check
                    break;
                } // if (idx == concrete.size())
            } // if (word[next] == concrete[0])
            next++;
        } // while (next < wend)

        // determine if the concrete string is part of the word
        if (next >= wend || concrete.size() + next > wend) {
            // this current check doesn't match
            continue;
        }

        // we've found the concrete pattern in word, check if it is in a valid position

        if (option == '*') {
            // find all other concrete within the word and add to the states vector.
            std::size_t wnext = next + 1;
            while (wnext + concrete.size() <= wend) {
                if (word[wnext] == concrete[0]) {
                    std::size_t idx = 1;
                    while (idx < concrete.size() && word[wnext + idx] == concrete[idx]) {
                        idx++;
                    }
                    // found another matching concrete string
                    if (idx == concrete.size()) {
                        // add to states to check other possibilities
                        states.push_back(state(ppos,wnext + concrete.size()));
                    }
                }
                wnext++;
            }
        } else if (next != wpos) {
            // the pattern found was not within the appropiate section of the word
            continue;
        } // if (option == '*')

        // update the wpos using next value
        wpos = next + concrete.size();

        // append the current state information to the end of the vector...or should this be the beginning?
        states.push_back(state(ppos, wpos));

    } // while ( ! states.empty() )

    return false;
}

bool attempt_three(std::string word, std::string pattern) {
    if (word.empty() && pattern.empty() == false && pattern.find_first_not_of("*") != pattern.npos) {
        return false;
    }

    if(word == pattern) {
        return true;
    }

    // holds the current state of the pattern check against the word
    std::vector<state> states;

    // add a single state to the states to get started
    states.push_back(state());

    const std::size_t wend = word.size(), pend = pattern.size();

    // while we have states we continue to check for confirmation of pattern/word combination
    while ( ! states.empty() ) {
        // Get the next state
        state current = states.front();
        // Remove the next state from the vector
        states.pop_back();

        // set the positions for the pattern and word
        std::size_t ppos = current.ppos, wpos = current.wpos;
        std::size_t optional = 0;
        char option = ' ';

        // find the next pattern to check
        while (ppos < pend && (pattern[ppos] == '*' || pattern[ppos] == '?')) {
            if (pattern[ppos] == '*') {
                option = '*';
            } else {
                optional++;
                option = (option != '*') ? '?' : option;
            }
            ppos++;
        } // while (ppos < pend && (pattern[ppos] == '*' || pattern[ppos] == '?'))

        std::string concrete;

        // find the next concrete characters
        while (ppos < pend && pattern[ppos] != '*' && pattern[ppos] != '?') {
            concrete += pattern[ppos++];
        } // while (ppos < pend && pattern[ppos] != '*' && pattern[ppos] != '?')

        // make initial checks
        if (concrete.empty()) {
            if (option == '*' || (optional + wpos) >= wend) {
                return true;
            }
            // this is not a valid option
            continue;
        } else if (option == ' ') {
            std::size_t idx = 0;
            while (idx < concrete.size() && concrete[idx] == word[wpos + idx]) {
                idx++;
            } // while (idx < concrete.size() && concrete[idx] == word[wpos + idx])

            if (idx != concrete.size()) {
                // pattern doesn't match word
                continue;
            } // if (idx != concrete.size())

            // push current state onto the queue and continue
            states.push_back(state(ppos,wpos + concrete.size()));
            continue;
        } // if (concrete.empty())

        std::size_t next = wpos + optional;

        // find the first character of the pattern
        while (next < wend) {
            if (word[next] == concrete[0]) {
                if (concrete.size() + next > wend) {
                    // this is not a valid pattern check. break out of the while loop
                    break;
                } // if (concrete.size() + next > wend)

                // determine if the concrete is found in word at position next
                std::size_t idx = 1;
                while (idx < concrete.size() && concrete[idx] == word[next + idx]) {
                    idx++;
                } // while (idx < concrete.size() && concrete[idx] == word[next + idx])

                if (idx == concrete.size()) {
                    // this is valid pattern check
                    break;
                } // if (idx == concrete.size())
            } // if (word[next] == concrete[0])
            next++;
        } // while (next < wend)

        // determine if the concrete string is part of the word
        if (next >= wend || concrete.size() + next > wend) {
            // this current check doesn't match
            continue;
        }

        // we've found the concrete pattern in word, check if it is in a valid position

        if (option == '*') {
            // find all other concrete within the word and add to the states vector.
            std::size_t wnext = next + 1;
            while (wnext + concrete.size() <= wend) {
                if (word[wnext] == concrete[0]) {
                    std::size_t idx = 1;
                    while (idx < concrete.size() && word[wnext + idx] == concrete[idx]) {
                        idx++;
                    }
                    // found another matching concrete string
                    if (idx == concrete.size()) {
                        // add to states to check other possibilities
                        states.push_back(state(ppos,wnext + concrete.size()));
                    }
                }
                wnext++;
            }
        } else if (next != wpos) {
            // the pattern found was not within the appropiate section of the word
            continue;
        } // if (option == '*')

        // update the wpos using next value
        wpos = next + concrete.size();

        // append the current state information to the end of the vector...or should this be the beginning?
        states.push_back(state(ppos, wpos));

    } // while ( ! states.empty() )

    return false;
}

// This implemented an incorrect implementation of the '?' character since I had assumed that '?' was similar
// to the regular expression '?' and not to this problem version of '?' which is completely different. :(.
bool attempt_two(std::string word, std::string pattern) {
    // holds the current state of the pattern check against the word
    std::vector<state> states;

    // add a single state to the states to get started
    states.push_back(state());

    const std::size_t wend = word.size(), pend = pattern.size();

    // while we have states we continue to check for confirmation of pattern/word combination
    while ( ! states.empty() ) {
        // Get the next state
        state current = states.front();
        // Remove the next state from the vector
        states.pop_back();

        // set the positions for the pattern and word
        std::size_t ppos = current.ppos, wpos = current.wpos;

        std::size_t optional = 0;
        char option = ' ';

        // find the next pattern to check
        while (ppos < pend && (pattern[ppos] == '*' || pattern[ppos] == '?')) {
            if (pattern[ppos] == '*') {
                optional = 0;
                option = '*';
            } else if (option != '*') {
                optional++;
                option = '?';
            }
            ppos++;
        } // while (ppos < pend && (pattern[ppos] == '*' || pattern[ppos] == '?'))

        std::string concrete;

        // find the next concrete characters
        while (ppos < pend && pattern[ppos] != '*' && pattern[ppos] != '?') {
            concrete += pattern[ppos++];
        } // while (ppos < pend && pattern[ppos] != '*' && pattern[ppos] != '?')

        // make initial checks
        if (concrete.empty()) {
            if (option == '*' || (optional + wpos) >= wend) {
                return true;
            }
            // this is not a valid option
            continue;
        } else if (option == ' ') {
            std::size_t idx = 0;
            while (idx < concrete.size() && concrete[idx] == word[wpos + idx]) {
                idx++;
            } // while (idx < concrete.size() && concrete[idx] == word[wpos + idx])

            if (idx != concrete.size()) {
                // pattern doesn't match word
                continue;
            } // if (idx != concrete.size())

            // push current state onto the queue and continue
            states.push_back(state(ppos,wpos + concrete.size()));
            continue;
        } // if (concrete.empty())

        std::size_t next = wpos;

        // find the first character of the pattern
        while (next < wend) {
            if (word[next] == concrete[0]) {
                if (concrete.size() + next > wend) {
                    // this is not a valid pattern check. break out of the while loop
                    break;
                } // if (concrete.size() + next > wend)

                // determine if the concrete is found in word at position next
                std::size_t idx = 1;
                while (idx < concrete.size() && concrete[idx] == word[next + idx]) {
                    idx++;
                } // while (idx < concrete.size() && concrete[idx] == word[next + idx])

                if (idx == concrete.size()) {
                    // this is valid pattern check
                    break;
                } // if (idx == concrete.size())
            } // if (word[next] == concrete[0])
            next++;
        } // while (next < wend)

        // determine if the concrete string is part of the word
        if (next == wend || concrete.size() + next > wend) {
            // this current check doesn't match
            continue;
        }

        // we've found the concrete pattern in word, check if it is in a valid position

        if (option == '*') {
            // find all other concrete within the word and add to the states vector.
            std::size_t wnext = next + 1;
            while (wnext + concrete.size() <= wend) {
                if (word[wnext] == concrete[0]) {
                    std::size_t idx = 1;
                    while (idx < concrete.size() && word[wnext + idx] == concrete[idx]) {
                        idx++;
                    }
                    // found another matching concrete string
                    if (idx == concrete.size()) {
                        // add to states to check other possibilities
                        states.push_back(state(ppos,wnext + concrete.size()));
                    }
                }
                wnext++;
            }
        } else if (option == '?') {
            // find all other concrete within the word and add to the states vector.
            std::size_t wnext = next + 1;
            for(std::size_t optidx = 0 ; optidx < optional && optidx + wnext + concrete.size() < wend ; optidx++) {
                if (word[wnext] == concrete[0]) {
                    std::size_t idx = 1;
                    while (idx < concrete.size() && word[wnext + idx] == concrete[idx]) {
                        idx++;
                    }
                    // found another matching concrete string
                    if (idx == concrete.size()) {
                        // add to states to check other possibilities
                        states.push_back(state(ppos,wnext + concrete.size()));
                    }
                } // if (word[wnext] == concrete[0])
                wnext++;
            } // for(std::size_t optidx = 0 ; optidx < optional && optidx + wnext + concrete.size() < wend ; optidx++)
        } else if (next != wpos) {
            // the pattern found was not within the appropiate section of the word
            continue;
        } // if (option == '*')

        // update the wpos using next value
        wpos = next + concrete.size();

        // append the current state information to the end of the vector...or should this be the beginning?
        states.push_back(state(ppos, wpos));

    } // while ( ! states.empty() )

    return false;
}

bool attempt_one(std::string word, std::string pattern) {
    /*
        The idea is simple, go through the pattern string and look
        for the next pattern that doesn't include the '*' and '?'
        characters.  All '*' and '?' prior patterns will determine
        the type of actions that needs to be applied to the passed
        word.  Note that anytime that '*' is found all '?' option
        will be embedded within the '*'.  While multiple '?' will
        be incremented and used when a string is expected within
        the passed word.

        As part of the above, we keep track of where we are in
        the word and pattern check.  This information will be
        used to determine if we have found a match or not.
     */
    bool matched = true;
    std::size_t wpos = 0, ppos = 0;
    const std::size_t wend = word.size(), pend = pattern.size();

    while ( true ) {
        std::size_t optional = 0;
        Type type = NONE;
        std::string concrete;

        // find next concrete pattern
        for ( ; ppos < pend ; ppos++ ) {
            char chr = pattern[ppos];
            if (chr == '*') {
                // Check if we've already found a concrete string
                if ( ! concrete.empty() ) {
                    // decrement position and break out of the loop
                    ppos--;
                    break;
                }
                type = ANY;
                optional = 0;
            } else if (chr == '?') {
                // Check if we've already found a concrete string
                if ( ! concrete.empty() ) {
                    // decrement position and break out of the loop
                    ppos--;
                    break;
                }
                if (type == OPTIONAL) {
                    optional++;
                } else {
                    type = OPTIONAL;
                }
            } else {
                // append character to concrete string
                concrete += chr;
            }
        } // for ( ; ppos < pend ; ppos++ )

        if (concrete.empty()) {
            // This means that we are at the end of the pattern and just check
            // the current position of the word with the type of check.
            if (type == ANY) {
                // we have found a match
                return true;
            } else if (type == OPTIONAL) {
                // check that we have enough optional characters to cover remaining unchecked word section
                return (wend - wpos) <= optional;
            } else {
                // check that we've reach the end of the word
                return wpos == wend;
            }
        } else {
            // This means that we need to determine is the current concrete string can be found within the
            // current word position.
            if (type == NONE) {
                if (wpos + concrete.size() >= wend) {
                    // The remaining characters in the word doesn't include the remaining pattern
                    return false;
                }

                // compare the concrete characters against the current position in the word
                for (auto idx = 0 ; idx < concrete.size() ; idx++) {
                    if (word[wpos] != concrete[idx]) {
                        // we haven't found the required pattern in the string
                        return false;
                    }
                    // increment word position.
                    wpos++;
                }

                // the concrete pattern was found within the current position in the word.

                if (wpos == wend) {
                    // determine if the remaining pattern doesn't contain '*' and '?'
                    while ( ppos < pend) {
                        if (pattern[ppos] != '*' && pattern[ppos++] != '?') {
                            // the remaining pattern contains non '*' and '?' characters
                            return false;
                        }
                    }
                    // the remaining pattern is compatible with the word
                    return true;
                } else if (ppos == pend) {
                    // the pattern doesn't match the passed word
                    return false;
                } // if (wpos == wend)
            } else {
                if (type == ANY) {
                    while (true) {
                        // find the first section of the word that contains the current pattern
                        while (wpos < wend && word[wpos] != concrete[0]) wpos++;

                        if (wpos == wend || wpos + concrete.size() >= wend) {
                            // the remaining word check doesn't contain the concrete string
                            return false;
                        }

                        // check that the concrete string is part of the
                        std::size_t idx = 1;
                        while ( idx < concrete.size() && word[wpos + idx] == concrete[idx]) idx++;

                        if (idx == concrete.size()) {
                            // the pattern was found continue to the next set of pattern check
                            break;
                        }
                    } // while (true)
                    continue;
                } // if (type == ANY)

                // determine where the concrete pattern is located within the current word position
                while (true) {
                    // find the first section of the word that contains the current pattern
                    while (wpos < wend && word[wpos] != concrete[0] && optional > 0) {
                        wpos++;
                        optional--;
                    }

                    if (wpos == wend || wpos + concrete.size() >= wend || (optional == 0 && word[wpos] != concrete[0])) {
                        // the remaining word check doesn't contain the concrete string
                        return false;
                    }

                    // check that the concrete string is part of the
                    std::size_t idx = 1;
                    while ( idx < concrete.size() && word[wpos + idx] == concrete[idx]) idx++;

                    if (idx == concrete.size()) {
                        // the pattern was found continue to the next set of pattern check
                        break;
                    }
                } // while (true)
            } // if (type == NONE)
        } // if (concrete.empty())
    }

    return matched;
}

bool Solution::isMatch(std::string word, std::string pattern) {
    return attempt_four(word, pattern);
} // isMatch

} // namespace wildcard_pattern_matching_two

} // namespace dynamic_programming

} // namespace valhalla
