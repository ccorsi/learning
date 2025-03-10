/**
 * @file lexicographic_sorting.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=LexicographicSorting
 * @version 0.2
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "lexicographic_sorting.h"

#include <list>
#include <iostream>

namespace valhalla {

namespace trie {

namespace lexicographic_sorting {

/*

Given a set of strings, return them in lexicographic order (dictionary/alphabetical order).

Input: [code, coder, coding, coded, codex, codify, codependents, codes, codesign, codeveloper]
Output: [code, coded, codependents, coder, codes, codesign, codeveloper, codex, codify, coding]

*/

std::vector<std::string> attempt_five(std::unordered_set<std::string> const & words) {
    std::vector<std::string> results;

    struct trie {
        struct trie_entry {
            std::string m_key;
            bool m_end;
            std::list<trie_entry> m_children;

            trie_entry() = default;
            trie_entry(std::string key, bool end = false) :
                m_key(key), m_end(end) {}
            trie_entry(std::string key, bool end, std::list<trie_entry> & children) :
                m_key(key), m_end(end), m_children(children) {}

            trie_entry const & add(std::string key) {
                // Determine if this is the head trie_entry and this is the first key being added
                if (m_key.empty() && m_children.empty()) {
                    m_key = key;
                    m_end = true;
                    return *this;
                } // if (m_key.empty() && m_children.empty())

                // determine if the current entry key matches with the passed key
                if (m_key == key) {
                    // they are the same
                    m_end = true;
                    return *this;
                } // if (m_key == key)

                std::string::size_type idx = 0;

                // Determine the length of the number of similar prefixing characters between the two keys
                while (idx < m_key.size() && idx < key.size() && m_key[idx] == key[idx]) {
                    idx++;
                } // while (idx < m_key.size() && idx < key.size() && m_key[idx] == key[idx])

                if (idx == m_key.size()) {
                    // the passed key contains more characters than the current key...
                    // ...determine which of the children the remaining key should be passed on too
                    key = key.substr(idx);

                    if (m_children.empty()) {
                        // This is the first children entry for this trie entry.
                        m_children.push_back(trie_entry(key,true));
                        return m_children.back();
                    } // if (m_children.empty())

                    std::list<trie_entry>::iterator itr = m_children.begin();

                    if ((*itr).m_key.empty()) {
                        // There shouldn't be more than this trie_entry entry for this key....
                        return (*itr).add(key);
                    } // if ((*itr).m_key.empty())

                    while (itr != m_children.end() && (*itr).m_key[0] < key[0]) {
                        itr++;
                    } // while (itr != m_children.end() && (*itr).m_key[0] < key[0])

                    if (itr == m_children.end()) {
                        m_children.push_back(trie_entry(key,true));
                        return m_children.back();
                    } // if (itr == m_children.end())

                    return (*itr).add(key);
                } // if (idx == m_key.size())

                if (idx == 0) {
                    // the two key are completely different thus we need to move the current children into their own
                    // trie entry.
                    trie_entry entry(m_key.substr(idx), m_end, m_children);
                    m_key = "";
                    m_children.clear();
                    m_end = false;
                    m_children.push_back(entry);
                    if (entry.m_key < key) {
                        m_children.push_back(trie_entry(key,true));
                        return m_children.back();
                    } // if (entry.m_key < key)

                    m_children.push_front(trie_entry(key,true));
                    return m_children.front();
                } // if (idx == 0)

                // a subset of the m_key is similar to the passed key...
                // ...how are they connected

                trie_entry entry(m_key.substr(idx), m_end, m_children);
                m_key.resize(idx);
                m_end = false;
                m_children.clear();
                m_children.push_back(entry);

                if (key.size() == idx) {
                    // the passed key is a prefix of the m_key
                    m_end = true;
                    return *this;
                } // if (key.size() == idx)

                key = key.substr(idx);

                if (entry.m_key < key) {
                    m_children.push_back(trie_entry(key,true));
                    return m_children.back();
                } // if (m_key < key)

                m_children.push_front(trie_entry(key,true));
                return m_children.front();
            }
        };

        trie_entry head;

        trie_entry const & add(std::string key) {
            return head.add(key);
        }
    };

    trie root;

    for (auto & word : words) {
        auto & entry = root.add(word);
    }

    return results;
} // attempt_five

std::vector<std::string> attempt_four(std::unordered_set<std::string> const & words) {
    std::vector<std::string> results;

    struct trie_entry {
        std::string m_key;
        std::list<trie_entry> m_children;
        bool m_end;

        trie_entry() : m_end(false) {}
        trie_entry(std::string key, bool end = false) : m_key(key), m_end(end) {}
        trie_entry(std::string key, bool end, std::list<trie_entry> & children) :
            m_key(key), m_end(end), m_children(children) {}

        trie_entry const & add(std::string key) {
            if (m_key.empty() && m_children.empty()) {
                m_key = key;
                m_end = true;
                std::cout << __LINE__ << '\n';
                return *this;
            } // if (m_key.empty())

            if (m_children.size() == 1 && m_children.front().m_key == "") {
                std::cout << __LINE__ << '\n';
                return m_children.front().add(key);
            } // if (m_children.size() == 1 && m_children.front().m_key == "")

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
                        std::cout << __LINE__ << '\n';
                        return m_children.back();
                    } // if (m_children.empty())

                    // find trie entry to add the current key
                    std::list<trie_entry>::iterator itr = m_children.begin();
                    while (itr != m_children.end() && (*itr).m_key[0] < key[0]) {
                        itr++;
                    } // while (itr != m_children.end() && (*itr).m_key < key)

                    if (itr == m_children.end()) {
                        m_children.push_back(trie_entry(key,true));
                        std::cout << __LINE__ << '\n';
                        return m_children.back();
                    } // if (itr == m_children.end())

                    if ((*itr).m_key[0] == key[0]) {
                        // the current trie entry key have some characters in common
                        std::cout << __LINE__ << '\n';
                        return (*itr).add(key);
                    } // if ((*itr).m_key[0] == key[0])

                    // create a new entry for the remaining key characters
                    trie_entry entry(key, true);

                    // insert it before the current trie entry
                    // return the newly inserted trie entry
                    std::cout << __LINE__ << '\n';
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

                    std::cout << __LINE__ << '\n';
                    return m_children.back();
                } // if (entry.m_key[0] != key[0])

                // the remaining key string has common prefixed characters with the split trie entry
                std::cout << __LINE__ << '\n';
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

                std::cout << __LINE__ << '\n';
                return *this;
            } // if (idx == key.size())

            // this key doesn't complete the words
            m_end = false;
            // add the last characters from idx of the passed key
            m_children.push_front(trie_entry(key.substr(idx), true));

            std::cout << __LINE__ << '\n';
            return m_children.front();
        }

        std::vector<std::string> & populate(std::vector<std::string> & results, std::string prefix = "") {
            prefix += m_key;
            if (m_end) {
                results.push_back(prefix);
            } // if (m_end)

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
        std::cout << "Adding key: " << key << '\n';
        trie_entry const & entry = head.add(key);
        // std::cout << "m_key: " << entry.m_key << ", m_end: " << entry.m_end << ", children size: " << entry.m_children.size() << '\n';
        head.print();
    } // for (std::string const & entry : words)

    // head.print();
    results = head.populate(results);

    return results;
} // attempt_four

std::vector<std::string> attempt_three(std::unordered_set<std::string> const & words) {
    std::vector<std::string> results;

    struct trie_entry {
        std::string m_key;
        std::list<trie_entry> m_children;
        bool m_end;

        trie_entry() : m_end(false) {}
        trie_entry(std::string key, bool end = false) : m_key(key), m_end(end) {}
        trie_entry(std::string key, bool end, std::list<trie_entry> & children) :
            m_key(key), m_end(end), m_children(children) {}

        trie_entry const & add(std::string key) {
            if (m_key.empty()) {
                if (m_children.empty()) {
                    m_key = key;
                    m_end = true;
                    return *this;
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
            } // if (m_key.empty())

            if (m_children.size() == 1 && m_children.front().m_key == "") {
                return m_children.front().add(key);
            } // if (m_children.size() == 1 && m_children.front().m_key == "")

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
            prefix += m_key;
            if (m_end) {
                results.push_back(prefix);
            } // if (m_end)

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

    // head.print();
    results = head.populate(results);

    return results;
}

std::vector<std::string> solution_two(std::unordered_set<std::string> const & words) {
    std::vector<std::string> results;

    if (words.empty()) {
        return results;
    } // if (words.empty())

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
            prefix += m_key;
            if (m_end) {
                results.push_back(prefix);
            } // if (m_end)

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

    return head.populate(results);
} // solution_two

std::vector<std::string> attempt_one(std::unordered_set<std::string> const & words) {
    std::vector<std::string> results;

    /**
     * @brief This implements the trie structure with the assumption that we are passed unique
     *  strings.  It doesn't assume that we are possibly being passed multiple instances of the
     *  same string.
     *
     */
    struct trie_entry {
        std::string m_key;
        std::list<trie_entry> m_children;
        trie_entry() = default;

        trie_entry(std::string key)
            : m_key(key) {}

        trie_entry(std::string key, std::list<trie_entry> & children)
            : m_key(key), m_children(children) {}

        trie_entry const & add(std::string key) {
            if (m_key.empty() && m_children.empty()) {
                m_key = key;
                return *this;
            } else if (m_children.empty()) {
                auto size = std::min(m_key.size(), key.size());
                auto idx = 0;
                while (idx < size && m_key[idx] == key[idx]) idx++;
                if (idx == size) {
                    if (m_key.size() == size) {
                        m_children.push_back(trie_entry(key.substr(size)));
                    } else {
                        m_children.push_back(trie_entry(m_key.substr(size)));
                        m_key.resize(size);
                    } // else of if (m_key.size() == size)
                } else {
                    m_children.push_back(trie_entry(m_key.substr(idx)));
                    m_children.push_back(trie_entry(key.substr(idx)));
                    m_key.resize(idx);
                } // else of if (idx == size)
                return m_children.back();
            } else {
                // find the string entry in the child that would best represent the passed key
                std::list<trie_entry>::iterator itr = m_children.begin();

                // NOTE: we assume that we are being passed unique strings, i.e., no duplicate entries
                while ( itr != m_children.end() && (*itr).m_key < key ) {
                    itr++;
                } // while ( itr != m_children.end() && (*itr).m_key < key )

                // determine if the current key needs to be add at the end
                if (itr == m_children.end()) {
                    m_children.push_back(trie_entry(key));
                    return m_children.back();
                } else {
                    // determine where the two keys are different
                    auto idx = 0;
                    for ( ; idx < m_key.size() && m_key[idx] == key[idx] ; idx++);

                    trie_entry & entry = *itr;

                    if (idx == m_key.size()) {
                        // the passed key is a prefix of m_key
                        return entry.add(key.substr(m_key.size()));
                    } else {
                        // we need to split this current trie_entry
                        trie_entry child(m_key.substr(idx), m_children);
                        // resize the current key to purge discrepency between keys
                        m_key.resize(idx);
                        // clear children since they are now part of the child trie_entry
                        m_children.clear();
                        // add the child trie_entry to the m_children list
                        m_children.push_back(child);
                        // add remaining key different to the m_children list
                        m_children.push_back(trie_entry(key.substr(idx)));
                        // return the currently added trie_entry
                        return m_children.back();
                    } // if (idx == m_key.size())
                } // if (itr == m_children.end())
            } // else of if (head.m_key.empty() && head.m_children.empty())
        } // trie_entry const & add(std::string & key)

        void populate(std::vector<std::string> & results, std::string & prefix) {
            if (m_children.empty()) {
                results.push_back(prefix + m_key);
            } else {
                for (auto & entry : m_children) {
                    entry.populate(results, prefix + m_key);
                } // for (auto & entry : m_children)
            } // if (m_children.empty())
        }
    };

    trie_entry head;

    for (auto key : words) {
        trie_entry const & entry = head.add(key);
        std::cout << "head key: " << entry.m_key << "\n";
    } // for (auto & entry : words)

    std::string empty;
    // add the ordered trie entries to the results vector
    head.populate(results, empty);

    return results;
} // attempt_one

std::vector<std::string> Solution::lexicographicSort(std::unordered_set<std::string> const & words) {
    return solution_two(words);
} // lexicographicSort

} // namespace lexicographic_sorting

} // namespace trie

} // namespace valhalla
