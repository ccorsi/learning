/**
 * @file shortest_unique_prefix.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=ShortestUniquePrefix
 * @version 0.1
 * @date 2025-03-09
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "shortest_unique_prefix.h"

#include <iostream>
#include <list>

namespace valhalla {

namespace trie {

namespace shortest_unique_prefix {

/*

Given a list of words in lexicographic order where no word is the prefix of another, find the shortest unique prefix to identify each word in the array uniquely.

Input: ["AND", "BONFIRE", "BOOL", "CASE", "CATCH", "CHAR"]
Output: ["A", "BON", "BOO", "CAS", "CAT", "CH"]

Explanation:

"A" can uniquely identify "AND"
"BON" can uniquely identify "BONFIRE"
"BOO" can uniquely identify "BOOL"
"CAS" can uniquely identify "CASE"
"CAT" can uniquely identify "CATCH"
"CH" can uniquely identify "CHAR"

*/

std::vector<std::string> attempt_one(std::vector<std::string> const & words) {
    struct trie_entry {
        std::string m_key;
        std::list<trie_entry> m_children;
        bool m_end;

        trie_entry() = default;
        trie_entry(std::string key, bool end = false) : m_key(key), m_end(end) {}
        trie_entry(std::string key, bool end, std::list<trie_entry> & children) :
            m_key(key), m_end(end), m_children(children) {}

        trie_entry const & add(std::string key) {
            if (m_key.empty() && m_children.empty()) {
                m_key = key;
                m_end = true;
                return *this;
            } // if (m_key.empty() && m_children.empty())

            if (m_key == key) {
                m_end = true;
                return *this;
            } // if (m_key == key)

            std::string::size_type idx = 0;

            if (m_key < key) {
                // find the first character that is different
                while (idx < m_key.size() && m_key[idx] == key[idx]) {
                    idx++;
                } // while (idx < m_key.size() && m_key[idx] == key[idx])

                if (idx == m_key.size()) {
                    // the current key is a prefix of the passed key, get the remaining suffix
                    key = key.substr(idx);

                    // check if this is the first child of this entry
                    if (m_children.empty()) {
                        m_children.push_back(trie_entry(key,true));
                        return m_children.back();
                    } // if (m_children.empty())

                    // find trie entry to add the current key
                    std::list<trie_entry>::iterator itr = m_children.begin();
                    while (itr != m_children.end() && (*itr).m_key[0] < key[0]) {
                        itr++;
                    } // while (itr != m_children.end() && (*itr).m_key < key)

                    if (itr == m_children.end()) {
                        m_children.push_back(trie_entry(key,true));
                        return m_children.back();
                    } // if (itr == m_children.end())

                    if ((*itr).m_key[0] == key[0]) {
                        // the current trie entry key have some characters in common
                        return (*itr).add(key);
                    } // if ((*itr).m_key[0] == key[0])

                    // create a new entry for the remaining key characters
                    trie_entry entry(key, true);

                    // insert it before the current trie entry
                    // return the newly inserted trie entry
                    return *(m_children.insert(itr, entry));
                } // if (idx == m_key.size())

                // the first idx characters of the passed key is the same as the m_key, split this entry
                trie_entry entry(m_key.substr(idx), m_end, m_children);
                // purge the first idx characters from this entry key
                m_key.resize(idx);
                // remove all of the current entries for this trie entry
                m_children.clear();
                // add the newly created trie entry since it preceeds the passed key
                m_children.push_back(entry);
                // the key is not a complete words since there is still some left to process
                m_end = false;

                key = key.substr(idx);
                // determine the remaining key string contains any common characters
                if (entry.m_key[0] != key[0]) {
                    // add the remaining key characters to the trie entry collection
                    m_children.push_back(trie_entry(key, true));

                    return m_children.back();
                } // if (entry.m_key[0] != key[0])

                // the remaining key string has common prefixed characters with the split trie entry
                return entry.add(key);
            } // if (m_key < key)

            // find the first character that is different
            while (idx < key.size() && key[idx] == m_key[idx]) {
                idx++;
            } // while (idx < key.size() && key[idx] < m_key[idx])

            // the first idx characters of the m_key is the same as the passed key, split this entry
            trie_entry entry(m_key.substr(idx), m_end, m_children);
            // purge the first idx characters from this entry key
            m_key.resize(idx);
            // remove all of the current entries for this trie entry
            m_children.clear();
            // add the newly created trie entry since it preceeds the passed key
            m_children.push_back(entry);

            if (idx == key.size()) {
                // this key completes the words
                m_end = true;

                return *this;
            } // if (idx == key.size())

            // this key doesn't complete the words
            m_end = false;
            // add the last characters from idx of the passed key
            m_children.push_front(trie_entry(key.substr(idx), true));

            return m_children.front();
        }

        std::vector<std::string> & populate(std::vector<std::string> & results, std::string prefix = "") {
            if (m_children.empty()) {
                prefix += m_key[0];
                results.push_back(prefix);
                return results;
            } // if (m_children.empty())

            prefix += m_key;

            for (trie_entry & entry : m_children) {
                entry.populate(results, prefix);
            } // for (trie_entry & entry : m_children)

            return results;
        }

        void print(std::string prefix = "") {
            std::cout << prefix << "trie_entry [\n";
            std::cout << prefix << "\tkey: " << m_key << "\n";
            std::cout << prefix << "\tend: " << m_end << "\n";
            for (auto & child : m_children)
                child.print(prefix + '\t');
            std::cout << prefix << "]\n";
        }
    };

    trie_entry head;

    for (std::string key : words) {
        // std::cout << "Adding key: " << key << '\n';
        trie_entry const & entry = head.add(key);
        // std::cout << "m_key: " << entry.m_key << ", m_end: " << entry.m_end << ", children size: " << entry.m_children.size() << '\n';
        // head.print();
    } // for (std::string const & entry : words)

    std::vector<std::string> results;

    if (words.empty())
        return results;

    return head.populate(results);
} // attempt_one

std::vector<std::string> Solution::findShortestUniquePrefix(std::vector<std::string> const & words) {
    return attempt_one(words);
} // findShortestUniquePrefix

} // namespace shortest_unique_prefix

} // namespace trie

} // namespace valhalla
