/**
 * @file tokenizer.cpp
 */

#include <fstream>
#include <iostream>
#include "util/invertible_map.h"
#include "tokenizers/parse_tree.h"
#include "tokenizers/tokenizer.h"

namespace meta {
namespace tokenizers {

using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::unordered_map;

using util::InvertibleMap;
using index::TermID;
using index::Document;

tokenizer::tokenizer():
    _term_map(InvertibleMap<TermID, string>()),
    _current_term_id(0)
{ /* nothing */ }

TermID tokenizer::mapping(const string & term)
{
    if(!_term_map.containsValue(term))
    {
        _term_map.insert(_current_term_id, term);
        return _current_term_id++;
    }
    else
    {
        TermID termID = _term_map.getKeyByValue(term);
        return termID;
    }
}

void tokenizer::set_term_id_mapping(const InvertibleMap<TermID, string> & mapping)
{
    _term_map = mapping;
    _current_term_id = _term_map.size();
}

void tokenizer::save_term_id_mapping(const string & filename) const
{
    _term_map.saveMap(filename);
}

const InvertibleMap<TermID, std::string> & tokenizer::term_id_mapping() const
{
    return _term_map;
}

string tokenizer::label(TermID termID) const
{
    return _term_map.getValueByKey(termID);
}

void tokenizer::print_data() const
{
    for(auto & term: _term_map)
        cout << term.first << "\t" << term.second << endl;
}

void tokenizer::set_max_term_id(size_t start)
{
    _current_term_id = start;
}

TermID tokenizer::max_term_id() const
{
    return _current_term_id;
}

size_t tokenizer::num_terms() const
{
    return _term_map.size();

}

}
}