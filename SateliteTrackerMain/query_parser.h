
#pragma once

#include <map>
#include <string>


/**
 * Parser HTTP GET query strings 
 * 
 * e.g. 
 * input = "test1=12345&test2=56789"
 * output = {
 *    "test1" => "12345",
 *    "test2" => "56789"
 * }
 * 
 * @args   query  - query string. 
 * @return result - Hash map key and values.
 * 
 */ 
std::map<std::string, std::string> query_parser(const std::string &query);

