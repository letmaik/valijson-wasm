#include <iostream>
#include "json_schema.h"

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    std::cout << "Usage: " << argv[0] << " <schema_json> <input_json>" << std::endl;
    return 1;
  }
  try
  {
    std::ifstream schema_file(argv[1]);
    if (!schema_file.is_open())
    {
      std::cout << "Error opening schema file: " << argv[1] << std::endl;
      return 1;
    }
    std::stringstream schema_buffer;
    schema_buffer << schema_file.rdbuf();

    std::ifstream input_file(argv[2]);
    if (!input_file.is_open())
    {
      std::cout << "Error opening input file: " << argv[2] << std::endl;
      return 1;
    }
    std::stringstream input_buffer;
    input_buffer << input_file.rdbuf();

    auto schema_json = nlohmann::json::parse(schema_buffer.str());
    auto input_json = nlohmann::json::parse(input_buffer.str());

    auto schema_error_msg = json::validate_json(input_json, schema_json);
    if (schema_error_msg.has_value())
    {
      std::cout << "Error validating JSON schema:" << std::endl;
      std::cout << schema_error_msg.value() << std::endl;
      return 1;
    }
    else
    {
      std::cout << "JSON Schema validation succeeded!" << std::endl;
    }
  }
  catch (std::exception& exc)
  {
    std::cout << "Error:" << std::endl;
    std::cout << exc.what() << std::endl;
    return 1;
  }
  return 0;
}